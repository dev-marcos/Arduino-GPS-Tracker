#include <TimeLib.h> 
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "config.h"

//tempo de atualização em milisegundos
#define LOG_RATE 10000 


//definição do arquivo gerado
#define LOG_FILE_PREFIX "gpslog"
#define MAX_LOG_FILES 100 
#define LOG_FILE_SUFFIX "csv"
#define LOG_COLUMN_COUNT 8

//definição de comunicação
#define BAUD_RATE 9600
#define PIN_GPS_TX 3
#define PIN_GPS_RX 4
#define PIN_LORA_RX 6
#define PIN_LORA_TX 7
#define PIN_SD_CS 8

const int UTC_offset = -3;


char logFileName[13]; 

char * log_col_names[LOG_COLUMN_COUNT] = {
  //"latitude", "longitude", "altitude", "velocidade", "percurso", "data", "hora", "satélites"
  "latitude", "longitude", "altitude", "speed", "course", "date", "time", "satellites"
}; 
 

unsigned long LAST_LOG = 0; 
 
TinyGPSPlus tinyGPS; 

SoftwareSerial ssGPS(PIN_GPS_TX, PIN_GPS_RX);
SoftwareSerial ssLora(PIN_LORA_TX, PIN_LORA_RX);

void configureLora(){
  //Device EUI: 0012F80000000986 
  ssLora.println("AT+NJM=0"); //(0:ABP/1:OTAA)
  delay(2000);
  //Application EUI
  ssLora.println("AT+APPEUI=70:B3:D5:7E:D0:02:19:28");
  delay(2000);
  //Device Address
  ssLora.println("AT+DADDR=26:01:18:A3");
  delay(2000);
  //Network Session Key
  ssLora.println("AT+NWKSKEY=65:FA:24:86:2A:05:68:F6:48:7D:F5:41:CA:7E:26:F0");
  delay(2000);
  //App Session Key
  ssLora.println("AT+APPSKEY=4C:68:F3:F9:F5:0F:43:9A:C4:55:5E:2F:51:B1:C2:FE");
  delay(500);
}

void sendLora(double latitude, double longitude){
  ssLora.print(F("AT+SEND=6:")); 
  ssLora.print(latitude,6); 
  ssLora.print(F(",")); 
  ssLora.println(longitude,6);  
}

 
void setup()
{
  Serial.begin(BAUD_RATE);
  ssGPS.begin(BAUD_RATE);
  ssLora.begin(BAUD_RATE);

//  GPS_Timezone_Adjust();
 
  Serial.println("Iniciando Cartão SD");

  if (!SD.begin(PIN_SD_CS))
  {
   Serial.println("Erro ao abrir o cartão");
  }
  updateFileName();
  printHeader(); 
}
 
void loop()
{
  if (LAST_LOG <= millis()){

    if (tinyGPS.location.isUpdated()){
      if (logGPSData()){
        Serial.println("GPS registrado."); 
        printSerialGPS(); 
        sendLora(tinyGPS.location.lat(), tinyGPS.location.lng());
        LAST_LOG = millis() + LOG_RATE;
      }else{
        Serial.println("Falha ao registrar novos dados do GPS.");
      }
      
    }else{
      Serial.print("Não há dados de GPS. Sat.: ");
      Serial.println(tinyGPS.satellites.value());
    }
  }

  ssGPS.listen();
  while (ssGPS.available())
    tinyGPS.encode(ssGPS.read());

}

void printSerialGPS(){
  for (int i = 0; i < LOG_COLUMN_COUNT; i++){
      Serial.print(log_col_names[i]);
      if (i < LOG_COLUMN_COUNT - 1)
        Serial.print(',');
      else
        Serial.println();
    }
  Serial.print(tinyGPS.location.lat(), 6);
  Serial.print(',');
  Serial.print(tinyGPS.location.lng(), 6);
  Serial.print(',');
  Serial.print(tinyGPS.altitude.feet(), 1);
  Serial.print(',');
  Serial.print(tinyGPS.speed.mph(), 1);
  Serial.print(',');
  Serial.print(tinyGPS.course.deg(), 1);
  Serial.print(',');
  Serial.print(tinyGPS.date.value());
  Serial.print(',');
  Serial.print(tinyGPS.time.value());
  Serial.print(',');
  Serial.print(tinyGPS.satellites.value());
  Serial.println(); 
}

void GPS_Timezone_Adjust(){
  ssGPS.listen();
  while (ssGPS.available()) {
    if (tinyGPS.encode(ssGPS.read())) { 
      
      int Year = tinyGPS.date.year();
      byte Month = tinyGPS.date.month();
      byte Day = tinyGPS.date.day();
      byte Hour = tinyGPS.time.hour();
      byte Minute = tinyGPS.time.minute();
      byte Second = tinyGPS.time.second();
      
      setTime(Hour, Minute, Second, Day, Month, Year);
      adjustTime(UTC_offset * SECS_PER_HOUR);  

    }
  }
}

  
void printHeader(){
  File logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile){
    for (int i = 0; i < LOG_COLUMN_COUNT; i++){
      logFile.print(log_col_names[i]);
      if (i < LOG_COLUMN_COUNT - 1)
        logFile.print(',');
      else
        logFile.println();
    }
    logFile.close();
  }
}


 byte logGPSData()
{
  File logFile = SD.open(logFileName, FILE_WRITE);
 
  if (logFile){ 
    logFile.print(tinyGPS.location.lat(), 6);
    logFile.print(',');
    logFile.print(tinyGPS.location.lng(), 6);
    logFile.print(',');
    logFile.print(tinyGPS.altitude.feet(), 1);//in feet
    logFile.print(',');
    logFile.print(tinyGPS.speed.mph(), 1);//in mph
    logFile.print(',');
    logFile.print(tinyGPS.course.deg(), 1);//in degrees
    logFile.print(',');
    logFile.print(tinyGPS.date.value());
    logFile.print(',');
    logFile.print(tinyGPS.time.value());
    logFile.print(',');
    logFile.print(tinyGPS.satellites.value());
    logFile.println();
    logFile.close();
 
    return 1; 
  }
 
  return 0; 
}

void updateFileName(){
  for (int i = 0; i < MAX_LOG_FILES; i++){
    memset(logFileName, 0, strlen(logFileName)); 
    sprintf(logFileName, "%s%d.%s", LOG_FILE_PREFIX, i, LOG_FILE_SUFFIX);
    if (!SD.exists(logFileName)){
      break; 
    }
    else{
      Serial.print(logFileName);
      Serial.println(" existe"); 
    }
  }
  Serial.print("Nome do arquivo: ");
  Serial.println(logFileName);
}
