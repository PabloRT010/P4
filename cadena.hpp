#ifndef CADENA_HPP
#define CADENA_HPP
#include<iostream>
#include<cstring>
#include<stdexcept>
#include<cassert>
#include<iterator>
#include<iomanip>

class Cadena{
    
    public:
    //constructores
    explicit Cadena(unsigned tam = 0, char r = ' '); //ctor predeterminado
    Cadena(const Cadena& cad); //ctor copia
    Cadena(const char* cad); // a partir de cadena de bajo nivel
    Cadena(Cadena&& cad);
    //operadores
    Cadena& operator=(const Cadena& cad);
    Cadena& operator=(Cadena&& cad);
    Cadena& operator=(const char* cad);
    Cadena& operator+=(const Cadena& a);
    Cadena& operator +=(const char* cad);
    friend Cadena operator +(const Cadena& a, const Cadena& b); 
    
    //observadores
    //char* imprimir() const;
    const char* c_str() const;
    unsigned length() const;
    char operator[](const int n) const; // devuelve el caracter de la posicion
    char& operator[](const int n);
    char& at(int n); //comprueba si el numero esta en el rango de la cadena y si lo esta devuelve el caracter de la posicion
    char at(int n)const;
    //otras
    Cadena substr(int n, int tam)const;
    //destructor
    ~Cadena();

    //Iteradores
    typedef char* iterator ;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    private:
    //atributos
    char* s_;
    unsigned tam_; //no cuenta el caracter terminador /0
};
//flujo
std::ostream& operator<<(std::ostream& os, const Cadena& cad);
std::istream& operator>>(std::istream& is, Cadena& cad);

//bool operator !=(const char* a, const Cadena& cad);

//comparadores (externos para que se pueda construir en base a una cadena)
bool operator ==(const Cadena& a, const Cadena& b);
bool operator !=(const Cadena& a, const Cadena& b);
bool operator <(const Cadena& a, const Cadena& b);
bool operator >(const Cadena& a, const Cadena& b);
bool operator <=(const Cadena& a, const Cadena& b);
bool operator >=(const Cadena& a, const Cadena& b);

namespace std { // Estaremos dentro del espacio de nombres std
template <> // Es una especialización de una plantilla para Cadena
struct hash<Cadena> { // Es una clase con solo un operador publico
size_t operator() (const Cadena& cad) const // El operador función
{
hash<string> hs; // Creamos un objeto hash de string
const char* p = cad.c_str(); // Obtenemos la cadena de la Cadena
string s(p); // Creamos un string desde una cadena
size_t res = hs(s); // El hash del string. Como hs.operator()(s);
return res; // Devolvemos el hash del string
}
};
}
#endif
