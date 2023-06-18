#include "DHT.h" 
int suhu= 30.00;
#define DHTPIN 5 // definisikan pin yang digunakan utk sensor DHT11
const int led = 4;
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = A0;
int soilmoisturepercent=0;


void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(led,OUTPUT);
}

void loop() {
  // Baca humidity dan temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  // Cek hasil pembacaan, dan tampilkan bila ok
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");

  } else {
    Serial.print("Humidity: ");//kelembaban
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
if (t > suhu )
{
  digitalWrite(led,HIGH);
  delay(5000);
}
else 
{
  digitalWrite(led,LOW);
}
//
if(soilmoisturepercent >= 100)
{
  digitalWrite(led,LOW);
  delay(5000);
}
else 
{
   digitalWrite(led,HIGH);
   delay(5000);

  
}
  
}