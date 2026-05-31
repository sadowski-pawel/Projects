#include "Konfiguracja.h"

const float startYDroga = 275.f;
const float startYSamochod = 0.f;
bool hamulec = false;
float gaz = 1.0f;
const float MIN_X = -15.f;
const float MAX_X = 705.f;
float minPredkosc = 0.1f;
bool odbicie = 0;
bool restart = true;
float poprzedniGaz = 0.0f;
unsigned int Rozmiarznaku = 16;
float wykresPrzesuniecieX = 810.f;
sf::SoundBuffer buffor;


sf::Font& getFont(){
	static sf::Font font;
	static bool loaded = font.openFromFile("assets/Arial.ttf");
	return font;
}

Zakladka aktywnaZakladka = Zakladka::ParametryZ;