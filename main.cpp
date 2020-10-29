#include <iostream>
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
///const int ancho_formato = 80, alto_formato=25 ;


/// verificar dni que no se repita, ni el mail (agregarle el hotmail.com yahoo.com gmail.com )

int main(){
    initUI ();
    AperturaArchivos ();
    menu_principal ();
    cls ();

    return 0 ;
}
