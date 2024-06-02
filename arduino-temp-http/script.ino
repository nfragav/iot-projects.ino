#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;

int cycles = 0;
int step = 0;
boolean wifi_connected = false;

String SSID = "Fraga Valcarcel 2.4";        // AP NAME
String PASS = "Ctn120330";  // AP PASSWORD
String API = "PXSTSNG9RTFLQUR8";       // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand = 0;
int countTimeCommand = 0;
boolean found = false;
int valSensor = 1;
SoftwareSerial esp8266(2, 3); // RX, TX


void setup() {
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("Tamo activo bby");
  dht.begin();
  esp8266.begin(115200);
  delay(1000);
  setup_shield();
  delay(100);
  manage_wifi();

  getSensorData();
  refresh_lcd();
}

void loop() {
  step = 0;
  update_step();
  manage_wifi();
  update_step();
  getSensorData();
  refresh_lcd();
  update_step();
  manage_host_connection();
  cycles++;
  delay(10 * 1000);
}

void getSensorData() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    // Serial.println("Error reading dht22 data");
    return;
  }
  // Serial.print("Humidity: ");
  // Serial.print(humidity);
  // Serial.print("% ");
  // Serial.print("Temperature: ");
  // Serial.print(temperature);
  // Serial.println(" °C");
}

void manage_host_connection() {
  if (!wifi_connected) return;
  if (cycles < 100) return;
  cycles = 0;

  String getData = "GET /update?api_key=" + API + "&" + "field2=" + humidity + "&field3=" + temperature;
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");

  lcd.setCursor(13,1);
  lcd.print("Req");
  esp8266.println(getData);
  lcd.print("   ");
  delay(1500);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void manage_wifi() {
  wifi_connected = sendCommand("AT+CWSTATE?", 20, "OK");
  if (wifi_connected) {
    digitalWrite(8, HIGH);
    // Serial.println("Succesfully connected to " + SSID);
  }
  else {
    digitalWrite(8, LOW);
    wifi_connected = sendCommand("AT+CWJAP=\"" + SSID + "\",\"" + PASS + "\"", 20, "OK");
    if (wifi_connected) digitalWrite(8, HIGH);
  }
}

void setup_shield() {
  sendCommand("AT", 5, "OK");
  sendCommand("AT+RST", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
}

boolean sendCommand(String command, int maxTime, char readReplay[]) {
  found = false;
  // Serial.print(countTrueCommand);
  // Serial.print(". at command => ");
  // Serial.print(command);
  // Serial.print(" ");
  while (countTimeCommand < (maxTime * 1)) {
    esp8266.println(command);      //at+cipsend
    delay(100);
    if (esp8266.find(readReplay))  //ok
    {
      found = true;
      break;
    }
    countTimeCommand++;
  }

  if (found == true) {
    // Serial.println("[OYI]");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false) {
    // Serial.println("[Fail]");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  return found;
}

void printESP () {
  if (esp8266.available()) {
    // Serial.println(char(esp8266.read()));
  }
}

void refresh_lcd() {
  String line_1 = String(humidity) + "%";
  String line_2 = String(temperature) + " C";
  if (isnan(humidity)) {
    String line_1 = "Error";
  }
  if (isnan(temperature)) {
    String line_2 = "Error";
  }
  const char* char_line_1 = line_1.c_str();
  const char* char_line_2 = line_2.c_str();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line_1);
  lcd.setCursor(0,1);
  lcd.print(line_2);
  lcd.setCursor(10, 0);
  if (wifi_connected) {
    lcd.print("[WiFi]");
  } else {
    lcd.print("[xxxx]");
  }
}

void update_step() {
  step++;
  lcd.setCursor(10, 1);
  if (cycles >= 10 and cycles <= 99) lcd.setCursor(9, 1);
  if (cycles >= 100) lcd.setCursor(8, 1);
  lcd.print(cycles);
  lcd.print(".");
  lcd.print(step);
}