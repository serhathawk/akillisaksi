🌱 Akıllı Saksı Projesi

Bu proje, bir Aloe Vera bitkisinin toprak ve ortam koşullarını izleyerek kullanıcıyla sesli ve görsel (LCD) şekilde etkileşim kurmasını sağlayan bir akıllı saksı sistemidir.
Proje, Arduino tabanlıdır ve sensörlerden alınan veriler doğrultusunda bitkinin ihtiyaçlarını kullanıcıya bildirir.

📌 Proje Amacı

Bu projenin amacı;

Bitkinin toprak nemini,

Ortam sıcaklığını ve

Ortam nemini

sensörler yardımıyla ölçmek ve bu verilere göre bitkinin durumunu sesli uyarılar ve LCD ekran çıktıları ile kullanıcıya aktarmaktır.
Böylece bitkinin bakım süreci daha bilinçli ve etkileşimli hale getirilmiştir.

🧩 Kullanılan Donanımlar

Arduino Uno

Toprak Nem Sensörü

DHT11 Sıcaklık & Nem Sensörü

DS1302 RTC Modülü

DFPlayer Mini MP3 Modülü

Hoparlör

I2C 16x2 LCD Ekran

SD Kart

Jumper kablolar

📚 Kullanılan Kütüphaneler

SoftwareSerial

DFRobotDFPlayerMini

LiquidCrystal_I2C

DHT

Ds1302

⚙️ Sistem Çalışma Mantığı

Toprak nemi belirlenen eşik değerin altına düştüğünde bitki susadığını sesli olarak belirtir.

Ortam sıcaklığı veya nemi Aloe Vera için uygun aralıkların dışına çıktığında, duruma uygun sesli uyarılar verilir.

Ortam koşulları normal olduğunda, belirli aralıklarla rastgele mırıldanma/etkileşim sesleri çalınır.

LCD ekranda:

satırda toprak nem durumu

satırda sıcaklık ve ortam nemi bilgisi
görüntülenir.

🔊 Ses Sistemi Hakkında

Sesler DFPlayer Mini üzerinden oynatılmaktadır.
Tüm ses dosyaları SD kart içerisinde 0001.mp3 – 0014.mp3 formatında sıralı şekilde bulunmaktadır.
Ses içerikleri ElevenLabs kullanılarak üretilmiş olup, bitki sanki konuşuyormuş hissi verecek şekilde tasarlanmıştır.

🎥 Proje Videosu

📌 Proje tanıtım ve çalışma videosu Classroom’a yüklenmiştir.
(GitHub için istersen buraya YouTube linki de ekleyebilirsin.)

👨‍💻 Geliştirici

Proje Sahibi: [İsmini buraya yaz]

Ders: 2209 Proje

Yıl: 2025
