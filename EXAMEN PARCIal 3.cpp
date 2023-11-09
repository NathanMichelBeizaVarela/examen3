#include <stdio.h>
#include <time.h>

void sumWords(FILE *csvFile, int startingRow, int numRows) {
    const int numWords = 24;
    int sums[numWords] = {0};
    for (int i = 1; i < startingRow; ++i) {
        while (fgetc(csvFile) != '\n') ; 
    }

    
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numWords; ++j) {
            int value;
            fscanf(csvFile, "%d", &value);
            sums[j] += value;
        }
    }

   
    FILE *excelFile = fopen("emails.csv", "w");
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

    clock_t start = clock();
    sumWords(csvFile, startingRow, 50);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    fclose(csvFile);

    return 0;
}

