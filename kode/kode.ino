#include "DHT.h"
int suhu = 30.00;
#define DHTPIN 5 // Definisikan pin yang digunakan untuk sensor DHT11
const int led = 4;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int AirValue = 620;   // Anda perlu mengganti nilai ini dengan Value_1
const int WaterValue = 310;  // Anda perlu mengganti nilai ini dengan Value_2
int soilMoistureValue = A0;
int soilmoisturepercent = 0;

unsigned long previousMillis = 0;
const unsigned long interval = 60000; // Waktu interval 1 menit (60.000 milidetik)

bool ledState = false;
bool isSensorConditionMet = false; // Menyimpan status apakah salah satu atau kedua sensor memenuhi syarat

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(led, OUTPUT);
}

void loop() {
  // Baca humidity dan temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  soilMoistureValue = analogRead(A0);  // Masukkan sensor ke dalam tanah
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, WaterValue, AirValue, 0, 100); // Memperbaiki penyesuaian nilai

  // Cek hasil pembacaan, dan tampilkan jika berhasil
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); // Kelembaban
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }

  // Periksa apakah salah satu atau kedua sensor memenuhi syarat
  if (t >= suhu || soilmoisturepercent >= 79) { // Memperbaiki kondisi sensor kelembapan terbalik
    isSensorConditionMet = true;
  } else {
    isSensorConditionMet = false;
  }

  // Kontrol LED berdasarkan kondisi sensor
  if (isSensorConditionMet) {
    unsigned long currentMillis = millis();
    unsigned long elapsedMillis = currentMillis - previousMillis;
    
    // Jika sudah melewati interval 1 menit (nyala-mati), flip-flop LED
    if (elapsedMillis >= interval) {
      ledState = !ledState; // Toggle LED state
      digitalWrite(led, ledState ? HIGH : LOW);
      
      // Reset waktu sebelumnya sesuai dengan keadaan LED saat ini
      previousMillis = currentMillis - (elapsedMillis - interval);
    }
  } else {
    digitalWrite(led, LOW);
    previousMillis = 0; // Reset waktu sebelumnya jika kedua sensor tidak memenuhi syarat
  }

  delay(250);
}
