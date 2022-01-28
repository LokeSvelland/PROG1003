/**
 * 
 * 
 * 
 * 
 * @file OPPG_6.cpp
 * @author Loke Svelland
 * 
 */

#include <iostream>              //  Samme som stdio.h
#include <iomanip>               //  setw
#include <string>                  //  STRING-KLASSEN
#include "LesData2.h"            //  Verktøykasse for lesing av diverse data
using namespace std;             //  Slipper da å bruke std::cout / std::cin


/**
 * 
 * Hovedprogram
 */
int main() {

    string tekst1;
    string tekst2;
    string tekst3;
    string tekst4;
    string tekst5;


    cout << "Ditt navn: ";
    cin >> tekst1;
    cin.ignore();

    cout << "\nAdressen din: ";
    getline(cin, tekst2);

    cout << "\nSkriv inn flere ord: ";
    getline(cin, tekst3);

    cout << "Ditt navn er: " << tekst1 << "\n\nDin adresse er: " << tekst2 << "\n\nDine ord: " << tekst3 << "\n\n\n";

    tekst2 = tekst3;
    cout << "Kopiert tekst3 over til tekst 2: " << tekst2 << "\n\n\n";

    if(tekst2 == tekst3) {
        cout << "tekst2 er lik tekst3";
    } else {
        cout << "tekst2 og tekst3 er ikke like";
    }

    cout << "\n\n\n";

    tekst4 = tekst1 + tekst2;
    cout << tekst1 << " Pluss " << tekst2 << " skjøtet sammen er: " << tekst4;

    cout << "\n\n\n";

    tekst1 += ".......";
    cout << "tekst1 er nå: " << tekst1 << "\n\n\n";

    cout << "tekst1 sin lengde er: " << tekst1.size() << "\n\n"
         << "tekst2 sin lengde er: " << tekst2.length() << "\n\n\n";
}