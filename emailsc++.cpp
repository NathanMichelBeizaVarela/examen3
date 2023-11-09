#include <stdio.h>
#include <time.h>

void sumWords(FILE *csvFile, int startingRow, int numRows) {
    const int numWords = 24;
    int sums[numWords] = {0};

    // Saltar las filas antes de la fila de inicio
    for (int i = 1; i < startingRow; ++i) {
        while (fgetc(csvFile) != '\n') ; // Saltar la l�nea actual
    }

    // Sumar las cantidades para los primeros 50 correos electr�nicos
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numWords; ++j) {
            int value;
            fscanf(csvFile, "%d", &value);
            sums[j] += value;
        }
    }

    // Imprimir las sumas y guardar en el archivo Excel
    FILE *excelFile = fopen("emails.xlsx", "w");
    if (!excelFile) {
        fprintf(stderr, "Error al abrir el archivo Excel\n");
        return;
    }

    for (int i = 0; i < numWords; ++i) {
        fprintf(excelFile, "%d\n", sums[i]);
    }

    fclose(excelFile);
    printf("Sumas guardadas en emails.xlsx\n");
}

int main() {
    FILE *csvFile = fopen("emails.csv", "r");
    if (!csvFile) {
        fprintf(stderr, "Error al abrir el archivo CSV\n");
        return 1;
    }

    const int startingRow = 3; // Cambiar seg�n los �ltimos d�gitos de tu ID

    printf("Utilizando los datos del CSV, se obtendr� la suma de las veces que aparece cada palabra.\n");
    printf("Sin embargo, la suma se har� solo para 50 correos electr�nicos (renglones).\n");
    printf("El rengl�n de inicio ser� el n�mero %d.\n", startingRow);
    printf("El output esperado son 3,000 valores los cuales ser�n guardados en un archivo (un valor por rengl�n).\n");

    clock_t start = clock();
    sumWords(csvFile, startingRow, 50);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecuci�n: %f segundos\n", cpu_time_used);

    fclose(csvFile);

    return 0;
}

