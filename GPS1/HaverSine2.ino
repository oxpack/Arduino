float HaverSine(float lat1, float lon1)
{
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
 
 float d = R * c;
 lat2 = lat1;
 lon2 = lon1;
 return d;
}
