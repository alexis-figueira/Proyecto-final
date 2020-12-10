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

int ObtenerIdCliente (){
    int id , pos_cli;
    srand (time(NULL));
    id = rand () %1000+1;
    pos_cli = BuscarCliente (id);
    while (pos_cli>=0){
        //srand (time(NULL));
        id = rand () %1000+1;
        pos_cli = BuscarCliente (id);
    }
    return id ;
}

void MenuVerCliente (){
    int id, pos ;
    clientes reg ;
    cls ();
    devolucion ("VER CLIENTE", "VERDE",ancho_formato,alto_formato);
    titulo ("VER CLIENTE","VERDE",ancho_formato);
    msj ("Ingrese número de cliente: ", 2,ancho_formato); cin >> id ;
    pos = BuscarCliente (id);
    if (pos==-2){
        devolucion ("NO SE ENCONTRÓ EL NÚMERO DE CLIENTE", "ROJO",ancho_formato,alto_formato);
        titulo ("NO SE ENCONTRÓ EL NÚMERO DE CLIENTE","ROJO",ancho_formato);
        anykey ();
        return ;
    }
    if (pos<0){
        devolucion ("OCURRIÓ UN ERROR", "ROJO",ancho_formato,alto_formato);
        titulo ("OCURRIÓ UN ERROR","ROJO",ancho_formato);
        anykey ();
        return ;
    }
    reg = LeerCliente (pos);
    MostrarCliente (reg);

}

bool GuardarClienteNuevo (clientes reg){///YA ESTA
    FILE *f;
    f=fopen(ArchivoClientes, "ab");
    if (f==NULL){
        return false;
    }
    fwrite (&reg,sizeof(clientes),1,f);
    fclose (f);
    return true ;
}

bool GuardarCliente (clientes reg, int pos){ /// YA ESTA
    FILE *f;
    f=fopen (ArchivoClientes,"rb+");
    if (f==NULL){
        return false ;
    }
    fseek (f, pos*sizeof(clientes) ,SEEK_SET);
    fwrite (&reg,sizeof(clientes),1,f);
    fclose (f);
    return true ;
}

int BuscarMail (char *mail){
    int pos=0, cant, x;
    char texto[50];
    clientes *reg;
    cant = CantClientes ();
    if (cant ==-1){
        return -1 ; /// error de lectura de archivos
    }

    reg = (clientes*) malloc (cant*sizeof(clientes));
    if (reg==NULL){
        free (reg);
        return -2; /// error con la memoria interna
    }

    FILE *f;
    f=fopen (ArchivoClientes, "rb") ;
    if (f==NULL){
        return -1 ; ///ERROR DE LECTURA
    }
    fread (reg,sizeof(clientes),cant,f);
    fclose (f);

    for (x=0 ; x<cant ; x++){
        reg[x].GetMail (texto);
        if (strcmp(mail, texto) == 0 ){
            pos = x ;
            free (reg);
            return pos ; /// DEVUELVE POSICION

        }

    }

    free(reg);
    return pos = - 2 ; /// DEVUELVE -2 SI NO LO ENCUENTRA
}

int BuscarCliente (int id){ /// YA ESTA
    int pos=0, cant, x;
    clientes *reg;
    cant = CantClientes ();
    if (cant ==-1){
        return -1 ; /// error de lectura de archivos
    }

    reg = (clientes*) malloc (cant*sizeof(clientes));
    if (reg==NULL){
        free (reg);
        return -2; /// error con la memoria interna
    }

    FILE *f;
    f=fopen (ArchivoClientes, "rb") ;
    if (f==NULL){
        return -1 ; ///ERROR DE LECTURA
    }
    fread (reg,sizeof(clientes),cant,f);
    fclose (f);

    for (x=0 ; x<cant ; x++){
        if (id==reg[x].GetId ()){
            pos = x ;
            free(reg);
            return pos ; /// DEVUELVE POSICION incluyendo 0
        }
    }

    free(reg);
    return pos = - 2 ; /// DEVUELVE -2 SI NO LO ENCUENTRA
}

int BuscarDni (int dni){ /// Recibe dni y devuelve posicion
    int pos=0, cant, x;
    clientes *reg;
    cant = CantClientes ();
    if (cant ==-1){
        return -1 ; /// error de lectura de archivos
    }
    reg = (clientes*) malloc (cant*sizeof(clientes));
    if (reg==NULL){
        free (reg);
        return -1; /// error con la memoria interna
    }
    FILE *f;
    f=fopen (ArchivoClientes, "rb") ;
    if (f==NULL){
        return -1 ; ///ERROR DE LECTURA
    }
    fread (reg,sizeof(clientes),cant,f);
    fclose (f);
    for (x=0 ; x<cant ; x++){
        if (dni==reg[x].GetDni ()){
            pos = x ;
            free(reg);
            return pos ; /// DEVUELVE POSICION incluyendo 0
        }
    }
    free(reg);
    return pos = - 2 ; /// DEVUELVE -2 SI NO LO ENCUENTRA
}

int CantClientes (){ /// YA ESTA
    int bts, cant;
    FILE *f;
    f=fopen (ArchivoClientes, "rb") ;
    if (f==NULL){
        return -1 ;
    }
    fseek (f,0,SEEK_END);
    bts=ftell (f);
    cant=bts /sizeof(clientes);
    return cant ;
}

