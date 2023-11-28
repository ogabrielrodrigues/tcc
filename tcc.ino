#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/*
  FRENTE MOTOR DA DIREITA (B2A) = MARROM
  RÉ MOTOR DA DIREITA (B1A) = AZUL

  FRENTE MOTOR DA ESQUERDA (A1B) = MARROM
  RÉ MOTOR DA ESQUERDA (A1A) = BRANCO
*/

// Configuração de rede Wi-Fi
const char* rede = "TCC";
const char* senha = "05092005*";

// Instancia o objeto Udp
WiFiUDP Udp;

// Configura os pacotes e a porta do Udp
unsigned int porta_udp = 12340;
char pacote_pendente[255];
char pacote_resposta[] = "Respondendo!!\n";

void setup() {
  // Configura os pinos do arduino

  // A
  pinMode(13, OUTPUT); // Marrom
  pinMode(12, OUTPUT);  // Vermelho
  pinMode(4, OUTPUT);   // Amarelo
  pinMode(5, OUTPUT);   // Verde

  pinMode(16, OUTPUT); // Marrom
  pinMode(1, OUTPUT); // Roxo
  pinMode(3, OUTPUT); // Cinza
  pinMode(0, OUTPUT); // Branco

  // Configura o modo do Wi-Fi
  WiFiMode(WIFI_AP);

  Serial.begin(115200);
  delay(10);

  // Conectando ao WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(rede);
  WiFi.hostname("ARDUINO");
  WiFi.begin(rede, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi conectado");

  // Print the IP address
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  // Inicia o servidor Udp
  Udp.begin(porta_udp);
}

void Parar() {
  // Desliga os motores da Direita e da Esquerda

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  analogWrite(4, 0);
  analogWrite(5, 0);

  digitalWrite(16, LOW);
  digitalWrite(1, LOW);
  analogWrite(3, 0);
  analogWrite(0, 0);
}

void Frente() {
  // Liga os 2 motores para a Ré

  // A
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  analogWrite(4, 0);
  analogWrite(5, 255);

  // B
  digitalWrite(16, HIGH);
  digitalWrite(1, HIGH);
  analogWrite(3, 0);
  analogWrite(0, 255);
}

void Re() {
  // Liga os 2 motores para a Frente 

  // A
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  analogWrite(4, 255);
  analogWrite(5, 0);

  digitalWrite(16, HIGH);
  digitalWrite(1, HIGH);
  analogWrite(3, 255);
  analogWrite(0, 0);
}

void Gira(int lado) {
  // 0: Direita | 1: Esquerda

  if (lado == 0) {
    // Desliga o motor da Esquerda (A)

    digitalWrite(16, LOW);
    digitalWrite(1, LOW);
    analogWrite(3, 0);    
    analogWrite(0, 0);
    
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    analogWrite(4, 255);
    analogWrite(5, 0);
  } else {
    // Desliga o motor da Direita (B)

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    analogWrite(4, 0);
    analogWrite(5, 0);
    
    digitalWrite(16, HIGH);
    digitalWrite(1, HIGH);
    analogWrite(3, 255);
    analogWrite(0, 0);
  }
}

void loop() {
  // Recebe o pacote Udp
  int tamanho_pacote = Udp.parsePacket();

  if (tamanho_pacote) {
    // Lê o tamanho do pacote
    int tamanho = Udp.read(pacote_pendente, 255);

    // Verifica se o pacote não está vazio
    if (tamanho > 0) {
      pacote_pendente[tamanho] = 0;
    }

    Serial.printf("pacote UDP: %s\n", pacote_pendente);

    // Pega a mensagem
    String mensagem = String(pacote_pendente);
    Serial.printf("Mensagem: %s\n", mensagem);

    // Verifica se a mensagem recebida é o comando para frente
    if (mensagem.startsWith("frente")) {
      Frente();
      delay(250);
      Parar();
    }

    // Verifica se a mensagem recebida é o comando para ré
    if (mensagem.startsWith("re")) {
      Re();
      delay(250);
      Parar();
    }

    // Verifica se a mensagem recebida é o comando para esquerda
    if (mensagem.startsWith("esquerda")) {
      Gira(1);
      delay(200);
      Parar();
    }

    // Verifica se a mensagem recebida é o comando para direita
    if (mensagem.startsWith("direita")) {
      Gira(0);
      delay(200);
      Parar();
    }

    // Responde o client e fecha o pacote
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(pacote_resposta);
    Udp.endPacket();
  }
}
