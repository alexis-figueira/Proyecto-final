#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED


void CambiarTodoStock ();

bool CambiarStockArticulo (int, int, bool);

void MenuAgregarStock ();

void MenuReducirStock ();

void MenuEstado ();

void StockInvalido ();

void MostrarStockArticulo (int cod_art);

void MostrarListaStock ();

int BuscarStock (int);

bool BuscarEstadoArt (int);

#endif // STOCK_H_INCLUDED
