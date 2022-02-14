/**
 * @file 7-2.cpp
 * 
 * enkelt lite program som viser en enkel klasse med funksjoner definert 
 * utenfor klassen
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>     // cout / cin
#include <cmath>        // pow
using namespace std;

class Circle {

    private:
        float radius;

    public:
        void setRadius(float r);
        float calcArea() const;

};

/**
 * hovedprogram
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

void Circle::setRadius(float r) {
    radius = r;
}

float Circle::calcArea() const {
    return 3.14f * pow(radius, 2);
}