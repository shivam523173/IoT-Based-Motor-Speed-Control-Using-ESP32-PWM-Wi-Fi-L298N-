#include <WiFi.h>
#include <WebServer.h>

// ------- Wi-Fi Login -------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ------- L298N Pin Assignments -------
#define ENA 25   // PWM Speed Control for Motor A
#define IN1 27   // Direction
#define IN2 26

WebServer server(80);
int speedValue = 150; // Default PWM duty (0–255)

// Set motor direction + speed
void motorForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(0, speedValue);
}

void motorReverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(0, speedValue);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(0, 0);
}

// ------- Web Page -------
String webpage() {
  String html = "<html><body><h2>ESP32 Motor Control</h2>";
  html += "<p>Speed: <b>" + String(speedValue) + "</b></p>";
  html += "<input type='range' min='0' max='255' value='" + String(speedValue) +
          "' oninput='location.href=\"/speed?val=\"+this.value'><br><br>";
  html += "<button onclick='location.href=\"/forward\"'>Forward</button> ";
  html += "<button onclick='location.href=\"/reverse\"'>Reverse</button> ";
  html += "<button onclick='location.href=\"/stop\"'>Stop</button>";
  html += "</body></html>";
  return html;
}

// ------- HTTP Routes -------
void handleRoot() { server.send(200, "text/html", webpage()); }
void handleForward() { motorForward(); handleRoot(); }
void handleReverse() { motorReverse(); handleRoot(); }
void handleStop() { motorStop(); handleRoot(); }
void handleSpeed() {
  if (server.hasArg("val")) speedValue = server.arg("val").toInt();
  ledcWrite(0, speedValue);
  handleRoot();
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // PWM setup on ENA
  ledcSetup(0, 1000, 8);
  ledcAttachPin(ENA, 0);

  motorStop();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(200); }
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/stop", handleStop);
  server.on("/speed", handleSpeed);
  server.begin();
}

void loop() {
  server.handleClient();
}
