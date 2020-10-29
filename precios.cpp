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
#include "precios.h"
const char *ArchivoPrecios = "archivoprecios.dat" ;


float ValorVenta (int cod_art, int cant_venta){
    float valor ;
    precios reg ;
    FILE *f ;
    f=fopen (ArchivoPrecios, "rb");
    if (f==NULL){
        return - 2;
    }
    fread (&reg, sizeof (precios),1, f);
    fclose(f);
    if (cod_art ==100){
        valor = reg.andador_comun * cant_venta ;
        return valor ;
    }
    if (cod_art ==110){
        valor = reg.andador_ruedas* cant_venta ;
        return valor ;
    }
    if (cod_art ==120){
        valor = reg.andador_asiento * cant_venta ;
        return valor ;
    }
    if (cod_art ==200){
        valor = reg.cama_manual_eco * cant_venta ;
        return valor ;
    }
    if (cod_art ==210){
        valor = reg.cama_manual * cant_venta ;
        return valor ;
    }
    if (cod_art ==220){
        valor = reg.cama_electrica * cant_venta ;
        return valor ;
    }
    if (cod_art ==300){
        valor = reg.baston_1 * cant_venta ;
        return valor ;
    }
    if (cod_art ==310){
        valor = reg.baston_3 * cant_venta ;
        return valor ;
    }
    if (cod_art ==320){
        valor = reg.baston_4 * cant_venta ;
        return valor ;
    }
    if (cod_art ==400){
        valor = reg.silla_t * cant_venta ;
        return valor ;
    }
    if (cod_art ==410){
        valor = reg.silla_a * cant_venta ;
        return valor ;
    }
    if (cod_art ==420){
        valor = reg.silla_r * cant_venta ;
        return valor ;
    }
    return -1 ;
}

void CrearPrecios (){
    precios reg ;
    cls ();
    devolucion ("PRECIOS", "BLANCO",ancho_formato,alto_formato);
    guiones (ancho_formato,15);
    titulo ("PRECIOS", "BLANCO",ancho_formato);

    msj ("Andador común: $",2,ancho_formato);
    cin >> reg.andador_comun ;
    while (reg.andador_comun < 0 ){
        PrecioInvalido ();
        borrar_renglon (3);
        msj ("Andador común: $",2,ancho_formato);
        cin >> reg.andador_comun ;
    }

    msj ("Andador con ruedas: $",2,ancho_formato);
    cin >> reg.andador_ruedas ;
    while (reg.andador_ruedas < 0 ){
        PrecioInvalido ();
        borrar_renglon (4);
        msj ("Andador con ruedas: $",2,ancho_formato);
        cin >> reg.andador_ruedas ;
    }

    msj ("Andador con asiento: $",2,ancho_formato);
    cin >> reg.andador_asiento ;
    while (reg.andador_asiento < 0 ){
        PrecioInvalido ();
        borrar_renglon (5);
        msj ("Andador con asiento: $",2,ancho_formato);
        cin >> reg.andador_asiento ;
    }

    msj ("Cama económica: $",2,ancho_formato);
    cin >> reg.cama_manual_eco ;
    while (reg.cama_manual_eco < 0 ){
        PrecioInvalido ();
        borrar_renglon (6);
        msj ("Cama económica: $",2,ancho_formato);
        cin >> reg.cama_manual_eco ;
    }

    msj ("Cama manual: $",2,ancho_formato);
    cin >> reg.cama_manual ;
    while (reg.cama_manual < 0 ){
        PrecioInvalido ();
        borrar_renglon (7);
        msj ("Cama manual: $",2,ancho_formato);
        cin >> reg.cama_manual ;
    }

    msj ("Cama eléctrica: $",2,ancho_formato);
    cin >> reg.cama_electrica ;
    while (reg.cama_electrica < 0 ){
        PrecioInvalido ();
        borrar_renglon (8);
        msj ("Cama eléctrica: $",2,ancho_formato);
        cin >> reg.cama_electrica ;
    }

    msj ("Bastón de 1 apoyo: $",2,ancho_formato);
    cin >> reg.baston_1 ;
    while (reg.baston_1 < 0 ){
        PrecioInvalido ();
        borrar_renglon (9);
        msj ("Bastón de 1 apoyo: $",2,ancho_formato);
        cin >> reg.baston_1 ;
    }

    msj ("Bastón de 3 apoyos: $",2,ancho_formato);
    cin >> reg.baston_3 ;
    while (reg.baston_3 < 0 ){
        PrecioInvalido ();
        borrar_renglon (10);
        msj ("Bastón de 3 apoyos: $",2,ancho_formato);
        cin >> reg.baston_3 ;
    }

    msj ("Bastón de 4 apoyos: $",2,ancho_formato);
    cin >> reg.baston_4 ;
    while (reg.baston_4 < 0 ){
        PrecioInvalido ();
        borrar_renglon (11);
        msj ("Bastón de 4 apoyos: $",2,ancho_formato);
        cin >> reg.baston_4 ;
    }

    msj ("Silla de transporte: $",2,ancho_formato);
    cin >> reg.silla_t ;
    while (reg.silla_t < 0 ){
        PrecioInvalido ();
        borrar_renglon (12);
        msj ("Silla de transporte: $",2,ancho_formato);
        cin >> reg.silla_t ;
    }

    msj ("Silla de autotransporte: $",2,ancho_formato);
    cin >> reg.silla_a ;
    while (reg.silla_a < 0 ){
        PrecioInvalido ();
        borrar_renglon (13);
        msj ("Silla de autotransporte: $",2,ancho_formato);
        cin >> reg.silla_a ;
    }

    msj ("Silla reforzada: $",2,ancho_formato);
    cin >> reg.silla_r ;
    while (reg.silla_r < 0 ){
        PrecioInvalido ();
        borrar_renglon (14);
        msj ("Silla reforzada: $",2,ancho_formato);
        cin >> reg.silla_r ;
    }

    FILE*f ;
    f=fopen (ArchivoPrecios, "rb+") ;
    if (f==NULL){
        return ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg, sizeof (precios),1,f);
    fclose(f);
}

