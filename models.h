#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

// Enum class para tipos de ejercicios (C++20 moderno)
enum class ExerciseType {
    Lectura,
    Escritura,
    Comprension,
    Unknown
};

// Enum class para niveles de dificultad
enum class DifficultyLevel {
    Basico,
    Intermedio,
    Avanzado
};

// Struct para representar un ejercicio
struct Exercise {
    int id;
    ExerciseType type;
    DifficultyLevel difficulty;
    string question;
    string correctAnswer;
    string options;  // Opciones separadas por |
    int timesUsed;
    double successRate;
    
    Exercise() : id(0), type(ExerciseType::Unknown), difficulty(DifficultyLevel::Basico),
                 timesUsed(0), successRate(0.0) {}
    
    Exercise(int i, ExerciseType t, DifficultyLevel d, string q, string ca, string opt)
        : id(i), type(t), difficulty(d), question(q), correctAnswer(ca), 
          options(opt), timesUsed(0), successRate(0.0) {}
};

// Struct para representar una sesión de ejercicios (con chrono para fechas)
struct Session {
    int userId;
    year_month_day date;
    ExerciseType type;
    int exercisesCompleted;
    int exercisesCorrect;
    int durationMinutes;
    system_clock::time_point startTime;
    system_clock::time_point endTime;
    
    Session() : userId(0), date(year{2024}/month{1}/day{1}), 
                type(ExerciseType::Unknown), exercisesCompleted(0), 
                exercisesCorrect(0), durationMinutes(0) {
        startTime = system_clock::now();
        endTime = system_clock::now();
    }
    
    int getDurationMinutes() const {
        if (durationMinutes > 0) return durationMinutes;
        auto duration = duration_cast<minutes>(endTime - startTime);
        return duration.count();
    }
    
    double getSuccessRate() const {
        if (exercisesCompleted == 0) return 0.0;
        return (static_cast<double>(exercisesCorrect) / exercisesCompleted) * 100.0;
    }
};

// Struct para estadísticas del usuario
struct UserStats {
    int totalExercises;
    int totalCorrect;
    int totalSessions;
    int totalMinutes;
    double overallAccuracy;
    int currentStreak;
    DifficultyLevel recommendedDifficulty;
    ExerciseType weakestType;
    ExerciseType strongestType;
    
    UserStats() : totalExercises(0), totalCorrect(0), totalSessions(0),
                  totalMinutes(0), overallAccuracy(0.0), currentStreak(0),
                  recommendedDifficulty(DifficultyLevel::Basico),
                  weakestType(ExerciseType::Unknown), 
                  strongestType(ExerciseType::Unknown) {}
};

// Funciones helper para convertir entre enum y string
inline string exerciseTypeToString(ExerciseType type) {
    switch(type) {
        case ExerciseType::Lectura: return "Lectura";
        case ExerciseType::Escritura: return "Escritura";
        case ExerciseType::Comprension: return "Comprension";
        default: return "Unknown";
    }
}

inline ExerciseType stringToExerciseType(const string& str) {
    if (str == "Lectura") return ExerciseType::Lectura;
    if (str == "Escritura") return ExerciseType::Escritura;
    if (str == "Comprension") return ExerciseType::Comprension;
    return ExerciseType::Unknown;
}

inline string difficultyLevelToString(DifficultyLevel level) {
    switch(level) {
        case DifficultyLevel::Basico: return "Basico";
        case DifficultyLevel::Intermedio: return "Intermedio";
        case DifficultyLevel::Avanzado: return "Avanzado";
        default: return "Basico";
    }
}

inline DifficultyLevel stringToDifficultyLevel(const string& str) {
    if (str == "Basico") return DifficultyLevel::Basico;
    if (str == "Intermedio") return DifficultyLevel::Intermedio;
    if (str == "Avanzado") return DifficultyLevel::Avanzado;
    return DifficultyLevel::Basico;
}

#endif
