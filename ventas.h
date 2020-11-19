#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED
#define ArchivoVentas "archivoventas.dat"

bool NuevaVenta () ;

bool GuardarVenta (ventas vta);

bool GuardarVenta (ventas vta,int pos);

int BuscarVenta (int);

int CantVentas ();

ventas LeerVenta (int);

int ListarVentas () ;

int ListarClientesPorMail (char *);

int ListarClientesPorId (int);

int ListarClientesPorDni (int);

void MostrarVenta (ventas);

float ValorVenta (int, int);

#endif // VENTAS_H_INCLUDED
