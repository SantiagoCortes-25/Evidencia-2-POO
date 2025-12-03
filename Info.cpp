#include <iostream>
#include <fstream>
#include <string>
#include "Info.h"

using namespace std;

void Info:: cargarArchivo(string nombreArchivo){
  // Agregar extension .txt si no tiene extension
  string archivoCompleto = nombreArchivo;
  if (nombreArchivo.find('.') == string::npos) {
    archivoCompleto += ".txt";
  }
  
  ifstream archivo(archivoCompleto);

  if (archivo.is_open()){
    string linea;
    cout << "\n--- Contenido de " << archivoCompleto << " ---\n";

    while (getline(archivo, linea)){
      cout << linea << endl;
    }
    cout << "---------------------\n";
    archivo.close();
  } else {
    cerr << "Error: no se pudo abrir el archivo " << archivoCompleto << endl;
  }

}

void Info::mostrarCSV(string nombreArchivo){
  // Agregar extension .csv si no tiene extension
  string archivoCompleto = nombreArchivo;
  if (nombreArchivo.find('.') == string::npos) {
    archivoCompleto += ".csv";
  }
  
  ifstream archivo(archivoCompleto);
  
  if (!archivo.is_open()) {
    cerr << "Error: no se pudo abrir el archivo " << archivoCompleto << endl;
    return;
  }
  
  cout << "\n========================================\n";
  cout << "     CONTACTOS DE APOYO - DISLEXIA     \n";
  cout << "========================================\n\n";
  
  string linea;
  bool esPrimeraLinea = true;
  
  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string nombre, contacto;
    
    // Separar por coma (CSV)
    getline(ss, nombre, ',');
    getline(ss, contacto, ',');
    
    if (esPrimeraLinea) {
      // Encabezado en mayusculas y con separador
      cout << left << setw(45) << nombre << " | " << contacto << endl;
      cout << string(80, '-') << endl;
      esPrimeraLinea = false;
    } else {
      // Datos normales con formato de tabla
      cout << left << setw(45) << nombre << " | " << contacto << endl;
    }
  }
  
  cout << "========================================\n";
  archivo.close();
}
