#ifndef ROBOT_MODE_H
#define ROBOT_MODE_H

#include <Arduino.h>
#include <Wire.h>
#include "robot.h"
#include "button_menager.h"


// ================= robot_mode ==================
// - klasa do zarządzania działaniami robota
// - wybiera odpowiedni tryb, na podstawie 
//   wybranej pozycji z menu
// ===============================================
class robot_mode : public robot, public button_menager {
public:
    // steruje robotem w zależności od wybranej pozycji w menu
    void choose_mode();

    // wyświetla odczyt z czujników i wybraną pozycje w menu
    void print_data() override;
};

#endif
