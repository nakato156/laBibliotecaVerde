#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

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
	Nodo <T>* _encontrarMax(Nodo<T>* nodo) { //encuentra el valor maximo del arbol, recorriendolo hacia la derecha
		if (nodo == nullptr) { return 0; } //en caso de que el arbol este vacio
	
		while (nodo->der!=nullptr)
		{
			nodo = nodo->derecha;
		}
		return nodo;		
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
	Nodo <T>* FoundNext() { return _encontrarSiguiente(raiz); }
	Nodo <T>* foundMax() { return _encontrarMax(raiz); }

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
	void eliminar(K key) {
		int index = buscar(key);  // Buscar el índice del elemento con la clave proporcionada

		if (index != -1) {
			delete tabla[index];  // Elimina el elemento en la posición index
			tabla[index] = nullptr;  // Establece el puntero en la posición index a nullptr
			numElementos--;  // Decrementa el número de elementos

			auto hashActual = hashear(key);
			if (hashActual != index) reorganizar(index);
			else if (hashear(tabla[index + 1].getKey()) == hashActual) reorganizar(index);
		}
	}
	int sizeTabla() {
		return TABLE_SIZE;
	}

	int size() {
		return numElementos;
	}

	int buscar(K key) {//buscar en hash
		int step = 0;
		size_t i, base;
		i = base = hashear(key); //hash1 es = a hash2 cuando step=0;
		//hashear, en caso de que la clave no sea un valor entero o flotante.
		while (true)
		{
			if (tabla[i] == nullptr) return -1;		//si el elemento esta vacio, devolver -1. Es decir, error,no existe.
			else if (tabla[i]->getKey() == key) {	// si esta lleno, que me retorne el indice de la clave
				return i;
			}
			else step++;							//si no, que el salto aumente, osea que vaya al siguiente espacio

			i = (base + step) % modulo;				//modulamos
		}
	}

	V get(K key) {
		int i = buscar(key);
		if (i != -1) {								//revisar si la clave a buscar existe en la tabla
			return tabla[i]->getValue();			//si existe, que me retorne el valor.
		}
		else {
			throw std::runtime_error("¡Se ha producido un error!");		//si no existe, que retorne error
		}
	}

private:
	size_t hashear(K key) { //convertir cualquier tipo de datos a un valor hash
		size_t hash = 0;
		size_t tamBytesKey = sizeof(K);
		unsigned char* data = reinterpret_cast<unsigned char*>(&key); //convertir un tipo de dato a otro de una manera distinta. Cambia los bytes de un tipo a otro
		//cadena de caracteres		unsigned para no guardar el signo
		for (int i = 0; i < tamBytesKey; i++) {
			hash ^= data[i];
		}
		return hash % modulo;
	}

	void reorganizar(int index) {
		// Reorganiza la tabla si es necesario, para evitar los huecos en la tabla, como una posicion vacia donde antes estaba el primer elemento
		int nextIndex = (index + 1) % modulo;	//calcula el siguiente indice
		while (tabla[nextIndex] != nullptr) {	//se sigue ejecutando cuando next index no sea null ptr
			HashEntidad<K, V>* temp = tabla[nextIndex];	//se crea un puntero temp que apunta al siguiente elemento
			tabla[nextIndex] = nullptr;
			numElementos--;
			insertar(temp->getKey(), temp->getValue());	//se inserta el elemento temp en la tabla
			delete temp;
			nextIndex = (nextIndex + 1) % modulo;
		}
	}
};


//////////////////////////CLASES ENTIDADES/////////////////////////////
class Fecha {
private:
	int dia, mes, anio;

public:
	Fecha() = default;
	Fecha(string fecha) {
		string data[] = { "0", "0", "0" };
		for (int i = 0; i < 3; i++) {
			int index = fecha.find("/");
			data[i] = fecha.substr(0, index);
			fecha = fecha.substr(index + 1);
		}

		try {
			anio = stoi(data[0]);
			mes = stoi(data[1]);
			dia = stoi(data[2]);
		}
		catch (const exception&) {
			throw invalid_argument("La fecha no es válida");
		}
	}
	Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

	bool operator==(const Fecha& otraFecha) const {
		return (dia == otraFecha.dia && mes == otraFecha.mes && anio == otraFecha.anio);
	}

	bool operator!=(const Fecha& otraFecha) const {
		return !(*this == otraFecha);
	}

	bool operator<(const Fecha& otraFecha) const {
		if (anio < otraFecha.anio)
			return true;
		else if (anio > otraFecha.anio)
			return false;
		else {
			if (mes < otraFecha.mes)
				return true;
			else if (mes > otraFecha.mes)
				return false;
			else
				return (dia < otraFecha.dia);
		}
	}

