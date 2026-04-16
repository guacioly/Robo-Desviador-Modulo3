# 🚗 Robô Desviador de Obstáculos - Módulo 3

<div align="center">
  <img src="https://img.shields.io/badge/Status-Em%20Desenvolvimento-orange?style=for-the-badge" alt="Status Badge"/>
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" alt="Arduino Badge"/>
</div>

<br>

## 📖 Sobre o Projeto
Este repositório contém a documentação e o código-fonte do **Projeto Final do Módulo 3**. O objetivo é integrar hardware e software para criar um robô móvel autônomo capaz de navegar em um ambiente, identificar obstáculos via sensor ultrassônico e realizar desvios automáticos utilizando o **CI L293D**.

## 🎯 Funcionalidades
- **Movimentação Inteligente:** O robô avança até encontrar um bloqueio.
- **Leitura de Distância:** Sensor HC-SR04 monitora objetos em tempo real.
- **Desvio Reativo:** Ao detectar um obstáculo a menos de 20cm, o robô para e vira à direita.

## 🛠️ Hardware Utilizado
A montagem utiliza componentes discretos para maior aprendizado sobre eletrônica:

| Componente | Função |
| :--- | :--- |
| **Arduino Uno** | Microcontrolador (Cérebro do robô) |
| **CI L293D** | Ponte H DIP-16 para controle dos motores |
| **Sensor HC-SR04** | Medição de distância por ultrassom |
| **Motores DC (2x)** | Tração e locomoção |
| **Chassi 2WD** | Estrutura física do robô |
| **Protoboard** | Base para montagem do circuito do CI |
| **Bateria 9V** | Alimentação do sistema |

## 🔌 Esquema de Ligações
As conexões no Arduino seguem a configuração abaixo:

* **Ponte H (L293D):**
  * Motores A: Pinos **9** (EN), **7** (IN1) e **6** (IN2).
  * Motores B: Pinos **10** (EN), **5** (IN3) e **4** (IN4).
* **Sensor Ultrassônico:**
  * **TRIG:** Pino **12**
  * **ECHO:** Pino **11**

<br>

<div align="center">
  <img src="circuito.png" alt="Diagrama do Circuito" width="800"/>
</div>

<br>

## 💻 Código Fonte Principal
O código utiliza funções modulares para facilitar a leitura e manutenção:

```cpp
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
  digitalWrite(TRIG, HIGH); delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);
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
