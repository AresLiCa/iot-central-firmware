// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.

#ifndef PAIRING_CONTROLLER
#define PAIRING_CONTROLLER

#include "AZ3166WiFi.h"
#include "AZ3166WiFiUdp.h"
#include "globals.h"
#include "loop.h"

class WiFiUDP;
class PairingController : public LoopController
{
    bool setupCompleted;
    WiFiUDP *udpClient;

    void listen();
    void pair();
    void cleanup();

    PairingController() : setupCompleted(false)
    {
        listen();
    }

private:
    bool startPairing();
    bool receiveData();
    bool storeConfig();
    bool broadcastSuccess();

public:
    static PairingController *New()
    {
        return new PairingController();
    }

    bool withTelemetry() override { return false; }

    void loop() override;

    ~PairingController()
    {
        cleanup();
    }
};

#endif // PAIRING_CONTROLLER