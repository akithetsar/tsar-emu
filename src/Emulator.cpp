//
// Created by akith on 10/27/2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "../h/Emulator.hpp"


void Emulator::bootEmu() {

    //Internal test, real test in boot ROM program
    if (this->cartridge->verifyHeader()){
        std::cout << "Header good";
    }
    else{
        std::cout << "Header bad";
    }

    //Run boot ROM

}