#include "trie.h"
#include "preprocesador.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector <Resultado> Trie::buscar(string consulta) {
    string limpio = normalizar(consulta);
    NodoTrie* actual = raiz;
    for (char c : limpio) {
        int indice = obtenerIndice(c);
        if (indice == -1) continue;

        if (actual->hijos[indice]==nullptr) {
            return {};
        }
        actual = actual->hijos[indice];
    }
    unordered_map<int, int> consolidado;
    recolectarResultados(actual, consolidado);
    priority_queue<Resultado> pq;
    for (auto const& [id, frec] : consolidado) {
        pq.push({id, frec});
    }
    vector<Resultado> listaOrdenada;
    while (!pq.empty()) {
        listaOrdenada.push_back(pq.top());
        pq.pop();
    }

    return listaOrdenada;
}

void Trie::recolectarResultados(NodoTrie *nodo, unordered_map<int, int> &resultadosAcumulados) {
    if (nodo == nullptr) return;
    for (auto const& [id, frec] : nodo->contadorPeliculas) {
        resultadosAcumulados[id] += frec;
    }

    for (int i = 0; i < 36; i++) {
        if (nodo->hijos[i] != nullptr) {
            recolectarResultados(nodo->hijos[i], resultadosAcumulados);
        }
    }
}

vector<Resultado> Trie::obtenerPagina(const vector<Resultado>& resultados, int pagina, int tamanoPagina) {
    vector<Resultado> subLista;

    int inicio = (pagina - 1) * tamanoPagina;

    if (inicio >= resultados.size() || pagina <= 0) return {};

    for (int i = inicio; i < inicio + tamanoPagina && i < resultados.size(); i++) {
        subLista.push_back(resultados[i]);
    }

    return subLista;
}

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
        
        if (i % 1000 == 0) cout << "Indexadas " << i << " peliculas" << endl;
    }
}
// [TESTEO: No finalizado aún]// [TESTEO: No finalizado aun]
