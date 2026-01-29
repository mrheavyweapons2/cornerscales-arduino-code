#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const uint64_t address = 0xE8E8F0F0E1LL;

void setup() {
    Serial.begin(9600);

    radio.begin();

    if (!radio.isChipConnected()) {
        Serial.println("NRF24 NOT DETECTED");
        while (1);
    }

    radio.setChannel(76);
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(true);
    radio.setRetries(5, 15);

    radio.openWritingPipe(address);
    radio.stopListening();

    Serial.println("Radio ready");
}

void loop() {
    uint8_t dummy = 42;

    bool tx_ok = false;
    bool tx_fail = false;
    bool rx_ready = false;

    bool write_ok = radio.write(&dummy, sizeof(dummy));

    radio.whatHappened(tx_ok, tx_fail, rx_ready);

    Serial.print("write()=");
    Serial.print(write_ok);
    Serial.print("  tx_ok=");
    Serial.print(tx_ok);
    Serial.print("  tx_fail=");
    Serial.print(tx_fail);
    Serial.print("  rx_ready=");
    Serial.println(rx_ready);

    delay(500);
}