void PrecioInvalido (){
    devolucion ("PRECIO INVÁLIDO", "BLANCO",ancho_formato, alto_formato);
    titulo ("PRECIO INVÁLIDO", "BLANCO",ancho_formato);
    anykey ();
    devolucion ("PRECIOS", "BLANCO",ancho_formato, alto_formato);
    titulo ("PRECIOS", "BLANCO",ancho_formato);
}

precios LeerPrecio (){
    precios reg ;

    FILE*f ;
    f=fopen (ArchivoPrecios,"rb");
    if (f==NULL){
        return reg ;
    }
    fseek (f,0,SEEK_SET);
    fread (&reg, sizeof (precios), 1,f);
    fclose (f);
    return reg ;
}

void CambiarPrecio (){
    ///TO DO: FUNCION DE PRECIOS

    int cod_art ;
    char opcion ;
    float valor ;
    bool estado = true ;
    cls ();

    devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
    titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);

    msj ("Ingrese el código del artículo: ",2,ancho_formato) ; cin >> cod_art;
    while (cod_art!=100 && cod_art!=110 && cod_art!=120 && cod_art!=200 && cod_art!=210 && cod_art!=220 && cod_art!=300 && cod_art!=310 &&cod_art!=320 && cod_art!=400 &&cod_art!=410 &&cod_art!=420){
        devolucion ("CÓDIGO DE ARTICULO INCORRECTO","ROJO", ancho_formato, alto_formato);
        titulo ("CÓDIGO DE ARTICULO INCORRECTO","ROJO", ancho_formato);
        anykey ();
        devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
        titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
        borrar_renglon (3);
        msj ("Ingrese el código del artículo: ",2,ancho_formato) ; cin >> cod_art;
    }
    msj ("Ingrese el nuevo monto: $",2,ancho_formato) ; cin >> valor;
    while (valor <0){
        devolucion ("MONTO INCORRECTO","ROJO", ancho_formato, alto_formato);
        titulo ("MONTO INCORRECTO","ROJO", ancho_formato);
        anykey ();
        devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
        titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
        borrar_renglon (4);
        msj ("Ingrese el nuevo monto: $",2,ancho_formato) ; cin >> valor;
    }
    guiones (ancho_formato, alto_formato/2-1);
    guiones (ancho_formato, alto_formato/2+2);
    gotoxy(1,alto_formato/2);
    msj ("¿Confirmar cambio?",2,ancho_formato,"BLANCO") ;
    msj ("(S/N):", 2,ancho_formato); cin >> opcion ;
    while (estado==true){
        switch (opcion){
        case 'S':
        case 's':
            cls ();
            devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
            titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
            gotoxy (1, alto_formato/2);
            msj ("Cambio realizado.",2,ancho_formato);
            anykey ();
            estado =false ;
            break ;
        case 'n':
        case 'N':
            cls ();
            devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
            titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
            gotoxy (1, alto_formato/2);
            msj ("Cambio cancelado.",2,ancho_formato);
            anykey ();
            return;
            break ;
        default :
            devolucion ("CARÁCTER INCORRECTO","ROJO", ancho_formato, alto_formato);
            titulo ("CARÁCTER INCORRECTO","ROJO", ancho_formato);
            anykey();
            devolucion ("CAMBIAR PRECIO","BLANCO", ancho_formato, alto_formato);
            titulo ("CAMBIAR PRECIO","BLANCO", ancho_formato);
            borrar_renglon (alto_formato/2+1);
            borrar_renglon (alto_formato/2);
            msj ("¿Confirmar cambio?",2,ancho_formato,"BLANCO") ;
            msj ("(S/N):", 2,ancho_formato); cin >> opcion ;
            break ;
        }
    }

    precios reg = LeerPrecio ();
    switch (cod_art){
    case 100:
        reg.andador_comun = valor ;
        break;
    case 110:
        reg.andador_ruedas = valor ;
        break;
    case 120:
        reg.andador_asiento = valor ;
        break;
    case 200:
        reg.cama_manual_eco = valor ;
        break;
    case 210:
        reg.cama_manual = valor ;
        break;
    case 220:
        reg.cama_electrica = valor ;
        break;
    case 300:
        reg.baston_1 = valor ;
        break;
    case 310:
        reg.baston_3 = valor ;
        break;
    case 320:
        reg.baston_4 = valor ;
        break;
    case 400:
        reg.silla_t = valor ;
        break;
    case 410:
        reg.silla_a = valor ;
        break;
    case 420:
        reg.silla_r = valor ;
        break;
    default:
        return ;
        break ;
    }
    FILE *f ;
    f=fopen (ArchivoPrecios,"rb+");
    if (f==NULL){
        return ;
    }
    fseek (f,0,SEEK_SET);
    fwrite (&reg, sizeof (precios), 1,f);
    fclose (f);
}

