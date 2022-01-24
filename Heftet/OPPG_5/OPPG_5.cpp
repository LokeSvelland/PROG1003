/**
 * 
 *  
 * 
 * 
 * 
 * @file OPPG_5.cpp
 * @author Loke Svelland
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>              //  Samme som stdio.h
#include <iomanip>               //  setw
#include "LesData2.h"            //  Verktøykasse for lesing av diverse data
using namespace std;             //  Slipper da å bruke std::cout / std::cin

const int STRLEN           = 40; ///< Max.tekstLengde
const int MAXFORELESNINGER = 10; ///< Max.antall forelesninger

struct Forelesning {
    char emne[STRLEN/2],
         Foreleser[STRLEN],
         sted[STRLEN/2];
    int  timeStart, minuttStart,
         timeSlutt, minuttSlutt;
};

void forelesningLesData(Forelesning* f);
void forelesningSkrivData(const Forelesning* f);



/**
 *  Hovedprogram
 */
int main() {

    Forelesning forelesninger[MAXFORELESNINGER];

    for(int i = 0; i < MAXFORELESNINGER; i++) {
        cout << "\t\nData om forelesning nr. " << i+1 << ":\n";
        forelesningLesData(&forelesninger[i]);
    }

    cout << "\n\n";

    for(int i = 0; i < MAXFORELESNINGER; i++) {
        cout << "\t\nInnlest data om forelesning nr. " << i+1 << ":\n";
        forelesningSkrivData(&forelesninger[i]);
    }

    return 0;
}

/**
 * Leser inn verdier til ALLe datamedlemmene i/til den medsendte structen
 * 
 * @param f - Forelesning-struct som får sine datamedlemmer innlest
 * 
 */
void forelesningLesData(Forelesning* f) {

    cout << "\tEmnenavn : ";    cin.getline(f->emne, STRLEN/2);
    cout << "\tForeleser: ";    cin.getline(f->Foreleser, STRLEN);
    cout << "\tSted/rom : ";    cin.getline(f->sted, STRLEN/2);
    f->timeStart           =    lesInt("Time-start",    8, 20);
    f->minuttStart         =    lesInt("Minutt-start",  0, 59);
    f->timeSlutt           =    lesInt("Time-slutt", f->timeStart+1, 20);
    f->minuttSlutt         =    lesInt("Minutt-slutt",  0, 59);

}


/**
 * Skriver ut ALLE datamedlemmene i/til den medsendte structen
 * 
 * @param f - Forelesning-struct som får sine datamedlemmer skrevet ut
 * 
 */
void forelesningSkrivData(const Forelesning* f) {
    cout << "\t" << f->timeStart << ":" << ((f->minuttStart < 10) ? "0" : "") << f->minuttStart << "-" << f->timeSlutt << ":" << ((f->minuttSlutt < 10) ? "0" : "") << f->minuttSlutt << ", " << f->emne << ", " << f->sted << "\n\tmed: " << f->Foreleser << "\n";
}