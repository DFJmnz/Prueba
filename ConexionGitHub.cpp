#include <iostream>
#include <vector>
#include <iomanip>  // Necesario para std::setw y std::setfill
#include <conio.h>
#include <string.h>  // Necesario para funciones relacionadas con cadenas de caracteres
#include <algorithm> 
#include <limits> //Utilizada para función de leer enteros
#include <fstream>  //Permiten el manejo de archivos
#include <filesystem>

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
    libro() : anioPublic(0), precio(0.0), numPaginas(0) {   // Constructor predeterminado
        numeroLibro++;
        ISBN = generarISBN();
    }

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

//Funciones y variables globales
int libro::numeroLibro = 0;
string nombreArchivoCargar;
void imprimirLibros(vector<libro*> v);
void menuPrincipal();
void menu1();
void menu2();
void menu3();
vector<libro*> v;   //Vector para alamacenar todos los libros
vector<libro*> carrito; // Vector para almacenar libros en el carrito

int leerEntero() {  // Función para leer enteros de manera segura
    int valor;
    while (true) {
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR. Introduce un valor entero valido: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    return valor;
}

/*-------------------------- MENÚ 1 (BUSCADOR DE LIBROS) Y SUS FUNCIONES --------------------------*/
void listadoLibros(vector<libro*> v) {
    system("cls");
    if (v.empty()) {
        cout << "\nLa lista esta vacia. Presiona cualquier tecla para volver al buscador.";
    } else {
        imprimirLibros(v);
        cout << "Presiona enter para volver al buscador.";
    }
    getch();
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
    system("cls");
    cout << "\n>> Selecciona el genero para ver los libros disponibles:\n\n";
    cout << " 1. Ciencias de la computacion \n 2. Ciencias de la salud \n 3. Ciencias ambientales \n 4. Ingenieria mecanica \n 5. Arquitectura";
    cout << "\n\nSeleccion: ";
    opcion = leerEntero();

    // Filtrar la lista de libros según la opción seleccionada
    vector<libro*> librosPorGenero;

    switch (opcion) {

        case 1:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias de la Computacion") == 0; });
            break;

        case 2:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias de la Salud") == 0; });
            break;

        case 3:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ciencias Ambientales") == 0; });
            break;

        case 4:
            copy_if(v.begin(), v.end(), back_inserter(librosPorGenero),
                    [](const libro* L) { return strcmp(L->getGenero(), "Ingenieria Mecanica") == 0; });
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

    system("cls");
    cout << "\nLibros del genero seleccionado:\n";
    if (librosPorGenero.empty()) {
        cout << "\nNo hay libros en este genero.\n";
    } else {
        imprimirLibros(librosPorGenero);
    }

    cout << "\n\nPresiona enter para volver al buscador.";
    getch();
}

libro* comparadorISBN(const string& isbn, const vector<libro*>& v) {
    auto it = find_if(v.begin(), v.end(), [isbn](const libro* L) {
        return L->compararISBN(isbn);
    });

    if (it != v.end()) {
       cout << "\nLibro encontrado. ";
        return *it;  //Retorna el puntero al libro si se encuentra
    } else {
        cout << "\nNo se encontro un libro con ese ISBN. Verifique el ISBN." << endl;
        return nullptr;  //Retorna nullptr si no se encuentra el libro
    }
}

void imprimirLibroISBN() {
    system("cls");
    string isbn;
    cout << "\n>> Ingrese el ISBN del libro que desea buscar: ";
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

float calcularPromedioPags() {
    system("cls");
    float suma = 0.0;
    for (int i = 0; i < v.size(); i++) {
        suma += v[i]->getNumPaginas();
    }
    
    float promedioPags = suma / v.size();
    imprimirLibros(v);
    cout << "El promedio de paginas de todos los libros es: " << promedioPags << "\n\n";
}

void menu1() {
    system("cls");
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n\t\t Buscador de libros\n";
        cout<<"\n>> Selecciona una opcion para ver los libros:\n";
        cout<<" 1. Ver todos los libros \n 2. Buscar por genero \n 3. Buscar libro por ISBN \n 4. Promedio de numero de paginas de todos los libros \n 5. Volver al menu principal";
        cout<<"\n\nSeleccion: ";
        opcion = leerEntero();

        switch(opcion) {
            case 1:
                listadoLibros(v);
                menu1();
                break;
            case 2:
                imprimirLibroGenero(v);
                menu1();
                break;
            case 3:
                imprimirLibroISBN();
                menu1();
                break;
            case 4:
                calcularPromedioPags();
                getch();
                menu1();
                break;
            case 5:
                menuPrincipal();
                break;
            default:
                cout << "Opcion invalida. Ingrese otra opcion.";
                getch();
                menu1();
                break;
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

    system("cls");
    cout << ">> Nuevo Libro\n\n";
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

    cout << "\nLibro agregado exitosamente. Presione cualquier tecla para volver al gestionador.\n";
    getch();
}

void eliminarLibro() {
    system("cls");
    string isbnEliminar;
    cout << "Ingrese el ISBN del libro que desea eliminar: ";
    cin >> isbnEliminar;

    libro* libroEncontrado = comparadorISBN(isbnEliminar, v);

    if (libroEncontrado != nullptr) {
         v.erase(remove(v.begin(), v.end(), libroEncontrado), v.end());
        delete libroEncontrado;

        cout << "\n\n Libro eliminado exitosamente. Presiona cualquier tecla para volver al gestionador.\n";
    }

    getch();
}

void modificarLibro() {
    system("cls");
    string isbnModificar;
    cout << "Ingrese el ISBN del libro que desea modificar: ";
    cin >> isbnModificar;

    auto it = find_if(v.begin(), v.end(), [isbnModificar](const libro* L) {
        return L->getISBN() == isbnModificar;
    });

    if (it != v.end()) {
        int opcion;
        cout << "\n>> Seleccione el campo que desea modificar:\n";
        cout << " 1. Titulo\n 2. Autor\n 3. Genero\n 4. Anio de Publicacion\n 5. Editorial\n 6. Precio\n 7. Numero de Paginas\n 8. Cancelar";
        cout << "\n\nSeleccion: ";
        cin >> opcion;
        cout << "\n";

        switch (opcion) {
            case 1: 
                char nuevoTitulo[150];
                cout << "Ingrese el nuevo titulo: ";
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
                cout << "Opcion no valida. Vuelva a intentar\n";
                getch();
                return;
        }

        cout << "\nLibro modificado exitosamente. Presione cualquier tecla para volver al gestionador.\n";
    } else {
        cout << "No se encontró un libro con ese ISBN. Vuelva a intentar.\n";
    }

    getch();
}

void descargarLibros(const vector<libro*>& v) {
    const string nombreArchivoDescargar = "libros.txt";

    ifstream archivoEntrada(nombreArchivoDescargar);
    if (!archivoEntrada.good()) {
        // Si el archivo no existe, crea uno nuevo
        ofstream nuevoArchivo(nombreArchivoDescargar);
        nuevoArchivo.close();
    }

    ofstream archivoSalida(nombreArchivoDescargar, ios_base::trunc); //Permitira abrir el archivo y borrar contenido antes de escribir
    if (archivoSalida.is_open()) {
        for (const auto& libro : v) {
            archivoSalida << "Titulo: " << libro->getTitulo() << "\n";
            archivoSalida << "Autor: " << libro->getAutor() << "\n";
            archivoSalida << "Genero: " << libro->getGenero() << "\n";
            archivoSalida << "# Paginas: " << libro->getNumPaginas() << endl;
            archivoSalida << "Anio de publicacion: " << libro->getAnioPublic() << endl;
            archivoSalida << "Editorial: " << libro->getEditorial() << endl;
            archivoSalida << "ISBN: " << libro->getISBN() << endl;
            archivoSalida << "Precio: " << libro->getPrecio() << endl;
            archivoSalida << "\n";
        }
        // Cierra el archivo
        archivoSalida.close();
        cout << "\n>> Libros guardados en el archivo 'libros.txt'. Presione cualquier tecla para volver al gestionador.\n";
    } else {
        cerr << "\nHubo problemas para escribir en el archivo para escribir. Vuelve a intentar.\n";
    }
    getch();
}

void cargarLibros(vector<libro*>& v) {
    system("cls");
    string nombreArchivoCargar;
    cout << ">> Ingrese el nombre del archivo para cargar los libros: ";
    cin >> nombreArchivoCargar;
    ifstream archivoEntrada(nombreArchivoCargar);

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivoCargar << endl;
        cout << "Presiona cualquier tecla para volver al gestionador.";
        getch();
        return;
    }

    string linea;
    libro* nuevoLibro = nullptr;

    while (getline(archivoEntrada, linea)) {
        istringstream iss(linea);
        string clave, valor;
        getline(iss, clave, ':');
        getline(iss, valor);

        if (clave == "Titulo") {
            if (nuevoLibro != nullptr) {
                v.push_back(nuevoLibro); // Agregar el libro al vector de todos los objetos
            }       
            nuevoLibro = new libro();   // Crear un nuevo objeto libro
            nuevoLibro->setTitulo(valor.c_str());
        } else if (clave == "Autor") {
            nuevoLibro->setAutor(valor.c_str());
        } else if (clave == "Genero") {
            nuevoLibro->setGenero(valor.c_str());
        } else if (clave == "# Paginas") {
            nuevoLibro->setNumPaginas(stoi(valor));
        } else if (clave == "Anio de publicacion") {
            nuevoLibro->setAnioPublic(stoi(valor));
        } else if (clave == "Editorial") {
            nuevoLibro->setEditorial(valor.c_str());
        } else if (clave == "Precio") {
            nuevoLibro->setPrecio(stof(valor));
        }
    }

    // Agregar libro al vector
    if (nuevoLibro != nullptr) {
        v.push_back(nuevoLibro);
    }
    archivoEntrada.close();

    cout << "\nLibros agregados con exito. Presione cualquier tecla para volver al gestionador.";
    getch();

}

void menu2() {
    system("cls");
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n\t\t Gestion de libros\n";
        cout<<"\n>> Selecciona una opcion para gestionar los libros:\n";
        cout<<" 1. Agregar un nuevo libro \n 2. Eliminar un libro \n 3. Modificar un libro \n 4. Descargar los libros de la base de datos\n 5. Cargar los libros a la base de datos\n 6. Volver al menu principal";
        cout<<"\n\nSeleccion: ";
        opcion = leerEntero();

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
                descargarLibros(v);
                menu2();
                break;
            case 5:
                cargarLibros(v);
                menu2();
                break;
            case 6:
                menuPrincipal();
            default:
                cout << "Opcion invalida. Ingrese otra opcion.";
                getch();
                menu2();
        }
}

/*-------------------- MENÚ 3 (SIMULADOR DE COMPRA) Y SUS FUNCIONES ---------------------------*/
float calcularPrecioCarrito() {
    float suma = 0.0;
    for (int i = 0; i < carrito.size(); i++) {
        suma += carrito[i]->getPrecio();
    }
    return suma;
}

void mostrarCarrito() {
    system("cls");
    if (carrito.empty()) {
        cout << "\nEl carrito esta vacio. Presiona enter para volver al simulador de compra." << endl;
    } else {
        cout << ">> Contenido del carrito\n" << endl;
        imprimirLibros(carrito);
        cout << "EL SALDO TOTAL ES: $" << calcularPrecioCarrito() << "\n\n";
        cout << "Presiona enter para volver al simulador de compra.";
    }
    getch();
}

void agregarAlCarrito() {
    system("cls");
    string isbn;
    int opcion;
    cout << "\n>> Ingresa el ISBN del libro que deseas agregar al carrito: ";
    cin >> isbn;

    libro* libroEncontrado = comparadorISBN(isbn, v);

    if (libroEncontrado != nullptr) {
        if (count(carrito.begin(), carrito.end(), libroEncontrado) == false){
            carrito.push_back(libroEncontrado); //Agrega el libro al carrito
            cout << "Agregado al carrito exitosamente." << endl;
        } else cout << "No se puede agregar porque ya se encuentra en el carrito\n";
    }

    cout << "\n1. Agregar otro libro \n2. Mostrar el carrito \n3. Volver al menu";
    cout << "\n\nSeleccione: ";
    opcion = leerEntero();

    switch(opcion) {
        case 1:
        system("cls");
        agregarAlCarrito();
        break;

        case 2:
        system("cls");
        mostrarCarrito();

        case 3:
        system("cls");
        menu3();
        break;
    }

}

void eliminarDelCarrito() {
    system("cls");
    string isbnEliminarCarrito;
    cout << "\n>> Ingrese el ISBN del libro que desea eliminar: ";
    cin >> isbnEliminarCarrito;

   auto it = find_if(carrito.begin(), carrito.end(), [isbnEliminarCarrito](const libro* L) {
        return L->getISBN() == isbnEliminarCarrito;
    });

    if (it != carrito.end()) {
        carrito.erase(it);
        delete *it;

        cout << "\nLibro eliminado exitosamente. Presione para volver al simulador de compra.\n";
    } else {
        cout << "\nNo se encontro un libro con ese ISBN. Vuelva a intentar.\n";
    }
    
    getch();
}

void menu3() {
    system("cls");
    int opcion;
    cout << "\n**** SISTEMA DE GESTION PARA LIBRERIAS ****\n\t\t Simulador de compra\n";
    cout << "\n>> Bienvenido al simulador de compra. Selecciona una opcion:\n";
    cout << " 1. Agregar un libro al carrito \n 2. Mostrar carrito \n 3. Eliminar un libro del carrito \n 4. Volver al menu principal";
    cout << "\n\nSeleccion: ";
    opcion = leerEntero();

    switch (opcion) {
    case 1:
        agregarAlCarrito();
        menu3();
        break;
    case 2:
        mostrarCarrito();
        menu3();
        break;
    case 3:
        eliminarDelCarrito();
        menu3();
        break;
    case 4:
        menuPrincipal();
        break;
    default:
        cout << "Opcion invalida. Ingrese otra opcion.";
        getch();
        menu3();
    }
}

/*--------------------------- MENÚ PRINCIPAL ------------------------------*/
void menuPrincipal() {
    system("cls");
    int opcion;
        cout<<"\n***** SISTEMA DE GESTION PARA LIBRERIAS *****\n";
        cout<<"\n>> Bienvenido. Eliga una opcion para comenzar:\n";
        cout<<" 1. Buscador de libros \n 2. Gestionar libros \n 3. Simulador de compra \n 4. Salir";
        cout<<"\n\nSeleccion: ";

        switch(opcion = leerEntero()) {
            case 1:
                menu1();
                break;
            case 2:
                menu2();
                break;
            case 3:
                menu3();
                break;
            case 4:
                exit(0);
            default:
                cout << "Opcion invalida. Vuelva a intentar.";
                getch();
                menuPrincipal();
        }
}

int main() {
    menuPrincipal();
}
