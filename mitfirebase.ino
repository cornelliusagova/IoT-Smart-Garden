#include <ThingSpeak.h>  
// Library yang diperlukan
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN D4
#define LED D3
#define DHTTYPE DHT11
#define relay D7

// Harus diisi
#define FIREBASE_HOST "iot-system-ac4bc-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HOj4GuXsXmbwgx0wMPUacVbTziwMLmVpdqWWaGhW"
#define WIFI_SSID "ppppp"
#define WIFI_PASSWORD "pppppppp"  

DHT dht(DHTPIN, DHTTYPE);
           
WiFiClient  client;   
unsigned long ChannelNumber =  1975388;       
const char * ReadAPIKey = "II8DTMMX9HBIBHBN"; 
const int FieldNumber1 = 1;  

// mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;



void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(relay, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("5200411479");
  Serial.println("CORNELLIUS AGOVA MADU PUTERA");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop(){
  int A = ThingSpeak.readLongField(ChannelNumber, FieldNumber1, ReadAPIKey);
  // Sensor Soil Mosture membaca kelembaban tanah
  int s = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String p = "Aktif";
  String m = "Tidak-Aktif";
  String siram = "Menyiram";
  String normal = "Tidak-Menyiram";
  String tidak = "Tidak-Menyiram";

  if(A==1){
    Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/soil", s);
    Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/Humidity", h);
    Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/Temperature", t);
    Firebase.setString(firebaseData, "/Hasil_Pembacaan/status", p);
     // Menampilkan kelembaban tanah pada serial monitor
    Serial.print("--------Hasil--------");
    Serial.print("\n");
    Serial.print("Kelembaban : ");
    Serial.print(s); 
    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F(" Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print("\n");
    Serial.print("💻 Data terkirim");
    Serial.print("\n");
    fuzzy();
    
    }else if(A==0){
    Firebase.setString(firebaseData, "/Hasil_Pembacaan/status", m);
    Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
    digitalWrite(relay, LOW);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    }
    
  delay(500);
}

void fuzzy(){
  int s = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String p = "Aktif";
  String m = "Mati";
  String siram = "Menyiram";
  String normal = "Tidak-Menyiram";
  String tidak = "Tidak-Menyiram";

  if(t>=15 && t<=20 &&s>=1 && s<=500){
    Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
    digitalWrite(relay, LOW);
    }else if(t>=15 && t<=20 && s>=501 && s<=600){
      Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
      digitalWrite(relay, LOW);
      }else if(t>=15 && t<=20 && s>=601 && s<=750){
        Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", siram);
        digitalWrite(relay, HIGH);
        }else if(t>=20 && t<=25 && s>=1 && s<=500){
          Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
          digitalWrite(relay, LOW);
          }else if(t>=20 && t<=25 && s>=501 && s<=600){
            Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
            digitalWrite(relay, LOW);
             }else if(t>=20 && t<=25 && s>=601 && s<=750){
              Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", siram);
              digitalWrite(relay, HIGH);
               }else if(t>=25 && t<=30 && s>=1 && s<=500){
                  Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
                  digitalWrite(relay, LOW);
                  }else if(t>=25 && t<=30 && s>=501 && s<=600){
                    Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
                    digitalWrite(relay, LOW);
                    }else if(t>=25 && t<=30 && s>=601 && s<=750){
                      Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", siram);
                      digitalWrite(relay, HIGH);
                      }else if(t>=30 && t<=35 && s>=1 && s<=500){
                        Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
                        digitalWrite(relay, LOW);
                         }else if(t>=30 && t<=35 && s>=501 && s<=600){
                          Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", siram);
                          digitalWrite(relay, HIGH);
                           }else if(t>=30 && t<=35 && s>=601 && s<=750){
                            Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", siram);
                            digitalWrite(relay, HIGH);
                            }else{
                              Firebase.setString(firebaseData, "/Hasil_Pembacaan/air", tidak);
                              digitalWrite(relay, LOW);
                              }
  }