	bool operator>(const Fecha& otraFecha) const {
		return (otraFecha < *this);
	}

	// Sobrecarga del operador de comparación <=
	bool operator<=(const Fecha& otraFecha) const {
		return (*this < otraFecha || *this == otraFecha);
	}

	// Sobrecarga del operador de comparación >=
	bool operator>=(const Fecha& otraFecha) const {
		return (*this > otraFecha || *this == otraFecha);
	}
	operator string() const {
		return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
	}

	friend ostream& operator<<(ostream& os, const Fecha& fecha) {
		os << fecha.anio << "/" << fecha.mes << "/" << fecha.dia;
		return os;
	}
};


class Libro {
	string codigo, titulo, autor;
	Fecha fecha_publicacion;
	float precio;

public:
	Libro() = default;
	Libro(string cod, string title, string author, string date, float price) :
		codigo(cod), titulo(title), autor(author), fecha_publicacion(date), precio(price) {};

	string getCodigo() { return codigo; }
	string getTitulo() { return titulo; }
	string getAutor() { return autor; }
	string getFechaPub() { return fecha_publicacion; }
	float getPrecio() { return precio; }

	bool operator<(const Libro& otro) {
		return fecha_publicacion < otro.fecha_publicacion;
	}

	bool operator==(const Libro& otro) {
		return otro.codigo == codigo;
	}
	friend ostream& operator<<(ostream& os, Libro libro) {
		os << libro.codigo << " | " << libro.titulo << " | " 
			<< libro.autor << " | " << libro.fecha_publicacion << " | " << libro.precio << endl;
		return os;
	}
};


/////////////////////////CLASE COLECCIONADORA/////////////////////////////
enum TiposOrden { EnOrden, PreOrden, PostOrden };

class Biblioteca {
	BinaryTree<Libro> arbol;
	HashTabla<string, Libro> tablaHash;
public:
	Biblioteca() = default;
	void insertar(Libro libro) {
		arbol.insert(libro);
		tablaHash.insertar(libro.getCodigo(), libro);
	}
	void eliminar(string codigo) {
		arbol.eliminar(Libro(codigo, "", "", "", 0));
		tablaHash.eliminar(codigo);
	}
	void eliminar(Libro libro) {
		eliminar(libro.getCodigo());
	}

	void recorrer(TiposOrden orden) const { // se imprime el recorrido
		if(orden == EnOrden){}
		else if(orden == PreOrden){}
		else if(orden == PostOrden){}
	}

	friend ostream& operator<<(ostream& os, const Biblioteca& b) {
		b.recorrer(EnOrden); // no sé si funciona
		return os;
	}
};

// no se que estoy haciendo, ya tengo sueño
// si quieren usen lo del profe o lo del TP
// https://github.com/rsylvian/CSVparser/blob/master/CSVparser.cpp
struct Fila {
	string columna;
	string val;
	Fila() = default;
	Fila(string col, string val_) : columna(col), val(val_) {};
};

class DataFrame {
	vector<string> columnas;
	vector<vector<string>> filas;
	int size = 0;
public:
	DataFrame() = default;
	int size() { return size; }
	void read_csv(const string filename, const char sep = ',') {
		ifstream archivo(filename);

		if (!archivo.is_open()) {
			cerr << "No se pudo leer el archivo" << endl;
			return;
		}

		string linea;
		while (getline(archivo, linea)) {
			vector<string> fila;
			int pos;
			while((pos = linea.find(sep)) != string::npos){
				string campo = linea.substr(0, pos);
				fila.push_back(campo);
				linea.erase(0, pos + 1);
			}
			fila.push_back(linea);
			filas.push_back(fila);
			size++;
		}

		archivo.close();
	}

private:
	vector<string> getRow(int i) {
		return filas[i];
	}

	vector<string>& operator[](int i) {
		return filas[i];
	}
};


////////////////////////////CLASE CONTROLADORA////////////////////////
using busquedaFunc = void(*)(Libro, Libro); // esto es un alias
using ordenamientoFunc = void(*)(); // en el segundo parenteis pones el tipo de parametro que recibe la función

class Tests {
	Tests() = default;

	void compararBusqueda(busquedaFunc, busquedaFunc){}
	void compararOrdenameinto(busquedaFunc, busquedaFunc){}

	void export(double tiempo, string tipoAlgoritmo, int cantDatos) {
		ofstream archivo("resultados.txt");
		if (!archivo.is_open()) {
			archivo << "Tiempo: " << tiempo;
			archivo << "Algoritmo: " << tipoAlgoritmo;
			archivo << "Cant. de datos: " << cantDatos;
			archivo.close();
		}
	}
};

int main()
{
    return 0;
}