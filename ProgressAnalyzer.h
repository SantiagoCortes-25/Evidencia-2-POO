#ifndef PROGRESSANALYZER_H
#define PROGRESSANALYZER_H

#include "models.h"
#include "DateUtils.h"
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>

class ProgressAnalyzer {
private:
    vector<Session> sessions;

public:
    ProgressAnalyzer() {}

    void addSession(const Session& session) {
        sessions.push_back(session);
    }

    void loadSessions(const vector<Session>& s) {
        sessions = s;
    }

    // ALGORITMO RETADOR 1: Calcular tendencia usando regresión lineal
    // Retorna la pendiente (m > 0 = mejorando, m < 0 = empeorando)
    double calculateLearningTrend(int userId, ExerciseType type) {
        vector<Session> filtered;
        
        // Filtrar sesiones del usuario y tipo específico
        for (const auto& s : sessions) {
            if (s.userId == userId && s.type == type) {
                filtered.push_back(s);
            }
        }

        if (filtered.size() < 2) return 0.0;

        // Ordenar por fecha
        sort(filtered.begin(), filtered.end(), 
             [](const Session& a, const Session& b) {
                 return a.date < b.date;
             });

        // Regresión lineal simple: y = mx + b
        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
        int n = filtered.size();

        for (int i = 0; i < n; i++) {
            double x = i;  // Índice de sesión
            double y = filtered[i].getSuccessRate();
            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
        }

        // Calcular pendiente
        double m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
        return m;
    }

    // ALGORITMO RETADOR 2: Identificar áreas débiles
    map<ExerciseType, double> identifyWeakAreas(int userId) {
        map<ExerciseType, vector<double>> typeScores;

        for (const auto& s : sessions) {
            if (s.userId == userId) {
                typeScores[s.type].push_back(s.getSuccessRate());
            }
        }

        map<ExerciseType, double> avgScores;
        for (const auto& [type, scores] : typeScores) {
            if (!scores.empty()) {
                double avg = accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
                avgScores[type] = avg;
            }
        }

        return avgScores;
    }

    // ALGORITMO RETADOR 3: Predecir nivel recomendado
    DifficultyLevel recommendNextDifficulty(int userId, ExerciseType type) {
        vector<Session> recent;
        
        // Obtener sesiones del tipo
        for (const auto& s : sessions) {
            if (s.userId == userId && s.type == type) {
                recent.push_back(s);
            }
        }

        if (recent.empty()) return DifficultyLevel::Basico;

        // Ordenar por fecha y tomar las más recientes
        sort(recent.begin(), recent.end(), 
             [](const Session& a, const Session& b) {
                 return a.date > b.date;
             });

        int limit = min(5, (int)recent.size());
        recent.resize(limit);

        // Calcular promedio
        double avgSuccess = 0.0;
        for (const auto& s : recent) {
            avgSuccess += s.getSuccessRate();
        }
        avgSuccess /= limit;

        // Determinar nivel basado en desempeño
        if (avgSuccess >= 85.0) return DifficultyLevel::Avanzado;
        if (avgSuccess >= 65.0) return DifficultyLevel::Intermedio;
        return DifficultyLevel::Basico;
    }

    // ALGORITMO RETADOR 4: Calcular racha de días consecutivos
    int calculateStreak(int userId) {
        vector<year_month_day> dates;

        for (const auto& s : sessions) {
            if (s.userId == userId) {
                dates.push_back(s.date);
            }
        }

        if (dates.empty()) return 0;

        // Ordenar fechas
        sort(dates.begin(), dates.end());

        // Eliminar duplicados
        dates.erase(unique(dates.begin(), dates.end()), dates.end());

        // Contar días consecutivos desde hoy hacia atrás
        auto today = DateUtils::today();
        int streak = 0;

        for (auto it = dates.rbegin(); it != dates.rend(); ++it) {
            int daysDiff = DateUtils::daysBetween(*it, today);
            
            if (daysDiff == streak) {
                streak++;
            } else {
                break;
            }
        }

        return streak;
    }

    // Obtener estadísticas completas del usuario
    UserStats getUserStats(int userId) {
        UserStats stats;

        for (const auto& s : sessions) {
            if (s.userId == userId) {
                stats.totalExercises += s.exercisesCompleted;
                stats.totalCorrect += s.exercisesCorrect;
            }
        }

        if (stats.totalExercises > 0) {
            stats.averageSuccessRate = 
                (static_cast<double>(stats.totalCorrect) / stats.totalExercises) * 100.0;
        }

        // Identificar tipo más débil y más fuerte
        auto weakAreas = identifyWeakAreas(userId);
        if (!weakAreas.empty()) {
            double minScore = 100.0;
            double maxScore = 0.0;

            for (const auto& [type, score] : weakAreas) {
                if (score < minScore) {
                    minScore = score;
                    stats.weakestType = type;
                }
                if (score > maxScore) {
                    maxScore = score;
                    stats.strongestType = type;
                }
            }
        }

        stats.streakDays = calculateStreak(userId);

        return stats;
    }

    // Obtener total de sesiones
    int getTotalSessions() const {
        return sessions.size();
    }

    // Obtener sesiones de un usuario
    vector<Session> getUserSessions(int userId) const {
        vector<Session> userSessions;
        for (const auto& s : sessions) {
            if (s.userId == userId) {
                userSessions.push_back(s);
            }
        }
        return userSessions;
    }
};

#endif
