#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// ——————— Zmienne Globalne ———————
extern const float startYDroga;
extern const float startYSamochod;
extern bool hamulec;
extern float gaz;
extern const float MIN_X;
extern const float MAX_X;
extern float minPredkosc;
extern bool odbicie;
extern bool restart;
extern float poprzedniGaz;
extern float wykresPrzesuniecieX;
extern unsigned int Rozmiarznaku;
extern sf::SoundBuffer buffor;



// ——————— Struktura Parametrów fizycznych ———————
struct ParametryFizyczne {
    float gestoscPowietrza = 1.225f;   // kg/m? (przy poziomie morza, 15 °C)

    float wspolczynnikTarciaDrogi = 0.6f;     // np. asfalt suchy
    float wspTarciaOpon = 1.0f;     // dobre opony
    float przyspieszenieGrawitacyjne = 9.81f;  // m/s?

    ParametryFizyczne(float wsp, float rho) : wspolczynnikTarciaDrogi(wsp), gestoscPowietrza(rho) {};
};

// ———————  Struktura Punktu na wykresie prêdkoœci wzglêdem czasu ———————
struct Punkt {
    float t;   // czas
    float v;   // prêdkoœæ
};

sf::Font& getFont();


enum class Zakladka {
    ParametryZ,
    Help,
};

extern Zakladka aktywnaZakladka;
