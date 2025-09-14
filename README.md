# Proyek Robot Pengikut Garis

## Deskripsi Singkat
Proyek ini membuat robot pengikut garis yang menggunakan sensor inframerah (IR), motor DC dengan driver (mis. L298N), dan mikrokontroler Arduino untuk mendeteksi dan mengikuti jalur (garis) pada permukaan. Robot akan bergerak maju, belok kiri/kanan, atau berhenti berdasarkan pembacaan sensor.

## Fitur Utama
- Deteksi garis menggunakan dua sensor IR (kiri dan kanan).
- Kontrol dua motor DC via motor driver.
- Logika sederhana untuk mengikuti garis: maju, belok kiri, belok kanan, dan berhenti.
- Contoh kode Arduino siap pakai untuk pengujian.

## Komponen yang Dibutuhkan
1. Arduino Uno (atau kompatibel)  
2. Sensor Infrared (IR) x2  
3. Motor DC x2 dan Motor Driver (mis. L298N)  
4. Chassis (karton, akrilik, atau bahan lain)  
5. Roda dan komponen mekanis pendukung  
6. Kabel jumper dan breadboard  
7. Power supply (baterai 9V atau baterai pack yang sesuai)

## Skema Singkat & Flow
- Sensor kiri terhubung ke pin digital 5, sensor kanan ke pin digital 6.
- Motor dikendalikan melalui 4 pin output (dua untuk masing-masing motor) dan dua pin enable.
- Logika dasar:
  - Jika kedua sensor tidak mendeteksi garis (LOW): maju lurus.
  - Jika sensor kiri LOW & kanan HIGH: belok kanan.
  - Jika sensor kiri HIGH & kanan LOW: belok kiri.
  - Jika kedua sensor HIGH: berhenti.

Flowchart singkat (teks):
Start → Read sensor kiri & kanan →  
- Kedua LOW → Maju  
- Kiri LOW, Kanan HIGH → Belok kanan  
- Kiri HIGH, Kanan LOW → Belok kiri  
- Kedua HIGH → Berhenti  
End

## Contoh Kode (Arduino)
(Cukup ringkasan; simpan di file .ino)
```cpp
// Pin sensor
int sensorKiri = 5;
int sensorKanan = 6;

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
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  delay(2000);
}

void loop() {
  int bacaSensorKiri = digitalRead(sensorKiri);
  int bacaSensorKanan = digitalRead(sensorKanan);

  if (bacaSensorKiri == LOW && bacaSensorKanan == LOW) {
    majuLurus();
  } else if (bacaSensorKiri == LOW && bacaSensorKanan == HIGH) {
    belokKanan();
  } else if (bacaSensorKiri == HIGH && bacaSensorKanan == LOW) {
    belokKiri();
  } else if (bacaSensorKiri == HIGH && bacaSensorKanan == HIGH) {
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
```

## Cara Menjalankan / Pengujian
1. Rakit rangkaian sesuai penjelasan pin di atas dan datasheet motor driver.
2. Sambungkan sensor ke permukaan berwarna kontras (mis. garis hitam di atas latar putih).
3. Hidupkan power supply, upload sketsa ke Arduino.
4. Uji dan kalibrasi posisi sensor serta kecepatan motor sesuai kebutuhan.

## Tips & Troubleshooting
- Pastikan sensor IR diposisikan dekat ke permukaan (jarak kerja beberapa mm).
- Jika robot terlalu sering melewatkan garis, kurangi kecepatan motor (PWM pada pin enable).
- Periksa pengkabelan motor driver jika motor tidak berputar atau berputar balik.
- Gunakan filter perangkat lunak (debouncing atau pembacaan rata-rata) jika sensor menghasilkan noise.
