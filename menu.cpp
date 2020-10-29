#include <iostream>
using namespace std ;
#include "rlutil.h"
using namespace rlutil ;
#include "interfaz.h"
#include "menu.h"
#include "clases.h"
#include "ventas.h"
#include "precios.h"
#include "stock.h"
#include "clientes.h"
#include "config.h"

///const int ancho_formato = 80, alto_formato=25 ;

void AperturaArchivos (){
    FILE *f;
    f=fopen("archivoventas.dat","ab");
    if (f==NULL){
        return ;
    }
    fclose (f);
    f=fopen ("archivoprecios.dat","ab");
    if (f==NULL){
        return ;
    }
    fclose (f);
    f=fopen ("archivostock.dat","ab");
    if (f==NULL){
        return ;
    }
    fclose (f);
    f=fopen ("archivoclientes.dat","ab");
    if (f==NULL){
        return ;
    }
    fclose (f);
}

void menu_principal (){
    char opcion_menu [5];
    bool estado = true ;
    while (estado == true){
        cls () ;
        devolucion ("ABASTECER ORTOPÉDICO","AZUL", ancho_formato, alto_formato);
        titulo ("ABASTECER ORTOPÉDICO","AZUL",ancho_formato);
        msj ("01. Menú ventas.", 2,ancho_formato) ; cout << endl ;
        msj ("02. Menú stock." , 2,ancho_formato) ; cout << endl ;
        msj ("03. Menú clientes.", 2,ancho_formato); cout << endl ;
        msj ("04. Menú precios.", 2,ancho_formato); cout << endl ;
        msj ("05. Registros.", 2,ancho_formato) ; cout << endl ;
        msj ("06. Ajustes.", 2,ancho_formato); cout << endl ;

        guiones (ancho_formato);

        msj ("00. Salir del programa.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);
        gotoxy (1, alto_formato/2+5);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (*opcion_menu) {
            case '1':
                menu_ventas ();
                break ;
            case '2':
                menu_stock ();
                break ;
            case '3':
                menu_clientes ();
                break ;
            case '4':
                menu_precios ();
                break ;
            case '5':
                menu_registros ();
                break ;
            case '6':
                menu_ajustes ();
                break ;
            case '0':
                estado = false ;
                break ;
            default :
                cls ();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
                break ;
        }
    }
}

void menu_ventas (){
    char opcion_menu [5];
    bool estado=true ;
    while (estado==true){
        cls ();
        devolucion ("VENTAS","MAGENTA", ancho_formato, alto_formato);
        titulo ("VENTAS","MAGENTA", ancho_formato);

        msj ("01. Nueva venta.", 2,ancho_formato); cout << endl ;
        msj ("02. Cancelar venta.", 2, ancho_formato); cout << endl ;
        msj ("03. Mostrar una venta.", 2 ,ancho_formato) ; cout << endl ;
        msj ("04. Listar todas las ventas.", 2, ancho_formato); cout << endl ;
        msj ("05. Listar ventas de un cliente", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (*opcion_menu) {

            {case '1': /// Nueva venta
                char opc;
                bool grabo ;
                ventas venta1 ;
                grabo = venta1.SetNuevaVenta () ;
                if (grabo==false){
                    return ;
                }
                cls ();

                devolucion ("VENTAS","MAGENTA", ancho_formato, alto_formato);
                titulo ("VENTAS","MAGENTA", ancho_formato);

                gotoxy (1,alto_formato /2);

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
                    bool grabo ;
                    int pos;
                    clientes cli ;
                    grabo = GuardarVenta(venta1);
                    if (grabo ==true){
                        devolucion ("VENTA REALIZADA","MAGENTA", ancho_formato, alto_formato);
                        titulo ("VENTA REALIZADA","MAGENTA", ancho_formato);
                        gotoxy (1, alto_formato/2);
                        msj ("VENTA CONFIRMADA",2, ancho_formato,"VERDE");
                        anykey ();
                        pos = BuscarCliente (venta1.GetIdCliente());
                        if (pos==-2){
                            CargarClienteNuevo (venta1);
                        }else {
                            if (pos>=0){
                                cli=LeerCliente (pos);
                                cli.SetAcumulado (venta1.GetValorVenta ());
                                GuardarCliente (cli,pos);
                            }

                        }
                    }else {
                        devolucion ("ERROR AL GRABAR","ROJO", ancho_formato, alto_formato);
                        titulo ("ERROR AL GRABAR","ROJO", ancho_formato);
                        anykey ();
                    }


                }else{
                    devolucion ("VENTA CANCELADA","MAGENTA", ancho_formato, alto_formato);
                    titulo ("VENTA CANCELADA","MAGENTA", ancho_formato);
                    gotoxy (1, alto_formato/2);
                    msj ("VENTA CANCELADA",2, ancho_formato,"ROJO");
                    anykey ();
                }
                CambiarStockArticulo (venta1.GetCodArt(),-1*venta1.GetCant(),venta1.GetEstado());
            break ;}

            {case '2': /// Cancelar venta
                int id , pos;
                char opcion ;
                ventas reg ;
                cls ();
                devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
                titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
                gotoxy (1,alto_formato/2);
                msj ("ingrese el id de la venta que quiere cancelar: ", 2, ancho_formato); cin >> id ;
                pos =BuscarVenta (id);
                if (pos==-2){
                    devolucion ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato, alto_formato);
                    titulo ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato);
                    anykey ();
                }else {
                    if (pos==-1){
                        devolucion ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato, alto_formato);
                        titulo ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato);
                        anykey ();
                    }else {
                        reg = LeerVenta (pos);
                        MostrarVenta (reg);
                        gotoxy (1, alto_formato-8);
                        msj ("¿Está seguro de eliminar esta venta?",2,ancho_formato,"ROJO"); cout << endl ;
                        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
                        bool opc = false ;
                        while (opc==false){
                            switch (opcion){
                            case 's':
                            case 'S':
                                bool grabo ;
                                cls ();
                                anykey ();
                                reg.CancelarVenta ();
                                cout << "el estado de la venta es: " ;
                                cout << reg.GetEstado ();
                                anykey ();
                                grabo=GuardarVenta(reg,pos);
                                MostrarVenta (reg);
                                if (grabo==true){
                                    cls ();
                                    devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
                                    titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
                                    gotoxy (1,alto_formato/2);
                                    msj ("La venta fue dada de baja exitosamenta", 2, ancho_formato,"VERDE") ;
                                    hidecursor();
                                    anykey ();
                                    showcursor ();
                                }

                                opc=true ;
                                break ;
                            case 'n':
                            case 'N':
                                cls ();
                                devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
                                titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
                                gotoxy (1,alto_formato/2);
                                msj ("La venta no fue dada de baja", 2, ancho_formato,"VERDE") ;
                                hidecursor();
                                anykey ();
                                showcursor ();
                                opc=true ;
                                break ;
                            default :
                                devolucion ("CARÁCTER INVÁLIDO","ROJO",ancho_formato,alto_formato);
                                titulo ("CARÁCTER INVÁLIDO", "ROJO", ancho_formato);
                                anykey ();
                                devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
                                titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
                                gotoxy (1, alto_formato-8);
                                msj ("¿Está seguro de eliminar esta venta?",2,ancho_formato,"ROJO"); cout << endl ;
                                borrar_renglon(alto_formato-7);
                                msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
                                break ;
                            }
                        }

                        anykey ();
                    }
                }
            break ;}

            {case '3': /// Mostrar una venta
                int id, x;
                ventas reg ;
                cls ();
                devolucion ("VENTA", "MAGENTA", ancho_formato, alto_formato) ;
                titulo ("VENTA", "MAGENTA", ancho_formato) ;
                gotoxy (1,alto_formato/2);
                msj ("Ingrese el código de la venta que quiere mostrar: ", 2,ancho_formato); cin >> id ;
                x =BuscarVenta (id);
                if (x==-2){
                    devolucion ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato, alto_formato);
                    titulo ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato);
                    anykey ();
                    return ;
                }
                if (x==-1){
                    devolucion ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato);
                    anykey ();
                    return ;
                }

                reg = LeerVenta (x);
                MostrarVenta (reg);
                break ;}

            {case '4': /// Listar ventas
                int x ;
                x = ListarVentas ();
                if (x==-2 || x==-1){
                    devolucion ("OCURRIÓ UN ERROR","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR","ROJO", ancho_formato);
                    anykey ();
                }
                break ;}
            {case '5': /// Listar ventas de un cliente
                bool estado = true ;
                char opcion ;
                while (estado==true){
                    cls ();
                    devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
                    titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
                    msj ("01. Listar por id de cliente.",2,ancho_formato);cout << endl ;
                    msj ("02. Listar por dni.",2,ancho_formato);cout << endl ;
                    msj ("03. Listar por mail.",2,ancho_formato);cout << endl ;
                    guiones (ancho_formato);
                    msj ("00. Volver atrás.",2,ancho_formato,"ROJO");cout << endl ;
                    guiones (ancho_formato);
                    msj ("Ingrese opción: ",2,ancho_formato) ; cin >> opcion ;
                    switch (opcion){
                    {case '1': ///listar por id
                        int id , dev ;
                        cls ();
                        devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
                        titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
                        msj ("Ingrese id del cliente: ",2,ancho_formato); cin >> id ;
                        dev = ListarClientesPorId (id);
                        if (dev==0){
                            devolucion ("No se encontraron ventas de ese id", "ROJO", ancho_formato, alto_formato) ;
                            titulo ("No se encontraron ventas de ese id", "ROJO", ancho_formato) ;
                            anykey ();
                        }else {
                            if (dev<0){
                                devolucion ("OCURRIÓ UN ERROR", "ROJO", ancho_formato, alto_formato) ;
                                titulo ("OCURRIÓ UN ERROR", "ROJO", ancho_formato) ;
                                anykey ();
                            }
                        }
                        break ;}
                    {case '2':///listar por dni
                        int dni , dev ;
                        cls ();
                        devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
                        titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
                        msj ("Ingrese dni: ",2,ancho_formato); cin >> dni ;
                        dev = ListarClientesPorDni (dni);
                        if (dev==0){
                            devolucion ("No se encontraron ventas con ese id", "ROJO", ancho_formato, alto_formato) ;
                            titulo ("No se encontraron ventas con ese id", "ROJO", ancho_formato) ;
                            anykey ();
                        }else {
                            if (dev<0){
                                devolucion ("OCURRIÓ UN ERROR", "ROJO", ancho_formato, alto_formato) ;
                                titulo ("OCURRIÓ UN ERROR", "ROJO", ancho_formato) ;
                                anykey ();
                            }
                        }
                        break ;}
                    {case '3':///listar por mail
                        int dev ;
                        char mail [50];
                        cls ();
                        devolucion ("LISTADO DE VENTAS", "MAGENTA", ancho_formato, alto_formato) ;
                        titulo ("LISTADO DE VENTAS", "MAGENTA", ancho_formato) ;
                        msj ("Ingrese Mail: ",2,ancho_formato);
                        cin.ignore ();
                        cin.getline (mail,50) ;
                        dev = ListarClientesPorMail (mail);
                        if (dev==0){
                            devolucion ("No se encontraron ventas de ese mail", "ROJO", ancho_formato, alto_formato) ;
                            titulo ("No se encontraron ventas de ese mail", "ROJO", ancho_formato) ;
                            anykey ();
                        }else {
                            if (dev<0){
                                devolucion ("OCURRIÓ UN ERROR", "ROJO", ancho_formato, alto_formato) ;
                                titulo ("OCURRIÓ UN ERROR", "ROJO", ancho_formato) ;
                                anykey ();
                            }
                        }
                        break ;}
                    {case '0':
                        estado = false ;
                        break ;}
                    default :
                        devolucion ("CARÁCTER INVÁLIDO", "ROJO", ancho_formato, alto_formato) ;
                        titulo ("CARÁCTER INVÁLIDO", "ROJO", ancho_formato) ;
                        break ;






                    }


                }
                break ;}
            {case '0':
                estado = false ;
            break ;}

            {default :
                cls ();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
            break ;}
        }
    }
}

