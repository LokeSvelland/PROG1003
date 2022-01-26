/**
 *   Programeksempel nr 1 - Større programeksempel.
 *
 *   Eksemplet viser/vektlegger bruk av en array med globale structer,
 *   at ulike funksjoner opererer p� denne, og sender med pekere til structer.
 *
 *   Programmet:
 *     - har oversikt over og skriver ut en brusautomats innhold
 *     - lar en bruker f� kj�pe EN flaske av en drikke
 *     - lar det p�fylles (bli mer) av EN GITT drikke
 *     - lar brukeren endre ALLE en drikkes data (navn, antall, pris)
 *
 *   @file     EKS_01.CPP
 *   @author   Frode Haug, NTNU
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <cstring>                 //  strcpy
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


const int STRLEN     = 20;         ///<  Max.tekstlengde.
const int MAXDRIKKER = 10;         ///<  Max.antall forelesninger.


struct AutomatDrikke {
    char  navn[STRLEN];
    int   antall,
          pris;
};


void automatDrikkeEndre(AutomatDrikke* ad);
void automatDrikkeKjop(AutomatDrikke* ad);
void automatDrikkePaafyll(AutomatDrikke* ad);
void automatDrikkeSkrivData(const AutomatDrikke* ad);
void endreDrikke();
void initierDrikker();
void kjopDrikke();
void paafyllAvDrikke();
void skrivAlleDrikker();
void skrivMeny();


AutomatDrikke gDrikker[MAXDRIKKER];   ///<  ALT innholdet i drikkeautomaten.
int gTotalSalg = 0;                   ///<  Totalsalget siden programstart.


/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    initierDrikker();
    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'K': kjopDrikke();              break;
          case 'P': paafyllAvDrikke();         break;
          case 'E': endreDrikke();             break;
          default:  skrivMeny();               break;
        }
        kommando = lesChar("\nKommando");
    }

    cout << "\n\nDagens salg ble p� kr. " << gTotalSalg << "\n\n";
    return 0;
}


/**
 *  F�r tilbud om og mulighet til � endre p� ALLE structens datamedlemmer.
 *
 *  @param   ad  -  Structen som f�r endret 0 eller flere datamedlemmer
 *  @see     'automatDrikkeSkrivData(...)'
 */
void automatDrikkeEndre(AutomatDrikke* ad)  {
    char valg;
    cout << "\n\tLagrede data er alts�:  ";
    automatDrikkeSkrivData(ad);      //  Skriver n�v�rende status for drikken.

    cout << "\n\tEndre:\n"           //  Meny for endrings-valg:
        << "\t\tN - Navn\n"
        << "\t\tA - Antall\n"
        << "\t\tP - Pris\n"
        << "\t\tS - Slutt\n";
    valg = lesChar("\t\tValg (N/A/P/S)");

    while (valg != 'S')  {           //  �nsker fortsatt � endre noe:
      switch (valg)  {               //  Endrer aktuelt datamedlem.
        case 'N':  cout << "\t\tNytt navn: ";
                   cin.getline(ad->navn, STRLEN);                  break;
        case 'A':  ad->antall = lesInt("\t\tNytt antall", 0, 40);  break;
        case 'P':  ad->pris   = lesInt("\t\tNy pris", 15, 40);     break;
        default:   cout << "\t\tUlovlig valg!\n";                  break;
      }
      valg = lesChar("\n\t\tValg (N/A/P/S)");
    }
    cout << "\n\tNye lagrede data:  ";
    automatDrikkeSkrivData(ad);      //  Skriver ny(?) status for drikken.
}


/**
 *  Kj�per ETT stk. flaske av vedkommende drikke.
 *
 *  @param   ad  -  Structen som evt. f�r redusert antall igjen med EN
 *  @see     'automatDrikkeSkrivData(...)'
 */
void automatDrikkeKjop(AutomatDrikke* ad)  {
    int betalt;
    cout << "\n\tStatus er alts�:  ";
    automatDrikkeSkrivData(ad);      //  Skriver n�v�rende status for drikken.
    if (ad->antall > 0) {            //  Fortsatt igjen av drikken:
        cout << "\tDen koster pr.flaske: " << ad->pris << " kr\n\n\t";
        betalt = lesInt("Betal kr", 0, 100);  //  Brukerens myntinnkast.

        if (betalt > ad->pris)       // For mye betalt - skal ha penger igjen:
            cout << "\n\tDu betalte for mye. Retur kr. "
                 << betalt - ad->pris << '\n';

        if (betalt >= ad->pris) {    //  Betalt nok - skal ha drikke/flaske:
            cout << "\n\tTa imot din " << ad->navn << " i luken .....\n";
            ad->antall--;            //  Teller ned antallet igjen.
            gTotalSalg += ad->pris;  //  �ker (dagens) totalsalg.
        } else                       //  Ikke betalt nok - penger tilbake:
            cout << "\n\tFor lite betalt.\n\t"
                 << "Ta returpengene, gj�r evt. nytt valg og betal nok.\n";
    } else                           //  Tomt for drikken:
        cout << "\n\tDvs. det er TOMT for denne drikken. Velg en annen.\n";
}


/**
 *  F�r/setter inn flere flasker av en gitt drikke.
 *
 *  @param   ad  -  Structen som evt. f�r �kt antallet igjen av
 *  @see     'automatDrikkeSkrivData(...)'
 */
