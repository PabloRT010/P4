#include "tarjeta.hpp"
#include "usuario.hpp"
#include "cadena.hpp"
#include <cstddef>
#include <algorithm>
#include <iomanip>
bool luhn(const Cadena& numero);
std::set<Numero> Tarjeta:: TAR_;

bool EsBlanco::operator ()(char c) const {
return isspace(c);
}
bool EsDigito::operator ()(char c) const {
return isdigit(c);
}

Numero::Numero(const Cadena& num){
    
    int tam = num.length();
    char* aux = new char[tam + 1];
    char* ini = aux;
    char* fin = aux + tam;
    strcpy(aux, num.c_str());

    fin = remove_if(ini, fin, EsBlanco()); //iterator que apunta a la siguiente posición que se eliminó el espacio
    *fin = '\0';
    tam = strlen(aux);
    
    if(tam < 13 || tam > 19)
    throw Numero::Incorrecto(Numero::LONGITUD);

    if(find_if(ini, fin, not1(EsDigito())) != fin)
    throw Numero::Incorrecto(Numero::DIGITOS);

    if(!luhn(aux))
    throw Numero::Incorrecto(Numero::NO_VALIDO);

    num_ = aux;
    delete[] aux;
}

/*bool luhn(const Cadena& numero){
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}*/

Numero::operator const char *() const{
    
    return num_.c_str();
}

bool operator <(const Numero& a, const Numero& b){

    return(a.num_ < b.num_);
}
//clase tarjeta
Tarjeta::Tarjeta(const Numero& num, Usuario& tit, const Fecha& fech): numero_(num), titular_(&tit), activa_(true){

    Fecha hoy;
    if(fech < hoy){

        throw Caducada(fech);
    }
    if(TAR_.insert(num).second == false){ //si no esta duplicado

        throw Num_duplicado(num);
    }

    const_cast<Usuario*>(titular_)-> es_titular_de(*this); //asociacion con usuario. const_cast desecha el const

}

const Tarjeta::Tipo Tarjeta::tipo()const{
    Tipo aux;
    
    if(numero_.num_[0] == '3'){ 
        if(numero_.num_[1] == '4' || numero_.num_[1] == '7'){
            aux = AmericanExpress;
        }
        else
            aux = JCB;
    }
    else if(numero_.num_[0] == '4'){
        aux = VISA;
    }
    else if(numero_.num_[0] == '5'){
        aux = Mastercard;
    }
    else if(numero_.num_[0] == '6'){
        aux = Maestro;
    }
    else
        aux = Otro;
    
    return aux;
}

void Tarjeta::anula_titular(){
    titular_ = nullptr;
    activa_ = false;
}



std::ostream& operator <<(std::ostream& os, const Tarjeta& tar){
    os << tar.tipo() << '\n';
    os << tar.numero() << '\n';
    //ahora recorremos las cadenas nombre y apellido y transformamos a mayusculas todas sus letras
    for(auto iter = tar.titular()->nombre().begin(); iter != tar.titular()->nombre().end(); iter++){
        os << static_cast<char>(toupper(*iter)); //obligamos al iterador a ser un caracter
    }
    os << " ";
    for(auto iter = tar.titular()->apellidos().begin(); iter != tar.titular()->apellidos().end(); iter++){
        os << static_cast<char>(toupper(*iter)); //obligamos al iterador a ser un caracter
    }
    os << "\n";
    os << "Caduca: " << std::setw(2) << std::setfill('0') << tar.caducidad().mes() << '/' << std::setw(2) << std::setfill('0') << tar.caducidad().anno() % 100;
    return os;
}

std::ostream &operator<<(std::ostream &os, Tarjeta::Tipo t){
    if (t == Tarjeta::Otro)
        os << "Otro";
    else if (t == Tarjeta::VISA)
        os << "VISA";
    else if (t == Tarjeta::Mastercard)
        os << "Mastercard";
    else if (t == Tarjeta::Maestro)
        os << "Maestro";
    else if (t == Tarjeta::JCB)
        os << "JCB";
    else if (t == Tarjeta::AmericanExpress)
        os << "AmericanExpress";

    return os;
}

bool operator <(const Tarjeta& a, const Tarjeta& b){
    return a.numero() < b.numero();
}

Tarjeta::~Tarjeta(){
    TAR_.erase(numero_);

    if(titular_ != nullptr){
        const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
    }
}
