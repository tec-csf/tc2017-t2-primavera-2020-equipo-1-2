#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Ramas{
    int *valores;
    int grados;
    Ramas **apun;
    int x; 
    bool war; //waraq == hoja (en árabe)

public:
    Ramas(int grados, bool war );

    void insertarVacio(int nuevo);

    void separaBloque(int i, Ramas *z);

    void atraviesa();

    Ramas *busqueda(int lost);
};

template <class T>
class arbolB{

    NodoArbol *raiz;    //Apuntador al nodo raíz
    int grados;         // Valor que define cantidad de números que tendrá el bloque

public:
    arbolB(int val);
    void atraviesa(){
        raiz = NULL;
        
    }
    void insertar(int nuevo);
    void busqueda(int lost);
    void eliminar(int posKey)
        {
            int remover = 0; // aquí se va a agregar de buscar la posición en donde se encuentra
        }
        void impresionValores();

};

void 

int main()
{

    int noGrados = 5;
    int cantValores;    // Cantidad de valores aleatorios que se insertarán en el Árbol
    //arbolB grados(noGrados);   //Se predefinió que cada grupo va a alojar 5 números.

    cout << "¿Cuántos valores quieres que se ingresen al árbol?" << endl;
    cout << "1) 10\t2) 100\t3) 1000\t4) 10000\t5) 100000\t6) 1000000" << endl;

    cin >> cantValores;

    auto startIn = high_resolution_clock::now();
    switch (cantValores)
    {
    

    case 1:

        cout << "Se insertarán " << cantValores << " aleatorios." << endl;



        auto stopIn = high_resolution_clock::now();
        auto durationMilli = duration_cast<milliseconds>(stopIn - startIn);
        cout << "Le tomo " << durationMilli.count() << " milisegundos\n";

        break;
    
    case 2:

        break;

    case 3:

        break;

    case 4:

        break;

    case 5:

        break;

    case 6:

        break;

    default:

        cout << "Porfavor, seleccione una de las opciones disponibles" << endl;

        break;
    }

    

    return 0;
}
