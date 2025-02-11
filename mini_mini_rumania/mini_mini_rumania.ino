#include <Arduino.h>
#include <Servo.h>

// Definición de pines para sensores y motores
#define LINE_B 10   // Sensor de línea izquierdo
#define LINE_A A5   // Sensor de línea derecho
#define RIGHT A4    // Sensor derecho
#define FRONT_A A3  // Sensor frontal derecho
#define FRONT_B A6  // Sensor frontal izquierdo
#define LEFT A1     // Sensor izquierdo
#define Mder1 3     // Motor derecho 1
#define Mder2 6     // Motor derecho 2
#define Mizq1 9     // Motor izquierdo 1
#define Mizq2 5     // Motor izquierdo 2

// Definición de pines para servos
#define SERVO1_PIN 7
#define SERVO2_PIN 12

// Definición de pulsos para servos
#define PULSE_0 1000    // Pulso para 0 grados (en microsegundos)
#define PULSE_90 1500   // Pulso para 90 grados (en microsegundos)
#define PULSE_180 2000  // Pulso para 180 grados (en microsegundos)
#define DELAY_MS 20     // Delay entre pulsos (en milisegundos)

// Definición de pines para control remoto y botón
const int REMOTE = 2;  // Pin de entrada para control remoto
const int buttonPin = 13;  // Pin de entrada para botón

// Variables para el estado del botón y sensores
int initial = 0;      // Estado inicial
int oldstate = 0;     // Último estado
int buttonstate = 0;  // Estado del botón

int sensorState;  // Estado de los sensores
int lineState;    // Estado de las líneas

// Variables para el control del tiempo
unsigned long tiempoInicio;
bool contadorIniciado;

// Variable para el control de la dirección de giro
bool turn_Clockwise;

// Inicialización de servos
Servo servo1;
Servo servo2;

void setup() {
  // Configuración de pines
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LINE_A, INPUT);
  pinMode(LINE_B, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(FRONT_A, INPUT);
  pinMode(FRONT_B, INPUT);
  pinMode(Mizq1, OUTPUT);
  pinMode(Mizq2, OUTPUT);
  pinMode(Mder1, OUTPUT);
  pinMode(Mder2, OUTPUT);
  pinMode(REMOTE, INPUT);
  pinMode(buttonPin, INPUT);
  
  // Inicialización de servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // Inicialización de la comunicación serial
  Serial.begin(9600);
  
  // Inicialización de variables
  contadorIniciado = false;
  tiempoInicio = 0;
  turn_Clockwise = false;
  
  // Mensaje de inicio
  Serial.println("Starting booting sequence...");
  
  // Generar pulsos iniciales para los servos
  for (int i = 0; i < 20; i++) {
    generarPulso(SERVO1_PIN, PULSE_0);
    generarPulso(SERVO2_PIN, PULSE_180);
  }
}

// Función para leer el estado de los sensores
int sensorValue() {
  int sens1 = digitalRead(FRONT_A) * 1;  // Sensor frontal derecho
  int sens2 = digitalRead(FRONT_B) * 2;  // Sensor frontal izquierdo
  int sens3 = digitalRead(RIGHT) * 4;    // Sensor derecho
  int sens4 = digitalRead(LEFT) * 8;     // Sensor izquierdo
  int total = sens1 + sens2 + sens3 + sens4;
  return total;
}

// Función para leer el estado de las líneas
int lineValue() {
  int line1 = digitalRead(LINE_A) * 1;   // Línea derecha
  int line2 = !digitalRead(LINE_B) * 2;  // Línea izquierda
  int total = line1 + line2;
  return total;
}

// Función genérica para controlar los motores
void controlMotores(int potenciaDerecha1, int potenciaDerecha2, int potenciaIzquierda1, int potenciaIzquierda2) {
  analogWrite(Mder1, potenciaDerecha1);
  analogWrite(Mder2, potenciaDerecha2);
  analogWrite(Mizq1, potenciaIzquierda1);
  analogWrite(Mizq2, potenciaIzquierda2);
}

// Funciones para controlar los motores
void adelante(int potenciaDerecha, int potenciaIzquierda) {
  controlMotores(potenciaDerecha, LOW, potenciaIzquierda, LOW);
}

void atras(int potenciaDerecha, int potenciaIzquierda) {
  controlMotores(LOW, potenciaDerecha, LOW, potenciaIzquierda);
}

void paro() {
  controlMotores(LOW, LOW, LOW, LOW);
}

void derecha(int potenciaDerecha, int potenciaIzquierda) {
  controlMotores(LOW, potenciaDerecha, potenciaIzquierda, LOW);
}

void izquierda(int potenciaDerecha, int potenciaIzquierda) {
  controlMotores(potenciaDerecha, LOW, LOW, potenciaIzquierda);
}

// Función para generar pulsos para los servos
inline void generarPulso(int pin, int microsegundos) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(microsegundos);
  digitalWrite(pin, LOW);
  delay(DELAY_MS);
}

