
#include <string>
#include <iostream>
#include <vector>


const int ANTSTOPP = 11; ///< Totalt antall ulike busstopp.

const vector <string> gBusstopp = ///< Navn på alle busstopp.
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



/**
 * ! får ikke til å printe ut minuttene
 * 
 * @return int 
 */
int main() {

    int stop = 4;

    for(int i = 0; i < 11; i++) {
        std::cout << std::endl;
        if(gMinutter[stop][i] != 0) {
            std::cout << gBusstop[i];
        }
    }

}


    int stop,
        nyttStopp;

    vector<string> nyeStopp;

    rute.ruteNr = gRuter.size()+1;
    skrivStopp();
    stop = lesInt("\t\nVelg startsted: \n", 1, 11);
                        // Legger inn første stopp
    rute.stopp.push_back(gBusstopp[stop - 1]);

                        //skriver neste lovlige stopp
    skrivNesteStoppesteder(stop - 1);
    
                        //gjør det samme som skrivNesteStoppesteder()
                        // men denne legger dem i egen vector slik at 
                        // jeg kan velge bare dem som er tilgjenglig
    for(int i = 0; i < ANTSTOPP; i++) {
        cout << "\n";
        if(gMinutter[stop-1][i] != 0) {
            nyeStopp.push_back(gBusstopp[i]);
        }
    }

    nyttStopp = lesInt("\nSkriv inn neste stopp nummer: ", 0, ANTSTOPP);
    rute.stopp.push_back(nyeStopp[nyttStopp]);
    rute.totMin += gMinutter[stop][nyttStopp];
    nyeStopp.clear();                         //  Alle PEKERNE slettes.
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
        nyeStopp.clear();                     //  Alle PEKERNE slettes.
   }*/

   void skrivNesteStoppesteder(const int stopp) {
    int nr = 0;

    for(int i = 0; i < ANTSTOPP; i++) {
        cout << endl;
        if(gMinutter[stopp][i] != 0) {
            cout << i+1 << ".  "<< gMinutter[stopp][i] << "min " << gBusstopp[i];
        }
    }


}