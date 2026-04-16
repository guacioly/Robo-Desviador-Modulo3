// ■■ Pinos do CI L293D ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
#define EN12 9 // Enable Motor A (PWM)
#define IN1 7 // Direção Motor A – entrada 1
#define IN2 6 // Direção Motor A – entrada 2
#define EN34 10 // Enable Motor B (PWM)
#define IN3 5 // Direção Motor B – entrada 1
#define IN4 4 // Direção Motor B – entrada 2
// ■■ Pinos do Sensor Ultrassônico ■■■■■■■■■■■■■■■■■■■■■■■■■■■■
#define TRIG 12
#define ECHO 11
#define DIST_MIN 20 // distância mínima em cm
void setup() {
pinMode(EN12, OUTPUT); pinMode(EN34, OUTPUT);
pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
analogWrite(EN12, 200); // velocidade Motor A
analogWrite(EN34, 200); // velocidade Motor B
}
void moverFrente() {
digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // Motor A frente
digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Motor B frente
}
void parar() {
digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
void virarDireita() {
digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); // Motor A ré
digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Motor B frente
delay(500);
}
long medirDistancia() {
digitalWrite(TRIG, LOW); delayMicroseconds(2);
digitalWrite(TRIG, HIGH); delayMicroseconds(10); digitalWrite(TRIG, LOW);
long duracao = pulseIn(ECHO, HIGH);
if (duracao == 0) return 999; // guarda: sem retorno = longe
return duracao * 0.034 / 2;
}
void loop() {
long dist = medirDistancia();
if (dist < DIST_MIN) {
parar();
delay(300);
virarDireita();
} else {
moverFrente();
}
}