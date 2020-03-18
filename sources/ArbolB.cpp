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

    int encontrarLlave(int nuevo);

    void eliminar(int nuevo);

    void eliminarHoja(int index);

    void eliminarPadre(int index);

    void obtenerPredecesor(int index);

    void obternerSucesor(int index);

    void llenar(int index);

    void tomarPrevio(int index);

    void tomarSiguiente(int index);

    void mezclaa(int index);

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

    void eliminar(int lost);

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
void arbolB<int>::insertar(int lost)
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
int Ramas::encontrarLlave(int nuevo)
{
    int i = 0;
    while(i < x && valores[i]<nuevo)
    {
        ++i;
    }
    return i;
}
void Ramas::eliminar(int lost)
{
    int i = encontrarLlave(lost);

    if(i < x && valores[i] == lost) //si es la llave a ser eliminada en el nodo
    {
        //si el nodo es un nodo Hoja se llama eliminarHoja, de otra forma eliminarPadre sera llamado
        if(waraq)
            eliminarHoja(i);
        else
        {
            eliminarPadre(i);
        }
        
    }
    else
    {
        //si no esta presente y es un nodo hoja entonces no esta presente en el arbol
        if(waraq)
        {
            cout<<"el valor "<<lost << " no existe en el árbol"<<endl;
            return;
        }
        //la bandera ayuda a saber si el valor se encuentra en un subárbol
        bool bandera = ((i==x)? true : false);

        //si el hijo donde tiene menos valores de grado entonceshay que llenarlo
        if (apun[i] -> x < grados)
        {
            llenar(i);
        }

        //usamos recursividad para mezclar en la hoja i-1. 
        //Si no, usamos recursividad en la hoja i que ahora tendría valores en grados 
        if(bandera && i > x)
        {
            apun[i-1]->eliminar(lost);
        }
        else
        {
            apun[i]-> eliminar(lost);
        }
    }
    return;
}

void Ramas::eliminarHoja(int index)
{
    //mueve todas las llaaves después de la posición index una posición en reversa
    for (int i = index+1; i < x; ++i)
    {
        valores[i-1] = valores[i];
    }
    //reduce el conteo de valores
    x--;
    return;
}

void Ramas::eliminarPadre(int index)
{
    int val = valores[index];

    if(apun[index]-> x >= grados)
    {

    }
}

int main(int argc, char const *argv[])
{

    string inputDoc, nombreArchivo, number;
    fstream inputFile;
    int nuevoNo, noOperaciones;

    int noGrados = 5;
    int cantValores;    // Cantidad de valores aleatorios que se insertarán en el Árbol
    arbolB <int> grados(noGrados);   //Se predefinió que cada grupo va a alojar 5 números.

    ofstream inDoc("../examples//OutputInsertion.txt");

    cout << "Cuántos valores se van a insertar/borrar/buscar?" << endl;
    cin >> noOperaciones;

    cout << "El tiempo será tomado en microsegundos.\n" << endl;

    nombreArchivo = argv[2];

    inputFile.open(nombreArchivo.c_str());

    cout << "Número \t\t" << " |" << "\t\tTiempo que le tomó" << endl;
    cout << "--------------------------------------------------------" << endl;

    inDoc << "Número \t\t" << " |" << "\t\tTiempo que le tomó" << endl;
    inDoc << "--------------------------------------------------------" << endl;

    if (inputFile.is_open())
    {
        auto startIn = high_resolution_clock::now();

        while (getline(inputFile, number))
        {
            nuevoNo = stoi(number);

            grados.insertar(nuevoNo);

            auto stopIn = high_resolution_clock::now();
            auto durIn = duration_cast<microseconds>(stopIn - startIn);

            cout << "    "<< nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
            inDoc << "    " << nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
        }
        
    }
    inDoc.close();
    inputFile.close();

    cout <<"\nÁrbol reacomodado\n" << endl;
    grados.atraviesa();
    cout << endl;



    return 0;
}