void menu_stock (){
    char opcion_menu ;
    bool estado=true ;
    while (estado==true){
        cls ();
        devolucion ("CONTROL DE STOCK","VERDE", ancho_formato, alto_formato);
        titulo ("CONTROL DE STOCK","VERDE", ancho_formato);
        msj ("01. Agregar stock.", 2,ancho_formato); cout << endl ;
        msj ("02. Reducir stock.", 2, ancho_formato); cout << endl ;
        /*msj ("03. Dar de baja un artículo.",2,ancho_formato); cout << endl ;
        msj ("04. Dar de alta un artículo.", 2, ancho_formato); cout << endl ;
        */
        msj ("03. Cambiar todo el stock.", 2, ancho_formato); cout << endl ;
        msj ("04. Mostrar stock.", 2, ancho_formato); cout << endl ;

        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) {
            case '1': /// ESTA
                MenuAgregarStock ();
            break ;
            case '2': /// ESTA
                MenuReducirStock ();
            break ;
            /*case '3': /// FALTA
                MenuEstado();
            break ;
            case '4': /// FALTA
                MenuEstado();
            break ;
            */
            case '3': /// HECHO
                CambiarTodoStock ();
            break ;
            case '4': /// HECHO
                MostrarListaStock ();
            break ;
            case '0':
                estado = false ;
            break ;
            default :
                cls ();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
            break ;
        }
    }
}

