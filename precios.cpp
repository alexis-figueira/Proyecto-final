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
    devolucion ("PRECIO INV�LIDO", "BLANCO",ancho_formato, alto_formato);
    titulo ("PRECIO INV�LIDO", "BLANCO",ancho_formato);
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

    msj ("Ingrese n�mero de art�culo: ", 2, ancho_formato) ; cin >> cod_art;
    pos = BuscarArticulo (cod_art);
    if (pos < 0){
        devolucion ("NO SE ENCONTR� EL ART�CULO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE ENCONTR� EL ART�CULO","ROJO",ancho_formato);
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
    msj ("�Est� seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CAR�CTER INV�LIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CAR�CTER INV�LIDO", "ROJO",ancho_formato);
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
            devolucion ("SE REALIZ� EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZ� EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato)/2);
            MostrarPrecioArticulo (reg);
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZ� EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZ� EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato)/2);
        MostrarPrecioArticulo (reg);
    }
}

///-------------------------------------------------------------------------------

void MostrarListaPrecios (){
    articulo *art;
    int cant_art=CantArt(), x, cont=8,aux;
    char texto[25];
    if (cant_art<0){
        devolucion ("OCURRI� UN ERROR", "ROJO", ancho_formato,alto_formato);
        titulo ("OCURRI� UN ERROR", "ROJO", ancho_formato);
        anykey ();
        return ;
    }
    art = (articulo*) malloc (cant_art*sizeof(articulo));
    if (art==NULL){
        free (art);
        return ;
    }

    FILE *f;
    f = fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        free (art);
        return ;
    }
    fread (art, sizeof(articulo),cant_art,f);
    fclose (f);

    OrdenarAritculos (art,cant_art);

    cls ();
    devolucion ("LISTA DE PRECIOS", "VERDE", ancho_formato,alto_formato);
    titulo ("LISTA DE PRECIOS", "VERDE", ancho_formato);
    gotoxy (15,6);
    cout << "        ART�CULO       | COD |  PRECIO" << endl ;
    gotoxy (15,7);
    cout << "-----------------------------------------" << endl ;

    aux = art[0].GetTipoArt();
    gotoxy (1,cont);
    cout << "Andadores" ;

    for (x=0; x<cant_art ; x++){

        if (cont ==20){
            anykey ();
            borrar_restopantalla(8);
            cont = 8 ;
        }

        if (aux!=art[x].GetTipoArt()){
            gotoxy (15,cont);
            cout << "-----------------------------------------" << endl ;
            cont ++ ;
            gotoxy (1,cont);
            switch (art[x].GetTipoArt()){
            case 2 : cout << "Camas" ;
                break;
            case 3: cout << "Bastones" ;
                break;
            case 4 : cout << "Sillas" ;
                break ;
            case 5 : cout << "Otros";
                break ;
            }
        }



        art[x].GetNombre(texto);
        gotoxy (15,cont);
        cout << texto ;
        gotoxy (38,cont);
        cout << "| " << art[x].GetCodArt() ;
        gotoxy (44,cont);
        cout << "|   $" << art[x].GetPrecio ();
        gotoxy (57,cont);

        if (art[x].GetStock()>6){
            setBackgroundColor(GREEN);
        }
        else {
            if (art[x].GetStock()>2){
                setBackgroundColor (YELLOW);
            }
            else {
                setBackgroundColor(RED);
            }
        }
        cout << "   " ;
        setBackgroundColor (BLACK);
        cont ++ ;
        aux = art[x].GetTipoArt();
    }
    gotoxy (15,cont);
    cout << "-----------------------------------------" << endl ;
    anykey ();
}

void MostrarPrecioArticulo (articulo reg){
    char texto [25];
    reg.GetNombre(texto);
    cout << "          Art�culo: " << texto << " | COD: " << reg.GetCodArt() << " | Precio: $" << reg.GetPrecio () << endl ;
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

