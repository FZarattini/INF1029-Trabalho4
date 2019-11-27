#include <MultiFuncShield.h>
#include <TimerOne.h>

enum GeneratorStates
{
  GENERATOR_STARTED,
  GENERATOR_STOPPED
};

enum LEDModeValue
{
  LED_ALL_OFF,
  LED_1_ON,
  LED_2_ON,
  LED_3_ON,
  LED_4_ON
};

long randNumber;
long randNumberAux;
long unidade;
long dezena;
long centena;
long milhar;
long a = 0;
long b = 0;
long c = 0;
long d = 0;
char toDisplay[4];
String ca;
String cb;
String cc;
String cd;
bool unidadeDisplay = false;
bool dezenaDisplay = false;
bool centenaDisplay = false;
bool milharDisplay = false;

byte generatorState = GENERATOR_STOPPED;
byte ledMoveValue = LED_ALL_OFF;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  MFS.initialize(&Timer1);
  randomSeed(analogRead(0));
  randNumber = random(0, 10000);
  randNumberAux = randNumber;
  unidade = randNumberAux % 10;
  randNumberAux /= 10;
  dezena = randNumberAux % 10;
  randNumberAux /= 10;
  centena = randNumberAux % 10;
  randNumberAux /= 10;
  milhar = randNumberAux;
  unidade = unidade + '0';
  dezena = dezena + '0';
  centena = centena + '0';
  milhar = milhar + '0';
  
}

void loop() {
  // put your main code here, to run repeatedly:
  byte btn = MFS.getButton();

  switch (generatorState)
  {

    case GENERATOR_STARTED:

      if(unidadeDisplay){
        
      }else{
        a++;
        if (a == 10){
          a = 0;
        }
        toDisplay[3] = a + '0';
      }

      if(dezenaDisplay){
        
      }else{
        b++;
        if (b == 10){
          b = 0;
        }
        toDisplay[2] = b + '0';
      }

      if (centenaDisplay){
        
      }else{
        c++;
        if (c == 10){
          c = 0;
        }
        toDisplay[1] = c + '0';
      }

      if(milharDisplay){
        
      }else{
        d++;
        if (d == 10){
          d = 0;
        }
        toDisplay[0] = d + '0';
      }

      //delay(10000);
      MFS.write(toDisplay);

      if (btn == BUTTON_1_SHORT_RELEASE) {
        MFS.write("intr");
        generatorState = GENERATOR_STOPPED;
      }
  
      delay(100);

    case GENERATOR_STOPPED:

      if (btn == BUTTON_1_SHORT_RELEASE) {
        generatorState = GENERATOR_STARTED;
      }
  }

  //MFS.write((int)randNumber);
}
