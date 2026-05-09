# Programación III: Plataforma de Streaming

**Integrantes:**
- Ariel Mathias Fernando Choque Marcelo
- Marco Antonio Benito Corimanya Juarez 
- Ernesto Yen Mendoza Aguilar
- Adrian Gabriel Rojas Tejada
- Gabriel Omar Saavedra Peralta

---

## ¿Por qué elegimos el Trie?

Elegimos el Trie porque permite buscar palabras por prefijo de forma muy eficiente. Por ejemplo, si el usuario escribe "bat", el programa encuentra todas las películas que contienen palabras que empiezan con "bat" sin tener que revisar todo el dataset. Además es sencillo de implementar en C++ sin necesidad de librerías externas.

---

## Estructura de un nodo

Cada nodo del Trie tiene:
- 36 cajitas (una por cada letra a-z y cada número 0-9)
- Una marca que indica si en ese nodo termina una palabra
- Una lista que registra en qué películas apareció esa palabra y cuántas veces

---

## Diagrama del árbol

Ejemplo con las palabras "bat" y "bad":


  ```
raiz
└── b
    └── a
        ├── t (fin de palabra)
        └── d (fin de palabra)
```
*La marca de fin de palabra indica que ahí termina un token válido y se guarda el ID de la película correspondiente.*

---

## Algoritmo de inserción

1. *Proceso de Inserción*

Cada palabra que proviene del preprocesamiento se ingresa al Trie carácter por carácter.
Primero, se obtiene el índice del carácter actual, donde las letras a-z ocupan los índices 0-25 y los números 0-9 ocupan los índices 26-35.
Si el nodo correspondiente a ese índice no existe, se crea uno nuevo.
Al llegar al último carácter de la palabra, se marca ese nodo como fin de palabra y se incrementa el contador de la película correspondiente.

2. *Construcción del Trie*

Para construir el Trie completo, se itera sobre todas las películas del dataset.
Por cada película, se concatena su título, sinopsis, director, género y cast en un solo texto.
Ese texto pasa por la función *normalizar()* y *tokenizar()* para obtener las palabras limpias.
Finalmente, cada palabra se inserta en el Trie asociada al índice de su película.

3. *Pseudocódigo*

Funcion insertar(palabra, idPelicula): Algoritmo que ingresa una palabra al Trie y la asocia a una película.
```
ALGORITMO insertar(palabra, idPelicula)
nodo actual = raiz
PARA CADA caracter EN palabra:
    indice = obtenerIndice(caracter)
    SI indice ES invalido (-1) ENTONCES:
        CONTINUAR al siguiente caracter
    SI nodo actual.hijos[indice] ES nulo ENTONCES:
        crear nuevo NodoTrie en nodo actual.hijos[indice]
    nodo actual = nodo actual.hijos[indice]

nodo actual.esFin = verdadero
nodo actual.contadorPeliculas[idPelicula]++
FIN del ALGORITMO
```


Funcion construirTrie(peliculas): Función que itera todas las películas y las ingresa al Trie.
```
ALGORITMO construirTrie(peliculas)
PARA CADA pelicula EN peliculas CON indice i:
contenido = pelicula.titulo + pelicula.sinopsis +
pelicula.director + pelicula.genero + pelicula.cast
contenido limpio = normalizar(contenido)
palabras = tokenizar(contenido limpio)
    PARA CADA palabra EN palabras:
        insertar(palabra, i)

FIN del ALGORITMO
```

---

## Algoritmo de búsqueda

1. *Proceso de Búsqueda*

La frase o palabra ingresada por el usuario se procesa por la función *normalizar()* para eliminar tildes, caracteres especiales y convertir todo a minúsculas.
Se recorre el árbol nodo por nodo siguiendo los caracteres de la consulta. Si se interrumpe el camino significaría que no existen coincidencias.
Una vez alcanzado el último nodo de la consulta, se realiza un recorrido profundo sobre todo el subárbol. Esto permite encontrar películas donde el término buscado es solo el inicio de la palabra.

Ejemplo:

  ```
"bar" -> "barco","barista"
```

2. *Pseudocódigo*

Funcion buscar(consulta): Algoritmo que localiza el nodo del prefijo y realiza la recolección de datos.
  ```
ALGORITMO buscar(consulta)
consulta limpia = normalizar(consulta)
nodo actual = raiz
PARA CADA caracter EN consulta limpia:
    indice = obtenerIndice(caracter)
    SI nodo actual.hijos[indice] ES nulo ENTONCES:
        RETORNAR lista vacia
    nodo actual = nodo actual.hijos[indice]

resultados mapa = nuevo MapaVacio()
recolectarResultados(nodo actual, resultados mapa)

RETORNAR resultados mapa     
```


---

## Notas sobre el código de prueba

Durante el desarrollo de esta primera entrega, como equipo, decidimos implementar en C++ algunas funciones que originalmente solo requerían pseudocódigo. Esto fue necesario por dos razones:

**Para validar los pseudocódigos de P2 y P3:** Antes de documentar los algoritmos de inserción y búsqueda, implementamos el código real para verificar que la lógica funcionara correctamente con datos reales del dataset. Una vez validado, extrajimos esa lógica para escribir los pseudocódigos del README. Estas funciones están marcadas con `[TESTEO P2]` y `[TESTEO P3]` en el código.

**Para que P4 pudiera construir un prototipo funcional:** En lugar de hardcodear películas inventadas, P4 conectó la interfaz directamente al CSV real para poder validar que el preprocesamiento y la inserción producían resultados correctos. Esto está marcado con `[TESTEO P4]` en el código.

Todo el código marcado como testeo es un prototipo. Para la entrega 2 será corregido o mejorado.

---

## Limitaciones actuales y trabajo pendiente para entrega 2

- La búsqueda por frase (ejemplo: "barco fantasma") aún no está implementada
- El algoritmo de similitud por Likes está pendiente
- La búsqueda por tag específico (solo director, solo género) está pendiente
- La interfaz actual es un prototipo de prueba, será reemplazada por la versión final
