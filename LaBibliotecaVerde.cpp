#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

////////////////////////////////clases genericas (estructuras de datos)/////////////////////////////////////////////////////
////////////ARBOLES BINARIOS//////////////
template <class T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;
};
template <class T>
class BinaryTree {
    Nodo<T>* raiz;

    bool _insert(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>();
            nodo->elemento = e;
        }
        else if (e < nodo->elemento) {
            return _insert(nodo->izq, e);
        }
        else if (e >= nodo->elemento) {
            return _insert(nodo->der, e);
        }
    }
    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        cout << nodo->elemento << endl;
        _enOrden(nodo->der);
    }
	void _imprimirPreorden(Nodo<T>* nodo) {
		if (nodo != nullptr) {											//primero confirmamos que el arbol no este vacio (raiz)
			cout << nodo->elemento << " ";						//imprimimos el elemento
			_imprimirPreorden(nodo->izq);						//recursividad pero ahora comparando el hijo izquierdo. 
			_imprimirPreorden(nodo->der);						//recursividad con el hijo derecho
			//Se sigue el algoritmo original, RAIZ-IZQUIERDA-DERECHA
		}
	}

	void _imprimirPostorden(Nodo<T>* nodo) {
		if (nodo != nullptr) {										//primero confirmamos que el arbol no este vacio (raiz)
			_imprimirPostorden(nodo->izq);				//recursividad pero ahora comparando el hijo izquierdo. 
			_imprimirPostorden(nodo->der);				//recursividad con el hijo derecho
			cout << nodo->elemento << " ";					//imprimimos el elemento
			//Se sigue el algoritmo original, IZQUIERDA-DERECHA-RAIZ
		}
	}
	int _binSearch(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) {//sino se encuentra se devuelve -1
			return -1;
		}

		if (e == nodo->elemento) {//si se encuentra se devuelve 1 
			return 1;
		}

		if (e < nodo->elemento) { //en caso sea menor revisa a la izquierda con recursividad 
			int result = _binSearch(nodo->izq, e);
			if (result != -1) {
				return result;
			}
		}
		else {
			int result = _binSearch(nodo->der, e);//lo mismo pa la derecha
			if (result != -1) {
				return result;
			}
		}
		return -1;
	}
	int _obtenerProfundidad(Nodo<T>* nodo) {//caso0 
		if (nodo == nullptr) { return 0; } //en caso de que el arbol este vacio
		else
		{
			int profizquierda = _obtenerProfundidad(nodo->izq);
			int profderecha = _obtenerProfundidad(nodo->der);
			if (profizquierda > profderecha) { return 1 + profizquierda; }
			else { return 1 + profderecha; }

		}
	}
	Nodo<T>* _eliminar(Nodo<T>* nodo, T valor) {
		//en caso de que el elemento a eliminar sea la raiz o sea hoja
		if (nodo == nullptr) {														//primero confirmamos que el arbol no este vacio (raiz)
			return nullptr;																//si es asi retorna vacio
		}
		if (valor < nodo->elemento) {											//primero comparamos si el valor es menor que el elemento del primer nodo
			nodo->izq = _eliminar(nodo->izq, valor);			//si es menor, recursividad en caso del hijo izquierdo. 
			//Si el hijo izquierdo es hoja, se re asigna su puntero a nullptr
		}
		else if (valor > nodo->elemento) {									//si el valor es mayor que el elemento del nodo
			nodo->der = _eliminar(nodo->der, valor);			//recursividad en caso del hijo derecho. 
			//Si el hijo derecho es hoja, se re asigna su puntero a nullptr
		}

		//en caso de que el elemento a eliminar tenga 1 hijo

		else {
			if (nodo->izq == nullptr) {											//si el puntero izquierdo es nullptr, quiere decir que tiene hijo derecho
				Nodo<T>* temp = nodo->der;								//asignamos el derecho a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo izquierdo al arbol
			}
			else if (nodo->der == nullptr) {									//si el puntero derecho es nullptr, quiere decir que tiene hijo izquierdo
				Nodo<T>* temp = nodo->izq;								//asignamos el izquierdo a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo derecho al arbol
			}
			//en caso de que el elemento a eliminar tenga 2 hijos
			Nodo<T>* sucesor = _encontrarSiguiente(nodo->der);					//siempre se tomara el hijo derecho ya que estos suelen ser mayores que el padre
			nodo->elemento = sucesor->elemento;											//asignamos los valores	
			nodo->der = _eliminar(nodo->der, sucesor->elemento);		//eliminamos el nodo
		}
		return nodo;
	}
	//metodo que nos servira para encontrar al siguiente
	Nodo<T>* _encontrarSiguiente(Nodo<T>* nodo) {
		Nodo<T>* actual = nodo;
		while (actual->izq != nullptr) {
			actual = actual->izq;
		}
		return actual;
	}
