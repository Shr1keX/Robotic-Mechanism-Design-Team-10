//replace this with the pins you're actually using
#define enA 11
#define in1 8
#define in2 9
#define in3 12
#define in4 13
#define enB 10
void setup() {
  //motor controller stuff
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  //onboard led setup (this is like for the blink program thing you do when you are just setting up the uno)
  pinMode(LED_BUILTIN, OUTPUT);

  //set up serial monitor
  Serial.begin(9600);
}
void loop() {
  //this sets up the variables that hold ur position. 
  //This assumes that you are looking straight on at the robot, like the wires coming out of the joystick are pointing out at the robot, and then x is left and right and 
  //y is towards the robot and then -y is back away from the robot
  float x_pos = (analogRead(A0)  - 512)*-1;
  float y_pos = (analogRead(A1) - 512)*-1;
  //this guy tells you if the joystick is "at rest" because when at rest, due to calibration issues, it will NOT rest at 0/0
  bool joystick_at_rest = false;

  //can use these to print out joystick x/y
  //Serial.print("X: ");
  //Serial.println(x_pos);
  //Serial.print(" Y: ");
  //Serial.println(y_pos); // Print and move to a new line

  //gives ya the angle ur at. ranges from 0 to 360 because of some stuff i did
  float angle_rad = atan2(y_pos, x_pos); 

  //doublechecks if the joystick is at rest or not
  if (abs(x_pos)<15 && abs(y_pos)<15) {
    joystick_at_rest = true; 
  }
  Serial.print(" Is Joystick at rest: ");
  Serial.println(joystick_at_rest);
  
  float angle_deg = angle_rad * (180.0 / PI);
  //this if statement makes it so that instead of having this wierd range of -180 degrees to 180 degrees, it's just 0 -> 360, like the way you learned in trig
  if (angle_deg<0) {
    float new_angle = 360 - fabs(angle_deg);
    angle_deg = new_angle;
  }
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
  
  //Serial.print(" Angle: ");
  //Serial.println(angle_deg); // Print the calculated angle in degrees
  
  delay(100);

}
