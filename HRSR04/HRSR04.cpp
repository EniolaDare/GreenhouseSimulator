#include "HRSR04.h"
#include <cstdlib>

int HRSR04::getDuration(){
    return duration;
}

double HRSR04::getDist(){
    return (duration / 2.0) * 0.0343;
}

void HRSR04::genRandDist(){
    duration = (rand() % 271) + 30;
}