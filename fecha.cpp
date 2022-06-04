#include "fecha.hpp"
#include <ctime>
#include <iostream>
#include <locale>
#include <cstring>
#include <exception>
using namespace std;

Fecha::Fecha(unsigned d, unsigned m, unsigned a):dia_(d), mes_(m), anno_(a){
    if(d == 0 || m == 0 || a == 0){
        time_t now = time(nullptr);
        tm* dt = localtime(&now);

        if (a == 0)
            anno_ = dt->tm_year + 1900;
        if(m == 0)
            mes_ = dt->tm_mon + 1;   
        if(d == 0)
            dia_ = dt->tm_mday;
    }
    probar_anno(anno_);
    probar_mes(mes_);
    probar_dia(dia_,mes_,anno_);
}
void Fecha::probar_dia(unsigned d, unsigned m, unsigned a){
    
    if(d > 31){

        throw(Invalida("No puedes poner un número mayor al 31 en el día"));
    }
    if((m == 4 || m == 6 || m == 9 || m == 11) && d > 30){
            
        throw(Invalida("Este mes no puede tener mas de 30 días"));
    }
    if(m == 2){
        if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)){
            if(d > 29){
                throw(Invalida("Febrero tiene 28 días si el año no es bisiesto"));
            }
        }
        else if(d > 28)//comprobamos si es bisiesto
                throw(Invalida("No hay más de 29 días en un año bisiesto"));
    }
    dia_ = d;
   
        
}

void Fecha::probar_mes(const unsigned m){
    
    if (m > 12){
        throw Invalida("El mes no puede ser mayor que 12");
    }
    else{
        mes_ = m;
    }
}

void Fecha::probar_anno(const unsigned a){
    
    if (a < Fecha::AnnoMinimo){
        throw Invalida("Año menor que el año min");
    }
    if (a > Fecha::AnnoMaximo){
        throw Invalida("Año mayor que el maximo");
    }
    else{
        anno_ = a;
    }
}

Fecha::Fecha(const char* cad){

    int d = 0, m = 0, a = 0;
    int n_param = std::sscanf(cad,"%d/%d/%d", &d, &m, &a); //aqui se guardará el número de parámetros separados por barra

    if(n_param != 3){
        throw Invalida("Cadena no válida, tiene que ser de la forma dd/mm/aaaa");
    }
    else{ 
        *this = Fecha(d,m,a); 
    }
}

//Fecha::Fecha(const Fecha& f): dia_(f.dia_), mes_(f.mes_), anno_(f.anno_){} //definición ctor copia

//operadores

Fecha& operator+=(Fecha& f, int n){

    //time_t aux = std::time(nullptr);
    tm nueva_fecha = {};
    nueva_fecha.tm_mday = f.dia_ + n;
    nueva_fecha.tm_mon = f.mes_ - 1;
    nueva_fecha.tm_year = f.anno_ - 1900;

    mktime(&nueva_fecha); //esta funcion tiene en cuenta los años bisiestos y realiza todas las sumas/restas de meses y años necesarias según la suma de el día de la fecha y el numero
    f.dia_ = nueva_fecha.tm_mday;
    f.mes_ = nueva_fecha.tm_mon + 1;

    //try{ //probamos si la fecha se encuentra en el intervalo indicado
    f.probar_anno(nueva_fecha.tm_year + 1900);
    //}catch(Fecha:: Invalida& e){
    //    cerr<<e.por_que()<<endl;
    
   // }
    return f;
}


Fecha& operator-=(Fecha& f, int n){
    return f += -n;
}

/*Fecha& Fecha::operator=(const Fecha& f){
    if(dia_ == f.dia_ && mes_ == f.mes_ && anno_ == f.anno_){
        return *this;
    }
    else{
        dia_ = f.dia_;
        mes_ = f.mes_;
        anno_ = f.anno_;
        return *this;
    }
}*/
Fecha operator+(const Fecha& f, int n){
    Fecha t;
    t = f;
    return t += n;
}

Fecha operator-(const Fecha& f, int n){
    Fecha t;
    t = f;
    return t += -n;
}

Fecha& Fecha::operator++(){//preincremento
    return *this += 1;
}

Fecha Fecha::operator++(int n){//postincremento  
    Fecha t;
    t = *this;
    *this += 1;
    return t;
}

Fecha& Fecha::operator--(){//predecremento
    return *this+= -1;
}

Fecha Fecha::operator--(int n){
    Fecha t;
    t = *this;
    *this += -1;
    return t;
}

bool operator==(const Fecha& a, const Fecha& b){
    return(a.dia() == b.dia() && a.mes() == b.mes() && a.anno() == b.anno());
}

bool operator!=(const Fecha& a, const Fecha& b){
    return !(a == b);
}

bool operator<(const Fecha& a, const Fecha& b){

    if(a.anno() < b.anno()){
        return true;
    }
    else if(a.anno() == b.anno()){
        if(a.mes() < b.mes())
            return true;
        else if(a.mes() == b.mes() && a.dia() < b.dia())
            return true;
        else 
            return false;
    }
    else
        return false;
        
}

bool operator>(const Fecha& a, const Fecha& b){
    return !((a <= b));
}

bool operator<=(const Fecha& a, const Fecha& b){

    return (a < b || a == b);
}

bool operator>=(const Fecha& a, const Fecha& b){
    
    return !((a < b));
}

//observadores:
unsigned Fecha::dia() const{
    return dia_;
}

unsigned Fecha::mes() const{
    return mes_;
}

unsigned Fecha::anno() const{
    return anno_;
}

//flujo
const char* Fecha::cadena()const{
    time_t now = time(nullptr);
    tm* dt = localtime(&now);
    
    locale::global(locale("es_ES.UTF-8"));
    tm* fecha_cadena = localtime(&now);
    fecha_cadena->tm_mday = dia_;
    fecha_cadena->tm_mon = mes_ - 1;
    fecha_cadena->tm_year = anno_ - 1900;

    static char cadena[50];
    mktime(fecha_cadena);
    strftime(cadena, 50,"%A %d de %B de %Y", fecha_cadena); //referencias en cpp reference
    return cadena;
}
//flujo
ostream& operator<<(ostream& os, const Fecha& fech){
    os << fech.cadena();
    return os;
}

std::istream& operator>>(std::istream& is, Fecha& fech){
    int d = 0, m = 0, a = 0;
    char aux[50];
    is >> aux;

    if(strlen(aux) > 10){ 
        is.setstate(ios::failbit);
        throw Fecha::Invalida("Mal hecho, desbordamiento");
    }
    /*if(sscanf(aux, "%d/%d/%d", &d, &m, &a) != 3){ //sscanf devuele el numero de parametros leidos del buffer
        is.setstate(ios::failbit);
        throw Fecha::Invalida("Desbordamiento o formato invalido");
    }*/

    try{
        Fecha f(aux);
        fech = f;
    }catch(Fecha::Invalida &e){
        is.setstate(ios::failbit);
        throw Fecha::Invalida("Entrada Invalida");
    }
        
    
    return is;
}