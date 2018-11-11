/*
    Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES 
    OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
    OR OTHER DEALINGS IN THE SOFTWARE.
*/

using System;

using Apache.NMS.ActiveMQ;
using Apache.NMS.ActiveMQ.Commands;
using Apache.NMS;

namespace XpaTQueue
{
    // Allows to send a message to a ActiveMq topic
    // Topic name and ActiveMq URI have to be specified when the object is created
    //
    public class SimpleTopicPublisher : IDisposable
    {
        private readonly string topicName = null;
        private readonly IConnectionFactory connectionFactory;
        private readonly IConnection connection;
        private readonly ISession session;
        private readonly IMessageProducer producer;
        private bool isDisposed = false;

        public SimpleTopicPublisher(string topicName, string brokerUri)
        {
            this.topicName = topicName;
            this.connectionFactory = new ConnectionFactory(brokerUri);
            this.connection = this.connectionFactory.CreateConnection();
            this.connection.Start();
            this.session = connection.CreateSession();
            ActiveMQTopic topic = new ActiveMQTopic(topicName);
            this.producer = this.session.CreateProducer(topic);

        }

        public void SendMessage(string message)
        {
            if (!this.isDisposed)
            {
                ITextMessage textMessage = this.session.CreateTextMessage(message);
                this.producer.Send(textMessage);
            }
            else
            {
                throw new ObjectDisposedException(this.GetType().FullName);
            }
        }

        #region IDisposable Members

        public void Dispose()
        {
            if (!this.isDisposed)
            {
                this.producer.Dispose();
                this.session.Dispose();
                this.connection.Dispose();
                this.isDisposed = true;
            }
        }

        #endregion
    }
}
