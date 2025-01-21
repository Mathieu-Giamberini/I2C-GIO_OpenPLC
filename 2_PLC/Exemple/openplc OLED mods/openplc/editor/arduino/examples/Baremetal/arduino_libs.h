//disable pins
//uint8_t disabled_pins[11] = {1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}; //10 pins max. First array position is used as index
extern uint8_t pinMask_DIN[];
extern uint8_t pinMask_AIN[];
extern uint8_t pinMask_DOUT[];
extern uint8_t pinMask_AOUT[];

#ifdef USE_OLED_BLOCK
    
    #include <string.h>
    #include <SPI.h>
    #include <Wire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>

    extern "C" void *init_oled(uint8_t);
    extern "C" void write_oled(void *,char *,char *,char *,char *);
    int8_t oled_toggle;
    char buffer[22];

    char* str2chr(String S){
        if(S.length()!=0){
            char *p = const_cast<char*>(S.c_str());
            return p;
        }
    }
    void substring(char s[], char sub[], int p, int l) {
    int c = 0;
    
    while (c < l) {
        sub[c] = s[p+c-1];
        c++;
    }
    sub[c] = '\0';
    }

    // if pin is 0 then use default I2C
    void *init_oled(uint8_t pin) 
    {
        oled_toggle = 0;

        Adafruit_SSD1306 *oled; 
        TwoWire CustomI2C0(0, 1);
        delay(50);   
        oled = new Adafruit_SSD1306(128, 32, &CustomI2C0);        
        oled->begin(0x3c);     
        oled->display();       
        delay(2000); 
        oled->clearDisplay();
        oled->setTextSize(1);      // Normal 1:1 pixel scale   
        oled->setTextColor(SSD1306_WHITE);             
        oled->setCursor(0, 0);
        oled->println("Ready.");         
        oled->display();         
        delay(100);         
        return oled;             
    }
   
    void write_oled(void *class_pointer, char * line1,char * line2,char * line3,char * line4)
    {            
        
        Adafruit_SSD1306 *oled = (Adafruit_SSD1306 *)class_pointer;  

         //once every 200ms. PLC loop is 50ms
        if (oled_toggle++ < 4) return; oled_toggle = 0;
        
        /* OLED is 128x32 or 128x64, font is a 6x8
           this limits the text to 21 characters on either display
        */
        oled->clearDisplay();          
        oled->setTextColor(SSD1306_WHITE); // Draw white text         
        oled->setCursor(0, 0);
        buffer[0] = '\0';
        
        if (strlen(line1) > 21) 
        {   memcpy(buffer,line1,21);
            buffer[21] = '\0';
        } else if (strlen(line1) > 1) strcpy(buffer,line1);  
        oled->println(F(buffer)); 
        
        if (strlen(line2) > 21) 
        {   memcpy(buffer,line2,21);
            buffer[21] = '\0';
        } else if (strlen(line1) > 1) strcpy(buffer,line2);  
        oled->println(F(buffer)); 

        if (strlen(line3) > 21) 
        {   memcpy(buffer,line3,21);
            buffer[21] = '\0';
        } else if (strlen(line1) > 1) strcpy(buffer,line3);  
        oled->println(F(buffer)); 

        if (strlen(line4) > 21) 
        {   memcpy(buffer,line4,21);
            buffer[21] = '\0';
        } else if (strlen(line1) > 1) strcpy(buffer,line4);  
        oled->println(F(buffer)); 
        oled->display(); 
        return;
    }

#endif

#ifdef USE_DHT11_BLOCKS
    #include "picoDHT.h"

    extern "C" void *init_dht11(uint8_t);
    extern "C" int request_dht11(void *);
    extern "C" int16_t read_dht11_temp(void *);
    extern "C" int8_t read_dht11_humidity(void *);
    int8_t dht_toggle = 0;
    
    void *init_dht11(uint8_t pin) 
    {
        DHT *dht;
        dht_toggle = 0;
        dht = new DHT(pin);
        return dht;    
    }

    int request_dht11(void *class_pointer)
    {
        if (dht_toggle++ < 20) return DHT_PENDING; dht_toggle = 0;
        DHT *dht = (DHT *)class_pointer;
        return dht->read();         
    }

    int16_t read_dht11_temp(void *class_pointer)
    {    
        DHT *dht = (DHT *)class_pointer;
        return dht->getTemperature(); 
    }
    
    int8_t read_dht11_humidity(void *class_pointer)
    {    
        DHT *dht = (DHT *)class_pointer;
        return dht->getHumidity();
    }

