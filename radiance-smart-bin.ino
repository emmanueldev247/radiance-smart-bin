#include <Servo.h> // Library to control servo motor
#include <SoftwareSerial.h> // library to create virtual serial pin and allows serial communication on other digital pins of an Arduino board

Servo myservo;
SoftwareSerial mySerial(7, 8); // RX, TX

#define trigIn 4 // Trigger pin for ultrasonic sensor inside the dustbin 
#define echoIn 3 // Echo pin for ultrasonic sensor inside the dustbin
#define trigOut 5 // Trigger pin for ultrasonic sensor outside the dustbin
#define echoOut 6 // Echo pin for ultrasonic sensor outside the dustbin
#define binLevel 10 // max bin level declared as 10cm

int powerLed = 10; // led to indicate power
int avlLed = 11; // led to indicate bin is not full
int fullLed = 12; // led to indicate bin is full

int pos = 20; // initial position of servo motor (Close or remain closed)
long duration; // store time duration of sound travel
int distance; // store actual distance to object
bool flag = 0; // to exit a loop
float disIn; // to store level of bin inside
float disOut; // to store distance to an obstruction outside

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Open serial communications and wait for port to open:
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port

  // setting pinMode
  pinMode(powerLed, OUTPUT);
  pinMode(avlLed, OUTPUT);
  pinMode(fullLed, OUTPUT);

  pinMode(trigIn, OUTPUT);
  pinMode(echoIn, INPUT);

  myservo.attach(9);
  pinMode(trigOut, OUTPUT);
  pinMode(echoOut, INPUT);
  myservo.write(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(powerLed, HIGH); // put on powerLed i.e red

  disOut = checkDistance(trigOut, echoOut);
  disIn = checkDistance(trigIn, echoIn);
  Serial.println("\nOutside = " + String(disOut));
  Serial.println("\nInside = " + String(disIn));

  // Condition to check if object in front of dustbin (Open)
  if (disOut < 20) {
    //digitalWrite(led, HIGH);
    myservo.write(pos + 100);
    delay(1000);
    
    // loop to keep the bin open until obstruction cleares
    while (disOut < 20) { 
      disOut = checkDistance(trigOut, echoOut);
      delay(1000);
    }
  }
  else {  // Condition to check if no object in front of dustbin (Close or stay closed)
    myservo.write(pos);
  }
  delay(100);

  // Condition to check if bin is full
  if ((disIn < binLevel) && (flag == 0)) {
    digitalWrite(avlLed, LOW);
    digitalWrite(fullLed, HIGH);
    delay(300);
    digitalWrite(fullLed, LOW);
    delay(300);
    digitalWrite(fullLed, HIGH);
    delay(300);
    digitalWrite(fullLed, LOW);
    delay(300);
    digitalWrite(fullLed, HIGH);
    delay(300);
    digitalWrite(fullLed, LOW);
    delay(300);
    digitalWrite(fullLed, HIGH);
    flag = 1; // prevent calling and sms sending continusly
    call("+2348050208547");
    call("+2349063952111");
    Serial. println ("Call made successfully");
    sendSMS("+2348050208547", "Greetings LAWMA,\nThis is to inform you that our waste bins are filled. It's time for removal.\nRadiance High School\nhttps://maps.app.goo.gl/uK1AxtS4tDk8PfYbA"); //Calling Function with SMS details)
    sendSMS("+2349063952111", "Greetings LAWMA,\nThis is to inform you that our waste bins are filled. It's time for removal.\nRadiance High School\nhttps://maps.app.goo.gl/uK1AxtS4tDk8PfYbA"); //Calling Function with SMS details)
    Serial. println ("SMS sent successfully");
  }
  // Condition to check if bin is not full
  if (disIn > binLevel) {
    digitalWrite(fullLed, LOW);
    digitalWrite(avlLed, HIGH);
    flag = 0; // clear flag for next event
  }
  delay(100);
}

int checkDistance(int var1, int var2) {
  digitalWrite(var1, LOW);
  delayMicroseconds(2);
  digitalWrite(var1, HIGH); // triger signal
  delayMicroseconds(10);
  digitalWrite(var1, LOW);
  duration = pulseIn(var2, HIGH);
  distance = 0.034 * (duration / 2); // formula to get distance using speed of sound and time
  return distance;
}


void call (String mobileNumber)
// Function to call a local cell
{
  mySerial.println ("ATD + " + mobileNumber + ";"); // Calling number // try no space
  delay(100);
  mySerial.println();
  delay(5000); // wait for 5 seconds …
  mySerial.println ("ATH"); // Ends the call
  delay(300);
  mySerial.println();
}

void sendSMS(String mobileNumber, String msgBody) {
  // Function to send SMS to a local cell
  mySerial.println("AT"); // check connection
  readResponse(); // read modem response
  delay(500); // check @1k
  mySerial.println("AT+CMGF=1");// SET MODULE TO TEXT MODE
  readResponse(); // read modem response
  delay(500);
  mySerial.println("AT+CMGS=\"" + mobileNumber + "\""); // sender mobile number
  readResponse(); // read modem response
  delay(500);
  mySerial.println(msgBody); // enter msg body
  delay(500);
  mySerial.print((char)26); // indicates end of sms and then sends msg
  delay(500);
}

void readResponse() {
  //simple function for read modem response. we will check work or not
  String response = mySerial.readStringUntil("OK");
  Serial.println(response);
}
