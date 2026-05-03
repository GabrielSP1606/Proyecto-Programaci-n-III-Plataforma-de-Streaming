#ifndef LISTA_VER_MAS_TARDE_H
#define LISTA_VER_MAS_TARDE_H

#include <vector>
#include <string>
#include "pelicula.h"
using namespace std;

vector<int> listaVerMasTarde;
vector<int> listaLikes;

void agregarVerMasTarde(int idPelicula);
void agregarLike(int idPelicula);
void cargarListas();
void guardarListas();
void mostrarVerMasTarde(const vector<Pelicula>& peliculas);

#endif