int latchpin = 2;
int clockpin = 3;
int datapin = 4;

bool keyboard[64];

void setup() {
    Serial.begin(31250);

    pinMode(latchpin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    pinMode(datapin, INPUT);

    for (int i = 0; i < 64; i++) {
        keyboard[i] = 0;
    }
}

void loop() {
    digitalWrite(latchpin, LOW);
    digitalWrite(latchpin, HIGH);
    for (int i = 0; i < 64; i++) {
        bool state = digitalRead(datapin);
        // Serial.print(state);
        if (state != keyboard[i]) {
            keyboard[i] = state;
            // Serial.print("Note ");
            // Serial.print(i);
            Serial.write(0x90);           // Status
            Serial.write(0x00 + 36 + i);  // Data
            if (state) {
                // Serial.println(": ON");
                Serial.write(0x00 + 127);  // Value
            }
            else {
                // Serial.println(": OFF");
                Serial.write(0x00 + 0);  // Value
            }
        }
        digitalWrite(clockpin, HIGH);
        digitalWrite(clockpin, LOW);
        // delay(5);
    }
}
