//Autor: Pawe³ Sadowski

#include <SFML/Graphics.hpp>
#include "interfejs_symulacji.h"

// Funkcja g³ówna programu
// Uruchamia symulacjê w pêtli, dopóki u¿ytkownik chce j¹ restartowaæ
int WinMain() {
    while (restart){ 
        sf::RenderWindow Parametry(sf::VideoMode({ 800, 600 }), L"Wczytywanie parametrów", sf::Style::Titlebar | sf::Style::Close);
        Parametry.setFramerateLimit(60);

        // Funkcja do pobierania parametrów od u¿ytkownika i przygotowania symulacji
        przygotujSymulacjeOdUzytkownika(Parametry);
    }
	return 0;
}