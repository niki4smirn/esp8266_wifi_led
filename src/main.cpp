#include <ESP8266WiFi.h>  // библиотека для работы с wi-fi модулем
#include <ESP8266WebServer.h>  // баблиотека для создания веб сервера

// впишите сюда данные, соответствующие вашей сети: 
const char* ssid = "........";
const char* password = "........";

ESP8266WebServer server(80);  // инициализация веб сервера на 80 порте

String webPage;  // строка с html разметкой страницы

const int LED_PIN = 2; 

void setup(){
  webPage = "<h1>ESP8266 Web Server</h1><p>LED<a href=\"ledOn\"><button>ON</button></a>&nbsp;<a href=\"ledOff\"><button>OFF</button></a></p>";
  
  // инициализируем порт как выходной
  pinMode(LED_PIN, OUTPUT);
  // выключаем светодиод
  digitalWrite(LED_PIN, HIGH);
  
  delay(1000);
  Serial.begin(115200);
  // подключаемся к wi-fi
  WiFi.begin(ssid, password);
  Serial.println("");

  // ждем соединения:
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");  //  "Подключились к "
  Serial.println(ssid);
  Serial.print("IP address: ");  //  "IP-адрес: "
  Serial.println(WiFi.localIP());
  
  // задаем разметку странице
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/ledOn", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  });
  server.on("/ledOff", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(LED_PIN, HIGH);
    delay(1000); 
  });

  // запускаем сервер
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(){
  server.handleClient();  // обновляем данные с сервера
}