void automatDrikkePaafyll(AutomatDrikke* ad)  {
    cout << "\n\tStatus F�R p�fylling:  ";
    automatDrikkeSkrivData(ad);     //  Skriver n�v�rende status for drikken.
                                    //  Fyller p� med et visst antall flasker:
    ad->antall += lesInt("\n\tP�fyll antall flasker", 0, 40);

    cout << "\n\tStatus ETTER p�fylling:  ";
    automatDrikkeSkrivData(ad);     //  Skriver ny(?) status for drikken.
}


/**
 *  Skriver ut p� skjermen ALLE datamedlemmer for EN drikke.
 *
 *  @param   ad  -  Structen som blir skrevet ut (ALLE datamedlemmer)
 */
void automatDrikkeSkrivData(const AutomatDrikke* ad)  {
  cout << "#igjen: "  << setw(3) << ad->antall
       << "   pris: " << setw(3) << ad->pris << "    - " << ad->navn << '\n';
}


/**
 *  Brukeren tilbys � endre ALLE datamedlemmene for EN drikke.
 *
 *  @see   'skrivAlleDrikker()'
 *  @see   'automatDrikkeEndre(...)'
 */
void endreDrikke()  {
    int endreNr;                      //  Drikkenummeret som skal endres.

    skrivAlleDrikker();               //  Skriver HELE automatens innhold.
    endreNr = lesInt("Endre nr", 0, MAXDRIKKER);
    if (endreNr)                      //  Noe annet enn 0 (null) er skrevet:
        automatDrikkeEndre(&gDrikker[endreNr-1]);   //  Drikkens data endres.
    else
        cout << "\n\tOK - ingen endring av noen drikke.\n";
}


/**
 *  Automaten med drikke initieres med en god del drikker, antallet og priser.
 */
void initierDrikker()  {
    strcpy(gDrikker[0].navn, "Cola");
           gDrikker[0].antall = 11;  gDrikker[0].pris = 21;
    strcpy(gDrikker[1].navn, "Cola Zero");
           gDrikker[1].antall = 12;  gDrikker[1].pris = 22;
    strcpy(gDrikker[2].navn, "Pepsi Cola");
           gDrikker[2].antall = 13;  gDrikker[2].pris = 23;
    strcpy(gDrikker[3].navn, "Pepsi MAX");
           gDrikker[3].antall = 14;  gDrikker[3].pris = 24;
    strcpy(gDrikker[4].navn, "Solo");
           gDrikker[4].antall = 15;  gDrikker[4].pris = 25;
    strcpy(gDrikker[5].navn, "Farris");
           gDrikker[5].antall = 16;  gDrikker[5].pris = 26;
    strcpy(gDrikker[6].navn, "Farris Gul");
           gDrikker[6].antall = 17;  gDrikker[6].pris = 27;
    strcpy(gDrikker[7].navn, "Urge");
           gDrikker[7].antall = 18;  gDrikker[7].pris = 28;
    strcpy(gDrikker[8].navn, "Red Bull");
           gDrikker[8].antall = 19;  gDrikker[8].pris = 29;
    strcpy(gDrikker[9].navn, "Imsdal Vann");
           gDrikker[9].antall = 20;  gDrikker[9].pris = 30;
}


/**
 *  Brukeren tilbys � kj�pe EN flaske av en eller annen drikke.
 *
 *  @see   'skrivAlleDrikker()'
 *  @see   'automatDrikkeKjop(...)'
 */
void kjopDrikke()  {
    int kjopeAvNr;                 //  Drikkenummeret det kj�pes EN flaske av.

    skrivAlleDrikker();            //  Skriver HELE automatens innhold.
    kjopeAvNr = lesInt("Kj�p av nr", 0, MAXDRIKKER);
    if (kjopeAvNr)                 //  Noe annet enn 0 (null) er skrevet:
        automatDrikkeKjop(&gDrikker[kjopeAvNr-1]);   //  Kj�per EN flaske.
    else
        cout << "\n\tOK - ingen kj�p skjer.\n";
}


/**
 *  Brukeren tilbys � fylle p� flere flasker av en eller annen drikke.
 *
 *  @see   'skrivAlleDrikker()'
 *  @see   'automatDrikkePaafyll(...)'
 */
void paafyllAvDrikke()  {
    int merAvNr;               //  Drikkenummeret det kommer flere flasker av.

    skrivAlleDrikker();        //  Skriver HELE automatens innhold.
    merAvNr = lesInt("P�fyll av nr", 0, MAXDRIKKER);
    if (merAvNr)               //  Noe annet enn 0 (null) er skrevet:
        automatDrikkePaafyll(&gDrikker[merAvNr-1]);  //  Flere flasker.
    else
        cout << "\n\tOK - ingen p�fylling.\n";
}


/**
 *  Skriver ut HELE automatens n�v�rende innhold (ALLE drikkenes status).
 *
 *  @see   'automatDrikkeSkrivData(...)'
 */
void skrivAlleDrikker()  {
    for (int i = 0;  i < MAXDRIKKER;  i++) {    //  G�r gjennom ALLE drikkene:
        cout << '\t' << setw(2) << i + 1 << ":  ";
        automatDrikkeSkrivData(&gDrikker[i]);   //  Skriver EN drikke.
    }
}


/**
 *  Skriver brukerens valgmuligheter:
 */
void skrivMeny()  {
    cout << "\nF�lgende kommandoer er tilgjengelig:\n"
         << "\tK = Kj�p en drikke\n"
         << "\tP = P�fyll av drikke\n"
         << "\tE = Endre en drikkes data\n"
         << "\tQ - Quit / avslutt\n";
}
