# Plan de trabajo - PMC12 Caída o recuperación de presión

Matrícula 2026-0296

## 1. Interpretación del problema
- Cada registro es una unidad independiente: `id nombre tipo p` y `m` muestras.
- `tipo = 0` (caída): score = máx(máximo_hasta_ahora - muestra_actual).
- `tipo = 1` (recuperación): score = máx(muestra_actual - mínimo_hasta_ahora).
- El máximo/mínimo **incluye** la muestra actual. Con una muestra, score = 0.
- `estado = 1` si `score > p`, si no 0.
- Salida: una línea por unidad (orden original), luego TOTAL, ORDER, FIND.
- Cualquier error de entrada (fuera de dominio, id repetido, incompleta): solo `ERROR`.

## 2. Estructuras
- `int muestras[20][8]` y `Registro regs[20]`.
- `Registro { id, nombre[16], Config{tipo,p}, score, estado }`.

## 3. Pseudocódigo

```
LEER n, m, q       -> validar 1<=n<=20, 1<=m<=8, 1<=q<=9999
PARA cada registro i:
    LEER id, nombre, tipo, p y m muestras
    VALIDAR dominio de todo y que el id no esté repetido
    (si algo falla -> imprimir ERROR y terminar)

PARA cada unidad i:                      # sin arrastrar datos entre unidades
    score <- calcular(muestras[i], m, tipo, p, &estado)

IMPRIMIR "id score estado" por unidad, en orden original
IMPRIMIR "TOTAL" total_rec(regs, n)
ordenar(regs, n, orden)                  # score desc, id asc
IMPRIMIR "ORDER" + ids según orden
IMPRIMIR "FIND q" buscar(regs, n, q)     # -1 si no existe
```

```
calcular(x, m, tipo, p, *estado):
    extremo <- x[0] ; score <- 0
    PARA i de 0 a m-1:
        SI tipo = 0:
            SI x[i] > extremo: extremo <- x[i]
            dif <- extremo - x[i]
        SINO:
            SI x[i] < extremo: extremo <- x[i]
            dif <- x[i] - extremo
        SI dif > score: score <- dif
    *estado <- (score > p) ? 1 : 0
    DEVOLVER score

total_rec(regs, n):
    SI n = 0: DEVOLVER 0
    DEVOLVER regs[n-1].score + total_rec(regs, n-1)

ordenar: llenar orden[i] = i y aplicar selección con criterio
         (score mayor primero; si empatan, id menor primero)

buscar(regs, n, q): copiar regs, ordenar la copia por id (inserción),
                    búsqueda binaria; DEVOLVER score o -1
```

## 4. Decisiones
- `ordenar` trabaja sobre un arreglo de índices para preservar el orden original.
- `buscar` ordena una copia por id; no modifica `regs`.
- Se valida todo antes de imprimir para no producir salidas parciales.
- Sin `qsort`, `bsearch`, `gets`, `system` ni memoria dinámica.

## 5. Plan de pruebas
Grupos 1 a 6 públicos más casos propios: borde de igualdad (score = p),
capacidad máxima 20x8, q ausente, id repetido, entrada incompleta, tipo inválido.
