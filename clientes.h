#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#define ArchivoClientes "archivoclientes.dat"

void MenuVerCliente ();
int ObtenerIdCliente ();


int BuscarCliente (int);
int BuscarDni (int);
int BuscarMail (char *);

int CantClientes ();

clientes LeerCliente (int) ;
void MostrarCliente (clientes) ;

int ListarClientes ();

bool GuardarClienteNuevo (clientes);
bool GuardarCliente (clientes, int);

clientes ClientesMasVentas ();










#endif // CLIENTES_H_INCLUDED
