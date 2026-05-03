#include <iostream>
#include "cargador_csv.h"
#include <fstream>
#include <vector>
#include <string>
#include "preprocesador.h"

using namespace std;


int main() {
    vector<Pelicula> pelis = cargarCSV("../wiki_movie_plots_deduped.csv");

    for (int i = 0; i < 4; i++) {

        string texto = pelis[i].titulo + " " + pelis[i].sinopsis;

        string limpio = normalizar(texto);

        vector<string> palabras = tokenizar(limpio);

        cout << "Pelicula: " << pelis[i].titulo << endl;

        for (int j = 0; j < 5 && j < palabras.size(); j++) {
            cout << palabras[j] << " ";
        }

        cout << "\n-----------------\n";
    }

    
    Trie miTrie;
    cout << "Construyendo estructura de busqueda" << endl;
    miTrie.construirTrie(pelis);
    
    return 0;

}