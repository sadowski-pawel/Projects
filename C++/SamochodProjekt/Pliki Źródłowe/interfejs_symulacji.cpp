#include "interfejs_symulacji.h"
#include "Grafika.h"
#include "ZaladowaniePlikow.h"
#include "Pole_tekstowe.h"

using namespace std;

//Funkcje dodatkowe do przygotujSymulacjeOdUzytkownika

//Tworzenie Pól tekstowych - do odczytania parametrów
static std::vector<Pole_tekstowe> stworzPole_tekstowe() {
    Pole_tekstowe tbMasa = Pole_tekstowe({ 500.f,  80.f }, { 200.f, 30.f }, getFont());
    Pole_tekstowe tbSila = Pole_tekstowe({ 500.f, 160.f }, { 200.f, 30.f }, getFont());
    Pole_tekstowe tbuDrogi = Pole_tekstowe({ 500.f, 240.f }, { 200.f, 30.f }, getFont());
    Pole_tekstowe tboV = Pole_tekstowe({ 500.f, 320.f }, { 200.f, 30.f }, getFont());
    Pole_tekstowe tbrho = Pole_tekstowe({ 500.f, 400.f }, { 200.f, 30.f }, getFont());
    Pole_tekstowe tbuopon = Pole_tekstowe({ 500.f, 480.f }, { 200.f, 30.f }, getFont());

    std::vector<Pole_tekstowe> boxes = { tbMasa, tbSila, tbuDrogi, tboV, tbrho, tbuopon };

    return boxes;
}

static bool obsluga_zdarzen(sf::RenderWindow& window, std::vector<Pole_tekstowe>& boxes,
    std::size_t& aktywny_index, bool& enterPressed,
    const sf::RectangleShape& zakladkaParametry,
    const sf::RectangleShape& zakladkaHelp) {
    while (auto e = window.pollEvent()) {
        //Zakoñæzenie Programu
        if (e->is<sf::Event::Closed>()) {
            window.close();
            restart = false;
            return false;
        }
        //Zakoñczenie Programu
        if (auto keyEv = e->getIf<sf::Event::KeyPressed>()) {
            if (keyEv->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
                restart = false;
                return false;
            }
            //Wybieranie obramowania ktróego chcemy aby tekst zosta³ wpisany
            if (keyEv->scancode == sf::Keyboard::Scancode::Tab) { 
                boxes[aktywny_index].setActive(false);
                aktywny_index = (aktywny_index + 1) % boxes.size();
                boxes[aktywny_index].setActive(true);
            }
            //Wczytywanie Parametru
            if (keyEv->scancode == sf::Keyboard::Scancode::Enter) {
                enterPressed = true;
            }
        }

        for (auto& tb : boxes)
            tb.handleEvent(*e);

        if (auto mouse = e->getIf<sf::Event::MouseButtonPressed>();
            mouse && mouse->button == sf::Mouse::Button::Left) {
            sf::Vector2f klik(mouse->position);
            if (zakladkaParametry.getGlobalBounds().contains(klik)) { //Wyœwietlenie Formularza do odczytu parametrów
                aktywnaZakladka = Zakladka::ParametryZ;
            }
            else if (zakladkaHelp.getGlobalBounds().contains(klik)) { //Wyœwietlenie pomocy dla u¿ytkownika
                aktywnaZakladka = Zakladka::Help;
            }
        }
    }
    return true;
}

//Rysowanie wczytywanie parametru
static void rysuj_parametry(sf::RenderWindow& Parametry, sf::Text& informacja, sf::Text& label1,
    sf::Text& label2, sf::Text& label3, sf::Text& label4, sf::Text& label5, sf::Text& label6, Pole_tekstowe& tbMasa,
    Pole_tekstowe& tbSila, Pole_tekstowe& tbuDrogi, Pole_tekstowe& tboV, Pole_tekstowe& tbrho, Pole_tekstowe& tbuopon) {
    Parametry.draw(informacja);
    Parametry.draw(label1);
    Parametry.draw(label2);
    Parametry.draw(label3);
    Parametry.draw(label4);
    Parametry.draw(label5);
    Parametry.draw(label6);

    tbMasa.draw(Parametry);
    tbSila.draw(Parametry);
    tbuDrogi.draw(Parametry);
    tboV.draw(Parametry);
    tbrho.draw(Parametry);
    tbuopon.draw(Parametry);
}

