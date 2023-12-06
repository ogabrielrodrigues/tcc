#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <RobojaxBTS7960.h>

// Motor da Esquerda
#define R_EN_ESQUERDA 13
#define R_PWM_ESQUERDA 4
#define L_EN_ESQUERDA 12
#define L_PWM_ESQUERDA 5

// Motor da Direita
#define R_EN_DIREITA 1
#define R_PWM_DIREITA 0
#define L_EN_DIREITA 16
#define L_PWM_DIREITA 3

#define debug 1
#define CW 1 
#define CCW 0 

// Configuração de rede Wi-Fi
const char* rede = "TCC";
const char* senha = "05092005*";

RobojaxBTS7960 motor_esquerda(R_EN_ESQUERDA, R_PWM_ESQUERDA, 0, L_EN_ESQUERDA, L_PWM_ESQUERDA, 0, debug);
RobojaxBTS7960 motor_direita(R_EN_DIREITA, R_PWM_DIREITA, 0, L_EN_DIREITA, L_PWM_DIREITA, 0, debug);

// Instancia o objeto Udp
WiFiUDP Udp;

// Configura os pacotes e a porta do Udp
unsigned int porta_udp = 12340;
char pacote_pendente[255];
char pacote_resposta[] = "Respondendo!!\n";

void setup() {
  motor_esquerda.begin();
  motor_direita.begin();

  // Configura o modo do Wi-Fi
  WiFiMode(WIFI_AP);

  Serial.begin(115200);
  delay(10);

  // Conectando ao WiFi
  Serial.printf("Conectando à %s\n", rede);
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
      for(int i = 0; i <= 100; i++) { 
        motor_esquerda.rotate(i, CW);
        motor_direita.rotate(i, CW);
        delay(50);
      }

      motor_esquerda.stop();
      motor_direita.stop();
    }

    // Verifica se a mensagem recebida é o comando para ré
    if (mensagem.startsWith("re")) {
      for(int i = 0; i <= 100; i++) { 
        motor_esquerda.rotate(i, CCW);
        motor_direita.rotate(i, CCW);
        delay(50);
      }

      motor_esquerda.stop();
      motor_direita.stop();
    }

    // Verifica se a mensagem recebida é o comando para esquerda
    if (mensagem.startsWith("esquerda")) {
      motor_direita.stop();

      for(int i = 0; i <= 100; i++) { 
        motor_esquerda.rotate(i, CW);
        delay(50);
      } 
  
      motor_esquerda.stop();
    }

    // Verifica se a mensagem recebida é o comando para direita
    if (mensagem.startsWith("direita")) {
      motor_esquerda.stop();

      motor_direita.rotate(40, CW);
  
      motor_direita.stop();
    }

    // Responde o client e fecha o pacote
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(pacote_resposta);
    Udp.endPacket();
  }
}
