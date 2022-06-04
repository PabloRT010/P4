#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <cstring>
#include <random>
#include <map>
#include <unistd.h>
Usuario::ID Usuario::ID_;

Clave::Clave(const char* contr){

    if(strlen(contr) < 5)
        throw Clave::Incorrecta(Clave::CORTA);
        
    const char* caracteres = "0123456789abcdefghijklmnopqrstuvwxyz/.ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(rand() % 100);
    const char salt[2] = {caracteres[rand() % 64], caracteres[rand() % 64]};
    
    if (const char* pcc = crypt(contr, salt))
      contrasenna_ = pcc;
    else
       throw Incorrecta(ERROR_CRYPT);

}

bool Clave::verifica(const char* cad) const{

    if(!strcmp(crypt(cad,contrasenna_.c_str()), contrasenna_.c_str()))
        return true;
    else 
        return false;
    
}

//Usuario 
Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& clave): id_(id), nom_(nom), apell_(apell), dir_(dir), clave_(clave){

    if(ID_.insert(id).second == false){ //un conjunto no admite elementos duplicados, este metodo devuelve un booleano de si esta o no en el conjunto
        throw Id_duplicado(id);
    }
    
}

void Usuario::es_titular_de(Tarjeta& t){ //ligamos a tarjeta
    T[t.numero()] = &t; //la tarjeta del usuario cuyo numero sea el de la tarjeta pasada
}

void Usuario::no_es_titular_de(Tarjeta& t){
    T.erase(t.numero());
}

void Usuario::compra(Articulo& art, int cant){
    if(cant == 0){
        A.erase(&art);
    }
    if(cant > 0){
        A[&art] = cant;
    }
}

int Usuario::n_articulos()const{
    return A.size();
}


std::ostream& operator << (std::ostream& os, const Usuario& u){

    os << u.id() << " ["<< u.clave_.clave() <<"] "<<u.nombre()<<" "<<u.apellidos()<<"\n"; //**devuelve contrasenna cifrada??
    os << u.direccion()<<"\n";
    os << "Tarjetas :"<<"\n";

    for(Usuario::Tarjetas::const_iterator it = u.T.begin(); it != u.T.end(); it++){
        os << *(it->second) << "\n"; //mostramos la tarjeta 
    }
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u){

    os << "Carrito de compra de " << u.id() << " [Articulos:" << u.compra().size()<<"] " << std::endl;
    os << "===================================================================="<<std::endl;

    for (Usuario::Articulos::const_iterator it = u.compra().begin(); it != u.compra().end(); it++){
        os<<"\t" << it->second << " ["<< it->first->referencia() <<"] \""<< it->first->titulo()<<"\", " << it->first->f_publi().anno()<<". "<<std::fixed<< std::setprecision(2) << it->first->precio() << " €" << std::endl;
        
    }

    return os;
}

Usuario::~Usuario(){
    for (Usuario::Tarjetas::iterator it = T.begin(); it != T.end(); it++){
        it->second->anula_titular();
    }
    ID_.erase(id_);
}

//observadores clase usuario
Cadena Usuario::id() const {return id_;}
Cadena Usuario::nombre() const {return nom_;}
Cadena Usuario::apellidos() const {return apell_;}
Cadena Usuario::direccion() const {return dir_;}
const Usuario::Tarjetas& Usuario::tarjetas() const {return T;}
const Usuario::Articulos& Usuario::compra() const {return A;}