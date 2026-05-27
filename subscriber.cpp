#include <iostream>
#include <cstring>
#include "MQTTClient.h"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "SubscriberClient"
#define TOPIC       "test/topic"
#define QOS         1
#define TIMEOUT     10000L

void delivered(void* context, MQTTClient_deliveryToken dt)
{
    std::cout << "Message delivered token: " << dt << std::endl;
}

int msgarrvd(void* context, char* topicName, int topicLen,
             MQTTClient_message* message)
{
    std::cout << "Received message on topic: " << topicName << std::endl;

    std::string payload(
        (char*)message->payload,
        message->payloadlen
    );

    std::cout << "Message: " << payload << std::endl;

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}

void connlost(void* context, char* cause)
{
    std::cout << "Connection lost: " << cause << std::endl;
}

int main()
{
    MQTTClient client;

    MQTTClient_create(
        &client,
        ADDRESS,
        CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE,
        NULL
    );

    MQTTClient_setCallbacks(
        client,
        NULL,
        connlost,
        msgarrvd,
        delivered
    );

    MQTTClient_connectOptions conn_opts =
        MQTTClient_connectOptions_initializer;

    int rc;

    if ((rc = MQTTClient_connect(client, &conn_opts))
        != MQTTCLIENT_SUCCESS)
    {
        std::cout << "Failed to connect, return code "
                  << rc << std::endl;
        return -1;
    }

    std::cout << "Connected to broker" << std::endl;

    MQTTClient_subscribe(client, TOPIC, QOS);

    std::cout << "Subscribed to topic: " << TOPIC << std::endl;

    std::cout << "Waiting for messages..." << std::endl;

    while (true)
    {
    }

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return 0;
}