#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <queue>

using namespace std::chrono;
using namespace std;

/* AVLnode: this class defines the nodes
*/
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent; //pointer to the parts of the AVL tree

    AVLnode(T k, AVLnode* p)
        : key(k)
        , balance(0)
        , parent(p)
        , left(NULL)
        , right(NULL)
    {
    }

    ~AVLnode()
    {
        delete left;
        delete right;
    }
};

/* AVL tree: this class defines the AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void); //porque empieza en void?
    ~AVLtree(void);
    bool insert(T key);
    bool deleteKey(const T key);
    void printBalance();
    bool search(const T target);

private:
    AVLnode<T>* root;

    AVLnode<T>* rotateLeft(AVLnode<T>* a);
    AVLnode<T>* rotateRight(AVLnode<T>* a);
    AVLnode<T>* rotateLeftThenRight(AVLnode<T>* n);
    AVLnode<T>* rotateRightThenLeft(AVLnode<T>* n);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
    void clearNode(AVLnode<T>* n);

};

/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(AVLnode<T>* n)
{
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T>* a)
{
    AVLnode<T>* b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T>* a)
{
    AVLnode<T>* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T>* n)
{
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T>* n)
{
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T>* n)
{
    if (n == NULL)
        return -1;
    return 1 + max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T>* n)
{
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T>* n)
{
    if (n != NULL) {
        printBalance(n->left);
        cout << n->balance << " ";
        printBalance(n->right);
    }
}
/* AVLtree: this class initializes the tree creating the first node in NULL
*/
template <class T>
AVLtree<T>::AVLtree(void)
    : root(NULL)
{
}

template <class T>
AVLtree<T>::~AVLtree(void)
{
    delete root;
}
/* insert: this method insert a new node with it's value
* @param key contains the value of the node
* @return true
*/
template <class T>
bool AVLtree<T>::insert(T key)
{
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL); //if there's no root it will create a new node which will be the node of the new tree
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
bool AVLtree<T>::deleteKey(const T delKey)
{
    if (root == NULL)
        return false;

    AVLnode<T>
        *n = root,
        *parent = root,
        *delNode = NULL,
        *child = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
            return true;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;

            }

            return true;
            rebalance(parent);
        }
    }
    return false;
}

template <class T>
void AVLtree<T>::printBalance()
{
    printBalance(root);
    cout << endl;
}

