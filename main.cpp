#include <iostream> 
#include <algorithm>
#include <random> // std :: default_random_engine
#include <chrono> // std :: chrono :: system_clock
#include <vector>
#include "Spielkarte.hpp" // Inkludiert meine Header-Datei
#include "Eigenschaften.hpp"

using std::endl;
using namespace std;

//Line zum Kompilen fürs Terminal "g++ -std=c++23 -Wall ./SKAT.cpp -o ./skat  && ./skat"


std::string spieler1_name;                                                                                                      // Außerhalb der Funktion deklariert damit andere Funktionen einfacher darauf zugreifen können
std::string spieler2_name;
std::string spieler3_name;

//Die Klasse Spielkarte wird definiert





std::vector<Spielkarte> spieler1;
std::vector<Spielkarte> spieler2;
std::vector<Spielkarte> spieler3;
std::vector<Spielkarte> tischmitte;
std::vector<Spielkarte> ablagestapel_1;
std::vector<Spielkarte> ablagestapel_2;
std::vector<Spielkarte> ablagestapel_3;
std::vector<Spielkarte> skat;

void losgehts()
{

    std::cout << "+++ SKAT +++" << endl;
    std::cout << "Bitte Name von Spieler 1 eingeben:" << endl;
    std::cin >> spieler1_name;
    std::cout << "Bitte Name von Spieler 2 eingeben:" << endl;
    std::cin >> spieler2_name;
    std::cout << "Bitte Name von Spieler 3 eingeben:" << endl;
    std::cin >> spieler3_name;

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
            return true;                                                                    // Sobald eine Karte mit der Farbe gefunden wurde, direkt beenden
        } 
    }
    return false;
}



