#include <iostream>
using namespace std;

#include "Usuario.cpp"
#include "Ejercicio.cpp"
#include "Progreso.cpp"
#include "Info.cpp"
#include "App.h"

App::App() : usuario("", ""), progreso(nullptr) {
}

App::~App() {
    if (progreso != nullptr) {
        delete progreso;
    }
}

void App::run(){
  while(true){
    if (usuario.getEstadoLog()){
        menuUsuario();
    } else{
      menuPrincipal();
    }
  }
}

void App::menuPrincipal(){
  int opcion;
  string user, pass;
   cout << "\n====================================\n";
   cout << "          LEXBOT - BIENVENIDO       \n";
   cout << "====================================\n";
   cout << "1. Iniciar sesion\n";
   cout << "2. Registrarse\n";
   cout << "3. Salir\n";
   cout << "Opcion: ";
   cin >> opcion;

   switch (opcion) {
    case 1:
        cout << "Usuario: ";
        cin >> user;
        cout << "Contrasena: ";
        cin >> pass;
        if (usuario.login(user, pass)) {
            // Crear objeto Progreso después del login exitoso
            if (progreso != nullptr) delete progreso;
            progreso = new Progreso(usuario.getId(), usuario.getUsername());
        }
        break;

    case 2: {
        string nuevoUser, nuevaPass;
        if (Usuario::registrarse(nuevoUser, nuevaPass)) {
            cout << "Ahora puedes iniciar sesion con tu nuevo usuario." << endl;
        }
        break;
    }

    case 3:
        cout << "Hasta pronto!\n";
        exit(0);

    default:
        cout << "Opcion no valida.\n";
    }
}

void App::menuUsuario(){
  int opcion;
   cout << "\n====================================\n";
   cout << "  Hola " << usuario.getUsername() << "! Que haras hoy?    \n";
   cout << "====================================\n";
   cout << "1. Ejercicios\n";
   cout << "2. Estadisticas basicas\n";
   cout << "3. Analytics avanzado\n";
   cout << "4. Informacion\n";
   cout << "5. Mi cuenta\n";
   cout << "Opcion: ";
   cin >> opcion;

   switch (opcion) {
    case 1:
        menuEjercicios();
        break;
    case 2:
        if (progreso != nullptr) {
            progreso->mostrarEstadisticasBasicas();
        }
        break;
    case 3:
        menuAnalytics();
        break;
    case 4:
        menuInfo();
        break;
    case 5: 
        menuCuenta();
        break;
    default:
        cout << "Opcion no valida.\n";
    }
}

void App::menuEjercicios(){
    int tipoOpcion, nivelOpcion;
    
    cout << "\n--- SELECCIONA TIPO DE EJERCICIO ---\n";
    cout << "1. Lectura\n";
    cout << "2. Escritura\n";
    cout << "3. Comprension\n";
    cout << "4. Regresar\n";
    cout << "Opcion: ";
    cin >> tipoOpcion;
    
    if (tipoOpcion == 4) return;
    
    ExerciseType tipo;
    switch(tipoOpcion) {
        case 1: tipo = ExerciseType::Lectura; break;
        case 2: tipo = ExerciseType::Escritura; break;
        case 3: tipo = ExerciseType::Comprension; break;
        default: 
            cout << "Opcion invalida.\n";
            return;
    }
    
    cout << "\n--- SELECCIONA NIVEL DE DIFICULTAD ---\n";
    cout << "1. Basico\n";
    cout << "2. Intermedio\n";
    cout << "3. Avanzado\n";
    cout << "Opcion: ";
    cin >> nivelOpcion;
    
    DifficultyLevel nivel;
    switch(nivelOpcion) {
        case 1: nivel = DifficultyLevel::Basico; break;
        case 2: nivel = DifficultyLevel::Intermedio; break;
        case 3: nivel = DifficultyLevel::Avanzado; break;
        default:
            cout << "Opcion invalida.\n";
            return;
    }
    
    realizarEjercicios(tipo, nivel);
}

