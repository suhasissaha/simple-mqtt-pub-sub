#include <iostream>
#include <cstring>
#include "MQTTClient.h"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "PublisherClient"
#define TOPIC       "test/topic"
#define PAYLOAD     "Hello MQTT from C++"
#define QOS         1
#define TIMEOUT     10000L

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

    MQTTClient_message pubmsg =
        MQTTClient_message_initializer;

    pubmsg.payload = (void*)PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    MQTTClient_deliveryToken token;

    MQTTClient_publishMessage(
        client,
        TOPIC,
        &pubmsg,
        &token
    );

    std::cout << "Publishing message..." << std::endl;

    MQTTClient_waitForCompletion(
        client,
        token,
        TIMEOUT
    );

    std::cout << "Message delivered" << std::endl;

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return 0;
}