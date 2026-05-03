#include "trie.h"
#include "preprocesador.h"
#include <iostream>

NodoTrie::NodoTrie() {
    for (int i = 0; i < 36; i++) hijos[i] = nullptr;
    esFin = false;
}

Trie::Trie() {
    raiz = new NodoTrie();
}

int Trie::obtenerIndice(char c) {
    if (c >= 'a' and c <= 'z') return c - 'a';
    if (c >= '0' and c <= '9') return c - '0' + 26;
    return -1; // ignoamos los caracteres que no son letras ni numeros
}

void Trie::insertar(const string& palabra, int idPelicula) {
    NodoTrie* actual = raiz;
    for (char c : palabra) {
        int indice = obtenerIndice(c);
        if (indice == -1) continue; // saltar caracteres invalidos

        if (actual->hijos[indice] == nullptr) {
            actual->hijos[indice] = new NodoTrie();
        }
        actual = actual->hijos[indice];
    }
    actual->esFin = true;
    actual->contadorPeliculas[idPelicula]++;
}

void Trie::construirTrie(const vector<Pelicula>& peliculas) {
    for (int i = 0; i < peliculas.size(); i++) {
        string contenido = peliculas[i].titulo + " " + 
                           peliculas[i].sinopsis + " " + 
                           peliculas[i].director + " " + 
                           peliculas[i].genero + " " + 
                           peliculas[i].cast;

        string limpio = normalizar(contenido);
        vector<string> palabras = tokenizar(limpio);

        for (const string& pal : palabras) {
            insertar(pal, i); 
        }
        
        if (i % 1000 == 0) cout << "Indexadas " << i << " peliculas..." << endl;
    }
}