    #include <iostream>
    #include "cargador_csv.h"
    #include <fstream>
    #include <vector>
    #include <string>
    #include "preprocesador.h"
    #include "trie.h"

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
        cout << "Construyendo estructura de busqueda.... " << endl;
        miTrie.construirTrie(pelis);
        cout << "Trie construido con exito" << endl;

        string consulta;
        cout << "\nIngrese su la busqueda que desea: ";
        cin >> consulta;

        vector <Resultado> resultados = miTrie.buscar(consulta);
        if (resultados.empty()) {
            cout << "No se encontraron coincidencias para: " << consulta << endl;
        } else {
            cout << "Se encontraron " << resultados.size() << " coinciencias." << endl;
            int paginaActual = 1;
            vector<Resultado> pagina = miTrie.obtenerPagina(resultados, paginaActual);
            cout << "\n--- Resulados Pagina " << paginaActual << " (Top 5) ---" << endl;
            for (const auto& res: pagina) {
                cout << "ID: " << res.idPelicula << " | Titulo " << pelis[res.idPelicula].titulo << " | Relevancia: " << res.relevancia << endl;
            }
        }

        return 0;

    }