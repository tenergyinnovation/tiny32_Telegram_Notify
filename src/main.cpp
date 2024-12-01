/***********************************************************************
 * Project      :     tiny32_Telegram_Notify
 * Description  :     Template coding for tiny32_v3 on vscode with platformIO
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     30/11/2024
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <tiny32_v3.h>
#include <esp_task_wdt.h>

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
Serial.printf("\r\n***********************************************************************\r\n");
Serial.printf("* Project      :     tiny32_Telegram_Notify\r\n");
Serial.printf("* Description  :     Template coding for tiny32_v3 on vscode with platformIO\r\n");
Serial.printf("* Hardware     :     tiny32_v3\r\n");
Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
Serial.printf("* Date         :     30/11/2024\r\n");
Serial.printf("* Revision     :     %s\r\n",version);
Serial.printf("* Rev1.0       :     Origital\r\n");
Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
Serial.printf("* TEL          :     +66 89-140-7205\r\n");
Serial.printf("***********************************************************************/\r\n");
}



/**************************************/
/*            GPIO define             */
/**************************************/


/**************************************/
/*       Constand define value        */
/**************************************/
// 10 seconds WDT
#define WDT_TIMEOUT 10

// Replace with your network credentials
const char* ssid = "XXXXXXXXXXXXXXXX";
const char* password = "XXXXXXXXXXXXXXXXXXX";

// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXXX:XYXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "-XXXXXXXXXXXXX"

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/


/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup() {
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  String imageUrl = "https://img.freepik.com/premium-vector/maintenance-logo-icon_617585-1962.jpg?w=1380";
    bool success = bot.sendPhoto(CHAT_ID, imageUrl, "Start Smart Maintenace System");
}

 /***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    if(mcu.Sw1())
    {
        mcu.buzzer_beep(1);
        bot.sendMessage(CHAT_ID,"Switch 1 pressing");
        while(mcu.Sw1());
    }


    if(mcu.Sw2())
    {
        mcu.buzzer_beep(1);
        bot.sendMessage(CHAT_ID,"Switch 2 pressing");
        while(mcu.Sw1());
    }


    esp_task_wdt_reset();
    vTaskDelay(100);
}
