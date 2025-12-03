#ifndef PROGRESS_ANALYZER_NEW_H
#define PROGRESS_ANALYZER_NEW_H

#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include "models.h"
#include "CSVParser.h"
#include "DateUtils.h"

class ProgressAnalyzer {
private:
    int userId;
    vector<Session> sessions;

public:
    ProgressAnalyzer() : userId(0) {}
    
    ProgressAnalyzer(int uid) : userId(uid) {}
    
    void agregarSesion(const Session& sesion) {
        if (sesion.userId == userId) {
            sessions.push_back(sesion);
        }
    }

    // ALGORITMO 1: Regresión lineal
    double calculateLearningTrend() {
        if (sessions.size() < 2) return 0.0;
        
        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
        int n = sessions.size();
        
        for (int i = 0; i < n; i++) {
            double x = i;
            double y = sessions[i].getSuccessRate();
            
            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
        }
        
        double denominator = n * sumX2 - sumX * sumX;
        if (denominator == 0) return 0.0;
        
        return (n * sumXY - sumX * sumY) / denominator;
    }

    // ALGORITMO 2: Clustering por tipo
    map<ExerciseType, double> identifyWeakAreas() {
        map<ExerciseType, double> typeScores;
        map<ExerciseType, int> typeCounts;
        
        for (const auto& s : sessions) {
            typeScores[s.type] += s.getSuccessRate();
            typeCounts[s.type]++;
        }
        
        for (auto& pair : typeScores) {
            if (typeCounts[pair.first] > 0) {
                pair.second /= typeCounts[pair.first];
            }
        }
        
        return typeScores;
    }

    // ALGORITMO 3: Recomendación adaptativa
    DifficultyLevel recommendNextDifficulty() {
        if (sessions.empty()) return DifficultyLevel::Basico;
        
        int startIdx = max(0, static_cast<int>(sessions.size()) - 5);
        double totalSuccess = 0;
        int count = 0;
        
        for (size_t i = startIdx; i < sessions.size(); i++) {
            totalSuccess += sessions[i].getSuccessRate();
            count++;
        }
        
        if (count == 0) return DifficultyLevel::Basico;
        
        double avgSuccess = totalSuccess / count;
        
        if (avgSuccess >= 85.0) return DifficultyLevel::Avanzado;
        else if (avgSuccess >= 65.0) return DifficultyLevel::Intermedio;
        else return DifficultyLevel::Basico;
    }

    // ALGORITMO 4: Cálculo de racha
    int calculateStreak() {
        if (sessions.empty()) return 0;
        
        vector<Session> sortedSessions = sessions;
        sort(sortedSessions.begin(), sortedSessions.end(), 
             [](const Session& a, const Session& b) {
                 return a.date > b.date;
             });
        
        auto today = DateUtils::today();
        int streak = 0;
        auto currentDate = today;
        
        for (const auto& s : sortedSessions) {
            if (DateUtils::isSameDate(s.date, currentDate)) {
                streak++;
                auto ymd = year_month_day{currentDate};
                auto sysDays = sys_days{ymd} - days{1};
                currentDate = year_month_day{sysDays};
            } else if (s.date < currentDate) {
                break;
            }
        }
        
        return streak;
    }

    // Método auxiliar
    UserStats getUserStats() const {
        UserStats stats;
        
        for (const auto& s : sessions) {
            stats.totalExercises += s.exercisesCompleted;
            stats.totalCorrect += s.exercisesCorrect;
            stats.totalMinutes += s.durationMinutes;
        }
        
        stats.totalSessions = sessions.size();
        
        if (stats.totalExercises > 0) {
            stats.overallAccuracy = (static_cast<double>(stats.totalCorrect) / stats.totalExercises) * 100.0;
        }
        
        stats.currentStreak = const_cast<ProgressAnalyzer*>(this)->calculateStreak();
        stats.recommendedDifficulty = const_cast<ProgressAnalyzer*>(this)->recommendNextDifficulty();
        
        auto weakAreas = const_cast<ProgressAnalyzer*>(this)->identifyWeakAreas();
        double minScore = 100.0, maxScore = 0.0;
        
        for (const auto& pair : weakAreas) {
            if (pair.second < minScore) {
                minScore = pair.second;
                stats.weakestType = pair.first;
            }
            if (pair.second > maxScore) {
                maxScore = pair.second;
                stats.strongestType = pair.first;
            }
        }
        
        return stats;
    }
};

#endif
