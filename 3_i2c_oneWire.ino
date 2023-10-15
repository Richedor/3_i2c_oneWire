#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(4);  // Broche de données du DS18B20
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialisation du bus I2C

  sensors.begin();  // Initialisation du DS18B20
}

void loop() {
  float temperatureDS18B20;
  float sensorData[3];  // Tableau pour stocker les données de 3 capteurs I2C

  // Lecture des capteurs I2C
  for (int i = 0; i < 3; i++) {
    Wire.beginTransmission(0x50 + i);  // Remplacez 0x50 par l'adresse I2C du capteur
    Wire.write(0x00);  // Remplacez 0x00 par le registre de lecture de votre capteur
    Wire.endTransmission();

    Wire.requestFrom(0x50 + i, 2);  // 2 octets de données
    if (Wire.available() == 2) {
      int msb = Wire.read();
      int lsb = Wire.read();
      int rawData = (msb << 8) | lsb;
      sensorData[i] = rawData / 100.0;  // Conversion en une valeur utile
    }
  }

  // Lecture du capteur DS18B20
  sensors.requestTemperatures();  // Demande de la température
  temperatureDS18B20 = sensors.getTempCByIndex(0);

  // Affichage des données dans le moniteur série
  Serial.print("Capteur I2C 1: ");
  Serial.print(sensorData[0]);
  Serial.println(" unité de mesure");
  Serial.print("Capteur I2C 2: ");
  Serial.print(sensorData[1]);
  Serial.println(" unité de mesure");
  Serial.print("Capteur I2C 3: ");
  Serial.print(sensorData[2]);
  Serial.println(" unité de mesure");
  Serial.print("Température DS18B20: ");
  Serial.print(temperatureDS18B20);
  Serial.println(" °C");
  Serial.println();

  delay(5000);  // Attendre 5 secondes avant de lire à nouveau les capteurs
}
