#include "button_menager.h"


void button_menager::read_button() {
    reading = !digitalRead(pins.BUTTON);

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == HIGH) {
                curentState = !curentState;
            }
        }
    }

    lastButtonState = reading;
}

void button_menager::menu() {
    read_button();

    last_choice = choice;

// jeśli przycisk był wciśnięty to zmienia menu
    if (curentState == HIGH) {
        if (choice < 4)
            choice++;
        else
            choice = 0;

        curentState = LOW;
    }
}

int const button_menager::get_menu_state() {
    return choice;
}

bool const button_menager::is_same_state() {
    return last_choice == choice;
}
 
