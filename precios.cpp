#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "interfaz.h"
#include "clases.h"
#include "precios.h"
#include "articulo.h"
//const char *ArchivoPrecios = "archivoprecios.dat" ;


float ValorVenta (int cod_art, int cant_venta){
    int pos ;
    articulo reg;
    float valor;
    pos=BuscarArticulo (cod_art);
    if(pos<0){
        return - 1 ;
    }
    reg=LeerArticulo (pos);
    valor = reg.GetPrecio () * cant_venta ;
    return valor ;
}

void PrecioInvalido (){
    devolucion ("PRECIO INVÁLIDO", "BLANCO",ancho_formato, alto_formato);
    titulo ("PRECIO INVÁLIDO", "BLANCO",ancho_formato);
    anykey ();
    devolucion ("PRECIOS", "BLANCO",ancho_formato, alto_formato);
    titulo ("PRECIOS", "BLANCO",ancho_formato);
}

void CambiarPrecio (){
    //TODO: FUNCION DE PRECIOS

    int cod_art, pos;
    bool grabo ;
    char opcion;
    float valor ;
    articulo reg ;
    cls ();
    devolucion ("CAMBIAR PRECIO","BLANCO",ancho_formato,alto_formato);
    guiones (ancho_formato,7);
    titulo ("CAMBIAR PRECIO","BLANCO",ancho_formato);
    cout << endl ;

    msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
    pos = BuscarArticulo (cod_art);
    if (pos < 0){
        devolucion ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato);
        anykey ();
        return ;
    }
    reg = LeerArticulo (pos);
    msj ("Ingrese el nuevo monto: $", 2, ancho_formato) ; cin >> valor;
    while (valor <= 0){
        devolucion ("MONTO INCORRECTO","ROJO", ancho_formato, alto_formato);
        titulo ("MONTO INCORRECTO","ROJO", ancho_formato);
        anykey ();
        devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
        titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
        borrar_renglon (5);
        msj ("Ingrese el nuevo monto: $",2,ancho_formato) ; cin >> valor;
    }
    gotoxy(1,9);
    MostrarPrecioArticulo (reg);
    cout << endl ;
    guiones (ancho_formato);
    cout << endl << endl ;
    msj ("¿Está seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
        titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
        borrar_renglon (16);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    if (opcion=='s' || opcion=='S'){ //TODO: CHEQUEAR SI GRABA O NO
        reg.SetPrecio(valor);
        grabo = GuardarArticulo (reg,pos);
        if (grabo ==true){
            cls ();
            devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato)/2);
            MostrarPrecioArticulo (reg);
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato)/2);
        MostrarPrecioArticulo (reg);
    }
}


///-------------------------------------------------------------------------------


void MostrarListaPrecios (){
    articulo reg;
    int cant=CantArt(), x, cont=8;
    char texto[25];
    if (cant<0){
        devolucion ("OCURRIÓ UN ERROR", "ROJO", ancho_formato,alto_formato);
        titulo ("OCURRIÓ UN ERROR", "ROJO", ancho_formato);
        anykey ();
        return ;
    }

    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return ;
    }
    cls ();
    devolucion ("LISTA DE STOCK", "VERDE", ancho_formato,alto_formato);
    titulo ("LISTA DE STOCK", "VERDE", ancho_formato);
    gotoxy (12,6);
    cout << "        ARTÍCULO       | COD |  PRECIO" << endl ;
    gotoxy (12,7);
    cout << "-----------------------------------------" << endl ;
    for (x=0; x<cant ; x++){
        if (cont ==20){
            anykey ();
            cls ();
            cont = 8 ;
        }
        fread (&reg, sizeof(articulo),1,f);
        reg.GetNombre(texto);
        gotoxy (12,cont);
        cout << texto ;
        gotoxy (35,cont);
        cout << "| " << reg.GetCodArt() ;
        gotoxy (41,cont);
        cout << "|   $" << reg.GetPrecio ();
        gotoxy (54,cont);
        if (reg.GetEstado()==true){
            setBackgroundColor(GREEN);
        }
        else {
            setBackgroundColor(RED);
        }
        cout << "   " ;
        setBackgroundColor (BLACK);
        cont ++ ;
    }
    anykey ();
    fclose (f);
}

void MostrarPrecioArticulo (articulo reg){
    char texto [25];
    reg.GetNombre(texto);
    cout << "          Artículo: " << texto << " | COD: " << reg.GetCodArt() << " | Precio: $" << reg.GetPrecio () << endl ;
    anykey ();
}

float BuscarPrecio (int pos) {// Recibe posicion y devuelve precio del art
    articulo reg;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return -1 ; /// ERROR DE ARCHIVO
    }
    fseek (f, pos*sizeof(articulo), SEEK_SET);
    fread (&reg,sizeof (articulo),1,f);
    fclose (f);
    return reg.GetPrecio  ();
}

