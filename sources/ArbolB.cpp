#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

template <class T>
class arbolB{

    

    public:
    arbolB();
    void insertar();
    void busqueda();
    void eliminar(int posKey)
    {
        int remover = 0; // aquí se va a agregar de buscar la posición en donde se encuentra

        
    }
    void impresionValores();

};

int main()
{

    int grados = 5;     // Valor que define cantidad de números que tendrá el bloque
    int cantValores;    // Cantidad de valores aleatorios que se insertarán en el Árbol

    arbolB(grados);


    return 0;
}
