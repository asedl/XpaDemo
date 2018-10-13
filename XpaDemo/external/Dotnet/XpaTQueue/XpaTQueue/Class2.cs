using System;
using System.Collections.Generic;
using System.Text;

using Apache.NMS.ActiveMQ;
using Apache.NMS.ActiveMQ.Commands;
using Apache.NMS;

namespace XpaTQueue
{
    public delegate void MessageReceivedDelegate(string message);

    public class SimpleTopicSubscriber : IDisposable
    {
        private readonly string topicName = null;
        private readonly IConnectionFactory connectionFactory;
        private readonly IConnection connection;
        private readonly ISession session;
        private readonly IMessageConsumer consumer;
        private bool isDisposed = false;
        public event MessageReceivedDelegate OnMessageReceived;

        public SimpleTopicSubscriber(string topicName, string brokerUri, string clientId, string consumerId)
        {
            this.topicName = topicName;
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
            }
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
