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
#include "articulo.h"
///INTERFAZ MAGENTA


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

void MostrarVenta (ventas reg){/// esta
    clientes cli ;
    int pos ;
    char texto [50];
    pos=BuscarCliente (reg.GetIdCliente());
    cli = LeerCliente (pos);

    cls ();
    devolucion ("VENTA", "MAGENTA", ancho_formato, alto_formato);
    guiones (ancho_formato,13);
    titulo ("VENTA", "MAGENTA", ancho_formato);
    gotoxy ((ancho_formato-6)/2,3);
    reg.MostrarFechaVenta () ;cout << endl ;
    msj ("Num. venta: ", 2, ancho_formato) ; cout << reg.GetNumVenta () << endl ;
    msj ("ID cliente: ", 2, ancho_formato) ; cout << reg.GetIdCliente () << endl ;
    cli.GetNombre (texto);
    msj ("Nombre: ", 2, ancho_formato-10) ; cout << texto << endl ;
    cli.GetApellido (texto);
    msj ("Apellido: ", 2, ancho_formato-10) ; cout << texto << endl ;
    msj ("DNI: ", 2, ancho_formato-5) ; cout << cli.GetDni () << endl ;
    cli.GetMail (texto);
    msj ("Mail: ", 2, ancho_formato-15) ;  cout << texto << endl ;
    msj ("Cod. artículo: ", 2, ancho_formato) ; cout << reg.GetCodArt () << endl ;
    msj ("Cantidad: ", 2, ancho_formato) ; cout << reg.GetCantVenta () << endl ;
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

int ListarVentas (){ /// esta
    clientes cli ;
    char texto [50];
    int cant = CantVentas (),x=0, cont=0, pos;
    ventas *vta  ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vta = (ventas*) malloc (cant*sizeof (ventas));
    if (vta ==NULL){
        free (vta);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }
    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vta);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vta,sizeof (ventas), cant, f) ;
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
        pos = BuscarCliente (vta[x].GetIdCliente());
        cli = LeerCliente (pos);
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vta[x].GetEstado()==true) {
            gotoxy (1, cont+9);
            cout << "  " ; vta[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vta[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cli.GetApellido (texto);
            cout << "| " << texto ;
            gotoxy (41,cont+9);
            cout << "| " << vta[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vta[x].GetCantVenta () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vta[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vta[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    anykey ();
    free (vta);
    return 0 ; /// Todo ok
}

int ListarClientesPorId (int id){ ///esta
    clientes cli ;
    int pos ;
    char texto [50];
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

    pos = BuscarCliente (id);
    if (pos<0){
        return 0 ;
    }
    cli = LeerCliente (pos);
    itoa (id,texto,10);

    cls ();
    devolucion (texto, "MAGENTA", ancho_formato, alto_formato) ;
    titulo (texto, "MAGENTA", ancho_formato) ;
    //guiones (ancho_formato,19);
    gotoxy (1,x+7);
    msj (" ",2,ancho_formato,"AZUL");
    setBackgroundColor (BLUE);
    gotoxy (1,x+7);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    setBackgroundColor (BLACK);
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
            cli.GetApellido (texto);
            cout << "| " << texto ;
            gotoxy (41,cont+9);
            cout << "| " << vec[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vec[x].GetCantVenta () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vec[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vec[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    guiones (ancho_formato);
    anykey ();
    free (vec);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}

int ListarClientesPorDni (int dni){ /// esta
    int cant = CantVentas (),x=0, cont=0, pos_cli;
    ventas *vta  ;
    clientes cli ;

    char texto [50];
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vta = (ventas*) malloc (cant*sizeof (ventas));
    if (vta ==NULL){
        free (vta);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }
    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vta);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vta,sizeof (ventas), cant, f) ;
    fclose (f);

    pos_cli=BuscarDni (dni);
    if (pos_cli<0){
        return -0 ;
    }
    cli = LeerCliente (pos_cli);
    itoa (dni,texto,10);

    cls ();
    devolucion (texto, "MAGENTA", ancho_formato, alto_formato) ;
    titulo (texto, "MAGENTA", ancho_formato) ;
    gotoxy (1,x+7);
    msj (" ",2,ancho_formato,"AZUL");
    setBackgroundColor (BLUE);
    gotoxy (1,x+7);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    setBackgroundColor (BLACK);
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vta[x].GetEstado()==true && vta[x].GetIdCliente()==cli.GetId ()) {
            gotoxy (1, cont+9);
            cout << "  " ; vta[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vta[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cli.GetApellido (texto);
            cout << "| " << texto ;
            gotoxy (41,cont+9);
            cout << "| " << vta[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vta[x].GetCantVenta () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vta[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vta[x].GetIdCliente ();
            cout << endl ;

            cont ++ ;
        }
    }
    guiones (ancho_formato);
    anykey ();
    free (vta);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}

int ListarClientesPorMail (char *mail){ /// esta
    clientes cli ;
    int cant = CantVentas (),x=0, cont=0, comp, pos_cli;
    ventas *vta  ;
    char texto[50] ;
    if (cant==-1){
        return -1; /// ERROR DE LECTURA CANTIDAD
    }
    vta = (ventas*) malloc (cant*sizeof (ventas));
    if (vta ==NULL){
        free (vta);
        return -2 ; /// ERROR DE MEMORIA INTERNA
    }
    FILE*f ;
    f =fopen (ArchivoVentas, "rb");
    if (f==NULL){
        free (vta);
        return -1 ; /// ERROR DE LECTURA
    }
    fread (vta,sizeof (ventas), cant, f) ;
    fclose (f);

    pos_cli = BuscarMail (mail);
    if (pos_cli<0){
        return 0;
    }
    cli = LeerCliente (pos_cli);
    cli.GetMail (texto);

    cls ();
    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
    titulo (texto, "MAGENTA", ancho_formato) ;

    gotoxy (1,x+7);
    msj (" ",2,ancho_formato,"AZUL");
    setBackgroundColor (BLUE);
    gotoxy (1,x+7);
    cout << "    Fecha    | Vta |  Apellido          | Art | Cant | Valor vta.| ID " << endl ;
    setBackgroundColor (BLACK);
    guiones(ancho_formato);
    for (x=0 ; x< cant ;x++){
        if (cont>9){
            cont = 0 ;
            anykey ();
            borrar_restopantalla (cont+9);
            devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
            guiones (ancho_formato,19);
        }
        if (vta[x].GetEstado()==true && vta[x].GetIdCliente() == cli.GetId()/*comp==0*/) {
            gotoxy (1, cont+9);
            cout << "  " ; vta[x].MostrarFechaVenta ();
            gotoxy (14,cont+9);
            cout << "| " ;
            cout << vta[x].GetNumVenta() ;
            gotoxy (20,cont+9);
            cli.GetApellido (texto);
            cout << "| " << texto ;
            gotoxy (41,cont+9);
            cout << "| " << vta[x].GetCodArt() ;
            gotoxy (47,cont+9) ;
            cout << "| " << vta[x].GetCantVenta () ;
            gotoxy (54,cont+9) ;
            cout << "|  $" << vta[x].GetValorVenta() ;
            gotoxy (66,cont+9);
            cout << "| " << vta[x].GetIdCliente ();
            cout << endl ;
            cont ++ ;
        }
    }
    guiones (ancho_formato);
    anykey ();
    free (vta);
    if (cont == 0){
        return 0 ; /// No encontro ventas
    }
    return 1 ; /// Encontro alguna venta
}

bool NuevaVenta (){
    char texto [50], opc;
    ventas vta ;
    clientes cli ;
    articulo art ;
    fecha dia ;
    int x , pos, cant_stock, pos_art, pos_cli;
    float valor ;
    bool cli_nuevo = true, grabo , grabo1;
    cls ();
    devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
    guiones (ancho_formato,13);
    titulo ("NUEVA VENTA","MAGENTA",ancho_formato);

    MostrarFecha (2,ancho_formato); cout << endl ;
    dia = CargarFechaActual ();
    vta.SetFecCompra (dia);
    vta.SetNumVenta (CantVentas()+1);
    msj ("Num. venta: ", 2, ancho_formato) ; cout << vta.GetNumVenta () << endl ;
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
    vta.SetIdCliente (x);
    cli.SetId (x);
    pos_cli=BuscarCliente (x);
    if (pos_cli>=0){
        cli=LeerCliente (pos_cli);

        cli.GetNombre (texto);
        msj ("Nombre: ",2,ancho_formato-10); cout << texto << endl ;

        cli.GetApellido (texto);
        msj ("Apellido: ",2,ancho_formato-10); cout << texto << endl ;

        msj ("DNI: ", 2, ancho_formato-5); cout << cli.GetDni () << endl ;

        cli.GetMail (texto);
        msj ("Mail: ",2,ancho_formato-15); cout << texto << endl ;
        cli_nuevo = false ;
    }else {
        if (pos_cli==-2){
            msj ("Nombre: ", 2, ancho_formato-10) ;
            cin.ignore ();
            cin.getline(texto,50);
            x=ValidarTexto (texto);
            while (x==0){
                devolucion ("NOMBRE INCORRECTO ","ROJO",ancho_formato,alto_formato);
                titulo ("NOMBRE INCORRECTO","ROJO",ancho_formato);
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (6);
                msj ("Nombre: ", 2, ancho_formato-10) ;
                cin.getline(texto,50);
                x=ValidarTexto (texto);
            }
            cli.SetNombre (texto);

            msj ("Apellido: ", 2, ancho_formato-10) ;
            cin.getline (texto, 50);
            x=ValidarTexto (texto);
            while (x==0){
                devolucion ("APELLIDO INCORRECTO ","ROJO",ancho_formato,alto_formato);
                titulo ("APELLIDO INCORRECTO","ROJO",ancho_formato);
                anykey ();
                devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
                titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
                borrar_renglon (7);
                msj ("Apellido: ", 2, ancho_formato-10) ;
                cin.getline(texto,50);
                x=ValidarTexto (texto);
            }
            cli.SetApellido (texto);


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
            cli.SetDni(x);

            msj ("Mail: ", 2, ancho_formato-15) ;
            cin.ignore ();
            cin.getline (texto, 50);
            x=ValidarMail (texto);
            pos = BuscarMail (texto);
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
                cin.getline(texto,50);
                x=ValidarMail (texto);
            }
            cli.SetMail(texto);
        }
        else {
            cls ();
            cout << "error" ;
            anykey ();
        }
    }

    msj ("Cod. artículo: ", 2, ancho_formato) ;
    cin >> x ;
    pos_art = BuscarArticulo (x);
    while (pos_art<0){
        devolucion ("CÓDIGO INCORRECTO","ROJO",ancho_formato,alto_formato);
        titulo ("CÓDIGO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("NUEVA VENTA","MAGENTA",ancho_formato,alto_formato);
        titulo ("NUEVA VENTA","MAGENTA",ancho_formato);
        borrar_renglon (10);
        msj ("Cod. artículo: ", 2, ancho_formato) ;
        cin >> x ;
        pos_art = BuscarArticulo (x);
    }
    vta.SetCodArt (x);
    pos_art = BuscarArticulo (x);
    art=LeerArticulo (pos_art);
    cant_stock = BuscarStock (pos);
    msj ("Cantidad: ", 2, ancho_formato) ;
    cin >> x ;
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
            MostrarStockArticulo (pos);
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
    vta.SetCantVenta (x);
    art.SetStock (x * -1);
    msj ("Monto: $", 2, ancho_formato-5) ;
    valor = ValorVenta (vta.GetCodArt (), vta.GetCantVenta ()) ;
    cout << valor ;
    vta.SetValorVenta (valor);
    cli.SetAcumulado (valor);
    vta.SetEstado (true);
    hidecursor ();
    anykey ();
    showcursor ();


    gotoxy (1,16);

    msj ("Confirme la venta (S/N): ",2,ancho_formato);
    cin >> opc ;

    while (opc!='s' && opc!='S' && opc!='n' && opc!='N'){
        devolucion ("CARÁCTER INVÁLIDO","ROJO", ancho_formato, alto_formato);
        titulo ("CARÁCTER INVÁLIDO","ROJO", ancho_formato);
        anykey ();
        devolucion ("VENTAS","MAGENTA", ancho_formato, alto_formato);
        titulo ("VENTAS","MAGENTA", ancho_formato);
        borrar_renglon (alto_formato/2);
        gotoxy (1,alto_formato /2);
        msj ("Confirme la venta (S/N): ",2,ancho_formato);
        cin >> opc ;
    }

    if (opc =='s' || opc=='S'){
        grabo = GuardarVenta(vta);
        if (grabo ==true){
            cls ();
            devolucion ("VENTA REALIZADA","MAGENTA", ancho_formato, alto_formato);
            titulo ("VENTA REALIZADA","MAGENTA", ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("VENTA CONFIRMADA",2, ancho_formato,"VERDE");
            anykey ();
            cli.SetEstado(true);
            if (cli_nuevo == true){
                grabo1=GuardarClienteNuevo (cli);
            }else {
                grabo1=GuardarCliente (cli, pos_cli);
            }
            if (grabo1 == false){
                devolucion ("OCURRIÓ UN ERROR AL GUARDAR EL CLIENTE","MAGENTA", ancho_formato, alto_formato);
                titulo ("OCURRIÓ UN ERROR AL GUARDAR EL CLIENTE","MAGENTA", ancho_formato);
                anykey ();
            }
            grabo = GuardarArticulo (art,pos_art);
        }
        else {
            devolucion ("ERROR AL GRABAR","ROJO", ancho_formato, alto_formato);
            titulo ("ERROR AL GRABAR","ROJO", ancho_formato);
            anykey ();
        }
    }
    else{
        devolucion ("VENTA CANCELADA","MAGENTA", ancho_formato, alto_formato);
        titulo ("VENTA CANCELADA","MAGENTA", ancho_formato);
        gotoxy (1, alto_formato/2);
        msj ("VENTA CANCELADA",2, ancho_formato,"ROJO");
        anykey ();
    }
}

///------------------------------------------------------------------------------------//

void ventas::CancelarVenta (){
    estado = false ;
}

void ventas::SetFecCompra (fecha dia){
    fec_compra.dia = dia.dia ;
    fec_compra.mes = dia.mes ;
    fec_compra.anio = dia.anio ;
}

void ventas::SetNumVenta (int num){
    num_venta = num ;
}

int ventas::GetNumVenta (){
    return num_venta ;
}

void ventas::SetIdCliente (int id){
    id_cliente = id ;
}

int ventas::GetIdCliente (){
    return id_cliente;
}

float ventas::GetValorVenta (){
    return valor_venta ;
}

void ventas::SetValorVenta (float valor){
    valor_venta = valor ;
}

bool ventas::GetEstado (){
    return estado ;
}

void ventas::SetEstado (bool es){
    estado = es ;
}

int ventas::GetCantVenta (){
    return cant_venta ;
}

void ventas::SetCantVenta (int cant){
    cant_venta = cant ;
}

int ventas::GetCodArt (){
    return cod_art ;
}

void ventas::SetCodArt (int cod){
    cod_art = cod ;
}

void ventas::MostrarFechaVenta () {
    cout << fec_compra.dia << "/" << fec_compra.mes << "/" << fec_compra.anio ;
}

