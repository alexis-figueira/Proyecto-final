#include <iostream>
#include <cstdlib>
using namespace std ;
#include "rlutil.h"
using namespace rlutil;
#include "clases.h"
#include "stock.h"
#include "interfaz.h"
#include "articulo.h"
/// INTERFAZ VERDE



void MenuAgregarStock (){
    int cod_art, cantidad, pos;
    bool grabo;
    char opcion;
    articulo reg ;
    cls ();
    devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,7);
    titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
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
    msj ("Ingrese cantidad a aumentar: ", 2, ancho_formato) ; cin >> cantidad;
    while (cantidad <= 0){
        devolucion ("SE DEBE AUMENTAR AL MENOS 1","ROJO",ancho_formato,alto_formato);
        titulo ("SE DEBE AUMENTAR AL MENOS 1","ROJO",ancho_formato);
        anykey ();
        devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
        borrar_renglon (5);
        msj ("Ingrese cantidad a aumentar: ", 2, ancho_formato) ;
        cin >> cantidad ;
    }

    gotoxy (1,10);
    MostrarStockArticulo (pos);
    cout << endl << endl ;
    cout << endl ;
    guiones (ancho_formato);
    guiones (ancho_formato,17);
    gotoxy (1,15);

    msj ("¿Está seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
        borrar_renglon (16);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    if (opcion=='s' || opcion=='S'){ //TODO: CHEQUEAR SI GRABA O NO
        reg.SetStock (cantidad);
        grabo = GuardarArticulo (reg,pos);
        if (grabo ==true){
            cls ();
            devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato-4)/2);
            MostrarStockArticulo (pos);
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato-4)/2);
        MostrarStockArticulo (pos);
    }
}

void MenuReducirStock (){
    int cod_art, cantidad, pos, stock_actual;
    bool grabo ;
    char opcion;
    articulo reg;
    cls ();
    devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,7);
    titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
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
    stock_actual = reg.GetStock ();
    msj ("Ingrese cantidad a reducir: ", 2, ancho_formato) ; cin >> cantidad;
    while (cantidad <= 0 || cantidad > stock_actual){
        if (cantidad <= 0){
            devolucion ("SE DEBE REDUCIR AL MENOS 1","ROJO",ancho_formato,alto_formato);
            titulo ("SE DEBE REDUCIR AL MENOS 1","ROJO",ancho_formato);
        }else {
            devolucion ("EL STOCK ES MENOR AL DE LA CANTIDAD A REDUCIR","ROJO",ancho_formato,alto_formato);
            titulo ("EL STOCK ES MENOR AL DE LA CANTIDAD A REDUCIR","ROJO",ancho_formato);
        }
        anykey ();
        devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
        borrar_renglon (5);
        msj ("Ingrese cantidad a reducir: ", 2, ancho_formato) ;
        cin >> cantidad ;
    }
    gotoxy (1,10);
    MostrarStockArticulo (pos);
    cout << endl << endl ;
    cout << endl ;
    guiones (ancho_formato);
    guiones (ancho_formato,17);
    gotoxy (1,15);
    msj ("¿Está seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
        borrar_renglon (16);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    if (opcion=='s' || opcion=='S'){
        reg.SetStock (cantidad *-1);
        grabo = GuardarArticulo (reg,pos);
        if (grabo ==true){
            cls ();
            devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato-4)/2);
            MostrarStockArticulo (pos);
        }else{
            cls ();
            devolucion (" ","ROJO",ancho_formato,alto_formato);
            titulo (" ","ROJO",ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("Ocurrio un error",2,ancho_formato,"ROJO");
            anykey ();
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato-4)/2);
        MostrarStockArticulo (pos);
    }
}

void StockInvalido (){ ///LISTO a revisar
    devolucion ("STOCK INVÁLIDO", "ROJO",ancho_formato, alto_formato);
    titulo ("STOCK INVÁLIDO", "ROJO",ancho_formato);
    anykey ();
    devolucion ("STOCK", "VERDE",ancho_formato, alto_formato);
    titulo ("STOCK", "VERDE",ancho_formato);
}

void MostrarListaStock (){ ///LISTO a revisar
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
    gotoxy (15,6);
    cout << "        ARTÍCULO       | COD | STOCK" << endl ;
    gotoxy (15,7);
    cout << "---------------------------------------" << endl ;
    for (x=0; x<cant ; x++){
        if (cont ==20){
            anykey ();
            borrar_restopantalla (9);
            cont = 8 ;
        }
        fread (&reg, sizeof(articulo),1,f);
        reg.GetNombre(texto);
        gotoxy (15,cont);
        cout << texto ;
        gotoxy (38,cont);
        cout << "| " << reg.GetCodArt() ;
        gotoxy (44,cont);
        cout << "|   " << reg.GetStock ();
        gotoxy (55,cont);
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

void MostrarStockArticulo (int pos){ /// LISTO a revisar
    char texto [25];
    articulo reg;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return ;
    }
    fseek (f,pos*sizeof(articulo),SEEK_SET);
    fread (&reg, sizeof(articulo),1,f);
    fclose (f);
    reg.GetNombre(texto);
    cout << "\t\tArtículo: " << texto << " | COD: " << reg.GetCodArt() << " | STOCK: " << reg.GetStock () << endl ;
    anykey ();
}

int BuscarStock (int pos){ /// LISTO a revisar
    articulo reg;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return -1 ; /// ERROR DE ARCHIVO
    }
    fseek (f, pos*sizeof(articulo), SEEK_SET);
    fread (&reg,sizeof (articulo),1,f);
    fclose (f);
    return reg.GetStock();
}
