const int trigPin = 26;
const int echoPin = 32;
const int buttonPin = 22;
const int umidadePin = 34; // ADC para potenciômetro (sensor de umidade simulado)

const float limiteSeguro = 150.0;  // acima disso, seguro (água baixa)
const float limiteAlerta = 100.0;  // entre alerta e seguro
const float limitePerigo = 50.0;   // perigo se menor que isso

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // botão com pull-up interno
  // pinMode(umidadePin, INPUT);  // opcional, ADC já é entrada por padrão
}

void loop() {
  bool chovendo = (digitalRead(buttonPin) == LOW);

  float distancia = medirDistancia();

  int umidadeRaw = analogRead(umidadePin);  // lê valor do potenciômetro (0-4095)
  float umidadePercent = map(umidadeRaw, 0, 4095, 0, 100); // converte para 0-100%

  Serial.print("Chovendo? ");
  Serial.println(chovendo ? "Sim" : "Nao");

  Serial.print("Distancia medida: ");
  Serial.print(distancia);
  Serial.print(" cm - ");

  if (distancia < limitePerigo) {
    Serial.println("Status: PERIGO - Enchente! RISCO MAXIMO!");
  } else if (distancia < limiteAlerta) {
    Serial.println("Status: ALERTA");
  } else if (distancia < limiteSeguro) {
    Serial.println("Status: SEGURO");
  } else {
    Serial.println("Status: NORMAL (agua baixa)");
  }

  Serial.print("Umidade simulada: ");
  Serial.print(umidadePercent);
  Serial.println(" %");

  Serial.println("---------------------------");
  delay(1000);
}

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  float distancia = (duration * 0.0343) / 2;
  return distancia;
}
