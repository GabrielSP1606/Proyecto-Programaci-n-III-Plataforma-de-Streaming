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

*Pendiente de persona 2*

---

## Algoritmo de búsqueda

1. *Proceso de Busqueda*

La frase o palabra ingresada por el usuario se procesa por la function *normalizar()* para eliminar tildes, carecteres especiales y convertir todo a minusculas. 
También, se recorre el arbol nodo por nodo siguiendo los caracteres de la consulta, cosa que si se interrumpe el camino significaria que no existe coincidencias.
Por último, una vez alcanzado el último nodo de la consulta, se realiza un recorrido profundo sobre todo el subarbol. Esto permite encontrar peliculas donde el termino buscando es solo el inicio de la palabra.

Ejemplo:

  ```
"bar" -> "barco","barista"
```

2. *Algoritmo de Relevancia*

Para determinar que peliculas tiene más importancia, se diseñó un algoritmo basado en la frecuencia de terminos.
Primero, cada nodo del Trie almacena un *map<int, int>* donde la llave es el *idPelicula* y el valor es la frecuencia de la palabra en esa pelicula.
Segundo, al buscar, se suma las frecuencias de todas las palabras encontradas en el subarbol para cada pelicula.
Por último, se utiliza una cola de prioridad (*priority_queue*) para ordenar los resultados de mayor a menor frecuencia acumulada. Esto aseguraria que una pelicula que menciona "fantasma" diez veces aparezca antes que una que la menciona solo una vez.

3. *Paginacion de Resultados*

Dado que una busqueda puede arrojar miles de posibles resultados se decidio por implementar una funcion de paginacion.
Por lo que determinamos dos cosas:

Capacidad: los resultados se muestren en bloques de 5 en 5 peliculas.

Logica: se calcula el índice de incio mediante *(página - 1 ) * 5*, lo cual nos permite la interfaz del usuario corra de una manera fluida y evitar que sufra de una saturacion de información.

4. *Complejidad*

- Busqueda de Prefijo: *O(L)*, donde *L* es la longitud del término buscado.
- Recoleccion: *O(N)*, donde *N* es el numero de nodos en el subarbol de la coincidencia.
- Ranking: *O(K log K)*, donde *K* es el número de peliculas encontradas.

5. *Pseudocódigo*

Funcion buscar(consulta): Algoritmo que localiza el nodo del prefijo y para la recoleccion de datos.
  ```
*ALGORITMO buscar(consulta)*
    consulta limpia = normalizar(consulta)
    nodo actual = raiz
    
    PARA CADA carecter EN consulta limpia:
        indice = obtenerIndice(caracter)
        SI nodo actual.hijos[indice] ES nulo Entonces:
            RETORNAR lista vacia
        nodo actual = nodo actual.hijos[indice]
    
    resultados mapa = nuevo MapaVacio()
    recolectarResultados(nodo actual, resultados mapa)
    
    cola prioridad = nueva PriorityQueue()
    PARA CADA (idPelicula, frecuencia) EN resultados mapa:
        cola prioridad.insertar(idPelicula, frecuencia)
    
    RETORNAR lista ordenada desde cola prioridad
FIN del ALGORITMO        
```

Funcion recolectarResultados(nodo, mapa): Funcion recursiva que permite encontra sub-palabras.
  ```
*ALGORITMO recolectarResutados(nodo, mapa acumulador)*
    SI nodo ES nulo ENTONCES RETORNAR
    
    PARA CADA (idPelicula, frec) EN nodo.contadorPeliculas:
        mapa acumulador[idPelicula] += frec
    
    PARA i DESDE 0 HASTA 35:
        SI nodo.hijos[i] NO ES nulo ENTONCES:
            recolectarResultados(nodo.hijos[i], mapa acumulador)
FIN del ALGORITMO        
```


