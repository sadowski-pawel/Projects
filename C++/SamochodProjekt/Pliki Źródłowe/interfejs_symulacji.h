#pragma once
#include <vector>
#include "Samochod.h"
#include "Konfiguracja.h"
#include <string>

int przygotujSymulacjeOdUzytkownika(sf::RenderWindow& Parametry);

void symulacja(
    sf::RenderWindow& window, Samochod& samochod, ParametryFizyczne& fizyka,
    sf::Sprite& samochodSprite, sf::Sprite& drzewo,sf::Sprite& trawaS, sf::Texture& samochodTexture, sf::Texture& samochodTextureOdwrocony,
    sf::Sprite& droga,sf::Sprite& dol,bool& restart, std::vector<Punkt>& wykresDanych,sf::Sprite& siatka,sf::Sound& dzwiek
);
void PrzygotowaniedoSymulacji(sf::RenderWindow& Okno_Symulacji, float& masa, float& Sila, float& uDrogi, float& oV, float& rho, float& uopon);



