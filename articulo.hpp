#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <set>

class Autor{
    public:
    Autor(const Cadena& nom, const Cadena& apell, const Cadena& direc):nom_(nom), apell_(apell), direc_(direc){}
    const Cadena& nombre() const{return nom_;}
    const Cadena& apellidos() const {return apell_;}
    const Cadena& direccion() const {return direc_;}

    private:
    const Cadena nom_, apell_, direc_;
};

class Articulo{

    public:
        typedef std::set<Autor*> Autores;

        Articulo(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec, int st = 0): autores_(aut), cod_ref_(ref), titulo_(tit), fecha_pub_(fech), precio_(prec), stock_(st) {
            if(autores_.empty()){
                throw Autores_vacios{}; }
        };
        class Autores_vacios{};
        //observadores
        const Cadena& referencia() const;
        const Cadena& titulo() const;
        const Fecha& f_publi() const;
        double precio() const; // 2 decimales
        double& precio();
        int stock() const;
        int& stock();
        const Autores autores()const{return autores_;}
        virtual void impresion_especifica(std::ostream& os)const = 0; //virtual puro
     
    private:
        const Autores autores_;
        const Cadena cod_ref_;
        const Cadena titulo_;
        const Fecha fecha_pub_;
        double precio_;
        int stock_;
};

std::ostream& operator <<(std::ostream& os, Articulo& art);



#endif