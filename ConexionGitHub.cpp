//Gutiérrez Córdova () - Jiménez Bracamonte (221213676) - Retana Romero ()

#include <iostream>
#include <vector>

using namespace std;

class libro {
private:
string titulo;
string autor;
string genero;
int anioPublic;
int ISBN;
string review;
int stock;
int numPaginas;

public:
libro(string titulo, string autor, string genero, int anioPublic, 
int ISBN, string review, int stock, int numPaginas) {
    this->titulo = titulo;
    this->autor = autor;
    this->genero = genero;
    this->anioPublic = anioPublic;
    this->ISBN = ISBN;
    this->review = review;
    this->stock = stock;
    this->numPaginas = numPaginas;
    }

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

int getISBN() {
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
};

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

int main() {

libro L1("Caperucita roja", "Charles Perrault", "Infantil", 1697, 001, "Muy bueno", 5, 20);
libro L2("El lorax", "Dr. Seuss", "Infantil", 1971, 002, "Muy bueno", 5, 20);
libro L3("Don Quijote de la Mancha", " Miguel de Cervantes", "Aventura", 1605, 003, "Muy bueno", 5, 500);

vector<libro*> v = {&L1, &L2, &L3};

imprimirLibros(v);

return 0;
}