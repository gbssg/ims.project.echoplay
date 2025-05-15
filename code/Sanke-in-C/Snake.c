#include <stdio.h>
#include <string.h>

int main()
{
    // Deklarationen
    int screenBreite = 120;
    int temp = 0;

    // Eingabe
    printf("\x1B[1;%dHSnake\n", (screenBreite - 3) / 2);
    temp = strlen("Druecken Sie eine beliebige Taste um zu spielen.");
    printf("\x1B[2;%d", (screenBreite - temp) / 2);
    system("pause");

    // Verarbeitung

    // Ausgabe

    printf("\n");
    system("pause");
    return 0;
}
