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

struct Tid storst (
    const struct Tid tid1,
    const struct Tid tid2
);