#endif

#ifdef USE_DS18B20_BLOCK
    #include <OneWire.h>
    #include <DallasTemperature.h>

    extern "C" void *init_ds18b20(uint8_t);
    extern "C" void request_ds18b20_temperatures(void *);
    extern "C" float read_ds18b20(void *, uint8_t);

    void *init_ds18b20(uint8_t pin)
    {
        //Disable pin
        //disabled_pins[disabled_pins[0]] = pin;
        //if (disabled_pins[0] < 10) disabled_pins[0]++;
        for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
        {
            if (pinMask_DIN[i] == pin)
                pinMask_DIN[i] = 255;
        }
        for (int i = 0; i < NUM_ANALOG_INPUT; i++)
        {
            if (pinMask_AIN[i] == pin)
                pinMask_AIN[i] = 255;
        }
        for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
        {
            if (pinMask_DOUT[i] == pin)
                pinMask_DOUT[i] = 255;
        }
        for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
        {
            if (pinMask_AOUT[i] == pin)
                pinMask_AOUT[i] = 255;
        }
        
        OneWire *oneWire;
        DallasTemperature *sensors;
        oneWire = new OneWire(pin);
        sensors = new DallasTemperature(oneWire);
        sensors->begin();
        return sensors;
    }
    void request_ds18b20_temperatures(void *class_pointer)
    {
        DallasTemperature *sensors = (DallasTemperature *)class_pointer;
        sensors->requestTemperatures();
    }
    float read_ds18b20(void *class_pointer, uint8_t index)
    {
        DallasTemperature *sensors = (DallasTemperature *)class_pointer;
        return sensors->getTempCByIndex(index);
    }
#endif

#ifdef USE_P1AM_BLOCKS
    #include <P1AM.h>
    extern "C" uint8_t p1am_init();
    extern "C" void p1am_writeDiscrete(uint32_t, uint8_t, uint8_t);
    extern "C" uint32_t p1am_readDiscrete(uint8_t, uint8_t);
    
    uint8_t modules_initialized = 0;
    
    uint8_t p1am_init()
    {
        if (modules_initialized == 0)
        {
            modules_initialized = P1.init();
            //P1.init takes a while, so we need to reset scan cycle timer
            timer_ms = millis() + scan_cycle;
        }
        
        return modules_initialized;
    }
    
    void p1am_writeDiscrete(uint32_t data, uint8_t slot, uint8_t channel)
    {
        P1.writeDiscrete(data, slot, channel);
    }
    
    uint32_t p1am_readDiscrete(uint8_t slot, uint8_t channel)
    {
        return P1.readDiscrete(slot, channel);
    }
#endif

#ifdef USE_CLOUD_BLOCKS
    #include <ArduinoIoTCloud.h>
    #include <Arduino_ConnectionHandler.h>
    
    extern "C" void cloud_begin(char *, char *, char *);
    extern "C" void cloud_add_bool(char *, int *);
    extern "C" void cloud_add_int(char *, int *);
    extern "C" void cloud_add_float(char *, float *);
    extern "C" void cloud_update();
    
    bool first_update = true;
    
    WiFiConnectionHandler *ArduinoIoTPreferredConnection;
    
    void cloud_begin(char *thing_id, char *str_ssid, char *str_pass)
    {
        Serial.begin(9600);
        ArduinoIoTPreferredConnection = new WiFiConnectionHandler(str_ssid, str_pass);
        ArduinoCloud.setThingId(thing_id);
    }
    
    void cloud_update()
    {
        if (first_update)
        {
            first_update = false;
            ArduinoCloud.begin(*ArduinoIoTPreferredConnection);
        
            //Temporary
            setDebugMessageLevel(4);
            ArduinoCloud.printDebugInfo();
        }
        ArduinoCloud.update();
    }
    
    void cloud_add_bool(char *var_name, int *bool_var)
    {
        ArduinoCloud.addPropertyReal(*bool_var, String(var_name));
    }
    
    void cloud_add_int(char *var_name, int *int_var)
    {
        ArduinoCloud.addPropertyReal(*int_var, String(var_name));
    }
    
    void cloud_add_float(char *var_name, float *float_var)
    {
        ArduinoCloud.addPropertyReal(*float_var, String(var_name));
    }
    
#endif