#include <iostream>
#include <cstdlib>
using namespace std ;
#include "rlutil.h"
using namespace rlutil;
#include "clases.h"
#include "stock.h"
#include "interfaz.h"
/// INTERFAZ VERDE
const char *ArchivoStock = "archivostock.dat" ;


void CambiarTodoStock (){
    stock reg ;
    char opcion;
    cls ();
    devolucion ("CAMBIO DE STOCK", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,15);
    titulo ("CAMBIO DE STOCK", "VERDE",ancho_formato);

    msj ("Andador común: ",2,ancho_formato);
    cin >> reg.andador_comun ;
    while (reg.andador_comun < 0 ){
        StockInvalido ();
        borrar_renglon (3);
        msj ("Andador común: ",2,ancho_formato);
        cin >> reg.andador_comun ;
    }

    msj ("Andador con ruedas: ",2,ancho_formato);
    cin >> reg.andador_ruedas ;
    while (reg.andador_ruedas < 0 ){
        StockInvalido ();
        borrar_renglon (4);
        msj ("Andador con ruedas: ",2,ancho_formato);
        cin >> reg.andador_ruedas ;
    }

    msj ("Andador con asiento: ",2,ancho_formato);
    cin >> reg.andador_asiento ;
    while (reg.andador_asiento < 0 ){
        StockInvalido ();
        borrar_renglon (5);
        msj ("Andador con asiento: ",2,ancho_formato);
        cin >> reg.andador_asiento ;
    }

    msj ("Cama económica: ",2,ancho_formato);
    cin >> reg.cama_manual_eco ;
    while (reg.cama_manual_eco < 0 ){
        StockInvalido ();
        borrar_renglon (6);
        msj ("Cama económica: ",2,ancho_formato);
        cin >> reg.cama_manual_eco ;
    }

    msj ("Cama manual: ",2,ancho_formato);
    cin >> reg.cama_manual ;
    while (reg.cama_manual < 0 ){
        StockInvalido ();
        borrar_renglon (7);
        msj ("Cama manual: ",2,ancho_formato);
        cin >> reg.cama_manual ;
    }

    msj ("Cama eléctrica: ",2,ancho_formato);
    cin >> reg.cama_electrica ;
    while (reg.cama_electrica < 0 ){
        StockInvalido ();
        borrar_renglon (8);
        msj ("Cama eléctrica: ",2,ancho_formato);
        cin >> reg.cama_electrica ;
    }

    msj ("Bastón de 1 apoyo: ",2,ancho_formato);
    cin >> reg.baston_1 ;
    while (reg.baston_1 < 0 ){
        StockInvalido ();
        borrar_renglon (9);
        msj ("Bastón de 1 apoyo: ",2,ancho_formato);
        cin >> reg.baston_1 ;
    }

    msj ("Bastón de 3 apoyos: ",2,ancho_formato);
    cin >> reg.baston_3 ;
    while (reg.baston_3 < 0 ){
        StockInvalido ();
        borrar_renglon (10);
        msj ("Bastón de 3 apoyos: ",2,ancho_formato);
        cin >> reg.baston_3 ;
    }

    msj ("Bastón de 4 apoyos: ",2,ancho_formato);
    cin >> reg.baston_4 ;
    while (reg.baston_4 < 0 ){
        StockInvalido ();
        borrar_renglon (11);
        msj ("Bastón de 4 apoyos: ",2,ancho_formato);
        cin >> reg.baston_4 ;
    }

    msj ("Silla de transporte: ",2,ancho_formato);
    cin >> reg.silla_t ;
    while (reg.silla_t < 0 ){
        StockInvalido ();
        borrar_renglon (12);
        msj ("Silla de transporte: ",2,ancho_formato);
        cin >> reg.silla_t ;
    }

    msj ("Silla de autotransporte: ",2,ancho_formato);
    cin >> reg.silla_a ;
    while (reg.silla_a < 0 ){
        StockInvalido ();
        borrar_renglon (13);
        msj ("Silla de autotransporte: ",2,ancho_formato);
        cin >> reg.silla_a ;
    }

    msj ("Silla reforzada: ",2,ancho_formato);
    cin >> reg.silla_r ;
    while (reg.silla_r < 0 ){
        StockInvalido ();
        borrar_renglon (14);
        msj ("Silla reforzada: ",2,ancho_formato);
        cin >> reg.silla_r ;
    }
    gotoxy (1,18);
    msj ("¿Está seguro del cambio a realizar?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N'){
        devolucion ("CARÁCTER INVÁLIDO","ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO", ancho_formato);
        anykey ();
        devolucion ("CAMBIO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("CAMBIO DE STOCK", "VERDE",ancho_formato);
        gotoxy (1,18);
        msj ("¿Está seguro del cambio a realizar?",2,ancho_formato,"ROJO");
        borrar_renglon (19);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    if (opcion == 's' || opcion == 'S'){
        FILE*f ;
        f=fopen (ArchivoStock, "rb+") ;
        if (f==NULL){
            return ;
        }
        fseek (f,0,SEEK_SET);
        fwrite (&reg, sizeof (stock),1,f);
        fclose(f);
        cls ();
        devolucion ("  ","VERDE",ancho_formato,alto_formato);
        titulo ("  ", "VERDE", ancho_formato);
        gotoxy (1,alto_formato/2);
        msj ("SE REALIZÓ EL CAMBIO", 2,ancho_formato,"VERDE");
        anykey ();
    }else {
        cls ();
        devolucion ("  ","VERDE",ancho_formato,alto_formato);
        titulo ("  ", "VERDE", ancho_formato);
        gotoxy (1,alto_formato/2);
        msj ("NO SE REALIZÓ EL CAMBIO", 2,ancho_formato,"ROJO");
        anykey ();
    }











}

bool CambiarStockArticulo (int cod_art, int cantidad,bool estado){
    stock reg ;
    FILE *f ;
    f = fopen (ArchivoStock,"rb+");
    if (f==NULL){
        return false ;
    }
    fseek (f, 0, SEEK_SET);
    fread (&reg,sizeof (stock),1,f);

    switch (cod_art){
    case 100:
        reg.andador_comun += cantidad ;
        reg.an_co = estado ;
        break ;
    case 110:
        reg.andador_ruedas += cantidad ;
        reg.an_ru = estado ;

        break ;
    case 120:
        reg.andador_asiento += cantidad ;
        reg.an_as = estado ;

        break ;
    case 200:
        reg.cama_manual_eco += cantidad ;
        reg.ca_eco = estado ;

        break ;
    case 210:
        reg.cama_manual += cantidad ;
        reg.ca_ma = estado ;

        break ;
    case 220:
        reg.cama_electrica += cantidad ;
        reg.ca_el = estado ;

        break ;
    case 300:
        reg.baston_1 += cantidad ;
        reg.ba_1 = estado ;

        break ;
    case 310:
        reg.baston_3 += cantidad ;
        reg.ba_3 = estado ;

        break ;
    case 320:
        reg.baston_4 += cantidad ;
        reg.ba_4 = estado ;

        break ;
    case 400:
        reg.silla_t += cantidad ;
        reg.si_t = estado ;

        break ;
    case 410:
        reg.silla_a += cantidad ;
        reg.si_a = estado ;

        break ;
    case 420:
        reg.silla_r += cantidad ;
        reg.si_r = estado ;
        break ;
    default :
        cout << "ENTRO A DEFAULT" ;
        break ;
    }
    fseek(f,0,SEEK_SET);
    fwrite (&reg,sizeof (stock),1,f);
    fclose (f);
    return true ;
}

void MenuAgregarStock (){
    int cod_art, cantidad;
    bool grabo, estado ;
    char opcion;
    cls ();
    devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,7);
    titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
    cout << endl ;

    msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
    while (cod_art!=100 && cod_art!=110 && cod_art!=120 && cod_art!=200 && cod_art!=210 && cod_art!=220 && cod_art!=300 && cod_art!=310 && cod_art!=320 && cod_art!=400 &&cod_art!=410 && cod_art!=420){
        devolucion ("CÓDIGO INCORRECTO","ROJO",ancho_formato,alto_formato);
        titulo ("CÓDIGO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
        borrar_renglon (4);
        msj ("Ingrese número de artículo: ", 2, ancho_formato) ;
        cin >> cod_art ;
    }

    msj ("Ingrese cantidad a aumentar: ", 2, ancho_formato) ; cin >> cantidad;
    while (cantidad <= 0){
        devolucion ("SE DEBE AUMENTAR AL MENOS 1","ROJO",ancho_formato,alto_formato);
        titulo ("SE DEBE AUMENTAR AL MENOS 1","ROJO",ancho_formato);
        anykey ();
        devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
        borrar_renglon (5);
        msj ("Ingrese cantidad a aumentar: ", 2, ancho_formato) ;
        cin >> cantidad ;
    }
    gotoxy (1,9);
    MostrarStockArticulo (cod_art);
    guiones (ancho_formato);
    cout << endl << endl ;
    msj ("¿Está seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("AGREGADO DE STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("AGREGADO DE STOCK", "VERDE",ancho_formato);
        borrar_renglon (16);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    estado = BuscarEstadoArt (cod_art);
    if (opcion=='s' || opcion=='S'){
        grabo = CambiarStockArticulo (cod_art,cantidad,estado);
        if (grabo ==true){
            cls ();
            devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato-4)/2);
            MostrarStockArticulo (cod_art);
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato-4)/2);
        MostrarStockArticulo (cod_art);
    }

}

