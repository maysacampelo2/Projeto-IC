// Biblioteca do led - neopixel 16
#include <Adafruit_NeoPixel.h>
//Biblioteca do solenoide
#include <TimerOne.h> // obs: essa biblioteca específica foi importante para conseguirmos definir a frequência
//definição da frequência
#define FREQ 15061 //fomos testando uma combinação de frequência e PWM que simultaneamente fizesse o solenoide funcionar, 
//a corrente não ficar tão alta e instável e o som do solenoide ficar mais baixo

const int potenciometro = A0; 
const int solenoide = 9; 
int pwm = 935; // o pwm e a frequência tem a mesma lógica

#define PIN 2
#define NUMPIXELS 16;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //configurações led

void setup() {
  pinMode(solenoide, OUTPUT);
  Serial.begin(9600);
  
  pixels.begin();
  pixels.show(); 

 
  randomSeed(analogRead(A1)); 
  Timer1.initialize(1000000/FREQ); //a biblioteca pede aqui o período em microssegundos e colocamos assim pra conseguir mexer direto na frequência
  Timer1.pwm(solenoide, 512);
}

bool impulso = true; //

void loop() {
  int valor = analogRead(potenciometro);

  //Primavera: colorido
  if (valor < 256) {
    Serial.println("Primavera");
    Serial.println(valor);
    
    for(byte i = 0; i < NUMPIXELS; i++) {
      int R = random(256);
      int G = random(256);
      int B = random(256);
      pixels.setPixelColor(i, pixels.Color(R, G, B));
    }
    
    pixels.show(); 
    
    if (impulso){
    	Timer1.setPwmDuty(solenoide, 1023);
    }
    else{
      	Timer1.setPwmDuty(solenoide, pwm);
    }
    impulso = false;

    
  // Verão - Verde
  } else if (valor < 512) {

    mudarCorFixa(0, 255, 0); 
    
       if (impulso){
       	Timer1.setPwmDuty(solenoide, 1023);
    }
    else{
      	Timer1.setPwmDuty(solenoide, pwm);
    }
    impulso = false;
    

  //Outono - Laranja
  } else if (valor < 768) {
    
    mudarCorFixa(255, 100, 0); 
    
    if (impulso){
    	Timer1.setPwmDuty(solenoide, 1023);
    }
    else{
      	Timer1.setPwmDuty(solenoide, pwm);
    }
    impulso = false;
    

  // Inverno - Desligado
  } else {
    mudarCorFixa(0, 0, 0); // desliga os leds
    
    Timer1.setPwmDuty(solenoide, 0);  // solta as folhas
    impulso = true;
   
  }

  delay(150);

}

//Pintar os leds
void mudarCorFixa(int r, int g, int b) {
  for(byte i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show(); 
}
