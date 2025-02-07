#include <iostream> 
#include <algorithm> // std :: shuffle
#include <array> // std :: array
#include <random> // std :: default_random_engine
#include <chrono> // std :: chrono :: system_clock
#include <vector>

using std::endl;
using namespace std;

//Line zum Kompilen fürs Terminal "g++ -std=c++23 -Wall ./SKAT.cpp -o ./skat  && ./skat"

// Die Deklarierung und Definition von drei Arrays : Die 8 "Symbole", die 4 Farben, die 8 möglichen Augenzahlen
std::vector<std::string>symbole_französisch = {"Sieben" , "Acht" , "Neun" , "Bube" , "Dame" , "König" , "Zehn" , "Ass"};
std::vector<std::string>symbole = {"Sieben" , "Acht" , "Neun" , "Unter" , "Ober" , "König" , "Zehn" , "Ass"};
std::vector<std::string>farben_französisch = {"Karo" , "Herz" , "Pik" , "Kreuz"};
std::vector<std::string>farben = {"Eicheln","Grün","Rot", "Schellen"};

std::vector<int>augenwerte = {0,0,0,2,3,4,10,11};  

enum Test {
  HALLO, WELT
};
Test enumeration = Test::WELT;

// void sprache_waehlen(){
//    int sprachwahl;
//    std::cout << "Wählen sie Ihr Blatt" << endl;
//    std::cout << "1 Deutsch" << endl;
//    std::cout << "2 Französisch" << endl;
//    std::cin >> sprachwahl;
//    if (sprachwahl == 1) {
//        std::vector symbole = symbole_deutsch;
//        std::vector farben = farben_deutsch;
//        std::cout << "Sie spielen mit deutschem Blatt:" << endl;
//    } 
//    else
//        std::vector symbole = symbole_französisch;
//        std::vector farben = farben_französisch;
//        std::cout << "Sie spielen mit französischem Blatt:" << endl;
//}

//Die Klasse Spielkarte wird definiert
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
        return symbol + " von " + farbe + " (Augen: " + std::to_string(augen) + ")";
    }

    void clearScreen() {
    std::cout << "\033[2J\033[H";
    }

    std::string getFarbe() {
        return farbe;
    }
    
    std::string getSymbol() {
        return symbol;
    }

    int getAugen() {
        return augen;
    }


    //Eine Funktion definieren die alle Karten eines Skatblatts generiert
