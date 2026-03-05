# EchoPlay

EchoPlay ist eine selbst entwickelte Spielkonsole, die von einem ESP32 angetrieben wird. Sie verfügt über eine 16x16 LED-Matrix-Anzeige und enthält eine Sammlung klassischer Arcade-Spiele sowie Hilfsprogramme. Das System ist modular aufgebaut, wobei jedes Spiel und jedes Programm in einer eigenen Bibliothek gekapselt ist.

## Hardware

Die Konsole besteht aus folgenden Hauptkomponenten:

- **Prozessor:** SparkFun ESP32-S2 WROOM MicroMod
- **Anzeige:** Eine benutzerdefinierte 16x16 LED-Matrix
- **Eingabe:**
  - Zwei Qwiic-Buttons für primäre Spielaktionen (z. B. Bewegung, Springen)
  - Ein gelber Druckknopf zum Wechseln zwischen den verfügbaren Programmen
  - Ein roter Druckknopf zum Ein- und Ausschalten des Displays

Detaillierte Hardware-Schaltpläne und Verdrahtungsdiagramme befinden sich im Ordner `/chart`, insbesondere in der Datei `EchoPlay_Steckplan_250826.drawio`.

## Spiele und Programme

Die EchoPlay-Konsole enthält mehrere vorinstallierte Anwendungen:

- **Snake:** Das klassische Spiel, bei dem du eine Schlange steuerst, Äpfel einsammelst und dabei wächst, ohne gegen Wände oder dich selbst zu stossen. Es gibt drei Schwierigkeitsstufen, die die Geschwindigkeit der Schlange anpassen.

- **Car-Jump:** Ein Endlos-Runner, inspiriert vom Chrome-Dino-Spiel. Springe über Autos und andere Hindernisse, um so lange wie möglich zu überleben. Die Geschwindigkeit steigt im Verlauf des Spiels.

- **Arkanoid:** Ein Retro-Blockbreaker. Steuere ein Paddle am unteren Bildschirmrand, um einen Ball zurückzuschlagen und alle Blöcke am oberen Rand zu zerstören.

- **Clock:** Ein Hilfsprogramm, das sich mit deinem WLAN verbindet, um über NTP die aktuelle Uhrzeit und das Datum abzurufen und anzuzeigen. Die Sekunden werden durch ein wanderndes Pixel am Rand des Displays visualisiert.

## Steuerung

Die Konsole wird über einfache Bedienelemente gesteuert:

- **Gelber Knopf:** Wechselt im Hauptmenü zum nächsten Spiel oder Programm
- **Roter Knopf:** Schaltet die LED-Matrix ein oder aus
- **Linker und rechter Qwiic-Button:** Hauptsteuerung innerhalb der Spiele (z. B. links/rechts bewegen, springen, ducken)

## Software-Architektur

Das Projekt wurde mit PlatformIO für das ESP32-Framework entwickelt. Die Architektur ist modular gestaltet, sodass neue Spiele oder Programme einfach hinzugefügt werden können.

- **Kernschnittstellen:**
  Eine abstrakte Klasse `IProgramm` definiert die Grundstruktur aller Anwendungen (`setup`, `update`).
  Die Klasse `IGame` erbt von `IProgramm` und erweitert diese um spieltypische Logik wie Startbildschirm, Game-Over-Zustand und Endbildschirm.

- **Bildschirmverwaltung:**
  Die Klasse `Screen` stellt eine High-Level-API zum Zeichnen auf der 16x16-Anzeige bereit und verwaltet einen 2D-Bildpuffer.

- **Hardware-Treiber:**
  - `LedWallEncoder`: Wandelt den 2D-Bildpuffer mithilfe einer `TranslationTable` in einen 1D-Puffer um, der dem physischen Layout der LED-Matrix entspricht.
  - `LEDWallDriver`: Übernimmt die Low-Level-Signalisierung, um die Pufferdaten an die Schieberegister der LED-Matrix zu senden.

- **Spielbibliotheken:**
  Jedes Spiel (`Snake`, `Car-Jump`, `Arkanoid`) sowie das Hilfsprogramm (`Clock`) ist als eigenständige Bibliothek im Ordner `lib` implementiert und folgt dem `IGame`- oder `IProgramm`-Interface.

Detaillierte UML-Diagramme zur Code-Struktur befinden sich im Ordner `/chart`.

## Kompilieren und Ausführen

So kannst du das Projekt auf eigener Hardware ausführen:

1. **Voraussetzungen:** VS Code mit installierter PlatformIO-IDE-Erweiterung

2. **Repository klonen:** Repository lokal auf deinen Rechner klonen

3. **Projekt öffnen:** In PlatformIO den Projektordner unter `code/EchoPlay` öffnen

4. **WLAN-Zugangsdaten:**
   Für das Clock-Programm musst du deine WLAN-Zugangsdaten angeben.
   Erstelle dazu eine Datei `Secrets.h` im Verzeichnis `code/EchoPlay/lib/Wifi/` mit folgendem Inhalt:

   ```cpp
   #define WIFI_SSID "deine_wifi_ssid"
   #define WIFI_PASSWORD "dein_wifi_passwort"
   ```

5. **Hardware aufbauen:** ESP32, LED-Matrix und Buttons gemäss den Plänen im Ordner `/chart` anschliessen

6. **Build und Upload:** Projekt in PlatformIO kompilieren und auf den SparkFun ESP32 MicroMod hochladen

## Projektdateien

- `code/EchoPlay/` – Haupt-PlatformIO-Projekt mit Quellcode
- `code/Snake-in-C/` – Früher, eigenständiger Prototyp von Snake in C für die Konsolenausführung
- `chart/` – Draw.io-Dateien mit UML-Diagrammen, Ablaufdiagrammen und Verdrahtungsplänen
- `docs/` – Projektplanung, Anträge und weitere Dokumentation
