#if !defined(Usuario_h)
#define Usuario_h
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include "models.h"
#include "CSVParser.h"
#include "DateUtils.h"

using namespace std;

// Estructura interna para representar un usuario completo
struct UsuarioData {
    int id;
    string username;
    string password;
    chrono::year_month_day registrationDate;
    int totalSessions;
};

class Usuario{
  private:
  // Caracteristicas del objeto
  int id;
  string username;
  string password;   
  bool estadoLog;
  chrono::year_month_day registrationDate;
  int totalSessions;

  // Métodos privados auxiliares
  static vector<UsuarioData> cargarUsuarios();
  static void guardarUsuario(const UsuarioData& userData);
  static bool usuarioExiste(const string& user);
  static int obtenerNuevoId();
  static void actualizarArchivo(const vector<UsuarioData>& usuarios);

  public: 
  // Constructores 
  Usuario();
  Usuario(string user, string pass);
  Usuario(string user, string pass, bool estadoLog);

  // Metodos o acciones
  bool login(string userIngresado, string passIngresada);
  void logout();
  void cambiarPassword(string nueva);
  void mostrarEstado();
  static bool registrarse(string& nuevoUser, string& nuevaPass);
  void incrementarSesiones();

  // Getters
  int getId() const;
  string getUsername() const;
  bool getEstadoLog() const;
  chrono::year_month_day getRegistrationDate() const;
  int getTotalSessions() const;
};

#endif // Usuario_h
