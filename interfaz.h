#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED
#define alto_formato 25
#define ancho_formato 80

void initUI();

void func_hora ();
void MostrarFecha (int, int);


void borrar_renglon (int);
void borrar_restorenglon(int, int);
void borrar_restopantalla (int);

/*void titulo(const char *, int);*/
void titulo(const char * msj, const char *color, int ancho);

void devolucion (const char *msj, int ancho, int renglon);
void devolucion(const char *, const char *, int , int);

void guiones(int);
void guiones(int ancho, int renglon);

void msj (const char *, int, int);
void msj (const char *, int , int, const char*);

void linea_horizontal (int, int, int);

void ColorRenglon (int, int, char *);



#endif // INTERFAZ_H_INCLUDED
