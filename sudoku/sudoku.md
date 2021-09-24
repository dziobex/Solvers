# Co to sudoku?
Klasyczne Sudoku to łamigłówka o rozmiarze 9x9, którą należy rozwiązać poprzez wpisanie w odpowiednie pola liczb 1-9, tak aby w każdym wierszu, kolumnie i kwadracie znajdowały się niepowtarzające się liczby 1-9.
Dobre sudoku to takie, w które ma tylko jedno rozwiązanie, a do niego można dojść w logiczny sposób (bez zgadywania). <br/>

# Jak działa ten solver?
Solver opiera się na backtracingu. Wartości z planszy są przechowywane w 2D tablicach (kolumny, wiersze i kwadraty).
1. Każde puste pole jest sprawdzane czy w nim możne znajdować się pierwsza liczba (do N-rozmiaru planszy), która nie została jeszcze użyta w jego kolumnie, wierszu i kwadracie.
2. Jeśli może, kolejne pole (kolejność sprawdzania: lewo->prawo, góra->doł) jest tak samo sprawdzane, dopóki warunek powyżej zostanie niespełniony.
3. Jeśli warunek z p. 3 nie zostanie spełniony, sprawdzator się cofa o jedno pole wstecz.
4. Jeśli poprzednie puste pole (z p. 3) nie ma już żadnych możliwiości, sprawdzator znowu się cofa, dopóki nie znajdzie pierwszego pustego pola z potencjalnie możliwą wartością. Jeśli takie pole się znajdzie, sprawdzator wraca do p. 1.
5. Jeśli sprawdzator wróci do pierwotnie pierwszego pustego pola i nie zostanie żadna możliwość do sprawdzenia, to sudoku jest błędne (nie ma rozwiązań).

# Złożoność czasowa
Złożność czasowa: O(n^N)<br/>
n - liczba pustych pól<br/>
N - liczba liczb, które mogą być w dowolnym pustym polu (dla tradycyjnego sudoku 9x9, N=9)
