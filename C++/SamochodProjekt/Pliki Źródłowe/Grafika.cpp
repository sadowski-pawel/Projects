#include "Grafika.h"
#include "Pole_tekstowe.h"
#include "Konfiguracja.h"

sf::Text Przygotuj_Tekst() {
    sf::Text p(getFont(), "", 20);
    return p;
}

sf::Text stworzTekst(const std::wstring& tresc, unsigned int rozmiar,
    sf::Vector2f pozycja, sf::Color kolor) {
    sf::Text tekst = Przygotuj_Tekst();
    tekst.setFont(getFont());
    tekst.setString(tresc);
    tekst.setCharacterSize(rozmiar);
    tekst.setPosition(pozycja);
    tekst.setFillColor(kolor);
    return tekst;
}

sf::Sprite przygotujSprite(const sf::Texture& s, float poczatekX, float poczatekY) {
    sf::Sprite sp(s);
    sp.setPosition({ poczatekX,  poczatekY });
    return sp;
}

sf::RectangleShape przygotujDrogi() {
    sf::RectangleShape DrogaShape(sf::Vector2f(820.f, 80.f));
    DrogaShape.setFillColor(sf::Color::Black);
    DrogaShape.setPosition({ 0.f, startYDroga });

    return DrogaShape;
}

std::vector<sf::RectangleShape> przygotujPas() {
    std::vector<sf::RectangleShape> pasy;
    for (int i = 0; i < 10; ++i) {
        sf::RectangleShape pasek(sf::Vector2f(40.f, 5.f));
        pasek.setFillColor(sf::Color::White);
        pasek.setPosition({ i * (40.f + 40.f) + 10.f, startYDroga + 37.5f });
        pasy.push_back(pasek);
    }
    return pasy;
}

void tworzenie_etykiet(sf::Text& label1, sf::Text& label2, sf::Text& label3,
    sf::Text& label4, sf::Text& label5, sf::Text& label6) {


    label1.setString(L"Podaj masê samochodu (kg) [1000]:");
    label2.setString(L"Podaj maks. si³ê napêdow¹ (N) [15000]:");
    label3.setString(L"Podaj µ drogi [0.5]:");
    label4.setString(L"Podaj prêdkoœæ pocz¹tkow¹ (m/s) [0]:");
    label5.setString(L"Podaj gêstoœæ powietrza (kg/m3) [1.225]:");
    label6.setString(L"Podaj µ opon [0.8]:");


    label1.setPosition({ 50.f, 90.f });
    label2.setPosition({ 50.f, 170.f });
    label3.setPosition({ 50.f, 250.f });
    label4.setPosition({ 50.f, 330.f });
    label5.setPosition({ 50.f, 410.f });
    label6.setPosition({ 50.f, 490.f });
}

 void tworzenie_elementow_p(sf::Text& informacja, sf::RectangleShape& zakladkaParametry,
    sf::Text& tekstParametry, sf::RectangleShape& zakladkaHelp, sf::Text& tekstHelp) {
    // Tworzenie tekstu
    informacja.setCharacterSize(20);
    informacja.setFillColor(sf::Color::White);
    informacja.setPosition({ 200, 0 });

    //Zak³adki
    zakladkaParametry.setSize({ 150.f,30.f });

    zakladkaParametry.setPosition({ 10.f, 10.f });
    zakladkaParametry.setFillColor(sf::Color::Blue);

    tekstParametry.setString("Parametry");
    tekstParametry.setPosition({ 15.f, 15.f });

    zakladkaHelp.setSize({ 150.f,30.f });
    zakladkaHelp.setPosition({ 170.f, 10.f });
    zakladkaHelp.setFillColor(sf::Color::Blue);

    tekstHelp.setString("Help");
    tekstHelp.setPosition({ 175.f, 15.f });
}