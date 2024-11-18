#define LED_PIN 8
#define BUTTON_PIN 7

#define MOTOR_IN1_PIN 9  // Motor direction pin 1
#define MOTOR_IN2_PIN 10 // Motor direction pin 2

byte lastButtonState = HIGH;  // Button is HIGH when not pressed (due to the internal pull-up)
byte ledState = LOW;

unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);          // LED pin
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button pin with internal pull-up resistor
  pinMode(MOTOR_IN1_PIN, OUTPUT);    // Motor direction pin 1
  pinMode(MOTOR_IN2_PIN, OUTPUT);    // Motor direction pin 2
  
  Serial.begin(9600);
  Serial.println("Starting program...");
}

void loop() {
  if (millis() - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;

      // Check if the button is pressed (LOW because of the pull-up)
      if (buttonState == LOW) {
        Serial.print("Button pressed. LED state: ");
        Serial.println(ledState ? "ON" : "OFF");
        
        // Toggle the LED state
        ledState = (ledState == HIGH) ? LOW : HIGH;
        digitalWrite(LED_PIN, ledState);
        
        // Move the actuator: Alternate between forward and reverse
        if (ledState == HIGH) {
          // Extend the actuator (move forward)
          digitalWrite(MOTOR_IN1_PIN, HIGH);
          digitalWrite(MOTOR_IN2_PIN, LOW);
          Serial.println("Actuator extending...");
        } else {
          // Retract the actuator (move backward)
          digitalWrite(MOTOR_IN1_PIN, LOW);
          digitalWrite(MOTOR_IN2_PIN, HIGH);
          Serial.println("Actuator retracting...");
        }
      }
    }
  }
}
