# Projekt - minisumo


### Założenia projektu:

 Głównym założeniem projektu jest napisanie kodu robota z jak najmniejszymi opóźnieniami i wykluczenie podejmowania niepożądanych działań w trakcie walki.
- Program będzie pisany w środowisku **Arduino IDE** oraz będzie korzystać z bibliotek służących do odczytu danych z czujników i obsługi hardware płytki **Raspberry Pi Pico** (ustawianie sygnałów PWM, stanów wysokich i niskich na pinach wyjściowych mikrokontrolera etc.). 
- Robot posiada czujniki odległości (tzw. TOF) oraz czujniki odbiciowe (rozróżniają kolor podłoża). Program będzie musiał wczytywać wartości wskazywane przez czujniki, analizować je oraz podejmować na ich bazie decyzje co do przebiegu walki.
- Musi on również walczyć według zasad zawodów:
-- Nie może wystartować przed otrzymaniem sygnału z pilota sędziego. 
-- Nie może wypaść z ringu.



### Dodatkowe cele projektu:
> Pod warunkiem, że poprzednie założenia będą działać poprawnie, zaimplementuje kolejne, ułatwiające interakcje zawodnika z robotem.

- Robot za pomocą kolorowych diód, będzie informować zawodnika o aktualnych działaniach (np. "nie widzę przeciwnika - szukam", lub "widzę białą krawędź ringu - zawracam").
- Będzie możliwość wystartowania robota za pomocą przycisku.
- Implementacja bardziej złożonych algorytmów szukania i walki.