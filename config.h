#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define VentasBkp "archivoventas.bkp"
#define StockBkp "archivostock.bkp"
#define PreciosBkp "archivoprecios.bkp"
#define ClientesBkp "archivoclientes.bkp"



bool BkpClientes ();
bool BkpPrecios ();
bool BkpVentas ();
bool BkpStock ();

bool RecuperarVentas ();
bool RecuperarStock ();
bool RecuperarClientes ();
bool RecuperarPrecios ();

bool BorrarClientes ();
bool BorrarVentas ();
bool BorrarStock ();
bool BorrarPrecios ();

bool BorrarBkpClientes ();
bool BorrarBkpVentas ();
bool BorrarBkpStock ();
bool BorrarBkpPrecios ();

int CantClientesBkp ();
int CantVentasBkp ();




#endif // CONFIG_H_INCLUDED