void MenuReducirStock (){
    int cod_art, cantidad, stock_actual;
    bool grabo, estado ;
    char opcion;
    cls ();
    devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,7);
    titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
    cout << endl ;

    msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
    while (cod_art!=100 && cod_art!=110 && cod_art!=120 && cod_art!=200 && cod_art!=210 && cod_art!=220 && cod_art!=300 && cod_art!=310 && cod_art!=320 && cod_art!=400 &&cod_art!=410 && cod_art!=420){
        devolucion ("CÓDIGO INCORRECTO","ROJO",ancho_formato,alto_formato);
        titulo ("CÓDIGO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
        borrar_renglon (4);
        msj ("Ingrese número de artículo: ", 2, ancho_formato) ;
        cin >> cod_art ;
    }
    stock_actual = BuscarStock (cod_art);
    msj ("Ingrese cantidad a reducir: ", 2, ancho_formato) ; cin >> cantidad;
    while (cantidad <= 0 || cantidad > stock_actual){
        if (cantidad <= 0){
            devolucion ("SE DEBE REDUCIR AL MENOS 1","ROJO",ancho_formato,alto_formato);
            titulo ("SE DEBE REDUCIR AL MENOS 1","ROJO",ancho_formato);
        }else {
            devolucion ("EL STOCK ES MENOR AL DE LA CANTIDAD A REDUCIR","ROJO",ancho_formato,alto_formato);
            titulo ("EL STOCK ES MENOR AL DE LA CANTIDAD A REDUCIR","ROJO",ancho_formato);
        }
        anykey ();
        devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
        borrar_renglon (5);
        msj ("Ingrese cantidad a reducir: ", 2, ancho_formato) ;
        cin >> cantidad ;
    }
    gotoxy (1,9);
    MostrarStockArticulo (cod_art);
    guiones (ancho_formato);
    cout << endl << endl ;

    msj ("¿Está seguro de realizar el cambio?",2,ancho_formato,"ROJO");
    msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    while (opcion != 's' && opcion != 'S' &&opcion != 'N' &&opcion != 'n'){
        devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
        titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
        anykey ();
        devolucion ("REDUCIR STOCK", "VERDE",ancho_formato,alto_formato);
        titulo ("REDUCIR STOCK", "VERDE",ancho_formato);
        borrar_renglon (16);
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
    }
    estado = BuscarEstadoArt (cod_art);
    if (opcion=='s' || opcion=='S'){
        grabo = CambiarStockArticulo (cod_art,cantidad*-1,estado);
        if (grabo ==true){
            cls ();
            devolucion ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato,alto_formato);
            titulo ("SE REALIZÓ EL CAMBIO","VERDE",ancho_formato);
            gotoxy (1,(alto_formato-4)/2);
            MostrarStockArticulo (cod_art);
        }else{
            cls ();
            devolucion (" ","ROJO",ancho_formato,alto_formato);
            titulo (" ","ROJO",ancho_formato);
            gotoxy (1,alto_formato/2);
            msj ("No poseé tantos artículos",2,ancho_formato,"ROJO");
            anykey ();
        }
    }else {
        cls ();
        devolucion ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato,alto_formato);
        titulo ("NO SE REALIZÓ EL CAMBIO","ROJO",ancho_formato);
        gotoxy (1,(alto_formato-4)/2);
        MostrarStockArticulo (cod_art);
    }
}

