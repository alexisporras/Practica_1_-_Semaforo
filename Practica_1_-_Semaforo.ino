//LEDSS
#define ledAzul 2
#define ledRojo 6
#define ledAmarillo 7
#define ledVerde 8
//BOTON
#define boton 9
//POTENCIOMETRO
#define pot A0

//INICIALIZAR VARIABLES
boolean valorLedAzul =  LOW;
boolean valorLedRojo =  LOW;
boolean valorLedAmarillo =  LOW;
boolean valorLedVerde =  LOW;

boolean flag = false;

long valorPot = 0;
int cont = 0;
float valorPotQuarter = 0;
int contW = 0;

void setup() {
  //ASIGNAR MODO DEL PIN
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(boton, INPUT_PULLUP);

  //INICIA PUERTO SERIE
  Serial.begin(9600);
}

void loop() {
  //ASIGNAR EN VARIABLE EL VALOR DEL POTENCIOMETRO
  valorPot = analogRead(pot);

  //MULTIPLICAR PARA TENER MAS TIEMPO DE ESPERA
  valorPot = valorPot * 10;
  valorPotQuarter = valorPot / 20;

  //INICIALIZAR PROGRAMA CON METODO
  semaforo();

  //PRUEBA PARA VER EL VALOR ESPERA
  Serial.print(valorPot);
  Serial.print("\n");
}

void peaton() {
  //METODO PARA LA ACCION DEL BOTON
  while (digitalRead(boton) == LOW)
  {
    flag = true;
  }

  if (flag == true)
  {
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);

    for (int i = 0; i < 5; i++) {
      digitalWrite(ledAzul, HIGH); //Parpadeo azul(peaton)
      delay(250);
      digitalWrite(ledAzul, LOW); //Parpadeo azul (peaton)
      delay(250);
    }
    flag = false;
    digitalWrite(ledRojo, LOW);
    semaforo();
  }
}

void semaforo() {
  //METODO PARA LA SECUENCIA DEL SEMAFORO

  peaton();
  digitalWrite(ledVerde, HIGH); //Inicia verde
  for (int i = 0; i < 19; i++) {
    peaton();
    delay(valorPotQuarter);
    peaton();
  }

  while (cont < 3)
  {
    peaton();
    digitalWrite(ledVerde, LOW); //Parpadeo cuando se cambia a verde
    peaton();
    delay(200);
    peaton();
    digitalWrite(ledVerde, HIGH); //Parpadeo cuando se cambia a verde
    peaton();
    delay(200);
    peaton();
    digitalWrite(ledVerde, LOW); //Parpadeo cuando se cambia a verded
    peaton();
    cont = cont + 1;
  }

  cont = 0;//Reiniciar contador para utilizarlo de nuevo


  digitalWrite(ledAmarillo, HIGH); //Inicia amarillo
  delay(3000);

  digitalWrite(ledAmarillo, LOW); //Parpadeo cuando se cambia a amarillo

  digitalWrite(ledRojo, HIGH); //Inicia rojo
  delay(5000);
  digitalWrite(ledRojo, LOW); //Apaga rojo
}
