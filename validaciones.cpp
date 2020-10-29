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

int ValidarTexto (char* texto){
    if (texto[0]== ' ' || texto[0]==NULL){
        return 0 ;
    }
    return 1 ;
}

int ValidarMail (char *texto){
    int cont =0,x,tam;
    if (texto[0]== ' ' || texto[0]==NULL){
        return 0 ;
    }
    tam=strlen (texto);
    for (x=3 ; x<tam-6 ; x++){
        if (texto[x]=='@'){
            cont ++;
        }
    }
    if (cont == 1){
        return 1 ;
    }
    return 0 ;
}



int validar_fecha(int d, int m, int y){
    int i;
    bool bisiesto = false;
    //comprobamos si el año es bisiesto
    if(y%4==0 && y%100!=100 || y%400==0){
        bisiesto = true;
    }
    //comprobamos que los datos ingresados esten en un rango valido
    if(d>0 && d<32 && m>0 && m<13 && y>0){
        if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
           return 1 ;        // Fecha valida
        }else{
            if(m==2 && d<30 && bisiesto)
                return 1 ;   // Fecha valida
            else if(m==2 && d<29 && !bisiesto)
                return 1 ;   // Fecha valida
            else if(m!=2 && d<31)
                return 1 ;   // Fecha valida
            else
                return 0 ;  // Fecha no valida
        }
    }
    else {
        return 0 ;// Fecha no valida
    }
}

int validar_edad (int d, int m, int y, int ed){
    int edad ;
    if (validar_fecha(d,m,y)!=0){
        return -0 ; /// fecha invalida
    }
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    edad = 1900+tmPtr->tm_year - y ;
    if (m>tmPtr->tm_mon+1){
        edad -- ;
    }else {
        if(m==tmPtr->tm_mon+1){
            if(d>tmPtr->tm_mday){
                edad -- ;
            }
        }
    }
    if (edad>=ed && edad < 100 ){
        return 1 ; /// fecha y edad valida
    }
    else {
        if (edad<=0 || edad>100){
            return -1 ; /// edad menor a 0 años
        }
        return -2 ; /// edad menor
    }
}

fecha CargarFechaActual (){
    struct fecha fecha_actual ;
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;

    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

    fecha_actual.dia = tmPtr->tm_mday ;
    fecha_actual.mes = tmPtr->tm_mon+1 ;
    fecha_actual.anio = 1900+tmPtr->tm_year ;
    return fecha_actual ;

    ///       tmPtr->tm_mday // dia
    ///       tmPtr->tm_mon+1 // mes
    ///       1900+tmPtr->tm_year // anio
}
