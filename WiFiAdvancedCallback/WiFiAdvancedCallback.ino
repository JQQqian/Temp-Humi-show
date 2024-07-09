#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include <DFRobot_DHT11.h>
#include <ArduinoJson.h>

DFRobot_DHT11 DHT;
#define DHT11_PIN 5     //change

char ssid[] = "vivo X100";    // your network SSID (name)
char pass[] = "11111111";    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[]    = "a1eiPYXCiPY.iot-as-mqtt.cn-shanghai.aliyuncs.com";
int        port        = 1883;

const char inTopic[]   = "/sys/a1eiPYXCiPY/esp8266_dev/thing/event/property/set";
const char outTopic[]  = "/sys/a1eiPYXCiPY/esp8266_dev/thing/service/property/post";

const long interval = 10000;
unsigned long previousMillis = 0;

String inputString = "";
int count = 0;

void setup() {
  //Initialize serial and wait for port to open:

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(4,OUTPUT);
  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  mqttClient.setId("a1eiPYXCiPY.esp8266_dev|securemode=2,signmethod=hmacsha256,timestamp=1719451451667|");//ClientID
  mqttClient.setUsernamePassword("esp8266_dev&a1eiPYXCiPY","f33f3eabffbb446a8c2065abdfd52ad4dba73080b13e822c10fbe8430e91efce");//用户名和密码

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(inTopic);
  Serial.println();

  int subscribeQos = 1;

  mqttClient.subscribe(inTopic, subscribeQos);


  Serial.print("Waiting for messages on topic: ");
  Serial.println(inTopic);
  Serial.println();
}

void loop() {

  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;
    
    String payload;

    DHT.read(DHT11_PIN);

    //payload = "{\"params\": {\"temp\": 40,\"humi\":66},\"version\":\"1.0.0\"}";


    Serial.print(DHT.temperature);
    Serial.println(DHT.humidity);

    DynamicJsonDocument json_msg(512);
    DynamicJsonDocument json_data(512);

    json_data["temp"] = DHT.temperature;
    json_data["humi"] = DHT.humidity;

    json_msg["params"] = json_data;
    json_msg["version"] = "1.0.0";

    serializeJson(json_msg,payload);

    Serial.print("Sending message to topic: ");
    Serial.println(outTopic);
    Serial.println(payload);

    bool retained = false;
    int qos = 1;
    bool dup = false;

    mqttClient.beginMessage(outTopic, payload.length(), retained, qos, dup);
    mqttClient.print(payload);
    mqttClient.endMessage();

    Serial.println();

    count++;
  }
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', duplicate = ");
  Serial.print(mqttClient.messageDup() ? "true" : "false");
  Serial.print(", QoS = ");
  Serial.print(mqttClient.messageQoS());
  Serial.print(", retained = ");
  Serial.print(mqttClient.messageRetain() ? "true" : "false");
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    char inChar =(char)mqttClient.read();
    inputString +=inChar;
    if(inputString.length()==messageSize) {

      DynamicJsonDocument json_msg(1024);
      DynamicJsonDocument json_item(1024);
      DynamicJsonDocument json_value(1024);

      deserializeJson(json_msg,inputString);

      String items = json_msg["items"];

      deserializeJson(json_item,items);
      String led = json_item["led"];

      deserializeJson(json_value,led);
      bool value = json_value["value"];

      if(value ==0) {
        //关
        Serial.println("off");
        digitalWrite(4,HIGH);
      } else {
        //开
        Serial.println("on");
        digitalWrite(4,LOW);
      }
      inputString="";
    }


  }
  Serial.println();

  Serial.println();
}
