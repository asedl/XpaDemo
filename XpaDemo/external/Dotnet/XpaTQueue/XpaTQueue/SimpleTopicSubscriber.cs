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
    public delegate void MessageReceivedDelegate(string message);

    public class QueueEventArgs : EventArgs
    {
        private int nrings;

        //Constructor.
        //
        public QueueEventArgs(int nrings)
        {
            this.nrings = nrings;
        }

        public int NumRings
        {
            get { return nrings; }
        }

        public string EventText
        {
            get
            {
                return ("EventText: " + nrings);
            }
        }
    }


    // When instantiated object subscribes to a ActiveMQ topic.
    // Topic name, broker uri and other things have to be specified when object is created (see constructor)
    // The object then creates a durable consumer and notifies callee by raising an event if a message for this 
    // topic is received.
    //
    public class SimpleTopicSubscriber : IDisposable
    {
        private readonly string topicName = null;
        private readonly string consumerId = null;
        private readonly IConnectionFactory connectionFactory;
        private readonly IConnection connection;
        private readonly ISession session;
        private readonly IMessageConsumer consumer;
        private bool isDisposed = false;

        // Delegate declaration.
        //
        public delegate void QueueEventHandler(object sender, QueueEventArgs e);

        public event MessageReceivedDelegate OnMessageReceived;

        public event QueueEventHandler QueueEvent;

        // The protected OnQueueEvent method raises the event by invoking
        // the delegates. The sender is always this, the current instance
        // of the class.
        //
        protected virtual void OnQueueEvent(QueueEventArgs e)
        {
            QueueEventHandler handler = QueueEvent;
            if (handler != null)
            {
                // Invokes the delegates.
                handler(this, e);
            }
        }

        public SimpleTopicSubscriber(string topicName, string brokerUri, string clientId, string consumerId)
        {
            this.topicName = topicName;
            this.consumerId = consumerId;
            this.connectionFactory = new ConnectionFactory(brokerUri);
            this.connection = this.connectionFactory.CreateConnection();
            this.connection.ClientId = clientId;
            this.connection.Start();
            this.session = connection.CreateSession();
            ActiveMQTopic topic = new ActiveMQTopic(topicName);
            this.consumer = this.session.CreateDurableConsumer(topic, consumerId, "2 > 1", false);
            this.consumer.Listener += new MessageListener(OnMessage);

        }

        public void OnMessage(IMessage message)
        {
            ITextMessage textMessage = message as ITextMessage;
            if (this.OnMessageReceived != null)
            {
                this.OnMessageReceived(textMessage.Text);

//                QueueEventArgs e = new QueueEventArgs(0);
//                OnQueueEvent(e);
            }
        }

        public void DeleteDurableConsumer() {
            this.session.DeleteDurableConsumer(consumerId);
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
