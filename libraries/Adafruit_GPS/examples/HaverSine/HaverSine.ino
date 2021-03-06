long cnt = 1;

void setup()
{
 Serial.begin(115200);
}

void loop()
{
 cnt++;
 Serial.print(millis() / 1000);
 Serial.print("\t");
 Serial.print(cnt);
 Serial.print("\t");  
 Serial.print(cnt * 1000 / millis());
 Serial.print("\t");  
 float x = HaverSine(0, 0, 0, 180);
 Serial.println(x, 5);
} 

float HaverSine(float lat1, float lon1, float lat2, float lon2)
{
 float ToRad = PI / 180.0;
 float R = 6371;   // radius earth in Km
 
 float dLat = (lat2-lat1) * ToRad;
 float dLon = (lon2-lon1) * ToRad; 
 
 float a = sin(dLat/2) * sin(dLat/2) +
       cos(lat1 * ToRad) * cos(lat2 * ToRad) * 
       sin(dLon/2) * sin(dLon/2); 
       
 float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
 
 float d = R * c;
 return d;
}