void MenuEstado (){
    int cod_art;
    char opcion ;
    bool estado ;
    cls ();
    devolucion ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
    guiones (ancho_formato,6);
    titulo ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato);
    cout << endl ;
    msj ("Ingrese número de artículo: ", 2, ancho_formato) ; cin >> cod_art;
    while (cod_art!=100 && cod_art!=110 && cod_art!=120 && cod_art!=200 && cod_art!=210 && cod_art!=220 && cod_art!=300 && cod_art!=310 && cod_art!=320 && cod_art!=400 &&cod_art!=410 && cod_art!=420){
        devolucion ("CÓDIGO INCORRECTO","ROJO",ancho_formato,alto_formato);
        titulo ("CÓDIGO INCORRECTO","ROJO",ancho_formato);
        anykey ();
        devolucion ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
        titulo ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato);
        borrar_renglon (4);
        msj ("Ingrese número de artículo: ", 2, ancho_formato) ;
        cin >> cod_art ;
    }
    gotoxy (1,7);
    estado = BuscarEstadoArt (cod_art);
    if (estado==false){
        MostrarStockArticulo (cod_art);
        cout << endl ;
        guiones (ancho_formato);
        msj ("¿Desea reactivar el artículo?",2,ancho_formato,"ROJO");cout << endl ;
        msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
        while (opcion != 's' && opcion != 'S' && opcion != 'N' && opcion != 'n'){
            devolucion ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato,alto_formato);
            titulo ("CARÁCTER INVÁLIDO", "ROJO",ancho_formato);
            anykey ();
            devolucion ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato,alto_formato);
            titulo ("ALTA/BAJA DE ARTÍCULO", "VERDE",ancho_formato);
            borrar_renglon (12);
            msj ("(S/N): ",2,ancho_formato); cin >> opcion ;
        }
        if (opcion == 's'|| opcion == 'S'){



        }
    }else {
    }


}

