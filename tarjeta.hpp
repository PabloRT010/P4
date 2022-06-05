#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <set>
#include <iomanip>
class Tarjeta;
class Usuario;
//class Cadena;

class Numero{
    public:
    Numero(const Cadena& num);
    enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto{
        public:
        Incorrecto(Razon r): r_(r){}
        Razon razon() const {return r_;} 

        private:
        Razon r_;
    };
    friend Tarjeta;
    operator const char*() const; //constructor de conversion

    friend bool operator <(const Numero& a, const Numero& b);

    private:
    Cadena num_;
};

class Tarjeta{
    public:
    enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

    Tarjeta(const Numero& num, Usuario& tit, const Fecha& fech);
    Tarjeta(const Tarjeta& t) = delete;
    Tarjeta& operator =(const Tarjeta& t) = delete;
    //observadoras
    Numero numero()const;
    const Usuario* titular()const;
    Fecha caducidad()const ;
    bool activa()const;
    Tipo tipo() const;

    bool activa(bool par);
    void anula_titular();
    friend bool operator <(const Tarjeta& a, const Tarjeta& b);

    class Caducada{
        public:
        Caducada(const Fecha& f):f_caducada_(f){}
        Fecha cuando()const;

        private:
        Fecha f_caducada_;
    };

    class Num_duplicado{
        public:
        Num_duplicado(const Numero& num): num_(num){}
        Numero que() const;

        private:
        Numero num_;
    };

    class Desactivada{};
    friend Usuario;
    ~Tarjeta();
    private:
    Numero numero_;
    const Usuario* titular_;
    Fecha caducidad_;
    bool activa_;
    typedef std::set<Numero> TAR; //duplicidad de tarjeta
    static TAR TAR_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& tar);
std::ostream& operator<<(std::ostream &os, Tarjeta::Tipo t);


#endif