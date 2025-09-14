# Proyek Robot Pengikut Garis (Line Follower) dengan Arduino

![Arduino](https://img.shields.io/badge/Arduino-UNO-blue?style=for-the-badge&logo=arduino)
![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Hardware-orange?style=for-the-badge)

Proyek ini adalah panduan lengkap untuk membangun sebuah robot pengikut garis (line follower) otonom dari awal. Robot ini menggunakan komponen dasar elektronika seperti mikrokontroler Arduino, sensor inframerah (IR), dan motor DC untuk secara otomatis mendeteksi dan mengikuti sebuah jalur (garis hitam di atas permukaan putih).

## Daftar Komponen

Berikut adalah komponen perangkat keras yang dibutuhkan untuk membangun robot ini:

| No. | Komponen | Jumlah | Keterangan |
| :-- | :--- | :--- | :--- |
| 1. | Mikrokontroler Arduino | 1 | Arduino Uno, Nano, atau yang kompatibel. |
| 2. | Sensor Inframerah (IR) | 2 | Digunakan sebagai "mata" untuk mendeteksi garis. |
| 3. | Motor Driver | 1 | L298N atau sejenisnya untuk mengendalikan motor DC. |
| 4. | Motor DC + Roda | 2 | Motor DC dengan gearbox untuk torsi yang cukup. |
| 5. | Chassis Robot | 1 | Bisa menggunakan akrilik, kayu, atau bahkan karton tebal. |
| 6. | Roda Caster / Roda Bebas | 1 | Sebagai roda ketiga untuk keseimbangan. |
| 7. | Power Supply | 1 | Baterai 9V atau Baterai Pack Li-ion/Li-Po (7.4V - 12V). |
| 8. | Breadboard & Kabel Jumper | Secukupnya | Untuk merangkai sirkuit. |

## Skema Rangkaian dan Koneksi Pin

Robot ini dirangkai dengan menghubungkan sensor dan motor driver ke pin-pin digital pada Arduino.

*(Disarankan untuk menambahkan gambar skema Fritzing atau diagram buatan tangan di sini untuk memperjelas koneksi.)*

Berikut adalah tabel koneksi pin yang digunakan dalam kode:

| Komponen | Pin Komponen | Pin Arduino |
| :--- | :--- | :--- |
| **Sensor IR Kiri** | `OUT` | Pin Digital `5` |
| **Sensor IR Kanan** | `OUT` | Pin Digital `6` |
| **Motor Driver (L298N)** | `IN1` (Motor Kiri) | Pin Digital `8` |
| | `IN2` (Motor Kiri) | Pin Digital `9` |
| | `IN3` (Motor Kanan)| Pin Digital `10`|
| | `IN4` (Motor Kanan)| Pin Digital `11`|
| | `ENA` (Enable Kiri)| Pin Digital `4` |
| | `ENB` (Enable Kanan)| Pin Digital `7` |

**Catatan:** Hubungkan pin `VCC` dan `GND` dari sensor dan motor driver ke pin `5V` dan `GND` pada Arduino. Power supply eksternal (baterai) dihubungkan ke input `V_MOTOR` dan `GND` pada motor driver.

## Prinsip Kerja & Logika Kontrol

Robot bekerja berdasarkan prinsip sederhana pembacaan sensor IR. Sensor IR memancarkan cahaya inframerah dan mendeteksi pantulannya.

-   **Permukaan Putih:** Memantulkan banyak cahaya. Sensor akan membaca **LOW** (0).
-   **Permukaan Hitam (Garis):** Menyerap banyak cahaya. Sensor akan membaca **HIGH** (1).

Logika gerakan robot didasarkan pada kombinasi pembacaan dari kedua sensor tersebut:

| Sensor Kiri (Pin 5) | Sensor Kanan (Pin 6) | Kondisi | Aksi Robot | Fungsi yang Dipanggil |
| :---: | :---: | :--- | :--- | :--- |
| `LOW` (Putih) | `LOW` (Putih) | Robot berada di tengah garis. | Maju Lurus | `majuLurus()` |
| `LOW` (Putih) | `HIGH` (Hitam) | Robot terlalu ke kiri. | Belok Kanan | `belokKanan()` |
| `HIGH` (Hitam) | `LOW` (Putih) | Robot terlalu ke kanan. | Belok Kiri | `belokKiri()` |
| `HIGH` (Hitam) | `HIGH` (Hitam) | Robot mencapai persimpangan/akhir. | Berhenti | `berhenti()` |

## Kode Program

Kode lengkap untuk mengoperasikan robot dapat ditemukan di file `.ino` dalam repositori ini. Berikut adalah ringkasan fungsional dari kode tersebut.

```cpp
/*
 * KODE LENGKAP ROBOT PENGIKUT GARIS
 * ---------------------------------
 * File ini berisi semua logika untuk membaca sensor IR
 * dan menggerakkan motor DC sesuai dengan posisi robot
 * terhadap garis.
 */

// Definisi Pin Sensor
const int sensorKiri = 5;
const int sensorKanan = 6;

// Definisi Pin Motor Driver L298N
const int motorKiri1 = 8;
const int motorKiri2 = 9;
const int motorKanan1 = 10;
const int motorKanan2 = 11;
const int enableA = 4; // Enable untuk motor kiri
const int enableB = 7; // Enable untuk motor kanan

void setup() {
  // Inisialisasi semua pin sebagai INPUT atau OUTPUT
  pinMode(sensorKiri, INPUT);
  pinMode(sensorKanan, INPUT);
  pinMode(motorKiri1, OUTPUT);
  pinMode(motorKiri2, OUTPUT);
  pinMode(motorKanan1, OUTPUT);
  pinMode(motorKanan2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  // Aktifkan motor driver (kecepatan penuh)
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);

  // Beri jeda 2 detik saat pertama kali dinyalakan
  delay(2000);
}

void loop() {
  // Baca nilai digital dari kedua sensor
  int bacaSensorKiri = digitalRead(sensorKiri);
  int bacaSensorKanan = digitalRead(sensorKanan);

  // Terapkan logika kontrol
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

// === Fungsi-Fungsi Gerakan ===

void majuLurus() {
  digitalWrite(motorKiri1, HIGH);
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, HIGH);
  digitalWrite(motorKanan2, LOW);
}

void belokKanan() {
  digitalWrite(motorKiri1, HIGH); // Roda kiri maju
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, LOW); // Roda kanan mundur (untuk belokan tajam)
  digitalWrite(motorKanan2, HIGH);
}

void belokKiri() {
  digitalWrite(motorKiri1, LOW); // Roda kiri mundur
  digitalWrite(motorKiri2, HIGH);
  digitalWrite(motorKanan1, HIGH); // Roda kanan maju
  digitalWrite(motorKanan2, LOW);
}

void berhenti() {
  digitalWrite(motorKiri1, LOW);
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, LOW);
  digitalWrite(motorKanan2, LOW);
}
