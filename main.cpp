#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>
#include <ArduinoJson.h>


const char* ssid = "Wokwi-GUEST";
const char* password = ""; 


const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "leonardo/1espb/dados";


#define DHT_PIN 15
#define LDR_PIN 34 

const float gama = 0.7; 
const float rl10 = 50;   


WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dht;


void connectToWiFi() {
  Serial.print("Conectando-se ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi!");
}


void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect("ESP32ClientLeonardo")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  connectToWiFi();

  client.setServer(mqtt_server, 1883);
  connectToMQTT();

  dht.setup(DHT_PIN, DHTesp::DHT22); 
}


void loop() {
  
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  
  int ldr = analogRead(LDR_PIN);
  ldr = map(ldr, 4095, 0, 1024, 0);  

  float tensao = ldr / 1024.0 * 5;  
  float resistencia = 2000 * tensao / (1 - tensao / 5); 
  float brilho = pow(rl10 * 1e3 * pow(10, gama) / resistencia, (1 / gama));  
  Serial.print(brilho);

  
  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Falha na leitura do sensor DHT!");
  } else if(brilho > 200) {
    Serial.print("Temperatura: ");
    Serial.print(data.temperature);
    Serial.print(" °C | Umidade: ");
    Serial.print(data.humidity);
    Serial.println(" %");

    

    
    StaticJsonDocument<128> doc;
    doc["temperatura"] = data.temperature;
    doc["umidade"] = data.humidity;


    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer);

    
    client.publish(mqtt_topic, jsonBuffer);
  }

  delay(5000); 
}
