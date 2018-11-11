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
using System.Threading;

using Apache.NMS.ActiveMQ;
using Apache.NMS.ActiveMQ.Commands;
using Apache.NMS;
using Apache.NMS.Util;

namespace XpaTQueue
{
    // Allows to consume messages from ActiveMQ queues.
    // Session with ActiveMQ is created if the class is instantiated.

    //
    public class SimpleConsumer : IDisposable
    {

        protected static AutoResetEvent semaphore = new AutoResetEvent(false);
        protected static ITextMessage message = null;
        private TimeSpan receiveTimeout;

        private readonly string queuename = null;
        private readonly IConnectionFactory connectionFactory;
        private readonly IConnection connection;
        private readonly ISession session;
        private readonly IMessageConsumer consumer;
        private bool isDisposed = false;

        protected TimeSpan ReceiveTimeout { get => receiveTimeout; set => receiveTimeout = value; }

        public SimpleConsumer(string queuename, string brokerUri, int timeoutms, AcknowledgementMode acknowledgeMode )
        {
            this.queuename = queuename;
            this.receiveTimeout = TimeSpan.FromMilliseconds(timeoutms);

            this.connectionFactory = new ConnectionFactory(brokerUri);
            this.connection = this.connectionFactory.CreateConnection();
            this.connection.Start();

            this.session = connection.CreateSession(acknowledgeMode);

            IDestination destination = SessionUtil.GetDestination(session, "queue://" + queuename);

            this.consumer = session.CreateConsumer(destination);

        }

        public ITextMessage ConsumeMessage()
        {
            if (!this.isDisposed)
            {
                // Wait for a message
                IMessage m = consumer.Receive(receiveTimeout);
                if (m != null) {
                    message = m as ITextMessage;
                    return message;
                }
            }
            else
            {
                throw new ObjectDisposedException(this.GetType().FullName);
            }

            return null;
        }

        protected static void OnMessage(IMessage receivedMsg)
        {
            message = receivedMsg as ITextMessage;
            semaphore.Set();
        }

        #region IDisposable Members

        public void Dispose()
        {
            if (!this.isDisposed)
            {
                this.consumer.Dispose();
                this.session.Dispose();
                this.connection.Dispose();
                this.isDisposed = true;
            }
        }

        #endregion
    }
}