static void rysuj_help(sf::RenderWindow& Parametry) {
    sf::Text tekstPomoc = stworzTekst(L"Autor: Pawe³ Sadowski\n"
        L"Instrukcja:\n"
        L"Jeœli u¿ytkownik wpisze b³êdne dane dla takich parametrów: \n  - wspó³czynnik tarcia drogi, \n - wspó³czynnik tarcia \n - opon prêdkoœæ pocz¹tkow¹, \n  - masê, \n - si³ê napêdow¹, \n "
        L"S¹ mniejsze od 0 lub nie s¹ liczbami. (dla wszystkich) \n Symulacja wczyta domyœlne wartoœci z nawiasów kwadratowych []. \n\n"
        L"Sterowanie:\n"
        L"1. TAB - Wybieranie parametru \n"
        L"2. ENTER - Symulacja wczytuje dane z pola tekstowego\n"
        L"2. Hamulec - Spacja\n"
        L"3. Gaz - Strza³ka w górê (zwiêkszenie), Strza³ka w dó³ (zmniejszenie)\n"
        L"4. Num 0 - Wczytanie nowych danych\n"
        L"5. ESC - Zamkniêcie symulacji", 20, { 40.f,70.f }, sf::Color::White);

    Parametry.draw(tekstPomoc);
}

//Walidacja do danych + dodanie domyœlnej wartoœci 
static  float WczytajDaneodUzytkownika(const std::string& line, float DomyslneWartosci, bool mozebyc0 = false) {
    if (!line.empty()) {
        try {
            float wartosc = std::stof(line);
            if (wartosc > 0.f || mozebyc0) 
                //Dane musz¹ byæ wy¿sze od 0 w przypadku prêdkoœci pocz¹tkowej , gêstoœci powietrza mo¿e wynieœæ 0
                return wartosc;

        }
        catch (...) {
        }
    }
    return DomyslneWartosci; //Gdy u¿ytkownik poda niepoprawn¹ wartoœæ program wpisze domyœln¹ wartoœæ
}

//Funckja otwieraj¹ okno do wczytywania parametrów   -- przygotujSymulacjeOdUzytkownika --

static void rysuj_do_odczytywania(sf::RenderWindow& Parametry,sf::RectangleShape& zakladkaParametry, sf::RectangleShape& zakladkaHelp,sf::Text& tekstParametry, sf::Text& tekstHelp) {
    Parametry.clear(sf::Color::Black); //T³o czarne do odczytywania parametrów
    Parametry.draw(zakladkaParametry);
    Parametry.draw(tekstParametry);
    Parametry.draw(zakladkaHelp);
    Parametry.draw(tekstHelp);
}


