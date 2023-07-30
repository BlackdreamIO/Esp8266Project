#include <ESP8266WiFi.h>

// WIFI INFO : SSID AND PASSWORD

const char* ssid = "MOFIZ";     // Replace with your Wi-Fi network SSID
const char* password = "01747666"; // Replace with your Wi-Fi network password

// DEFINE THE LED

const int CONNECTED_LED = D2;
const int DISCONNECTED_LED = D0;
const int ESP_STATUS_LED = D1;
const int ERROR_LED = D3;
const int AS_LED = D6;

// DEFINE BOOLEAN FOR CONDITION

bool isConnected = false; 
bool isConnecting = true;
bool startUp = false;


//----------------------------------------------------------------------------------------//

bool CONNECT_TO_WIFI() 
{
  
  WiFi.begin(ssid, password);

  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  isConnecting = true;

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED) 
  {
    if (millis() - startTime > 10000) 
    {  
      // Timeout after 10 seconds
      return false;
    }
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to Wi-Fi");

  isConnecting = false;

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

bool CHECK_NETWORK() 
{
  bool connected = (WiFi.status() == WL_CONNECTED);
  if (connected) { return true; } 
  else { return false; }
}

void BLINK_CONNECTED_LED() 
{
  digitalWrite(CONNECTED_LED, HIGH);
  delay(50);
  digitalWrite(CONNECTED_LED, LOW);
  delay(50);
}
void BLINK_DISCONNECTED_LED() 
{
  digitalWrite(DISCONNECTED_LED, HIGH);
  delay(100);
  digitalWrite(DISCONNECTED_LED, LOW);
  delay(100);
}
void BLINK_STARTUP_LED()
{
  unsigned long startTime = millis();

  while (startUp)
  {
    // Blink CONNECTED_LED with a delay of 50 milliseconds
    digitalWrite(CONNECTED_LED, HIGH);
    delay(50);
    digitalWrite(CONNECTED_LED, LOW);
    delay(50);

    // Blink ERROR_LED with a delay of 1000 milliseconds
    digitalWrite(ERROR_LED, LOW);
    delay(1000);
    digitalWrite(ERROR_LED, HIGH);
    delay(1000);

    // Check if the elapsed time has exceeded 5 seconds
    if (millis() - startTime > 5000)
    {
      digitalWrite(ERROR_LED, LOW);
      startUp = false; // Exit the loop
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(115200);
  delay(20);
  startUp = true;
  CONNECT_TO_WIFI();
  pinMode(CONNECTED_LED, OUTPUT);
  pinMode(DISCONNECTED_LED, OUTPUT);
  pinMode(ESP_STATUS_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(AS_LED, OUTPUT);

  digitalWrite(ERROR_LED, HIGH);
  digitalWrite(ESP_STATUS_LED, HIGH);
  digitalWrite(AS_LED, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  isConnected = CHECK_NETWORK();

  if(isConnected) 
  {
    if(!startUp) 
    {
      BLINK_CONNECTED_LED();
    }
    else if (startUp) 
    {
      BLINK_STARTUP_LED();
    }
  }
  else 
  {
    BLINK_DISCONNECTED_LED();
  }
}
