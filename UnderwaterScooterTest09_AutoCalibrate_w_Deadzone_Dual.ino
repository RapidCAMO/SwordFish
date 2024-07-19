#include <DShot.h>

// Create DShot instances for two ESCs
DShot esc_L(DShot::Mode::DSHOT300);
DShot esc_R(DShot::Mode::DSHOT300);

//Left side variables
int throttle_L = 0;
int rawthrottle_L = 0;
int throttlePerc_L = 0;
int hallef_L = 0; // variable to store hall effect value

int MaxInput_L = 0;
int MinInput_L = 1023;

//Right side variables
int throttle_R = 0;
int rawthrottle_R = 0;
int throttlePerc_R = 0;
int hallef_R = 0; // variable to store hall effect value

int MaxInput_R = 0;
int MinInput_R = 1023;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Attach the ESCs to the appropriate pins
  esc_L.attach(11); // Attach Left ESC to pin 11
  esc_R.attach(10); // Attach Right ESC to pin 10

  // Initialize both ESCs with a neutral throttle
  esc_L.setThrottle(0);
  esc_R.setThrottle(0);

  delay(3000);
}

void loop() {
  hallef_L = analogRead(A0);
  hallef_R = analogRead(A1);
  Serial.print("Hall effect: L = ");  Serial.print(hallef_L); Serial.print("   R = ");  Serial.println(hallef_R);

  AutoCalibrate(); //Autocalibrate both HES

  rawthrottle_L = map(hallef_L, MinInput_L, MaxInput_L, 48, 1047);
  throttle_L = RemapWithDeadzone(hallef_L, MinInput_L + 25, MaxInput_L - 7); //min is 0 not 48
  throttlePerc_L = map(throttle_L, 48, 1047, 0, 100);

  rawthrottle_R = map(hallef_R, MinInput_R, MaxInput_R, 48, 1047);
  throttle_R = RemapWithDeadzone(hallef_R, MinInput_R + 25, MaxInput_R - 7); //min is 0 not 48
  throttlePerc_R = map(throttle_R, 48, 1047, 0, 100);

  esc1_L.setThrottle(throttle_L);
  esc1_R.setThrottle(throttle_R);

  Serial.print("HES ranges (0%-100%) are "); Serial.print(MinInput_L); Serial.print(" - "); Serial.print(MaxInput_L); Serial.print(" (Left) and ");  Serial.print(MinInput_R); Serial.print(" - "); Serial.print(MaxInput_R); Serial.println(" (Right)")
  Serial.print("Throttle Percentage: "); Serial.print(throttlePerc_L); Serial.print("% (Left), ");  Serial.print(throttlePerc_R); Serial.println("% (Right)");
  Serial.print("Throttle: "); Serial.print(throttle_L); Serial.print(" (Left), ");  Serial.print(throttle_R); Serial.println(" Right");
  Serial.println();

  //delay(300); //can remove
}

void AutoCalibrate(){
  if (hallef_L < MinInput_L){
    MinInput_L = hallef_L;
  }
  else if (hallef_L > MaxInput_L){
    MaxInput_L = hallef_L;
  }

  if (hallef_R < MinInput_R){
    MinInput_R = hallef_R;
  }
  else if (hallef_R > MaxInput_R){
    MaxInput_R = hallef_R;
  }
}

int RemapWithDeadzone(int rawthrottle, int MinDeadzone, int MaxDeadzone){ //takes the raw input from HES and remaps it to 0,48-1047 with deadzones
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
