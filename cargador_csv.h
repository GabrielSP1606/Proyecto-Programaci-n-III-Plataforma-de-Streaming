#ifndef PROYECTO_1_CARGADOR_CSV_H
#define PROYECTO_1_CARGADOR_CSV_H


#include <vector>
#include <string>
#include "pelicula.h"

using namespace std;


vector<Pelicula> cargarCSV(const string& archivo);
string leerRegistroCompleto(ifstream& archivo);
vector<string> parsearCSV(const string& linea);


#endif //PROYECTO_1_CARGADOR_CSV_H