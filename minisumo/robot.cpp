#include "robot.h"

robot::robot() {
    set_pinout();
    motor_stop();
};


void const robot::initialize_tof() {
    // reset wszystkich czujników
    digitalWrite(pins.XSHUT_2, LOW);
    digitalWrite(pins.XSHUT_3, LOW);
    digitalWrite(pins.XSHUT_4, LOW);
    digitalWrite(pins.XSHUT_5, LOW);
    delay(20);
    digitalWrite(pins.XSHUT_2, HIGH);
    digitalWrite(pins.XSHUT_3, HIGH);
    digitalWrite(pins.XSHUT_4, HIGH);
    digitalWrite(pins.XSHUT_5, HIGH);
    digitalWrite(pins.XSHUT_2, LOW);
    digitalWrite(pins.XSHUT_3, LOW);
    digitalWrite(pins.XSHUT_4, LOW);
    digitalWrite(pins.XSHUT_5, LOW);

    // ustawienie pinów dla pierwszego interfejsu i2c
    Wire.setSDA(pins.I2C0_SDA);
    Wire.setSCL(pins.I2C0_SCL);

    // inicjalizacja interfeju i2c
    Wire.begin();

    // ustawienie interfejsów dla czujników
    // wszystkie czujniki podłączone do wspólnego interfejsu
    (czujnik_tof[0]).setBus(&Wire);
    (czujnik_tof[1]).setBus(&Wire);
    (czujnik_tof[2]).setBus(&Wire);
    (czujnik_tof[3]).setBus(&Wire);

    // ustawianie adresów czujników
    int gap = 50;
    digitalWrite(pins.XSHUT_2, HIGH);
    (czujnik_tof[0]).setAddress(0x32);
    delay(gap);
    digitalWrite(pins.XSHUT_3, HIGH);
    (czujnik_tof[1]).setAddress(0x33);
    delay(gap);
    digitalWrite(pins.XSHUT_4, HIGH);
    (czujnik_tof[2]).setAddress(0x34);
    delay(gap);
    digitalWrite(pins.XSHUT_5, HIGH);
    (czujnik_tof[3]).setAddress(0x35);

    // jeśli podczas czasu ustawionego dla
    // jednego pomiaru nic nie to zwraca max
    // złoty środek dla set_Timeout = 20
    int set_Timeout = 20;
    (czujnik_tof[0]).setTimeout(set_Timeout);
    (czujnik_tof[1]).setTimeout(set_Timeout);
    (czujnik_tof[2]).setTimeout(set_Timeout);
    (czujnik_tof[3]).setTimeout(set_Timeout);

    (czujnik_tof[0]).init(false);
    (czujnik_tof[1]).init(false);
    (czujnik_tof[2]).init(false);
    (czujnik_tof[3]).init(false);

    // mminimalny timing budget to 20 ms (standarodow 33 ms)
    int MeasurmentTimeBudget = 20000;
    (czujnik_tof[0]).setMeasurementTimingBudget(MeasurmentTimeBudget);
    (czujnik_tof[1]).setMeasurementTimingBudget(MeasurmentTimeBudget);
    (czujnik_tof[2]).setMeasurementTimingBudget(MeasurmentTimeBudget);
    (czujnik_tof[3]).setMeasurementTimingBudget(MeasurmentTimeBudget);

    (czujnik_tof[0]).startContinuous();
    (czujnik_tof[1]).startContinuous();
    (czujnik_tof[2]).startContinuous();
    (czujnik_tof[3]).startContinuous();

}

int const robot::reading_debug(int x) {
    // zwraca max dla będnych wartości
    if (x <= values.tof_debug)
        return 8190;
    else
        return x;
}

void robot::read_sensors() {
    // zapisuje odczyty do struktury
    data.Tof_Front_R = reading_debug((czujnik_tof[0]).readRangeSingleMillimeters());
    data.Tof_Front_L = reading_debug((czujnik_tof[2]).readRangeSingleMillimeters());
    data.Tof_Side_R = reading_debug((czujnik_tof[1]).readRangeSingleMillimeters() + 5);
    data.Tof_Side_L = reading_debug((czujnik_tof[3]).readRangeSingleMillimeters());

    // szuka min i też zapisuje
    data.Tof_min = min(min(data.Tof_Front_R, data.Tof_Front_L), min(data.Tof_Side_R, data.Tof_Side_L));
}

