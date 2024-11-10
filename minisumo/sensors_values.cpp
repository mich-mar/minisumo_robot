#include "sensors_values.h"

virables::virables() {
    czulosc = 50; //mm

    tof_debug = 25;

    // docelowo na ring - maks_distance = 300
    maks_distance = 300;

    //  docelowo na rinhg - border_color = 800
    // do testów - border_color = 0
    // black = 950
    // white = 550

    border_color = 0;
}
