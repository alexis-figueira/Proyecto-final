#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

struct fecha {
    int dia, mes, anio;
};

class ventas {
private:
    fecha fec_compra ;
    int num_venta ;
    int id_cliente ;
    int cod_art ;
    int cant_venta ;
    char nombre [50] ;
    char apellido [50] ;
    int dni ;
    char mail [50];
    float valor_venta ;
    bool estado ;

public:
    bool SetNuevaVenta ();
    void CancelarVenta ();

    int GetCodArt ();
    int GetNumVenta ();
    int GetIdCliente ();
    void MostrarNombre();
    void GetNombre (char *);
    void SetApellido (char*);
    void GetApellido (char*);
    void MostrarApellido ();
    int GetDni ();
    void GetMail (char*);
    void MostrarMail ();
    float GetValorVenta ();
    bool GetEstado ();
    void MostrarFechaVenta ();
    int GetCant ();
};

struct stock {
    float andador_comun ;
    bool an_co;
    float andador_ruedas ;
    bool an_ru ;
    float andador_asiento ;
    bool an_as ;

    float cama_manual_eco;
    bool ca_eco;
    float cama_manual;
    bool ca_ma;
    float cama_electrica ;
    bool ca_el;

    float baston_1;
    bool ba_1;
    float baston_3;
    bool ba_3;
    float baston_4;
    bool ba_4;

    float silla_t;
    bool si_t;
    float silla_a;
    bool si_a;
    float silla_r;
    bool si_r;
};

class clientes{
private:
    int id_cliente ;
    char nombre [50];
    char apellido [50];
    int dni ;
    char mail [50];
    float acumulado ;
    bool estado ;
public:
    clientes ();
    clientes (int);
    ~clientes ();
    float GetAcumulado ();
    void SetAcumulado (float);
    int GetId ();
    void SetId (int);
    void GetApellido (char*);
    void SetApellido (char*);
    void GetNombre (char*);
    void SetNombre (char*);
    void GetMail (char*);
    void SetMail (char*);
    int GetDni ();
    void SetDni (int);
    bool GetEstado ();
    void SetEstado (bool);

};

struct precios {
    float andador_comun ;
    float andador_ruedas ;
    float andador_asiento ;

    float cama_manual_eco;
    float cama_manual ;
    float cama_electrica ;

    float baston_1;
    float baston_3;
    float baston_4;

    float silla_t;
    float silla_a;
    float silla_r;
};


#endif // CLASES_H_INCLUDED
