#include <DShot.h>

// Create DShot instances for two ESCs
DShot esc1(DShot::Mode::DSHOT300);

int throttle = 0;
int rawthrottle = 0;
int throttlePerc = 0;

int hallef = 0; // variable to store hall effect value

//Read values will be compared with these initial values
int MaxInput = 0;
int MinInput = 1023;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Attach the ESCs to the appropriate pins
  esc1.attach(10); // Attach ESC1 to pin 11

  // Initialize both ESCs with a neutral throttle
  esc1.setThrottle(0);

  delay(3000);
}

void loop() {
  hallef = analogRead(A1);
  Serial.print("Hall effect: ");
  Serial.println(hallef);

  AutoCalibrate();

  rawthrottle = map(hallef, MinInput, MaxInput, 48, 1047);
  throttle = RemapWithDeadzone(hallef, MinInput + 25, MaxInput - 7); //min is 0 not 48
  throttlePerc = map(throttle, 48, 1047, 0, 100);

  Serial.print("HES range (0%-100%) is now "); Serial.print(MinInput); Serial.print(" - "); Serial.println(MaxInput);
  Serial.print("Throttle Percentage: "); Serial.print(throttlePerc); Serial.println("%");
  Serial.print("Throttle: "); Serial.println(throttle); 
  Serial.println();

  esc1.setThrottle(throttle);

  delay(100);
}

void AutoCalibrate(){
  if (hallef < MinInput){
    MinInput = hallef;
  }
  if (hallef > MaxInput){
    MaxInput = hallef;
  }
}

int RemapWithDeadzone(int rawthrottle, int MinDeadzone, int MaxDeadzone){
  if(hallef < MinDeadzone){
    Serial.print("Input < "); Serial.print(MinDeadzone); Serial.println(", defaulting to 0 (no power)");
    return 0;
  }
  else if (hallef > MaxDeadzone){
    Serial.print("Input > "); Serial.print(MaxDeadzone); Serial.println(", defaulting to 1047 (full power)");
    return 1047;
  }
  else{
    Serial.print("Input between deadzones: "); Serial.print(MaxDeadzone); Serial.println(", has been remapped");
    return map(rawthrottle, MinInput, MaxInput, 48, 1047);
  }
}