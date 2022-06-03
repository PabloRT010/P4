#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP
#include <iostream>
#include <map>
#include <set>
#include "usuario.hpp"
#include "pedido.hpp"
class Pedido;
class Usuario;

class Usuario_Pedido{
    public:
    typedef std::set<Pedido*> Pedidos;
    void asocia(Usuario& usu, Pedido& ped);
    void asocia(Pedido& ped, Usuario& usu);
    Pedidos& pedidos(Usuario& usu);
    Usuario* cliente(Pedido& ped); 
    private:
    std::map<Usuario*, Pedidos> Usu_Ped;
    std::map<Pedido*, Usuario*> Ped_Usu;
};

#endif