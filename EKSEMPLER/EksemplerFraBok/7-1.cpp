/**
 * @file 7-1.cpp
 * 
 * ! start på classer / objekter
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>     // cout / cin
#include <cmath>        // pow
using namespace std;

/**
 * Circle class DECLARATION
 * 
 */
class Circle {

    private:            // Data i private endres ikke direkte av bruker
        float radius;

    public:             // kun funksjoner er offentlig
        void setRadius(float r) {
            radius = r;
        }

    float calcArea()    const   {           // const da funksjonen ikke endrer 
                                            // bare leser data
        return 3.14F * pow(radius, 2);      // pow opphøyer
    }
};

/**
 * hovedprogrammet
 * 
 */
int main() {

    Circle circle1,
           circle2;

    
                        // kaller funksjon for hver sirkel
    circle1.setRadius(1);
    circle2.setRadius(2.5);


    cout << "The area of circle1 is " << circle1.calcArea() << '\n';
    cout << "The area of circle2 is " << circle2.calcArea() << '\n';

    return 0;

}