template <class T>
bool AVLtree<T>::search(const T target)
{
	if (root == NULL)
    {
    	return false;
    }

    AVLnode<T>
    	*node = root;

    while(true)
    {
        if(target == node->key)
        {
            return true;
        }
        else if(target < node->key)
        {
            if(node->left != NULL)
            {
                node = node->left;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(node->right != NULL)
            {
                node = node->right;
            }
            else
            {
                return false;
            }
        }
    }


}

// void Ascendente(int arr[], int tamArreglo)
// {

//     sort(arr, arr + tamArreglo);

//     cout << "El arreglo en orden ascendente es " << endl;

//     for (int i = 0; i < tamArreglo; ++i) {
//         cout << arr[i] << " ";
//     }

//     cout << "\n";
// };

// void Descendente(int arr[], int tamArreglo)
// {

//     sort(arr, arr + tamArreglo, greater<int>());

//     cout << "El arreglo en orden ascendente es " << endl;

//     for (int i = 0; i < tamArreglo; ++i) {
//         cout << arr[i] << " ";
//     }

//     cout << "\n";
// };

void Buscar(int arr[], int tamArreglo, int valPerd)
{

    sort(arr, arr + tamArreglo);

    bool res = false;
    int i = 0;

    while (i < tamArreglo && res != true) {
        if (arr[i] == valPerd) {

            res = true;
        }
        else {

            i++;
        }
    }

    if (arr[i] == valPerd) {
        cout << "El valor " << valPerd << " si se encuentra en el árbol" << '\n';
    }
    else {

        cout << "El valor " << valPerd << " no se encuentra en el árbol" << '\n';
    }

    cout << "\n" << '\n';
};

int main(int argc, char const *argv[])
{	
	AVLtree<int> tree;

	srand((unsigned)time(0)); 

	string inputDoc, nombreArchivo, number;
	fstream inputFile;
	int nuevoNo, noOperaciones, perdu;
	int arr[10];

	int cantValores;              // Cantidad de valores aleatorios que se insertarán en el Árbol

	ofstream inDoc("OutputsAVL/OutputInsertionAVL.txt");
    ofstream searchDoc("OutputsAVL/OutputSearchAVL.txt");
    ofstream delDoc("OutputsAVL/OutputDeleteAVL.txt");

	// cout << "Cuántos valores se van a insertar/borrar/buscar?" << endl;
	// cin >> noOperaciones;

	noOperaciones = 0;

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

	        tree.insert(nuevoNo);

	        auto stopIn = high_resolution_clock::now();
	        auto durIn = duration_cast<microseconds>(stopIn - startIn);

	        cout << "    " << nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
	        inDoc << "    " << nuevoNo << "\t\t | \t\t" << durIn.count() << endl;
	    }

	    auto stopIn = high_resolution_clock::now();
	    auto durIn = duration_cast<microseconds>(stopIn - startIn);
	    cout << "Tiempo total de creación de Árbol AVL: " << durIn.count() << endl << endl;
	}
	inDoc.close();
	inputFile.close();

    cout << "\n\nInicio de búsqueda\n";
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

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = (rand()%100)+1; 
	}

	auto startBus = high_resolution_clock::now();

	for (int i = 0; i < 10; ++i)
	{
		if(tree.search(arr[i]))
        {
            auto stopBus = high_resolution_clock::now();
            auto durBus = duration_cast<microseconds>(stopBus - startBus);
            cout << "    " << arr[i] << "\t\t | \t\t"
                 << "Encontrado"
                 << "\t\t | \t\t" << durBus.count() << endl;
            searchDoc << "    " << arr[i] << "\t\t | \t\t"
                      << "Encontrado"
                      << "\t\t | \t\t" << durBus.count() << endl;
        }
        else
        {
            auto stopBus = high_resolution_clock::now();
            auto durBus = duration_cast<microseconds>(stopBus - startBus);
            cout << "    " << arr[i] << "\t\t | \t\t"
                 << "No se encontró"
                 << "\t\t | \t\t" << durBus.count() << endl;
            searchDoc << "    " << arr[i] << "\t\t | \t\t"
                      << "No se encontró"
                      << "\t\t | \t\t" << durBus.count() << endl;
        }
	}

	auto stopBus = high_resolution_clock::now();
	auto durBus = duration_cast<microseconds>(stopBus - startBus);
	cout << endl << "Tiempo total de búsqueda de 10 valores aleatorios: " << durBus.count() << endl << endl;;

    cout << "\n\nInicio de eliminación\n";
    cout << "\n\nNúmero \t\t"
         << " |"
         << "\t\t¿Se eliminó?\t\t"
         << " |"
         << "\t\tTiempo que le tomó" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;

    delDoc << "\n\nNúmero \t\t"
         << " |"
         << "\t\t¿Se eliminó?\t\t"
         << " |"
         << "\t\tTiempo que le tomó" << endl;

    auto startDel = high_resolution_clock::now();

    for (int i = 0; i < 10; ++i)
    {
        if(tree.deleteKey(arr[i]))
        {
            auto stopDel = high_resolution_clock::now();
            auto durDel = duration_cast<microseconds>(stopDel - startDel);
            cout << "    " << arr[i] << "\t\t | \t\t"
                 << "Eliminado"
                 << "\t\t | \t\t" << durDel.count() << endl;
            delDoc << "    " << arr[i] << "\t\t | \t\t"
                   << "Eliminado"
                   << "\t\t | \t\t" << durDel.count() << endl;
        }
        else
        {
            auto stopDel = high_resolution_clock::now();
            auto durDel = duration_cast<microseconds>(stopDel - startDel);
            cout << "    " << arr[i] << "\t\t | \t\t"
                 << "No se encontró"
                 << "\t\t | \t\t" << durDel.count() << endl;
            delDoc << "    " << arr[i] << "\t\t | \t\t"
                   << "No se encontró"
                   << "\t\t | \t\t" << durDel.count() << endl;
        }
    }

    auto stopDel = high_resolution_clock::now();
    auto durDel = duration_cast<microseconds>(stopDel - startDel);
    cout << "Tiempo total de eliminación de 10 valores aleatorios: " << durDel.count() << endl << endl;

    return 0;
}