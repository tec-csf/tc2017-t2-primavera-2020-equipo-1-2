/*
 *  Arbol B - Seguna Tarea
 * 
 *  Análisis y diseño de algoritmos
 *  Fecha de entrega:
 *  22 de marzo del 2020
 */
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Ramas
{
    int *valores; //llave de valores
    int grados;   //definición de grados
    Ramas **apun; //apuntadores para manipular los nodos
    int x;        //número actual de valores
    bool waraq;   //waraq == hoja (en árabe)

public:
    Ramas(int grados_, bool waraq_);

    void atraviesa();

    Ramas *busqueda(int k);

    int encontrarLlave(int k);

    void insertarVacio(int k);

    void separaBloque(int i, Ramas *y);

    void eliminar(int k);

    void eliminarHoja(int idx);

    void eliminarPadre(int idx);

    int obtenerPredecesor(int idx);

    int obternerSucesor(int idx);

    void llenar(int idx);

    void tomarPrevio(int idx);

    void tomarSiguiente(int idx);

    void mezclar(int idx);

    template <class T>
    friend class arbolB;
};

template <class T>
class arbolB
{
    Ramas *raiz; //Apuntador al nodo raíz
    int grados;  // Valor que define cantidad de números que tendrá el bloque
public:
    arbolB(int grados_)
    {
        raiz = NULL;
        grados = grados_;
    }

    void atraviesa()
    {
        if (raiz != NULL)
            raiz->atraviesa();
    }

    Ramas *busqueda(int k)
    {
        return (raiz == NULL) ? NULL : raiz->busqueda(k);
    }

    void insert(int k);

    void eliminar(int k);
};

Ramas::Ramas(int val1, bool ramita)
{
    grados = val1;
    waraq = ramita;

    valores = new int[2 * grados - 1];
    apun = new Ramas *[2 * grados];

    x = 0;
}

int Ramas::encontrarLlave(int k)
{
    int idx = 0;
    while (idx < x && valores[idx] < k)
        ++idx;
    return idx;
}

void Ramas::eliminar(int k)
{
    int idx = encontrarLlave(k);

    if (idx < x && valores[idx] == k)
    {

        if (waraq)
            eliminarHoja(idx);
        else
            eliminarPadre(idx);
    }
    else
    {
        if (waraq)
        {
            cout << "No se encontró " << k << " en el árbol\n";
            return;
        }

        bool flag = ((idx == x) ? true : false);

        if (apun[idx]->x < grados)
            llenar(idx);

        if (flag && idx > x)
            apun[idx - 1]->eliminar(k);
        else
            apun[idx]->eliminar(k);
    }
    return;
}

void Ramas::eliminarHoja(int idx)
{

    for (int i = idx + 1; i < x; ++i)
        valores[i - 1] = valores[i];

    x--;

    return;
}

void Ramas::eliminarPadre(int idx)
{

    int k = valores[idx];

    if (apun[idx]->x >= grados)
    {
        int pred = obtenerPredecesor(idx);
        valores[idx] = pred;
        apun[idx]->eliminar(pred);
    }

    else if (apun[idx + 1]->x >= grados)
    {
        int succ = obternerSucesor(idx);
        valores[idx] = succ;
        apun[idx + 1]->eliminar(succ);
    }

    else
    {
        mezclar(idx);
        apun[idx]->eliminar(k);
    }
    return;
}

int Ramas::obtenerPredecesor(int idx)
{
    Ramas *cur = apun[idx];
    while (!cur->waraq)
        cur = cur->apun[cur->x];

    return cur->valores[cur->x - 1];
}

int Ramas::obternerSucesor(int idx)
{
    Ramas *cur = apun[idx + 1];
    while (!cur->waraq)
        cur = cur->apun[0];

    return cur->valores[0];
}

void Ramas::llenar(int idx)
{

    if (idx != 0 && apun[idx - 1]->x >= grados)
        tomarPrevio(idx);

    else if (idx != x && apun[idx + 1]->x >= grados)
        tomarSiguiente(idx);

    else
    {
        if (idx != x)
            mezclar(idx);
        else
            mezclar(idx - 1);
    }
    return;
}

