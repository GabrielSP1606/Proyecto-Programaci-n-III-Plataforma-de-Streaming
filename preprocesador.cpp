#include "preprocesador.h"


string normalizar(string texto) {
    string r = "";

    for (int i = 0; i < texto.size(); i++) {
        char c = texto[i];


        if (c >= 'A' && c <= 'Z') {
            c = c + 32;
        }


        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ') {
            r += c;
        }
    }

    return r;
}

vector<string> tokenizar(string texto) {
    vector<string> palabras;
    string actual = "";

    for (int i = 0; i < texto.size(); i++) {
        if (texto[i] == ' ') {
            if (actual != "") {
                palabras.push_back(actual);
                actual = "";
            }
        } else {
            actual += texto[i];
        }
    }

    if (actual != "") {
        palabras.push_back(actual);
    }

    return palabras;
}