int przygotujSymulacjeOdUzytkownika(sf::RenderWindow& Parametry) {
    sf::Image ikona = przygotuj_zdjecie("assets/Ikona_1.png");
    Parametry.setIcon(ikona);

    //Zak³adka
    sf::Text informacja = Przygotuj_Tekst();
    sf::RectangleShape zakladkaParametry;
    sf::Text tekstParametry = Przygotuj_Tekst();

    sf::RectangleShape zakladkaHelp;
    sf::Text tekstHelp = Przygotuj_Tekst();
    tworzenie_elementow_p(informacja, zakladkaParametry, tekstParametry, zakladkaHelp, tekstHelp);

    //Etykiety
    sf::Text label1 = Przygotuj_Tekst(), label2 = Przygotuj_Tekst(), label3 = Przygotuj_Tekst(), label4 = Przygotuj_Tekst(), label5 = Przygotuj_Tekst(), label6 = Przygotuj_Tekst();
    tworzenie_etykiet(label1, label2, label3, label4, label5, label6);

    // Pole_tekstowey
    std::vector<Pole_tekstowe> boxes = stworzPole_tekstowe();

    std::size_t aktywny_index = 0;
    boxes[aktywny_index].setActive(true);

    bool enterPressed = false;
    while (Parametry.isOpen() && !enterPressed) {

        if (!obsluga_zdarzen(Parametry, boxes, aktywny_index, enterPressed, zakladkaParametry, zakladkaHelp)) { return 0; };

        rysuj_do_odczytywania(Parametry,zakladkaParametry,zakladkaHelp,tekstParametry,tekstHelp); //Rysowanie zak³adek i tekstu

        if (aktywnaZakladka == Zakladka::ParametryZ) {
            rysuj_parametry(Parametry, informacja, label1, label2, label3, label4, label5, label6, boxes[0], boxes[1],boxes[2]
                , boxes[3], boxes[4], boxes[5]);
        }
        else if (aktywnaZakladka == Zakladka::Help) {
            rysuj_help(Parametry);
        }
        Parametry.display();

    }

    // Po Enter mamy ju¿ tekst i nastêpnie z tego tekstu wcyi¹gamy dane
    std::string masaStr = boxes[0].getS();
    float masa = WczytajDaneodUzytkownika(masaStr, 1000.f, false);

    std::string SilaStr = boxes[1].getS();
    float Sila = WczytajDaneodUzytkownika(SilaStr, 15000.f, false);

    std::string uDrogiStr = boxes[2].getS();
    float uDrogi = WczytajDaneodUzytkownika(uDrogiStr, 0.5f, false);

    std::string tboVStr = boxes[3].getS();
    float oV = WczytajDaneodUzytkownika(tboVStr, 0.f, true);

    std::string rhoStr = boxes[4].getS();
    float rho = WczytajDaneodUzytkownika(rhoStr, 1.255f, true);

    std::string uoponStr = boxes[5].getS();
    float uopon = WczytajDaneodUzytkownika(uoponStr, 0.8f, false);

    boxes.clear();
    Parametry.close();

    sf::RenderWindow Okno_Symulacji(sf::VideoMode({ 1600, 600 }), L"Symulacja Pojazdu", sf::Style::Titlebar | sf::Style::Close);
    Okno_Symulacji.setFramerateLimit(60);

    ikona = przygotuj_zdjecie("assets/Ikona_2.png");
    Okno_Symulacji.setIcon(ikona);

    PrzygotowaniedoSymulacji(Okno_Symulacji, masa, Sila, uDrogi, oV, rho, uopon);
    return 0;
}

//Funckja przygotowuj¹ca okno do  symulacji   -- PrzygotowaniedoSymulacji --