void Ramas::tomarPrevio(int idx)
{

    Ramas *child = apun[idx];
    Ramas *sibling = apun[idx - 1];

    for (int i = child->x - 1; i >= 0; --i)
        child->valores[i + 1] = child->valores[i];

    if (!child->waraq)
    {
        for (int i = child->x; i >= 0; --i)
            child->apun[i + 1] = child->apun[i];
    }

    child->valores[0] = valores[idx - 1];

    if (!child->waraq)
        child->apun[0] = sibling->apun[sibling->x];

    valores[idx - 1] = sibling->valores[sibling->x - 1];

    child->x += 1;
    sibling->x -= 1;

    return;
}

void Ramas::tomarSiguiente(int idx)
{

    Ramas *child = apun[idx];
    Ramas *sibling = apun[idx + 1];

    child->valores[(child->x)] = valores[idx];

    if (!(child->waraq))
        child->apun[(child->x) + 1] = sibling->apun[0];

    valores[idx] = sibling->valores[0];

    for (int i = 1; i < sibling->x; ++i)
        sibling->valores[i - 1] = sibling->valores[i];

    if (!sibling->waraq)
    {
        for (int i = 1; i <= sibling->x; ++i)
            sibling->apun[i - 1] = sibling->apun[i];
    }

    child->x += 1;
    sibling->x -= 1;

    return;
}

void Ramas::mezclar(int idx)
{
    Ramas *child = apun[idx];
    Ramas *sibling = apun[idx + 1];

    child->valores[grados - 1] = valores[idx];

    for (int i = 0; i < sibling->x; ++i)
        child->valores[i + grados] = sibling->valores[i];

    if (!child->waraq)
    {
        for (int i = 0; i <= sibling->x; ++i)
            child->apun[i + grados] = sibling->apun[i];
    }

    for (int i = idx + 1; i < x; ++i)
        valores[i - 1] = valores[i];

    for (int i = idx + 2; i <= x; ++i)
        apun[i - 1] = apun[i];

    child->x += sibling->x + 1;
    x--;

    delete (sibling);
    return;
}

template <>
void arbolB<int>::insert(int k)
{
    // If tree is empty
    if (raiz == NULL)
    {
        raiz = new Ramas(grados, true);
        raiz->valores[0] = k;
        raiz->x = 1;
    }
    else
    {
        if (raiz->x == 2 * grados - 1)
        {
            Ramas *s = new Ramas(grados, false);

            s->apun[0] = raiz;

            s->separaBloque(0, raiz);

            int i = 0;
            if (s->valores[0] < k)
                i++;
            s->apun[i]->insertarVacio(k);

            raiz = s;
        }
        else
            raiz->insertarVacio(k);
    }
}

void Ramas::insertarVacio(int k)
{
    int i = x - 1;

    if (waraq == true)
    {
        while (i >= 0 && valores[i] > k)
        {
            valores[i + 1] = valores[i];
            i--;
        }

        valores[i + 1] = k;
        x = x + 1;
    }
    else
    {
        while (i >= 0 && valores[i] > k)
            i--;

        if (apun[i + 1]->x == 2 * grados - 1)
        {
            separaBloque(i + 1, apun[i + 1]);

            if (valores[i + 1] < k)
                i++;
        }
        apun[i + 1]->insertarVacio(k);
    }
}

void Ramas::separaBloque(int i, Ramas *y)
{
    Ramas *z = new Ramas(y->grados, y->waraq);
    z->x = grados - 1;

    for (int j = 0; j < grados - 1; j++)
        z->valores[j] = y->valores[j + grados];

    if (y->waraq == false)
    {
        for (int j = 0; j < grados; j++)
            z->apun[j] = y->apun[j + grados];
    }

    y->x = grados - 1;

    for (int j = x; j >= i + 1; j--)
        apun[j + 1] = apun[j];

    apun[i + 1] = z;

    for (int j = x - 1; j >= i; j--)
        valores[j + 1] = valores[j];

    valores[i] = y->valores[grados - 1];

    x = x + 1;
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

    if (waraq == false)
        apun[i]->atraviesa();
}

Ramas *Ramas::busqueda(int k)
{
    int i = 0;
    while (i < x && k > valores[i])
        i++;

    if (valores[i] == k)
        return this;

    if (waraq == true)
        return NULL;

    return apun[i]->busqueda(k);
}

