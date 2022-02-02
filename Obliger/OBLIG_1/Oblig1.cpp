/**
 *
 *  Obligatorisk oppgave nr 1 Våren 2022, PROG1003
 *
 * @file Oblig1.cpp
 * @author Loke Svelland
 *
 */

#include <iostream>   //  Samme som stdio.h
#include <iomanip>    //  setw
#include <vector>     //  FOR å KUNNE BRUKE: STLs vector
#include <string>     //  STRING-KLASSEN
#include "LesData2.h" //  Verktøykasse for lesing av diverse data
using namespace std;  //  Slipper da å bruke std::cout / std::cin

const int ANTSTOPP = 11; ///< Totalt antall ulike busstopp.

struct Rute
{
    vector<string> stopp; // Rutens ulike stoppesteder.
    int ruteNr,           // Reelt rutenr, f.eks. 42, 165, 718
        totMin;           // Totalt antall minutter å kjøre på ruten
};                        // (fra første til siste stoppested).

vector<Rute *> gRuter; ///< Pekere til rutene.

const vector<string> gBusstopp = ///< Navn på alle busstopp.
    {"Skysstasjonen", "Fahlstroms plass", "Sykehuset",
     "Gjovik stadion", "Bergslia", "Overby", "Nybrua",
     "NTNU", "Kallerud", "Hunndalen", "Mustad fabrikker"};

const int gMinutter[ANTSTOPP][ANTSTOPP] = ///< Min.mellom stoppesteder.
                                          // const vector <vector <int> > gMinutter = // Alternativt (nå lært i vår).
    {{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Skysstasjonen = 0
     {3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4},   // Fahlstrøms plass = 1
     {0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0},   // Sykehuset = 2
     {0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},   // Gjøvik stadion = 3
     {0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0},   // Bergslia = 4
     {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},   // Øverby = 5
     {0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 2},   // Nybrua = 6
     {0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0},   // NTNU = 7
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Kallerud = 8
     {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2},   // Hunndalen = 9
     {0, 4, 0, 0, 0, 0, 2, 0, 0, 2, 0}};  // Mustad fabrikker = 10

void skrivMeny();
void skrivStopp();
void skrivRuter();
void ruteSkrivData(const Rute rute);
void skrivNesteStoppesteder(const int stopp);
void nyRute();
void slett(const int nr);
void slettRute();
bool ruteLesData(Rute &rute);

/**
 * hovedprogram
 */
int main()
{

    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q')
    {
        switch (kommando)
        {
        case 'N':   nyRute();           break;
        case 'S':   slettRute();        break;
        case 'A':   skrivRuter();       break;
        case 'B':   skrivStopp();       break;
        }
        kommando = lesChar("\nKommando");
    }

    return 0;
}

void skrivMeny() {

    cout << "\nValg: \n"
         << "\tN - Ny rute\n"
         << "\tS - slett Rute\n"
         << "\tA - Skriv alle ruter\n"
         << "\tB - Skriv stopp\n"
         << "\tQ - avslutt\n";

}

void skrivStopp() {
    
    //Skriver alle stopp stedene nummerert
    for(int i = 0; i < gBusstopp.size(); i++) {
        cout << i+1 << ". " << gBusstopp[i] << '\n';
    }

}

void skrivRuter() {



}

/**
 * 
 * @param rute - ruten som blir skrevet ut
 */
void ruteSkrivData(const Rute rute) {



}

/**
 * 
 * @param stopp - nr på stoppe sted 
 */
void skrivNesteStoppesteder(const int stopp) {



}

void nyRute() {



}

void slettRute() {



}


/**
 * 
 * @param nr - nr på rute som blir slettet
 */
void slett(const int nr) {



}


/**
 * 
 * @param rute - ruten som blir lest
 * @return true 
 * @return false 
 */
bool ruteLesData(Rute &rute) {



}