void robot::print_data() {
    read_sensors();

    data.Qrd_Right = analogRead(pins.QRD_28);
    data.Qrd_Left = analogRead(pins.QRD_27);

    Serial.println("========= Data: =========");
    Serial.print("Side left: ");
    Serial.println(data.Tof_Side_L);
    Serial.print("Side right: ");
    Serial.println(data.Tof_Side_R);
    Serial.print("Front right: ");
    Serial.println(data.Tof_Front_R);
    Serial.print("Front left: ");
    Serial.println(data.Tof_Front_L);

    Serial.print("Floor sensor right: ");
    Serial.println(data.Qrd_Right);
    Serial.print("Floor sensor left: ");
    Serial.println(data.Qrd_Left);
    Serial.println("=========================");
}

void const robot::drive_forward(int speed) {
    //rigth wheel
    digitalWrite(pins.STER21, LOW);
    analogWrite(pins.STER20, speed);
    //left wheel
    digitalWrite(pins.STER19, LOW);
    // redukcja pwm ponieważ silniki są słabej jakości
    // i różnią się rpm
    analogWrite(pins.STER18, speed / 2);
}

void const robot::drive_forward_L(int speed, int ratio) {
    //rigth wheel
    digitalWrite(pins.STER21, LOW);
    analogWrite(pins.STER20, speed);
    //left wheel
    digitalWrite(pins.STER19, LOW);
    analogWrite(pins.STER18, speed / ratio);
}

void const robot::drive_forward_R(int speed, int ratio) {
    //rigth wheel
    digitalWrite(pins.STER21, LOW);
    analogWrite(pins.STER20, speed / ratio);
    //left wheel
    digitalWrite(pins.STER19, LOW);
    analogWrite(pins.STER18, speed);
}

void const robot::drive_back(int speed) {
    //left wheel
    analogWrite(pins.STER21, speed);
    digitalWrite(pins.STER20, LOW);
    //right wheel
    analogWrite(pins.STER19, speed);
    digitalWrite(pins.STER18, LOW);
}


void const robot::turn_right(int speed) {
    //left wheel
    analogWrite(pins.STER21, speed);
    digitalWrite(pins.STER20, LOW);
    //right wheel
    digitalWrite(pins.STER19, LOW);
    analogWrite(pins.STER18, speed);
}

void const robot::turn_left(int speed) {
    //left wheel
    digitalWrite(pins.STER21, LOW);
    analogWrite(pins.STER20, speed);
    //right wheel
    analogWrite(pins.STER19, speed);
    digitalWrite(pins.STER18, LOW);
}

void const robot::motor_stop() {
    //left wheel
    digitalWrite(pins.STER21, LOW);
    digitalWrite(pins.STER20, LOW);
    //right wheel
    digitalWrite(pins.STER19, LOW);
    digitalWrite(pins.STER18, LOW);
}

bool robot::is_on_white() {
    // odczytuje wartość analogową czujników podłoża
    data.Qrd_Left = analogRead(pins.QRD_26);
    data.Qrd_Right = analogRead(pins.QRD_27);


    if (data.Qrd_Right < values.border_color || data.Qrd_Left < values.border_color)
        return true;
    else
        return false;
}

pos robot::where_enemy() {
    read_sensors();

    //zwraca enum'y w zależności od danych

    if (data.Tof_min > values.maks_distance) {
        if (is_on_white())
            return BORDER;
        else
            return NOWHERE;
    }

    if ((data.Tof_Front_R < values.maks_distance) && (data.Tof_Front_L < values.maks_distance))
        if (abs(data.Tof_Front_R - data.Tof_Front_L) < values.czulosc)
            return FRONT;

    if (data.Tof_min == data.Tof_Front_R)
        return FRONT_R;

    if (data.Tof_min == data.Tof_Front_L)
        return FRONT_L;

    if (data.Tof_min == data.Tof_Side_R)
        return SIDE_R;

    if (data.Tof_min == data.Tof_Side_L)
        return SIDE_L;

    return OTHER;
}


