using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace ParameterParser
{
    internal class CharContext
    {
        private readonly char _keyValuesplitter;

        public CharContext(char value, char keyValuesplitter = '=')
        {
            _keyValuesplitter = keyValuesplitter;
            Value = value;
            _isBetweenQuotes = new Lazy<bool>(GetIsBetweenQuotes);
        }

        public CharContext Previous { get; set; }
        public CharContext Next { get; set; }
        public char Value { get; private set; }

        private readonly Lazy<bool> _isBetweenQuotes;
        private bool IsBetweenQuotes
        {
            get
            {
                return _isBetweenQuotes.Value;
            }
        }

        private bool GetIsBetweenQuotes()
        {
            if (Previous == null) return false;
            if (Value != '"') return Previous.IsBetweenQuotes;
            if (IsToEscape || IsEscapedQuote) return Previous.IsBetweenQuotes;
            return !Previous.IsBetweenQuotes;
        }

        private bool UnEscapedQuote
        {
            get
            {
                if (Value != '"') return false;
                if (Previous == null) return true;
                return !Previous.IsToEscape;
            }
        }

        private bool IsToEscape
        {
            get
            {
                if (Previous == null ||
                    Next == null ||
                    Value != '"' ||
                    Next.Value != '"') return false;
                return !Previous.IsToEscape;
            }
        }

        private bool IsEscapedQuote
        {
            get
            {
                if (Previous == null ||
                    Value != '"') return false;
                return Previous.IsToEscape;
            }
        }

        public bool IsNetto
        {
            get
            {
                return !(IsToEscape || IsBetweenParameters || UnEscapedQuote);
            }
        }

        public bool IsBetweenParameters
        {
            get
            {
                return Value == ' ' && !IsBetweenQuotes;
            }
        }

        public bool IsFirstBetweenParameters
        {
            get
            {
                return IsBetweenParameters && !Previous.IsBetweenParameters;
            }
        }

        public bool IsKeyValueSplitter
        {
            get
            {
                return Value == _keyValuesplitter && !IsBetweenQuotes;
            }
        }

        public override string ToString() // Makes debugging easier
        {
            return Value.ToString();
        }
    }

    internal class BareParametersParser
    {
        private readonly char _keyValuesplitter;
        private readonly string _text;

        public BareParametersParser(string text, char keyValuesplitter = '=')
        {
            _keyValuesplitter = keyValuesplitter;
            _text = text.Trim();
        }

        private IEnumerable<CharContext> CharContexts
        {
            get
            {
                var enumerator = _text.GetEnumerator();

                // go to the first char
                if (!enumerator.MoveNext())
                    yield break;

                CharContext previous = null;
                char value = enumerator.Current;

                //  Continue with the second char
                while (enumerator.MoveNext())
                {
                    var next = new CharContext(enumerator.Current, _keyValuesplitter);
                    var context = new CharContext(value, _keyValuesplitter)
                    {
                        Previous = previous,
                        Next = next
                    };
                    yield return context;

                    previous = context;
                    value = next.Value;
                }

                // Return the last char
                var last = new CharContext(value, _keyValuesplitter)
                {
                    Previous = previous,
                    Next = null
                };
                yield return last;
            }
        }

        public IEnumerable<Parameter> Parameters
        {
            get
            {
                var parameterChars = new List<CharContext>();
                var index = 0;
                foreach (var charContext in CharContexts)
                {
                    if (!charContext.IsBetweenParameters)
                    {
                        parameterChars.Add(charContext);
                    }
                    if (charContext.IsFirstBetweenParameters && parameterChars.Any())
                    {
                        yield return new Parameter(parameterChars, index);
                        parameterChars = new List<CharContext>();
                        index++;
                    }

                }
                if (parameterChars.Any())
                {
                    yield return new Parameter(parameterChars, index);
                }
            }
        }
    }
    public class Parameter
    {
        public int Index { get; private set; }
        private readonly IEnumerable<CharContext> _charContexts;

        internal Parameter(IEnumerable<CharContext> charContexts, int index)
        {
            Index = index;
            _charContexts = charContexts;
        }

        public override string ToString()
        {
            return Bruto;
        }

        // Including quotes
        public string Bruto
        {
            get
            {
                var charInfos = _charContexts.Select(c => c.Value);
                return new string(charInfos.ToArray());
            }
        }

        // Excluding quotes
        public string Netto
        {
            get
            {
                var charInfos = _charContexts.Where(c => c.IsNetto).Select(c => c.Value);
                return new string(charInfos.ToArray());
            }
        }

        public string Key
        {
            get
            {
                if (!HasValue)
                {
                    return Netto;
                }
                var valueChars = _charContexts.Take(IndexOfKeyValueSplitter)
                    .Where(c => c.IsNetto)
                    .Select(v => v.Value);
                var result = new string(valueChars.ToArray());
                return result;
            }
        }

        public bool HasValue
        {
            get
            {
                return IndexOfKeyValueSplitter > -1;
            }
        }

        public string Value
        {
            get
            {
                if (!HasValue)
                {
                    return null;
                }
                var valueChars = _charContexts.Skip(IndexOfKeyValueSplitter + 1)
                    .Where(c => c.IsNetto)
                    .Select(v => v.Value);
                var result = new string(valueChars.ToArray());
                return result;
            }
        }

        private int IndexOfKeyValueSplitter
        {
            get
            {
                for (var index = 0; index < _charContexts.Count(); index++)
                {
                    var charContext = _charContexts.ElementAt(index);
                    if (charContext.IsKeyValueSplitter)
                    {
                        return index;
                    }
                }
                return -1;
            }
        }

    }

    public class ParametersParser : IEnumerable<Parameter>
    {
        private readonly bool _caseSensitive;
        private readonly List<Parameter> _parameters;
        public string ParametersText { get; private set; }

        public ParametersParser(
            string parametersText = null,
            bool caseSensitive = false,
            char keyValuesplitter = '=')
        {
            _caseSensitive = caseSensitive;
            ParametersText = parametersText != null ? parametersText : GetAllParametersText();
            _parameters = new BareParametersParser(ParametersText, keyValuesplitter)
                                 .Parameters.ToList();
        }

        public ParametersParser(bool caseSensitive)
            : this(null, caseSensitive)
        {
        }

        public IEnumerable<Parameter> GetParameters(string key)
        {
            return _parameters.Where(p => p.Key.Equals(key, ThisStringComparison));
        }

        public IEnumerable<string> GetValues(string key)
        {
            return GetParameters(key).Where(p => p.HasValue).Select(p => p.Value);
        }

        public string GetFirstValue(string key)
        {
            return GetFirstParameter(key).Value;
        }

        public Parameter GetFirstParameterOrDefault(string key)
        {
            return ParametersWithDistinctKeys.FirstOrDefault(KeyEqualsPredicate(key));
        }

        public Parameter GetFirstParameter(string key)
        {
            return ParametersWithDistinctKeys.First(KeyEqualsPredicate(key));
        }

        private Func<Parameter, bool> KeyEqualsPredicate(string key)
        {
            return p => p.Key.Equals(key, ThisStringComparison);
        }

        public IEnumerable<string> Keys
        {
            get
            {
                return _parameters.Select(p => p.Key);
            }
        }

        public IEnumerable<string> DistinctKeys
        {
            get
            {
                return ParametersWithDistinctKeys.Select(p => p.Key);
            }
        }

        public IEnumerable<Parameter> ParametersWithDistinctKeys
        {
            get
            {
                return _parameters.GroupBy(k => k.Key, ThisEqualityComparer).Select(k => k.First());
            }
        }

        public bool HasKey(string key)
        {
            return GetParameters(key).Any();
        }

        public bool HasKeyAndValue(string key)
        {
            var parameter = GetFirstParameterOrDefault(key);
            return parameter != null && parameter.HasValue;
        }

        public bool HasKeyAndNoValue(string key)
        {
            var parameter = GetFirstParameterOrDefault(key);
            return parameter != null && !parameter.HasValue;
        }

        private IEqualityComparer<string> ThisEqualityComparer
        {
            get
            {
                return _caseSensitive ? StringComparer.Ordinal : StringComparer.OrdinalIgnoreCase;
            }
        }

        private StringComparison ThisStringComparison
        {
            get
            {
                return _caseSensitive ? StringComparison.Ordinal : StringComparison.OrdinalIgnoreCase;
            }
        }

        public bool HasHelpKey
        {
            get
            {
                return HelpParameters.Any(h =>
                    _parameters.Any(p => p.Key.Equals(h, StringComparison.OrdinalIgnoreCase)));
            }
        }

        public static IEnumerable<string> HelpParameters
        {
            get
            {
                return new[] { "?", "help", "-?", "/?", "-help", "/help" };
            }
        }

        private static string GetAllParametersText()
        {
            var everything = Environment.CommandLine;
            var executablePath = Environment.GetCommandLineArgs()[0];

            var result = everything.StartsWith("\"") ?
                everything.Substring(executablePath.Length + 2) :
                everything.Substring(executablePath.Length);
            result = result.TrimStart(' ');
            return result;
        }

        public IEnumerator<Parameter> GetEnumerator()
        {
            return _parameters.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public Parameter this[int index]
        {
            get
            {
                return _parameters[index];
            }
        }

        public int Count
        {
            get
            {
                return _parameters.Count;
            }
        }
    }
}
