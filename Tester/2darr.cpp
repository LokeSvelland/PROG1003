
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