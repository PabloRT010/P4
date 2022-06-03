#include "pedido.hpp"
#include <iomanip>
#include <cstddef>
unsigned Pedido::num_pedidos_ = 0;
Pedido::Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& us, const Tarjeta& tar, const Fecha& fech):tar_(&tar), fecha_(fech){
    if(us.compra().empty()){
        throw Pedido::Vacio(&us);
    }
    if(tar.titular() != &us){
        throw Pedido::Impostor(&us);
    }
    if(tar.caducidad() < fech){
        throw Tarjeta::Caducada(tar.caducidad());
    }
    if(!tar.activa()){
        throw Tarjeta::Desactivada();
    }
    for(Usuario::Articulos::const_iterator it = us.compra().begin(); it != us.compra().end(); it++){
        
        if(it->second > it->first->stock()){ //si el valor del iterador es mayor que el stock de la clave(articulo)
            const_cast<Usuario::Articulos&>(us.compra()).clear(); //vaciamos carrito
            throw Pedido::SinStock(it->first); //pasamos el articulo encontrado con mayor stock del que hay
        }
    }
    //calculamos el importe
    importe_ = 0;
    us_ped.asocia(*this, us); //asociamos pedido con usuario

    for(Usuario::Articulos::const_iterator iter = us.compra().begin(); iter != us.compra().end() ; iter ++) {
        importe_ += iter->second * iter->first->precio(); //sumamos al importe :(cantidad producto * precio)
        ped_art.pedir(*iter->first, *this, iter->first->precio(), iter->second); //creamos enlace bidireccional entre pedido y articulo
        iter->first->stock() -= iter->second; //decrementamos el stock del articulo
    }
    const_cast<Usuario::Articulos&>(us.compra()).clear();
    num_ = ++ num_pedidos_;
}

std::ostream& operator <<(std::ostream& os, const Pedido& ped){
    os << "Núm. pedido: "<< ped.numero()<< "\n";
    os << "Fecha: "<<ped.fecha()<< "\n";
    os << "Pagado con: "<< *ped.tarjeta()<<"\n";
    os << "Importe: "<< std::fixed << std::setprecision(2) << ped.total()<< " €";

    return os;
}

//clase Pedido constructores 
Pedido::Vacio::Vacio(Usuario* usu): usu_(usu){}
Pedido::Impostor::Impostor(Usuario* usu): usu_(usu){}
Pedido::SinStock::SinStock(Articulo* art): art_(art){}