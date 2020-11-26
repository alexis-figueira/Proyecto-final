#ifndef DETALLEVTA_H_INCLUDED
#define DETALLEVTA_H_INCLUDED
#define ArchivoDetalle "archivodetalle.dat"


bool GuardarDetalle (detalle) ;
bool GuardarDetalle (detalle, int);

int CantDetalle ();
int BuscarDetalle (int, int);



int LeerTodoDetalle (int, detalle*); // recibe numero de venta y vector detalle, devuelve vector de los detalles y cantidad de detalles.
detalle LeerUnDetalle (int, int);

void MostrarUnDetalle (detalle);
void MostrarDetalleVenta (int cant, detalle* dle,ventas); /// falta hacer

void ListarDetalleVenta (int);


#endif // DETALLEVTA_H_INCLUDED
