#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define VentasBkp "archivoventas.bkp"
#define ArticulosBkp "archivoarticulos.bkp"
#define DetallesBkp "archivodetalles.bkp"
#define ClientesBkp "archivoclientes.bkp"




bool BkpArticulo ();
bool BkpDetalle ();
bool BkpClientes ();
bool BkpVentas ();

bool RecuperarVentas ();
bool RecuperarClientes ();
bool RecuperarArticulo ();
bool RecuperarDetalle ();

bool BorrarClientes ();
bool BorrarVentas ();
bool BorrarArticulo ();
bool BorrarDetalle ();

bool BorrarBkpClientes ();
bool BorrarBkpVentas ();
bool BorrarBkpArticulo ();
bool BorrarBkpDetalle ();

int CantClientesBkp ();
int CantVentasBkp ();
int CantDetallesBkp ();
int CantArticuloBkp ();



#endif // CONFIG_H_INCLUDED
