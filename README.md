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

*Pendiente de persona 3*
