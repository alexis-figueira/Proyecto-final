#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "interfaz.h"
///const int ancho_formato = 80, alto_formato=25 ;

void initUI() {
    system("mode con: cols=80 lines=25");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL, "spanish");
}

void MostrarFecha (int ubicacion, int ancho){
    int pos, x;

    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;

    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

    ///       tmPtr->tm_mday // dia
    ///       tmPtr->tm_mon+1 // mes
    ///       1900+tmPtr->tm_year // anio

    switch (ubicacion){
    case 1 :
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << 1900+tmPtr->tm_year ;
        break ;
    case 2 :
        pos =(ancho-10)/2 ;
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << 1900+tmPtr->tm_year ;
        break;
    case 3 :
        pos = (ancho-10);
        for (x=1 ; x<=pos ; x++){
        cout << " " ;
        }
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << 1900+tmPtr->tm_year ;
        break;
    }

}

void func_hora(){
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;

    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

    printf("FECHA ACTUAL \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
    strftime(cad, 80, "%A %d de %B de %Y", tmPtr);
    printf("\n\n%s", cad);

    ///       tmPtr->tm_mday // dia
    ///       tmPtr->tm_mon+1 // mes
    ///       1900+tmPtr->tm_year // anio
    ///       tmPtr->tm_hour // hora
    ///       tmPtr->tm_min // min
    ///       tmPtr->tm_sec // seg

}

void borrar_restopantalla(int y){
    int a, b ;
    for (a=0; a<ancho_formato; a++){
        for (b=y ; b<alto_formato ; b++){
            gotoxy (a,b);
            cout << " " ;
        }
    }
    gotoxy (1,y);
}

void borrar_restorenglon(int x, int y){
    int i ;
    for (i=x ; i<ancho_formato; i++){
        gotoxy(i, y);
        cout << " " ;
    }
    gotoxy(x,y);
}

void borrar_renglon(int y){
    int x ;
    for (x=1 ; x<=ancho_formato; x++){
        gotoxy(x, y);
        cout << " " ;
    }
    gotoxy(1,y);
}

void devolucion (const char *msj, int ancho, int renglon){
    int tam ;
    guiones (ancho, renglon -1);
    gotoxy (1,renglon);
    tam = strlen (msj);
    tam = (ancho-tam)/2;
    gotoxy (tam,renglon);
    cout << msj;
    setBackgroundColor(BLACK);
}

void devolucion(const char * msj, const char *color, int ancho, int renglon){
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" , *magenta="MAGENTA", *blanco="BLANCO", *amarillo= "AMARILLO";
    int tam ;
    guiones (ancho, renglon -1);
    gotoxy (1,renglon);
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                if(strcmp(color, magenta)==0){
                    setBackgroundColor(MAGENTA);
                }else {
                    if(strcmp(color, blanco)==0){
                        setColor(BLACK);
                        setBackgroundColor(WHITE);
                    }else {
                        if (strcmp(color, amarillo)==0){
                            setColor (BLACK);
                            setBackgroundColor (YELLOW);
                        }
                    }
                }
            }
        }
    }
    int x ;
    for (x=1 ; x<=ancho ; x++){
        gotoxy (x,renglon);
        cout << " " ;
    }
    tam =strlen (msj);
    tam = (ancho-tam)/2;
    gotoxy (tam,renglon);
    cout << msj;
    setBackgroundColor(BLACK);
    if(strcmp(color, blanco)==0){
        setColor(WHITE);
    }else {
        if(strcmp(color, amarillo)==0){
        setColor(WHITE);
        }
    }
}

