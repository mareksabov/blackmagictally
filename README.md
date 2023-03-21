# Black Magic Tally light 

- based on ```https://oneguyoneblog.com/2020/06/13/tally-light-esp32-for-blackmagic-atem-switcher/```

## Installation

### Install M5StickC board to arduino studio

- Pridat Esp32 boardy: File > Preferencies > Addition Board Manager: ```https://dl.espressif.com/dl/package_esp32_index.json```
- Nainstalovar Esp32 platformu: Tools > Board > Board Manager > esp32
- Nainstalovat M5StickC: Sketch > Include library > Manage libraries > M5StickC

### Choose Board

- Zvolit board: Tools > Board > Esp32 Arduino > M5Stick-C
- Zvolit Tools > UploadSpeed: 1500000
- Zvolit Tools > Port : COM port na ktory je pripojeny board

## Sketch Edit

### Zmena Client ip
24: ```IPAddress clientIp(192, 168, 0, 61);```
- nastavit volnu ip adresu pre Esp32 
- je mozne ze ju DHCP server prenastavi

### Zmena BlackMagic ip
25: ```IPAddress switcherIp(192, 168, 0, 60);```
- nastavit ip adresu ATEM switcheru

### Zmena Wifi SSID
33: ```const char* ssid = "wifiSSID";```
- nastavit wifi SSID

### Zmena Wifi Password
34: ```const char* password =  "wifiPassword";```
- nastavit wifi heslo

### Zmena Camera Id
36: ```int cameraNumber = 1;```
- zmenic cislo kamery pre konkretny tally light