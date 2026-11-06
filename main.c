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

    if (!leer_entrada(&n, &m, &q, regs, muestras)) {
        printf("ERROR\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        regs[i].score = calcular(muestras[i], m, regs[i].config.tipo,
                                 regs[i].config.p, &regs[i].estado);
    }

    for (i = 0; i < n; i++) {
        printf("%d %d %d\n", regs[i].id, regs[i].score, regs[i].estado);
    }
    /* Pendiente: TOTAL, ORDER y FIND */
    return 0;
}
