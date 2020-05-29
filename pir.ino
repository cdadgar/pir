/*
 * HC-SR501 
 * http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
 * bottom view: jumper top right:
 * left pot:  time delay adjust (counter-clockwise to descrease)
 *   seems weird that you'd ever want anything other than minimum delay
 *   min = 3 seconds
 *   max = 5 minutes
 *   
 * right pot: sensitivity adjust (clockwise to decrease)
 *   doesn't seem to do a lot
 *   
 * jumper: trigger selection jumper (single, top: default)
 * din pins: power, output, ground
 * 
 * power: 5 to 20 vdc (not 3.3 compatible)
 * 
 * 
 * todo:  see how to convert module to 3.3
 * 
 * 
 * 
 * AM312
 * din pins: power, output, ground
 * (viewing from the din pins side (transistor is vivible on the left))
 * trigger length is 4 seconds
 * DC 2.7-12V
 * 
 * warning: the output doesn't seem compatible with a mux chip.  the output line was dragged high all the time
 * 
 * warning: don't connect backwards: swap vcc and gnd.....smoke is released
 * (output remains at vcc after that)
 */
#define SR501_PIN 0   // D3
#define AM312_PIN 16  // D0
int pir1State = LOW;
int pir2State = LOW;


void setup() {
  // start serial port
  Serial.begin(115200);
  Serial.print(F("\n\n"));

  Serial.println(F("esp8266 pir"));
  Serial.println(F("compiled:"));
  Serial.print(F(__DATE__));
  Serial.print(F(","));
  Serial.println(F(__TIME__));


  pinMode(SR501_PIN, INPUT);
  pinMode(AM312_PIN, INPUT);
}

void loop() {
  int val = digitalRead(SR501_PIN);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pir1State == LOW) {
      // we have just turned on
      Serial.println(F("SR501 Motion detected"));
      // We only want to print on the output change, not state
      pir1State = HIGH;
    }
  } else {
    if (pir1State == HIGH){
      // we have just turned of
      Serial.println(F("SR501 Motion ended"));
      // We only want to print on the output change, not state
      pir1State = LOW;
    }
  }

  int val2 = digitalRead(AM312_PIN);  // read input value
  if (val2 == HIGH) {            // check if the input is HIGH
    if (pir2State == LOW) {
      // we have just turned on
      Serial.println(F("AM312 Motion detected"));
      // We only want to print on the output change, not state
      pir2State = HIGH;
    }
  } else {
    if (pir2State == HIGH){
      // we have just turned of
      Serial.println(F("AM312 Motion ended"));
      // We only want to print on the output change, not state
      pir2State = LOW;
    }
  }
//  Serial.print(val);
//  Serial.print(" ");
//  Serial.println(val2);
}
