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
#include "articulo.h"
#include "detallevta.h"
#include "validaciones.h"

void AperturaArchivos (){
    FILE *f;
    f=fopen(ArchivoVentas,"ab");
    if (f==NULL){
        return ;
    }
    fclose (f);

    f=fopen (ArchivoClientes,"ab");
    if (f==NULL){
        return ;
    }
    fclose (f);

    f=fopen (ArchivoArticulo,"ab");
    if(f==NULL){
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
        msj ("02. Menú clientes.", 2,ancho_formato); cout << endl ;
        msj ("03. Menú artículos.", 2,ancho_formato); cout << endl ;
        msj ("04. Registros.", 2,ancho_formato) ; cout << endl ;
        msj ("05. Ajustes.", 2,ancho_formato); cout << endl ;

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
                menu_clientes ();
                break ;
            case '3':
                menu_articulos ();
                break ;
            case '4':
                menu_registros ();
                break ;
            case '5':
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
            NuevaVenta();
        break ;}
        {case '2': /// Cancelar venta
            int id , pos_vta, cant_detalle, pos_cli, pos_art, z ;
            char opcion ;
            detalle det [15];
            ventas vta ;
            articulo art ;
            clientes cli ;
            cls () ;
            devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
            titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("Ingrese el número de venta que quiere cancelar: ", 2, ancho_formato); cin >> id ;
            pos_vta =BuscarVenta (id);
            if (pos_vta==-2){
                devolucion ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato, alto_formato);
                titulo ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato);
                anykey ();
            }else {
                if (pos_vta==-1){
                    devolucion ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR CON LOS ARCHIVOS","ROJO", ancho_formato);
                    anykey ();
                }else {
                    vta = LeerVenta (pos_vta);
                    cant_detalle = LeerTodoDetalle (vta.GetNumVenta(),det);
                    pos_cli = BuscarCliente (vta.GetIdCliente());
                    cli = LeerCliente (pos_cli);
                    MostrarDetalleVenta(cant_detalle, det, vta,cli);
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
                            vta.CancelarVenta ();
                            grabo=GuardarVenta(vta,pos_vta);
                            if (grabo==true){
                                cls ();
                                devolucion ("CANCELAR UNA VENTA","MAGENTA", ancho_formato, alto_formato);
                                titulo ("CANCELAR UNA VENTA","MAGENTA", ancho_formato);
                                gotoxy (1,alto_formato/2);
                                msj ("La venta fue dada de baja exitosamente", 2, ancho_formato,"VERDE") ;
                                hidecursor();
                                anykey ();
                                showcursor ();


                                cli.SetAcumulado (-1* vta.GetValorVenta());
                                GuardarCliente (cli,pos_cli);

                                for (z=0 ; z<cant_detalle ; z++){
                                    pos_art = BuscarArticulo (det[z].GetCodArt());
                                    art = LeerArticulo (pos_art);
                                    art.SetStock (det[z].GetCantVenta());
                                    GuardarArticulo(art,pos_art);
                                }
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
                }
            }
        break ;}
        {case '3': /// Mostrar una venta
            int id, x, cant_det, pos,pos_cli;
            char texto [25];
            ventas vta ;
            detalle dle [15];
            clientes cli ;
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

            vta = LeerVenta (x);
            pos_cli = BuscarCliente (vta.GetIdCliente());
            cli = LeerCliente (pos_cli);


            if (vta.GetEstado()==false ){
                devolucion ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato, alto_formato);
                titulo ("NO SE ENCONTRÓ EL CÓDIGO DE LA VENTA","ROJO", ancho_formato);
                anykey ();
                return ;
            }
            cant_det = LeerTodoDetalle (vta.GetNumVenta(), dle);
            MostrarDetalleVenta (cant_det,dle,vta,cli);
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
                    msj ("Ingrese Mail: ",2,ancho_formato-14);
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
        msj ("03. Mostrar lista de stock.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) { //TODO: HACER EL MENU
            case '1':
                MenuAgregarStock ();
            break ;
            case '2':
                MenuReducirStock ();
            break ;
            case '3':
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

void menu_clientes (){
    char opcion_menu, opc_2 ;
    bool estado=true, grabo;
    int dni, pos ;
    clientes cli(0);
    while (estado==true){
        cls ();
        devolucion ("CLIENTES","VERDE", ancho_formato, alto_formato);
        titulo ("CLIENTES","VERDE", ancho_formato);
        msj ("01. Ver cliente.", 2,ancho_formato); cout << endl ;
        msj ("02. Eliminar cliente.", 2, ancho_formato); cout << endl ;
        msj ("03. Listar clientes.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) {
            case '1':
                MenuVerCliente ();
            break ;
            case '2':
                cls ();
                devolucion ("CLIENTES","VERDE", ancho_formato, alto_formato);
                titulo ("CLIENTES","VERDE", ancho_formato);
                msj ("Ingrese dni de cliente: ", 2, ancho_formato);
                cin >> dni ;
                pos = BuscarDni (dni);

                if (pos<0){
                    devolucion ("NO SE ENCONTRÓ EL DNI EN LOS REGISTROS","ROJO", ancho_formato, alto_formato);
                    titulo ("NO SE ENCONTRÓ EL DNI EN LOS REGISTROS","ROJO", ancho_formato);
                    anykey ();
                    return ;
                }
                cli = LeerCliente (pos);
                cls ();
                MostrarCliente (cli);
                guiones(ancho_formato,15);
                guiones(ancho_formato,12);
                msj ("Está seguro de eliminar este cliente:", 2, ancho_formato,"ROJO"); cout << endl ;
                msj ("(S/N): ", 2 ,ancho_formato);
                cin >> opc_2 ;
                while (opc_2 !='s' && opc_2 !='S' && opc_2 !='n' && opc_2 !='N'){
                    devolucion ("CARÁCTER INCORRECTO","ROJO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","ROJO", ancho_formato);
                    anykey ();
                    devolucion ("CLIENTES","VERDE", ancho_formato, alto_formato);
                    titulo ("CLIENTES","VERDE", ancho_formato);
                    borrar_renglon (14);
                    msj ("(S/N): ", 2 ,ancho_formato);
                    cin >> opc_2 ;
                }

                if (opc_2 == 'n' || opc_2 == 'N'){
                    cls ();
                    devolucion ("","ROJO", ancho_formato, alto_formato);
                    titulo ("","ROJO", ancho_formato);
                    msj ("NO SE ELIMINÓ EL CLIENTE",2,ancho_formato,"ROJO") ;
                    anykey();
                    return ;
                }
                cli.SetEstado (false);
                grabo = GuardarCliente (cli,pos);
                if (grabo == false){
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL ELIMINAR","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL ELIMINAR","ROJO", ancho_formato);
                    anykey();
                    return ;
                }
                cls ();
                devolucion ("","ROJO", ancho_formato, alto_formato);
                titulo ("","ROJO", ancho_formato);
                msj ("CLIENTE ELIMINADO",2,ancho_formato,"ROJO") ;
                anykey();

            break ;
            case '3':
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

void menu_articulos (){
    char opcion_menu ;
    bool estado=true ;
    while (estado==true){
        cls ();
        devolucion ("ARTÍCULOS","AMARILLO", ancho_formato, alto_formato);
        titulo ("ARTÍCULOS","AMARILLO", ancho_formato);
        msj ("01. Articulos.", 2,ancho_formato); cout << endl ;
        msj ("02. Stock.", 2, ancho_formato); cout << endl ;
        msj ("03. Precios.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) { //TODO: HACER EL MENU
            case '1':
                submenu_articulos ();
            break ;
            case '2':
                menu_stock ();
            break ;
            case '3':
                menu_precios ();
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

void submenu_articulos (){
    char opcion_menu, opcion ;
    bool estado=true ;
    int x , pos;
    articulo reg ;
    while (estado==true){
        cls ();
        devolucion ("ARTÍCULOS","AMARILLO", ancho_formato, alto_formato);
        titulo ("ARTÍCULOS","AMARILLO", ancho_formato);
        msj ("01. Agregar un artículo", 2,ancho_formato); cout << endl ;
        msj ("02. Dar de baja un artículo.", 2, ancho_formato); cout << endl ;
        msj ("03. Dar de alta un artículo.", 2, ancho_formato); cout << endl ;
        msj ("04. Mostrar lista de artículos.", 2, ancho_formato); cout << endl ;
        msj ("05. Mostrar un artículo.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (opcion_menu) { //TODO: HACER EL MENU
            case '1':
                CargarArticulo ();
            break ;
            case '2':
                cls ();
                guiones (ancho_formato,6);
                devolucion ("BAJA DE ARTÍCULO","AMARILLO", ancho_formato, alto_formato);
                titulo ("BAJA DE ARTÍCULO","AMARILLO", ancho_formato);
                cout << endl ;
                msj ("¿Qué artículo quiere dar de baja?: ",2,ancho_formato);
                cin >> x ;

                pos = BuscarArticulo (x);
                while (pos<0){
                    devolucion ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato,alto_formato);
                    titulo ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato);
                    anykey ();
                    devolucion ("BAJA DE ARTÍCULO","AMARILLO",ancho_formato,alto_formato);
                    titulo ("BAJA DE ARTÍCULO","AMARILLO",ancho_formato);
                    borrar_renglon (4);
                    msj ("¿Qué artículo quiere dar de baja?: ", 2, ancho_formato) ;
                    cin >> x ;
                    pos=BuscarArticulo (x);
                }
                reg = LeerArticulo (pos);
                gotoxy (1,9);
                ListarArticulo (reg);
                guiones (ancho_formato,15);
                gotoxy (1,12);
                guiones (ancho_formato);
                msj ("¿Está seguro de continuar?",2,ancho_formato,"ROJO"); cout << endl ;
                msj ("(S/N): ",2,ancho_formato);
                cin >> opcion ;

                while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
                    devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
                    titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
                    anykey ();
                    devolucion ("BAJA DE ARTÍCULO","AMARILLO",ancho_formato,alto_formato);
                    titulo ("BAJA DE ARTÍCULO","AMARILLO",ancho_formato);
                    borrar_renglon (14);
                    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
                }
                if (opcion=='s' || opcion=='S'){ //TODO: CHEQUEAR SI GRABA O NO
                    reg.SetEstado (false);
                    GuardarArticulo (reg,pos);
                    cls ();
                    devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
                    titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
                    anykey ();
                }else {
                    cls ();
                    devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
                    titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
                    anykey ();
                }
            break ;
            case '3':
                cls ();
                guiones (ancho_formato,6);
                devolucion ("ALTA DE ARTÍCULO","AMARILLO", ancho_formato, alto_formato);
                titulo ("ALTA DE ARTÍCULO","AMARILLO", ancho_formato);
                cout << endl ;
                msj ("¿Qué artículo quiere dar de alta?: ",2,ancho_formato);
                cin >> x ;

                pos = BuscarArticulo (x);
                while (pos<0){
                    devolucion ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato,alto_formato);
                    titulo ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato);
                    anykey ();
                    devolucion ("ALTA DE ARTÍCULO","AMARILLO",ancho_formato,alto_formato);
                    titulo ("ALTA DE ARTÍCULO","AMARILLO",ancho_formato);
                    borrar_renglon (4);
                    msj ("¿Qué artículo quiere dar de alta?: ", 2, ancho_formato) ;
                    cin >> x ;
                    pos=BuscarArticulo (x);
                }
                reg = LeerArticulo (pos);
                gotoxy (1,9);
                ListarArticulo (reg);
                guiones (ancho_formato,15);
                gotoxy (1,12);
                guiones (ancho_formato);
                msj ("¿Está seguro de continuar?",2,ancho_formato,"ROJO"); cout << endl ;
                msj ("(S/N): ",2,ancho_formato);
                cin >> opcion ;

                while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
                    devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
                    titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
                    anykey ();
                    devolucion ("ALTA DE ARTÍCULO","AMARILLO",ancho_formato,alto_formato);
                    titulo ("ALTA DE ARTÍCULO","AMARILLO",ancho_formato);
                    borrar_renglon (14);
                    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
                }
                if (opcion=='s' || opcion=='S'){ //TODO: CHEQUEAR SI GRABA O NO
                    reg.SetEstado (true);
                    GuardarArticulo (reg,pos);
                    cls ();
                    devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
                    titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
                    anykey ();
                }else {
                    cls ();
                    devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
                    titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
                    anykey ();
                }
            break ;
            case '4':
                MostrarListaArticulos ();
            break ;
            case '5':
                cls ();
                guiones (ancho_formato,6);
                devolucion ("VER ARTÍCULO","AMARILLO", ancho_formato, alto_formato);
                titulo ("VER ARTÍCULO","AMARILLO", ancho_formato);
                cout << endl ;
                msj ("¿Qué artículo quiere ver?: ",2,ancho_formato);
                cin >> x ;

                pos = BuscarArticulo (x);
                while (pos<0){
                    devolucion ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato,alto_formato);
                    titulo ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato);
                    anykey ();
                    devolucion ("VER ARTÍCULO","AMARILLO",ancho_formato,alto_formato);
                    titulo ("VER ARTÍCULO","AMARILLO",ancho_formato);
                    borrar_renglon (4);
                    msj ("¿Qué artículo quiere ver?: ", 2, ancho_formato) ;
                    cin >> x ;
                    pos=BuscarArticulo (x);
                }
                reg = LeerArticulo (pos);
                gotoxy (1,10);
                MostrarUnArticulo (reg);

                break;
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
    int val;
    char opcion_menu [5];
    bool estado=true ;
    while (estado==true){
        clientes cli ;
        fecha fec;
        cls ();
        devolucion ("REGISTROS","AZUL", ancho_formato, alto_formato);
        titulo ("REGISTROS","AZUL", ancho_formato);

        msj ("01. Listar Ventas de un dia.", 2,ancho_formato); cout << endl ;
        msj ("02. Listar Ventas de un mes.", 2, ancho_formato); cout << endl ;
        msj ("03. Cliente con mas compras.", 2 ,ancho_formato) ; cout << endl ;
        msj ("04. Producto mas vendido.", 2, ancho_formato); cout << endl ;
        msj ("05. Producto menos vendido", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;
        switch (*opcion_menu) {
        case '1':
            cls ();
            devolucion ("REGISTROS","AZUL", ancho_formato, alto_formato);
            titulo ("REGISTROS","AZUL", ancho_formato);
            cout << endl << endl ;
            msj ("Muestra de ventas de un día",2,ancho_formato,"AZUL"); cout << endl ;
            msj ("Ingrese el día: ",2,ancho_formato) ; cin >> fec.dia ;
            msj ("Ingrese el mes: ",2,ancho_formato) ; cin >> fec.mes ;
            msj ("Ingrese el año: ",2,ancho_formato) ; cin >> fec.anio ;
            val = ValidarFecha(fec.dia, fec.mes, fec.anio);
            if (val==0){
                devolucion ("FECHA INCORRECTA","ROJO", ancho_formato, alto_formato);
                titulo ("FECHA INCORRECTA","ROJO", ancho_formato);
                anykey ();
            }
            else {
                val=ListarVentasPorFecha (fec,1);
                if (val==-1){
                    cls();
                    devolucion ("NO SE REGISTRARON VENTAS ESE DÍA","ROJO", ancho_formato, alto_formato);
                    titulo ("NO SE REGISTRARON VENTAS ESE DÍA","ROJO", ancho_formato);
                    anykey ();
                }
                else {
                    if(val==-2){
                        cls();
                        devolucion ("OCURRIÓ UN ERROR","ROJO", ancho_formato, alto_formato);
                        titulo ("OCURRIÓ UN ERROR","ROJO", ancho_formato);
                        anykey ();
                    }
                }
            }
            break;
        case '2':
            cls ();
            devolucion ("REGISTROS","AZUL", ancho_formato, alto_formato);
            titulo ("REGISTROS","AZUL", ancho_formato);
            msj ("Muestra de ventas de un mes",2,ancho_formato,"AZUL"); cout << endl ;
            msj ("Ingrese el mes: ",2,ancho_formato) ; cin >> fec.mes ;
            msj ("Ingrese el año: ",2,ancho_formato) ; cin >> fec.anio ;
            val = ValidarFecha(fec.dia, fec.mes, fec.anio);
            if (val==0){
                devolucion ("FECHA INCORRECTA","ROJO", ancho_formato, alto_formato);
                titulo ("FECHA INCORRECTA","ROJO", ancho_formato);
                anykey ();
            }
            else {
                val=ListarVentasPorFecha (fec,2);
                if (val==-1){
                    cls ();
                    devolucion ("NO SE REGISTRARON VENTAS ESE DÍA","ROJO", ancho_formato, alto_formato);
                    titulo ("NO SE REGISTRARON VENTAS ESE DÍA","ROJO", ancho_formato);
                    anykey ();
                }
                else {
                    if(val==-2){
                        cls ();
                        devolucion ("OCURRIÓ UN ERROR","ROJO", ancho_formato, alto_formato);
                        titulo ("OCURRIÓ UN ERROR","ROJO", ancho_formato);
                        anykey ();
                    }
                }
            }
            break ;
        case '3':
            cls ();
            devolucion ("VENTAS","AZUL", ancho_formato, alto_formato);
            titulo ("VENTAS","AZUL", ancho_formato);
            msj ("03. Cliente con mas compras.", 2 ,ancho_formato) ; cout << endl ;
            cli = ClientesMasVentas ();
            MostrarCliente (cli);
            break;
        case'4':
            ArtMasVendido (1);
            break;
        case'5':
            ArtMasVendido (2);
            break ;
        case '0':
            estado = false ;
            break ;
        }
    }
}

void menu_precios (){
    char opcion_menu ;
    bool estado =true ;
    while (estado ==true){
        cls ();
        articulo reg ;
        devolucion ("PRECIOS","BLANCO", ancho_formato, alto_formato);
        titulo ("PRECIOS","BLANCO", ancho_formato);
        msj ("01. Lista de precios.", 2,ancho_formato); cout << endl ;
        msj ("02. Mostrar precio de un articulo", 2,ancho_formato); cout << endl ;
        msj ("03. Cambiar un precio.", 2, ancho_formato); cout << endl ;
        guiones (ancho_formato);
        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;
        guiones (ancho_formato);
        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (opcion_menu){ //TODO: HACER EL MENU
        case '1':
            MostrarListaPrecios ();
            break;
        case'2':
            int cod_art, pos;
            cls ();
            devolucion ("VER PRECIO","BLANCO",ancho_formato,alto_formato);
            guiones (ancho_formato,6);
            titulo ("VER PRECIO","BLANCO",ancho_formato);
            cout << endl ;
            msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
            pos = BuscarArticulo (cod_art);
            while (pos < 0){
                devolucion ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato,alto_formato);
                titulo ("NO SE ENCONTRÓ EL ARTÍCULO","ROJO",ancho_formato);
                anykey ();
                devolucion ("VER PRECIO","BLANCO",ancho_formato,alto_formato);
                titulo ("VER PRECIO","BLANCO",ancho_formato);
                borrar_renglon (4);
                msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
                pos = BuscarArticulo (cod_art);
            }
            reg = LeerArticulo (pos);
            gotoxy (1,10);
            MostrarPrecioArticulo(reg);
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
    bool estado=true, grabo, grabo1;
    while (estado==true){
        cls ();
        devolucion ("AJUSTES","AZUL", ancho_formato, alto_formato);
        titulo ("AJUSTES","AZUL", ancho_formato);

        msj ("01. Eliminar ventas.", 2,ancho_formato); cout << endl ;
        msj ("02. Eliminar Articulos.", 2,ancho_formato); cout << endl ;
        msj ("03. Eliminar clientes.", 2,ancho_formato); cout << endl ;
        msj ("04. Recuperar datos.", 2,ancho_formato); cout << endl ;

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
                    devolucion ("CARÁCTER INCORRECTO","ROJO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","ROJO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;

                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpVentas();
                    grabo1=BkpDetalle ();
                    if (grabo==true && grabo1==true){
                        grabo = BorrarVentas ();
                        grabo1 = BorrarDetalle ();
                        if (grabo==true && grabo1==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '2':  /// BORRAR ARTICULOS
                cls ();
                setColor (RED);
                gotoxy (1,alto_formato/2);
                msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                while (opcion !='s' && opcion !='S' && opcion !='N' && opcion !='n'){
                    devolucion ("CARÁCTER INCORRECTO","ROJO", ancho_formato, alto_formato);
                    titulo ("CARÁCTER INCORRECTO","ROJO", ancho_formato);
                    anykey ();
                    cls ();
                    setColor (RED);
                    gotoxy (1,alto_formato/2);
                    msj ("ESTA SEGURO DE ELIMINAR LOS DATOS?(S/N): ",2,ancho_formato) ;cin >> opcion;
                }
                if (opcion== 's'|| opcion =='S'){
                    setColor(BLACK);
                    grabo=BkpArticulo();
                    if (grabo==true){
                        grabo = BorrarArticulo ();
                        if (grabo==true){
                            cls ();
                            devolucion ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato, alto_formato);
                            titulo ("SE ELIMINARON LOS DATOS","BLANCO", ancho_formato);
                            anykey ();
                        }
                        else {
                            cls ();
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '3':  /// BORRAR CLIENTES
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
                            devolucion ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                            titulo ("OCURRIÓ UN ERROR AL ELIMINAR LOS DATOS","ROJO", ancho_formato);
                            anykey ();
                        }
                    }
                }
                break ;}
            {case '4':
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
    bool estado=true, recupero, recupero1 ;
    while (estado==true){
        cls ();
        devolucion ("BACKUP","AZUL", ancho_formato, alto_formato);
        titulo ("BACKUP","AZUL", ancho_formato);

        msj ("01. Recuperar datos de ventas.", 2,ancho_formato); cout << endl ;
        msj ("02. Recuperar datos de artículos.", 2,ancho_formato); cout << endl ;
        msj ("03. Recuperar datos de clientes.", 2,ancho_formato); cout << endl ;

        guiones (ancho_formato);

        msj ("00. Volver atrás.", 2, ancho_formato, "ROJO"); cout << endl ;

        guiones (ancho_formato);

        msj ("Elija una opción: ", 2, ancho_formato) ;
        cin >> opcion_menu ;

        switch (opcion_menu) {
            case '1': /// Recuperar datos de ventas
                recupero=RecuperarVentas ();
                recupero1= RecuperarDetalle ();
                if(recupero==true&&recupero1==true){
                    BorrarBkpVentas ();
                    BorrarBkpDetalle ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato);
                    anykey ();

                }
                break ;
            case '2': /// Recuperar datos de articulos
                recupero=RecuperarArticulo ();
                if(recupero==true){
                    BorrarBkpArticulo ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato);
                    anykey ();

                }
                break ;
            case '3': /// Recuperar datos de clientes
                recupero=RecuperarClientes ();
                if(recupero==true){
                    BorrarBkpClientes ();
                    cls ();
                    devolucion ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato, alto_formato);
                    titulo ("SE RECUPERARON LOS DATOS","AZUL", ancho_formato);
                    anykey ();
                }
                else {
                    cls ();
                    devolucion ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato, alto_formato);
                    titulo ("OCURRIÓ UN ERROR AL RECUPERAR LOS DATOS","ROJO", ancho_formato);
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
