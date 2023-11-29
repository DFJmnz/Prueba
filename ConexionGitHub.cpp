//Gutiérrez Córdova (221214790) - Jiménez Bracamonte (221213676) - Retana Romero (221216071)
//HOLA
#include <iostream>
#include <vector>
#include <iomanip>  // Necesario para std::setw y std::setfill
#include <conio.h>

using namespace std;

class libro {
public:
    /*libro(string titulo, string autor, string genero, int anioPublic, 
    string ISBN, string review, int stock, int numPaginas) {
        this->titulo = titulo;
        this->autor = autor;
        this->genero = genero;
        this->anioPublic = anioPublic;
        this->ISBN = generarISBN();
        this->review = review;
        this->stock = stock;
        this->numPaginas = numPaginas;
    }*/

    libro(string titulo, string autor, string genero, int anioPublic, 
        string review, int stock, int numPaginas) 
        : titulo(titulo), autor(autor), genero(genero), anioPublic(anioPublic),
          review(review), stock(stock), numPaginas(numPaginas) {
        // Incrementar el número de libro y generar el ISBN
        numeroLibro++;
        ISBN = generarISBN();
    }

//Getters
string getTitulo() {
    return titulo;
    }

string getAutor() {
    return autor;
    }

string getGenero() {
    return genero;
    }

int getAnioPublic() {
    return anioPublic;
    }

string getISBN() {
    return ISBN;
    }

string getReview() {
    return review;
    }

int getStock() {
    return stock;
    }

int getNumPaginas() {
    return numPaginas;
    }


private:
    string titulo;
    string autor;
    string genero;
    int anioPublic;
    string ISBN;
    string review;
    int stock;
    int numPaginas;
    static int numeroLibro;

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


void imprimirLibros(vector<libro*> v) {
    for(libro* L: v) {
        cout << "Titulo: " << L->getTitulo() << endl;
        cout << "Autor: " << L->getAutor()<< endl;
        cout << "Genero: " << L->getGenero() << endl;
        cout << "Anio de publicacion: " << L->getAnioPublic() << endl;
        cout << "ISBN: " << L->getISBN()<< endl;
        cout << "Resenia: " << L->getReview() << endl;
        cout << "Stock disponible: " << L->getStock()<< endl;
        cout << "# Paginas: " << L->getNumPaginas() << endl;
        cout << endl;

    }
    
}

void menuPrincipal() {
int opcion;
    cout<<"\n*********** SISTEMA DE GESTION PARA LIBRERIAS ***********\n";
    cout<<"\n>>Bienvenido. Eliga una opcion para comenzar:\n";
    cout<<"1. Ver lista de libros \n2. Gestionar libros \n3. Simulador de compra \n4. Salir";
    cout<<"\nSeleccion : ";
    cin>>opcion;

    switch(opcion) {
        case 1:
        cout << "1";
        break;

        case 2:
        cout << "2";
        break;

        case 3:
        cout << "3";
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

    libro L1("Caaaaaaa", "Charles Perrault", "Infantil", 1697, "Muy bueno", 5, 20);
    libro L2("Eaaaaaaaaa", "Dr. Seuss", "Infantil", 1971, "Muy bueno", 5, 20);
    libro L3("Daaaaaaaaa", " Miguel de Cervantes", "Aventura", 1605, "Muy bueno", 5, 500);

    vector<libro*> v = {&L1, &L2, &L3};

    //imprimirLibros(v);
    menuPrincipal();
    getch();

    return 0;
}
