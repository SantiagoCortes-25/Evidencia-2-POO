#if !defined(Info_h)
#define Info_h
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std; 

class Info{
  private: 
  
  public: 
    void cargarArchivo(string nombreArchivo);
    void mostrarCSV(string nombreArchivo);
};



#endif // Info_h
