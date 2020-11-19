#ifndef PRECIOS_H_INCLUDED
#define PRECIOS_H_INCLUDED
#define ArchivoPrecios "archivoprecios.dat"

float ValorVenta (int, int);

void CrearPrecios ();

void CambiarPrecio ();

void PrecioInvalido ();


/// --------------------------------------


void MostrarPrecioArticulo (articulo);

void MostrarListaPrecios ();

float BuscarPrecio (int);


#endif // PRECIOS_H_INCLUDED
