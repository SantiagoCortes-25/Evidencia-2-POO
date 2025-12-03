#if !defined(Progreso_h)
#define Progreso_h
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "models.h"
#include "CSVParser.h"
#include "DateUtils.h"
#include "ProgressAnalyzer_new.h"

using namespace std;

class Progreso{
  private:
    int userId;
    string username;
    vector<Session> sesiones;
    ProgressAnalyzer analyzer;

    // Métodos privados auxiliares
    void cargarSesiones();
    void guardarSesion(const Session& sesion);

  public: 
    Progreso(int userId, string user);

    // Métodos para registrar sesiones
    void iniciarSesion(ExerciseType tipo);
    void finalizarSesion(int ejerciciosCompletados, int ejerciciosCorrectos);

    // Métodos para mostrar estadísticas
    void mostrarEstadisticasBasicas();
    void mostrarTendenciaAprendizaje();
    void mostrarAreasDebiles();
    void mostrarRecomendacionDificultad();
    void mostrarRacha();
    void mostrarEstadisticasCompletas();

    // Getters
    vector<Session> getSesiones() const;
    UserStats getEstadisticas() const;
};

#endif // Progreso_h
