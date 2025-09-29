#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display


int latchpin = 2;
int clockpin = 3;
int datapin = 4;
int stopspin = 5;
bool keyboard[64];
bool stops[8];

char buffer[3];
char disp[3];
char comb_num = 0;


// int volumepin = A0;
// int volume = 0;


void setup() {
    u8g2.begin(); // start the u8g2 library
    Serial.begin(31250);

    pinMode(latchpin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    pinMode(datapin, INPUT);
    pinMode(stopspin, INPUT);

    for (int i = 0; i < 64; i++) {
        keyboard[i] = 0;
    }

    for (int i = 0; i < 8; i++) {
        stops[i] = 0;
    }

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
    
    digitalWrite(latchpin, LOW);
    digitalWrite(latchpin, HIGH);
    for (int i = 0; i < 8; i++) {
        bool state = digitalRead(stopspin);
        if (state && !stops[i]) {
            Serial.write(0x91);      // Status
            Serial.write(0x00 + i);  // Data
            Serial.write(0x00 + 127);  // Value
            comb_num = i + 1;
        }
        if (state != stops[i]) {
            stops[i] = state;
        }
        digitalWrite(clockpin, HIGH);
        digitalWrite(clockpin, LOW);
    }

    // Recieve midi message
    if (Serial.available() > 0) {
        if (Serial.read() == 144 && Serial.available() > 0) {
            comb_num = Serial.read();
        }
    }

    // Display on screen
    u8g2.clearBuffer();  // clear the internal memory
    u8g2.setBitmapMode(1);
    u8g2.setFont(u8g2_font_logisoso62_tn);
    sprintf(buffer, "00%d", comb_num);
    u8g2.drawStr(4, 63, buffer);
    u8g2.sendBuffer();  // transfer internal memory to the display
        
    // int newvolume = analogRead(volumepin) / 8;
    // if (newvolume != volume) {
    //     volume = newvolume;
    //     Serial.write(0xb0);           // Status
    //     Serial.write(0x07);           // Data
    //     Serial.write(0x00 + volume);  // Value
    // }
}
