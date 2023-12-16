# windowed-couscous

Definicje:
- PrZ: przekaźnik zwierający fazę na zacisku siłownika odpowiadającym za zamknięcie okna
- PrO: przekaźnik zwierający fazę na zacisku siłownika odpowiadającym za otwarcie okna
- Tz: temperatura zadana, przy której następuje zmiana stanu okna
- To: temperatura otoczenia w którym działa urządzenie
- Pi: przycisk odpowiadający za inkrementację temperatury zadanej (Tz)
- Pd: przycisk odpowiadający za dekrementację temperatury zadanej (Tz)
- SwM: przełącznik trybu konfiguracji, 3-pozycyjny
- Co: częstwotliwość sprawdzania temperatury
- Cz: czas zmiany stanu okna (otwierania/zamykania) [s]
- Kz: komunikat przy zamykaniu okna
- Ko: komunikat przy otwieraniu okna
 
Działanie programu:
- sprawdź stan przełącznika SwM:
    - jeśli SwM jest ustawiony na środkową pozycję (tryb normalny):
        - wyświetl aktualną temperaturę
        - sprawdź zmiany temperatury otoczenia co Co sekund:
            - IF To > Tz
                - wyslij sygnal na przekaźnik PrO przez czas Cz (otwórz okno)
                - wyświetl komunikat Ko
            - IF To < Tz
                - wyślij sygnał na przekaźnik PrZ przez czas Cz (zamknij okno)
                - wyświetl komunikat Kz
- jeśli SwM jest ustawiony w lewą skrajną pozycję (tryb zmiany temperatury):
    - wyświetl aktualną wartość Tz
    - pojedyncze wciśnięcie Pi: Tz = Tz + 1 °C
    - pojedyncze wciśnięcie Pd: Tz = Tz - 1 °C
- jeśli SwM jest ustawiony w prawą skrajną pozycję (tryb zmiany częstotliwości sprawdzania):
    - wyświetl aktualną wartość Co
    - pojedyncze wciśnięcie Pi: Co = Co + 1 min
    - pojedyncze wciśnięcie Pd: Co = Co - 1 min
