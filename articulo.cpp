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
#include "ventas.h"
#include "stock.h"
#include "validaciones.h"

int CantArt (){ /// HECHA
    int bts, cant;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(articulo);
    return cant ;
}

int BuscarArticulo (int cod_art){ ///Recibe codigo y devuelve posicion
    int x, cant=CantArt () ;
    if (cant==-1){
        return -2; /// ERROR CON LA CANTIDAD DE ARTICULOS
    }
    if(cant==0){
        return -1; /// HAY 0 ARTICULOS
    }
    articulo *reg ;
    reg = (articulo*) malloc (cant*sizeof(articulo));
    if (reg==NULL){
        free (reg);
        return -2 ; ///ERROR DE MEMORIA INTERNA
    }
    FILE *f ;
    f = fopen (ArchivoArticulo,"rb");
    if (f==NULL){
        return -2 ;
    }
    fseek (f, 0, SEEK_SET);
    fread (reg,sizeof (articulo),cant,f);
    fclose (f);

    for (x=0; x<cant ;x++){
        if (reg[x].GetCodArt()==cod_art){
            free (reg);
            return x ; /// RETORNA LA POS DONDE ENCONTRO (INCLUYENDO 0)
        }
    }
    free (reg);
    return -1 ; /// NO ENCONTRO EL ARTICULO.
}

articulo LeerArticulo (int pos){ /// HECHA
    articulo reg;
    FILE*f ;
    f =fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return reg ;
    }
    fseek (f,pos*sizeof(articulo),SEEK_SET);
    fread (&reg,sizeof (articulo), 1, f) ;
    fclose (f);
    return reg ;
}

void ListarArticulo (articulo reg){ /// FALTA TERMINAR
    char texto [25];
    reg.GetNombre(texto);
    cout << "    Artículo: " << texto << " | COD: " << reg.GetCodArt() << " | STOCK: " << reg.GetStock () << " | PRECIO: $" << reg.GetPrecio ()<< " " ;
    if (reg.GetStock()>6){
        setBackgroundColor(GREEN);
    }
    else {
        if (reg.GetStock()>2){
            setBackgroundColor (YELLOW);
        }
        else {
            setBackgroundColor(RED);
        }
    }
    cout << "   "  ;
    setBackgroundColor(BLACK);
    cout << endl ;
    anykey ();
}