void App::realizarEjercicios(ExerciseType tipo, DifficultyLevel nivel){
    Ejercicio ejercicio;
    string respuesta;
    int completados = 0;
    int correctos = 0;
    
    if (progreso != nullptr) {
        progreso->iniciarSesion(tipo);
    }
    
    while (true) {
        ejercicio.generarEjercicio(tipo, nivel);
        cin >> respuesta;
        
        bool correcto = ejercicio.verificarRespuesta(respuesta);
        completados++;
        if (correcto) correctos++;
        
        cout << "\nContinuar?\n";
        cout << "1) Si\n2) No (Guardar y salir)\n";
        cout << "Opcion: ";
        cin >> respuesta;
        
        if (respuesta == "2") {
            if (progreso != nullptr) {
                progreso->finalizarSesion(completados, correctos);
                usuario.incrementarSesiones();
            }
            cout << "\nResumen: " << correctos << "/" << completados << " correctos\n";
            break;
        }
    }
}

void App::menuCuenta(){
  int opcion;
   cout << "\n--- MI CUENTA ---\n";
   cout << "1. Cambiar contrasena\n";
   cout << "2. Mostrar informacion\n";
   cout << "3. Cerrar sesion\n";
   cout << "4. Regresar\n";
   cout << "Opcion: ";
   cin >> opcion;

   switch (opcion) {
    case 1: {
        string nueva;
        cout << "Nueva contrasena: ";
        cin >> nueva;
        usuario.cambiarPassword(nueva);
        break;
    }
    case 2:
        usuario.mostrarEstado();
        break;
    case 3:
        usuario.logout();
        if (progreso != nullptr) {
            delete progreso;
            progreso = nullptr;
        }
        break;
    case 4:
        return;
    default:
        cout << "Opcion no valida.\n";
    }
}

void App::menuProgreso(){
    if (progreso == nullptr) {
        cout << "Error: No hay progreso disponible.\n";
        return;
    }
    
    progreso->mostrarEstadisticasBasicas();
}

void App::menuAnalytics(){
    if (progreso == nullptr) {
        cout << "Error: No hay datos de progreso.\n";
        return;
    }
    
    int opcion;
    while (true) {
        cout << "\n--- ANALYTICS AVANZADO ---\n";
        cout << "1. Tendencia de aprendizaje \n";
        cout << "2. Areas de oportunidad \n";
        cout << "3. Nivel recomendado\n";
        cout << "4. Racha actual\n";
        cout << "5. Estadisticas completas\n";
        cout << "6. Regresar\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                progreso->mostrarTendenciaAprendizaje();
                break;
            case 2:
                progreso->mostrarAreasDebiles();
                break;
            case 3:
                progreso->mostrarRecomendacionDificultad();
                break;
            case 4:
                progreso->mostrarRacha();
                break;
            case 5:
                progreso->mostrarEstadisticasCompletas();
                break;
            case 6:
                return;
            default:
                cout << "Opcion invalida.\n";
        }
    }
}

void App::menuInfo(){
    int opcion;
    Info gestorInfo;
    while (true) {
        cout << "\n--- INFORMACION ---\n";
        cout << "1. Que es la dislexia?\n";
        cout << "2. Sobre LexBot\n";
        cout << "3. Contactos de apoyo\n";
        cout << "4. Quienes somos?\n";
        cout << "5. Regresar\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                gestorInfo.cargarArchivo("dislexia");
                break;
            case 2:
                gestorInfo.cargarArchivo("lexbot");
                break;
            case 3:
                gestorInfo.mostrarCSV("contactos");
                break;
            case 4:
                cout << "\n========================================" << endl;
                cout << "           QUIENES SOMOS?" << endl;
                cout << "========================================" << endl;
                cout << "\nFundadores del proyecto LexBot:" << endl;
                cout << "\nEstudiantes del area de computacion" << endl;
                cout << "Tecnologico de Monterrey" << endl;
                cout << "\n----------------------------------------" << endl;
                cout << "Alexia Gonzalez Zavala" << endl;
                cout << "Matricula: A01710687" << endl;
                cout << "\nOscar Andre Galicia Anduaga" << endl;
                cout << "Matricula: A01724046" << endl;
                cout << "\nSantiago Cortes Martinez" << endl;
                cout << "Matricula: A00843691" << endl;
                cout << "========================================" << endl;
                break;
            case 5:
                return;
            default:
                cout << "Opcion no valida.\n";
        }
    }
}