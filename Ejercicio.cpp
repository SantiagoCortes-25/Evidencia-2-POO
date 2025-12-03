#include "Ejercicio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Ejercicio::Ejercicio(){
    puntos = 0;
    srand(time(0));
    cargarEjercicios();
}

void Ejercicio::cargarEjercicios(){
    ejercicios.clear();

    ifstream archivo("ejercicios.csv");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir ejercicios.csv" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar header

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = CSVParser::split(linea);
        if (campos.size() >= 6) {
            Exercise ex;
            ex.id = stoi(campos[0]);
            ex.type = stringToExerciseType(campos[1]);
            ex.difficulty = stringToDifficultyLevel(campos[2]);
            ex.question = campos[3];
            ex.correctAnswer = campos[4];
            ex.options = campos[5];
            
            ejercicios.push_back(ex);
        }
    }
    archivo.close();
    
    cout << "Cargados " << ejercicios.size() << " ejercicios." << endl;
}

vector<string> Ejercicio::separarOpciones(const string& opciones) {
    vector<string> resultado;
    stringstream ss(opciones);
    string opcion;
    
    while (getline(ss, opcion, '|')) {
        // Trim whitespace
        opcion.erase(0, opcion.find_first_not_of(" \t\r\n"));
        opcion.erase(opcion.find_last_not_of(" \t\r\n") + 1);
        resultado.push_back(opcion);
    }
    
    return resultado;
}

void Ejercicio::seleccionarEjercicio(ExerciseType tipo, DifficultyLevel nivel) {
    // Filtrar ejercicios por tipo y nivel
    vector<Exercise> filtrados;
    for (const auto& ex : ejercicios) {
        if (ex.type == tipo && ex.difficulty == nivel) {
            filtrados.push_back(ex);
        }
    }
    
    if (filtrados.empty()) {
        cout << "No hay ejercicios disponibles para este tipo y nivel." << endl;
        return;
    }
    
    // Seleccionar uno al azar
    int idx = rand() % filtrados.size();
    ejercicioActual = filtrados[idx];
}

void Ejercicio::generarEjercicio(ExerciseType tipo, DifficultyLevel nivel) {
    seleccionarEjercicio(tipo, nivel);
    
    cout << "\n=== EJERCICIO ===" << endl;
    cout << "Tipo: " << exerciseTypeToString(ejercicioActual.type) << endl;
    cout << "Nivel: " << difficultyLevelToString(ejercicioActual.difficulty) << endl;
    
    // Para ejercicios de Lectura, mostrar instrucción clara
    if (ejercicioActual.type == ExerciseType::Lectura) {
        cout << "\nCual esta escrito correctamente?" << endl;
    } else if (ejercicioActual.type == ExerciseType::Escritura) {
        cout << "\n" << ejercicioActual.question << endl;
    } else {
        cout << "\n" << ejercicioActual.question << endl;
    }
    
    // Mostrar opciones
    vector<string> opciones = separarOpciones(ejercicioActual.options);
    for (size_t i = 0; i < opciones.size(); i++) {
        cout << (i + 1) << ") " << opciones[i] << endl;
    }
    
    cout << "\nTu respuesta (1-" << opciones.size() << "): ";
}

bool Ejercicio::verificarRespuesta(const string& respuestaUsuario) {
    vector<string> opciones = separarOpciones(ejercicioActual.options);
    
    // Convertir respuesta de string a índice
    int indice = 0;
    try {
        indice = stoi(respuestaUsuario);
    } catch (...) {
        cout << "Respuesta invalida." << endl;
        return false;
    }
    
    if (indice < 1 || indice > static_cast<int>(opciones.size())) {
        cout << "Opcion fuera de rango." << endl;
        return false;
    }
    
    string respuestaSeleccionada = opciones[indice - 1];
    
    if (respuestaSeleccionada == ejercicioActual.correctAnswer) {
        puntos++;
        cout << "\nCORRECTO!" << endl;
        cout << "Puntos totales: " << puntos << endl;
        return true;
    } else {
        cout << "\nIncorrecto" << endl;
        cout << "La respuesta correcta era: " << ejercicioActual.correctAnswer << endl;
        return false;
    }
}

int Ejercicio::getPuntos() const {
    return puntos;
}

Exercise Ejercicio::getEjercicioActual() const {
    return ejercicioActual;
}

int Ejercicio::contarEjerciciosPorTipo(ExerciseType tipo) const {
    int count = 0;
    for (const auto& ex : ejercicios) {
        if (ex.type == tipo) count++;
    }
    return count;
}

int Ejercicio::contarEjerciciosPorDificultad(DifficultyLevel nivel) const {
    int count = 0;
    for (const auto& ex : ejercicios) {
        if (ex.difficulty == nivel) count++;
    }
    return count;
}