void PrzygotowaniedoSymulacji(sf::RenderWindow& Okno_Symulacji, float& masa, float& Sila, float& uDrogi, float& oV, float& rho, float& uopon) {
    Samochod samochod(masa, Sila, oV, uopon);
    ParametryFizyczne fizyka{ uDrogi,rho };

    sf::Texture samochodTexture;
    sf::Texture samochodTextureOdwrocony;

    przygotuj_Samochody(samochodTexture, samochodTextureOdwrocony);

    sf::Sprite samochodSprite = przygotujSprite(samochodTexture, 0, startYSamochod);

    sf::Texture drzewotexture = przygotuj_teksture("assets/Drzewo.png");

    sf::Sprite drzewo = przygotujSprite(drzewotexture, 0, startYSamochod + 80);

    sf::Texture trawa = przygotuj_teksture("assets/Trawa.png");

    sf::Sprite trawaS = przygotujSprite(trawa, 0, 0);

    sf::Texture drogatexture = przygotuj_teksture("assets/Droga.png");
    sf::Sprite droga = przygotujSprite(drogatexture, 0, startYDroga);

    sf::Texture tekstury_dolne = przygotuj_teksture("assets/tlo_dolne.png");
    sf::Sprite dolPprogramu = przygotujSprite(tekstury_dolne, 40, 300);


    std::vector<Punkt> wykresDanych; 

    sf::Texture siatka = przygotuj_teksture("assets/Siatka.png");

    sf::Sprite s = przygotujSprite(siatka, 800, 0);

    sf::Sound dzwiek = przygotuj_dzwiek(buffor, "assets/Dzwiek.mp3");


    

    dzwiek.setVolume(30);


    symulacja(
        Okno_Symulacji, samochod, fizyka,
        samochodSprite, drzewo, trawaS, samochodTexture, samochodTextureOdwrocony,droga,dolPprogramu,restart, wykresDanych, s, dzwiek
    );
}

//Funkcje dodatkowe do symulacji

static bool obsluga_zdarzen(sf::RenderWindow& window) {
    while (auto ev = window.pollEvent()) {
        //Zamkniêcie programu
        if (ev->is<sf::Event::Closed>()) {
            window.close();
            restart = false;
            return false;
        }
        //Zamkniêcie programu
        if (auto key = ev->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
                restart = false;
                return false;
            }
            //Hamulec
            if (key->scancode == sf::Keyboard::Scancode::Space) {
                hamulec = !hamulec;
            }
            //Zwiekszenie Gazu
            if (key->scancode == sf::Keyboard::Scancode::Up) {
                gaz += 0.1f;
                if (gaz > 1.f) gaz = 1.f;
            }
            //Zmniejsze Gazu
            if (key->scancode == sf::Keyboard::Scancode::Down) {
                gaz -= 0.1f;
                if (gaz < 0.f) gaz = 0.f;
            }
            //Reset
            if (key->scancode == sf::Keyboard::Scancode::Num0) {
                restart = true;
                window.close();
            }
        }

    }
    return true;
}

static void sprawdzOdbicie(float& x, Samochod& samochod, sf::Sprite& samochodSprite,
    const sf::Texture& texNormalny, const sf::Texture& texOdwrocony, bool& odbicie){
    if (x < MIN_X) { //odbicie  w prawo jeœli samochód napotka na œciane
        x = MIN_X;
        samochod.setPredkosc(-samochod.getPredkosc());
        samochodSprite.setTexture(texNormalny);
        odbicie = !odbicie;
    }
    else if (x > MAX_X) { //odbicie w lewo
        x = MAX_X;
        samochod.setPredkosc(-samochod.getPredkosc());
        samochodSprite.setTexture(texOdwrocony);
        odbicie = !odbicie;
    }
}
//Rysowanie sceny do Symulacji samochodu
static void rysuj_scene(sf::RenderWindow& window, sf::Sprite& trawaS,
    sf::Sprite& samochodSprite, sf::Sprite& drzewo, sf::Text& speedText,
    sf::Text& hamText, sf::RectangleShape& gazPasek_s, sf::RectangleShape& gazPasek_z, sf::Text& CzasText,
    sf::Text& atext, sf::Text& gazText, sf::Text& sText, sf::Sprite& Droga,sf::Sprite& dol) {
    window.clear(sf::Color::White);
    window.draw(trawaS);
    window.draw(dol);
    window.draw(Droga);
    window.draw(samochodSprite);
    window.draw(drzewo);
    window.draw(speedText);
    window.draw(hamText);
    window.draw(gazPasek_s);
    window.draw(gazPasek_z);
    window.draw(CzasText);
    window.draw(atext);
    window.draw(gazText);
    window.draw(sText);
}

