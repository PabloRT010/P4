#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include <iostream>
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario.hpp"
class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{
    public:

    Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& us, const Tarjeta& tar, const Fecha& fech = Fecha());
    class Vacio{
        public:
        Vacio(Usuario* usu);
        Usuario& usuario() const;

        private:
        Usuario* usu_;
    };
    class Impostor{
        public:
        Impostor(Usuario* usu);
        Usuario& usuario() const;

        private:
        Usuario* usu_;
    };
    class SinStock{
        public:
        SinStock(Articulo* art);
        Articulo& articulo() const;

        private:
        Articulo* art_;
    };
    unsigned numero() const{return num_;}
    const Tarjeta* tarjeta() const{return tar_;}
    Fecha fecha() const{return fecha_;}
    double total() const{return importe_;}
    static unsigned n_total_pedidos() {return num_pedidos_;}

    private:
    unsigned num_;
    const Tarjeta* tar_;
    Fecha fecha_;
    double importe_;
    static unsigned num_pedidos_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& ped);



#endif