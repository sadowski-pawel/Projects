#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Grafika.h"

class Pole_tekstowe {
private:
    sf::RectangleShape box;
    sf::Text text;  //Tekst wpisywania przez u¿ytkownika
    bool czy_aktywne = false;
    std::size_t wielkosc = 10; //Maksymalna liczba znaków

public:
    //Konstruktor
    Pole_tekstowe(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, unsigned int charSize = 20) : text(font, " ", charSize){

        //Pole tekstwoe --- obramowanie
        box.setPosition(position);
        box.setSize(size);
        box.setFillColor(sf::Color(30, 30, 30));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::White);

        //Tekst w polu teksowym
        text = stworzTekst(L"", charSize, sf::Vector2f(position) + sf::Vector2f(5.f, 5.f), sf::Color::White);
    }
    // Aktywuje lub dezaktywuje pole
    // Aktywne pole ma ¿ó³te obramowanie
    void setActive(bool aktywna) {
        czy_aktywne = aktywna;
        box.setOutlineColor(aktywna ? sf::Color::Yellow : sf::Color::White);
    }
    // Zwraca, czy pole jest aktywne
    bool getActive() const { return czy_aktywne; }

    //Obs³uga Zdarzeñ
    void handleEvent(const sf::Event& event) {
        if (!czy_aktywne) return;

        if (auto textEntered = event.getIf<sf::Event::TextEntered>(); textEntered) {
            char entered = static_cast<char>(textEntered->unicode);
            //Usuwanie znaku
            if (entered == '\b') {
                // backspace
                auto& s = text.getString();
                if (!s.isEmpty()) {
                    text.setString(s.substring(0, s.getSize() - 1));
                }
            }
            //Pomijanie nowej lini i enter
            else if (entered == '\r' || entered == '\n') {
            }
            // Dodawanie cyfr i jednej przecinka (do liczb zmiennoprzecinkowych)
            else if (auto s = text.getString();
                s.getSize() < wielkosc &&
                (std::isdigit(entered) ||
                    (entered == ',' && s.find(L',') == sf::String::InvalidPos))){
                // dopisujemy cyfrê lub (gdy jeszcze nie ma) jedn¹ kropkê
                text.setString(s + entered);
            }
        }
    }
    //Rysowanie obramowania i tekstu
    void draw(sf::RenderTarget& target) const {
        target.draw(box);  
        target.draw(text);
    }
    //Wcyztanie tekstu z pola tekstowego jako string
    std::string getS() const {
        std::string textSTR = text.getString().toAnsiString(); 
        return textSTR;
    }
};
