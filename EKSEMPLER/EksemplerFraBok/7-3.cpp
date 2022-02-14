/**
 * @file 7-3.cpp
 * 
 * her implementeres en rektangel klasse
 * 
 * litt større eksempel som viser set...(MUTATOR) og get...(ACCESSOR) funksjonr
 * 
 * 
 */

#include <iostream>     // cout / cin
using namespace std;


/**
 * rektangel klasse deklarasjon med lengde og bredde
 * 
 */
class Rectangle {

    private:
        float length;
        float width;
    
    public:
        float calcArea()    const;
        float getLength()   const;
        float getWidth()    const;
        void  setLength(float len);
        void  setWidth(float w);
};

/**
 * hovedprogram
 * 
 */
int main() {

    Rectangle box;
    float boxLength, boxWidth;

    cout << "This program will calculate the area of a rectangle.\n";
    cout << "What is the length? ";     cin >> boxLength;
    cout << "What is the Width? ";      cin >> boxWidth;


    box.setLength(boxLength);
    box.setWidth(boxWidth);


    cout << "\nHere is the rectangle's data:\n";
    cout << "" << box.getLength() << "\n";
    cout << "" << box.getWidth() << "\n";
    cout << "" << box.calcArea() << "\n\n";

    return 0;
}


/**
 * @return  Rektangelets areal
 * 
 */
float Rectangle::calcArea()     const {
    return length * width;
}

/**
 * @return Rektangelets lengde
 * 
 */
float Rectangle::getLength()    const {
    return length;
}

/**
 * @return Rektangelets bredde
 * 
 */
float Rectangle::getWidth()     const {
    return width;
}

/**
 * @param - len - Objektets 'Length' blir satt  til len eller 1.0F
 * 
 */
void Rectangle::setLength(float len) {
    if (len >= 00.F)
        length = len;
    else {
        length = 1.0F;
        cout << "Invalid length. Using a default value of 1.0\n";
    }
}

/**
 * @param - w - Objektets 'width' blir satt  til w eller 1.0F
 * 
 */
void Rectangle::setWidth(float w)  {
    if (w >= 00.F)
        width = w;
    else {
        width = 1.0F;
        cout << "Invalid width. Using a default value of 1.0\n";
    }
}