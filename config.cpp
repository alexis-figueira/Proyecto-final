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

//const char *ArchivoVentas = "archivoventas.dat" ;
const char *VentasBkp = "archivoventas.bkp" ;
//const char *ArchivoStock = "archivostock.dat" ;
const char *StockBkp ="archivostock.bkp" ;
//const char *ArchivoPrecios = "archivoprecios.dat" ;
const char *PreciosBkp ="archivoprecios.bkp" ;
//const char *ArchivoClientes = "archivoclientes.dat" ;
const char *ClientesBkp = "archivoclientes.bkp" ;



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
    f=fopen ("archivoclientes.dat","rb");
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
    f=fopen ("archivoventas.dat","rb");
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

bool BkpStock (){
    stock reg ;
    FILE *f;
    f=fopen ("archivostock.dat","rb");
    if (f==NULL){
        return false ;
    }
    fread (&reg,sizeof (stock), 1, f) ;
    fclose (f);
    f= fopen (StockBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg,sizeof(clientes),1,f);
    fclose (f);
    return true ;
}

bool BkpPrecios (){
    precios reg ;
    FILE *f;
    f=fopen ("archivoprecios.dat","rb");
    if (f==NULL){
        return false ;
    }
    fread (&reg,sizeof (precios), 1, f) ;
    fclose (f);
    f= fopen (PreciosBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg,sizeof(precios),1,f);
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

    f= fopen ("archivoclientes.dat","wb");
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
    f= fopen ("archivoventas.dat","wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (vec,sizeof(ventas),cant,f);
    fclose (f);
    return true ;
}

bool RecuperarStock (){
     stock reg ;
    FILE *f;
    f=fopen (StockBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (&reg,sizeof (stock), 1, f) ;
    fclose (f);
    f= fopen ("archivostock.dat","wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg,sizeof(clientes),1,f);
    fclose (f);
    return true ;
}

bool RecuperarPrecios (){
    precios reg ;
    FILE *f;
    f=fopen (PreciosBkp,"rb");
    if (f==NULL){
        return false ;
    }
    fread (&reg,sizeof (precios), 1, f) ;
    fclose (f);
    f= fopen ("archivoprecios.dat","wb");
    if (f==NULL){
        return false ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg,sizeof(precios),1,f);
    fclose (f);
    return true ;
}

/// ---------------------------------------------------------------------///

bool BorrarClientes (){
    FILE *f;
    f= fopen ("archivoclientes.dat","wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarVentas (){
    FILE *f;
    f= fopen ("archivoventas.dat","wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarStock (){
    FILE *f;
    f= fopen ("archivostock.dat","wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarPrecios (){
    FILE *f;
    f= fopen ("archivoprecios.dat","wb");
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

bool BorrarBkpStock (){
    FILE *f;
    f= fopen (StockBkp,"wb");
    if (f==NULL){
        return false ;
    }
    fclose (f);
    return true ;
}

bool BorrarBkpPrecios (){
    FILE *f;
    f= fopen (PreciosBkp,"wb");
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

