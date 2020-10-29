#include <iostream>
#include <cstdlib>
using namespace std;
#include "rlutil.h"
using namespace rlutil ;
#include "interfaz.h"
#include "clases.h"
#include "validaciones.h"
#include "ventas.h"
#include "clientes.h"
#include "stock.h"
///INTERFAZ MAGENTA
const char *ArchivoVentas = "archivoventas.dat" ;



bool GuardarVenta (ventas vta){
    FILE *f ;
    f = fopen (ArchivoVentas , "ab") ;
    if (f==NULL){
        return false ;
    }
    fwrite (&vta, sizeof (ventas),1, f);
    fclose (f);
    return true ;
}

bool GuardarVenta (ventas vta,int pos){
    FILE *f ;
    f = fopen (ArchivoVentas , "rb+") ;
    if (f==NULL){
        return false ;
    }
    fseek (f, pos*sizeof(ventas),SEEK_SET);
    fwrite (&vta, sizeof (ventas),1, f);
    fclose (f);
    return true ;
}

int CantVentas (){
    int bts, cant ;
    FILE *f ;
    f=fopen (ArchivoVentas, "rb");
    if (f==NULL){
        return -1 ;
    }
    fseek(f, 0,SEEK_END);
    bts=ftell (f);
    cant=bts/sizeof(ventas);
    fclose (f);
    return cant ;
}

int BuscarVenta (int num){ /// Por id venta
    int pos, cant ;
    cant= CantVentas ();
    if (cant==-1){
        return -1 ; /// ERROR DE LECTURA
    }
    ventas reg ;
    FILE *f;
    f = fopen (ArchivoVentas, "rb");
    if (f==NULL){
        return -1 ; /// ERROR DE LECTURA
    }
    for (pos=0 ; pos<cant ; pos++){
        fread (&reg, sizeof (ventas),1,f);
        if (reg.GetNumVenta() ==num){
            fclose (f);
            return pos ; /// Se encontro y devuelve posicion
        }
    }
    fclose (f);
    return -2 ; ///No se encontro el registro
}

ventas LeerVenta (int pos) {
    ventas reg;
    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        return reg ;
    }
    fseek (f,pos*sizeof(ventas),SEEK_SET);
    fread (&reg,sizeof (ventas), 1, f) ;
    fclose (f);
    return reg ;
}

void MostrarVenta (ventas reg){
    cls ();
    devolucion ("VENTA", "MAGENTA", ancho_formato, alto_formato);
    guiones (ancho_formato,13);
    titulo ("VENTA", "MAGENTA", ancho_formato);
    gotoxy ((ancho_formato-65656)/2,3);
    reg.MostrarFechaVenta () ;cout << endl ;
    msj ("Num. venta: ", 2, ancho_formato) ; cout << reg.GetNumVenta () << endl ;
    msj ("ID cliente: ", 2, ancho_formato) ; cout << reg.GetIdCliente () << endl ;
    msj ("Nombre: ", 2, ancho_formato-10) ; reg.MostrarNombre (); cout << endl ;
    msj ("Apellido: ", 2, ancho_formato-10) ; reg.MostrarApellido () ; cout << endl ;
    msj ("DNI: ", 2, ancho_formato-5) ; cout << reg.GetDni () << endl ;
    msj ("Mail: ", 2, ancho_formato-15) ; reg.MostrarMail () ; cout << endl ;
    msj ("Cod. artículo: ", 2, ancho_formato) ; cout << reg.GetCodArt () << endl ;
    msj ("Cantidad: ", 2, ancho_formato) ; cout << reg.GetCant () << endl ;

    msj ("Monto: $", 2, ancho_formato-5) ; cout << reg.GetValorVenta () << endl ;
    gotoxy (ancho_formato-3,alto_formato-2);
    if (reg.GetEstado()==true){
        setBackgroundColor(GREEN);
        cout << "    " ;
    }else{
        setBackgroundColor (RED);
        cout << "    " ;
    }
    setBackgroundColor(BLACK);
    hidecursor ();
    anykey ();
    showcursor ();
}

