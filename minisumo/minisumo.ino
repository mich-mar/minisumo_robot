#include "robot_mode.h"

robot_mode minisumo;

void setup() {
//Serial.begin(11500);
    minisumo.initialize_tof();
}

void loop() {
//minisumo.print_data();

    minisumo.menu();
    minisumo.choose_mode();
}
