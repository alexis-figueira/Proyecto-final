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
#include "clientes.h"
#include "ventas.h"
#include "precios.h"
#include "config.h"
#include "stock.h"



bool BkpClientes (){
    clientes *vec;
    int cant = CantClientes();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (clientes*) malloc (cant*sizeof (clientes));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ArchivoClientes,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (clientes), cant, f) ;
    fclose (f);
    f= fopen (ClientesBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(clientes),cant,f);
    fclose (f);
    return true ;
}

bool BkpVentas (){
    ventas *vec;
    int cant = CantVentas ();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ArchivoVentas,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);
    f= fopen (VentasBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(ventas),cant,f);
    fclose (f);
    return true ;
}


/// ---------------------------------------------------------------------///


bool RecuperarClientes (){
    clientes *vec;
    int cant = CantClientesBkp ();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (clientes*) malloc (cant*sizeof (clientes));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ClientesBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (clientes), cant, f) ;
    fclose (f);

    f= fopen (ArchivoClientes,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(clientes),cant,f);
    fclose (f);
    return true ;

}

bool RecuperarVentas (){
     ventas *vec;
    int cant = CantVentasBkp ();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (VentasBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);
    f= fopen (ArchivoVentas,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(ventas),cant,f);
    fclose (f);
    return true ;
}


/// ---------------------------------------------------------------------///


bool BorrarClientes (){
    FILE *f;
    f= fopen (ArchivoClientes,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarVentas (){
    FILE *f;
    f= fopen (ArchivoVentas,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarBkpClientes (){
    FILE *f;
    f= fopen (ClientesBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarBkpVentas (){
    FILE *f;
    f= fopen (VentasBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}


/// ---------------------------------------------------------------------///

int CantClientesBkp (){ /// YA ESTA
    int bts, cant;
    FILE *f;
    f=fopen (ClientesBkp, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(clientes);
    return cant ;
}

int CantVentasBkp (){
    int bts, cant;
    FILE *f;
    f=fopen (VentasBkp, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(clientes);
    return cant ;
}

