
float HaverSine(float lat1, float lon1)
{
  static float dist;
  lat1 = lat1 / 100.0;
  lon1 = lon1 / 100.0;
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
 if (d>10) d = 0; 
 lat2 = lat1;
 lon2 = lon1;
 dist = dist + d;
 return dist;
}


float climb(float alt)
{
static float old_alt,cum_alt;
if (old_alt == 0)
{
  old_alt = alt;
  return 0.0;
}
//check to see if we went up? If so add to the climb
if (alt>old_alt) cum_alt = cum_alt + (alt-old_alt);
old_alt = alt;
return cum_alt;
}