static void rysujWykres(sf::RenderWindow& window,
    const std::vector<Punkt>& dane,
    sf::Sprite& siatka) {
    window.draw(siatka);
    // 1. marginesy i rozmiar okna
    const float margin = 0.f;
    auto [winW, winH] = window.getSize();
    float width = static_cast<float>(winW);
    float height = static_cast<float>(winH - 10.f);

    // 2. zakresy: czas i prêdkoœæ
    float maxTime = dane.empty() ? 1.f : dane.back().t;
    float maxSpeed = 0.f;
    for (auto& p : dane)
        maxSpeed = std::max(maxSpeed, p.v);

    // 3. obszar rysowania i wspó³czynniki skali
    float plotWidth = width - wykresPrzesuniecieX - margin;
    float plotHeight = height;
    float scaleX = plotWidth / maxTime;
    float scaleY = plotHeight / maxSpeed;

    // 4. skalowanie i rysowanie sprite'a siatki
    auto bounds = siatka.getLocalBounds();
    float sx = plotWidth / bounds.size.x;
    float sy = plotHeight / bounds.size.y;
    siatka.setScale({ sx, sy });
    siatka.setPosition({ wykresPrzesuniecieX , margin });

    // 5. rysowanie krzywej V(t)
    sf::VertexArray curve(sf::PrimitiveType::LineStrip, dane.size());
    for (std::size_t i = 0; i < dane.size(); ++i) {
        float x = wykresPrzesuniecieX + dane[i].t * scaleX;
        float y = height - dane[i].v * scaleY;
        curve[i].position = sf::Vector2f(x, y);
        curve[i].color = sf::Color::Red;
    }
    window.draw(curve);

    // 6. rysowanie osi X i Y 
    // Oœ Y 
    sf::RectangleShape axisY(sf::Vector2f(11.f, height));  
    axisY.setPosition({ wykresPrzesuniecieX, margin });
    axisY.setFillColor(sf::Color::Magenta);
    window.draw(axisY);

    // Oœ X 
    sf::RectangleShape axisX(sf::Vector2f(width, 11.f));  
    axisX.setPosition({ wykresPrzesuniecieX, height });
    axisX.setFillColor(sf::Color::Magenta);
    window.draw(axisX);

    // 7. etykieta osi X
    sf::Text labelX = stworzTekst(L"Czas (t) [s]", 20, { width - 120.f, height - 40.f }, sf::Color::White);
    window.draw(labelX);

    // 8. etykieta osi Y
    sf::Text labelY = stworzTekst(L"Prêdkoœæ (V) [m/s]", 20, { 870.f, margin + 300.f }, sf::Color::White);
    labelY.setRotation(sf::degrees(-270.f));  // Obracamy etykietê o 90 stopni
    window.draw(labelY);
}

