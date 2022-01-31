/**
 *
 *
 *
 * @file Oblig1.cpp
 * @author Loke Svelland
 *
 */

#include <iostream>             //  Samme som stdio.h
#include <iomanip>              //  setw
#include <vector>               //  FOR å KUNNE BRUKE: STLs vector
#include <string>               //  STRING-KLASSEN
#include "LesData2.h"           //  Verktøykasse for lesing av diverse data
using namespace std;            //  Slipper da å bruke std::cout / std::cin

const int ANTSTOPP = 11;        ///< Totalt antall ulike busstopp.

struct Rute
{
    vector<string> stopp;       // Rutens ulike stoppesteder.
    int ruteNr,                 // Reelt rutenr, f.eks. 42, 165, 718
        totMin;                 // Totalt antall minutter å kjøre på ruten
};                              // (fra første til siste stoppested).

vector<Rute *> gRuter;          ///< Pekere til rutene.

const vector<string> gBusstopp = ///< Navn på alle busstopp.
    {"Skysstasjonen", "Fahlstroms plass", "Sykehuset",
     "Gjovik stadion", "Bergslia", "Overby", "Nybrua",
     "NTNU", "Kallerud", "Hunndalen", "Mustad fabrikker"};

const int gMinutter[ANTSTOPP][ANTSTOPP] = ///< Min.mellom stoppesteder.
                                          // const vector <vector <int> > gMinutter = // Alternativt (nå lært i vår).
    {{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // Skysstasjonen = 0
     {3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4},  // Fahlstrøms plass = 1
     {0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // Sykehuset = 2
     {0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},  // Gjøvik stadion = 3
     {0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0},  // Bergslia = 4
     {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},  // Øverby = 5
     {0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 2},  // Nybrua = 6
     {0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0},  // NTNU = 7
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // Kallerud = 8
     {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2},  // Hunndalen = 9
     {0, 4, 0, 0, 0, 0, 2, 0, 0, 2, 0}}; // Mustad fabrikker = 10

void skrivMeny();
void skrivStopp();
void skrivRuter();
void ruteSkrivData(const Rute rute);
void skrivNesteStoppesteder(const int stopp);
void nyRute();
void slett();
void slettRute();
bool ruteLesData(Rute & rute);


/**
 * hovedprogram
 */
int main() {

    char kommando = 
             lesChar("\n\nGi kommando (N)y rute, (S)lett rute, (B) skriv alle Bussruter, Q(uit))");

    while (kommando != 'Q') {
        switch (kommando)  {
          case 'N':  nyRute();         break;
          case 'S':  slettRute();      break;
          case 'P':  skrivRuter();     break;
        }
        kommando = 
             lesChar("\n\nGi kommando (N)y rute, (S)lett rute, (B) skriv alle Bussruter, (Q)uit");
    }

    return 0;

}


void skrivMeny() {



}



void skrivStopp() {



}



void skrivRuter() {



}



void ruteSkrivData(const Rute rute) {



}



void skrivNesteStoppesteder(const int stopp) {



}



void nyRute() {



}



void slettRute() {



}



bool ruteLesData(Rute & rute) {



}