// Función principal de batalla naval
void batallanaval(bool temblor = false) {
  Serial.println(digitalRead(REMOTE));
  while (digitalRead(REMOTE) == HIGH) {
    lineState = lineValue();
    switch (lineState) {
      case 3:
        Serial.print("negro - ");
        sensorState = sensorValue();
        switch (sensorState) {
          case 3:
            Serial.println("caso  1");
            derecha(90, 90);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 2:
            Serial.println("caso 2 ");
            izquierda(90, 90);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 1:
            Serial.println("caso  3");
            if (temblor && turn_Clockwise) {
              adelante(240, 30);
              delay(40); 
              paro();
              delay(75);
              adelante(30, 240);
              delay(40); 
              paro();
              delay(75);
              turn_Clockwise = false;
            } else if (temblor && !turn_Clockwise) {
              adelante(30, 240);
              delay(40); 
              paro();
              delay(75);
              adelante(240, 30);
              delay(40); 
              paro();
              delay(75);
              turn_Clockwise = true;
            } else {
              if (!contadorIniciado) {
                tiempoInicio = millis();
                contadorIniciado = true;
              }
              if (contadorIniciado && (millis() - tiempoInicio >= 800)) {
                adelante(240, 240);
                delay(20); 
                paro();
              } else {
                adelante(100, 100);
                delay(20);
                paro();
                delay(10);
              }
            }
            break;
          case 4:
            Serial.println("caso  4");
            derecha(200, 200);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 5:
            Serial.println("caso  5");
            derecha(120, 120);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 8:
            Serial.println("caso  8");
            izquierda(200, 200);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 10:
            Serial.println("caso  10");
            izquierda(120, 120);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 15:
            Serial.println("caso Todos");
            derecha(130, 130);
            delay(50);
            contadorIniciado = false;
            break;
          case 11:
            Serial.println("caso 11");
            izquierda(105, 105);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          case 7:
            Serial.println("caso 12");
            derecha(155, 155);
            delay(20);
            paro();
            delay(10);
            contadorIniciado = false;
            break;
          default:
            Serial.println("no detecta nada");
            adelante(255, 255);
            delay(80);
            paro();
            delay(1000);
            contadorIniciado = false;
            break;
        }
        break;
      case 1:
        Serial.println("Blanco 1 derecha");
        atras(240, 240);
        delay(300);
        paro();
        delay(20);
        izquierda(240, 240);
        delay(300);
        paro();
        delay(200);
        contadorIniciado = false;
        break;
      case 2:
        Serial.println("Blanco 2. izquierda");
        atras(240, 240);
        delay(500);
        paro();
        delay(20);
        izquierda(240, 240);
        delay(305);
        paro();
        delay(200);
        contadorIniciado = false;
        break;
      case 0:
        Serial.println("Blanco doble");
        atras(240, 240);
        delay(300);
        paro();
        delay(20);
        izquierda(240, 240);
        delay(300);
        paro();
        delay(200);
        contadorIniciado = false;
        break;
      default:
        Serial.println("Line default");
        break;
    }
  }
  if (digitalRead(REMOTE) == LOW) {
    paro();
    generarPulso(SERVO1_PIN, PULSE_0);
    generarPulso(SERVO2_PIN, PULSE_180);
    Serial.println("Apagado");
  }
}

// Funciones para diferentes movimientos
void CurveLeft() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    adelante(240, 150);
    delay(400);
    paro();
    delay(50);
    batallanaval();
  }
}

void CurveRight() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    adelante(150, 240);
    delay(400);
    paro();
    batallanaval();
  }
}

void Rocket() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    adelante(240, 240);
    delay(100);
    paro();
    batallanaval();
  }
}

void RocketDerecha() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    adelante(240, 240);
    delay(100);
    paro();
    izquierda(240, 240);
    delay(240);
    paro();
    delay(100);
    batallanaval();
  }
}

void VueltaDerceha() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    derecha(240, 240);
    delay(90);
    paro();
    batallanaval();
  }
}

void defa() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    adelante(240, 240);
    delay(10);
    paro();
    batallanaval();
  }
}

void temblor() {
  if (digitalRead(REMOTE) == HIGH) {
    generarPulso(SERVO1_PIN, PULSE_180);
    generarPulso(SERVO2_PIN, PULSE_0);
    batallanaval(true);
  }
}

// Función principal del loop
void loop() {
  buttonstate = digitalRead(buttonPin);  // Leer el estado del botón
  if (buttonstate == HIGH) {             // Si el botón está presionado
    delay(150);
    buttonstate = digitalRead(buttonPin);  // Leer el estado del botón nuevamente
    if (buttonstate == LOW) {              // Si el botón está liberado
      initial = oldstate + 1;              // Incrementar el estado inicial
      if (initial > 5) {
        oldstate = 0;
      }
    }
    batallanaval(true);
  }
}

void loop() {
  buttonstate = digitalRead(buttonPin);  // Leer el estado del botón
  if (buttonstate == HIGH) {             // Si el botón está presionado
    delay(150);
    buttonstate = digitalRead(buttonPin);  // Leer el estado del botón nuevamente
    if (buttonstate == LOW) {              // Si el botón está liberado
      initial = oldstate + 1;              // Incrementar el estado inicial
      if (initial > 5) {
        oldstate = 0;
      }
    }
  } else {  // Si el botón no está presionado
    delay(150);
  }
  if(initial % 2 == 0 || initial == 0){
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  switch (initial) {  // Reaccionar al estado del botón
    case 1:
      Serial.println("rocket");
      Rocket();
      oldstate = initial;
      break;
    case 2:
      Serial.println("rocketderecha");
      RocketDerecha();
      oldstate = initial;
      break;
    case 3:
      Serial.println("curveleft");
      CurveLeft();
      oldstate = initial;
      break;
    case 4:
      Serial.println("curveright");
      CurveRight();
      oldstate = initial;
      break;
    case 5:
      Serial.println("Terremoto");
      temblor();
      oldstate = initial;
      break;
    case 6:
      Serial.println("vuelta derecha");
      VueltaDerceha();
      oldstate = initial;
      break;
    default:
      Serial.println("defaul case 0");
      defa();
      oldstate = 0;
      break;
  }
}