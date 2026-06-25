#include <Adafruit_NeoPixel.h>
#include <Servo.h>

Servo servomotor;
const int potenciometro = A0;

int primavera = 255;
int verao = 255;
int outono = 128;
int inverno = 0;

#define PIN 2
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  pixels.begin();
  pixels.show(); 
  
  randomSeed(analogRead(A1)); 
  
  servomotor.attach(5);

}

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
    servomotor.write(0);
    

  // Verão - Verde
  } else if (valor < 512) {

  Serial.println("Verão");
    Serial.println(valor);
    
    mudarCorFixa(0, 255, 0); 
    servomotor.write(0);
    
       
   
  //Outono - Laranja
  } else if (valor < 768) {
    
    Serial.println("Outono");
    Serial.println(valor);

    mudarCorFixa(255, 100, 0); 
    
  servomotor.write(120);
    

  // Inverno - Desligado
  } else {
    Serial.println("Inverno");
    Serial.println(valor);
    mudarCorFixa(0, 0, 0);
    
    servomotor.write(180);
    
  
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
