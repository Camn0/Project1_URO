// Pin sensor
const int sensorKiri = A0;
const int sensorKanan = A1;

// Pin motor
const int motorKiriMaju = 5;
const int motorKananMaju = 6;

void setup() {
  pinMode(sensorKiri, INPUT);
  pinMode(sensorKanan, INPUT);
  pinMode(motorKiriMaju, OUTPUT);
  pinMode(motorKananMaju, OUTPUT);
}

void loop() {
  int bacaSensorKiri = analogRead(sensorKiri);
  int bacaSensorKanan = analogRead(sensorKanan);

  if (bacaSensorKiri < 500) { // sensor kiri mendeteksi garis
    belokKiri();
  } else if (bacaSensorKanan < 500) { // sensor kanan mendeteksi garis
    belokKanan();
  } else {
    majuLurus();
  }
}

void belokKiri() {
  digitalWrite(motorKiriMaju, LOW);
  digitalWrite(motorKananMaju, HIGH);
}

void belokKanan() {
  digitalWrite(motorKiriMaju, HIGH);
  digitalWrite(motorKananMaju, LOW);
}

void majuLurus() {
  digitalWrite(motorKiriMaju, HIGH);
  digitalWrite(motorKananMaju, HIGH);
}
