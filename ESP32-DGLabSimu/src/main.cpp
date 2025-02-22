#include <NimBLEDevice.h>

// 定义服务和特性 UUID
#define SERVICE_UUID_1 "955A180A-0FE2-F5AA-A094-84B8D4F3E8AD"
#define CHARACTERISTIC_UUID_1 "955A1500-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c1_data[1] = {100};
#define CHARACTERISTIC_UUID_2 "955A1501-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c2_data[2] = {0x2, 0x10};
#define CHARACTERISTIC_UUID_3 "955A1502-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c3_data[6] = {0xDF, 0xF7, 0xCC, 0x20, 0xEA, 0xEB};

#define SERVICE_UUID_2 "955A180B-0FE2-F5AA-A094-84B8D4F3E8AD"
#define CHARACTERISTIC_UUID_4 "955A1503-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c4_data[3] = {0x2C, 0x81, 0x3E};
#define CHARACTERISTIC_UUID_5 "955A1504-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c5_data[3] = {0x0, 0x0, 0x0};
#define CHARACTERISTIC_UUID_6 "955A1505-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c6_data[3] = {0x0, 0x0, 0x0};
#define CHARACTERISTIC_UUID_7 "955A1506-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c7_data[3] = {0x0, 0x0, 0x0};
#define CHARACTERISTIC_UUID_8 "955A1507-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c8_data[3] = {0x07, 0xD0, 0x07};
#define CHARACTERISTIC_UUID_9 "955A1508-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c9_data[4] = {0x0, 0x0, 0x0, 0x0};
#define CHARACTERISTIC_UUID_10 "955A1509-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c10_data[4] = {0x0, 0x0, 0x0, 0x0};

#define SERVICE_UUID_3 "955A180C-0FE2-F5AA-A094-84B8D4F3E8AD"
#define CHARACTERISTIC_UUID_11 "955A150A-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c11_data[2] = {0x0, 0x1};
#define CHARACTERISTIC_UUID_12 "955A150B-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c12_data[8] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x0};
#define CHARACTERISTIC_UUID_13 "955A150C-0FE2-F5AA-A094-84B8D4F3E8AD"
uint8_t c13_data[7] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};

#define SERVICE_UUID_4 "8E400001-F315-4F60-9FB8-838830DAEA50"
#define CHARACTERISTIC_UUID_14 "8E400001-F315-4F60-9FB8-838830DAEA50"

// 创建服务和特性对象
NimBLEService *pService1;
NimBLEService *pService2;
NimBLEService *pService3;
NimBLEService *pService4;

NimBLECharacteristic *pCharacteristic1;
NimBLECharacteristic *pCharacteristic2;
NimBLECharacteristic *pCharacteristic3;
NimBLECharacteristic *pCharacteristic4;
NimBLECharacteristic *pCharacteristic5;
NimBLECharacteristic *pCharacteristic6;
NimBLECharacteristic *pCharacteristic7;
NimBLECharacteristic *pCharacteristic8;
NimBLECharacteristic *pCharacteristic9;
NimBLECharacteristic *pCharacteristic10;
NimBLECharacteristic *pCharacteristic11;
NimBLECharacteristic *pCharacteristic12;
NimBLECharacteristic *pCharacteristic13;
NimBLECharacteristic *pCharacteristic14;

NimBLEServer* pServer;

// 设备连接和断开回调
class MyCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        Serial.println("设备已连接");
    }

    void onDisconnect(NimBLEServer* pServer) {
        Serial.println("设备已断开");
    }

};

// 特性读写回调
class MyCharacteristicCallbacks : public NimBLECharacteristicCallbacks {
    unsigned long last_recv_time = 0;
    void onRead(NimBLECharacteristic* pCharacteristic) {
        Serial.print("特性 ");
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.println(" 被读取");
    }

    void onWrite(NimBLECharacteristic* pCharacteristic) {
        auto cur_time = millis();
        if(last_recv_time == 0) {
            last_recv_time = cur_time;
        }
        unsigned long delta_time_ms = cur_time - last_recv_time;
        last_recv_time = cur_time;
        Serial.print("特性 ");
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.print(" 被写入。新值: ");
        std::string value = pCharacteristic->getValue();
        for (size_t i = 0; i < value.length(); i++) {
            Serial.printf("%02X ", (uint8_t)value[i]);
        }
        Serial.println();
        Serial.print("耗时: ");
        Serial.print(delta_time_ms);
        Serial.println("ms");
    }

    void onNotify(NimBLECharacteristic* pCharacteristic) {
        Serial.print("特性 ");
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.println(" 被Nofify。");
    }

};

void setup() {
    Serial.begin(115200);
    NimBLEDevice::init("D-LAB ESTIM01");

    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyCallbacks());

    // 创建服务
    pService1 = pServer->createService(SERVICE_UUID_1);
    pService2 = pServer->createService(SERVICE_UUID_2);
    pService3 = pServer->createService(SERVICE_UUID_3);
    pService4 = pServer->createService(SERVICE_UUID_4);

    // 创建特性并添加回调
    pCharacteristic1 = pService1->createCharacteristic(
        CHARACTERISTIC_UUID_1,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    pCharacteristic1->setValue(c1_data, 1);
    pCharacteristic1->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic2 = pService1->createCharacteristic(
        CHARACTERISTIC_UUID_2,
        NIMBLE_PROPERTY::READ
    );
    pCharacteristic2->setValue(c2_data, 2);
    pCharacteristic2->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic3 = pService1->createCharacteristic(
        CHARACTERISTIC_UUID_3,
        NIMBLE_PROPERTY::READ
    );
    pCharacteristic3->setValue(c3_data, 6);
    pCharacteristic3->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic4 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_4,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic4->setValue(c4_data, 3);
    pCharacteristic4->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic5 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_5,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR | NIMBLE_PROPERTY::NOTIFY
    );
    pCharacteristic5->setValue(c5_data, 3);
    pCharacteristic5->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic6 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_6,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic6->setValue(c6_data, 3);
    pCharacteristic6->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic7 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_7,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic7->setValue(c7_data, 3);
    pCharacteristic7->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic8 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_8,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic8->setValue(c8_data, 3);
    pCharacteristic8->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic9 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_9,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    pCharacteristic9->setValue(c9_data, 4);
    pCharacteristic9->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic10 = pService2->createCharacteristic(
        CHARACTERISTIC_UUID_10,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic10->setValue(c10_data, 4);
    pCharacteristic10->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic11 = pService3->createCharacteristic(
        CHARACTERISTIC_UUID_11,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
    );
    pCharacteristic11->setValue(c11_data, 2);
    pCharacteristic11->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic12 = pService3->createCharacteristic(
        CHARACTERISTIC_UUID_12,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    pCharacteristic12->setValue(c12_data, 8);
    pCharacteristic12->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic13 = pService3->createCharacteristic(
        CHARACTERISTIC_UUID_13,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
    );
    pCharacteristic13->setValue(c13_data, 7);
    pCharacteristic13->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic14 = pService4->createCharacteristic(
        CHARACTERISTIC_UUID_14,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );
    pCharacteristic14->setCallbacks(new MyCharacteristicCallbacks());

    // 启动服务
    pService1->start();
    pService2->start();
    pService3->start();
    pService4->start();


    // 开始广播
    NimBLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    Serial.println("开始广播");
}

void loop() {
    delay(1000);
}