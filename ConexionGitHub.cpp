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
    string ISBN;
    string review;
    int stock;
    int numPaginas;
    static int numeroLibro

    string generarISBN() {
        // Obtener el año de publicación con 4 dígitos
        string anio = to_string(anioPublic);
        // Obtener el número de libro con 2 dígitos
        string numLibroStr = to_string(numeroLibro);
        // Rellenar con ceros a la izquierda si es necesario
        numLibroStr = std::setw(2) << std::setfill('0') << numLibroStr;

        // Concatenar las partes para formar el ISBN
        string isbn = "978" + anio + numLibroStr;

        return isbn;
    }

public:
    libro(string titulo, string autor, string genero, int anioPublic, 
    string ISBN, string review, int stock, int numPaginas) {
        this->titulo = titulo;
        this->autor = autor;
        this->genero = genero;
        this->anioPublic = anioPublic;
        this->ISBN = ISBN;
        this->review = review;
        this->stock = stock;
        this->numPaginas = numPaginas;
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

libro L1("Caaaaaaa", "Charles Perrault", "Infantil", 1697, 001, "Muy bueno", 5, 20);
libro L2("Eaaaaaaaaa", "Dr. Seuss", "Infantil", 1971, 002, "Muy bueno", 5, 20);
libro L3("Daaaaaaaaa", " Miguel de Cervantes", "Aventura", 1605, 003, "Muy bueno", 5, 500);

vector<libro*> v = {&L1, &L2, &L3};

imprimirLibros(v);

return 0;
}