void menu_clientes (){  ///
    char opcion_menu ;
    bool estado=true ;
    while (estado==true){
        cls ();
        devolucion ("CLIENTES","AMARILLO", ancho_formato, alto_formato);
        titulo ("CLIENTES","AMARILLO", ancho_formato);
        msj ("01. Ver cliente.", 2,ancho_formato); cout << endl ;
        msj ("02. Eliminar cliente.", 2, ancho_formato); cout << endl ;
        msj ("03. Listar ventas de un cliente", 2,ancho_formato); cout << endl ;
        msj ("04. Listar clientes.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) {
            case '1':
                cls ();
                devolucion ("CLIENTES","AMARILLO", ancho_formato, alto_formato);
                titulo ("CLIENTES","AMARILLO", ancho_formato);
                MenuVerCliente ();
            break ;
            case '2':
                cls ();
                cout << "Eliminar cliente";
                anykey ();
            break ;
            case '3':
                break;
            case '4':
                int x ;
                x = ListarClientes ();
                if (x==-2 || x==-1){
                    devolucion ("OCURRIÓ UN ERROR","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR","ROJO", ancho_formato);
                    anykey ();
                }

                break ;
            case '0':
                estado = false ;
            break ;
            default :
                cls ();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
            break ;
        }
    }
}

