#ifndef HRSR04_H
#define HRSR04_H

class HRSR04 {
    public:
        // Default constructor
        HRSR04() : duration(200) {}

        // Parameterised constructor
        HRSR04(int duration) : duration(duration) {}

        // Convert duration to distance
        double getDist();

        int getDuration();

        // Generate random duration value between 30 and 300
        void genRandDist();

    private:
        int duration;
};

#endif