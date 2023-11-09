#include <stdio.h>
#include <time.h>

void sumWords(FILE *csvFile, int startingRow, int numRows) {
    const int numWords = 24;
    int sums[numWords] = {0};

    // Saltar las filas antes de la fila de inicio
    for (int i = 1; i < startingRow; ++i) {
        while (fgetc(csvFile) != '\n') ; // Saltar la línea actual
    }

    // Sumar las cantidades para los primeros 50 correos electrónicos
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

    const int startingRow = 3; // Cambiar según los últimos dígitos de tu ID

    printf("Utilizando los datos del CSV, se obtendrá la suma de las veces que aparece cada palabra.\n");
    printf("Sin embargo, la suma se hará solo para 50 correos electrónicos (renglones).\n");
    printf("El renglón de inicio será el número %d.\n", startingRow);
    printf("El output esperado son 3,000 valores los cuales serán guardados en un archivo (un valor por renglón).\n");

    clock_t start = clock();
    sumWords(csvFile, startingRow, 50);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    fclose(csvFile);

    return 0;
}

