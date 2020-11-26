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
    for (a=0; a<=ancho_formato; a++){
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
    const char lin_ver = 179;
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

void recuadro(int x, int y, int ancho, int alto){
    /// códigos windows, usando (char)
    const char esq_1=218 ;/// - ┌
    const char esq_2=191 ;/// - ┐
    const char esq_3=217 ;/// - ┘
    const char esq_4=192 ;/// - └
    //const char cruz=197 ;/// - ┼
    const char l_hor=196 ;/// - ─
    const char l_ver=179 ;/// - │
    //const char t_inv=193 ;/// - ┴
    //const char t_nor=194 ;/// - ┬"
    //const char t_lad1=195 ;/// 195 - ├
    //const char t_lad2=180 ;/// 180 - ┤
    /// Borramos el espacio del recuadro
    int i, j;
    for(i=x; i<=x+ancho; i++){
        for(j=y; j<=y+alto; j++){
            locate(i, j);
            cout << " ";

        }
    }
    /// Líneas horizontales
    for(i=x; i<=x+ancho; i++){
        locate(i, y);
        cout << l_hor ;

        locate(i, y+alto);
        cout << l_hor ;
    }
    /// Líneas verticales
    for(i=y; i<=y+alto; i++){
        locate(x, i);
        cout << l_ver ;
        locate(x+ancho, i);
        cout << l_ver ;
    }
    /// Vértices
    locate(x, y);
    cout << esq_1;
    locate(x, y+alto);
    cout << esq_4 ;
    locate(x+ancho, y);
    cout << esq_2 ;
    locate(x+ancho, y+alto);
    cout << esq_3;
}

void dibujarDado0(int x,int y, int ANCHO, int ALTO,int INI, int nroDado, int valor){
    const int Y = 5 ;
    //const int ALTO = 4;
    //const int INI = 15;
    const int X = INI + (nroDado * 10);
    //const int ANCHO = 8;

    /// Ubicaciones del punto
    const int CENTRO_X = X + ANCHO/2;
    const int CENTRO_Y = Y + ALTO/2;
    const int IZQUIERDA = CENTRO_X - 2;
    const int ARRIBA = CENTRO_Y - 1;
    const int DERECHA= CENTRO_X + 2;
    const int ABAJO= CENTRO_Y + 1;
    recuadro(X, Y, ANCHO, ALTO);
    /// Dibujar los puntos
    const char DOT = 254;
    switch(valor){
        case 1:{
            locate(CENTRO_X, CENTRO_Y);
            cout << DOT;
        }
        break;
        case 2:{
            if (nroDado%2 == 0){
                locate(IZQUIERDA, ARRIBA);
                cout << DOT;
                locate(DERECHA, ABAJO);
                cout << DOT;
            }
            else{
                locate(DERECHA, ARRIBA);
                cout << DOT;
                locate(IZQUIERDA, ABAJO);
                cout << DOT;
            }
        }
        break;
        case 3:{
            if (nroDado%2 == 0){
                locate(IZQUIERDA, ARRIBA);
                cout << DOT;
                locate(DERECHA, ABAJO);
                cout << DOT;
            }
            else{
                locate(DERECHA, ARRIBA);
                cout << DOT;
                locate(IZQUIERDA, ABAJO);
                cout << DOT;
            }
            locate(CENTRO_X, CENTRO_Y);
            cout << DOT;
        }
        break;
        case 4:{
            locate(IZQUIERDA, ARRIBA);
            cout << DOT;
            locate(DERECHA, ABAJO);
            cout << DOT;
            locate(DERECHA, ARRIBA);
            cout << DOT;
            locate(IZQUIERDA, ABAJO);
            cout << DOT;
        }
        break;
        case 5:{
            locate(IZQUIERDA, ARRIBA);
            cout << DOT;
            locate(DERECHA, ABAJO);
            cout << DOT;
            locate(DERECHA, ARRIBA);
            cout << DOT;
            locate(IZQUIERDA, ABAJO);
            cout << DOT;
            locate(CENTRO_X, CENTRO_Y);
            cout << DOT;
        }
        break;
        case 6:{
            locate(IZQUIERDA, ARRIBA);
            cout << DOT;
            locate(DERECHA, ABAJO);
            cout << DOT;
            locate(DERECHA, ARRIBA);
            cout << DOT;
            locate(IZQUIERDA, ABAJO);
            cout << DOT;
            locate(DERECHA, CENTRO_Y);
            cout << DOT;
            locate(IZQUIERDA, CENTRO_Y);
            cout << DOT;
        }
        break;
    }
}