void titulo(const char * msj, const char *color, int ancho){
    int x, pos , tam;
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" , *magenta="MAGENTA", *blanco="BLANCO", *amarillo="AMARILLO";
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                if(strcmp(color, magenta)==0){
                    setBackgroundColor(MAGENTA);
                }else {
                    if(strcmp(color, blanco)==0){
                        setColor(BLACK);
                        setBackgroundColor(WHITE);
                    }else {
                        if (strcmp (color,amarillo)==0){
                            setColor (BLACK);
                            setBackgroundColor(YELLOW);
                        }
                    }
                }
            }
        }
    }
    for (x=1 ; x<=ancho ; x++){
        gotoxy (x,1);
        cout << " " ;
    }
    tam= strlen (msj);
    pos =(ancho-tam)/2 ;
    gotoxy (pos,1);
    cout << msj ;
    setBackgroundColor(BLACK);
    cout << endl ;
    if(strcmp(color, blanco)==0){
        setColor(WHITE);
    }else {
        if(strcmp(color, amarillo)==0){
        setColor(WHITE);
        }
    }

    guiones (ancho);
}
/* TITULO SIN COLOR
void titulo(const char * msj, int ancho){
    setBackgroundColor(BLUE);
    int x, pos , tam;
    for (x=1 ; x<=ancho ; x++){
        gotoxy (x,1);
        cout << " " ;
    }
    tam= strlen (msj);
    pos =(ancho-tam)/2 ;
    gotoxy (pos,1);
    cout << msj ;
    setBackgroundColor(BLACK);
    cout << endl ;
}
*/
void guiones(int ancho){
    int x;
    for (x=1 ; x <=ancho ; x++ ){
        cout << "-" ;
    }
    cout << endl ;
}

void guiones(int ancho, int renglon){
    gotoxy(1,renglon);
    int x;
    for (x=1 ; x <=ancho ; x++ ){
        cout << "-" ;
    }
    cout << endl ;
}

void msj (const char *m, int ubicacion , int ancho){
    int x, pos , tam;
    switch (ubicacion){
    case 1 :
        cout << m ;
        break ;
    case 2 :
        tam = strlen (m);
        pos =(ancho-tam)/2 ;
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    case 3 :
        tam = strlen (m);
        pos = (ancho-tam);
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    }
}

void msj (const char *m, int ubicacion , int ancho, const char* color){
    int x, pos , tam;
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" , *magenta="MAGENTA", *blanco="BLANCO", *amarillo="AMARILLO";
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                if(strcmp(color, magenta)==0){
                    setBackgroundColor(MAGENTA);
                }else {
                    if(strcmp(color, blanco)==0){
                        setColor(BLACK);
                        setBackgroundColor(WHITE);
                    }else {
                        if (strcmp (color, amarillo)==0){
                            setColor (BLACK);
                            setBackgroundColor (YELLOW);
                        }
                    }
                }
            }
        }
    }
    tam = strlen (m);
    switch (ubicacion){
    case 1 :
        cout << m ;
        for (x=tam ; x<ancho_formato; x++){
            cout << " ";
        }
        break ;
    case 2 :
        pos =(ancho-tam)/2 ;
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        for (x=pos+tam;x<=ancho_formato;x++){
            cout << " " ;
        }

        break;
    case 3 :
        pos = (ancho-tam);
        for (x=1 ; x<=pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    }
    setBackgroundColor(BLACK);
    if(strcmp(color, blanco)==0){
        setColor(WHITE);
    }else {
        if(strcmp(color, amarillo)==0){
        setColor(WHITE);
        }
    }
}

void linea_horizontal (int x,int yinicial,int yfinal){
    int i ;
    const char lin_ver = 380;
    for (i=yinicial; i<=yfinal ; i++){
        gotoxy (x,i);
        cout << lin_ver ;
    }
}

void ColorRenglon (int ancho,int renglon, char *color){
    int x ;
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" , *magenta="MAGENTA", *blanco="BLANCO", *amarillo="AMARILLO";
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                if(strcmp(color, magenta)==0){
                    setBackgroundColor(MAGENTA);
                }else {
                    if(strcmp(color, blanco)==0){
                        setColor(BLACK);
                        setBackgroundColor(WHITE);
                    }else {
                        if (strcmp (color, amarillo)==0){
                            setColor (BLACK);
                            setBackgroundColor (YELLOW);
                        }
                    }
                }
            }
        }
    }
    gotoxy (1,renglon);
    for (x=0 ; x<ancho_formato; x++){
        cout << " ";
    }
    setBackgroundColor(BLACK);
    if(strcmp(color, blanco)==0){
        setColor(WHITE);
    }else {
        if(strcmp(color, amarillo)==0){
        setColor(WHITE);
        }
    }
    gotoxy (1,renglon);
}

