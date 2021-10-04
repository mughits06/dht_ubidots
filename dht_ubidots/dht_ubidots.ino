#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 4 // mendifinisikan pin dht di nodemcu adalah 4, D2 = 4
#define DHTTYPE DHT11 // mendefinisikan tipe dht yang kita gunakan

char auth[] = "BBFF-uG8ys6h0LYwfp0ZxLA8TRevuzVMNsu";
char ssid[] = "IDN Boarding School";
char pass[] = "12rpl";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); // setting token client di ubidots
unsigned long last = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); // dht mulai memcabaca suhu kelembapan
  delay(20); // sela 0,02 detik
  client.wifiConnection(ssid,pass); //  menyambungkan ubidots client dengan wifi

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-last>10000){ // jika sudah 10 detik
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis(); // 11
    client.add("Kelembapan",hum); // ubidots client membaca kecepatan
    client.add("Temperatur",hum); // ubidots client membaca suhu
    client.sendAll(true); // ubidots clien mengirimkan semua data
  }

}
