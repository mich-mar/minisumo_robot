#ifndef ROBOT_H
#define ROBOT_H

#include <VL53L0X.h>
#include "sensors_values.h"
#include "robot_pins.h"

// enum do ustalania pozycji przeciwnika
enum pos {
    SIDE_L, FRONT_L, FRONT_R, FRONT, SIDE_R, NOWHERE, BORDER, OTHER
};

// enum do kolorów diod
enum color {
    BLUE, RED
};


// ================= klasa robot =================
// - klasa przechowuje wartości z czujników,
//   podejmuje decyzje o walce i steruje robotem
// ===============================================
class robot {
    // tablica klass czujników VL53L0X
    VL53L0X czujnik_tof[4];

    // numery pinów
    const robot_pins pins;

    // stałe wartości potrzebne do walki
    const virables values;

    // struktura przechowująca odczyty z czujników
    sensors_values data;

public:
    // konstruktor, ustawia pinout (wejścia i wyjścia pinów)
    robot();

    // ustawia wejścia i wyjścia na pinach
    void const set_pinout();

    // inicjalizuje czujniki odległości
    void const initialize_tof();

    // odczytuje wartości z czujników i zapisuje do "data"
    void read_sensors();

    int const reading_debug(int x);

    // czyta czujniki i wyświetla dane na serial porcie
    virtual void print_data();

    // funkcja odpowiadająca za walkę
    void fight();

    // funkcja analizująca odczyty z czujników
    // i zwaracająca pozycję przeciwnika
    pos where_enemy();

    // funkcja sprawdza czy robot jest na krawędzi
    // ringu (białym kolorze)
    bool is_on_white();

    // funkcje ustawiające stany wysokie lub/i sygnały PWM
    // na pinach obsługujących sterownik do silników
    void const drive_forward(int speed);

    void const drive_forward_L(int speed, int ratio);

    void const drive_forward_R(int speed, int ratio);

    void const drive_back(int speed);

    void const turn_right(int speed);

    void const turn_left(int speed);

    void const motor_stop();

    // funkcje ułatwiające przejrzystość kodu,
    // włączające i wyłączające diody
    void const turn_led_on(color c);

    void const turn_led_off(color c);

    // funkcja szukająca przeciwnika,
    // tzw. "myszkowanie" na boki
    void looking_for_enemy();

    // funkcja pomocnicza, sprawdzająca czy robot nie widzi przeciwnika
    // i nie jest na krawędzi
    bool no_enemy_and_border();

    // funkcja do wycofywania się z granicy ringu
    void back_off_from_border();

    // funkcja zwracająca stan
    bool const get_starter_status();

    // funkcja do sekwencji startowej
    void start_sequence();
};

#endif
