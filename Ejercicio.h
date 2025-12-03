#if !defined(Ejercicio_h)
#define Ejercicio_h
#include <iostream>
#include <string>
#include <vector>
#include "models.h"
#include "CSVParser.h"

using namespace std;

class Ejercicio{
  private:
    vector<Exercise> ejercicios;
    Exercise ejercicioActual;
    int puntos;

    void cargarEjercicios();
    void seleccionarEjercicio(ExerciseType tipo, DifficultyLevel nivel);
    vector<string> separarOpciones(const string& opciones);

  public: 
    Ejercicio();

    // Metodos principales
    void generarEjercicio(ExerciseType tipo, DifficultyLevel nivel);
    bool verificarRespuesta(const string& respuestaUsuario);
    int getPuntos() const;
    Exercise getEjercicioActual() const;
    
    // Estadísticas
    int contarEjerciciosPorTipo(ExerciseType tipo) const;
    int contarEjerciciosPorDificultad(DifficultyLevel nivel) const;
};

#endif // Ejercicio_h
