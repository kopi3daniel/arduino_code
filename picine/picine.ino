 #include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleTimer.h>


SimpleTimer timer;

float calibration_value = 21.34 + .06; //
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
// for the OLED display


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


namespace pin {
const byte tds_sensor = A1;
const byte one_wire_bus = 7; // Dallas Temperature Sensor
}

namespace device {
float aref = 4.3;
}

namespace sensor {
float ec = 0;
unsigned int tds = 0;
float waterTemp = 0;
float ecCalibration = 1;
}

OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);

// EC isolator

// EC isolator
int EC_Isolator = 2; // 3906 PNP TYPE TRANSISTOR THIS is used to connect and disconnect the 3.3V wire 
int EC_GND_Wire = 3; // 2N2222 NPN TRANSISTOR THIS IS USED TO CONNECT AND DISCONNECT THE GND WIRE

// for the TOF10120 distance range sensor
unsigned char ok_flag;
unsigned char fail_flag;

unsigned short lenth_val = 0;
unsigned char i2c_rx_buf[16];
unsigned char dirsend_flag=0;

int x_mm; // distance in millimeters
float y_inches; // distance in inches

// to control pump
int relay = 9; 
int relay_flag = 0; 

void setup() 
{
  Wire.begin();
 Serial.begin(9600);
  dallasTemperature.begin();
    pinMode(relay, OUTPUT); 
  digitalWrite(relay, LOW);
  printf_begin();
pinMode(EC_Isolator, OUTPUT);
  pinMode(EC_GND_Wire, OUTPUT);
  digitalWrite(EC_Isolator, HIGH);
  digitalWrite(EC_GND_Wire, LOW); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE); 

 
timer.setInterval(500L, display_pHValue);
}
void loop() {
timer.run(); // Initiates SimpleTimer


tofsensor();



digitalWrite(EC_Isolator,HIGH); 
digitalWrite(EC_GND_Wire, LOW);
ph_sensor();
digitalWrite(EC_Isolator,LOW); 
digitalWrite(EC_GND_Wire, HIGH);
delay(1000);
 dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  float rawEc = analogRead(pin::tds_sensor) * device::aref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp - 25.0); // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration; // temperature and calibration compensation
  sensor::tds = (133.42 * pow(sensor::ec, 3) - 255.86 * sensor::ec * sensor::ec + 857.39 * sensor::ec) * 3.3; //convert voltage value to tds value
  Serial.print(F("TDS:")); Serial.println(sensor::tds);
  Serial.print(F("EC:")); Serial.println(sensor::ec, 2);
  Serial.print(F("Temperature:")); Serial.println(sensor::waterTemp,2);
  delay(1000); 

  
 
}

void display_pHValue()
{
     // display on Oled display

   // Oled display
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0); // column row
  display.print("pH:");

  display.setTextSize(2);
  display.setCursor(55, 0);
  display.print(ph_act);


    display.setTextSize(2);
  display.setCursor(0,20);
  display.print("Temp:");

  display.setTextSize(2);
  display.setCursor(60, 20);
  display.print(sensor::waterTemp);
 

    display.setTextSize(2);
  display.setCursor(0,40);
  display.print("EC:");

  display.setTextSize(2);
  display.setCursor(60, 40);
  display.print(sensor::ec);
 
  

 display.display();
}

void ph_sensor()
{
  for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*3.3/1024/6; // the original was float volt=(float)avgval*5.0/1024/6; when its connected with arduino's 5v
  ph_act = -5.70 * volt + calibration_value;

 Serial.println("pH Val: ");
 Serial.print(ph_act);
 delay(1000);
}




int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}

void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}



void SensorRead(unsigned char addr,unsigned char* datbuf,unsigned char cnt) 
{
  unsigned short result=0;
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(82); // transmit to device #82 (0x52), you can also find this address using the i2c_scanner code, which is available on electroniclinic.com
  // the address specified in the datasheet is 164 (0xa4)
  // but i2c adressing uses the high 7 bits so it's 82
  Wire.write(byte(addr));      // sets distance data address (addr)
  Wire.endTransmission();      // stop transmitting
  // step 2: wait for readings to happen
  delay(1);                   // datasheet suggests at least 30uS
  // step 3: request reading from sensor
  Wire.requestFrom(82, cnt);    // request cnt bytes from slave device #82 (0x52)
  // step 5: receive reading from sensor
  if (cnt <= Wire.available()) { // if two bytes were received
    *datbuf++ = Wire.read();  // receive high byte (overwrites previous reading)
    *datbuf++ = Wire.read(); // receive low byte as lower 8 bits
  }
}

int ReadDistance(){
    SensorRead(0x00,i2c_rx_buf,2);
    lenth_val=i2c_rx_buf[0];
    lenth_val=lenth_val<<8;
    lenth_val|=i2c_rx_buf[1];
    delay(300); 
    return lenth_val;
}

void tofsensor()
{
       x_mm = ReadDistance();
   Serial.print(x_mm);
   Serial.println(" mm");

   // You can convert millimeters to inches in one of two ways: divide the number of millimeters by 25.4, or multiply the number of millimeters by 0.0394
   y_inches = x_mm * 0.0394;
   Serial.print(y_inches); 
   Serial.println(" inches");

   if( (y_inches > 10 ) && (relay_flag == 0))
{
  digitalWrite(relay, LOW); 
  relay_flag = 1; 
}

if( (y_inches <= 5 ) && (relay_flag == 1))
{
  digitalWrite(relay, HIGH); 
  relay_flag = 0; 
}
}