void CargarArticulo (){
    articulo reg;
    char texto [25], opc;
    int x,z ;
    float y ;
    bool grabo ;

    cls ();
    devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
    titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
    gotoxy (1,alto_formato-2);
    msj ("1.Andadores | 2.Camas | 3.Bastones | 4.Sillas | 5.Otros",2,ancho_formato);
    gotoxy (1,6);
    msj ("Tipo de art: ",2,ancho_formato);
    cin >> x ;
    while (x>6 || x<1){
        devolucion ("TIPO DE ARTÍCULO INCORRECTO", "ROJO",ancho_formato,alto_formato);
        titulo ("TIPO DE ARTÍCULO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (6);
        msj ("Tipo de art: ", 2, ancho_formato);
        cin >> x ;
    }
    reg.SetTipoArt (x);
    borrar_renglon (alto_formato-2);
    gotoxy (1,7);
    msj ("Nombre del Artículo: ",2, ancho_formato-9);
    cin.ignore ();
    cin.getline (texto, 25);
    x=ValidarTexto (texto);
    while (x==0){
        devolucion ("NOMBRE INVÁLIDO","ROJO",ancho_formato,alto_formato);
        titulo ("NOMBRE INVÁLIDO","ROJO",ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (7);
        msj ("Nombre del artículo: ", 2, ancho_formato-9) ;
        cin.getline(texto,25);
        x=ValidarTexto (texto);
    }
    reg.SetNombre(texto);

    msj ("Código del artículo: ",2,ancho_formato);
    cin >> x ;
    z=BuscarArticulo (x);
    while (z>=0){
        devolucion ("YA EXISTE EL CÓDIGO","ROJO",ancho_formato,alto_formato);
        titulo ("YA EXISTE EL CÓDIGO","ROJO",ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (8);
        msj ("Código del artículo: ", 2, ancho_formato) ;
        cin >> x ;
        z=BuscarArticulo (x);
    }
    reg.SetCodArt (x);

    msj ("Stock: ",2,ancho_formato);
    cin >>  x ;
    while (x<0){
        devolucion ("NO PUEDE TENER STOCK NEGATIVO","ROJO",ancho_formato,alto_formato);
        titulo ("NO PUEDE TENER STOCK NEGATIVO","ROJO",ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (9);
        msj ("Stock: ", 2, ancho_formato) ;
        cin >> x ;
    }
    reg.SetStock (x);

    msj ("Valor de venta: $",2,ancho_formato);
    cin >> y ;
    while (y<0){
        devolucion ("NO PUEDE TENER PRECIO NEGATIVO","ROJO",ancho_formato,alto_formato);
        titulo ("NO PUEDE TENER PRECIO NEGATIVO","ROJO",ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (10);
        msj ("Valor de venta: ", 2, ancho_formato) ;
        cin >> y ;
    }
    reg.SetPrecio (y);

    reg.SetEstado (true);

    cout << endl ;
    guiones (ancho_formato);
    guiones (ancho_formato,15);
    gotoxy (1,13);
    msj ("¿Está seguro de guardar el artículo?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato);
    cin >> opc ;
    while (opc!='s' && opc!='S' && opc!='n' && opc!='N'){
        devolucion ("CARÁCTER INVÁLIDO","ROJO", ancho_formato, alto_formato);
        titulo ("CARÁCTER INVÁLIDO","ROJO", ancho_formato);
        anykey ();
        devolucion ("CARGA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("CARGA DE ARTÍCULO","VERDE",ancho_formato);
        borrar_renglon (14);
        msj ("(S/N): ",2,ancho_formato);
        cin >> opc ;
    }
    if (opc =='s' || opc=='S'){
        grabo=GuardarArticulo (reg);
        if (grabo ==true){
            cls ();
            devolucion (" ", "VERDE",ancho_formato,alto_formato);
            titulo (" ","VERDE",ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("Artículo guardado con éxito",2,ancho_formato,"VERDE");
            anykey ();
        }
        else {
            cls ();
            devolucion (" ", "ROJO",ancho_formato,alto_formato);
            titulo (" ","ROJO",ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("Ocurrió un error al guardar",2,ancho_formato,"ROJO");
            anykey ();
        }
    }
    else {
        cls ();
        devolucion (" ", "VERDE",ancho_formato,alto_formato);
        titulo (" ","VERDE",ancho_formato);
        gotoxy (1,alto_formato/2);
        msj ("Artículo cancelado",2,ancho_formato);
        anykey ();
    }
}

bool GuardarArticulo (articulo reg){
    FILE *f;
    f=fopen(ArchivoArticulo, "ab");
    if (f==NULL){
        return false ;
    }
    fwrite (&reg, sizeof(articulo),1,f);
    fclose(f);
    return true ;
}

bool GuardarArticulo (articulo reg, int pos){
    FILE *f;
    f=fopen(ArchivoArticulo, "rb+");
    if (f==NULL){
        return false ;
    }
    fseek (f, pos*sizeof(articulo) ,SEEK_SET);
    fwrite (&reg, sizeof(articulo),1,f);
    fclose(f);
    return true ;
}

void MostrarListaArticulos (){
    articulo *art ;
    int cant_art=CantArt (), x, cont=8, aux;
    char texto [25];
    if (cant_art<0){
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
    devolucion ("LISTA DE ARTÍCULOS", "VERDE", ancho_formato,alto_formato);
    titulo ("LISTA DE ARTÍCULOS", "VERDE", ancho_formato);
    gotoxy (13,6);
    cout << "       ARTÍCULOS       | COD |  PRECIO  | STOCK  " << endl ;
    gotoxy (13,7);
    cout << "------------------------------------------------" << endl ;

    aux = art[0].GetTipoArt();
    gotoxy (1,cont);
    cout << "Andadores" ;

    for (x=0 ; x<cant_art ; x++){

        if (cont== 20){
            anykey ();
            borrar_restopantalla (8);
            cont=8;
        }

        if (aux!=art[x].GetTipoArt()){
            gotoxy (13,cont);
            cout << "------------------------------------------------" << endl ;
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
        gotoxy (13,cont);
        cout << texto ;
        gotoxy (36,cont);
        cout << "| " << art[x].GetCodArt() ;
        gotoxy (42,cont);
        cout << "| $" << art[x].GetPrecio ();
        gotoxy (53,cont);
        cout << "| " << art[x].GetStock ();
        gotoxy (62, cont);

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
        aux = art[x].GetTipoArt ();
    }
    gotoxy (13,cont);
    cout << "------------------------------------------------" << endl ;
    anykey ();

}

void MostrarUnArticulo (articulo reg){
    char texto [25];
    reg.GetNombre (texto);
    cls ();
    gotoxy (1,(alto_formato/2)-3);
    msj (" ",2,ancho_formato,"VERDE");    msj ("Articulo: ",2,ancho_formato-8); cout << texto << endl ;
    msj ("Código: ",2,ancho_formato); cout << reg.GetCodArt () << endl ;
    msj ("Precio: $", 2, ancho_formato); cout << reg.GetPrecio () << endl ;
    msj ("Stock: ", 2, ancho_formato); cout << reg.GetStock () << endl ;
    msj (" ",2,ancho_formato,"VERDE");
    anykey ();
}

bool BuscarEstadoArt (int pos){ /// Recibe posicion y devuelve estado
    articulo reg;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        return -1 ; /// ERROR DE ARCHIVO
    }
    fseek (f, pos*sizeof(articulo), SEEK_SET);
    fread (&reg,sizeof (articulo),1,f);
    fclose (f);
    return reg.GetEstado();

}

void BuscarNombre (int pos, char* texto) { /// Recibe posicion y devuelve nombre por *char
    articulo reg;
    FILE *f;
    f=fopen (ArchivoArticulo, "rb");
    if (f==NULL){
        reg.GetNombre (texto);
        return ; /// ERROR DE ARCHIVO
    }
    fseek (f, pos*sizeof(articulo), SEEK_SET);
    fread (&reg,sizeof (articulo),1,f);
    fclose (f);
    reg.GetNombre (texto);
}

void OrdenarAritculos (articulo* art,int tam){
    int x , y ;
    articulo aux ;
    for (x=0 ; x<tam ; x++){
        for(y=0 ; y<tam-1 ; y++){
            if (art[y].GetTipoArt()>= art[y+1].GetTipoArt()){
                aux = art[y];
                art[y] = art[y+1];
                art[y+1] = aux;

            }
            if (art[y].GetTipoArt()==art[y+1].GetTipoArt()){
                if (art[y].GetCodArt()>= art[y+1].GetCodArt()){
                    aux = art[y];
                    art[y] = art[y+1];
                    art[y+1] = aux;
                }
            }
        }
    }
}



///------------------------------------------------------------------------------------------------------------------------\\\

articulo::articulo (){
    cod = -1;
    stock = 0 ;
}

articulo::~articulo (){

}

int articulo::GetTipoArt (){
    return tipo_art ;
}

void articulo::SetTipoArt (int tipo){
    tipo_art= tipo ;
}

void articulo::GetNombre (char*texto){
    strcpy (texto, nombre);
}

void articulo::SetNombre (char*texto){
    strcpy (nombre, texto);
}

int articulo::GetCodArt (){
    return cod;
}

void articulo::SetCodArt (int cod_art){
    cod=cod_art ;
}

int articulo::GetStock (){
    return stock ;
}

void articulo::SetStock (int cant){
    stock += cant ;
}

float articulo::GetPrecio (){
    return precio;
}

void articulo::SetPrecio (float valor){
    precio=valor;
}

bool articulo::GetEstado (){
    return estado ;
}

void articulo::SetEstado (bool es){
    estado = es;
}