int ListarVentas (){ /// falta hacer
    int cant = CantVentas (),x=0, cont=0;
    ventas *vec  ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec ==NULL){
        free (vec);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }


    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vec);
        return -1 ; /// ERROR DE LECTURA
    }

    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);
    cls ();
    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
    titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
    guiones (ancho_formato,19);
    gotoxy (1,x+6);
    guiones (ancho_formato);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vec[x].GetEstado()==true) {
            gotoxy (1, cont+9);
            cout << "  " ; vec[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vec[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cout << "| " ; vec[x].MostrarApellido() ;
            gotoxy (41,cont+9);
            cout << "| " << vec[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vec[x].GetCant () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vec[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vec[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    anykey ();
    free (vec);
    return 0 ; /// Todo ok
}

int ListarClientesPorId (int id){
    int cant = CantVentas (),x=0, cont=0;
    ventas *vec  ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec ==NULL){
        free (vec);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }


    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vec);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);

    cls ();
    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
    titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
    guiones (ancho_formato,19);
    gotoxy (1,x+6);
    guiones (ancho_formato);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vec[x].GetEstado()==true && vec[x].GetIdCliente()==id) {
            gotoxy (1, cont+9);
            cout << "  " ; vec[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vec[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cout << "| " ; vec[x].MostrarApellido() ;
            gotoxy (41,cont+9);
            cout << "| " << vec[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vec[x].GetCant () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vec[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vec[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    anykey ();
    free (vec);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}

int ListarClientesPorDni (int dni){
    int cant = CantVentas (),x=0, cont=0;
    ventas *vec  ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec ==NULL){
        free (vec);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }


    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vec);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);

    cls ();
    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
    titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
    guiones (ancho_formato,19);
    gotoxy (1,x+6);
    guiones (ancho_formato);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vec[x].GetEstado()==true && vec[x].GetDni()==dni) {
            gotoxy (1, cont+9);
            cout << "  " ; vec[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vec[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cout << "| " ; vec[x].MostrarApellido() ;
            gotoxy (41,cont+9);
            cout << "| " << vec[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vec[x].GetCant () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vec[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vec[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    anykey ();
    free (vec);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}

int ListarClientesPorMail (char *mail){
    int cant = CantVentas (),x=0, cont=0, comp;
    ventas *vec  ;
    char texto[50] ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vec = (ventas*) malloc (cant*sizeof (ventas));
    if (vec ==NULL){
        free (vec);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }


    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vec);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vec,sizeof (ventas), cant, f) ;
    fclose (f);

    cls ();
    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
    titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
    guiones (ancho_formato,19);
    gotoxy (1,x+6);
    guiones (ancho_formato);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        vec[x].GetMail (texto);
        comp = strcmp(mail, texto);
        if (vec[x].GetEstado()==true && comp==0) {
            gotoxy (1, cont+9);
            cout << "  " ; vec[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vec[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cout << "| " ; vec[x].MostrarApellido() ;
            gotoxy (41,cont+9);
            cout << "| " << vec[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vec[x].GetCant () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vec[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vec[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    anykey ();
    free (vec);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}


///---------------------------------------------------------------------------------------------------------------------///

bool ventas::SetNuevaVenta (){
    /// VALIDACIONES VENTA--------------------

    int x , pos, cant_stock;
    cls ();
    devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
    guiones (ancho_formato,13);
    titulo ("NUEVA VENTA","MAGENTA",ancho_formato);

    MostrarFecha (2,ancho_formato); cout << endl ;
    fec_compra = CargarFechaActual ();

    msj ("Num. venta: ", 2, ancho_formato) ; cout << CantVentas ()+1 << endl ;
    num_venta = CantVentas ()+1 ;

    msj ("ID cliente: ", 2, ancho_formato) ;
    cin >> x ;
    while (x<=0){ ///Validacion ID cliente
        devolucion ("EL ID DEBE SER POSITIVO", "ROJO",ancho_formato,alto_formato);
        titulo ("EL ID DEBE SER POSITIVO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
        titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
        borrar_renglon (5);
        msj ("ID cliente: ", 2, ancho_formato) ;
        cin >> x ;
    }


    /// FUNCION BUSCAR CLIENTE Y HACER IF PARA QUE SE COMPLETE SOLO LOS DATOS.
    id_cliente = x ;

    pos=BuscarCliente (x);
    if (pos>=0){
        char texto [50];
        clientes cli;
        cli=LeerCliente (pos);

        cli.GetNombre (texto);
        strcpy (nombre,texto);
        msj ("Nombre: ",2,ancho_formato-10); cout << texto << endl ;

        cli.GetApellido (texto);
        strcpy (apellido,texto);
        msj ("Apellido: ",2,ancho_formato-10); cout << texto << endl ;

        msj ("DNI: ", 2, ancho_formato-5); cout << cli.GetDni () << endl ;
        dni=cli.GetDni ();

        cli.GetMail (texto);
        strcpy (mail,texto);
        msj ("Mail: ",2,ancho_formato-15); cout << texto << endl ;
    }else {
        if (pos==-2){
            msj ("Nombre: ", 2, ancho_formato-10) ;
            cin.ignore ();
            cin.getline(nombre,50);
            x=ValidarTexto (nombre);
            while (x==0){
                devolucion ("NOMBRE INCORRECTO ","ROJO",ancho_formato,alto_formato);
                titulo ("NOMBRE INCORRECTO","ROJO",ancho_formato);
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (6);
                msj ("Nombre: ", 2, ancho_formato-10) ;
                cin.getline(nombre,50);
                x=ValidarTexto (nombre);
            }

            msj ("Apellido: ", 2, ancho_formato-10) ;
            cin.getline (apellido, 50);
            x=ValidarTexto (apellido);
            while (x==0){
                devolucion ("APELLIDO INCORRECTO ","ROJO",ancho_formato,alto_formato);
                titulo ("APELLIDO INCORRECTO","ROJO",ancho_formato);
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (7);
                msj ("Apellido: ", 2, ancho_formato-10) ;
                cin.getline(apellido,50);
                x=ValidarTexto (apellido);
            }

            msj ("DNI: ", 2, ancho_formato-5) ;
            cin >> x ;
            pos = BuscarDni (x);
            while (x<3000000 || x>100000000 || pos>=0){
                if (pos>=0){
                    devolucion ("EL DNI SE ENCUENTRA REGISTRADO","ROJO",ancho_formato,alto_formato);
                    titulo ("EL DNI SE ENCUENTRA REGISTRADO","ROJO",ancho_formato);
                }
                else {
                    devolucion ("DNI INCORRECTO","ROJO",ancho_formato,alto_formato);
                    titulo ("DNI INCORRECTO","ROJO",ancho_formato);
                }
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (8);
                msj ("DNI: ", 2, ancho_formato-5) ;
                cin >> x ;
                pos=BuscarDni (x);
            }
            dni = x ;

            msj ("Mail: ", 2, ancho_formato-15) ;
            cin.ignore ();
            cin.getline (mail, 50);
            x=ValidarMail (mail);
            pos = BuscarMail (mail);
            while (x==0 || pos>=0){
                if (pos>=0){
                    devolucion ("YA HAY UN CLIENTE CON ESE MAIL","ROJO",ancho_formato,alto_formato);
                    titulo ("YA HAY UN CLIENTE CON ESE MAIL","ROJO",ancho_formato);
                }
                else {
                    devolucion ("MAIL INCORRECTO ","ROJO",ancho_formato,alto_formato);
                    titulo ("MAIL INCORRECTO","ROJO",ancho_formato);
                }
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (9);
                msj ("Mail: ", 2, ancho_formato-15) ;
                cin.getline(mail,50);
                x=ValidarMail (mail);
            }
        }
        else {
            cls ();
            cout << "error" ;
            anykey ();
        }
    }

    msj ("Cod. artículo: ", 2, ancho_formato) ;
    cin >> x ;
    while (x!=100 && x!=110 && x!=120 && x!=200 && x!=210 && x!=220 && x!=300 && x!=310 && x!=320 && x!=400 &&x!=410 && x!=420){
        devolucion ("CÓDIGO INCORRECTO","ROJO",ancho_formato,alto_formato);
        titulo ("CÓDIGO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
        titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
        borrar_renglon (10);
        msj ("Cod. artículo: ", 2, ancho_formato) ;
        cin >> x ;
    }
    cod_art = x ;

    msj ("Cantidad: ", 2, ancho_formato) ;
    cin >> x ;
    cant_stock = BuscarStock (cod_art);
    while (x<=0 || cant_stock<x){
        if (x<=0){
        devolucion ("DEBE COMPRAR AL MENOS 1","ROJO",ancho_formato,alto_formato);
        titulo ("DEBE COMPRAR AL MENOS 1","ROJO",ancho_formato);
        anykey ();
        devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
        titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
        borrar_renglon (11);
        msj ("Cantidad: ", 2, ancho_formato) ;
        cin >> x ;
        }

        else{
            char opcion ;
            devolucion ("NO HAY STOCK SUFICIENTE","ROJO",ancho_formato,alto_formato);
            titulo ("NO HAY STOCK SUFICIENTE","ROJO",ancho_formato);
            gotoxy (1,alto_formato-10);
            MostrarStockArticulo (cod_art);
            cout << endl ;
            msj ("¿Desea cancelar la venta? ",2,ancho_formato,"ROJO"); cout << endl;
            msj ("(S/N): ",2,ancho_formato); cin >> opcion ;

            while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N'){
                devolucion ("CARÁCTER INCORRECTO","ROJO",ancho_formato,alto_formato);
                titulo ("CARÁCTER INCORRECTO","ROJO",ancho_formato);
                hidecursor ();
                anykey ();
                showcursor ();
                devolucion ("NO HAY STOCK SUFICIENTE","ROJO",ancho_formato,alto_formato);
                titulo ("NO HAY STOCK SUFICIENTE","ROJO",ancho_formato);
                borrar_renglon (alto_formato-5);
                msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
            }
            if (opcion == 's'){
                cls ();
                devolucion (" ","MAGENTA",ancho_formato,alto_formato);
                titulo (" ","MAGENTA",ancho_formato);
                gotoxy (1,alto_formato/2);
                msj ("La venta fue cancelada.", 2, ancho_formato);
                hidecursor ();
                anykey ();
                showcursor ();
                return false ;
            }else {
                borrar_restopantalla (alto_formato-10);
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (11);
                msj ("Cantidad: ", 2, ancho_formato) ;
                cin >> x ;
            }
        }
    }

    cant_venta = x ;
    msj ("Monto: $", 2, ancho_formato-5) ;
    valor_venta = ValorVenta (cod_art,cant_venta) ;
    cout << valor_venta ;

    estado = true ;
    hidecursor ();
    anykey ();
    showcursor ();
    return true ;
}

void ventas::CancelarVenta (){
    estado = false ;
}

int ventas::GetNumVenta (){
    return num_venta ;
}

int ventas::GetIdCliente (){
    return id_cliente;
}

void ventas::GetNombre (char *texto){
    strcpy (texto, nombre);
}

void ventas::MostrarNombre (){
    cout << nombre ;
}

void ventas::SetApellido (char* texto){
    strcpy (apellido, texto);
}

void ventas::GetApellido (char* texto){
    strcpy (texto, apellido);
}

void ventas::MostrarApellido (){
    cout << apellido ;
}

int ventas::GetDni (){
    return dni;
}

void ventas::GetMail (char* texto){
    strcpy (texto, mail);
}

void ventas::MostrarMail (){
    cout << mail ;
}

float ventas::GetValorVenta (){
    return valor_venta ;
}

bool ventas::GetEstado (){
    return estado ;
}

int ventas::GetCant (){
    return cant_venta ;
}

int ventas::GetCodArt (){
    return cod_art ;
}

void ventas::MostrarFechaVenta () {
    cout << fec_compra.dia << "/" << fec_compra.mes << "/" << fec_compra.anio ;
}

