#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WEMOS_SHT3X.h>
#include <WorkShop_Logos.h>
#include <TimeLib.h>

// Configure OLED display
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
// Configure STH30 sensor I2C address
SHT3X sht30(0x45);
int sensorToPrint = 1;

void setup() {

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop() {
  
  clearDisplayBuffer();

  if(sht30.get()==0){
    printSensorsMetricsToOLEDDisplay();
  }
  else
  {
    display.println("Error trying to get STH30 values!");
  }
  
  display.display();
  delay(1000);

}

void clearDisplayBuffer() {
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setRotation(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
}

void printSensorsMetricsToOLEDDisplay() {
  
  float sensorValue1 = analogRead(32) / 100.0f;
  float sensorValue2 = analogRead(33) / 100.0f;
  float sensorValue3 = analogRead(34) / 100.0f;

  char buf[7];
  snprintf (buf, 7, "Sen. %d:", sensorToPrint);

  display.println(buf);
  display.setTextSize(2);
  if (sensorToPrint == 1)
    display.println(sensorValue1, 1);
  else if (sensorToPrint == 2)
    display.println(sensorValue2, 1);
  else
  {
    display.println(sensorValue3, 1);
    sensorToPrint = 0;
  }
  sensorToPrint++;

  display.setTextSize(1);
  display.println("");
  display.print("T: ");
  display.println(sht30.cTemp);
  display.print("H: ");
  display.println(sht30.humidity);

  /*
   * need to deal with this later
  if (timeStatus() != timeSet)
  {
    display.setTextSize(1);
    display.print("Not sending!!!");
    display.setTextSize(1);
  }
  */
  
}
