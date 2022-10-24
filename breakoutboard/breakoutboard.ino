/*
Example script reading measurement values from the HTE501 sensor via I2C interface.

Copyright 2022 E+E Elektronik Ges.m.b.H.

Disclaimer:
This application example is non-binding and does not claim to be complete with regard
to configuration and equipment as well as all eventualities. The application example
is intended to provide assistance with the TEE/HTE501 sensor module design-in and is provided "as is".
You yourself are responsible for the proper operation of the products described.
This application example does not release you from the obligation to handle the product safely
during application, installation, operation and maintenance. By using this application example,
you acknowledge that we cannot be held liable for any damage beyond the liability regulations
described.

We reserve the right to make changes to this application example at any time without notice.
In case of discrepancies between the suggestions in this application example and other E+E
publications, such as catalogues, the content of the other documentation takes precedence.
We assume no liability for the information contained in this document.
*/

#include <hte501I2c.h> // include both classes 
#include <tee501I2c.h>
#include <Wire.h>
hte501I2c hte1(0x40); // initialise the HTE with the i2c address 0x40
hte501I2c hte2(0x42); // initialise the HTE with the i2c address 0x42
tee501I2c tee(0x48); // initialise the TEE with the i2c address 0x48
#define REQUEST_INTERVAL_MS 2000 //Time interval between measurements in ms
#define CSV_DELIMITER ','

float temperature = 0, humidity = 0, dewpoint = 0;
unsigned char identification[8];
char errorString[200];
uint8_t errorcode;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  errorcode = hte1.readIdentification(identification); // read the serialnumber
  if (errorcode != 0)
  {
    hte1.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print("HTE501_1: Identificationnumber: ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(identification[i] < 16 ? "0" : "");
      Serial.print(identification[i], HEX);
    }
  }
    errorcode = hte2.readIdentification(identification); // read the serialnumber
  if (errorcode != 0)
  {
    hte2.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print("\nHTE501_2:Identificationnumber: ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(identification[i] < 16 ? "0" : "");
      Serial.print(identification[i], HEX);
    }
  }
  errorcode = tee.readIdentification(identification); // read the serialnumber
  if(errorcode != 0)
  {
    tee.getErrorString(errorcode,errorString);
    Serial.println(errorString); 
  }
  else 
  {
    Serial.print("\nTEE501: Identificationnumber: ");
    for(int i = 0; i < 8; i++)
    {
      Serial.print(identification[i] < 16 ? "0" : "");
      Serial.print(identification[i],HEX);
    }
  }
  Serial.println("");
  Serial.print("HTE1: temperature");
  Serial.print(CSV_DELIMITER);
  Serial.print(" relative humidity");
  Serial.print(CSV_DELIMITER);
  Serial.print(" dewpoint");
  Serial.print(" HTE2: temperature");
  Serial.print(CSV_DELIMITER);
  Serial.print(" relative humidity");
  Serial.print(CSV_DELIMITER);
  Serial.print(" dewpoint");
  Serial.print(" TEE2: temperature\n");
  delay(1000);
}

void loop()
{
  errorcode = hte1.singleShotTempHum(temperature, humidity); // get temperature and humidity from the first hte sensor
  if (errorcode != 0)
  {
    hte1.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print(temperature);
    Serial.print(" °C");
    Serial.print(CSV_DELIMITER);
    Serial.print(humidity);
    Serial.print(" %RH");
    Serial.print(CSV_DELIMITER);
  }
  errorcode = hte1.getDewpoint(dewpoint); // get the dewpoint from the first HTE sensor
  if (errorcode != 0)
  {
    hte1.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print(dewpoint);
    Serial.print(" °C");
    Serial.print(CSV_DELIMITER);
  }
    errorcode = hte2.singleShotTempHum(temperature, humidity); // get temperature and humidity from the second HTE sensor
  if (errorcode != 0)
  {
    hte2.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print(temperature);
    Serial.print(" °C");
    Serial.print(CSV_DELIMITER);
    Serial.print(humidity);
    Serial.print(" %RH");
    Serial.print(CSV_DELIMITER);
  }
  errorcode = hte2.getDewpoint(dewpoint); // get the dewpoint from the second HTE sensor
  if (errorcode != 0)
  {
    hte2.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print(dewpoint);
    Serial.print(" °C");
    Serial.print(CSV_DELIMITER);
  }
  errorcode = tee.singleShotTemp(temperature); // get temperature from the TEE sensor
  if(errorcode != 0)
  {
      tee.getErrorString(errorcode,errorString);
      Serial.println(errorString); 
  }
  else 
  {
    Serial.print(temperature);
    Serial.println(" °C");
  }
  delay(REQUEST_INTERVAL_MS);
}
