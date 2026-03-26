#include "LM35.h"
#include <cstdlib>

int LM35::getAdcData(){
    return adcData;
}

double LM35::getTemp(){
    return (adcData * 5.0 / 1024.0) * 100.0;
}

void LM35::genRandTemp(){
    adcData = (rand() % 51) + 30;
}