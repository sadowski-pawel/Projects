#include "Samochod.h"
#include <cmath>



void Samochod::aktualizuj(float dt, const ParametryFizyczne& p) {
    // Ustalenie znaku prêdkoœci (czy porusza siê do przodu, do ty³u)
    float znakV = (predkosc > 0 ? 1 : (predkosc < 0 ? -1 : 0));


    float F_toczenia = -p.wspolczynnikTarciaDrogi * masa * p.przyspieszenieGrawitacyjne * znakV;

    /*
    Obliczanie si³y tarcia tocznego : dzia³a przeciwnie do kierunku ruchu
    zgodnie z wzorem T = N * ?obl

    T: to si³a tarcia tocznego,
    N: to si³a nacisku,
    ?obl: to obliczeniowy wspó³czynnik tarcia tocznego.
    */

    float F_powietrza = -0.5f * p.gestoscPowietrza * predkosc * fabs(predkosc) ;
    /*
    si³ê oporu powietrza  F = 0, 5 * ? * v2  * C_d
    F - si³a oporu powietrza [N]
    ? - gêstoœæ powietrza [kg/m?]
    v - prêdkoœæ obiektu [m/s]
    C_d - wspó³czynnik oporu powietrza
    */

    float Fw = silaNapedowa + silaHamowania + F_toczenia + F_powietrza;
    /*
    wypadkow¹ si³ê dzia³aj¹c¹ na samochód
    */

    przyspieszenie = Fw / masa;
    /*
        Wzór na przyspieszenie zgodny z II zasad¹ dynamiki Newtona
    */
    predkosc += przyspieszenie * dt;

    /*
        wzór z kinematyki prostoliniowej dla ruchu jednostajnie zmiennego
    */

    pozycja += predkosc * dt;
}

void Samochod::ustawHamowanie(bool aktywne, ParametryFizyczne& f) {
    if (aktywne) {
        // Znak przeciwny do kierunku prêdkoœci (hamowanie)
        float znakV = (predkosc > 0 ? -1.f : 1.f);

        // Maksymalna si³a hamowania wynikaj¹ca z tarcia opon
        float maxF = wspTarciaOpon * masa * f.przyspieszenieGrawitacyjne;

        /* 
         Si³a hamowania jest proporcjonalna do prêdkoœci, ale nie mo¿e byæ mniejsza ni¿ 0.1f, 
         aby unikn¹æ braku reakcji przy bardzo niskich prêdkoœciach.
        */
        float sila = (fabs(predkosc) / 100.f > 0.1f) ? fabs(predkosc) / 100.f : 0.1f;
        silaHamowania = znakV * maxF * sila;

        // 
    }
    else {
        silaHamowania = 0;
    }
}

float Samochod::drogaHamowania(ParametryFizyczne& f) const {
    float v = fabs(predkosc);
    if (v < 0.01f) return 0;
    return v * v / (2 * wspTarciaOpon * f.przyspieszenieGrawitacyjne); // Wzór na drogê hamowania
}

// Settery
void Samochod::setSilaNapedowa(float s) { silaNapedowa = s; }
void Samochod::setPredkosc(float v) { predkosc = v; }
void Samochod::setMasa(float m) { masa = m; }
void Samochod::setWspTarciaOpon(float mu) { wspTarciaOpon = mu; }
void Samochod::setprzyspieszenie(float a) { przyspieszenie = a; }

// Gettery
float Samochod::getPozycja()  const { return pozycja; }
float Samochod::getPredkosc()  const { return predkosc; }
float Samochod::getHamowanie()  const  { return silaHamowania; }
float Samochod::getWspTarciaOpon()  const  { return wspTarciaOpon; }
float Samochod::getprzyspieszenie()  const  { return przyspieszenie; }
float Samochod::getSilaNapedowa() const { return silaNapedowa; }