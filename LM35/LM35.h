#ifndef LM35_H
#define LM35_H

class LM35 {
    public:
        // Default constructor
        LM35() : adcData(0) {}

        // Parameterised constructor
        LM35(int adcData) : adcData(adcData) {}

        // Convert ADC data to temperature
        double getTemp();

        int getAdcData();

        // Generate random ADC value between 30 and 80
        void genRandTemp();

    private:
        int adcData;
};

#endif 