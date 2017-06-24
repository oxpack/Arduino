
class RunAvg
{
     byte n,num, err;
     float ave,v[20],band;
    
  public:
    RunAvg(int i, float x)
    { num = i;
      band = x;
      }

    void ins(float x)
    {
      //check to see if new value is within band
      if (abs((x - ave) / ave) < band)
      {
        v[n] = x;
        n++;
        if (n > num) {
          n = 0;
        }
      }
      else
      {
        err++;
      Serial.print("Error: ");
      Serial.println(err);
      }
    }

    float ret()
    {
      ave = 0.0;
      int i;
      for (i = 0; i < ((n < num) ? n : num); i++) {
        ave = ave + v[i];
      }
      ave = ave / (float) i;
      return ave;
    }
};

RunAvg co(10, .05);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  co.ins(10.0);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  co.ins(10.1);
  Serial.println(co.ret());
   
}

void loop()
{
  co.ins(10.);
  // put your main code here, to run repeatedly:

}
