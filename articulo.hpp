#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <iomanip>
#include <set>

class Autor{
    public:
    Autor(const Cadena& nom, const Cadena& apell, const Cadena& direc):nom_(nom), apell_(apell), direc_(direc){}
    Cadena nombre() const{return nom_;}
    Cadena apellidos() const {return apell_;}
    Cadena direccion() const {return direc_;}

    private:
    Cadena nom_, apell_, direc_;
};

class Articulo{

    public:
        typedef std::set<Autor*> Autores;

        Articulo(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec): autores_(aut), cod_ref_(ref), titulo_(tit), fecha_pub_(fech), precio_(prec) {
            if(autores_.empty()){
                throw Autores_vacios(); }
        };
        class Autores_vacios{};
        //observadores
        const Cadena& referencia() const;
        const Cadena& titulo() const;
        const Fecha& f_publi() const;
        double precio() const; // 2 decimales
        double& precio();
        const Autores autores()const{return autores_;}
        virtual void impresion_especifica(std::ostream& os)const = 0; //virtual puro
        virtual ~Articulo(){};
     
    private:
        const Autores autores_;
        const Cadena cod_ref_;
        const Cadena titulo_;
        const Fecha fecha_pub_;
        double precio_;
        //int stock_;
};

class ArticuloAlmacenable: public Articulo{
    public:
    ArticuloAlmacenable(const Articulo::Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec, int st = 0):Articulo(aut, ref, tit, fech, prec), stock_(st){}    
    int stock() const{return stock_;}
    int& stock(){return stock_;}
    virtual void impresion_especifica(std::ostream& os)const = 0; //virtual puro
    virtual ~ArticuloAlmacenable(){};

    private:
    int stock_;
};

class Libro: public ArticuloAlmacenable{
    public:
    Libro(const Articulo::Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec, int numpag, int st = 0): ArticuloAlmacenable(aut, ref, tit, fech, prec, st), n_paginas_(numpag) {}
    int n_pag()const {return n_paginas_;}
    virtual void impresion_especifica(std::ostream& os)const;

    protected:
    const int n_paginas_;
};

class Cederron:public ArticuloAlmacenable{
    public:

    Cederron(const Articulo::Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec, double tam, int st = 0): ArticuloAlmacenable(aut, ref, tit, fech, prec, st), tam_(tam) {}
    double tam()const{return tam_;}
    virtual void impresion_especifica(std::ostream& os)const;

    private:
    double tam_;
};

class LibroDigital: public Articulo{
    public:
    LibroDigital(const Articulo::Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fech, double prec, const Fecha& f_expir = Fecha()): Articulo(aut, ref, tit, fech, prec), fech_expir_(f_expir){}
    const Fecha f_expir() const{return fech_expir_;}
    virtual void impresion_especifica(std::ostream&)const;

    private:
    const Fecha fech_expir_;

};

std::ostream& operator <<(std::ostream& os, const Articulo& art);



#endif