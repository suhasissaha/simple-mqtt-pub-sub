````markdown
# Simple MQTT Publish/Subscribe Example in C++

A minimal MQTT publish/subscribe example using:

- Eclipse Paho MQTT C Client Library
- Mosquitto MQTT Broker
- C++
- macOS + Homebrew

This project demonstrates:
- MQTT broker setup
- MQTT publisher
- MQTT subscriber
- Topic-based messaging
- Basic MQTT workflow using C++

---

# Project Structure

```text
.
├── publisher.cpp
├── subscriber.cpp
└── README.md
````

---

# MQTT Overview

MQTT (Message Queuing Telemetry Transport) is a lightweight publish-subscribe messaging protocol commonly used in:

* IoT systems
* Embedded devices
* Telemetry
* Real-time messaging
* Low-bandwidth communication

Architecture:

```text
Publisher ---> MQTT Broker ---> Subscriber
```

Example topic:

```text
test/topic
```

---

# Prerequisites

* macOS
* Homebrew
* g++

Install Homebrew if needed:

[https://brew.sh](https://brew.sh)

---

# Install Dependencies

## Install Mosquitto Broker

```bash
brew install mosquitto
```

## Install Eclipse Paho MQTT C Client Library

```bash
brew install libpaho-mqtt
```

---

# Configure Mosquitto

Create the configuration file:

```bash
cp /opt/homebrew/etc/mosquitto/mosquitto.conf.example \
   /opt/homebrew/etc/mosquitto/mosquitto.conf
```

For simple local testing, replace the config with:

```bash
cat > /opt/homebrew/etc/mosquitto/mosquitto.conf <<'EOF'
listener 1883
allow_anonymous true
EOF
```

---

# Start MQTT Broker

## Run as Background Service

```bash
brew services start mosquitto
```

Verify:

```bash
brew services list | grep mosquitto
```

Check if port 1883 is listening:

```bash
lsof -iTCP:1883 -sTCP:LISTEN
```

---

## Run Manually (Foreground)

```bash
/opt/homebrew/opt/mosquitto/sbin/mosquitto \
-c /opt/homebrew/etc/mosquitto/mosquitto.conf -v
```

---

# Compile

## Subscriber

```bash
g++ subscriber.cpp -o subscriber \
-I"$(brew --prefix libpaho-mqtt)/include" \
-L"$(brew --prefix libpaho-mqtt)/lib" \
-lpaho-mqtt3c
```

## Publisher

```bash
g++ publisher.cpp -o publisher \
-I"$(brew --prefix libpaho-mqtt)/include" \
-L"$(brew --prefix libpaho-mqtt)/lib" \
-lpaho-mqtt3c
```

---

# Run

## Start Subscriber

```bash
./subscriber
```

Expected output:

```text
Connected to broker
Subscribed to topic: test/topic
Waiting for messages...
```

---

## Run Publisher

```bash
./publisher
```

Expected output:

```text
Connected to broker
Publishing message...
Message delivered
```

Subscriber output:

```text
Received message on topic: test/topic
Message: Hello MQTT from C++
```

---

# Useful Mosquitto CLI Tools

## Subscribe

```bash
mosquitto_sub -h 127.0.0.1 -p 1883 -t test/topic -v
```

## Publish

```bash
mosquitto_pub -h 127.0.0.1 -p 1883 -t test/topic -m "hello"
```

These tools are useful for debugging MQTT applications.

---

# MQTT Concepts Covered

* MQTT Broker
* Publisher/Subscriber Model
* Topics
* QoS
* Persistent TCP Connections
* Callback-based Message Handling

---

# Common Issues

## MQTTClient.h file not found

Install Paho library:

```bash
brew install libpaho-mqtt
```

Compile with include/library paths:

```bash
-I"$(brew --prefix libpaho-mqtt)/include"
-L"$(brew --prefix libpaho-mqtt)/lib"
```

---

## Failed to connect, return code -1

Ensure:

* Mosquitto broker is running
* Port 1883 is listening
* Broker address is correct

Recommended broker address:

```cpp
#define ADDRESS "tcp://127.0.0.1:1883"
```

---

# References

* Eclipse Paho MQTT:
  [https://github.com/eclipse-paho](https://github.com/eclipse-paho)

* Paho C Client:
  [https://github.com/eclipse-paho/paho.mqtt.c](https://github.com/eclipse-paho/paho.mqtt.c)

* Mosquitto:
  [https://mosquitto.org](https://mosquitto.org)

* MQTT Specification:
  [https://mqtt.org](https://mqtt.org)

---

# License

MIT License

```
```
