#include "cargador_csv.h"
#include <fstream>
#include <iostream>
using namespace std;


string leerRegistroCompleto(ifstream& archivo) {
    string linea, registro;
    int comillas = 0;

    while (getline(archivo, linea)) {
        registro += linea + "\n";

        for (char c : linea) {
            if (c == '"') comillas++;
        }

        if (comillas % 2 == 0) break;
    }

    return registro;
}

vector<string> parsearCSV(const string& texto) {
    vector<string> campos;
    string actual;
    bool enComillas = false;

    for (char c : texto) {
        if (c == '"') {
            enComillas = !enComillas;
        }
        else if (c == ',' && !enComillas) {
            campos.push_back(actual);
            actual.clear();
        }
        else {
            actual += c;
        }
    }

    campos.push_back(actual);
    return campos;
}

vector<Pelicula> cargarCSV(const string& archivoNombre) {
    ifstream archivo(archivoNombre);
    vector<Pelicula> peliculas;

    if (!archivo.is_open()) {
        cout << "Error al abrir archivo\n";
        return peliculas;
    }

    string cabecera;
    getline(archivo, cabecera);

    while (!archivo.eof()) {
        string registro = leerRegistroCompleto(archivo);

        if (registro.empty())
            continue;

        vector<string> campos = parsearCSV(registro);

        if (campos.size() < 8)
            continue;

        Pelicula p;

        p.releaseYear = campos[0];
        p.titulo      = campos[1];
        p.origen      = campos[2];
        p.director    = campos[3];
        p.cast        = campos[4];
        p.genero      = campos[5];
        p.url         = campos[6];
        p.sinopsis    = campos[7];

        peliculas.push_back(p);
    }

    archivo.close();
    return peliculas;
}
