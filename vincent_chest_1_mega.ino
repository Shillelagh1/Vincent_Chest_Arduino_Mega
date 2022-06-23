int pins [][2] = 
{
{32,22},{32,24},{32,26},{32,28},{32,30},
{34,22},{34,24},{34,26},{34,28},{34,30},
{36,22},{36,24},{36,26},{36,28},{36,30},
{38,22},{38,24},{38,26},{38,28},{38,30},
{40,22},{40,24},{40,26},{40,28},{40,30},
{42,22},{42,24},{42,26},{42,28},{42,30}
};

static int pinsLength = 27;
int lightIndex = 0;
bool buttonPressed = false;
bool buttonLastPressed = false;
int speedSelection = 2;
int speeds[] = {50,200,350,550};
unsigned long buttonAStart = 0;
unsigned long lastButtonA = 0;
static int interruptRising = 3;
static int interruptFalling = 2;
bool lightsRunning = true;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run 
  for (int i = 0; i < pinsLength; i++){
    Serial.print(pins[i][0]);
    Serial.println(pins[i][1]);
    pinMode(pins[i][0],OUTPUT);
    pinMode(pins[i][1],OUTPUT);
  }
  clearLEDs();
  pinMode(interruptFalling, INPUT_PULLUP);
  pinMode(interruptRising, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptRising), buttonAReleased, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptFalling), buttonAPressed, FALLING);
}

void loop() {
  // put your main code here, to ru
  cycleLEDs();
}

void selectLED(int index){
  for (int i = 0; i < pinsLength; i++){
      //Serial.println(String(i) + "False");
      digitalWrite(pins[i][0],HIGH);
      digitalWrite(pins[i][1],LOW);      
    } 
      digitalWrite(pins[index][0],LOW);
      digitalWrite(pins[index][1],HIGH); 
}
void clearLEDs(){
  for (int i = 0; i < pinsLength; i++){
      //Serial.println(String(i) + "False");
      digitalWrite(pins[i][0],HIGH);
      digitalWrite(pins[i][1],LOW);      
    } 
}
void cycleLEDs(){
    for (int lightIndex = 0; lightIndex < pinsLength; lightIndex++){
    if(!lightsRunning){
      break;
    }
    //Serial.println("Select");
    selectLED(lightIndex);
    delay(speeds[speedSelection]);
  }
  clearLEDs();
}
void buttonAReleased(){
  Serial.println("Button A Released");
  if(millis() > lastButtonA + 100){
    if (lightsRunning)
    {
      Serial.println(String(millis()) + ':' + String(buttonAStart));
      if (millis() < buttonAStart + 1000){
         if (speedSelection == 3)
         {
          speedSelection = 0;
         }
         else
         {
          speedSelection ++;
         }
      }
      else
      {
        lightsRunning = false;
      }
      }
      else
      {
        lightsRunning = true;
      }
    }
  lastButtonA = millis();
  Serial.println("Speed:" + String(speedSelection));
}
void buttonAPressed(){
   Serial.println("Button A Pressed");
   buttonAStart = millis();
   Serial.println(String(buttonAStart));
}
