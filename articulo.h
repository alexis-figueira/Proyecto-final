#ifndef ARTICULO_H_INCLUDED
#define ARTICULO_H_INCLUDED
#define ArchivoArticulo "archivoarticulo.dat"

int BuscarArticulo (int); ///Recibe codigo y devuelve posicion

articulo LeerArticulo (int);

void ListarArticulo (articulo);

void MostrarUnArticulo (articulo);

void MostrarListaArticulos ();

bool BuscarEstadoArt (int); /// Recibe posicion y devuelve estado

float BuscarPrecio (int); /// Recibe posicion y devuelve precio del art

void BuscarNombre (int) ; /// Recibe posicion y devuelve nombre por *char

int CantArt (); /// Devuelve la cantidad de artículos en el archivo

void CargarArticulo ();

bool GuardarArticulo (articulo);

bool GuardarArticulo (articulo, int);
#endif // ARTICULO_H_INCLUDED