void menu_registros (){
    cls ();
    cout << "MENU REGISTROS";
    anykey ();
}

void menu_precios (){
    char opcion_menu ;
    bool estado =true ;
    while (estado ==true){
        cls ();

        devolucion ("AJUSTES","BLANCO", ancho_formato, alto_formato);
        titulo ("AJUSTES","BLANCO", ancho_formato);

        msj ("01. Lista de precios.", 2,ancho_formato); cout << endl ;
        msj ("02. Modificar lista completa de precios.", 2,ancho_formato); cout << endl ;
        msj ("03. Cambiar precio.", 2, ancho_formato); cout << endl ;

        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (opcion_menu){
        case '1':
            MostrarListaPrecios ();
            break;
        case '2':
            CrearPrecios ();
            break ;
        case '3':
            CambiarPrecio ();
            break ;
        case '0':
            estado = false ;
            break ;
        default :
            cls ();
            devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
            titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
            hidecursor ();
            anykey ();
            showcursor ();
            break ;
        }




    }


}

void menu_ajustes (){
    char opcion_menu, opcion ;
    bool estado=true, grabo ;
    while (estado==true){
        cls ();
        devolucion ("AJUSTES","AMARILLO", ancho_formato, alto_formato);
        titulo ("AJUSTES","AMARILLO", ancho_formato);

        msj ("01. Eliminar todas las ventas.", 2,ancho_formato); cout << endl ;
        msj ("02. Eliminar lista de precios.", 2,ancho_formato); cout << endl ;
        msj ("03. Eliminar stock.", 2,ancho_formato); cout << endl ;
        msj ("04. Eliminar todos los clientes.", 2,ancho_formato); cout << endl ;
        msj ("05. Recuperar datos.", 2,ancho_formato); cout << endl ;

        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (opcion_menu) {
            {case '1': /// BORRAR VENTAS
                cls ();
                setColor (RED);
                gotoxy (1,alto_formato/2);
                msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                while (opcion !='s' && opcion !='S' && opcion !='N' && opcion !='n'){
                    devolucion ("CARÁCTER INCORRECTO","BLANCO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","BLANCO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;

                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpVentas();
                    if (grabo==true){
                        grabo = BorrarVentas ();
                        if (grabo==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '2':  /// BORRAR PRECIOS
                cls ();
                setColor (RED);
                gotoxy (1,alto_formato/2);
                msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                while (opcion !='s' && opcion !='S' && opcion !='N' && opcion !='n'){
                    devolucion ("CARÁCTER INCORRECTO","BLANCO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","BLANCO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpPrecios();
                    if (grabo==true){
                        grabo = BorrarPrecios ();
                        if (grabo==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '3':  /// BORRAR STOCK
                cls ();
                setColor (RED);
                gotoxy (1,alto_formato/2);
                msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                while (opcion !='s' && opcion !='S' && opcion !='N' && opcion !='n'){
                    devolucion ("CARÁCTER INCORRECTO","BLANCO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","BLANCO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpStock();
                    if (grabo==true){
                        grabo = BorrarStock ();
                        if (grabo==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '4':  /// BORRAR CLIENTES
                cls ();
                setColor (RED);
                gotoxy (1,alto_formato/2);
                msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                while (opcion !='s' && opcion !='S' && opcion !='N' && opcion !='n'){
                    devolucion ("CARÁCTER INCORRECTO","BLANCO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","BLANCO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpClientes();
                    if (grabo==true){
                        grabo = BorrarClientes ();
                        if (grabo==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '5':
                menu_recuperar_datos ();
                break ;}
            {case '0':
                estado = false ;
                break ;}
            default :
                cls();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
                break ;


        }
    }
}

void menu_recuperar_datos (){
    char opcion_menu ;
    bool estado=true, recupero ;
    while (estado==true){
        cls ();
        devolucion ("BACKUP","AMARILLO", ancho_formato, alto_formato);
        titulo ("BACKUP","AMARILLO", ancho_formato);

        msj ("01. Recuperar datos de ventas.", 2,ancho_formato); cout << endl ;
        msj ("02. Recuperar datos de precios.", 2,ancho_formato); cout << endl ;
        msj ("03. Recuperar datos de stock.", 2,ancho_formato); cout << endl ;
        msj ("04. Recuperar datos de clientes.", 2,ancho_formato); cout << endl ;

        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (opcion_menu) {
            case '1': /// Recuperar datos de ventas
                recupero=RecuperarVentas ();
                if(recupero==true){
                    BorrarBkpVentas ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();

                }
                break ;
            case '2': /// Recuperar datos de precios
                recupero=RecuperarPrecios ();
                if(recupero==true){
                    BorrarBkpPrecios ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();

                }
                break ;
            case '3': /// Recuperar datos de stock
                recupero=RecuperarStock ();
                if(recupero==true){
                    BorrarBkpStock ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();

                }
                RecuperarStock ();
                break ;
            case '4': /// Recuperar datos de clientes
                recupero=RecuperarClientes ();
                if(recupero==true){
                    BorrarBkpClientes ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","AMARILLO", ancho_formato);
                    anykey ();

                }
                break ;
            case '0':
                estado = false ;
                break ;
            default :
                cls();
                devolucion ("ERROR DE OPCIÓN", "ROJO", ancho_formato, alto_formato) ;
                titulo ("ERROR DE OPCIÓN", "ROJO", ancho_formato) ;
                hidecursor ();
                anykey ();
                showcursor ();
                break ;


        }
    }
}
