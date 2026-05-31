#pragma once
#include "konfiguracja.h"

class Samochod {
private:
    float pozycja = 0.f;
    float predkosc = 0.f;
    float masa = 1000;
    float silaNapedowa = 0.f;
    float silaHamowania = 0.f;
    float wspTarciaOpon = 0.8f; // domyœlnie
    float przyspieszenie = 0.f;
public:
    //Konstruktor
    Samochod(float m,float silaN ,float v0, float muOpon)
        : masa(m),silaNapedowa(silaN), predkosc(v0), wspTarciaOpon(muOpon) {
    };


    //Metody
    void aktualizuj(float dt, const ParametryFizyczne& p);
    void ustawHamowanie(bool aktywne, ParametryFizyczne& f);
    float drogaHamowania(ParametryFizyczne& f) const;

    // Settery
    void setSilaNapedowa(float s);
    void setPredkosc(float v);
    void setMasa(float m);
    void setWspTarciaOpon(float mu);
    void setprzyspieszenie(float a);

    //Gettery
    float getPozycja() const;
    float getPredkosc() const;
    float getHamowanie() const;
    float getWspTarciaOpon() const;
    float getprzyspieszenie() const;
    float getSilaNapedowa() const;
};
