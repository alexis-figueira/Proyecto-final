#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

void MenuVerCliente ();

int BuscarCliente (int);
int BuscarDni (int);
int BuscarMail (char *);

int CantClientes ();

clientes LeerCliente (int) ;
void MostrarCliente (clientes) ;

int ListarClientes ();

void CargarClienteNuevo (ventas);
bool GuardarClienteNuevo (clientes);
bool GuardarCliente (clientes, int);












#endif // CLIENTES_H_INCLUDED