template <>
void arbolB<int>::eliminar(int k)
{
    if (!raiz)
    {
        cout << "The tree is empty\n";
        return;
    }

    raiz->eliminar(k);

    if (raiz->x == 0)
    {
        Ramas *tmp = raiz;
        if (raiz->waraq)
            raiz = NULL;
        else
            raiz = raiz->apun[0];

        delete tmp;
    }
    return;
}

int main(int argc, char const *argv[])
{
    int noGrados = 5;

    arbolB<int> grados(noGrados); //Se predefinió que cada grupo va a alojar 5 números.

    string inputDoc, nombreArchivo, number;
    fstream inputFile;

    int nuevoNo, noOperaciones, perdu;
    int cantValores; // Cantidad de valores aleatorios que se insertarán en el Árbol

    ofstream inDoc("OutputInsertion.txt");
    ofstream searchDoc("OutputSearch.txt");
    ofstream delDoc("OutputDelete.txt");

    cout << "Cuántos valores se van a insertar/borrar/buscar?" << endl;
    cin >> noOperaciones;

    srand((unsigned)time(0));

    cout << "El tiempo será tomado en microsegundos.\n"
         << endl;

    nombreArchivo = argv[2];

    inputFile.open(nombreArchivo.c_str());

    cout << "Número \t\t"
         << " |"
         << "\t\tTiempo que le tomó" << endl;
    cout << "--------------------------------------------------------" << endl;

    inDoc << "Número \t\t"
          << " |"
          << "\t\tTiempo que le tomó" << endl;
    inDoc << "--------------------------------------------------------" << endl;

    if (inputFile.is_open())
    {
        auto startIn = high_resolution_clock::now();

        while (getline(inputFile, number))
        {
            nuevoNo = stoi(number);

            grados.insert(nuevoNo);

            auto stopIn = high_resolution_clock::now();
            auto durIn = duration_cast<microseconds>(stopIn - startIn);

            cout << "    " << nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
            inDoc << "    " << nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
        }
        cout << "Sale del ciclo" << endl;
    }
    inDoc.close();
    inputFile.close();

    cout << "\n\nInicio de búsqueda\n"
         << endl;

    int lost;

    cout << "\n\nNúmero \t\t"
         << " |"
         << "\t\t¿Se encontró?\t\t"
         << " |"
         << "\t\tTiempo que le tomó" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;

    searchDoc << "\n\nNúmero \t\t"
              << " |"
              << "\t\t¿Se encontró?\t\t"
              << " |"
              << "\t\tTiempo que le tomó" << endl;

    auto startBus = high_resolution_clock::now();

    for (int cont = 0; cont < noOperaciones; cont++)
    {
        lost = rand() % noOperaciones + 1;

        //cout << lost << endl;

        if (grados.busqueda(lost) != NULL)
        {
            auto stopBus = high_resolution_clock::now();
            auto durBus = duration_cast<microseconds>(stopBus - startBus);
            cout << "    " << lost << "\t\t | \t\t"
                 << "Encontrado"
                 << "\t\t | \t\t" << durBus.count() << endl;
        }
        else
        {
            auto stopBus = high_resolution_clock::now();
            auto durBus = duration_cast<microseconds>(stopBus - startBus);
            cout << "    " << lost << "\t\t | \t\t"
                 << "No se encontró"
                 << "\t\t | \t\t" << durBus.count() << endl;
        }
    }

    cout << "\n\nNúmero \t\t"
         << " |"
         << "\t\tTiempo que le tomó" << endl;
    cout << "--------------------------------------------------------" << endl;

    delDoc << "\n\nNúmero \t\t"
           << " |"
           << "\t\tTiempo que le tomó" << endl;
    delDoc << "--------------------------------------------------------" << endl;

    auto startDel = high_resolution_clock::now();

    for (int cont = 0; cont < noOperaciones; cont++)
    {
        lost = rand() % noOperaciones + 1;

        grados.eliminar(lost);

        auto stopDel = high_resolution_clock::now();
        auto durDel = duration_cast<microseconds>(stopDel - startDel);

        cout << "    " << lost << "\t\t | \t\t" << durDel.count() << endl;
        delDoc << "    " << lost << "\t\t | \t\t" << durDel.count() << endl;
    }

    return 0;
}
