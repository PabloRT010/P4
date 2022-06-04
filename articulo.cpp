#include"articulo.hpp"




const Cadena& Articulo::referencia()const{
    return cod_ref_;
}

const Cadena& Articulo::titulo()const{
    return titulo_;
}

const Fecha& Articulo::f_publi()const{
    return fecha_pub_;
}

double Articulo::precio()const{
    return precio_;
}

double& Articulo::precio(){
    return precio_;
}

void Libro::impresion_especifica(std::ostream& os) const{
    os<< n_paginas_<<" pags, "<<stock()<<" unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const{
    os<< tam_<<" MB, "<<stock()<<" unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const{
    os<< "A la venta hasta el "<<fech_expir_<<".";
}

std::ostream& operator <<(std::ostream& os, Articulo& art){
    os<<"["<<art.referencia()<<"] "<<'"'<<art.titulo()<<'"'<<", de ";
	
	for(auto i = art.autores().begin();i!=art.autores().end(); i++){

		if(i == --art.autores().end())
			os << (*i)->apellidos();
		else
            os << (*i)->apellidos() <<", ";
	}

    os << ". "<<art.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<art.precio()<<" €\n\t";
    art.impresion_especifica(os);
    return os;
}

