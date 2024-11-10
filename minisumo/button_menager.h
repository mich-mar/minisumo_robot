#ifndef BUTTON_MENAGER_H
#define BUTTON_MENAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "robot_pins.h"


// =============== button_menager ================
// - klasa do poprawnego odczytu z przycisku
//   i rozwiązywania problemów z drganiem styków
// - obsługuje poruszanie się pozycjach w menu:
//    0) robot nie działa
//    1) czyszczenie kół
//    2) oczekiwanie na przycisk
//    3) walka z przycisku
//    4) walka ze startera
// ===============================================
class button_menager {
    // struktura z nr pinów
    robot_pins pins;

    // pomocnicze zmienne do wywołania start_sequence();
    int choice = 0;
    int last_choice = 0;

    // zmienne do eliminacji błędów odczytu
    int curentState = LOW;                 // aktualny stan
    int buttonState;                       // aktualny odczyt z przycisku
    int lastButtonState = LOW;             // poprzedni odczyt z przycisku
    unsigned long lastDebounceTime = 0;    // kiedy ostatnio był wciśnięty
    unsigned long debounceDelay = 50;      // czas po którym nie powinno już być błędów
    int reading;                           // odczyt


public:
    // odczyt przycisku
    void read_button();

    // getter zwracający aktualny stan meu
    int const get_menu_state();

    // funkcja zmieniająca wybór w menu
    void menu();

    // funkcja sprawdzająca czy menu się zmieniło
    bool const is_same_state();
};

#endif
