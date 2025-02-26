# Macrolamp

## ✨ Projektbeschreibung
Projekt zur Aufnahme von Iris Augen Fotos. Hierzu werden zwei LED`s mit einem Arduino Nano gesteuert und im Richtigen Moment ein Shutter Auslösebefehl an die angeschlossene Kamera gesendet. 
Die Helligkeit der beiden LED`s kann im Vorfeld eingestellt werden und somit eine vergrößerung der Iris bewirkt werden. Das Zeitintervall, wie lange die LED`s an bleiben ist nur durch eine Anderung des Programmcodes möglich. Die angeschlossenen LED`s sind entweder mit dem Schwarnenhals verbunden oder aber mit dem Aufsatz für das Auge. Die LED`s sind mit Kabeln und entsprechenden Steckern verbunden, so dass eine mühelose verbindung untereinander möglich ist.  

## 🛠 Installation & Einrichtung
### Voraussetzungen
- Vorderer USB geht zur Kamera
- hintere USB geht an die Stromversorgung. Entweder über ein z.B. Handynetzteil, der über eine Powerbank.


## 📝 Features
- einstellen der Helligkeit
- einfacher Wechsel der LED`s
- synchronisation des Kamerashutters mit den LED`s

## 🏆 Ziele
- Aufnahme von Irisfotos durch zeitversetztes aufnehmen von zwei Fotos. Hierdurch wird der Lichtreflex verringert.
- Zusammensetzen beider Fotos später mit Photoshop

## ⚡ Nutzung
Der Kunde Legt seinen Kopf in eine Vorrichtung zum stabilisieren des Kopfes. Anschließend wird das LED Gerät vor das Auge gehalten. Nun kann der Fotograph die LEDs in zwei Stufen einstellen. In der ersten Stufe, welche durch den druck auf den Rotary Encoder ausgeführt wird, wird die vorhelligkeit eingestellt. Bei einem weiteren Druck auf den Knopf, wird die Zielhelligkeit für die Aufnahme des Fotos eingestellt. Anschließend wird durch einen weiteren Druck auf den Encoder das Menü verlassen. Nun wird durch den Druck auf den silberen Knopf der Durchlauf gestartet. 



## 🔄 Nächste Schritte
- Testen der Hard und Software für den Ventilator
- einbinden einer Klappe im Bad, die automatisch geöffnet und geschlossen wird, basierend auf dem Zustand des Ventilators
- implementierung einer Automatischen Bewässerung basierend auf den jeweiligen Bodenfeuchtigkeitswerten
- implementierung für das Einstellen des Schwellenwertes über NodeRed für die Soll Bodenfeuchtigkeit

## 🛠 Aktuelle Probleme
- reflexion des Lichts noch schwach im Foto erkennbar. Lösung --> schwarzen dünnen Stoff oder Papier auf die LEDs kleben
- Gerät schaltet nach einigerzeit an einer Powerbank ab. Liegt aber eher an der Powerbank
- Helligkeitswerte werden aktuell im Code nur temporär, also für jeden Bootvorgang, gespeichert. Dieses kann noch so verändert werden, dass die Werte in den EEPROM geschrieben werden. 
