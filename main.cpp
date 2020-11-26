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
#include "articulo.h"

/**
- VER PORQUE NO FUNCIONA 'MOSTRARLISTAARTICULOS1 '

- TIPO DE ARTICULO: (1-Andador, 2-Cama, 3-Baston etc). Con la posibilidad de seguir agregando tipos ;

- REGISTROS:
    Mostrar por fecha
    Mostrar cliente con mas gastos
    Mostrar cliente con menos gastos

- VER BACK UP Y HACER LOS CAMBIOS
*/

/**
    funcion itoa (cstdlib)
    atoi (alreves)
    atof (con float)

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
