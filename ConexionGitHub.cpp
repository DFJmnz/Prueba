//Gutiérrez Córdova (221214790) - Jiménez Bracamonte (221213676) - Retana Romero (221216071)

#include <iostream>
#include <vector>
#include <iomanip>  // Necesario para std::setw y std::setfill
#include <conio.h>
#include <cstring>  // Necesario para funciones relacionadas con cadenas de caracteres

using namespace std;

class libro {
private:
    char titulo[150];
    char autor[150];
    char genero[150];
    int anioPublic;
    string ISBN;
    char editorial[100];
    float precio;
    int numPaginas;
    static int numeroLibro;

public:
   libro(const char titulo[], const char autor[], const char genero[], int anioPublic, 
        const char editorial[], double precio, int numPaginas) 
        : anioPublic(anioPublic), numPaginas(numPaginas) {

        // Copiar títulos, autores y géneros a los arreglos de la clase
        strncpy(this->titulo, titulo, sizeof(this->titulo) - 1);
        this->titulo[sizeof(this->titulo) - 1] = '\0';  // Asegurar la terminación nula

        strncpy(this->autor, autor, sizeof(this->autor) - 1);
        this->autor[sizeof(this->autor) - 1] = '\0';

        strncpy(this->genero, genero, sizeof(this->genero) - 1);
        this->genero[sizeof(this->genero) - 1] = '\0';
        
        strncpy(this->editorial, editorial, sizeof(this->editorial) - 1);
        this->editorial[sizeof(this->editorial) - 1] = '\0';

	numeroLibro++;
        ISBN = generarISBN();
    }

//Getters
const char* getTitulo() {
    return titulo;
    }

const char* getAutor() {
    return autor;
    }

const char* getGenero() {
    return genero;
    }

int getAnioPublic() {
    return anioPublic;
    }

string getISBN() {
    return ISBN;
    }

const char* getEditorial() {
    return editorial;
    }

double getPrecio() {
    return precio;
    }

int getNumPaginas() {
    return numPaginas;
    }

    string generarISBN() {
        // Obtener el año de publicación con 4 dígitos
    	string anio = to_string(anioPublic);
    	// Obtener el número de libro con 2 dígitos
	    string numLibroStr = to_string(numeroLibro);
    	// Rellenar con ceros a la izquierda si es necesario
    	numLibroStr = std::string(2 - numLibroStr.length(), '0') + numLibroStr;

        // Concatenar las partes para formar el ISBN
        string isbn = "978" + anio + numLibroStr;

        return isbn;
    }
};

int libro::numeroLibro = 0;

//Prototipo de funcion
void menuPrincipal();
void menu1();
void menu2();
void menu3();
vector<libro*> v;

void imprimirLibros(vector<libro*> v) {
    for(libro* L: v) {
       cout << "Titulo: " << L->getTitulo() << endl;
        cout << "Autor: " << L->getAutor()<< endl;
        cout << "Genero: " << L->getGenero() << endl;
        cout << "# Paginas: " << L->getNumPaginas() << endl;
        cout << "Anio de publicacion: " << L->getAnioPublic() << endl;
        cout << "Editorial: " << L->getEditorial() << endl;
        cout << "ISBN: " << L->getISBN()<< endl;
        cout << "Precio: " << L->getPrecio()<< endl;
        cout << endl;
    } 
}

void listadoLibros(vector<libro*> v) {

    if (v.empty()) {
    cout << "El listado esta vacio.";
    getch();
    menu1();
    } else {imprimirLibros(v);
    cout << "Presiona enter para volver al menu.";
    getch();
    }
}

void agregarLibro() {
    char titulo[150];
    char autor[150];
    char genero[150];
    int anioPublic;
    char editorial[100];
    float precio;
    int numPaginas;

    cout << "Ingrese el título del libro: ";
    cin.ignore();
    cin.getline(titulo, sizeof(titulo));

    cout << "Ingrese el autor del libro: ";
    cin.getline(autor, sizeof(genero));

    cout << "Ingrese el género del libro: ";
    cin.getline(genero, sizeof(genero));

    cout << "Ingrese el año de publicación del libro: ";
    cin >> anioPublic;

    cout << "Ingrese la editorial del libro: ";
    cin.ignore();
    cin.getline(editorial, sizeof(editorial));

    cout << "Ingrese el precio del libro: ";
    cin >> precio;

    cout << "Ingrese el número de páginas del libro: ";
    cin >> numPaginas;

    libro* nuevoLibro = new libro(titulo, autor, genero, anioPublic, editorial, precio, numPaginas);
    v.push_back(nuevoLibro);

    cout << "Libro agregado exitosamente.\n";
    getch();
}

void menu1() {
    system("cls");
    int opcion;
        cout<<"\n*********** SISTEMA DE GESTION PARA LIBRERIAS ***********\n\t\t Listado de libros\n";
        cout<<"\n>>Selecciona una opcion para ver los libros:\n";
        cout<<"1. Ver todos los libros \n2. Ver por genero \n3. Buscar libro por ISBN \n4. Volver al menu principal";
        cout<<"\n\nSeleccion : ";
        cin>>opcion;

        switch(opcion) {
            case 1:
            listadoLibros(v);
            menu1();
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            menuPrincipal();

            default:
            cout << "Opcion invalida. Ingrese otra opcion.";
            getch();
            system("cls");
            menu1();
        }

}

void menu2() {
    int opcion;
        cout<<"\n*********** SISTEMA DE GESTION PARA LIBRERIAS ***********\n\t\t Gestion de libros\n";
        cout<<"\n>>Selecciona una opcion para gestionar los libros:\n";
        cout<<"1. Agregar un nuevo libro \n2. Eliminar un libro \n3. Modificar un libro \n4. Volver al menu principal";
        cout<<"\n\nSeleccion : ";
        cin>>opcion;

        switch(opcion) {
            case 1:
            agregarLibro();
            getch();
            menu2();
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            menuPrincipal();

            default:
            cout << "Opcion invalida. Ingrese otra opcion.";
            getch();
            system("cls");
            menu2();
        }

}

void menu3() {
    int opcion;
        cout<<"\n********* SISTEMA DE GESTION PARA LIBRERIAS *********\n\t\t Simulador de compra\n";
        cout<<"\n>>Bienvenido al simulador de compra. Selecciona una opcion:\n";
        cout<<"1. Agregar un libro al carrito \n2. Eliminar un libro del carrito";
        cout<<"\nSeleccion : ";
        cin>>opcion;
}

void menuPrincipal() {
system("cls");
int opcion;
        cout<<"\n*********** SISTEMA DE GESTION PARA LIBRERIAS ***********\n";
        cout<<"\n>>Bienvenido. Eliga una opcion para comenzar:\n";
        cout<<"1. Listado de libros \n2. Gestionar libros \n3. Simulador de compra \n4. Salir";
        cout<<"\n\nSeleccion : ";
        cin>>opcion;

        switch(opcion) {
            case 1:
            system("cls");
            menu1();
            break;

            case 2:
            system("cls");
            menu2();
            break;

            case 3:
            system("cls");
            menu3();
            break;

            case 4:
            exit(0);

            default:
            cout << "Opcion invalida. Ingrese otra opcion.";
            getch();
            system("cls");
            menuPrincipal();
        }
}

int main() {

    menuPrincipal();
    getch();

    return 0;
}
