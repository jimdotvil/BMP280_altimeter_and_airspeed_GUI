#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

int PRESION_LOCAL=1018;
float DENSIDAD=1.225;
float TEMPERATURA=0;
float PRESION_ABSOLUTA=0;
float ALTITUD=0;
float PRESION_DINAMICA=0;
float PRESION_MEDIDA=0;
float VELOCIDAD=0;

void setup() {
  Serial.begin(9600);
//  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    for(int i=0;i<4;i++){
      PRESION_MEDIDA=bmp.readPressure();   
    }
}

void loop() {
    
    TEMPERATURA=((bmp.readTemperature())*(1.8))+32; /*°F*/
    PRESION_ABSOLUTA=bmp.readPressure();            /*Pa*/
    ALTITUD=(bmp.readAltitude(PRESION_LOCAL))/0.3048;/*ft*/
    PRESION_DINAMICA= PRESION_ABSOLUTA-PRESION_MEDIDA; /*Pa*/
    VELOCIDAD=(pow((((PRESION_DINAMICA)/(0.5*DENSIDAD))),0.5)*1.944); /*knot*/
    if (isnan(VELOCIDAD)== 1){
      VELOCIDAD=0;
    }
/* Pabs=Pdin+Patm*/

//    Serial.print(F("TEMPERATURA = "));
//    Serial.print(TEMPERATURA);
//    Serial.println(" *F \n");

//    Serial.print(F("PRESION ABSOLUTA = "));
//    Serial.print(PRESION_ABSOLUTA);
//    Serial.println(" *PA \n");

//    Serial.print(F("ALTITUD = "));
      Serial.print((float)ALTITUD);
//    Serial.println(" *FT \n");
      Serial.print(',');

//    Serial.print(F("PRESION DINAMICA = "));
//    Serial.print(PRESION_DINAMICA);
//    Serial.println(" *PA \n");

//    Serial.print(F("VELOCIDAD = "));
      Serial.println((float)VELOCIDAD);
//    Serial.println(" *KNT \n");
    
    delay(500);
}
