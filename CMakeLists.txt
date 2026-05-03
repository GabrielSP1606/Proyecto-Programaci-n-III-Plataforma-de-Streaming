cmake_minimum_required(VERSION 4.0)
project(PROYECTO_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROYECTO_1 main.cpp
        cargador_csv.h
        cargador_csv.cpp
        pelicula.h
        preprocesador.h
        preprocesador.cpp)