void StockInvalido (){
    devolucion ("STOCK INVÁLIDO", "ROJO",ancho_formato, alto_formato);
    titulo ("STOCK INVÁLIDO", "ROJO",ancho_formato);
    anykey ();
    devolucion ("STOCK", "VERDE",ancho_formato, alto_formato);
    titulo ("STOCK", "VERDE",ancho_formato);
}

void MostrarListaStock (){
    stock reg;
    FILE *f;
    f=fopen (ArchivoStock, "rb");
    if (f==NULL){
        return ;
    }
    fread (&reg, sizeof(stock),1,f);
    fclose (f);
    cls ();
    devolucion ("LISTA DE STOCK", "VERDE", ancho_formato,alto_formato);
    titulo ("LISTA DE STOCK", "VERDE", ancho_formato);
    cout << endl ;
    msj ("   ARTÍCULO       | COD | STOCK",2,ancho_formato); cout <<endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;
    msj ("Andador común       | 100 |  ",2,ancho_formato-6) ;cout << reg.andador_comun << endl ;
    msj ("Andador c/ruedas    | 110 |  ",2,ancho_formato-6) ;cout << reg.andador_ruedas << endl ;
    msj ("Andador c/asiento   | 120 |  ",2,ancho_formato-6) ;cout << reg.andador_asiento << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Cama económica      | 200 |  ",2,ancho_formato-6) ;cout << reg.cama_manual_eco << endl ;
    msj ("Cama manual         | 210 |  ",2,ancho_formato-6) ;cout << reg.cama_manual << endl ;
    msj ("Cama eléctrica      | 220 |  ",2,ancho_formato-6) ;cout << reg.cama_electrica << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Bastón 1 apoyo      | 300 |  ",2,ancho_formato-6) ;cout << reg.baston_1 << endl ;
    msj ("Bastón 3 apoyos     | 310 |  ",2,ancho_formato-6) ;cout << reg.baston_3 << endl ;
    msj ("Bastón 4 apoyos     | 320 |  ",2,ancho_formato-6) ;cout << reg.baston_4 << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Silla de transporte | 400 |  ",2,ancho_formato-6) ;cout << reg.silla_t << endl ;
    msj ("Silla autotransp.   | 410 |  ",2,ancho_formato-6) ;cout << reg.silla_a << endl ;
    msj ("Silla reforzada     | 420 |  ",2,ancho_formato-6) ;cout << reg.silla_r << endl ;
    anykey ();
}

