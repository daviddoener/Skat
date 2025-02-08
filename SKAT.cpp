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
std::vector<int>prioritaet = {0,1,2,3,4,5,6,7};

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
    Spielkarte (std::string s,std::string f, int a, int p)
                : symbol(s), farbe(f), augen(a) {};

    //Deklarierung einer toString Funktion (kopiert aus ChatGPT)
    std::string toString() const {
        return symbol + " von " + farbe + " (Augen: " + std::to_string(augen) + ")";
    }

    void clearScreen() {
    std::cout << "\033[2J\033[H";
    }

    std::string getFarbe() const {
        return farbe;
    }
    
    std::string getSymbol() const {
        return symbol;
    }

    int getAugen() const {
        return augen;
    }
    //int getPrio() const {
    //    return prioritaet;
    //}

    //Eine Funktion definieren die alle Karten eines Skatblatts generiert
static std::vector<Spielkarte> karten_generieren()
    {   
        int symbol_i = 0; // Deklariert zähler für die Symbol Vektor, den Augenwerte Vektor und den Prioritäts Vektor
        int farbe_i = 0;  // Deklariert Zähler für den Farbe Vektor
        std::vector <Spielkarte> kartenstapel;


        for (symbol_i = 0; symbol_i < symbole.size(); symbol_i++)
        {   
            for (farbe_i = 0; farbe_i < farben.size(); farbe_i++)
            {
                kartenstapel.emplace_back(symbole[symbol_i], farben[farbe_i], augenwerte[symbol_i], prioritaet.at(symbol_i));
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


// Wenn bei einer Nutzereingabe "1234321" eingegeben wird, wird das Spiel abgebrochen.
static void check_exit(const int eingabe) {
    if (eingabe == 1234321) {
        std::cout << "Spiel wird beendet..." << endl;
        exit(0);  // Beendet das Programm sofort
    }
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

bool hat_farbe(const std::vector<Spielkarte>& karten, const std::string& gespielte_farbe) {
    for (int i = 0; i < karten.size(); i++) {
        if (karten[i].getFarbe() == gespielte_farbe) {
            return true; // Sobald eine Karte mit der Farbe gefunden wurde, direkt beenden
        } 
    }
    return false;
}

std::vector<Spielkarte> spieler1;
std::vector<Spielkarte> spieler2;
std::vector<Spielkarte> spieler3;
std::vector<Spielkarte> tischmitte;
std::vector<Spielkarte> ablagestapel_1;
std::vector<Spielkarte> ablagestapel_2;
std::vector<Spielkarte> ablagestapel_3;
std::vector<Spielkarte> skat;

static void karten_austeilen(std::vector<Spielkarte>& kartenstapel,std::vector<Spielkarte>& spieler1,std::vector<Spielkarte>& spieler2,std::vector<Spielkarte>& spieler3){
    // Es werden viele leere Vektoren erstellt, Hand der Spieler, Ablagestapel der Spieler, Tischmitte
    int karten_pro_spieler = 10; 


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
    skat = kartenstapel;

}
static void runde_spielen(std::vector<Spielkarte>& kartenstapel,
                            std::vector<Spielkarte>& spieler1,
                            std::vector<Spielkarte>& spieler2, 
                            std::vector<Spielkarte>& spieler3, 
                            std::vector<Spielkarte>& tischmitte, 
                            std::vector<Spielkarte>& ablagestapel_1, 
                            std::vector<Spielkarte>& ablagestapel_2, 
                            std::vector<Spielkarte>& ablagestapel_3, 
                            int aktuelle_runde, int& gewinner){
    


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

    std::cout << endl;


    //Spiellogik
    int karten_pick;
    
    std::string st_trumpf = "Eicheln";
    
    if (aktuelle_runde == 0){
        int trumpf = 1;
        std::string st_trumpf = "Eicheln";

        std::cout << "Spieler 1: Wähle den Trumpf aus (Gebe eine Zahl zwischen 1 und 4 ein?)(1 = Eichel, 2 = Grün, 3 = Rot, 4 = Schellen)" << endl;
        std::cin >> trumpf;
        check_exit(trumpf); 
        switch (trumpf) {
        case 1:
        std::cout << "Eicheln ist Trumpf" << endl; 
        st_trumpf = "Eicheln"; break;
        case 2: 
        std::cout << "Grün ist Trumpf" << endl; 
        st_trumpf = "Grün"; break;
        case 3: 
        std::cout << "Rot ist Trumpf" << endl; 
        st_trumpf = "Rot"; break;
        case 4: 
        std::cout << "Schellen ist Trumpf" << endl;
        st_trumpf = "Schellen"; break;
    }
    }
    if (aktuelle_runde != 0){
    std::cout << "Der Trumpf ist immer noch " << st_trumpf << endl;

    }

    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler1.size() <<" ein)" << endl;
    std::cin >> karten_pick;
    check_exit(karten_pick); 
    unsigned int auswaehler = karten_pick -1;

    
    tischmitte.push_back(spieler1.at(auswaehler));
    spieler1.erase(spieler1.begin() + auswaehler);


    std::string gespielte_farbe = tischmitte[0].getFarbe();

    std::cout << "Gespielte Farbe: " << gespielte_farbe << endl;

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << "Spieler 2 ist an der Reihe" << endl;

    bool kann_alles_spielen = false;

    if (hat_farbe(spieler2,gespielte_farbe) == true){
        std::cout << "Spieler 2 muss " << gespielte_farbe << " bedienen" << endl;
    }
    else {
        std::cout << "Spieler 2 kann nicht bedienen." << endl;
        kann_alles_spielen = true;
    }

    int karten_pick2;
    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler2.size() <<" ein)" << endl;
    std::cin >> karten_pick2;
    check_exit(karten_pick2); 
    auswaehler = karten_pick2 -1;


    // std::cout << ((spieler2.at(auswaehler)).getFarbe()) << endl; //gibt die Farbe der gespielten Farbe aus

    
    bool weitermachen;
    if ((spieler2.at(auswaehler)).getFarbe() != gespielte_farbe && kann_alles_spielen == false){
        std::cout << "Diese Karte ist ungültig" << endl;
        weitermachen = false;
    }
    else 
        weitermachen = true;
    
    
    while (weitermachen == false){
        std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler2.size() <<" ein)" << endl;
        std::cin >> karten_pick2;
        check_exit(karten_pick2); 
        auswaehler = karten_pick2 -1;
        if ((spieler2.at(auswaehler)).getFarbe() == gespielte_farbe){
            std::cout << "Super! Diese Karte ist besser." << endl;
            weitermachen = true;}

    }

    tischmitte.push_back(spieler2.at(auswaehler));
    spieler2.erase(spieler2.begin() + auswaehler);

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl;
    std::cout << "Spieler 3 ist an der Reihe" << endl;

    kann_alles_spielen = false;
    if (hat_farbe(spieler3,gespielte_farbe) == true){
        std::cout << "Spieler 3 muss " << gespielte_farbe << " bedienen" << endl;
    }
    else {
        std::cout << "Spieler 3 kann nicht bedienen." << endl;
        kann_alles_spielen = true;
    }

    int karten_pick3;
    std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler3.size() <<" ein)" << endl;
    std::cin >> karten_pick3;
    check_exit(karten_pick3); 
    auswaehler = karten_pick3 -1;

    bool weitermachen2 = true;
    if (((spieler3.at(auswaehler)).getFarbe() != gespielte_farbe) && (kann_alles_spielen == false)){
        std::cout << "Diese Karte ist ungültig" << endl;
        weitermachen2 = false;
    }
    else 
        weitermachen2 = true;
    
    
    while (weitermachen2 == false){
            std::cout << "Welche Karte möchtest du spielen (Gebe eine Zahl zwischen 1 und "<< spieler2.size() <<" ein)" << endl;
        std::cin >> karten_pick3;
        check_exit(karten_pick3); 
        auswaehler = karten_pick3 -1;
        if ((spieler3.at(auswaehler)).getFarbe() == gespielte_farbe){
            std::cout << "Super! Diese Karte ist besser." << endl;
            weitermachen2 = true;}

    }

    kann_alles_spielen = false;
    tischmitte.push_back(spieler3.at(auswaehler));
    spieler3.erase(spieler3.begin() + auswaehler);

    std::cout << "Auf dem Tisch liegt " << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl;
    std::cout << tischmitte[2].toString() << endl;
    
    gewinner = 1; //Spielerindex des gewinners (1 = Spieler 1, 2 = Spieler 2, 3 = Spieler 3), wird erstmal auf 1 gesetzt aber später im Programm noch geändert
    bool trumpf_gespielt = false;

    for (int i = 0; i < 3; i++) {
        if (tischmitte[i].getFarbe() == st_trumpf) {
            trumpf_gespielt = true;
        }
    }

    if (trumpf_gespielt) {
        for (int i = 0; i < 3; i++) {
            if (tischmitte[i].getFarbe() == st_trumpf &&
                tischmitte[i].getAugen() > tischmitte[gewinner].getAugen()) {
                gewinner = i;
            }
        }
    } 

    else {
        for (int i = 0; i < 3; i++) {
            if (tischmitte[i].getFarbe() == gespielte_farbe &&
                tischmitte[i].getAugen() > tischmitte[gewinner].getAugen()) {
                gewinner = i;
            }
        }
    }

    std::cout << "Den Stich gewinnt diese Karte: " << tischmitte[gewinner].toString() << endl;
    
    //hier werden die Karte in der Tischmitte dem Ablagestapel des gewinners zugeschoben
    switch (gewinner)
    {
    case 0:
        for (int i = 0; i < 3; i++) {
        ablagestapel_1.push_back(tischmitte[i]);
        };
        break;
    case 1:
        for (int i = 0; i < 3; i++) {
        ablagestapel_2.push_back(tischmitte[i]);
        };
        break;
    case 2:
        for (int i = 0; i < 3; i++) {
        ablagestapel_3.push_back(tischmitte[i]);
        };
        break;
    }
    tischmitte.clear(); //Die Tischmitte wird wieder geleert.
    
    
}

void punkte_auswerten(const std::vector<Spielkarte>& ablagestapel_1, 
    const std::vector<Spielkarte>& ablagestapel_2, 
    const std::vector<Spielkarte>& ablagestapel_3, 
    const std::vector<Spielkarte>& skat, 
    int& gewinner) 
{
int punkte_spieler1 = 0, punkte_spieler2 = 0, punkte_spieler3 = 0;

// Punkte berechnen
for (int i = 0; i < ablagestapel_1.size(); i++) {
punkte_spieler1 += ablagestapel_1[i].getAugen();
}
for (int i = 0; i < ablagestapel_2.size(); i++) {
punkte_spieler2 += ablagestapel_2[i].getAugen();
}
for (int i = 0; i < ablagestapel_3.size(); i++) {
punkte_spieler3 += ablagestapel_3[i].getAugen();
}

//Der Gewinner des letzten Stichs bekommt den Skat dazu
std::cout << "\n--- Der Skat geht an Spieler " << (gewinner + 1) << " ---\n";
for (int i = 0; i < skat.size(); i++) {
std::cout << skat[i].toString() << endl;
}

// Skat-Punkte zum Gewinner hinzufügen
for (const auto& karte : skat) {
if (gewinner == 0) punkte_spieler1 += karte.getAugen();
if (gewinner == 1) punkte_spieler2 += karte.getAugen();
if (gewinner == 2) punkte_spieler3 += karte.getAugen();
}

// Punkte ausgeben
std::cout << "--- Endergebnis ---";
std::cout << "Spieler 1 hat " << punkte_spieler1 << " Punkte." << endl;
std::cout << "Spieler 2 hat " << punkte_spieler2 << " Punkte." << endl;
std::cout << "Spieler 3 hat " << punkte_spieler3 << " Punkte." << endl;

// Gewinner bestimmen
if (punkte_spieler1 > punkte_spieler2 && punkte_spieler1 > punkte_spieler3) {
std::cout << "🎉 Spieler 1 hat gewonnen!" << endl;
} else if (punkte_spieler2 > punkte_spieler1 && punkte_spieler2 > punkte_spieler3) {
std::cout << "🎉 Spieler 2 hat gewonnen!" << endl;
} else if (punkte_spieler3 > punkte_spieler1 && punkte_spieler3 > punkte_spieler2) {
std::cout << "🎉 Spieler 3 hat gewonnen!" << endl;
std::cout << "wuuuup wuuuupppp wupppppp" << endl;
} else {
std::cout << "🤝 Unentschieden!" << endl;
}
}




//Eine Prüffunktion die aus einer anderen aufgabe stand aber meine Vektorkenntnisse testen soll
int main ()
{
//    sprache_waehlen();

    std::vector<Spielkarte> kartenstapel = mischen_und_printen();
    int aktuelle_runde = 0; 
    int max_runden = 10;  // Anzahl der maximalen Runden
    int gewinner = 0;
    karten_austeilen(kartenstapel, spieler1, spieler2, spieler3);
    while (aktuelle_runde < max_runden){
        std::cout << "\n--- Runde " << (aktuelle_runde + 1) << " beginnt! ---\n" << endl;
        runde_spielen(kartenstapel, spieler1, spieler2, spieler3, tischmitte, ablagestapel_1, ablagestapel_2, ablagestapel_3,aktuelle_runde, gewinner);
        aktuelle_runde++;
    }
    punkte_auswerten(ablagestapel_1, ablagestapel_2, ablagestapel_3, skat, gewinner);

    return 0;
}

