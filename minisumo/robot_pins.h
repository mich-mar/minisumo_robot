#ifndef ROBOT_PINS_H
#define ROBOT_PINS_H

#include <Arduino.h>
#include <Wire.h>

// ================= robot_pins ==================
// - struktura przechowuje nr pinów, do których
//   podłączone są dane komponenty
// ===============================================
struct robot_pins {
    //piny I2C
    int I2C0_SDA, I2C0_SCL;

    //piny xshut do czujników tof (wszystkie podpiete pod GPIO 2-5)
    int XSHUT_2, XSHUT_3, XSHUT_4, XSHUT_5;

    //piny sterownika do silników
    int STER21, STER20, STER19, STER18;

    //piny diod i przycisku
    int BUTTON, RED_DIODE, BLUE_DIODE;

    //wejscia czujnikow podloza QRD
    int QRD_28, QRD_27, QRD_26;

    //wejscie startera
    int STARTER;

    // konstruktor przypisujący nr pinów
    robot_pins();
};

#endif
