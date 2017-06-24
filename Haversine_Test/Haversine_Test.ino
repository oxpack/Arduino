#include <SPI.h>

float lat[] = {39.991375,39.992001,39.992611,39.993237,39.993912,
               39.994511,39.995308,39.996113,39.996933,39.997787};
float lon[] = {-105.257881,-105.258331,-105.258774,-105.259209,-105.259544,
                 -105.260063,-105.260605,-105.261116,-105.261642,-105.262192};
//should get .8031 km

void setup()
{
Serial.begin(9600);
int i=0;
  for(i = 0; i<10 ;i++){
    Serial.print(i);
    Serial.print(",");
    Serial.print(lat[i],6);
    Serial.print(",");
    Serial.print(lon[i],6);
    Serial.print(",");
    Serial.print( HaverSine(lat[i],lon[i]),6);
    Serial.print(",");
    Serial.println( Cart(lat[i],lon[i]),6);

  }
}

void loop()
{
}


float HaverSine(float lat1, float lon1)
{
  static float dist;
  static float lat2, lon2;
  if (lat2 == 0) {
   lat2 = lat1;
   lon2 = lon1;
   return 0;
  }
  
 float ToRad = PI / 180.0;
 float R = 6371;   // radius earth in Km
 
 float dLat = (lat2-lat1) * ToRad;
 float dLon = (lon2-lon1) * ToRad; 
 
 float a = sin(dLat/2) * sin(dLat/2) +
       cos(lat1 * ToRad) * cos(lat2 * ToRad) * 
       sin(dLon/2) * sin(dLon/2); 
       
 float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
 
 lat2 = lat1;
 lon2 = lon1;
 dist = dist + R * c;
 return dist;
}

float Cart(float lat1, float lon1)
//much simpler equation gets nearly the same results
{
  static float dist;
  static float lat2=99, lon2=99;
 
if (lat2 >90)
  {
  lat2 = lat1;
  lon2 = lon1;
  return 0;
  }
  //R = 6371km
  //111.19449266 = PI * R /180.0
  //.017453293 = PI / 180.0
  
float y = (lat2-lat1) * 111.1949266;
float x = (lon2-lon1) * 111.1949266 * cos(lat1 * .017453293); 
lat2 = lat1;
lon2 = lon1;
dist = dist + sqrt(x*x + y*y);
return dist;
}