void symulacja
(sf::RenderWindow& window, Samochod& samochod, ParametryFizyczne& fizyka,
    sf::Sprite& samochodSprite, sf::Sprite& drzewo, sf::Sprite& trawaS, sf::Texture& samochodTexture, sf::Texture& samochodTextureOdwrocony,
    sf::Sprite& droga,sf::Sprite& dol, bool& restart, std::vector<Punkt>& wykresDanych, sf::Sprite& siatka,sf::Sound& dzwiek) {
    
    //Zegar - s³u¿y do mierzenia czasu trwania pojedynczej symulacji
    //Zegar ca³kowity - s³u¿y do mierzenia czasu ca³kowitego czasu trrwania symulacji

    sf::Clock zegar, zegarCalkowity;


    float predkosc = samochod.getPredkosc(); //Wczytywanie prêdkoœci
    float czas = zegarCalkowity.getElapsedTime().asSeconds(); //Wczytywanie czasu trwania symulacji
    float przyspieszenie = samochod.getPredkosc(); //Przyszpieszenie
    float maxSila = samochod.getSilaNapedowa(); //Si³a Napêdu zale¿ny od gazu
    
    dzwiek.setLooping(true);
    dzwiek.play();

    while (window.isOpen()) {

        obsluga_zdarzen(window);
        //Obs³uga Klawisza
        

        samochod.ustawHamowanie(hamulec, fizyka);
        // Aktualizacja ustawienia si³y napêdowej w zale¿noœci od gazu
        if (hamulec) {
            gaz = 0.f; // Gdy w³¹czony jest hamulec, ustawiamy gaz na 0
            samochod.setSilaNapedowa(0); // Zatrzymanie si³y napêdowej
        }
        else {
            // Normalne ustawienie si³y napêdowej w zale¿noœci od gazu
            float kierunek = (samochod.getPredkosc() >= 0.f ? 1.f : -1.f);
            // Si³a napêdowa zale¿na od gazu (przy pe³nym gazie = maxSila)
            samochod.setSilaNapedowa(kierunek * maxSila * gaz);
        }

        // Delta czasu 
        float dt = zegar.restart().asSeconds();

        //Wczytywanie prêdkoœci , czasu
        predkosc = samochod.getPredkosc();
        czas = zegarCalkowity.getElapsedTime().asSeconds();
        samochod.aktualizuj(dt, fizyka);
        
        if (fabs(samochod.getPredkosc()) < minPredkosc) {
            samochod.setPredkosc(0.f);
        }

        //Samochód nie przyszpiesza natychmiast ale stopniowo
        if (fabs(gaz - poprzedniGaz) > 0.01f) {
            samochod.setprzyspieszenie(samochod.getprzyspieszenie() + (gaz - poprzedniGaz) * 5.0f);
        }
        poprzedniGaz = gaz;

        //Pozycja samochodu podczas trwania symulacji
        float x = samochod.getPozycja();

        //Odbijanie samochodu przez sciane
        sprawdzOdbicie(x, samochod, samochodSprite, samochodTexture, samochodTextureOdwrocony, odbicie);

        samochodSprite.setPosition({ x, startYSamochod });


        sf::Text speedText = stworzTekst(L"Predkosc: " + to_wstring(fabs(predkosc)) + L" m/s", 18, { 10.f, 10.f }, sf::Color::Black);
        sf::Text hamText = stworzTekst(hamulec ? L"Hamulec: ON" : L"Hamulec: OFF", 18, { 10.f, 50.f }, sf::Color::Black);

        float s = samochod.drogaHamowania(fizyka);
        sf::Text sText = stworzTekst(L"Droga hamowania: " + to_wstring(s) + L" m", 18, { 250.f, 10.f }, sf::Color::Black);

        przyspieszenie = odbicie ? -samochod.getprzyspieszenie() : samochod.getprzyspieszenie();
        sf::Text atext = stworzTekst(L"Przyspieszenie: " + to_wstring(przyspieszenie) + L" m/s^2", 18, { 250.f, 50.f },sf::Color::Black);

        sf::Text gazText = stworzTekst(L"Gaz: ", 18, { 600.f, 10.f },sf::Color::Black);
        sf::Text CzasText = stworzTekst(L"Czas: " + to_wstring(czas), 18, { 600.f, 50.f }, sf::Color::Black);

        sf::RectangleShape gazPasek_s(sf::Vector2f(100, 10));
        gazPasek_s.setPosition({ 650.f, 20.f });
        gazPasek_s.setFillColor(sf::Color(150, 150, 150));

        sf::RectangleShape gazPasek_z(sf::Vector2f(100 * gaz, 10));
        gazPasek_z.setPosition({ 650.f, 20.f });
        gazPasek_z.setFillColor(sf::Color::Green);

        wykresDanych.push_back({ czas, fabs(predkosc) });

        rysuj_scene(window, trawaS, samochodSprite, drzewo, speedText, hamText, gazPasek_s, gazPasek_z, CzasText, atext, gazText, sText,droga,dol);
        rysujWykres(window, wykresDanych, siatka);

        window.display();
    }
    window.clear();
}





