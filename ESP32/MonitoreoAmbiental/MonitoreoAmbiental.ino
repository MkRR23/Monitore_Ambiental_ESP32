#include "WiFi.h"
#include "HTTPClient.h"
#include <Adafruit_MAX31865.h>
#include "DHT.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "Wire.h"

// ================== WiFi ==================
const char* ssid = ""; //Your WiFi name
const char* pass = "";  //Your WiFi password
const char* servidor = ""; //Your local IP

// ================== DHT ==================
#define DHTPIN 4
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

// ================== MAX31865 ==================
#define MAX31865_CS   5
#define MAX31865_MOSI 23
#define MAX31865_MISO 19
#define MAX31865_CLK  18

#define RREF      4300.0
#define RNOMINAL  1000.0

Adafruit_MAX31865 thermo = Adafruit_MAX31865(
  MAX31865_CS,
  MAX31865_MOSI,
  MAX31865_MISO,
  MAX31865_CLK
);

// ================== SCD30 ==================
SCD30 airSensor;
bool calibrar = false;

// ================== SETUP ==================
void setup() {
  Serial.begin(9600);

  // WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConectado");

  // I2C
  Wire.begin();

  // MAX31865
  thermo.begin(MAX31865_3WIRE);

  // DHT
  dht.begin();

  // SCD30
  if (airSensor.begin() == false) {
    Serial.println("SCD30 no detectado");
    while (1);
  }

  Serial.println("SCD30 detectado");
  delay(5000);

  // Calibración opcional
  if (calibrar) {
    airSensor.setForcedRecalibrationFactor(400);
    Serial.println("Calibrado a 400 ppm");
  }
}

// ================== LOOP ==================
void loop() {

  // ===== PT1000 =====
  float temperatura = thermo.temperature(RNOMINAL, RREF);

  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Falla MAX31865: 0x");
    Serial.println(fault, HEX);
    thermo.clearFault();
  }

  // ===== DHT =====
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Error leyendo DHT");
    hum = 0;
  }

  // ===== CO2 =====
  float co2 = 0;

  if (airSensor.dataAvailable()) {
    co2 = airSensor.getCO2();
  } else {
    Serial.println("Esperando datos SCD30...");
  }

  // ===== Mostrar =====
  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print(" °C | Hum: ");
  Serial.print(hum);
  Serial.print(" % | CO2: ");
  Serial.print(co2);
  Serial.println(" ppm");

  // ===== Enviar datos =====
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(servidor);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String datos = "Temperatura=" + String(temperatura, 2) +
                   "&Humedad=" + String(hum, 2) +
                   "&CO2=" + String(co2, 2);

    int httpResponseCode = http.POST(datos);

    if (httpResponseCode > 0) {
      Serial.print("Respuesta servidor: ");
      Serial.println(http.getString());
    } else {
      Serial.println("Error enviando datos");
    }

    http.end();
  }

  delay(5000);
}