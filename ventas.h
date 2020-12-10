#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED
#define ArchivoVentas "archivoventas.dat"

bool NuevaVenta () ;

bool GuardarVenta (ventas vta);
bool GuardarVenta (ventas vta,int pos);
int BuscarVenta (int);
ventas LeerVenta (int);
void MostrarVenta (ventas);

int CantVentas ();
float ValorVenta (int, int);

int ListarVentas ();
int ListarVentasPorFecha (fecha, int);
int ListarClientesPorMail (char *);
int ListarClientesPorId (int);
int ListarClientesPorDni (int);

#endif // VENTAS_H_INCLUDED