void MostrarListaPrecios (){
    precios reg;
    FILE *f;
    f=fopen (ArchivoPrecios, "rb");
    if (f==NULL){
        return ;
    }
    fread (&reg, sizeof(precios),1,f);
    fclose (f);
    cls ();
    devolucion ("LISTA DE PRECIOS", "BLANCO", ancho_formato,alto_formato);
    titulo ("LISTA DE PRECIOS", "BLANCO", ancho_formato);
    cout << endl ;
    msj ("   ARTÍCULO       | COD | VALOR",2,ancho_formato); cout <<endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;
    msj ("Andador común       | 100 | $",2,ancho_formato-6) ;cout << reg.andador_comun << endl ;
    msj ("Andador c/ruedas    | 110 | $",2,ancho_formato-6) ;cout << reg.andador_ruedas << endl ;
    msj ("Andador c/asiento   | 120 | $",2,ancho_formato-6) ;cout << reg.andador_asiento << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Cama económica      | 200 | $",2,ancho_formato-6) ;cout << reg.cama_manual_eco << endl ;
    msj ("Cama manual         | 210 | $",2,ancho_formato-6) ;cout << reg.cama_manual << endl ;
    msj ("Cama eléctrica      | 220 | $",2,ancho_formato-6) ;cout << reg.cama_electrica << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Bastón 1 apoyo      | 300 | $",2,ancho_formato-6) ;cout << reg.baston_1 << endl ;
    msj ("Bastón 3 apoyos     | 310 | $",2,ancho_formato-6) ;cout << reg.baston_3 << endl ;
    msj ("Bastón 4 apoyos     | 320 | $",2,ancho_formato-6) ;cout << reg.baston_4 << endl ;
    msj ("----------------------------------",2,ancho_formato-1); cout << endl ;

    msj ("Silla de transporte | 400 | $",2,ancho_formato-6) ;cout << reg.silla_t << endl ;
    msj ("Silla autotransp.   | 410 | $",2,ancho_formato-6) ;cout << reg.silla_a << endl ;
    msj ("Silla reforzada     | 420 | $",2,ancho_formato-6) ;cout << reg.silla_r << endl ;
    anykey ();
}

