#include <iostream>
#include <vector>
#include <iomanip>  // Necesario para std::setw y std::setfill
#include <conio.h>
#include <string.h>  // Necesario para funciones relacionadas con cadenas de caracteres
#include <algorithm>

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
        const char editorial[], float precio, int numPaginas) 
        : anioPublic(anioPublic), precio(precio), numPaginas(numPaginas) {

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

    const char* getGenero() const{
        return genero;
    }

    int getAnioPublic() {
        return anioPublic;
    }

    string getISBN() const {
        return ISBN;
    }

    const char* getEditorial() {
        return editorial;
    }

    float getPrecio() {
        return precio;
    }

    int getNumPaginas() {
        return numPaginas;
    }

    // Setters
    void setTitulo(const char* nuevoTitulo) {
        strncpy(titulo, nuevoTitulo, sizeof(titulo) - 1);
        titulo[sizeof(titulo) - 1] = '\0';  // Ensure null termination
    }

    void setAutor(const char* nuevoAutor) {
        strncpy(autor, nuevoAutor, sizeof(autor) - 1);
        autor[sizeof(autor) - 1] = '\0';
    }

    void setGenero(const char* nuevoGenero) {
        strncpy(genero, nuevoGenero, sizeof(genero) - 1);
        genero[sizeof(genero) - 1] = '\0';
    }

    void setAnioPublic(int nuevoAnio) {
        anioPublic = nuevoAnio;
    }

    void setEditorial(const char* nuevaEditorial) {
        strncpy(editorial, nuevaEditorial, sizeof(editorial) - 1);
        editorial[sizeof(editorial) - 1] = '\0';
    }

    void setPrecio(float nuevoPrecio) {
        precio = nuevoPrecio;
    }

    void setNumPaginas(int nuevoNumPaginas) {
        numPaginas = nuevoNumPaginas;
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

    bool compararISBN(const string& isbnComparar) const {
        return ISBN == isbnComparar;
    }

};

int libro::numeroLibro = 0;

//Prototipo de funcion
void menuPrincipal();

void menu1();
void imprimirLibros(vector<libro*> v);
double calcularPromedio(double lista[], int longitud);

void menu2();


void menu3();



vector<libro*> v;
vector<libro*> carrito; // Nuevo vector para almacenar libros en el carrito



/*-------------------------- MENÚ 1 (BUSCADOR DE LIBROS) Y SUS FUNCIONES --------------------------*/
void listadoLibros(vector<libro*> v) {
    if (v.empty()) {
    cout << "La lista esta vacia.";
    getch();
    menuPrincipal();
    } else {
    imprimirLibros(v);
    cout << "Presiona enter para volver al menu.";
    getch();
    }
}

void imprimirLibros(vector<libro*> v) {
    for(libro* L: v) {
       cout << "Titulo: " << L->getTitulo() << endl;
        cout << "Autor: " << L->getAutor() << endl;
        cout << "Genero: " << L->getGenero() << endl;
        cout << "# Paginas: " << L->getNumPaginas() << endl;
        cout << "Anio de publicacion: " << L->getAnioPublic() << endl;
        cout << "Editorial: " << L->getEditorial() << endl;
        cout << "ISBN: " << L->getISBN() << endl;
        cout << "Precio: " << L->getPrecio() << endl;
        cout << endl;
    } 
}

void imprimirLibroGenero(vector<libro*> v) {
    int opcion;
    cout << "\n>>Selecciona el genero para ver los libros disponibles:\n";
    cout << "1. Ciencias de la computacion \n2. Ciencias de la salud \n3. Ciencias ambientales \n4. Ingenieria mecanica \n5. Arquitectura";
    cout << "\n\nSeleccion : ";
    cin >> opcion;

    // Filtrar la lista de libros según la opción seleccionada
    vector<libro*> librosPorGenero;
    switch (opcion) {
        system("cls");
        case 1:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias de la computacion") == 0; });
            break;

        case 2:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias de la salud") == 0; });
            break;

        case 3:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias ambientales") == 0; });
            break;

        case 4:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ingenieria mecanica") == 0; });
            break;

        case 5:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Arquitectura") == 0; });
            break;

        default:
            cout << "Opcion invalida. Ingrese otra opcion.";
            getch();
            return;
    }

    // Mostrar los libros del género seleccionado
    cout << "\nLibros del genero seleccionado:\n";
    if (librosPorGenero.empty()) {
        cout << "No hay libros en este genero.\n";
    } else {
        imprimirLibros(librosPorGenero);
    }

    cout << "Presiona enter para volver al menú principal.";
    getch();
}

libro* comparadorISBN(const string& isbn, const vector<libro*>& v) {
    auto it = find_if(v.begin(), v.end(), [isbn](const libro* L) {
        return L->compararISBN(isbn);
    });

    if (it != v.end()) {
       cout << "Libro encontrado. ";
        return *it;  // Retorna el puntero al libro si se encuentra
    } else {
        cout << "No se encontró un libro con ese ISBN." << endl;
        return nullptr;  // Retorna nullptr si no se encuentra el libro
    }
}

void imprimirLibroISBN() {
    string isbn;
    system("cls");
    cout << "Ingrese el ISBN del libro que desea buscar: ";
    cin >> isbn;
    
    libro* libroEncontrado = comparadorISBN(isbn, v);

        if (libroEncontrado != nullptr) {
            cout << "Detalles:\n";
            cout << "Titulo: " << libroEncontrado->getTitulo() << endl;
            cout << "Autor: " << libroEncontrado->getAutor() << endl;
            cout << "Genero: " << libroEncontrado->getGenero() << endl;
            cout << "# Paginas: " << libroEncontrado->getNumPaginas() << endl;
            cout << "Anio de publicacion: " << libroEncontrado->getAnioPublic() << endl;
            cout << "Editorial: " << libroEncontrado->getEditorial() << endl;
            cout << "ISBN: " << libroEncontrado->getISBN() << endl;
            cout << "Precio: " << libroEncontrado->getPrecio() << endl;
            cout << endl;
        }

    cout << "Presione cualquier tecla para volver al buscador.\n";
    getch();
    
}

void menu1() {
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n\t\t Buscador de libros\n";
        cout<<"\n>>Selecciona una opcion para ver los libros:\n";
        cout<<"1. Ver todos los libros \n2. Buscar por genero \n3. Buscar libro por ISBN \n4. Volver al menu principal";
        cout<<"\n\nSeleccion : ";
        cin>>opcion;

        switch(opcion) {
            case 1:
            listadoLibros(v);
            system("cls");
            menu1();
            break;

            case 2:
            imprimirLibroGenero(v);
            system("cls");
            menu1();
            break;

            case 3:
            imprimirLibroISBN();
            system("cls");
            menu1();
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

/*------------------------ MENÚ 2 (GESTIONAR LIBROS) Y SUS FUNCIONES ---------------------------*/
void agregarLibro() {
    char titulo[150];
    char autor[150];
    char genero[100];
    int anioPublic;
    char editorial[100];
    float precio;
    int numPaginas;

    cout << "Ingrese el titulo del libro: ";
    cin.ignore();
    cin.getline(titulo, sizeof(titulo));

    cout << "Ingrese el autor del libro: ";
    cin.getline(autor, sizeof(genero));

    cout << "Ingrese el genero del libro: ";
    cin.getline(genero, sizeof(genero));

    cout << "Ingrese el anio de publicacion del libro: ";
    cin >> anioPublic;

    cout << "Ingrese la editorial del libro: ";
    cin.ignore();
    cin.getline(editorial, sizeof(editorial));

    cout << "Ingrese el precio del libro: ";
    cin >> precio;
    cin.ignore();

    cout << "Ingrese el numero de paginas del libro: ";
    cin >> numPaginas;
    cin.ignore();

    libro* nuevoLibro = new libro(titulo, autor, genero, anioPublic, editorial, precio, numPaginas);
    v.push_back(nuevoLibro);

    cout << "\nLibro agregado exitosamente. Presione cualquier tecla para volver al menu.\n";
    getch();
}

void eliminarLibro() {
    string isbnEliminar;
    cout << "Ingrese el ISBN del libro que desea eliminar: ";
    cin >> isbnEliminar;

    auto it = find_if(v.begin(), v.end(), [isbnEliminar](const libro* L) {
        return L->getISBN() == isbnEliminar;
    });

    if (it != v.end()) {
        delete *it;
        v.erase(it);

        cout << "Libro eliminado exitosamente.\n";
    } else {
        cout << "No se encontro un libro con ese ISBN.\n";
    }

    getch();
}

void modificarLibro() {
    string isbnModificar;
    cout << "Ingrese el ISBN del libro que desea modificar: ";
    cin >> isbnModificar;

    auto it = find_if(v.begin(), v.end(), [isbnModificar](const libro* L) {
        return L->getISBN() == isbnModificar;
    });

    if (it != v.end()) {
        int opcion;
        cout << "Seleccione el campo que desea modificar:\n";
        cout << "1. Titulo\n 2. Autor\n 3. Genero\n 4. Anio de Publicacion\n 5. Editorial\n 6. Precio\n 7. Numero de Paginas\n 8. Cancelar";
        cout << "Seleccion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
                char nuevoTitulo[150];
                cout << "Ingrese el nuevo título: ";
                cin.ignore();
                cin.getline(nuevoTitulo, sizeof(nuevoTitulo));
                (*it)->setTitulo(nuevoTitulo);
                break;
            
            case 2: 
                char nuevoAutor[150];
                cout << "Ingrese el nuevo autor: ";
                cin.ignore();
                cin.getline(nuevoAutor, sizeof(nuevoAutor));
                (*it)->setAutor(nuevoAutor);
                break;       
            
            case 3:
                char nuevoGenero[100];
                cout << "Ingrese el nuevo genero: ";
                cin.ignore();
                cin.getline(nuevoGenero, sizeof(nuevoGenero));
                (*it)->setGenero(nuevoGenero);
                break;                       

            case 4:
                int nuevoAnio;
                cout << "Ingrese el nuevo anio de publicacion: ";
                cin >> nuevoAnio;
                (*it)->setAnioPublic(nuevoAnio);
                break;

            case 5:
                char nuevaEditorial[100];
                cout << "Ingrese la nueva editorial: ";
                cin.ignore();
                cin.getline(nuevaEditorial, sizeof(nuevaEditorial));
                (*it)->setEditorial(nuevaEditorial);
                break;

            case 6:
                float nuevoPrecio;
                cout << "Ingrese el nuevo precio: ";
                cin >> nuevoPrecio;
                (*it)->setPrecio(nuevoPrecio);
                break;

            case 7:
                int nuevoNumPaginas;
                cout << "Ingrese el nuevo numero de paginas: ";
                cin >> nuevoNumPaginas;
                (*it)->setNumPaginas(nuevoNumPaginas);
                break;

            case 8:
            menu2();
            break;

            default:
                cout << "Opción no válida.\n";
                getch();
                return;
        }

        cout << "Libro modificado exitosamente.\n";
    } else {
        cout << "No se encontró un libro con ese ISBN.\n";
    }

    getch();
}

void menu2() {
    system("cls");
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n\t\t Gestion de libros\n";
        cout<<"\n>>Selecciona una opcion para gestionar los libros:\n";
        cout<<"1. Agregar un nuevo libro \n2. Eliminar un libro \n3. Modificar un libro \n4. Volver al menu principal";
        cout<<"\n\nSeleccion : ";
        cin>>opcion;

        switch(opcion) {
            case 1:
            agregarLibro();
            menu2();
            break;

            case 2:
            eliminarLibro();
            menu2();
            break;

            case 3:
            modificarLibro();
            menu2();
            break;

            case 4:
            menuPrincipal();

            default:
            cout << "Opcion invalida. Ingrese otra opcion.";
            getch();
            menu2();
        }

}

/*-------------------- MENÚ 3 (SIMULADOR DE COMPRA) Y SUS FUNCIONES ---------------------------*/
void agregarAlCarrito() {
    string isbn;
    system("cls");
    cout << "\nIngresa el ISBN del libro que deseas agregar al carrito: ";
    cin >> isbn;

    libro* libroEncontrado = comparadorISBN(isbn, v);

    if (libroEncontrado != nullptr) {
        carrito.push_back(libroEncontrado); //Agrega el libro al carrito
        cout << " Agregado al carrito exitosamente." << endl;
    }
  
    cout << "\nPresione cualquier tecla para continuar.";
    getch();
    
    //cout << "Presione 's' si desea agregar otro libro o 'n' para volver al menu"
}

void mostrarCarrito() {
    if (carrito.empty()) {
        cout << "El carrito esta vacio. Presiona enter para volver al simulador de compra" << endl;
        getch();
    } else {
        system("cls");
        cout << ">> Contenido del carrito\n" << endl;
        imprimirLibros(carrito);
        cout << "Presiona enter para volver al simulador de compra.";
        getch();
    }
}

void eliminarDelCarrito() {
    string isbnEliminar;
    cout << "Ingrese el ISBN del libro que desea eliminar: ";
    cin >> isbnEliminar;

    auto it = find_if(v.begin(), v.end(), [isbnEliminar](const libro* L) {
        return L->getISBN() == isbnEliminar;
    });

    if (it != v.end()) {
        delete *it;
        v.erase(it);

        cout << "Libro eliminado exitosamente.\n";
    } else {
        cout << "No se encontro un libro con ese ISBN.\n";
    }

    getch(); 
}

void menu3() {
    int opcion;
    cout << "\n**** SISTEMA DE GESTION PARA LIBRERIAS ****\n\t\t Simulador de compra\n";
    cout << "\n>>Bienvenido al simulador de compra. Selecciona una opcion:\n";
    cout << "1. Agregar un libro al carrito \n2. Mostrar carrito \n3. Eliminar un libro del carrito \n4. Volver al menu principal";
    cout << "\nSeleccion : ";
    cin >> opcion;

    switch (opcion) {
    case 1:
        agregarAlCarrito();
        system("cls");
        menu3();
        break;

    case 2:
        mostrarCarrito();
        system("cls");
        menu3();
        break;

    case 3:
        //Código para eliminar un libro del carrito (implementación adicional)
        system("cls");
        menu3();
        break;

    case 4:
        menuPrincipal();
        break;

    default:
        cout << "Opcion invalida. Ingrese otra opcion.";
        getch();
        system("cls");
        menu3();
    }
}

/*--------------------------- MENÚ PRINCIPAL ------------------------------*/
void menuPrincipal() {
    system("cls");
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n";
        cout<<"\n>>Bienvenido. Eliga una opcion para comenzar:\n";
        cout<<"1. Buscador de libros \n2. Gestionar libros \n3. Simulador de compra \n4. Salir";
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

// Función para calcular el promedio de precios
double calcularPromedio(double lista[], int longitud) {
    double suma = 0.0;
    for (int i = 0; i < longitud; i++) {
        suma += lista[i];
    }
    double promedio = suma / longitud;

    return promedio;
}

int main() {
    menuPrincipal();
}
