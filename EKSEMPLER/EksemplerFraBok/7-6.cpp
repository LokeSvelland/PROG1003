/**
 * @file 7-6.cpp
 * 
 * Dette programmet viser bruken av overloaded constructors og destructors
 * 
 */


#include <iostream>
#include <iomanip>
using namespace std;


class Sale {
    private:
        float taxRate;

    public:
        Sale() {                // default constructor
            taxRate = 0.0F;
        }

        Sale(float rate) {      //constructor with one parameter
            taxRate = rate;
        }

        ~Sale() {               // destructor bruk av ~
            cout << "Og der sluttet DET objektet å eksistere.\n";
        }

        float clacSaleTotal(float cost) const   {
            return(cost + (cost*taxRate));
        }
  /**
   * Constructor er en medlemsfunksjon, likenavnet med klassen
   * som kjøres/utføres automatisk når et objekt blir laget
   * constructorer kan, og blir ofte overloaded
   * de kan (så lenge de kalles automatisk) aldri si 'return' om noe
   * se EKS_02.cpp med alle string-klassens ulike constructorer
   * 
   */

  /**
   * Destuctor kjøres i det et objekt slutter å eksistere "dør"
   * Dens hovedoppgave er å frigjøre memory som har blitt allokert/
   * satt avmens objektet eksisterte/fantes/levde.
   * Den kan verken si 'return', overloades eller ta parametere
   * 
   */

};


/**
 * hovedprogram
 * 
 */
int main() {
    Sale cashier1(0.06F),
         cashier2;

    

    cout << fixed << showpoint << setprecision(2);

    cout << "With a 0.06 sales tax rate, the total\n";
    cout << "of the $24.95 sale is $";
    cout << cashier1.clacSaleTotal(24.95) << '\n';

    cout << "\nOn a tax-exempt purchase, the total\n";
    cout << "of the $24.95 sale us, of course, $";
    cout << cashier2.clacSaleTotal(24.95) << "\n\n";

    return 0;

}