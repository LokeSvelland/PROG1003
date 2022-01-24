/**
 * @file OPPG_4.cpp
 * 
 * Programmet skal inneholde:
 *  - struct Tid (time, minutt, sekund)
 *  - struct Tid storst (const struct Tid tid1, const struct Tid tid2)
 * Som finner ut hvilken av de to parameterne som er størst/senest/høyest
 * og returnerer denne
 * 
 * @author Loke Svelland
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>              //  Samme som stdio.h
#include <iomanip>               //  setw
using namespace std;             //  Slipper da å bruke std::cout / std::cin

struct Tid
{
    int time,
        minutt,
        sekund;
};

struct Tid storst(const struct Tid tid1, const struct Tid tid2);

int main() {

    Tid tid1 = {2, 36, 44},
        tid2 = {5, 23, 50},
        tid3 = {13, 2, 40},
        tid4 = {20, 34, 2},
        svar;

    svar = storst(tid1, tid2);
    svar = storst(svar, tid3);
    svar = storst(svar, tid4);

    cout << "\t\nSeneste/største/høyeste tidspunkt er: " << svar.time << ":" << svar.minutt << ":" << svar.sekund << "\n\n\n";

    return 0;


}

Tid storst(const struct Tid tid1, const struct Tid tid2) {

    int tot1 = (tid1.time * 3600) + (tid1.minutt * 60) + tid1.sekund,
        tot2 = (tid2.time * 3600) + (tid2.minutt * 60) + tid2.sekund;

    return((tot1 >= tot2) ? tid1 : tid2);   //returnerer den største structen
}