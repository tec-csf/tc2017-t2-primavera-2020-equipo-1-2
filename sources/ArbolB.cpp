#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

class Ramas{
    int *valores;   //llave de valores
    int grados;     //definición de grados
    Ramas **apun;   //apuntadores para manipular los nodos
    int x;          //número actual de valores
    bool waraq;       //waraq == hoja (en árabe)

public:
    Ramas(int grados_, bool waraq_);

    void insertarVacio(int nuevo);

    void separaBloque(int i, Ramas *z);

    void atraviesa();

    Ramas *busqueda(int nuevo);

    template <class T>
    friend class arbolB;
};

template <class T>
class arbolB{

    Ramas *raiz;    //Apuntador al nodo raíz
    int grados;         // Valor que define cantidad de números que tendrá el bloque

public:
    arbolB(int grados_)
    {
        raiz = NULL;
        grados = grados_;
    }

    void atraviesa()
    {
        if (raiz != NULL)
        {
            raiz->atraviesa();
        }
    }//fin atraviesa

    Ramas* busqueda(int lost)
    {
        return(raiz == NULL)? NULL : raiz->busqueda(lost);
    }

    void insertar(int lost);

    void eliminar(int posKey)
        {
            int remover = 0; // aquí se va a agregar de buscar la posición en donde se encuentra
        }
        void impresionValores();

};

Ramas::Ramas(int val1, bool ramita)
{
    grados = val1;
    waraq = ramita;

    valores = new int[2*grados-1];
    apun = new Ramas *[2*grados];

    x = 0;
}

void Ramas::atraviesa()
{
    int i;
    for (i = 0; i < x; i++)
    {
        if (waraq == false)
            apun[i]->atraviesa();
        cout << " " << valores[i];
        
    }

    if(waraq == false)
        apun[i]->atraviesa();
    
}

Ramas *Ramas::busqueda(int nuevo)
{
    int i = 0;
    while (i < x && nuevo > valores[i])
    {
        i++;
    }
    
    if (valores[i] == nuevo)
    {
        return this;
    }
    
    if (waraq == true)
    {
        return NULL;
    }
    
    return apun[i]->busqueda(nuevo);
}
template<>
void arbolB<class T>::insertar(int lost)
{
    
    if (raiz == NULL)
    {
        raiz = new Ramas(grados, true);
        raiz->valores[1] = lost;
        raiz->x = 1;
    }
    else
    {
        if (raiz->x == 2*grados-1)
        {
            Ramas *s = new Ramas(grados, false);

            s->apun[0] = raiz;

            s->separaBloque(0, raiz);

            int cont = 0;
            if (s->valores[0] < lost)
                cont++;
            s->apun[cont]->insertarVacio(lost);
            
            raiz=s;

        }
        else
        {
            raiz->insertarVacio(lost);
        }   
    }
}

void Ramas::insertarVacio(int lost)
{
    int cont = x-1;

    if (waraq == true)
    {
        while (cont >= 0 && valores[cont] > lost)
        {
            valores[cont+1] = valores[cont];
            cont--;
        }
        
        valores[cont+1] = lost;
        x=x+1;
    }
    else
    {
        while (cont >= 0 && valores[cont] > lost)
            cont--;

        if (apun[cont+1]->x == 2*grados-1)
        {
            separaBloque(cont+1, apun[cont+1]);

            if (valores[cont+1] < lost)
            {
                cont++;
            }
            
        }
        apun[cont+1]->insertarVacio(lost);
    }
    
}

void Ramas::separaBloque(int i, Ramas *z)
{
    Ramas *a = new Ramas(z->grados, z->waraq);
    a->x = grados-1;

    for (int cont = 0; cont < grados-1; grados++)
        a->valores[cont] = z->valores[cont+grados];

    if (z->waraq == false)
    {
        for (int i = 0; i < 0; i++)
        {
            a->apun[i] = z->apun[i+grados];
        }
        
    }
    
    z->x = grados-1;
    
    for (int a = x; a >= i+1; a--)
    {
        apun[a+1] = apun[a];
    }
    

    valores[i] = z->valores[grados-1];

    x=x+1;
}

int main(int argc, char const *argv[])
{

    string inputDoc, nombreArchivo, number;
    fstream inputFile;
    int nuevoNo;

    int noGrados = 5;
    int cantValores;    // Cantidad de valores aleatorios que se insertarán en el Árbol
    arbolB <int> grados(noGrados);   //Se predefinió que cada grupo va a alojar 5 números.

    nombreArchivo = argv[2];

    inputFile.open(nombreArchivo.c_str());

    if (inputFile.is_open())
    {
        while (getline(inputFile, number))
        {
            nuevoNo = stoi(number);

            grados.insertar(nuevoNo);

            cout << "Números: " << nuevoNo << endl;
        }
        
    }
    
    inputFile.close();

    auto startIn = high_resolution_clock::now();
    
    auto stopIn = high_resolution_clock::now();
    auto durationMilli = duration_cast<milliseconds>(stopIn - startIn);


    return 0;
}
