"# ELClient-WordClock" 
Init
	Prüfen der Internetverbindung
	Zeitabfrage -> Berechnung der Zeit bis 5 min
	
Loop
	Extramodus? (weil Datum...)
	Anzeige
	Transition
	
Anzeigemodi
	Normal, Farbe
		Maske für aktuelle Zeit berechnen
	Animation entsprechend RGB Nodes
		Maske für aktuelle Zeit mit RGB Wert
	Jedes Wort eine Farbe
	NeoMatrix Animation
		Beispielanimationen mit Maske überlagern
	Matrix-Movie 
		Aktuelles in voller Helligkeit
		Von jedem dieser Punkte zufällig einen fallenden Buchstaben animieren
			Halbe helligkeit dadrunter
			0.5*0.5 Helligkeit im 2. Step, dafür der dadruinter in 0.75*0.5 der original Helligkeit
			
Transitionen
	Normal
	Fade
		Maske1 speichern und herunterfaden + Maske2 herauffadend
	Farbwechsel
		Farbe1 und Farbe2
	Heraus-/Herinfahrend von (links rechts oben unten)
		Shift von Maske1
		Shift von Maske2
	Matrix
		Buchstaben fallen von oben und bleiben da stehen wo sie hin sollen.
		Random start, falls in dieser Spalte noch ein Buchstabe muss weniger stark dämpfen als im Matrix anzeige modus, sonst genau so
	Ausblenden/Anzeigen von (links rechts oben unten)
		erst erste Zeile/Spalte anzeigen dann nächste
	Bunt gewürfelte Farben bis sich das Bild aufklärt/sortiert
		Random gefüllt mit 6 Farben, exakt so viele in der Hauptfarbe, wie später benötigt werden. Jetzt einzelne Pixel vertauschen bis sortiert ist. evtl bubble sort?
			tauschende Paare aufblitzen lassen
				in Mischfarbe
				weitest entfernte Farbe
			tauschende Paare überblenden
	Snake
		Pixel in gegenteiliger oder fester Farbe fährt über die Matrix und frisst die existierenden Buchstaben
			start unten links?
			fahre Zeilen ab, bis Spalte besetzt
			fahre Zeile ab und fress fahre auf nächste Zeile
		Kette von (n buchstaben) fährt über die matrix und kackt dorthin wo buchstaben hin müssen
	Explosion
		Füllen von Mitte und löschen von Mitte
	Implosion
	Epidemie
		Flächenfüllend alle Nachbarfelder färben
		fadend oder direkt
	Füllen von (links rechts oben unten)
		Komplett füllen und dann von gleicher Seite das löschen was nicht da sein muss
	Fallend/Springend
		beschleunigt oder linear
		überspringend/losspringend oder direkt
		Wort für Wort oder Buchstaben random

Extras
	ILU am ersten Mai-Wochenende
	Herz
	Weihnachtsbaum
	Ostereier
	Geburtstag
	Winter hintergrund
	Temperatur/Wetter	
	
Einstellungen
	Helligkeit
		Adaptiv?
		Auszeiten?
		Profile speichern laden
	Bewegungserkennung?
	Darstellungsdauer des Extras, wdh? je Stunde/je 5 min
	Modus	
		Modi Buttons
		Modi Liste
			Shuffle
		Farbreihenfolge
		Presets speichern laden	
