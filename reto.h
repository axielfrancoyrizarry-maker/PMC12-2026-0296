#ifndef RETO_H
#define RETO_H

/* PMC12 - Caida o recuperacion de presion
   Matricula 2026-0296 */

/* Capacidades y limites del dominio */
#define MAX_UNIDADES 20
#define MAX_MUESTRAS 8
#define LONG_NOMBRE  16      /* 15 caracteres + '\0' */
#define ID_MIN       1
#define ID_MAX       9999
#define VALOR_MIN    0
#define VALOR_MAX    100

/* Configuracion propia de cada unidad (estructura anidada) */
typedef struct {
    int tipo;                /* 0 = caida, 1 = recuperacion */
    int p;                   /* umbral: estado = 1 si score > p */
} Config;

/* Registro de una unidad */
typedef struct {
    int id;
    char nombre[LONG_NOMBRE];
    Config config;
    int score;
    int estado;
} Registro;

/* Calcula el score de una unidad; devuelve el estado por referencia. */
int calcular(const int x[], int m, int tipo, int p, int *estado);

/* Suma recursiva de los scores (caso base n = 0). */
int total_rec(const Registro regs[], int n);

/* Llena orden[] con los indices de regs[] ordenados por score
   descendente y, en empate, por id ascendente. No altera regs[]. */
void ordenar(const Registro regs[], int n, int orden[]);

/* Busqueda binaria de q sobre una copia ordenada por id.
   Devuelve el score de la unidad, o -1 si q no existe. */
int buscar(const Registro regs[], int n, int q);

#endif /* RETO_H */
