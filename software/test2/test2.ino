int latchpin = 2;
int clockpin = 3;
int datapin = 4;
// int stopspin = 5;
bool keyboard[64];
// bool stops[8];


// int volumepin = A0;
// int volume = 0;


void setup() {
    Serial.begin(31250);

    pinMode(latchpin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    pinMode(datapin, INPUT);
    // pinMode(stopspin, INPUT);

    for (int i = 0; i < 64; i++) {
        keyboard[i] = 0;
    }

    // for (int i = 0; i < 8; i++) {
    //     stops[i] = 0;
    // }

    // pinMode(volumepin, INPUT);
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
    }
    
    // digitalWrite(latchpin, LOW);
    // digitalWrite(latchpin, HIGH);
    // for (int i = 0; i < 8; i++) {
    //     bool state = digitalRead(stopspin);
    //     if (state && !stops[i]) {
    //         Serial.write(0x91);      // Status
    //         Serial.write(0x00 + i);  // Data
    //         Serial.write(0x00 + 127);  // Value
    //         comb_num = i + 1;
    //     }
    //     if (state != stops[i]) {
    //         stops[i] = state;
    //     }
    //     digitalWrite(clockpin, HIGH);
    //     digitalWrite(clockpin, LOW);
    // }

    // Recieve midi message
    // if (Serial.available() > 0) {
    //     if (Serial.read() == 144 && Serial.available() > 0) {
    //         comb_num = Serial.read();
    //     }
    // }
        
    // int newvolume = analogRead(volumepin) / 8;
    // if (newvolume != volume) {
    //     volume = newvolume;
    //     Serial.write(0xb0);           // Status
    //     Serial.write(0x07);           // Data
    //     Serial.write(0x00 + volume);  // Value
    // }
}
