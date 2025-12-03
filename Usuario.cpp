#include <iostream>
#include <sstream>
using namespace std;

#include "Usuario.h"

// Constructor por default
Usuario::Usuario(){
 this->id = 0;
 this->username = "";
 this->password = "";
 this->estadoLog = false;
 this->registrationDate = DateUtils::today();
 this->totalSessions = 0;
}

// Constructor parametrizado
Usuario::Usuario(string user, string pass) {
    this->id = 0;
    this->username = user;
    this->password = pass;
    this->estadoLog = false;
    this->registrationDate = DateUtils::today();
    this->totalSessions = 0;
}

// ---  Métodos privados auxiliares ---

vector<UsuarioData> Usuario::cargarUsuarios() {
    vector<UsuarioData> usuarios;
    ifstream archivo("usuarios.csv");
    
    if (archivo.is_open()) {
        string linea;
        getline(archivo, linea); // Saltar header
        
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            
            vector<string> campos = CSVParser::split(linea);
            if (campos.size() >= 5) {
                UsuarioData userData;
                userData.id = stoi(campos[0]);
                userData.username = campos[1];
                userData.password = campos[2];
                userData.registrationDate = DateUtils::parseDate(campos[3]);
                userData.totalSessions = stoi(campos[4]);
                usuarios.push_back(userData);
            }
        }
        archivo.close();
    }
    
    return usuarios;
}

void Usuario::guardarUsuario(const UsuarioData& userData) {
    ofstream archivo("usuarios.csv", ios::app);
    
    if (archivo.is_open()) {
        archivo << userData.id << ","
                << userData.username << ","
                << userData.password << ","
                << DateUtils::formatDate(userData.registrationDate) << ","
                << userData.totalSessions << endl;
        archivo.close();
        cout << "Usuario guardado exitosamente." << endl;
    } else {
        cout << "Error: No se pudo guardar el usuario." << endl;
    }
}

bool Usuario::usuarioExiste(const string& user) {
    vector<UsuarioData> usuarios = cargarUsuarios();
    for (const auto& u : usuarios) {
        if (u.username == user) return true;
    }
    return false;
}

int Usuario::obtenerNuevoId() {
    vector<UsuarioData> usuarios = cargarUsuarios();
    int maxId = 0;
    for (const auto& u : usuarios) {
        if (u.id > maxId) maxId = u.id;
    }
    return maxId + 1;
}

void Usuario::actualizarArchivo(const vector<UsuarioData>& usuarios) {
    ofstream archivo("usuarios.csv", ios::trunc);
    if (archivo.is_open()) {
        // Escribir header
        archivo << "id,username,password,registrationDate,totalSessions" << endl;
        
        // Escribir usuarios
        for (const auto& u : usuarios) {
            archivo << u.id << ","
                    << u.username << ","
                    << u.password << ","
                    << DateUtils::formatDate(u.registrationDate) << ","
                    << u.totalSessions << endl;
        }
        archivo.close();
    }
}

// ---  Métodos públicos ---

bool Usuario::login(string userIngresado, string passIngresada) {
    vector<UsuarioData> usuarios = cargarUsuarios();
    
    for (const auto& u : usuarios) {
        if (u.username == userIngresado && u.password == passIngresada) {
            this->id = u.id;
            this->username = u.username;
            this->password = u.password;
            this->registrationDate = u.registrationDate;
            this->totalSessions = u.totalSessions;
            this->estadoLog = true;
            cout << "Login exitoso. Bienvenido, " << this->username << "!" << endl;
            return true;
        }
    }
    
    this->estadoLog = false;
    cout << "Error: Usuario o contrasena incorrectos." << endl;
    return false;
}

void Usuario::logout() {
    this->estadoLog = false;
    cout << "Sesion cerrada para " << this->username << "." << endl;
}

void Usuario::cambiarPassword(string nuevaPass) {
    if (this->estadoLog) {
        this->password = nuevaPass;
        
        vector<UsuarioData> usuarios = cargarUsuarios();
        for (auto& u : usuarios) {
            if (u.id == this->id) {
                u.password = nuevaPass;
                break;
            }
        }
        
        actualizarArchivo(usuarios);
        cout << "Contrasena actualizada para " << this->username << "." << endl;
    } else {
        cout << "Error: Debes iniciar sesion para cambiar la contrasena." << endl;
    }
}

bool Usuario::registrarse(string& nuevoUser, string& nuevaPass) {
    cout << "\n--- REGISTRO DE NUEVO USUARIO ---" << endl;
    
    cout << "Ingresa un nombre de usuario: ";
    cin >> nuevoUser;
    
    if (usuarioExiste(nuevoUser)) {
        cout << "Error: El usuario '" << nuevoUser << "' ya existe. Intenta con otro." << endl;
        return false;
    }
    
    cout << "Ingresa una contrasena: ";
    cin >> nuevaPass;
    
    UsuarioData userData;
    userData.id = obtenerNuevoId();
    userData.username = nuevoUser;
    userData.password = nuevaPass;
    userData.registrationDate = DateUtils::today();
    userData.totalSessions = 0;
    
    guardarUsuario(userData);
    cout << "Usuario '" << nuevoUser << "' registrado exitosamente!" << endl;
    
    return true;
}

void Usuario::incrementarSesiones() {
    if (this->estadoLog) {
        this->totalSessions++;
        
        vector<UsuarioData> usuarios = cargarUsuarios();
        for (auto& u : usuarios) {
            if (u.id == this->id) {
                u.totalSessions = this->totalSessions;
                break;
            }
        }
        
        actualizarArchivo(usuarios);
    }
}

void Usuario::mostrarEstado() {
    cout << "--- Estado del Usuario ---" << endl;
    cout << "ID: " << this->id << endl;
    cout << "Username: " << this->username << endl;
    cout << "Logueado: " << (this->estadoLog ? "Si" : "No") << endl;
    cout << "Fecha de registro: " << DateUtils::formatDate(this->registrationDate) << endl;
    cout << "Sesiones totales: " << this->totalSessions << endl;
}

// --- Getters ---

int Usuario::getId() const {
    return this->id;
}

string Usuario::getUsername() const {
    return this->username;
}

bool Usuario::getEstadoLog() const {
    return this->estadoLog;
}

chrono::year_month_day Usuario::getRegistrationDate() const {
    return this->registrationDate;
}

int Usuario::getTotalSessions() const {
    return this->totalSessions;
}
