#include <iostream>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

int main(){

    int cantNumeros, numeroRandom;

    string nombreDoc;

    cout << "Como quiere que se llame el documento?" << endl;
    cin >> nombreDoc;

    cout << "Cuantos números se van a crear?" << endl;
    cin >> cantNumeros;

    ofstream nuevoDoc(nombreDoc);
    
    srand((unsigned)time(0));

    for (int i = 0; i < cantNumeros; i++)
    {
        numeroRandom = rand() % cantNumeros + 1;

        nuevoDoc << numeroRandom << endl;        
    }
    

}