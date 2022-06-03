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

int Articulo::stock()const{
    return stock_;
}

int& Articulo::stock(){
    return stock_;
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