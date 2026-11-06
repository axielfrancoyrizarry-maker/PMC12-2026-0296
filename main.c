/* PMC12 - Caida o recuperacion de presion
   Matricula 2026-0296 | 20260296@itla.edu.do */

#include <stdio.h>
#include <string.h>
#include "reto.h"

/* ---------- Calculo del score y el estado de UNA unidad ---------- */
int calcular(const int x[], int m, int tipo, int p, int *estado)
{
    int extremo = x[0];      /* maximo (tipo 0) o minimo (tipo 1) hasta ahora */
    int score = 0;
    int i;

    for (i = 0; i < m; i++) {
        int diferencia;

        if (tipo == 0) {
            if (x[i] > extremo) {
                extremo = x[i];
            }
            diferencia = extremo - x[i];
        } else {
            if (x[i] < extremo) {
                extremo = x[i];
            }
            diferencia = x[i] - extremo;
        }

        if (diferencia > score) {
            score = diferencia;
        }
    }

    *estado = (score > p) ? 1 : 0;
    return score;
}

/* ---------- Total recursivo ---------- */
int total_rec(const Registro regs[], int n)
{
    if (n == 0) {
        return 0;
    }
    return regs[n - 1].score + total_rec(regs, n - 1);
}

/* ---------- Ordenamiento (seleccion sobre indices) ---------- */
static int va_antes(const Registro *a, const Registro *b)
{
    if (a->score != b->score) {
        return a->score > b->score;
    }
    return a->id < b->id;
}

void ordenar(const Registro regs[], int n, int orden[])
{
    int i, j, mejor, temporal;

    for (i = 0; i < n; i++) {
        orden[i] = i;
    }

    for (i = 0; i < n - 1; i++) {
        mejor = i;
        for (j = i + 1; j < n; j++) {
            if (va_antes(&regs[orden[j]], &regs[orden[mejor]])) {
                mejor = j;
            }
        }
        if (mejor != i) {
            temporal = orden[i];
            orden[i] = orden[mejor];
            orden[mejor] = temporal;
        }
    }
}

/* ---------- Busqueda binaria sobre copia ordenada por id ---------- */
int buscar(const Registro regs[], int n, int q)
{
    Registro copia[MAX_UNIDADES];
    Registro clave;
    int i, j;
    int bajo = 0;
    int alto = n - 1;
    int medio;

    for (i = 0; i < n; i++) {
        copia[i] = regs[i];
    }

    /* insercion por id ascendente */
    for (i = 1; i < n; i++) {
        clave = copia[i];
        j = i - 1;
        while (j >= 0 && copia[j].id > clave.id) {
            copia[j + 1] = copia[j];
            j--;
        }
        copia[j + 1] = clave;
    }

    while (bajo <= alto) {
        medio = bajo + (alto - bajo) / 2;
        if (copia[medio].id == q) {
            return copia[medio].score;
        }
        if (copia[medio].id < q) {
            bajo = medio + 1;
        } else {
            alto = medio - 1;
        }
    }
    return -1;
}

/* ---------- Lectura y validacion completa de la entrada ---------- */
/* Devuelve 1 si todo es valido, 0 ante cualquier error. */
static int leer_entrada(int *n, int *m, int *q, Registro regs[],
                        int muestras[][MAX_MUESTRAS])
{
    char etiqueta[64];
    size_t largo;
    int i, j, k;

    if (scanf("%d %d %d", n, m, q) != 3) {
        return 0;
    }
    if (*n < 1 || *n > MAX_UNIDADES ||
        *m < 1 || *m > MAX_MUESTRAS ||
        *q < ID_MIN || *q > ID_MAX) {
        return 0;
    }

    for (i = 0; i < *n; i++) {
        if (scanf("%d %63s %d %d", &regs[i].id, etiqueta,
                  &regs[i].config.tipo, &regs[i].config.p) != 4) {
            return 0;
        }
        if (regs[i].id < ID_MIN || regs[i].id > ID_MAX) {
            return 0;
        }
        largo = strlen(etiqueta);
        if (largo < 1 || largo > LONG_NOMBRE - 1) {
            return 0;
        }
        strcpy(regs[i].nombre, etiqueta);

        if (regs[i].config.tipo != 0 && regs[i].config.tipo != 1) {
            return 0;
        }
        if (regs[i].config.p < VALOR_MIN || regs[i].config.p > VALOR_MAX) {
            return 0;
        }

        for (j = 0; j < *m; j++) {
            if (scanf("%d", &muestras[i][j]) != 1) {
                return 0;
            }
            if (muestras[i][j] < VALOR_MIN || muestras[i][j] > VALOR_MAX) {
                return 0;
            }
        }

        for (k = 0; k < i; k++) {
            if (regs[k].id == regs[i].id) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
    int n, m, q;
    int i;
    Registro regs[MAX_UNIDADES];
    int muestras[MAX_UNIDADES][MAX_MUESTRAS];
    int orden[MAX_UNIDADES];

    if (!leer_entrada(&n, &m, &q, regs, muestras)) {
        printf("ERROR\n");
        return 0;
    }

    /* cada unidad se calcula por separado, sin arrastrar acumuladores */
    for (i = 0; i < n; i++) {
        regs[i].score = calcular(muestras[i], m, regs[i].config.tipo,
                                 regs[i].config.p, &regs[i].estado);
    }

    for (i = 0; i < n; i++) {
        printf("%d %d %d\n", regs[i].id, regs[i].score, regs[i].estado);
    }

    printf("TOTAL %d\n", total_rec(regs, n));

    ordenar(regs, n, orden);
    printf("ORDER");
    for (i = 0; i < n; i++) {
        printf(" %d", regs[orden[i]].id);
    }
    printf("\n");

    printf("FIND %d %d\n", q, buscar(regs, n, q));
    return 0;
}
