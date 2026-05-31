#pragma once
#include <SFML/Graphics.hpp>


sf::Text Przygotuj_Tekst();

sf::Text stworzTekst(const std::wstring& tresc, unsigned int rozmiar,
    sf::Vector2f pozycja, sf::Color kolor = sf::Color::Blue);


sf::Sprite przygotujSprite(const sf::Texture& s, float poczatekX, float poczatekY);


void tworzenie_etykiet(sf::Text& label1, sf::Text& label2, sf::Text& label3,
    sf::Text& label4, sf::Text& label5, sf::Text& label6);

void tworzenie_elementow_p(sf::Text& informacja, sf::RectangleShape& zakladkaParametry,
    sf::Text& tekstParametry, sf::RectangleShape& zakladkaHelp, sf::Text& tekstHelp);