#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>
#include <map>
#include "pelicula.h"

using namespace std;

struct NodoTrie {
    NodoTrie* hijos[36]; // 26 letras + 10 números
    bool esFin;
    // Mapa: <idPelicula, frecuencia de la palabra en esa peli>
    map<int, int> contadorPeliculas;

    NodoTrie();
};

class Trie {
private:
    NodoTrie* raiz;
    int obtenerIndice(char c);

public:
    Trie();
    void insertar(const string& palabra, int idPelicula);
    void construirTrie(const vector<Pelicula>& peliculas);
    NodoTrie* getRaiz() { return raiz; } 
};

#endif