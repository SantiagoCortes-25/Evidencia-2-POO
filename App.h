#if !defined(App_h)
#define App_h

#include "Usuario.h"
#include "Progreso.h"
#include "Info.h"
#include "Ejercicio.h"
#include "models.h"

class App{
  private: 
    Usuario usuario;
    Progreso* progreso; // Puntero porque se crea después del login
  
  public:
    App();
    ~App();
    void run();
  
  private:
    void menuPrincipal();
    void menuUsuario();
    void menuEjercicios();
    void realizarEjercicios(ExerciseType tipo, DifficultyLevel nivel);
    void menuProgreso();
    void menuAnalytics();
    void menuInfo();
    void menuCuenta();
};

#endif // App_h
