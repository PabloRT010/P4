#include "pedido-articulo.hpp"
#include <iomanip>

LineaPedido::LineaPedido(double precio_venta, unsigned cant):precio_venta_(precio_venta), cant_(cant){}

std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}

bool OrdenaArticulos::operator()(const Articulo* a, const Articulo* b) const {
    return a->referencia() < b->referencia(); //ordenamos por referencia (asc)
}

bool OrdenaPedidos::operator()(const Pedido* a, const Pedido* b) const{
    return a->numero() < b->numero(); //ordenamos por numero (asc)
}

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, unsigned cant){
    Ped_Art[&ped].insert(std::make_pair(&art, LineaPedido(precio, cant)));
    Art_Ped[&art].insert(std::make_pair(&ped, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, unsigned cant){
    pedir(ped, art, precio, cant);
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped){
    return Ped_Art.find(&ped)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art) {
    if(Art_Ped.find(&art) == Art_Ped.end()) { //si no encontramos el articulo en pedidos
        Pedido_Articulo::Pedidos vacio;
        return vacio;
    } 
    else
        return Art_Ped.find(&art)->second;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itsped){
    double precio = 0;
    Pedido_Articulo::ItemsPedido::const_iterator i;
    os << "====================================================\n";
    os << " PVP \t Cant. \t Articulo \n";
    os << "====================================================\n";
    for(i = itsped.begin(); i != itsped.end(); ++i){
        os << " " << i->second.precio_venta() << "€\t";
        os << i->second.cantidad() << "\t";
        os << "[" << i->first->referencia() << "] ";
        os << "\"" << i->first->titulo() << "\" " << "\n";
        precio = precio + i->second.precio_venta() * i->second.cantidad();
    }
    os << "===================================================\n";
    os << std::fixed;
    os << std::setprecision(2) << precio << " €" << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
    double precio = 0;
    unsigned total = 0;
    Pedido_Articulo::Pedidos::const_iterator i;
    os << "====================================================\n";
    os << " PVP \t Cantidad \t Fecha venta \n";
    os << "====================================================\n";
    for(i = p.begin(); i != p.end(); ++i){
        os << " " << i->second.precio_venta() << "€\t";
        os << i->second.cantidad() << "\t";
        os << i->first->fecha() << "\n";
        precio = precio + i->second.precio_venta() * i->second.cantidad();
        total = total + i->second.cantidad();
    }
    os << "====================================================\n";
    os << std::fixed;
    os << std::setprecision(2) << precio << " €\t" << total <<"\n" ;
    return os;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const{
    double precio = 0;
    std::map<Pedido*, Pedido_Articulo::ItemsPedido, OrdenaPedidos>::const_iterator it;
    for(it = Ped_Art.begin() ; it != Ped_Art.end() ; it++){
        os << "Pedido núm. " << it->first->numero();
        os << "\tCliente: " << it->first->tarjeta()->titular()->nombre() << " " << "\n";
        os << "Fecha: " << it->first->fecha() << it->second;
        precio += it->first->total();
    }
    os << std::fixed;
    os << "TOTAL VENTAS: " << std::setprecision(2) << precio << " €" <<"\n";
    return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const{
    
    std::map<Articulo*, Pedido_Articulo::Pedidos, OrdenaArticulos>::const_iterator iter;
    for(iter = Art_Ped.begin() ; iter != Art_Ped.end() ; iter++){
        os << "Ventas de " << "[" << iter->first->referencia() << "] ";
        os << "\"" << iter->first->titulo() << "\" \n" << iter->second<< "\n"; //mostramos titulo y pedidos de ese articulo
    }
    return os;
}