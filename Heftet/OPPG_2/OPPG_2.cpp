/**
 *   OPPG_2.cpp
 *
 *   Utgangspunkt i eks 17 fra prog1001, kutter vekk all bruk av array
 * 
 * gav opp, skjønner ikke helt hva som skal gjøres videre, hopper til oppg 4
 *
 *   @file     OPPG_2.cpp
 *   @author   Frode Haug, NTNU
 */


#include <iostream>              //  Samme som stdio.h
#include <iomanip>               //  setw
#include <cctype>                //  toupper
using namespace std;             //  Slipper da å bruke std::cout / std::cin


const int MINTEMP   = -70;   ///<  Absolutt laveste mulige temperatur.
const int MAXTEMP   =  70;   ///<  Absolutt høyeste mulige temperatur.
const int MAXNEDBOR = 200;   ///<  Absolutt høyeste mulige nedbør pr.døgn.
const int MINDAGER  =   5;   ///<  Minimum antall dager i en måned.
const int MAXDAGER  =  31;   ///<  Maksimum antall dager i en måned.

/**
 *  Hovedprogrammet:
 */
int main ()  {
  char svar;                 //  Brukersvar til om vil fortsette eller ei.
  int  antDager,             //  Antall dager i aktuell måned.
       min,                  //  Min.temp EN gitt dag.
       max,                  //  Max.temp EN gitt dag.
       nedbor,               //  Nedbør EN gitt dag.
       totMin,               //  TOTALT min.grader i aktuell måned.
       totMax,               //  TOTALT max.grader i aktuell måned.
       totNedbor;            //  TOTALT nedbør i aktuell måned.
  int  alleMin[MAXDAGER],    //  ALLE min.temper i måneden.
       alleMax[MAXDAGER],    //  ALLE max.temper i måneden.
       alleNedbor[MAXDAGER]; //  ALL nedbør i måneden.

  cout << "\nLese inn værdata for en måned (J/n): ";   //  Kjøre programmet?
  cin >> svar;

  while (svar != 'N'  &&  svar != 'n')  { //  Så lenge ønsker (IKKE svart 'N'):
     do {                    //  Leser antall dager i måneden (28-31):
        cout << "Antall dager i måneden ( "<< MINDAGER << "-" << MAXDAGER << " ):";
        cin >> antDager;
     } while (antDager < MINDAGER  ||  antDager > MAXDAGER);

     for (int i = 0;  i < antDager;  i++)  { //  Går gjennom HELE måneden:
         cout << "\nDag nr." << setw(2) << i+1 << ":\n";

         do {                             //  Leser korrekt min.temp dag nr.i:
           cout << "\tMinimumstemp (" << setw(2) << MINTEMP << " til " << setw(2) << MAXTEMP << "): ";
           cin >> min;
         } while(min < MINTEMP ||  min > MAXTEMP);
         alleMin[i] = min;                //  Lagrer unna innlest verdi.

         do {                             //  Leser korrekt max.temp dag nr.i:
            cout << "\tMaksimumstemp (" << setw(2) << min << " til " << setw(2) << MAXTEMP << "): ";
            cin >> max;
         } while(max < min  ||  max > MAXTEMP);
         alleMax[i] = max;                //  Lagrer unna innlest verdi.

         do {                             //  Leser korrekt nedbør dag nr.i:
            cout << "\tNedbør (0 til " << MAXNEDBOR << "): ";
            cin >> nedbor;
         } while(nedbor < 0  ||  nedbor > MAXNEDBOR);
         alleNedbor[i] = nedbor;          //  Lagrer unna innlest verdi.
     }

 	 totMin = totMax = totNedbor = 0;          //  Nullstiller totalsummer.
     for (int i = 0;  i < antDager;  i++)  { //  Går gjennom HELE måneden:
         totMin    += alleMin[i];            //  Oppsummerer tot.min.
         totMax    += alleMax[i];            //  Oppsummerer tot.max.
         totNedbor += alleNedbor[i];         //  Oppsummerer tot.nedbør.
     }
                                    //  Skriver gjennomsnitter og EN totalsum:
     cout << "\n\nGjennomsnittlig min.temp: " << right << fixed << setprecision(2) << static_cast < float > (totMin/antDager) << " grader C\n";
     cout << "Gjennomsnittlig max.temp: " << fixed << setprecision(2) << static_cast < float > (totMax/antDager) << " grader C\n";
     cout << "Gjennomsnittlig nedbør: " << fixed << setprecision(2) << static_cast < float > (totNedbor/antDager) << " mm\n";
     cout << "Total nedbør i måneden:   " << totNedbor <<" mm\n";
                                             //  Kjøre programmet igjen?
     cout << "\nLese inn værdata for en måned til (J/n): ";
     cin >> svar;
  }

  cout << "\n\n\nHa en fortsatt god (vær(syk))dag!\n\n";

  return 0;
}