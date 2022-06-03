#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_
#include "articulo.hpp"
#include "pedido.hpp"
#include <map>
class Articulo;
class Pedido;

class LineaPedido{
    public:
    explicit LineaPedido(double precio_venta, unsigned cant = 1);
    double precio_venta() const {return precio_venta_;}
    unsigned cantidad() const {return cant_;}

    private:
    double precio_venta_;
    unsigned cant_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& lp);

class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool> {
    public:
    bool operator()(const Pedido* a, const Pedido* b) const;
};

class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool> {
    public:
    bool operator()(const Articulo* a, const Articulo* b) const;
};

class Pedido_Articulo{
    public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir(Pedido& ped, Articulo& art, double precio, unsigned cant = 1);
    void pedir(Articulo& art, Pedido& ped, double precio, unsigned cant = 1);
    ItemsPedido& detalle(Pedido& ped);
    Pedidos ventas(Articulo& art);
    std::ostream& mostrarDetallePedidos(std::ostream& os) const;
    std::ostream& mostrarVentasArticulos(std::ostream& os) const;
    private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos>Ped_Art;
    std::map<Articulo*, Pedidos, OrdenaArticulos>Art_Ped;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itsped);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds);



#endif