static void karten_austeilen(std::vector<Spielkarte>& kartenstapel,std::vector<Spielkarte>& spieler1,std::vector<Spielkarte>& spieler2,std::vector<Spielkarte>& spieler3){
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

static void blatt_ausgeben(){                       
                                

    std::cout << "Spieler" <<   " 1 (" << spieler1_name << ") beginnt: " << endl << endl;
    std::cout << "Hier das Blatt von " << spieler1_name << endl;
    std::cout << endl;


    for (int i = 0; i < spieler1.size(); i++)
        {
            std::cout << spieler1[i].toString() << endl;
            
        }
    std::cout << endl;
    std::cout << "Hier das Blatt von  "  << spieler2_name  << endl;
    std::cout << endl;


    for (int i = 0; i < spieler2.size(); i++)
        {
            std::cout << spieler2[i].toString() << endl;
            
        }
    std::cout << endl;
    std::cout << "Hier das Blatt von " << spieler3_name << endl;
    std::cout << endl;


    for (int i = 0; i < spieler3.size(); i++)
        {
            std::cout << spieler3[i].toString() << endl;
            
        }

    std::cout << endl;
}

std::string st_trumpf = "Eicheln";                                                                                              // Dieser String wird außerhalb einer Funktion deklariert
std::string trumpf_waehlen(int& aktuelle_runde, std::string st_trumpf){
    
    
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
    return st_trumpf;
    }

static void karten_waehlen(std::vector<Spielkarte>& kartenstapel,                                                               // Ist die größte Funktion und deutlich größer als 20 Zeilen            
                            std::vector<Spielkarte>& spieler1,
                            std::vector<Spielkarte>& spieler2, 
                            std::vector<Spielkarte>& spieler3, 
                            std::vector<Spielkarte>& tischmitte, 
                            std::vector<Spielkarte>& ablagestapel_1, 
                            std::vector<Spielkarte>& ablagestapel_2, 
                            std::vector<Spielkarte>& ablagestapel_3,
                            std::string st_trumpf, 
                            int aktuelle_runde, 
                            int& gewinner ){
    


    //Spiellogik
    int karten_pick;
    
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

    std::cout << "Gespielte Farbe: " << gespielte_farbe << endl << endl;

    std::cout << "Auf dem Tisch liegt:" << endl;
    std::cout << tischmitte[0].toString() << endl << endl;
    std::cout << "Spieler 2 ist an der Reihe" << endl;

    bool kann_alles_spielen = false;

    if (hat_farbe(spieler2,gespielte_farbe) == true){
        std::cout << spieler2_name << " muss " << gespielte_farbe << " bedienen." << endl << endl;
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

    std::cout << "Auf dem Tisch liegt:" << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl << endl;
    std::cout << "Spieler 3 ist an der Reihe" << endl;

    kann_alles_spielen = false;
    if (hat_farbe(spieler3,gespielte_farbe) == true){
        std::cout << spieler3_name << " muss " << gespielte_farbe << " bedienen." << endl << endl;
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

    std::cout << "Auf dem Tisch liegt:" << endl;
    std::cout << tischmitte[0].toString() << endl;
    std::cout << tischmitte[1].toString() << endl;
    std::cout << tischmitte[2].toString() << endl << endl;



    gewinner = 0; //Spielerindex des gewinners (0 = Spieler 1, 1 = Spieler 2, 2 = Spieler 3), wird erstmal auf -1 gesetzt aber später im Programm noch geändert
    bool trumpf_gespielt = false;


    if (trumpf_gespielt) {                                                                                                          // Wenn ein Trumpf liegt dann muss die Karte in Mitte                  
        for (int i = 0; i < 3; i++) {
            if (tischmitte[i].getFarbe() == st_trumpf && tischmitte[i].getAugen() > tischmitte[gewinner].getAugen()) {              // Prüft mit einer Schleife ob die aktuell angeschaute Karte Trumpf ist und einen höheren Augenwert hat als die bisherige Gewinner Karte
                gewinner = i;                                                                                                       // Als erstes wird gewinner auf 0 gesetzt aber verändert falls eine andere Karte der Gewinner ist
            }
        }
    } 

    else {
        for (int i = 0; i < 3; i++) {
            if (tischmitte[i].getFarbe() == gespielte_farbe && tischmitte[i].getAugen() > tischmitte[gewinner].getAugen()) {        // Falls kein Trumpf in der Tischmitte liegt so gewinnt die Karte mit dem höchsten Augenwert, welche zur gespielten Farbe gehört
                gewinner = i;                                                                                                       // "Abgeworfene" Karten werden so nicht gezählt
            }
        }
    }



    std::cout << "Den Stich gewinnt diese Karte: " << tischmitte[gewinner].toString() << endl << endl;
    
    //hier werden die Karte in der Tischmitte dem Ablagestapel des gewinners zugeschoben
    switch (gewinner)                                                                                                               // Da bei meinem Code immmer Spieler1 die erste Karte legt, Spieler 2 die 2. etc.
    {                                                                                                                               // können die Karten in der Tischmitte anhand ihrer Position dem richtigen Ablagestapel zugeordnet werden
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

void punkte_auswerten(const std::vector<Spielkarte>& ablagestapel_1,                                                                // Diese Funktion benötigt die Ablagestapel-Vektoren + den gewinner des letzten Stichs für den Skat
    const std::vector<Spielkarte>& ablagestapel_2,                                                                                  // Da diese Funktion erst ganz am Ende ausgeführt wird, kann die Gewinner Variable übernommen werden
    const std::vector<Spielkarte>& ablagestapel_3,                                                                                  // So wird automatisch der Gewinner des letzten Stichs genommen
    const std::vector<Spielkarte>& skat, 
    int& gewinner) 
{
    int punkte_spieler1 = 0, punkte_spieler2 = 0, punkte_spieler3 = 0;

    // Punkte berechnen
    for (int i = 0; i < ablagestapel_1.size(); i++) { 
    punkte_spieler1 += ablagestapel_1[i].getAugen();    // Die Augen aller Karten im Ablagestapel werden aufaddiert    
    }
    for (int i = 0; i < ablagestapel_2.size(); i++) {
    punkte_spieler2 += ablagestapel_2[i].getAugen();
    }
    for (int i = 0; i < ablagestapel_3.size(); i++) {
    punkte_spieler3 += ablagestapel_3[i].getAugen();
    }

    //Der Gewinner des letzten Stichs bekommt den Skat dazu
    std::cout << "\n--- Der Skat geht an Spieler " << (gewinner + 1) << " ---\n";                                                   // Gewinner der letzten Runde und damit des Skats wird über Konsole ausgegeben
    for (int i = 0; i < skat.size(); i++) {
        std::cout << skat[i].toString() << endl;
    }

    // Skat-Punkte zum Gewinner hinzufügen
        if (gewinner == 0) {
            for (int i = 0; i < skat.size(); i++){
                punkte_spieler1 += skat[i].getAugen();
            }
        }
        if (gewinner == 1) {
            for (int i = 0; i < skat.size(); i++){
                punkte_spieler2 += skat[i].getAugen();
            }
        }  
        if (gewinner == 2) {
            for (int i = 0; i < skat.size(); i++){
                punkte_spieler3 += skat[i].getAugen();
            }
        }
        


    // Punkte ausgeben
    std::cout << "--- Endergebnis ---" << endl;
    std::cout << "Spieler 1 hat " << punkte_spieler1 << " Punkte." << endl;
    std::cout << "Spieler 2 hat " << punkte_spieler2 << " Punkte." << endl;
    std::cout << "Spieler 3 hat " << punkte_spieler3 << " Punkte." << endl;

    // Gewinner bestimmen
    if (punkte_spieler1 > punkte_spieler2 && punkte_spieler1 > punkte_spieler3) {
        std::cout << "🎉 Spieler 1 hat gewonnen!" << endl;
    } 
        
    else if (punkte_spieler2 > punkte_spieler1 && punkte_spieler2 > punkte_spieler3) {
        std::cout << "🎉 Spieler 2 hat gewonnen!" << endl;
    } 
    else if (punkte_spieler3 > punkte_spieler1 && punkte_spieler3 > punkte_spieler2) {
        std::cout << "🎉 Spieler 3 hat gewonnen!" << endl;
        std::cout << "wuuuup wuuuupppp wupppppp" << endl;
    } 
    else {
        std::cout << "🤝 Unentschieden!" << endl;
    }
}

static void letze_runde_gewonnen(int aktuelle_runde, int gewinner){
    if (aktuelle_runde == 0){
    }
    else {
        std::cout << "--- Runde " << (aktuelle_runde + 1) << " beginnt! ---" << endl;
        if (gewinner + 1 == 1){
            std::cout << "--- Spieler " << (gewinner + 1) << " (" << spieler1_name << ") hat die letzte Runde gewonnen---" << endl; // Gewinner der letzten Runde wird ausgegeben
        }                                                                                                                           // Leider habe ich es nicht geschafft ein System zu implementieren, damit der Gewinner der letzten Runde die neue Runde beginnt
        if (gewinner + 1 == 2){                                                                                                     // Deswegen wird immer nur der gewinner der letzten Runde ausgegeben und es beginnt jedes mal Spieler 1, dann Spieler 2, dann Spieler 3
            std::cout << "--- Spieler " << (gewinner + 1) << " (" << spieler2_name << ") hat die letzte Runde gewonnen---" << endl; 
        }
        if (gewinner + 1 == 3){
            std::cout << "--- Spieler " << (gewinner + 1) << " (" << spieler3_name << ") hat die letzte Runde gewonnen---" << endl;
        }
    }
}


int main ()                                                                                                                         //Wie gefordert, habe ich den Quellcode in verschieden Funktionen unterteilt, die jetzt in der main-Funktion abgerufen werden
{
    losgehts();                                                                                                                     // Fragt die Spieler nach ihren Namen
    std::vector<Spielkarte> kartenstapel = mischen_und_printen();                                                                   // Der Vektor mit den 32 Spielkarten wird erstellt
    int aktuelle_runde = 0;                                                                                                        
    int max_runden = 10;                                                                                                            // Anzahl der maximalen Runden (bei Skat immer 10)
    int gewinner = 0;                                                                                                               
    karten_austeilen(kartenstapel, spieler1, spieler2, spieler3);                                                                   // Die Karten werden auf die 3 Spieler verteilt und die restlichen 2 Karten landen im Skat
    while (aktuelle_runde < max_runden){                                                                                            // Schleife damit 10 Runden gespielt werden
        blatt_ausgeben();                                                                                                           // In jeder Runde wird das Blatt der 3 Spieler zuerst ausgegeben
        letze_runde_gewonnen(aktuelle_runde, gewinner);                                                                             // Ab Runde 2 wird ausgegeben wer den letzten Stich gewonnen hat (leider fehlt das Feature, dass dieser Spieler auch anfängt)
        trumpf_waehlen(aktuelle_runde, st_trumpf);                                                                                  // Diese Funktion wird nur beim ersten mal ausgeführt
        karten_waehlen(kartenstapel, spieler1, spieler2, spieler3, tischmitte, ablagestapel_1, ablagestapel_2, ablagestapel_3, st_trumpf, aktuelle_runde, gewinner); // Die Hauptspielfunktion (etwas zu lang)
        aktuelle_runde++;
    }
    punkte_auswerten(ablagestapel_1, ablagestapel_2, ablagestapel_3, skat, gewinner);                                               // Wenn die Schleife vorbei ist, wird der Gewinner ausgerechnet und ausgegeben

    return 0;
}

