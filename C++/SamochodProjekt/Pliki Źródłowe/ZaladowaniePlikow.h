#pragma once
#include "Konfiguracja.h"
#include <string>

bool sprawdz_teksture(sf::Texture& s1, std::string sciezka);

sf::Texture przygotuj_teksture(std::string sciezka);

bool sprawdz_zdjecie(sf::Image& s1, std::string sciezka);

sf::Image przygotuj_zdjecie(std::string sciezka);

bool sprawdz_Samochody(sf::Texture& s1, sf::Texture& s2);

void przygotuj_Samochody(sf::Texture& s1, sf::Texture& s2);

bool sprawdz_dzwiek(sf::SoundBuffer& buffor, const std::string& sciezka);
sf::Sound przygotuj_dzwiek(sf::SoundBuffer& buffor,const std::string& sciezka);