#include "Progreso.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

Progreso::Progreso(int userId, string user) : analyzer(userId) {
    this->userId = userId;
    this->username = user;
    cargarSesiones();
}

void Progreso::cargarSesiones(){
    sesiones.clear();
    
    ifstream archivo("sesiones.csv");
    if (!archivo.is_open()) {
        return;
    }
    
    string linea;
    getline(archivo, linea); // Saltar header
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = CSVParser::split(linea);
        if (campos.size() >= 6) {
            int sessionUserId = stoi(campos[0]);
            
            if (sessionUserId == this->userId) {
                Session sesion;
                sesion.userId = sessionUserId;
                sesion.date = DateUtils::parseDate(campos[1]);
                sesion.type = stringToExerciseType(campos[2]);
                sesion.exercisesCompleted = stoi(campos[3]);
                sesion.exercisesCorrect = stoi(campos[4]);
                sesion.durationMinutes = stoi(campos[5]);
                
                sesiones.push_back(sesion);
                analyzer.agregarSesion(sesion);
            }
        }
    }
    archivo.close();
}

void Progreso::guardarSesion(const Session& sesion){
    ofstream archivo("sesiones.csv", ios::app);
    
    if (archivo.is_open()) {
        archivo << sesion.userId << ","
                << DateUtils::formatDate(sesion.date) << ","
                << exerciseTypeToString(sesion.type) << ","
                << sesion.exercisesCompleted << ","
                << sesion.exercisesCorrect << ","
                << sesion.durationMinutes << endl;
        archivo.close();
    }
}

void Progreso::iniciarSesion(ExerciseType tipo){
    // Guardar el tipo de sesión actual para cuando finalice
    Session nuevaSesion;
    nuevaSesion.userId = this->userId;
    nuevaSesion.date = DateUtils::today();
    nuevaSesion.type = tipo;
    nuevaSesion.exercisesCompleted = 0;
    nuevaSesion.exercisesCorrect = 0;
    nuevaSesion.durationMinutes = 0;
    
    sesiones.push_back(nuevaSesion);
}

void Progreso::finalizarSesion(int ejerciciosCompletados, int ejerciciosCorrectos){
    if (!sesiones.empty()) {
        Session& ultimaSesion = sesiones.back();
        ultimaSesion.exercisesCompleted = ejerciciosCompletados;
        ultimaSesion.exercisesCorrect = ejerciciosCorrectos;
        
        // Simular duración (en la práctica se mediría el tiempo real)
        ultimaSesion.durationMinutes = ejerciciosCompletados * 2;
        
        guardarSesion(ultimaSesion);
        analyzer.agregarSesion(ultimaSesion);
        
        cout << "\nSesion guardada exitosamente!" << endl;
    }
}

void Progreso::mostrarEstadisticasBasicas(){
    int totalEjercicios = 0;
    int totalCorrectos = 0;
    
    for (const auto& s : sesiones) {
        totalEjercicios += s.exercisesCompleted;
        totalCorrectos += s.exercisesCorrect;
    }
    
    cout << "\n=== ESTADISTICAS BASICAS ===" << endl;
    cout << "Usuario: " << username << endl;
    cout << "Sesiones realizadas: " << sesiones.size() << endl;
    cout << "Ejercicios completados: " << totalEjercicios << endl;
    cout << "Ejercicios correctos: " << totalCorrectos << endl;
    
    if (totalEjercicios > 0) {
        double promedio = (double)totalCorrectos / totalEjercicios * 100;
        cout << "Porcentaje de aciertos: " << fixed << setprecision(1) 
             << promedio << "%" << endl;
    }
}

void Progreso::mostrarTendenciaAprendizaje(){
    double tendencia = analyzer.calculateLearningTrend();
    
    cout << "\n=== TENDENCIA DE APRENDIZAJE ===" << endl;
    cout << "Pendiente de mejora: " << fixed << setprecision(3) << tendencia << endl;
    
    if (tendencia > 0.5) {
        cout << "Excelente! Estas mejorando rapidamente." << endl;
    } else if (tendencia > 0) {
        cout << "Vas progresando, sigue practicando." << endl;
    } else if (tendencia > -0.5) {
        cout << "Tu rendimiento es estable." << endl;
    } else {
        cout << "Considera revisar ejercicios anteriores." << endl;
    }
}

void Progreso::mostrarAreasDebiles(){
    auto areasDebiles = analyzer.identifyWeakAreas();
    
    cout << "\n=== AREAS DE OPORTUNIDAD ===" << endl;
    cout << "Promedio de aciertos por tipo:" << endl;
    for (const auto& par : areasDebiles) {
        cout << exerciseTypeToString(par.first) << ": " 
             << fixed << setprecision(1) << par.second << "%" << endl;
    }
}

void Progreso::mostrarRecomendacionDificultad(){
    DifficultyLevel recomendado = analyzer.recommendNextDifficulty();
    
    cout << "\n=== RECOMENDACION DE NIVEL ===" << endl;
    cout << "Nivel sugerido: " << difficultyLevelToString(recomendado) << endl;
}

void Progreso::mostrarRacha(){
    int racha = analyzer.calculateStreak();
    
    cout << "\n=== RACHA ACTUAL ===" << endl;
    cout << "Dias consecutivos practicando: " << racha << endl;
    
    if (racha >= 7) {
        cout << "Increible racha!" << endl;
    } else if (racha >= 3) {
        cout << "Buen trabajo!" << endl;
    } else if (racha == 0) {
        cout << "Comienza tu racha hoy." << endl;
    }
}

void Progreso::mostrarEstadisticasCompletas(){
    UserStats stats = analyzer.getUserStats();
    
    cout << "\n==========================================" << endl;
    cout << "   ESTADISTICAS COMPLETAS - " << username << "      " << endl;
    cout << "==========================================" << endl;
    
    cout << " Sesiones totales: " << stats.totalSessions << endl;
    cout << " Ejercicios completados: " << stats.totalExercises << endl;
    cout << " Ejercicios correctos: " << stats.totalCorrect << endl;
    cout << " Tasa de acierto: " << fixed << setprecision(1) 
         << stats.overallAccuracy << "%" << endl;
    cout << " Tiempo total: " << stats.totalMinutes << " min" << endl;
    cout << " Racha actual: " << stats.currentStreak << " dias" << endl;
    cout << " Nivel recomendado: " 
         << difficultyLevelToString(stats.recommendedDifficulty) << endl;
    
    cout << "==========================================" << endl;
}

vector<Session> Progreso::getSesiones() const {
    return sesiones;
}

UserStats Progreso::getEstadisticas() const {
    return analyzer.getUserStats();
}
