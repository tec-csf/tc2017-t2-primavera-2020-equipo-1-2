# Tarea *2*. *Análisis de Algoritmos*

---

##### Integrantes:
1. Luis Daniel Roa González - A01021960 - Campus Santa Fe
2. Katia Yareth Bellido López - A01023638 - Campus Santa Fe
3. Constanza Gómez Sánchez - A01026717 - Campus Santa Fe
4. Christopher Luis Miranda Vanegas - A01022676 - Campus Santa Fe
5. Miguel Monterrubio Bandera - A01022153 - Campus Santa Fe

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución

*[Incluya aquí una explicación de la solución implementada]*

### 2.1 Pasos a seguir para utilizar la aplicación
*[Incluya aquí una guía paso a paso para poder utilizar la aplicación, desde la clonación del repositorio, la compilación del código hasta la ejecución de los ejemplos para visualizar los resultados.]*
* Contar con acceso a internet
* Contar con una terminal
	* La terminal debe tener gcc instalado
	* La terminal debe tener git instalado
	* La terminal debe poder clonar un repositorio de git (cuenta con acceso a la red)

#### Para clonar el repositorio
1. Crear una carpeta en la que se vaya a clonar el repositorio
2. Mediante la terminal, navegar a dicha carpeta
3. Correr el comando `git clone https://github.com/tec-csf/tc2017-t2-primavera-2020-equipo-1-2`

#### Para correr el programa
1. Mediante la terminal, navegar a la carpeta sources
2. Correr el comando: `g++ -o AB ArbolB.cpp -std=c++17`
3. Correr el comando: `./AB -i ../examples/diez.txt`
4. Correr el comando: `g++ -o AVL ArbolAVL.cpp -std=c++17`
5. Correr el comando: `./AVL`

## 3. Referencias
> https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
> https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
> https://rosettacode.org/wiki/AVL_tree#C.2B.2B