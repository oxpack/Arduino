/*little program that sends integer
to tone on pin 8 to check output
*/
void setup()

{

Serial.begin(9600);

}


void loop()

{

//waiting for input

while (Serial.available() == 0);

int val = Serial.parseInt(); //read int or parseFloat for ..float...

tone(8,val);
Serial.println(val);
}
