#pragma once
#include <string>
#include <vector>

// Die Deklarierung und Definition von drei Arrays : Die 8 "Symbole", die 4 Farben, die 8 möglichen Augenzahlen
std::vector<std::string>symbole = {"Sieben" , "Acht" , "Neun" , "Unter" , "Ober" , "König" , "Zehn" , "Ass"};
std::vector<std::string>farben = {"Eicheln","Grün","Rot", "Schellen"};

std::vector<int>augenwerte = {0,0,0,2,3,4,10,11};  
std::vector<int>prioritaet = {0,1,2,3,4,5,6,7};                                                                                 // hier wollte ich noch einen weiteren Integer zur Klasse hinzufügen, im Falle, dass drei Karten mit dem Augenwert 0 gelegt werden
//                                                                                                                              // leider habe ich das nicht geschafft und deshalb wird im Falle von "Sieben", "Acht" und "Neun" in der gleichen Farbe, kein Gewinner festgelegt.
