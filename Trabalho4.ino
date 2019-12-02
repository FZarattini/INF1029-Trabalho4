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

bool inicio = true;
bool completo = false;
int seconds;
int tenths;


byte generatorState = GENERATOR_STOPPED;
byte ledModeValue = LED_ALL_OFF;

void inicializa(){
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
  completo = false;
}

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  MFS.initialize(&Timer1);
  randomSeed(analogRead(0));
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  byte btn = MFS.getButton();

  switch (generatorState)
  {

    case GENERATOR_STARTED:
    if(!completo){
        if(ledModeValue == LED_ALL_OFF){
        ledModeValue = LED_1_ON;
      }else if(ledModeValue == LED_1_ON){
        Serial.println("VAI ACENDER!");
        MFS.writeLeds(LED_4, OFF);
        MFS.writeLeds(LED_1, ON);
        ledModeValue = LED_2_ON;  
      }else if(ledModeValue == LED_2_ON){
        MFS.writeLeds(LED_1, OFF);
        MFS.writeLeds(LED_2, ON);
        ledModeValue = LED_3_ON;
      }else if(ledModeValue == LED_3_ON){
        MFS.writeLeds(LED_2, OFF);
        MFS.writeLeds(LED_3, ON);
        ledModeValue = LED_4_ON;
      }else if(ledModeValue == LED_4_ON){
        MFS.writeLeds(LED_3, OFF);
        MFS.writeLeds(LED_4, ON);
        ledModeValue = LED_1_ON;
      }  
    }
    
    
	//INICIA O CONTADOR
	tenths++;
	
	if (tenths == 10)
	{
		tenths = 0;
		seconds++;
	}

      if(seconds >= 1)
	  {
		  toDisplay[3] = unidade;
      }
	  else{
        a++;
        if (a == 10){
          a = 0;
        }
        toDisplay[3] = a + '0';
      }

      if(seconds >= 2){
        
		toDisplay[2] = dezena;
		
      }
	  else{
        b++;
        if (b == 10){
          b = 0;
        }
        toDisplay[2] = b + '0';
      }

      if (seconds >= 3){
        toDisplay[1] = centena;
      }
	  else{
        c++;
        if (c == 10){
          c = 0;
        }
        toDisplay[1] = c + '0';
      }

      if(seconds >= 4){
        toDisplay[0] = milhar;
		
      }
	  else{
        d++;
        if (d == 10){
          d = 0;
        }
        toDisplay[0] = d + '0';
      }

      if(seconds >= 5){
        completo = true;
        MFS.writeLeds(LED_1, OFF);
        MFS.writeLeds(LED_2, OFF);
        MFS.writeLeds(LED_3, OFF);
        MFS.writeLeds(LED_4, OFF);
        MFS.blinkDisplay(DIGIT_ALL, ON);
      }


      MFS.write(toDisplay);

      if (btn == BUTTON_1_SHORT_RELEASE && !completo) {
        MFS.write("intr");
        generatorState = GENERATOR_STOPPED;
      }

      if (btn == BUTTON_1_SHORT_RELEASE && completo) {
        inicio = true;
        MFS.blinkDisplay(DIGIT_ALL, OFF);
        generatorState = GENERATOR_STOPPED;
      }
  

      delay(100);

      break;
    case GENERATOR_STOPPED:

      if(inicio = true){
        MFS.write("0000");
      }
      
		//PAUSA O CONTADOR
      if (btn == BUTTON_1_SHORT_RELEASE) {
        if(inicio == true)
		    {
			    inicio = false;
          inicializa();
			    tenths = 0;
			    seconds = 0;
		    }
		
		    generatorState = GENERATOR_STARTED;

      }
      break;
  }

}
