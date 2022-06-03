#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& usu, Pedido& ped){
    Usu_Ped[&usu].insert(&ped);
    Ped_Usu[&ped] = &usu;
}

void Usuario_Pedido::asocia(Pedido& ped, Usuario& usu) {
    asocia(usu, ped);
}

Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& usu) {
return Usu_Ped.find(&usu)->second;
}
Usuario* Usuario_Pedido::cliente(Pedido& ped) {
return Ped_Usu.find(&ped)->second;
}