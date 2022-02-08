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
void slett();
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
    
    cout << "\nAlle stoppesteder:\n\n";
    //Skriver alle stopp stedene nummerert
    for(int i = 0; i < gBusstopp.size(); i++) {
        cout << setw(2) << i+1 << ". " << gBusstopp[i] << '\n';
    }

}

void skrivRuter() {

    if(gRuter.size() > 1) {
        for(int i = 0; i < ANTSTOPP; i++) {
            cout << "Rute nr." << setw(2) << i+1 << ". " << gRuter[i] << '\n';
        }
    } else if(gRuter.size() < 1) {
        cout << "\t\nIngen ruter lagt til\n\n\n";
    }

}

/**
 * 
 * @param rute - ruten som blir skrevet ut
 */
void ruteSkrivData(const Rute rute) {
    string pil = " --> ";

    cout << "\t\nRute nr." << rute.ruteNr << '\n'
         << "\tTotal minutt rute: " << rute.totMin << '\n'
         << "\tRute stopp: ";

    for(int i = 0; i < rute.stopp.size(); i++) {
        if() {
            cout << rute.stopp[i];
        }
    }

}

/**
 * 
 * @param stopp - nr på stoppe sted 
 * 
 * ! - Får nå skrevet ut tilgjenlige stoppesteder
 */
void skrivNesteStoppesteder(const int stopp) {
    int nr = 0;

    for(int i = 0; i < 11; i++) {
        cout << endl;
        if(gMinutter[stopp][i] != 0) {
            cout << "Stopp nummer." << ++nr << "  "<< gMinutter[stopp][i] << "min " << gBusstopp[i];
        }
    }


}

void nyRute() {

    Rute* nyRute = new Rute;
    ruteLesData(*nyRute);
    gRuter.push_back(nyRute);
    cout << "\t\nNy rute har nr." << gRuter.size() << '\n';
    ruteSkrivData(*nyRute);

}


/**
 * 
 * @param rute - ruten som blir lest
 * @return true 
 * @return false 
 * 
 */
bool ruteLesData(Rute & rute) {
    int stop,
        nyttStopp;

    vector<string> nyeStopp;

    rute.ruteNr = gRuter.size()+1;
    skrivStopp();
    stop = lesInt("\t\nVelg startsted: \n", 1, 11);
    rute.stopp.push_back(gBusstopp[stop - 1]);

    skrivNesteStoppesteder(stop - 1);
    
    for(int i = 0; i < 11; i++) {
        cout << "\n";
        if(gMinutter[stop][i] != 0) {
            nyeStopp.push_back(gBusstopp[i]);
        }
    }

    nyttStopp = lesInt("\nSkriv inn neste stopp nummer: ", 1, nyeStopp.size());
    rute.stopp.push_back(nyeStopp[nyttStopp - 1]);
    rute.totMin += gMinutter[stop][nyttStopp];
    nyeStopp.clear();
   /* while(nyttStopp != 0) {
        skrivNesteStoppesteder(nyttStopp);
    
        for(int i = 0; i < 11; i++) {
            cout << endl;
            if(gMinutter[stop][i] != 0) {
                nyeStopp.push_back(gBusstopp[i]);
            }
        }

        nyttStopp = lesInt("\nSkriv inn neste stopp nummer: ", 0, nyeStopp.size());
        rute.stopp.push_back(nyeStopp[nyttStopp - 1]);
        nyeStopp.clear();
   }*/


    if(rute.stopp.size() > 1) {
        return true;
    } else {return false;}
}


/**
 * Bruker velger her hvilke(n) rute som skal slettes
 * 
 */
void slettRute() {
    int valg;

    if(gRuter.size() == 0) {
        cout << "\t\nIngen ruter lagt til\n\n";
    } else {
        for(int i = 0; i < gRuter.size(); i++) {
            cout << i+1 << gRuter[i];
        }

        valg = lesInt("\nHvilken rute skal slettes: ", -1, gRuter.size());
        if(valg == -1) {        // sletter alle ruter
            void slett();
        } else if(valg == 0) {  // ingen slettes, går ut av funksjonen
            cout << "\t\nIngen rute fjernet, returnerer til startmeny\n\n";
            exit;
        } else if(valg <= 1) {  // sletter valgt rute
            slett(valg);
        }

    }

}

/**
 * Sletter alle ruter
 * 
 */
void slett() {

    for(int i = 0; i < gRuter.size(); i++)  // Sletter alle rutene i vectoren
        delete gRuter[i];

    gRuter.clear();                         // fjerner alle pekerne i vectoren
    cout << "\n\nvectoren er tom - antallet er: " << gRuter.size() << "\n\n";

}


/**
 * 
 * @param nr - nr på rute som blir slettet
 */
void slett(const int nr) {
    delete gRuter[nr-1];                    //sletter valgt rute
    gRuter[nr-1] = gRuter[gRuter.size()-1]; //bakerste flyttes til plassen
    gRuter.pop_back();                      // siste peker slettes også

}