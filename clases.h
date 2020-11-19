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
    //
    int cod_art ;
    int cant_venta ;
    //
    float valor_venta ;
    bool estado ;

public:
    void CancelarVenta ();

    int GetCodArt ();
    void SetCodArt (int);

    int GetNumVenta ();
    void SetNumVenta (int);

    int GetIdCliente ();
    void SetIdCliente (int);

    float GetValorVenta ();
    void SetValorVenta (float);

    bool GetEstado ();
    void SetEstado (bool);

    int GetCantVenta ();
    void SetCantVenta (int);

    void MostrarFechaVenta ();
    void SetFecCompra (fecha);
};

class detalle {
private:
    int num_venta ;
    int num_detalle ;
    int cod_art ;
    int cant_venta ;
    float valor_detalle ;
    bool estado ;
public:
    detalle ();
    detalle (int);
    ~detalle ();


    int GetNumVenta ();
    void SetNumVenta (int);

    int GetNumDetalle ();
    void SetNumDetalle (int);

    int GetCodArt ();
    void SetCodArt (int);

    int GetCantVenta ();
    void SetCantVenta (int);

    float GetValorDetalle ();
    void SetValorDetalle (float);

    bool GetEstado ();
    void SetEstado (bool);
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

class articulo {
private:
    /// int tipo_art ;
    char nombre [25];
    int cod ;
    int stock ;
    float precio ;
    bool estado ;
public:

    articulo ();
    ~articulo ();

    void GetNombre (char*);
    void SetNombre (char*);

    int GetCodArt ();
    void SetCodArt (int);

    int GetStock ();
    void SetStock (int);

    float GetPrecio ();
    void SetPrecio (float);

    bool GetEstado ();
    void SetEstado (bool);






};




#endif // CLASES_H_INCLUDED
