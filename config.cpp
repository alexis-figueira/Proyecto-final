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
#include "config.h"
#include "stock.h"
#include "detallevta.h"
#include "articulo.h"

bool BkpDetalle (){
    detalle *vec;
    int cant = CantDetalle();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (detalle*) malloc (cant*sizeof (detalle));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ArchivoDetalle,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (detalle), cant, f) ;
    fclose (f);
    f= fopen (DetallesBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(detalle),cant,f);
    fclose (f);
    return true ;
}

bool BkpArticulo (){
    articulo *vec;
    int cant = CantArt();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (articulo*) malloc (cant*sizeof (articulo));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ArchivoArticulo,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (articulo), cant, f) ;
    fclose (f);
    f= fopen (ArticulosBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(articulo),cant,f);
    fclose (f);
    return true ;
}

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

bool RecuperarDetalle (){
    detalle *vec;
    int cant = CantDetallesBkp ();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (detalle*) malloc (cant*sizeof (detalle));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (DetallesBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (detalle), cant, f) ;
    fclose (f);
    f= fopen (ArchivoDetalle,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(detalle),cant,f);
    fclose (f);
    return true ;
}

bool RecuperarArticulo (){
    articulo *vec;
    int cant = CantArticuloBkp ();
    if (cant ==-1){
        return false ; /// error de lectura de archivos
    }
    vec = (articulo*) malloc (cant*sizeof (articulo));
    if (vec==NULL){
        free(vec);
        return false ;
    }
    FILE *f;
    f=fopen (ArticulosBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (vec,sizeof (articulo), cant, f) ;
    fclose (f);
    f= fopen (ArchivoArticulo,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(articulo),cant,f);
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

bool BorrarArticulo (){
    FILE *f;
    f= fopen (ArchivoArticulo,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarDetalle (){
    FILE *f;
    f= fopen (ArchivoDetalle,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

/// ---------------------------------------------------------------------///

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

bool BorrarBkpArticulo (){
    FILE *f;
    f= fopen (ArticulosBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarBkpDetalle (){
    FILE *f;
    f= fopen (DetallesBkp,"wb");
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
    cant=bts /sizeof(ventas);
    return cant ;
}

int CantDetallesBkp (){
    int bts, cant;
    FILE *f;
    f=fopen (DetallesBkp, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(detalle);
    return cant ;
}

int CantArticuloBkp (){
    int bts, cant;
    FILE *f;
    f=fopen (ArticulosBkp, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(articulo);
    return cant ;
}
