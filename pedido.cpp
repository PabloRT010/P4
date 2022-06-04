#include "pedido.hpp"
#include <iomanip>
#include <cstddef>

unsigned Pedido::num_pedidos_ = 0;
Pedido::Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& us, const Tarjeta& tar, const Fecha& fech):tar_(&tar), importe_(0), fecha_(fech){
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
        
        if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(it->first)) {
            if(it->second > AA->stock()) {
                for(auto iter = us.compra().begin() ; iter != us.compra().end() ; iter ++)
                    us.compra(*iter->first, 0);
                    throw SinStock(it->first);
                }
            } else if(LibroDigital* LD = dynamic_cast<LibroDigital*>(it->first)) {
                if(LD->f_expir() < fech)
                us.compra(*it->first, 0);
                }
    }
    if(us.compra().empty())
        throw Vacio(&us);
    //calculamos el importe
    us_ped.asocia(*this, us); //asociamos pedido con usuario

    for(Usuario::Articulos::const_iterator iter = us.compra().begin(); iter != us.compra().end() ; iter ++) {
        importe_ += iter->second * iter->first->precio(); //sumamos al importe :(cantidad producto * precio)
        ped_art.pedir(*iter->first, *this, iter->first->precio(), iter->second); //creamos enlace bidireccional entre pedido y articulo
        
        if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter->first))
            AA->stock() -= iter->second;
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
//observadores
Usuario& Pedido::Vacio::usuario() const{return *usu_;}
Usuario& Pedido::Impostor::usuario() const{return *usu_;}
Articulo& Pedido::SinStock::articulo() const{return *art_;}