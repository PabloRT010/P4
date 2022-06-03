#ifndef FECHA_HPP_
#define FECHA_HPP_
#include<iostream>
#include<ctime>



class Fecha{
    public:

    class Invalida{//excepción lanzada cuando una fecha no es válida (no cumple los requisitos)
    
        public:
        Invalida(const char* cad):error(cad){} //constructor de fecha inválida que le pasamos una cadena indicando el error
        const char* por_que()const;

        private:
        const char* error; //cada excepción enviará un mensaje de error
    };
    //variables públicas:
    static const unsigned AnnoMinimo = 1902;
    static const unsigned AnnoMaximo = 2037;
    //constructores:
    explicit Fecha(unsigned d = 0, unsigned m = 0, unsigned a = 0); //constructor
    Fecha(const Fecha& f) = default; //ctor copia
    Fecha(const char* cad);//constructor con cadena (de conversión)

    //friend
    friend Fecha& operator+=(Fecha& f, int n);  //suma de dias a una fecha con asignación   
    friend Fecha& operator-=(Fecha& f, int n);  //resta de dias a una fecha con asignación
    //funcion cadena
    const char* cadena() const;                    //funcion que imprime la fecha en un formato
    //observadores:
    unsigned dia()const;
    unsigned mes()const;
    unsigned anno()const;

    Fecha& operator++();         //preincremento de una fecha
    Fecha& operator--();         //predecremento de una fecha
    Fecha operator++(int);    //postincremento de una fecha (pasamos el entero para diferenciar)
    Fecha operator--(int);    //postdecremento de una fecha (pasamos el entero para diferenciar)

    private:
    void probar_dia(unsigned d, unsigned m, unsigned a);
    void probar_mes(unsigned m);
    void probar_anno(unsigned a);
    unsigned dia_, mes_, anno_;
};
//operadores:
    Fecha operator+(const Fecha& f, int n);   //suma de días a una fecha
    Fecha operator-(const Fecha& f, int n);   //resta de días a una fecha
   /* Fecha& operator++(Fecha& f);         //preincremento de una fecha
    Fecha& operator--(Fecha& f);         //predecremento de una fecha
    Fecha operator++(Fecha& f, int);    //postincremento de una fecha (pasamos el entero para diferenciar)
    Fecha operator--(Fecha& f, int);    //postdecremento de una fecha (pasamos el entero para diferenciar)*/
    
    
//comparadores
    bool operator ==(const Fecha&, const Fecha& b);
    bool operator !=(const Fecha& a, const Fecha& b);
    bool operator <(const Fecha& a, const Fecha& b);
    bool operator >(const Fecha& a, const Fecha& b);
    bool operator <=(const Fecha& a, const Fecha& b);
    bool operator >=(const Fecha& a, const Fecha& b);

//flujo
std::ostream& operator<<(std::ostream& os, const Fecha& fech);
std::istream& operator>>(std::istream& is, Fecha& fech);

inline const char* Fecha::Invalida::por_que()const{

    return error;
}


#endif