#include <iostream>
#include <cstdlib>
using namespace std;
#include "rlutil.h"
using namespace rlutil ;
#include "interfaz.h"
#include "menu.h"
#include "clases.h"
#include "ventas.h"
#include "validaciones.h"
#include "precios.h"
#include "stock.h"
#include "clientes.h"
#include "config.h"
#include "detallevta.h"

/// mas de 1 venta ;
/// tipo de articulo (1-andador , 2-cama 3-baston etc) con la posibilidad de seguir agregando tipos ;
/// COLOR DE STOCK

//funcion itoa (cstdlib)
// atoi (alreves)
// atof (con float)

/*
    char texto [10];
    itoa (15,texto,2);
    cout << texto ;
    devolucion (texto, "ROJO",ancho_formato,alto_formato);
    return 0;
*/

int main(){


    initUI ();
    AperturaArchivos ();
    menu_principal ();
    cls ();
    return 0 ;
}
