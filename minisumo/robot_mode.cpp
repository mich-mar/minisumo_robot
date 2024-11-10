#include "robot_mode.h"


void robot_mode::choose_mode() {
    // wybiera tryb w zależności od wybranej pozycji w menu
    switch (get_menu_state()) {
        case 4:
            turn_led_on(RED);
            turn_led_off(BLUE);

            if (get_starter_status()) {
                if (!is_same_state())
                    start_sequence();

                fight();
            } else
                motor_stop();
            break;

        case 3:
            turn_led_on(RED);
            turn_led_off(BLUE);

            if (!is_same_state()) {
                motor_stop();
                delay(5000);
                start_sequence();
            }

            fight();
            break;

        case 2:
            turn_led_on(RED);
            turn_led_off(BLUE);

            motor_stop();
            break;

        case 1:
            turn_led_off(RED);
            turn_led_off(BLUE);

            drive_forward(255);
            break;

        case 0:
            turn_led_off(RED);
            turn_led_on(BLUE);

            motor_stop();
            break;
    }

}


void robot_mode::print_data() {
    robot::print_data();
    Serial.print("Menu: ");

    switch (get_menu_state()) {
        case 0:
            Serial.println("0 - robot stop");
            break;

        case 1:
            Serial.println("1 - clean wheels");
            break;

        case 2:
            Serial.println("2 - wait for button");
            break;

        case 3:
            Serial.println("3 - button fight");
            break;

        case 4:
            Serial.println("4 - starter fight");
            break;
    }

    Serial.println("=========================");
}
