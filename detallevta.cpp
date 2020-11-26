#include <iostream>
#include <cstdlib>
using namespace std;
#include "rlutil.h"
using namespace rlutil ;
#include "interfaz.h"
#include "clases.h"
#include "ventas.h"
#include "detallevta.h"
#include "articulo.h"

bool GuardarDetalle (detalle dle){
    FILE *f ;
    f = fopen (ArchivoDetalle, "ab");
    if (f==NULL){
        return false ;
    }
    fwrite (&dle,sizeof (detalle),1,f);
    fclose (f);
    return true ;
}

bool GuardarDetalle (detalle dle, int pos){
    FILE *f ;
    f = fopen (ArchivoDetalle, "rb+");
    if (f==NULL){
        return false ;
    }
    fseek (f,pos*sizeof(detalle),SEEK_SET);
    fwrite (&dle,sizeof (detalle),1,f);
    fclose (f);
    return true ;
}

int CantDetalle (){
    int bts, cant;
    FILE *f ;
    f= fopen (ArchivoDetalle,"rb");
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts = ftell (f);
    cant = bts / sizeof(detalle);
    return cant ;
}

/*
int BuscarDetalle (int vta, int det){
    detalle dle () ;
    int pos, cant=CantDetalle () ,x , nvta , ndet;
    if (cant==-1){
        return -2 ; /// ERROR CON LA CANT
    }
    FILE *f ;
    f= fopen (ArchivoDetalle,"rb");
    if ( f==NULL){
        return -3 ;/// ERROR CON ARCHIVO
    }
    for (x=0 ; x<cant ; x++){
        fread(&dle,sizeof (detalle),1,f);
        nvta = dle.GetNumVenta ();
        ndet = dle.GetNumDetalle ();
        if (nvta == vta && ndet == det){
            fclose (f);
            return x ; /// X=POS, incluye la pos 0
        }
    }
    fclose (f);
    return -1 ; /// No se encontro el detalle.
}
*/

int LeerTodoDetalle (int num_vta, detalle *dle){ // devuelve cant de detalles, y un vector del detalle
    detalle reg (0);
    int cant=CantDetalle (),x, cont=0;
    if (cant == -1){
        return -1 ; // ERROR CON CANTIDAD DETALLE
    }
    FILE*f ;
    f = fopen (ArchivoDetalle,"rb");
    if ( f== NULL){
        return -1 ; /// ERROR CON ARCHIVO
    }
    for (x=0 ; x<cant ; x++){
        fread(&reg,sizeof (detalle),1,f);
        if (reg.GetNumVenta()==num_vta){
            dle[cont]=reg ;
            cont ++ ;
        }
    }
    return cont ; /// 0 no encontro venta // <0 error  // >0 cantidad del detalle
    fclose (f);
}

detalle LeerUnDetalle (int vta,int det){ //recibe #venta y #detalle y devuelve el detalle.
    detalle dle (0) ;
    int pos, cant=CantDetalle () ,x , nvta , ndet;
    if (cant==-1){
        return dle ; /// ERROR CON LA CANT
    }
    FILE *f ;
    f= fopen (ArchivoDetalle,"rb");
    if ( f==NULL){
        return dle ;/// ERROR CON ARCHIVO
    }
    for (x=0 ; x<cant ; x++){
        fread (&dle,sizeof(detalle),1,f);
        nvta = dle.GetNumVenta ();
        ndet = dle.GetNumDetalle ();
        if (nvta == vta && ndet == det){
            fclose (f);
            return dle; /// X=POS, incluye la pos 0
        }
    }
    fclose (f);
    return dle ; /// No se encontro el detalle.

}

void MostrarUnDetalle (detalle dle){ /// falta cambiar formato
    detalle reg (0);
    reg.SetNumVenta (15);
    reg.SetNumDetalle (1);
    reg.SetCodArt (220);
    reg.SetCantVenta (2);
    reg.SetValorDetalle (25000);
    reg.SetEstado (true);
    cout << "numero de venta: " << dle.GetNumVenta () << endl ;
    cout << "Numero de detalle: " << dle.GetNumDetalle () << endl ;
    cout << "Numero de codigo: " << dle.GetCodArt () << endl ;
    cout << "Catidad vendida : " << dle.GetCantVenta () << endl ;
    cout << "Valor del detalle: " << dle.GetValorDetalle () << endl ;
    cout << "Estado: " << dle.GetEstado () << endl ;
    anykey ();
}

void MostrarDetalleVenta (int cant, detalle* dle,ventas vta){ /// falta hacer
    articulo art ;
    int pos_art,x;
    char texto [25];
    cls();
    devolucion ("DETALLE DE VENTA","MAGENTA",ancho_formato,alto_formato);
    titulo ("DETALLE DE VENTA", "MAGENTA",ancho_formato);
    gotoxy(1,7);
    msj ("VENTA ",2,ancho_formato-10,"VERDE");
    gotoxy (38,7);
    setBackgroundColor(GREEN);
    cout << dle[0].GetNumVenta() << endl ;
    setBackgroundColor (BLACK);
    gotoxy (1,11);
    vta.MostrarFechaVenta ();
    gotoxy (1,9);
    cout << "FECHA          Cod           Descripción          Cant  Monto  " << endl ;
    guiones (ancho_formato);
    for (x=0 ; x<cant ; x++){
        pos_art = BuscarArticulo (dle[x].GetCodArt()) ;
        art = LeerArticulo (pos_art);
        gotoxy (14,x+11);
        cout << "| " << dle[x].GetCodArt ();
        gotoxy (20,x+11);
        art.GetNombre (texto);
        cout << "| " << texto ;
        gotoxy (50,x+11);
        cout << "| " << dle[x].GetCantVenta();
        gotoxy (55,x+11);
        cout << "| $" << dle[x].GetValorDetalle () << endl;
    }
    guiones(ancho_formato);
    gotoxy (22,x+12);
    cout << "Total" ;
    gotoxy (57, x+12);
    cout << "$" <<vta.GetValorVenta ();

    hidecursor ();
    anykey ();
    showcursor();
}


void ListarDetalleVenta (int id_venta){
}


detalle::detalle (){
}

detalle::detalle (int x){
    num_venta = 0 ;
    num_detalle = 0 ;
}

detalle::~detalle (){
}

int detalle::GetNumVenta (){
    return num_venta ;
}
void detalle::SetNumVenta (int valor){
    num_venta = valor ;
}

int detalle::GetNumDetalle (){
    return num_detalle ;
}
void detalle::SetNumDetalle (int valor){
    num_detalle = valor ;
}

int detalle::GetCodArt (){
    return cod_art;
}
void detalle::SetCodArt (int valor){
    cod_art = valor ;
}

int detalle::GetCantVenta (){
    return cant_venta ;
}
void detalle::SetCantVenta (int valor){
    cant_venta = valor ;
}

float detalle::GetValorDetalle (){
    return valor_detalle ;
}
void detalle::SetValorDetalle (float valor){
    valor_detalle = valor ;
}

bool detalle::GetEstado (){
    return estado ;
}
void detalle::SetEstado (bool es){
    estado = es ;
}

