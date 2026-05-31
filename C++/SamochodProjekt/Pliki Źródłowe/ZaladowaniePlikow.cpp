#include "ZaladowaniePlikow.h"
#include <Windows.h>
#include <string>


bool sprawdz_teksture(sf::Texture& s1, std::string sciezka) {
    return s1.loadFromFile(sciezka);
}

sf::Texture przygotuj_teksture(std::string sciezka) {
    sf::Texture s1;
    if (!sprawdz_teksture(s1, sciezka)) {
        MessageBoxA(NULL, "Nie uda³o siê wczytaæ pliku tekstury", "B³¹d", MB_ICONERROR | MB_OK);
        return s1;
    }
    s1.loadFromFile(sciezka);
    return s1;
}

bool sprawdz_zdjecie(sf::Image& s1, std::string sciezka) {
    return s1.loadFromFile(sciezka);
}

sf::Image przygotuj_zdjecie(std::string sciezka) {
    sf::Image s1;
    if (!sprawdz_zdjecie(s1, sciezka)) {
        MessageBoxA(NULL, "Nie uda³o siê wczytaæ pliku zdjecia!", "B³¹d", MB_ICONERROR | MB_OK);
        return s1;
    }
    s1.loadFromFile(sciezka);
    return s1;
}

bool sprawdz_Samochody(sf::Texture& s1, sf::Texture& s2) {
    return s1.loadFromFile("assets/samochod.png")
        && s2.loadFromFile("assets/samochod_odwrocony.png");
}

void przygotuj_Samochody(sf::Texture& s1, sf::Texture& s2) {
    if (!sprawdz_Samochody(s1, s2)) {
        MessageBoxA(NULL, "Nie uda³o siê wczytaæ zdjêcia samochodu!", "B³¹d", MB_ICONERROR | MB_OK);
    }
}

bool sprawdz_dzwiek(sf::SoundBuffer& buffor,const std::string& sciezka) {
    return buffor.loadFromFile(sciezka);
}

sf::Sound przygotuj_dzwiek(sf::SoundBuffer& buffor,const std::string& sciezka) {
    if (!sprawdz_dzwiek(buffor,sciezka)) {
        MessageBoxA(NULL, "Nie uda³o siê wczytaæ pliku dŸwiêku!", "B³¹d", MB_ICONERROR | MB_OK);
    }
    sf::Sound s1(buffor);

    return s1;  
}