void MostrarStockArticulo (int cod_art){
    stock reg;
    FILE *f;
    f=fopen (ArchivoStock, "rb");
    if (f==NULL){
        return ;
    }
    fread (&reg, sizeof(stock),1,f);
    fclose (f);

    msj ("   ARTÍCULO       | COD | STOCK",2,ancho_formato); cout <<endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;
    switch (cod_art){
    case 100:
        msj ("Andador común       | 100 |  ",2,ancho_formato-6) ;cout << reg.andador_comun ;
        if (reg.an_co==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 110:
        msj ("Andador c/ruedas    | 110 |  ",2,ancho_formato-6) ;cout << reg.andador_ruedas ;
        if (reg.an_ru==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 120:
        msj ("Andador c/asiento   | 120 |  ",2,ancho_formato-6) ;cout << reg.andador_asiento  ;
        if (reg.an_as==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 200:
        msj ("Cama económica      | 200 |  ",2,ancho_formato-6) ;cout << reg.cama_manual_eco  ;
        if (reg.ca_eco==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 210:
        msj ("Cama manual         | 210 |  ",2,ancho_formato-6) ;cout << reg.cama_manual  ;
        if (reg.ca_ma==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 220:
        msj ("Cama eléctrica      | 220 |  ",2,ancho_formato-6) ;cout << reg.cama_electrica  ;
        if (reg.ca_el==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 300:
        msj ("Bastón 1 apoyo      | 300 |  ",2,ancho_formato-6) ;cout << reg.baston_1  ;
        if (reg.ba_1==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 310:
        msj ("Bastón 3 apoyos     | 310 |  ",2,ancho_formato-6) ;cout << reg.baston_3  ;
        if (reg.ba_3==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 320:
        msj ("Bastón 4 apoyos     | 320 |  ",2,ancho_formato-6) ;cout << reg.baston_4 ;
        if (reg.ba_4==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 400:
        msj ("Silla de transporte | 400 |  ",2,ancho_formato-6) ;cout << reg.silla_t ;
        if (reg.si_t==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 410:
        msj ("Silla autotransp.   | 410 |  ",2,ancho_formato-6) ;cout << reg.silla_a ;
        if (reg.si_a==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    case 420:
        msj ("Silla reforzada     | 420 |  ",2,ancho_formato-6) ;cout << reg.silla_r  ;
        if (reg.si_r==true){
            cout << "\t" ; setBackgroundColor (GREEN); cout << "   " << endl ;
        }else {
            cout << "\t" ; setBackgroundColor (RED); cout << "   " << endl ;
        }
        setBackgroundColor (BLACK);
        break ;
    default :
        cout << "ENTRO A DEFAULT" ;
        break ;
    }

    anykey ();
}

int BuscarStock (int cod_art){
    stock reg ;
    FILE *f ;
    f = fopen (ArchivoStock,"rb");
    if (f==NULL){
        return false ;
    }
    fseek (f, 0, SEEK_SET);
    fread (&reg,sizeof (stock),1,f);
    fclose (f);

    switch (cod_art){
    case 100:
        return reg.andador_comun ;
        break ;
    case 110:
        return reg.andador_ruedas ;
        break ;
    case 120:
        return reg.andador_asiento ;
        break ;
    case 200:
        return reg.cama_manual_eco;
        break ;
    case 210:
        return reg.cama_manual ;
        break ;
    case 220:
        return reg.cama_electrica ;
        break ;
    case 300:
        return reg.baston_1 ;
        break ;
    case 310:
        return reg.baston_3 ;
        break ;
    case 320:
        return reg.baston_4 ;
        break ;
    case 400:
        return reg.silla_t ;
        break ;
    case 410:
        return reg.silla_a ;
        break ;
    case 420:
        return reg.silla_r ;
        break ;
    default :
        return -1 ;
        break ;
    }
}

bool BuscarEstadoArt (int cod_art){
    stock reg ;
    FILE *f ;
    f = fopen (ArchivoStock,"rb");
    if (f==NULL){
        return false ;
    }
    fseek (f, 0, SEEK_SET);
    fread (&reg,sizeof (stock),1,f);
    fclose (f);

    switch (cod_art){
    case 100:
        return reg.an_co ;
        break ;
    case 110:
        return reg.an_ru ;
        break ;
    case 120:
        return reg.an_as;
        break ;
    case 200:
        return reg.ca_eco;
        break ;
    case 210:
        return reg.ca_ma ;
        break ;
    case 220:
        return reg.ca_el;
        break ;
    case 300:
        return reg.ba_1 ;
        break ;
    case 310:
        return reg.ba_3 ;
        break ;
    case 320:
        return reg.ba_4 ;
        break ;
    case 400:
        return reg.si_t ;
        break ;
    case 410:
        return reg.si_a ;
        break ;
    case 420:
        return reg.si_r ;
        break ;
    default :
        return -1 ;
        break ;
    }
}


