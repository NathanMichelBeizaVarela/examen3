#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <ctime>

int main() {
    // Abre el archivo CSV
    std::ifstream inputFile("tu_archivo.csv");

    // Verifica que el archivo se haya abierto correctamente
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo CSV." << std::endl;
        return 1;
    }

    // Crea un mapa para almacenar la suma de las palabras
    std::unordered_map<std::string, int> wordSum;

    // Define el número de renglones a procesar
    const int numRenglones = 50;

    // Lee los últimos tres dígitos de tu número de ID
    const char* id = "tu_numero_de_id"; // Reemplaza con tus últimos tres dígitos
    int startIndex = std::stoi(id);

    // Salta los renglones hasta llegar al índice de inicio
    for (int i = 0; i < startIndex; ++i) {
        std::string dummy;
        std::getline(inputFile, dummy);
    }

    // Procesa los siguientes 50 renglones
    for (int i = 0; i < numRenglones; ++i) {
        std::string line;
        std::getline(inputFile, line);

        // Usa un stringstream para dividir la línea en palabras
        std::istringstream iss(line);
        std::string word;
        int count;

        // Lee la palabra y su conteo de cada columna
        while (std::getline(iss, word, ',')) {
            if (std::getline(iss, word, ',')) {
                count = std::stoi(word);
                // Incrementa la suma de la palabra en el mapa
                wordSum[word] += count;
            }
        }
    }

    // Cierra el archivo CSV
    inputFile.close();

    // Guarda los resultados en un archivo de salida
    std::ofstream outputFile("output.txt");

    // Verifica que el archivo de salida se haya abierto correctamente
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    // Escribe las sumas en el archivo de salida
    for (const auto& pair : wordSum) {
        outputFile << pair.second << std::endl;
    }

    // Cierra el archivo de salida
    outputFile.close();

    // Muestra el tiempo de ejecución
    std::clock_t end = std::clock();
    std::cout << "Proceso completado. Resultados guardados en output.txt." << std::endl;

    return 0;
}


