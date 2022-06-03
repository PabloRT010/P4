#include "cadena.hpp"



Cadena::Cadena(unsigned tam, char r){
    s_ = new char[tam + 1]; 
    unsigned i;
    for(i = 0; i < tam; i++){
        s_[i] = r;
    }
    tam_ = tam;
    s_[tam] = '\0';
}

Cadena::Cadena(const Cadena& cad){
    s_ = new char[cad.tam_ + 1];
    strcpy(s_, cad.s_);
    tam_ = cad.tam_;
} 
 
Cadena::Cadena(const char* cad): tam_(strlen(cad)){
    s_ = new char[tam_ + 1];
    strcpy(s_, cad);
    
}
Cadena::Cadena(Cadena&& cad): s_(cad.s_), tam_(cad.tam_)
{
    cad.s_ = nullptr;
    cad.tam_ = 0;

}

Cadena& Cadena::operator=(const Cadena& cad){
    if(this != &cad){
        
        if(tam_ != cad.tam_){
            delete[] s_;
            tam_ = cad.tam_;
            s_ = new char[tam_ + 1];
        }
        strcpy(s_, cad.s_);
    
    }
    return *this;
}
Cadena& Cadena::operator=(Cadena&& cad){

    if(this != &cad){
        if(tam_ != cad.tam_){
            delete[] s_;
        }

        tam_ = cad.tam_;
        s_ = cad.s_;
        cad.tam_ = 0;
        cad.s_ = nullptr;
    }  
    return *this;
}
Cadena& Cadena::operator=(const char* cad){

    if(tam_ != strlen(cad)){
        delete[] s_;
        tam_ = strlen(cad);
        s_ = new char[tam_ + 1];
    }
    strcpy(s_, cad);
    return *this;
}
Cadena& Cadena::operator +=(const Cadena& a){

    unsigned tam_aux = tam_ + a.tam_;
    Cadena cad(tam_aux);
    strcpy(cad.s_, s_);
    strcat(cad.s_, a.s_);
    *this = cad;
    return *this;
}
Cadena& Cadena::operator +=(const char* cad){
    
    unsigned tam_aux = tam_ + strlen(cad);
    Cadena C(tam_aux);
    strcpy(C.s_, s_);
    strcat(C.s_, cad);
    *this = C;
    return *this;
}

Cadena operator +(const Cadena& a, const Cadena& b){

    unsigned tam_aux = a.tam_ + b.tam_;
    Cadena aux(tam_aux);
    strcpy(aux.s_,a.s_);
    strcat(aux.s_, b.s_);

    return aux;
}

/*char* Cadena::imprimir() const{
    return s_;
}*/

unsigned Cadena::length() const{
    return tam_;
}

char Cadena::operator[](const int n) const{
    return s_[n];
}

char& Cadena::operator[](const int n){
    return s_[n];
}

char& Cadena::at(int n){
    if (n < 0 || n >= tam_){
        throw std::out_of_range("Fuera de rango"); 
    }
    return s_[n];
}

char Cadena::at(int n) const{
    if (n < 0 || n >= tam_){
        throw std::out_of_range("Fuera de rango"); 
    }
    return s_[n];    
}

bool operator ==(const Cadena& a, const Cadena& b){
     return (strcmp(b.c_str(), a.c_str()) == 0);
}

bool operator !=(const Cadena& a, const Cadena& b){
    return !(a == b);
}

/*bool operator !=(const char* a, const Cadena& cad){
    return((strcmp(cad.s_, a) != 0));
}*/

bool operator <(const Cadena& a, const Cadena& b){
     return (strcmp(a.c_str(), b.c_str()) < 0);
}

bool operator >(const Cadena& a, const Cadena& b){
     return (strcmp(a.c_str(), b.c_str()) > 0);
}

bool operator <=(const Cadena& a, const Cadena& b){
     return ( a == b || a < b);
}

bool operator >=(const Cadena& a, const Cadena& b){
     return (a == b || a > b);
}

Cadena Cadena::substr(int n, int tam) const{

    Cadena aux;
    int i;
    if(n < 0 || n + tam > tam_|| tam < 0){

        throw std::out_of_range("Fuera de rango");
    }
    else{

        for(i = 0; i < tam; i++){
            aux[i] = s_[i + n];
        }
        //aux[tam] = '\0';

        return aux;
    }
    
} 
const char* Cadena::c_str() const{
    return s_;
}

std::ostream& operator<<(std::ostream& os, const Cadena& cad){
    os << cad.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, Cadena& cad){
    char s[33];
    s[0] = '\0';
    is >> std::setw(sizeof(s))>>s;
    Cadena S(s);
    cad = std::move(S);
    return is;
}

Cadena::~Cadena(){
    delete[]s_;
}

//Iteradores
Cadena::iterator Cadena::begin(){
    return s_;
}

Cadena::const_iterator Cadena::begin() const{
    return cbegin();
}

Cadena::iterator Cadena::end(){
    return s_ + length();
}

Cadena::const_iterator Cadena::end() const{
    return cend();
}

Cadena::const_iterator Cadena::cbegin() const{
    return s_;
}

Cadena::const_iterator Cadena::cend() const{
    return s_ + length();
}

Cadena::reverse_iterator Cadena::rbegin(){
    return reverse_iterator(end());
}

Cadena::reverse_iterator Cadena::rend(){
    return reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::crbegin() const{
    return const_reverse_iterator(cend());
}

Cadena::const_reverse_iterator Cadena::crend() const{
    return const_reverse_iterator(cbegin());
}

Cadena::const_reverse_iterator Cadena::rbegin() const{
    return crbegin();
}

Cadena::const_reverse_iterator Cadena::rend() const{
    return crend();
}