void robot::fight() {
    // podejmuje decyzje o walce na bazie położenia przeciwnika
    switch (where_enemy()) {

        case FRONT:
            drive_forward(255);
            break;

        case FRONT_R:
            drive_forward_R(255, 3);
            break;

        case FRONT_L:
            drive_forward_L(255, 4);
            break;

        case SIDE_R:
            turn_right(255);
            break;

        case SIDE_L:
            turn_left(255);
            break;

        case BORDER:
            back_off_from_border();
            break;

        case NOWHERE:
            turn_led_on(BLUE);
            looking_for_enemy();
            break;

        case OTHER:
            turn_led_on(BLUE);
            motor_stop();
            break;
    }
}

bool const robot::get_starter_status() {
    if (digitalRead(pins.STARTER) == HIGH)
        return true;
    else
        return false;
}

const void robot::set_pinout() {
    //inicjalizacja wyjść pinów
    pinMode(pins.XSHUT_2, OUTPUT);
    pinMode(pins.XSHUT_3, OUTPUT);
    pinMode(pins.XSHUT_4, OUTPUT);
    pinMode(pins.XSHUT_5, OUTPUT);
    pinMode(pins.STER21, OUTPUT);
    pinMode(pins.STER20, OUTPUT);
    pinMode(pins.STER19, OUTPUT);
    pinMode(pins.STER18, OUTPUT);
    pinMode(pins.BUTTON, INPUT_PULLUP);
    pinMode(pins.RED_DIODE, OUTPUT);
    pinMode(pins.BLUE_DIODE, OUTPUT);
    pinMode(pins.STARTER, INPUT);
    pinMode(pins.QRD_26, INPUT);
    pinMode(pins.QRD_27, INPUT);
    pinMode(pins.QRD_28, INPUT);
}

void const robot::turn_led_on(color c) {
    switch (c) {
        case BLUE:
            digitalWrite(pins.BLUE_DIODE, HIGH);
            break;

        case RED:
            digitalWrite(pins.RED_DIODE, HIGH);
            break;
    }
}

void const robot::turn_led_off(color c) {
    switch (c) {
        case BLUE:
            digitalWrite(pins.BLUE_DIODE, LOW);
            break;

        case RED:
            digitalWrite(pins.RED_DIODE, LOW);
            break;
    }
}

void robot::looking_for_enemy() {
    turn_led_on(BLUE);

    while (no_enemy_and_border()) {
        for (int i = 0; i < 20; i++) {
            if (no_enemy_and_border()) {
                turn_right(255);
            } else {
                turn_led_off(BLUE);
                return;
            }
        }

        for (int i = 0; i < 15; i++) {
            if (no_enemy_and_border()) {
                turn_left(255);
            } else {
                turn_led_off(BLUE);
                return;
            }
        }
    }
    turn_led_off(BLUE);
}

bool robot::no_enemy_and_border() {
    return (where_enemy() == NOWHERE && !is_on_white());
}

void robot::back_off_from_border() {
    turn_led_on(BLUE);

    for (int i = 0; i < 50; i++) {
        if (where_enemy() == NOWHERE) {
            drive_back(255);
        } else {
            return;
        }
    }

    for (int i = 0; i < 20; i++) {
        if (where_enemy() == NOWHERE) {
            turn_right(255);
        } else {
            return;
        }
    }
    turn_led_off(BLUE);
}

void robot::start_sequence() {

    for (int i = 0; i < 11; i++) {
        if (no_enemy_and_border()) {
            turn_right(255);
        } else {
            return;
        }
    }

    for (int i = 0; i < 25; i++) {
        if (no_enemy_and_border()) {
            drive_forward(255);
        } else {
            return;
        }
    }
}
