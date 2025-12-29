#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Ds1302.h>

// ===== PINLER =====
#define TOPRAK_PIN A0
#define DHTPIN 9
#define DHTTYPE DHT11

#define RTC_RST 5
#define RTC_DAT 6
#define RTC_CLK 7

// ===== NESNELER =====
SoftwareSerial dfSerial(10, 11);
DFRobotDFPlayerMini dfplayer;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
Ds1302 rtc(RTC_RST, RTC_CLK, RTC_DAT);

// ===== AYARLAR =====
const int KURU_ESIK = 800;

// Aloe vera ortam eşikleri
const float SICAK_MIN = 10.0;
const float SICAK_MAX = 30.0;
const float NEM_MIN   = 20.0;
const float NEM_MAX   = 70.0;

// ZAMANLAR
const unsigned long UYARI_ARALIK = 6000;      // 6 sn
const unsigned long MIRILDANMA_ARALIK = 600000; // 10 dk

unsigned long sonToprakUyari = 0;
unsigned long sonHavaUyari   = 0;
unsigned long sonMirildanma  = 0;

bool onceKuru = false;

enum HavaDurum { NORMAL, COK_SOGUK, COK_SICAK, COK_NEMLI, COK_KURU };
HavaDurum mevcutHava = NORMAL;

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  dfSerial.begin(9600);

  lcd.init();
  lcd.backlight();

  dht.begin();
  rtc.init();

  if (!dfplayer.begin(dfSerial)) {
    while (true);
  }

  dfplayer.volume(30);

  lcd.setCursor(0, 0);
  lcd.print("Akilli Saksi");
  delay(2000);
  lcd.clear();
}

// ===== LOOP =====
void loop() {
  unsigned long simdi = millis();

  int toprakNem = analogRead(TOPRAK_PIN);
  float sicaklik = dht.readTemperature();
  float havaNem = dht.readHumidity();

  // ===== LCD =====
  lcd.setCursor(0, 0);
  if (toprakNem <= KURU_ESIK) {
    lcd.print("ISLAK-");
    lcd.print(toprakNem);
    lcd.print("<K-");
    lcd.print(KURU_ESIK);
  } else {
    lcd.print("I-");
    lcd.print(KURU_ESIK);
    lcd.print("<KURU-");
    lcd.print(toprakNem);
  }
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(sicaklik, 1);
  lcd.print("C N:");
  lcd.print(havaNem, 0);
  lcd.print("% ");

  // ===== TOPRAK KURU =====
  if (toprakNem > KURU_ESIK) {
    if (simdi - sonToprakUyari >= UYARI_ARALIK) {
      dfplayer.playMp3Folder(random(1, 3)); // 0001-0003
      sonToprakUyari = simdi;
      onceKuru = true;
    }
  } else {
    if (onceKuru) {
      dfplayer.playMp3Folder(random(3, 5)); // 0003-0005
      onceKuru = false;
    }
  }

  // ===== HAVA DURUMU BELİRLE =====
  HavaDurum yeniDurum = NORMAL;

  if (sicaklik < SICAK_MIN) yeniDurum = COK_SOGUK;
  else if (sicaklik > SICAK_MAX) yeniDurum = COK_SICAK;
  else if (havaNem > NEM_MAX) yeniDurum = COK_NEMLI;
  else if (havaNem < NEM_MIN) yeniDurum = COK_KURU;

  // ===== HAVA SESLERİ (TOPRAK GİBİ TEKRARLI) =====
  if (yeniDurum != NORMAL) {
    if (simdi - sonHavaUyari >= UYARI_ARALIK) {
      switch (yeniDurum) {
        case COK_SOGUK: dfplayer.playMp3Folder(5); break;
        case COK_SICAK: dfplayer.playMp3Folder(6); break;
        case COK_NEMLI: dfplayer.playMp3Folder(7); break;
        case COK_KURU:  dfplayer.playMp3Folder(8); break;
        default: break;
      }
      sonHavaUyari = simdi;
    }
  }

  mevcutHava = yeniDurum;

  // ===== MIRILDANMA (10 DK) =====
  if (simdi - sonMirildanma >= MIRILDANMA_ARALIK &&
      mevcutHava == NORMAL &&
      toprakNem <= KURU_ESIK) {

    dfplayer.playMp3Folder(random(9, 15)); // 0009–0014
    sonMirildanma = simdi;
  }

  delay(500);
}