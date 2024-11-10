#include "robot_pins.h"

robot_pins::robot_pins() {
    I2C0_SDA = 0;
    I2C0_SCL = 1;

    XSHUT_2 = 3;
    XSHUT_3 = 4;
    XSHUT_4 = 5;
    XSHUT_5 = 6;

    STER21 = 21;
    STER20 = 20;
    STER19 = 19;
    STER18 = 18;

    BUTTON = 16;
    RED_DIODE = 10;
    BLUE_DIODE = 25;

    QRD_27 = 27;
    QRD_26 = 26;
    QRD_28 = 28;

    STARTER = 17;
};
