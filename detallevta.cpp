#include <iostream>
#include <cstdlib>
using namespace std;
#include "rlutil.h"
using namespace rlutil ;
#include "interfaz.h"
#include "clases.h"
#include "ventas.h"
#include "detallevta.h"

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

int LeerDetalle (int num_vta, detalle *dle){ // esta
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
            dle[cant]=reg ;
            cant ++ ;
        }
    }
    return cant ; /// 0 no encontro venta, <0 error y >0 cantidad
    fclose (f);
}

detalle LeerUnDetalle (int vta,int det){
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

void MostrarUnDetalle (detalle dle){ /// falta hacer
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

void MostrarDetalleVenta (detalle* dle){ /// falta hacer

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

