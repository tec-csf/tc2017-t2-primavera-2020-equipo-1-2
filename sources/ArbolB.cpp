#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;


template <class T>
class arbolB{

    NodoArbol *raiz;    //Apuntador al nodo raíz
    int grados;         // Valor que define cantidad de números que tendrá el bloque

public:
    arbolB(int val);
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

    int noGrados = 5;
    int cantValores;    // Cantidad de valores aleatorios que se insertarán en el Árbol
    //arbolB grados(noGrados);   //Se predefinió que cada grupo va a alojar 5 números.

    cout << "¿Cuántos valores quieres que se ingresen al árbol?" << endl;
    cout << "10\t100\t1000\t10000\t100000\t1000000" << endl;

    cin >> cantValores;

    auto start = high_resolution_clock::now();
    switch (cantValores)
    {
    

    case 10:
        
        break;
    
    case 100:

        break;

    case 1000:

        break;

    case 10000:

        break;

    case 100000:

        break;

    case 1000000:

        break;

    default:

        cout << "Porfavor, seleccione una de las opciones disponibles" << endl;

        break;
    }

    auto stop = high_resolution_clock::now();
    auto durationMilli = duration_cast<milliseconds>(stop - start);
    cout << "Le tomo " << durationMilli.count() << " milisegundos\n";

    return 0;
}
