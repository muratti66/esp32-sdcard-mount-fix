-----------------------
## ESP32 SDCard Mount Error Fix (English)

### Error Message
Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.

### Observation of the Symptom 
As a result of an uncontrolled shutdown (such as power failure ..etc) in ESP32, I observed the following situations while the sd card was loaded after esp_vfs_fat_sdmmc_mount in the setup section:
 * error return with esp_err_t
 * LoadProhibited error on the core level
 * The device restarts with a "LoadProhibited" error at the core hardware level.

### Guess of the Root Cause
I did not received this error when I used a 1GB memory card while developing on the card.
<br> However, that the error started to show itself with a 32GB card, which is the highest size I can use. it is interesting..
<br> No errors with software reboots
<br>My guess in this situation is; With the increasing size of the sd card, the device is lagging in disconnecting the sd card, <br>there may be a software error or it may be time insufficient.

### Solution
Firstly; The problem is fixed by re-formatting the SD card, but if the physical device is mounted somewhere, detach of the card and performing this process is a difficult job..
<br>Second; we guessed it might be to support device power with a strong capacitor to reduce latency - maybe - I haven't had a chance to try..
<br>Finally (more applicable) in case of errors, forcing the unmount with the esp_vfs_fat_sdmmc_unmount() command and restarting the device software was the solution, and the device has been working this way for months.
<br>I leave the sample codes for this application in the "mountfix.ino" file for this.

### Please Note: These solution-s were made by many tries and error and are for advice only.

-----------------------
## ESP32 SD kart bağlama hata çözümü (Türkçe)

### Hata Mesajı
```Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.```

### Semtpomun Gözlemlenmesi
ESP32'de kontrolsüz bir kapanma sonucu (güç kesintisi, kapatma .. gibi) cihaz açılırken setup bölümünde esp_vfs_fat_sdmmc_mount <br>
sonrası sd kart yüklenirken aşağıdaki durumlarda gözledim :
 * esp_err_t ile hata dönüşü 
 * core donanım seviyesinde "LoadProhibited" hatası vererek cihaz yeniden başlar.

### Asıl Sebeple ilgili Tahmin
Kart üzerinde geliştirme yaparken 1GB hafıza kartı kullandığım sürede bu hata ile karşılaşmamıştım.
<br>Ancak ilginçtir ki kullanabileceğim en yüksek boyut olan 32GB'lık bir kart ile hata kendini göstermeye başladı.
<br> Yazılımsal yeniden başlatmalarla hata oluşmadı
<br> Bu durumdaki tahminim sd kartta yükselen boyutlarla birlikte cihaz sd kart bağlantısını kesmekte gecikiyor, <br>burada yazılımsal bir hata olabilir veya yetersiz kalıyor olabilir.

### Çözüm
İlk olarak; sorun SD kartın yeniden formatlanması ile düzeliyor ancak cihaz biryere monte edilmiş ise kartın çıkartmak ve bu işlemin uygulanması zor bir iş.
<br>İkincisi sadece tahminde bulunduğum gecikmeyi azaltmak için yüksek mikrofaradlık bir kapasitör ile cihaz gücünü desteklemek olabilir - belki - deneme fırsatım olmadı..
<br>Son olarak (daha uygulanabilir) hata yaşanan durumlarda esp_vfs_fat_sdmmc_unmount() komutu ile bağlantıyı kesmeye zorlamak ve cihazı yazılımsal olarak yeniden başlatmak çözüm oldu ve cihaz aylardır bu şekilde çalışıyor.
<br>Bu uygulama için örnek kodları "mountfix.ino" dosyası içerisine bırakıyorum.

### Ve Not: Bu çözüm-ler deneme yanılma ile yapılmış olup sadece tavsiye amaçlıdır..

-----------------------