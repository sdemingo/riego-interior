/*

  Septiembre 2019


  Consumos medidos:
  - Sistema en reposo o dormido: 3 mA
  - Sistema encendido sin carga: 12 mA
  - Sistema activando el MOSFET de la bomba: 18 mA

*/

#include "LowPower.h"

const int WORKING_TIME = 60;   //secs
const long WORKING_PERIOD = 86400; //secs    86400 -> 1 día       172800 -> 2 dias
const int LED_PERIOD = 5;      //secs

const int LED_PIN = 3;
const int PUMP_PIN = 7;

double ultimoLed = 0, ultimoEncendido = 0, tiempoBombaOn=0, ahora = 0;
bool bombaOn = false;
bool bombaTested = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  //Serial.begin(9600);
}

void loop()
{
  ahora = millis() / 1000;

  // Enciendo el led de control cada LED_PERIOD segundos

  if ((ahora - ultimoLed) > LED_PERIOD)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    ultimoLed = millis() / 1000;
  }

  // Compruebo si enciendo bomba. Cuando se cumpla el periodo o 
  // la primera vez recien arrancada para testearla

  if ((!bombaTested) || ((ahora - ultimoEncendido) > WORKING_PERIOD)){
    digitalWrite(PUMP_PIN, HIGH);
    bombaOn = true;
    bombaTested = true;
    ultimoEncendido = millis() / 1000;
  }

  // Compruebo si apago la bomba
  if ((ahora - ultimoEncendido) > WORKING_TIME){
    if (bombaOn){
      digitalWrite(PUMP_PIN, LOW);
      bombaOn = false;
    }
  }
}
