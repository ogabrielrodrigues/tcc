#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
/*
  FRENTE MOTOR DA DIREITA (B2A) = MARROM
  RÉ MOTOR DA DIREITA (B1A) = AZUL

  FRENTE MOTOR DA ESQUERDA (A1B) = MARROM
  RÉ MOTOR DA ESQUERDA (A1A) = BRANCO
*/

const char* rede = "GABRIEL";
const char* senha = "05092005";

WiFiUDP Udp;

unsigned int porta_udp = 12340;
char pacote_pendente[255];
char pacote_resposta[] = "Respondendo!!\n";

void setup() {
  pinMode(13, OUTPUT); // A
  pinMode(12, OUTPUT); // A
  pinMode(4, OUTPUT); // B
  pinMode(5, OUTPUT); // B

  WiFiMode(WIFI_AP);

  Serial.begin(115200);
  delay(10);
 
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(rede);
  WiFi.hostname("ARDUINO");
  WiFi.begin(rede, senha);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

  Udp.begin(porta_udp);
}

void Parar() {
  // A
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);

  // B
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void Re() {
  // A
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);

  // B
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void Frente() {
  // A
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);

  // B
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

void loop() {
  int tamanho_pacote = Udp.parsePacket();

  if (tamanho_pacote) {
    int tamanho = Udp.read(pacote_pendente, 255);

    if (tamanho > 0) {
      pacote_pendente[tamanho] = 0;
    }

    Serial.printf("UDP packet contents: %s\n", pacote_pendente);

    String mensagem = String(pacote_pendente);
    Serial.printf("Mensagem: %s\n", mensagem);

    if (mensagem.startsWith("frente")) {
      Frente();
      delay(800);
      Parar();
    }

    if (mensagem.startsWith("re")) {
      Re();
      delay(800);
      Parar();
    }
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(pacote_resposta);
    Udp.endPacket();
  } 
}
