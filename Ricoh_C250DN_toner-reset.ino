
/*******************************************************************
 * By abbreza
**  Download from:                                                **
**  https://github.com/abbreza/RicohC250DN                        **
**                                                                **
**  Based on Code from:               **
**  http://arduino.cc/playground/                      
*  https://esdblog.org/ricoh-sp-c250dn-laser-printer-toner-hack/  **
**  Fun project. No commercial use is allowed                     **
**  Released into the public domain.                              **
********************************************************************/

#include <AH_24Cxx.h>
#include <Wire.h> 

#define AT24C01  0
#define AT24C02  1
#define AT24C04  2
#define AT24C08  3
#define AT24C16  4
#define AT24C32  5
#define AT24C64  6
#define AT24C128 8
#define AT24C256 9
//Initialisation

int data;

#define BUSADDRESS  0x52      
#define EEPROMSIZE  128     //AT24C16 2048byte

uint8_t data_250_blackK[]={//address A01
168 ,
0 ,
1 ,
3 ,
18  ,
1 ,
1 ,
255 ,
100 ,
0 ,
52  ,
48  ,
55  ,
53  ,
52  ,
51  ,
20  ,
9 ,
65  ,
66  ,
22  ,
0 ,
22  ,
38  ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
100 ,
0 ,
0 ,
0 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 
};

uint8_t data_250_cyan[]={//address A1, remove resistor
168 ,
0 ,
1 ,
3 ,
14  ,
2 ,
1 ,
255 ,
100 ,
0 ,
52  ,
48  ,
55  ,
53  ,
52  ,
52  ,
21  ,
1 ,
65  ,
66  ,
23  ,
0 ,
4 ,
85  ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
100 ,
0 ,
0 ,
0 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 
};


uint8_t data_250_yellow[]={//address 0
168 ,
0 ,
1 ,
3 ,
14  ,
4 ,
1 ,
255 ,
100 ,
0 ,
52  ,
48  ,
55  ,
53  ,
52  ,
54  ,
21  ,
1 ,
65  ,
66  ,
25  ,
0 ,
23  ,
39  ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
100 ,
0 ,
0 ,
0 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 
};
uint8_t data_250_magenta[]={//address A0
168 ,
0 ,
1 ,
3 ,
14  ,
3 ,
1 ,
255 ,
100 ,
0 ,
52  ,
48  ,
55  ,
53  ,
52  ,
53  ,
21  ,
1 ,
65  ,
66  ,
24  ,
0 ,
3 ,
114 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
100 ,
0 ,
0 ,
0 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
255 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 ,
0 
};



void setup(){
 Serial.begin(9600);
 Wire.begin();
}

void loop()
{
  printmenu();
  while(1)
  {
    if ((Serial.available() > 0)) 
    {
      int c=Serial.read();
            switch(c)
      {
                  case '1':
                    data = 1;
                    break;
                  case '2':
                    data = 2;
          break;
                  case '3':
                    data = 3;
                    break;
                  case '4':
                    data = 4;
                    break;
      }
      int deviceAddress = scanBus();
      if (deviceAddress !=0)
      {
        AH_24Cxx ic_eeprom = AH_24Cxx(AT24C01, deviceAddress);
        Serial.println("Reading old data...");
          for (int i=0;i<EEPROMSIZE;i++)
          {
            Serial.print("pos. ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(ic_eeprom.read_byte(i));
            delay(5);
          }
          Serial.println("########################");
          Serial.println("Write data");
        for(int i = 0; i < 128; i++) 
        {
          int temData=0;
          switch(data)
          {
            case 1:
            temData = data_250_yellow[i];
            break;
            case 2:
            temData = data_250_cyan[i];
            break;
            case 3:
            temData = data_250_magenta[i];
            break;
            case 4:
            temData = data_250_blackK[i];
            break;
          }
          ic_eeprom.write_byte(i,temData);
          delay(5);
        }
        Serial.println("########################");
        Serial.println("Reading new data...");
        for (int i=0;i<EEPROMSIZE;i++)
        {
            Serial.print("pos. ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(ic_eeprom.read_byte(i));
            delay(5);
        }
            }
      
        }
  }
}

void printmenu(void){
  Serial.println("Press 1[enter] for writing eeprom data[Ricoh 250e yellow toner]\r\n");
  Serial.println("Press 2[enter] for writing eeprom data[Ricoh 250e cyan toner]\r\n");
  Serial.println("Press 3[enter] for writing eeprom data[Ricoh 250e magenta toner]\r\n");
  Serial.println("Press 4[enter] for writing eeprom data[Ricoh 250e blackK toner]\r\n");
}

int scanBus()
{
      Serial.println("Scanning...");
      int nDevices = 0;
      for(int address = 1; address < 127; address++ )
      {
        Wire.beginTransmission(address);
        int error = Wire.endTransmission();
     
        if (error == 0)
        {
          Serial.print("I2C device found at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.print(address,HEX);
          Serial.println("  !");
      return address;
          
          nDevices++;
        }
        else if (error==4)
        {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
        }    
      }
      if (nDevices == 0){
        Serial.println("No I2C devices found\n");
        return 0;
      }
      else
        Serial.println("done\n");
     }
       