public:
    BinaryTree() {
        raiz = nullptr;
    }
    bool insert(T e) {
        return _insert(raiz, e);
    }
    void enOrden() {
        _enOrden(raiz);
    }
	void postOrden() {
		_imprimirPostorden(raiz);
	}
	void preOrden() { 
		_imprimirPreorden(raiz); 
	}
	int binSearch(T e) {
		return _binSearch(raiz,e);
	}
	int obtProfundidad() { 
		return _obtenerProfundidad(raiz); 
	}
	Nodo<T>* eliminar(T eliminar) { return _eliminar(raiz, eliminar); } 

};

///////////////////////////HASH TABLES//////////////////////////////////////
template <class K, class V>
class HashEntidad {
private:
    K key;
    V value;
public:
    HashEntidad(K key, V value) {
        this->key = key;
        this->value = value;
    }
    K getKey() { return key; }
    V getValue() { return value; }
};

template<class K, class V>
class HashTabla {
private:
	HashEntidad<K, V>** tabla;
	int numElementos;
	int TABLE_SIZE;
	int modulo;
public:
	HashTabla(int modulo) {
		TABLE_SIZE = modulo;
		this->modulo = modulo;
		tabla = new HashEntidad<K, V>* [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i) {
			tabla[i] = nullptr;
		}
		numElementos = 0;
	}
	~HashTabla()
	{
		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}
	//Direccionamiento según Prueba Lineal
	void insertar(K key, V value) {
		//Hash prima
		size_t base, hash;
		int step;
		//validar si la tabla está llena
		if (numElementos == TABLE_SIZE)return;
		//Función Hash1
		base = hashear(key);
		hash = base;
		//constante para Hash2
		step = 0;
		while (tabla[hash] != nullptr)
		{
			//Función Hash2
			step++;
			hash = (base + step) % modulo;
		}
		//almacenarlo en la tabla
		tabla[hash] = new HashEntidad<K, V>(key, value);
		numElementos++;
	}
	int size() {
		return TABLE_SIZE;
	}
	int sizeactual() {
		return numElementos;
	}

	int buscar(K key) {
		int step = 0;
		size_t i, base;
		i = base = hashear(key); //hash1 es = a hash2 cuando step=0;
		//hashear, en caso de que la clave no sea un valor entero o flotante.
		while (true)
		{
			if (tabla[i] == nullptr) return -1;						//si el elemento esta vacio, devolver -1. Es decir, error,no existe.
			else if (tabla[i]->getKey() == key) {				// si esta lleno, que me retorne el indice de la clave
				return i;
			}
			else step++;														//si no, que el salto aumente, osea que vaya al siguiente espacio

			i = (base + step) % modulo;							//modulamos
		}
	}

	V get(K key) {
		int i = buscar(key);
		if (i != -1) {										//revisar si la clave a buscar existe en la tabla
			return tabla[i]->getValue();			//si existe, que me retorne el valor.
		}
		else {
			throw std::runtime_error("¡Se ha producido un error!");		//si no existe, que retorne error
		}
	}

private:
	template <typename K>
	size_t hashear(K key) { //convertir cualquier tipo de datos a un valor hash
		size_t hash = 0;
		size_t tamBytesKey = sizeof(K);
		unsigned char* data = reinterpret_cast<unsigned char*>(&key); //convertir un tipo de dato a otro de una manera distinta. Cambia los bytes de un tipo a otro
		//cadena de caracteres
		//unsigned para no guardar el signo
		for (int i = 0; i < tamBytesKey; i++) {
			hash ^= data[i];
		}
		return hash % modulo;
	}
};


//////////////////////////CLASES ENTIDADES/////////////////////////////



/////////////////////////CLASE COLECCIONADORA/////////////////////////////


////////////////////////////CLASE CONTROLADORA////////////////////////
int main()
{
    return 0;
}