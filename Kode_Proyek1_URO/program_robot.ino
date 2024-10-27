   // Pin sensor
   int sensorKiri = 5;
   int sensorKanan = 6;
   int bacaSensorKiri = 0;
   int bacaSensorKanan = 0;

   // Pin motor
   int motorKiri1Maju = 8;
   int motorKiri2Maju = 9;
   int motorKanan1Maju = 10;
   int motorKanan2Maju = 11;

   // Pin enable
   int enableA = 4;
   int enableB = 7;

   void setup() {
     pinMode(sensorKiri, INPUT);
     pinMode(sensorKanan, INPUT);
     pinMode(motorKiri1Maju, OUTPUT);
     pinMode(motorKiri2Maju, OUTPUT);
     pinMode(motorKanan1Maju, OUTPUT);
     pinMode(motorKanan2Maju, OUTPUT);
     digitalWrite(enableA, HIGH); 
     digitalWrite(enableB, HIGH); 
     delay(2000)
   }

   void loop() {
     int bacaSensorKiri = digitalRead(sensorKiri);
     int bacaSensorKanan = digitalRead(sensorKanan);

     if (bacaSensorKiri == LOW && bacaSensorKanan == LOW) { // sensor kiri dan kanan lemah
       majuLurus();
     }
     if (bacaSensorKiri == LOW && bacaSensorKanan == HIGH) { // sensor kanan mendeteksi garis
       belokKanan();
     }
     if (bacaSensorKiri == HIGH && bacaSensorKanan == LOW) { // sensor kiri mendeteksi garis
       belokKiri();
     }
     if (bacaSensorKiri == HIGH && bacaSensorKanan == HIGH) { // berhenti
       berhenti();
     }
   }

   void belokKiri() {
     digitalWrite(motorKiri1Maju, LOW);
     digitalWrite(motorKanan1Maju, HIGH);
     digitalWrite(motorKiri2Maju, HIGH);
     digitalWrite(motorKanan2Maju, LOW);
   }

   void belokKanan() {
     digitalWrite(motorKiri1Maju, HIGH);
     digitalWrite(motorKanan1Maju, LOW);
     digitalWrite(motorKiri2Maju, LOW);
     digitalWrite(motorKanan2Maju, HIGH);
   }

   void majuLurus() {
     digitalWrite(motorKiri1Maju, HIGH);
     digitalWrite(motorKanan1Maju, HIGH);
     digitalWrite(motorKiri2Maju, LOW);
     digitalWrite(motorKanan2Maju, LOW);
   }

   void berhenti() {
     digitalWrite(motorKiri1Maju, LOW);
     digitalWrite(motorKanan1Maju, LOW);
     digitalWrite(motorKiri2Maju, LOW);
     digitalWrite(motorKanan2Maju, LOW);
}
