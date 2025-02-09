#pragma once
#include <string>
#include <iostream>
#include "Eigenschaften.hpp"

class Spielkarte 
{
    
private:

    std::string symbol;
    std::string farbe;
    int augen;

public:

    //Konstruktor
    Spielkarte (std::string s,std::string f, int a)
                : symbol(s), farbe(f), augen(a) {};

    //Deklarierung einer toString Funktion (kopiert aus ChatGPT)
    std::string toString() const {
        return symbol + " von " + farbe + " (Augen: " + std::to_string(augen) + ")";                                            // Funktion die einen String mit allen Eigenschaften eines Objekts in der Klasse ausgibt (mit ausgeben meine ich immer: in der Konsole ausgibt)
    }

    void clearScreen() {                                                                                                        // Die Anfänge eines Versuches, das Spiel grafisch ansprechender zu machen
    std::cout << "\033[2J\033[H";
    }

    std::string getFarbe() const {                                                                                              // Getter Funktionen geben einzelne Eigenschaften wie Farbe, Symbol und Augen zurück
        return farbe;
    }
    
    std::string getSymbol() const {
        return symbol;
    }

    int getAugen() const {
        return augen;

    }

    static std::vector<Spielkarte> karten_generieren()                                                                              //Eine Funktion definieren die alle Karten eines Skatblatts generiert
    {   
        int symbol_i = 0;                                                                                                       // Deklariert zähler für die Symbol Vektor, den Augenwerte Vektor und den Prioritäts Vektor
        int farbe_i = 0;                                                                                                        // Deklariert Zähler für den Farbe Vektor
        std::vector <Spielkarte> kartenstapel;


        for (symbol_i = 0; symbol_i < symbole.size(); symbol_i++)
        {   
            for (farbe_i = 0; farbe_i < farben.size(); farbe_i++)
            {
                kartenstapel.emplace_back(symbole[symbol_i], farben[farbe_i], augenwerte[symbol_i]);
            };

       }
            
        return kartenstapel;
    }
};