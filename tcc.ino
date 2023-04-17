/*
  FRENTE MOTOR DA DIREITA (B2A) = MARROM
  RÉ MOTOR DA DIREITA (B1A) = AZUL

  FRENTE MOTOR DA ESQUERDA (A1B) = MARROM
  RÉ MOTOR DA ESQUERDA (A1A) = BRANCO
*/

void setup() {
  pinMode(13, OUTPUT); // A
  pinMode(12, OUTPUT); // A
  pinMode(4, OUTPUT); // B
  pinMode(5, OUTPUT); // B
}

void Re() {
  // A
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);

  // B
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

void Frente() {
  // A
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);

  // B
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void loop() {
  Re();
  delay(2000);
  
  Frente();
  delay(2000);
}
