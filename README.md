# EchoPlay

## Inhaltsverzeichnis

- [Einleitung](#einleitung)
  - [Mein Projekt: EchoPlay](#mein-projekt-echoplay)
  - [Ausgangslage](#ausgangslage)
  - [Vision](#vision)
- [Inbetriebnahme](#inbetriebnahme)
  - [Getting started](#getting-started)
  - [Tooling und Hardware](#tooling-und-hardware)
- [Spiele erklärt](#spiele-erklaert)
  - [Allgemein](#allgemein)
  - [Snake](#snake)
  - [Car-Jump](#car-jump)
  - [Arkanoid](#arkanoid)
  - [Uhr](#uhr)
- [Links](#links)
- [Kontakt](#kontakt)

## Einleitung

### Mein Projekt: EchoPlay

EchoPlay ist eine selbstentwickelte Spielkonsole welche aus eine LED-Box von IKEA erstellt wurde. EchoPlay hat ein 16x16 Pixel Screen und wird von einem ESP32 betreiben. Es hat verschieden Spiele wie Snake, Arkanoid, Car-Jump und noch eine Uhr, welche mit einem Controller mit 2 Knöpfen bedient werden können. EchoPlay ist so aufgebaut das es sehr einfach erweiterbar ist.

### Ausgangslage

In der IMS-T wurde uns gesagt das wir ein Projekt durchführen sollen und eins der Vorschläge für ein Projekt war das modifizieren einer IKEA LED-Box. Da eins meiner Hobbys gaming ist habe ich mir gedacht das ich auf dieser LED-Box sicher Spiele zum laufen bringen kann, also habe ich dies als mein Projekt genommen.

### Vision

EchoPlay soll am Schluss eine Spielkonsole mit vielen verschieden Spielen und anderen Programmen sein. Es soll einfach erweiterbar sein, sodass man es viele Spiele auf EchoPlay gespielt werden können. Da es noch ein Mikrofon in der LED-Box hat sollte man diese auch benutzen können um mehr Möglichkeiten für die Spiele zu haben.

## Inbetriebnahme

### Getting started

Um EchoPlay zum starten zu bringen muss man der Box zuerst Strom geben. Hinten auf der Box hat es ein anschluss für ein Stromkabel, dort ein Stromkabel einstecken.

Nachdem Einstecken sollte die LED-Box mit dem Titelscreen eines Spieles aufleuchten, wenn nicht dann muss der Rote Knopf auf der Rückseite gedrückt werden.

Jetzt kann der Spass anfangen, auf der Box sind Klassiker wie Snake und Arkanoid. Um zwischen den Spielen zu wechseln muss man den Gelben Knopf auf der Rückseite drücken.

Für Anleitung für wie die Spiele Funktionieren kann man zur "[Spiele erklärt](#spiele-erklärt)" Sektion gehen.

### Tooling und Hardware

Dar Projekt wurde mit PlaformIO für das ESP32-Framwork entwickelt. Das Programm ist modular aufgebaut und einfach erweiterbar.

EchoPlay benutzt eine modifizierte Version der FREKVENS LED Multi-use Light Box von IKEA. Es wurde der Chip der Originällen Box mit einem ESP32 ersetzt und es wurden noch 2 QwiicKnöpfe verwendet.

## Spiele erklärt

### Allgemein

Spiel sind so aufgebaut das sie einen Start, das eigentliche Spiel und ein Ende haben. Um ein Spiel zu starten muss man irgeneinen Knopf drücken, dann wenn das Spiel fertig ist, also wenn man das Spiel verliert oder gewinnt, kommt man zum ende wo man dann wieder irgendein Knopf drücken muss um wieder von vorne zu beginnen.

### Snake

Snake startet mit einem Titlescreen aufdem gross Snake drauf steht. Nachdem start des Spieles kommt man in ein Menü auf welchem man die Schweirigkeit auswählen kann. Die Schwierigkeit bestimmt wie schnell die Schlange sich bewegt und kann mit dem Drücken der Knöpfe kontrolliert werden. Um die Schweirigkeit auszuwählen und Snake zu starten muss man dann beide Knöpfe gleichzeitig drücken.

Im eigentlichen Spiel ist das Ziel so lange wie möglich zu werden, dies erzielt man indem man die Äpfel, welche auf dem Screen erscheinen, isst. Um die Schlange zu kontrollieren muss man den Linken und den Rechten Knopf drücken. Der Linke Knopf dreht die Schlange nach links und der Rechte Knopf die Schlange nach rechts. Wenn man mit der Wand oder mit sich selbst kollidiert, verliert man.

### Car-Jump

Car-Jump startet mit einer kleinen Animation aufdem ein Man über ein Auto hüpft. Nachdem start, kontrolliert man den kleinen Man welche unten Links steht. Es kommen immerwieder verschiedene Hindernisse auf dich zu und du musst ihnen ausweichen. Das machst du indem du dich mit der Linken Taste hüpfst oder dich mit der rechten Taste duckst. Wenn ein Hinderniss dich berührt, verlierst du. Ziel ist es so lange wie möglich nicht von einem Hinderniss berührt zu werden.

### Arknaoid

Arkanoid started mit einem Titelscreen aufdem Arkanoid steht. Nachdem start kontrolliert man eine Platform unten am Bildschirm, mit dem linken Knopf bewegst du dich nach links und mit dem rechten Knopf nach rechts. Es hat oben eine Einheit von Blöcken und Ziel ist alle diese Blöcke zu zerstören. Die Blöcke können nur durch das kollidieren mit dem Ball zerstört werden und dieser Ball bewegt sich mit konstanter Geschwindigkeit überall herum. Du musst dafür sorgen das der Ball nicht auf den Boden fällt, sonst geht der Ball kaputt und du verlierst. Wenn der Ball auf der Platform aufprallt geht der Ball in die Richtung auf die er abgeprallt ist, also wenn der Ball auf der rechten Seite der Platform abprallt geht der Ball nach rechts, so kann man den Ball gut kontrollieren.

### Uhr

Die Uhr zeigt die Aktuelle Zeit in der Schweiz an. Es hat zwei Modi, eine zeigt die Zeit und die andere das Datum. Man kann mit dem linken und rechten Knopf zwischen diesen wechseln.

## Links

Link zum [Betriebshandbuch](./docs/Betriebshandbuch_260402.md)

Link zur [Techschischen Dokumentation](./docs/Technische-Dokumentation_260402.md)

## Kontakt

[tomnielsen2211@gmail.com](mailto:tomnielsen2211@gmail.com)
