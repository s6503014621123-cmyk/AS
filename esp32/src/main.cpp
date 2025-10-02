// Worked
#include <Arduino.h>
#include <WiFi.h> // 
#include <ArtronShop_LineMessaging.h> // 

const char* ssid = "Nut"; // 
const char* password = "sussus2468"; // 
#define LINE_TOKEN "pNF+oFF+jK3htyfo4qcqERcyyAM1kLG5re6GyGIL4fWjsRt5nRKJGGHKB+clKIKQVwKSfr12aB2VLC5edJ4L5VVlbALqG0wlw87QdRnTwPYzz/tvANu/FzTkJLve8THgpu7oYyThayvkyMCfTVklPQdB04t89/1O/w1cDnyilFU=" // Channel access token
int m = 0 ;
void Task1(void *pvParameters) {
  while (true) {
    Serial.println("A1" + String(xPortGetCoreID()));
    vTaskDelay(2000 / portTICK_PERIOD_MS);  //
  }
}

// Task 2: 
void Task2(void *pvParameters) {
  while (true){
    m++;
      if (m>= 5){      
        LINE_Messaging_Massage_Option_t option; // option
        LINE.send("C60487adccf1dfde5a206559107fac9e1", "Hello", &option);
        Serial.println("ทำงานเมื่อครบ 5 ครั้ง!"); 
        m = 0; 
      }
    Serial.println("A2" + String(xPortGetCoreID()));
    vTaskDelay(5000 / portTICK_PERIOD_MS);  //
  }
}

void setup() 
{
  Serial.begin(115200); // 
  while (!Serial) 
  { 
    delay(100); 
  }

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // 

  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  LINE.begin(LINE_TOKEN); //

  
   xTaskCreatePinnedToCore(
      Task1,           // Task function
      "Task1",         // Task
      1000,            // Stack size
      NULL,            // Parameter
      1,               // Priority
      NULL,            // Task Handle
      0                // Core 0
  );

  xTaskCreatePinnedToCore(
      Task2,
      "Task2",
      50000,
      NULL,
      1,
      NULL,
      1                // Core 1
  );
}

void loop() 
{

}