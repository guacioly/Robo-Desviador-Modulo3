# 🚗 Robô Desviador de Obstáculos - Módulo 3

<div align="center">
  <img src="https://img.shields.io/badge/Status-Em%20Desenvolvimento-orange?style=for-the-badge" alt="Status Badge"/>
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" alt="Arduino Badge"/>
</div>

<br>

## 📖 Sobre o Projeto
Este repositório contém o planejamento, código-fonte e documentação do **Projeto Final do Módulo 3 - Conceitos Básicos de Robótica**. 

Atualmente, estamos na fase de estruturação. Nosso objetivo final é aplicar os conceitos de controle de atuadores e percepção de ambiente para construir um robô móvel autônomo, capaz de detectar e desviar de obstáculos em tempo real utilizando o circuito integrado L293D e o sensor ultrassônico.

## 🎯 Funcionalidades Planejadas
- **Navegação Autônoma:** O robô se deslocará continuamente pelo ambiente.
- **Detecção de Obstáculos:** Leitura constante do ambiente utilizando pulsos ultrassônicos (Sensor HC-SR04).
- **Tomada de Decisão e Desvio:** Lógica reativa de controle onde o robô avalia a distância segura (ex: `< 20 cm`) para frear, girar à direita e buscar uma nova rota livre.
- **Controle de Potência (CI L293D):** Utilização da Ponte H em formato DIP-16 diretamente na protoboard para controlar o sentido de rotação dos motores e ajustar a velocidade via PWM.

## 🛠️ Hardware a ser Utilizado
Abaixo está a lista dos componentes que usaremos para a montagem:

| Quantidade | Componente |
| :---: | :--- |
| 1x | Arduino Uno (ou Nano) |
| 1x | Chassi robótico (2WD) |
| 2x | Motor DC (TT Motor) |
| 1x | **CI L293D (Ponte H DIP-16)** |
| 1x | **Sensor Ultrassônico (HC-SR04)** |
| 1x | Bateria 9V (ou Suporte 4xAA) |
| 1x | Protoboard (400 pontos) e Jumpers |

## 🔌 Esquema de Ligações (L293D DIP-16)
Como estamos utilizando o CI L293D solto na protoboard, a montagem exige atenção redobrada aos 16 pinos. A pinagem principal que utilizaremos no Arduino é:

* **EN1,2 (Pino 1):** Porta 9 (PWM) - Controle de velocidade Motor A
* **IN1 (Pino 2):** Porta 7 - Direção Motor A
* **IN2 (Pino 7):** Porta 6 - Direção Motor A
* **EN3,4 (Pino 9):** Porta 10 (PWM) - Controle de velocidade Motor B
* **IN3 (Pino 10):** Porta 5 - Direção Motor B
* **IN4 (Pino 15):** Porta 4 - Direção Motor B

<br>

<div align="center">
  <img src="Copy%20of%20Circuito%20Robô%20que%20desvia%20de%20obstáculos.png" alt="Circuito do Robô" width="700px">
  <p align="center">
    <em>Esquema elétrico do Robô: Arduino Uno + L293D + Sensor Ultrassônico</em>
  </p>
</div>
<br>
## 💻 Código Fonte Principal

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

## 🚧 Nosso Cronograma (To-Do)
Acompanhe o nosso progresso durante as aulas:

- [x] Criação do repositório no GitHub e planejamento estrutural.
- [ ] Separação e testes individuais dos componentes eletrônicos.
- [ ] Teste de medição de distância com o sensor HC-SR04 no Arduino.
- [ ] Montagem do circuito do CI L293D na protoboard .
- [ ] Integração do hardware no chassi.
- [ ] Upload do código reativo final.
- [ ] Testes práticos de desvio e calibração de velocidade e tempo de giro.

## 👥 Equipe (Módulo 3)
* Gabriella Sousa
* Giovanne Brendo Coelho Dias Pereira
* Gustavo Lima Acioly
* João Lucas Franca Chagas

---
*Repositório em constante atualização para a apresentação de avanços do curso de Robótica.*
