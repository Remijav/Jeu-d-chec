#include <iostream>
#include <string>
#include "echiquier.h"


int main(){

    echiquier E1;

    E1.depart();
    E1.affichage(std::cout);
    E1.jouer();


    return 0;
}