void MostrarCliente (clientes reg){ /// FALTA HACER
    cls ();
    char texto [50];
    cls ();
    devolucion ("CLIENTE", "VERDE", ancho_formato, alto_formato) ;
    guiones (ancho_formato,9);
    titulo ("CLIENTE", "VERDE", ancho_formato) ;

    msj ("ID: ", 2,ancho_formato-3); cout << reg.GetId() << endl;
    reg.GetNombre (texto);
    msj ("Nombre: ", 2 ,ancho_formato-10) ; cout << texto << endl ;
    reg.GetApellido (texto);
    msj ("Apellido: ", 2 ,ancho_formato-10) ; cout << texto << endl ;
    reg.GetMail (texto);
    msj ("Mail: ", 2 ,ancho_formato-14) ; cout << texto << endl ;
    msj ("Dni: ", 2 ,ancho_formato-8) ; cout << reg.GetDni() << endl;
    msj ("Acumulado: ", 2 ,ancho_formato-8) ; cout << reg.GetAcumulado() << endl;

    hidecursor ();
    anykey ();
    showcursor ();
}

clientes ClientesMasVentas (){
    clientes cli (0), maxi (0);
    int cont=0;
    FILE *f ;
    f = fopen (ArchivoClientes, "rb");
    if (f==NULL){
        return maxi; /// maxi con acumulado e id = 0
    }

    while (fread(&cli,sizeof(clientes),1,f)==1){
        if (cont==0){
            maxi = cli ;
        }
        else {
            if (cli.GetAcumulado() > maxi.GetAcumulado ()){
                maxi = cli ;
            }
        }
        cont ++ ;
    }
    fclose (f);
    return maxi ; // devuelve cliente maximo
}

int ListarClientes (){
    int cant = CantClientes (),x=0, cont=0;
    clientes *vec  ;
    char texto[50] ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vec = (clientes*) malloc (cant*sizeof (clientes));
    if (vec ==NULL){
        free (vec);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }

    FILE*f ;
    f =fopen (ArchivoClientes, "rb");
    if (f==NULL){
        free (vec);
        return -1; /// ERROR DE LECTURA
    }

    fread (vec,sizeof (clientes), cant, f) ;
    fclose (f);

    cls ();
    devolucion ("LISTADO DE CLIENTES", "VERDE", ancho_formato, alto_formato) ;
    titulo ("LISTADO DE CLIENTES", "VERDE", ancho_formato) ;
    guiones (ancho_formato,19);
    gotoxy (1,x+7);
    msj (" ",2,ancho_formato,"AZUL");
    setBackgroundColor (BLUE);
    gotoxy (1,x+7);
    cout << " ID  |      Nombre      |     Apellido       |    DNI   |  Acumulado" << endl ;
    setBackgroundColor (BLACK);
    guiones(ancho_formato);

    for (x=0 ; x<cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE CLIENTES", "VERDE", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vec[x].GetEstado()==true) {
            gotoxy (2, cont+9);
            cout << vec[x].GetId ();
            gotoxy (6, cont+9);
            vec[x].GetNombre(texto);
            cout << "| " << texto;
            gotoxy (25, cont+9);
            vec[x].GetApellido (texto);
            cout << "| " << texto;
            gotoxy (46, cont+9) ;
            cout << "| " << vec[x].GetDni();
            gotoxy (57, cont+9);
            cout << "|   $" << vec[x].GetAcumulado ();
            cout << endl ;
            cont ++ ;
        }
    }
    anykey ();
    free (vec);
    return 0 ;
}

clientes LeerCliente (int pos){
    clientes reg;
    FILE*f ;
    f =fopen (ArchivoClientes, "rb");
    if (f==NULL){
        return reg ;
    }
    fseek (f,pos*sizeof(clientes),SEEK_SET);
    fread (&reg,sizeof (clientes), 1, f) ;
    fclose (f);
    return reg ;
}

///-------------------------------------------------------------------------------------------------------------------

clientes::clientes (){
}

clientes::clientes (int acu){
    acumulado = acu ;
    id_cliente = 0 ;
}

clientes::~clientes (){
}

void clientes::SetAcumulado (float valor){
    acumulado+=valor ;
}

float clientes::GetAcumulado (){
    return acumulado ;
}

void clientes::SetId (int id){
    id_cliente=id ;
}

int clientes::GetId (){
    return id_cliente;
}

void clientes::SetApellido (char* texto){
    strcpy (apellido, texto);
}

void clientes::GetApellido (char *texto){
    strcpy (texto, apellido);
}

void clientes::SetNombre (char*texto){
    strcpy (nombre, texto);
}

void clientes::GetNombre (char* texto){
    strcpy (texto,nombre);
}

void clientes::SetMail (char *texto){
    strcpy (mail, texto);
}

void clientes::GetMail (char* texto){
    strcpy (texto, mail);
}

void clientes::SetDni (int dn){
    dni = dn;
}

int clientes::GetDni (){
    return dni ;
}

void clientes::SetEstado (bool est){
    estado = est ;
}

bool clientes::GetEstado (){
    return estado ;
}


