#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(11,10);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

void setup()
{
  //serial com baud rate
  Serial.begin(115200);
 //header
//  Serial.println("HDOP Latitude  Longitude   Date       Time      Alt    Course Speed Card  Chars Sentences Checksum");
//  Serial.println("     (deg)     (deg)                            (m)    --- from GPS ----  RX    RX        Fail");
//  Serial.println("------------------------------------------------------------------------------------------------------------------------");

//set baud rate of the gps module
  ss.begin(9600);
  
//initialize the display
display.begin();

pinMode(2, INPUT_PULLUP); 
}

float dist1, max_speed;
int metric;

void loop()
{
  metric = digitalRead(2);
  display.clearDisplay();
       display.setCursor(0,0);
       
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
   
  print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  gps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  print_date(gps);
  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 1);
  print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
  print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2);
  print_str(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(gps.f_course()), 6);
//  print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0xFFFFFFFF : (unsigned long)TinyGPS::distance_between(flat, flon, LONDON_LAT, LONDON_LON) / 1000, 0xFFFFFFFF, 9);
//  print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? TinyGPS::GPS_INVALID_F_ANGLE : TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
//  print_str(flat == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON)), 6);
Serial.print(" ");
dist1 = dist1 + (gps.f_speed_kmph()>2.0)*Cart(flat,flon);

Serial.print(dist1);
Serial.print("   ");

//display.print(GPS.hour, DEC); display.print(':');
  //    display.print(GPS.minute, DEC); display.print(':');
    //  display.println(GPS.seconds, DEC); 
         display.print(flat,2);
         display.print(" ");
         display.println(flon,2);
         display.print((int) (gps.f_altitude()*(1.0+metric*2.2808)));
         if (metric) {
           display.println(" ft");
         }
           else
           {
          display.println(" m");
           }
//cartesian result

display.print(dist1*(1.0-metric*.3787),2);
if (metric) {
           display.print(" mi ");
         }
           else
           {
          display.print(" km ");
           }
           
//display course
display.println((int) (gps.f_course()));
           
           
display.print(gps.f_speed_kmph()*(1.0-metric*.3787),1);

if (gps.f_speed_kmph() > max_speed){
  max_speed = gps.f_speed_kmph();
  }
  display.print("  ");
  display.print(max_speed*(1.0-metric*.3787),1);
  display.println(" max");
  Serial.println();
  display.display();     
  smartdelay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print(" ********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, " %02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  smartdelay(0);
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}

float Cart(float lat1, float lon1)
//much simpler equation gets nearly the same results
//does not work as well as Haversine especially at high latitudes or bigger distances

{
  static float lat2=99, lon2=191,dist ;
 //Serial.println(lat2);
 
//check for good data before going any further
if (lat1 <-90 || lat1>90 ||lon1>180 ||lon1<-180) {
  return 0;
  }
  
if (lat2 >90 && lon2 > 180)
  {
  Serial.println("setting last values");
  lat2 = lat1;
  lon2 = lon1;
  return 0.0;
  }
  
  //hardcode values into the equations
  //Radius of earth = 6371km
  //111.19449266 = PI * R / 180.0
  //.017453293 = PI / 180.0
  
float y = (lat2-lat1) * 111.1949266;
float x = (lon2-lon1) * 111.1949266 * cos(lat1 * .017453293); 
lat2 = lat1;
lon2 = lon1;

dist = sqrt(x*x + y*y);

if (dist<.0005)
{return 0.0;}
else
{
return dist;
}
dist = sqrt(x*x + y*y);
}


