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

### Install requider libraries

- v zlozke ```requiderLibraries``` su upravene kniznice pre Esp32
- Tieto kniznice treba nakopirovat do {Arduino Libraries}
- {Arduino Libraries} cestu zistime tak, ze pozrieme File > Preferences > Sketchbook location a k ceste pridame \libraries


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

### Zmena Camera Id po zapnuti
37: ```int cameraNumber = 1;```
- zmenit cislo kamery ktore sa nastavi po zapnuti tally light

### Zmena Max Camera Id
39: ```int maxCameraNumber = 8;```
- zmenit maximalne mozne cislo kamery, po presiahnuti tohto cisla sa cameraNumber prepne naspat na 1

## Ovladanie

- Po spusteni sa Tally light automaticky pripoji k wifine nastavenej v kode.
- Po pripojeni k wifi sa na displeji zobrazi nastavene cislo kamery.
- V pripade ze je display cierny, sa Tally nedokazalo pripojit k wifi
- Stlacenim a podrzanim Tlacitka A, sa zmeni cislo kamery smerom hore, Display preblikne oranzovou farbou pre upozornenie
- Po dosiahnuti maximalneho cisla kamery, sa dalsim stlacenim Tlacitka A nastavi znovu cislo 1

## FAQ

### Chyby pri kompilacii

#### exec: "python": executable file not found in $PATH
- Overit ze je pythohn3 nainstalovany spustenim v terminali ```python3 --version```
- Spustit v terminali prikaz ```sed -i -e 's/=python /=python3 /g' ~/Library/Arduino15/packages/esp32/hardware/esp32/*/platform.txt```