static std::vector<Spielkarte> karten_generieren()
    {   
        int symbol_i = 0; // Deklariert zähler für die Symbol Vektor und den Augenwerte Vektor
        int farbe_i = 0;  // Deklariert Zähler für den Farbe Vektor
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

void losgehts()
{
    std::cout << "+++ SKAT +++" << endl;
    std::cout << "Bitte Spielername eingeben:" << endl;



}

static std::vector<Spielkarte> mischen_und_printen(){

    std::vector<Spielkarte> kartenstapel = Spielkarte::karten_generieren();

    // Stapel shuffeln
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto rng = std::default_random_engine(seed);
    std::shuffle(std::begin(kartenstapel), std::end(kartenstapel), rng);

    // Ausgeben des gemischten Blatts im Terminal
    for (int i = 0; i < kartenstapel.size(); i++)
        {
            std::cout << kartenstapel[i].toString() << endl;
            
        }
    std::cout << "Der Stapel hat " << kartenstapel.size() << " Karten" << endl;
    std::cout << endl;
    return kartenstapel;
};  

static void karten_austeilen(std::vector<Spielkarte> kartenstapel){
    
    // Es werden drei leere Vektoren erstellt
    int anzahl_spieler = 3;
    int karten_pro_spieler = 10; 
    std::vector<Spielkarte> spieler1;
    std::vector<Spielkarte> spieler2;
    std::vector<Spielkarte> spieler3;
    std::vector<Spielkarte> tischmitte;
    std::vector<Spielkarte> ablagestapel_1;
    std::vector<Spielkarte> ablagestapel_2;
    std::vector<Spielkarte> ablagestapel_3;

    //Die Karten werden ausgeteilt;
    for (int i = 0; i < karten_pro_spieler; i++)
    {
        //Die letzte Karte vom Stapel wird zum Vektor des Spielers kopiert und dann vom Vektor des Stapels gelöscht
        spieler1.push_back(kartenstapel.back());
        kartenstapel.pop_back();
        spieler2.push_back(kartenstapel.back());
        kartenstapel.pop_back();
        spieler3.push_back(kartenstapel.back());
        kartenstapel.pop_back();
    }

    std::cout << "Spieler 1 beginnt: " << endl;
    std::cout << "Hier das Blatt von Spieler 1 " << endl;
    std::cout << endl;


    for (int i = 0; i < spieler1.size(); i++)
        {
            std::cout << spieler1[i].toString() << endl;
            
        }
    std::cout << endl;
    std::cout << "Hier das Blatt von Spieler 2 " << endl;
    std::cout << endl;


    for (int i = 0; i < spieler2.size(); i++)
        {
            std::cout << spieler2[i].toString() << endl;
            
        }
    std::cout << endl;
    std::cout << "Hier das Blatt von Spieler 3 " << endl;
    std::cout << endl;


    for (int i = 0; i < spieler3.size(); i++)
        {
            std::cout << spieler3[i].toString() << endl;
            
        }

    //Spiellogik
    int karten_pick;
    int gespielte_farbe = 1;                  // 1 = Eichel, 2 = Grün, 3 = Rot, 4 = Schellen
    int trumpf = 1;

    std::cout << "Spieler 1: Wähle den Trumpf aus (Gebe eine Zahl zwischen 1 und 4 ein?)(1 = Eichel, 2 = Grün, 3 = Rot, 4 = Schellen)" << endl;
    std::cin >> trumpf;
    switch (trumpf) {
        case 1:
        std::cout << "Eicheln ist Trumpf" << endl; break;
        case 2: 
        std::cout << "Grün ist Trumpf" << endl; break;
        case 3: 
        std::cout << "Rot ist Trumpf" << endl; break;
        case 4: 
        std::cout << "Schellen ist Trumpf" << endl; break;
    }
    

    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler1.size() <<" ein)" << endl;
    std::cin >> karten_pick;
    unsigned int auswaehler = karten_pick -1;

    tischmitte.push_back(spieler1.at(auswaehler));
    spieler1.erase(spieler1.begin() + auswaehler);

    //std::cout << auswaehler;
    switch (find(farben.begin(), farben.end(), tischmitte[0].getFarbe()) - farben.begin()) {
        case 0: gespielte_farbe = 1;  // Eicheln
        std::cout << "Eicheln ist die gespielte Farbe" << endl; break;
        case 1: gespielte_farbe = 2; // Grün
        std::cout << "Grün ist die gespielte Farbe" << endl; break;
        case 2: gespielte_farbe = 3; // Rot
        std::cout << "Rot ist die gespielte Farbe" << endl; break;
        case 3: gespielte_farbe = 4; // Schellen
        std::cout << "Schellen ist die gespielte Farbe" << endl; break;
    }

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << "Spieler 2 ist an der Reihe" << endl;


    int karten_pick2;
    auswaehler = karten_pick2 -1;
    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler1.size() <<" ein)" << endl;
    std::cin >> karten_pick2;
    tischmitte.push_back(spieler2.at(auswaehler));
    spieler2.erase(spieler2.begin() + auswaehler);

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl;
    std::cout << "Spieler 3 ist an der Reihe" << endl;

    int karten_pick3;
    auswaehler = karten_pick3 -1;
    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler1.size() <<" ein)" << endl;
    std::cin >> karten_pick3;
    tischmitte.push_back(spieler2.at(auswaehler));
    spieler3.erase(spieler3.begin() + auswaehler);

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl;
    std::cout << tischmitte[2].toString() << endl;

}



//Eine Prüffunktion die aus einer anderen aufgabe stand aber meine Vektorkenntnisse testen soll
int main ()
{
//    sprache_waehlen();

    std::vector<Spielkarte> stapel = mischen_und_printen();
    karten_austeilen(stapel);
    //runde_spielen;
    return 0;
}

