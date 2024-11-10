#ifndef SENSOR_VALUES_H
#define SENSOR_VALUES_H

#include <Arduino.h>
#include <Wire.h>

// ================ sensor_values ================
// - struktura przechowuje odczyty z czujników 
//   i ich minimum
// ===============================================
struct sensors_values {
    int Tof_Front_R;
    int Tof_Front_L;
    int Tof_Side_R;
    int Tof_Side_L;
    int Qrd_Back;
    int Qrd_Right;
    int Qrd_Left;
    int Tof_min;
};


// ================== virables ===================
// - struktura przechowuje wartości potrzebne do 
//   sprawdzania porzydatności odczytów w walce
// ===============================================
struct virables {
    int czulosc; //mm
    int maks_distance; //mm
    int border_color;
    int tof_debug; //mm

    // konstruktor struktury zapisujący stałe
    virables();
};

#endif
