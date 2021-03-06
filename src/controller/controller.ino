
#define PIN_SCLK 2
#define PIN_MOSI 4
#define PIN_SS 3

void setup()
{
    pinMode(PIN_SCLK, OUTPUT);
    pinMode(PIN_MOSI, OUTPUT);
    pinMode(PIN_SS, OUTPUT);
    digitalWrite(PIN_SCLK, HIGH);
    digitalWrite(PIN_MOSI, HIGH);
    digitalWrite(PIN_SS, HIGH);
}

void loop()
{   
    static uint8_t freq = 0;

    freq++;

    writeByte(0, 0); // PHCA
    writeByte(1, 255); // PHCB
    writeByte(2, 0xF8); // ASKB|ASKA
    writeByte(3, 8); // PW
    writeByte(4, 0);  // WF 0 sine, 1 sawtooth, 2 triangle, 3 pulse
    writeByte(5, 0);  // FCAH
    writeByte(6, 4);  // FCAL
    writeByte(7, 0);  // FCBH
    writeByte(8, freq);  // FCBL

    delay(10);
}

void writeByte(uint8_t address, uint8_t data)
{
    digitalWrite(PIN_SS, HIGH);

    for (uint8_t ix = 4; ix < 8; ix++)
    {
        writeBit(((address << ix) & 0x80) == 0x80);
    }

    for (uint8_t ix = 0; ix < 8; ix++)
    {
        writeBit(((data << ix) & 0x80) == 0x80);
    }

    digitalWrite(PIN_SS, LOW);
}

void writeBit(bool bit)
{
    digitalWrite(PIN_MOSI, bit);
    digitalWrite(PIN_SCLK, LOW);    
    digitalWrite(PIN_SCLK, HIGH);    
}