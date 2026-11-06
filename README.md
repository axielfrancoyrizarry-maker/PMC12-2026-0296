# PMC12 - Caída o recuperación de presión

- **Matrícula:** 2026-0296
- **Correo:** 20260296@itla.edu.do
- **Asignatura:** Programación para Mecatrónicos (ITLA)

## Modelo y decisiones
Cada registro es una unidad independiente. Para `tipo = 0` el score es la mayor
caída respecto al máximo observado hasta la muestra actual; para `tipo = 1`, la
mayor recuperación respecto al mínimo observado hasta la muestra actual (la
muestra actual se incluye). `estado = 1` si `score > p`.

- Se usa `int muestras[20][8]` y un arreglo de `Registro` (typedef struct) con
  una estructura anidada `Config { tipo, p }`.
- `reto.h` contiene constantes, tipos y prototipos con guardas; `main.c` contiene
  la implementación de `calcular`, `total_rec`, `ordenar` y `buscar`.
- `calcular` devuelve el estado por referencia (`int *estado`).
- `total_rec` es recursiva (caso base n = 0). `ordenar` usa selección sobre un
  arreglo de índices (preserva el orden original). `buscar` usa búsqueda binaria
  sobre una copia ordenada por id. No se usa `qsort`, `bsearch` ni memoria dinámica.
- Toda la entrada se valida antes de imprimir; ante cualquier error se imprime
  solo `ERROR`.

## Compilación y ejecución
```
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto
./reto < pruebas/publica1.in            # Linux / macOS
reto.exe < pruebas\publica1.in          # Windows (cmd)
python3 evaluar.py publicas.json ./reto # casos públicos
python3 evaluar.py propias.json ./reto  # casos propios
```
En Windows: `py evaluar.py publicas.json reto.exe`.

## Resultados
| Conjunto | Casos | Resultado |
| --- | --- | --- |
| Públicos (grupos 1 a 6) | 6 | 6 / 6 OK |
| Propios | 6 | 6 / 6 OK |

Cada prueba está en `pruebas/` con tres archivos: `.in` (entrada), `.esperado`
y `.obtenido` (salida real del programa).

### Pruebas propias
| Caso | Qué valida |
| --- | --- |
| propia1_borde_igualdad | score = p da estado 0; score = p + 1 da estado 1 (ambos tipos) |
| propia2_capacidad_20x8 | capacidad máxima, n = 20 y m = 8 |
| propia3_q_ausente | q ausente, FIND devuelve -1 |
| propia4_invalida_id_repetido | id repetido, solo ERROR |
| propia5_invalida_incompleta | entrada incompleta, solo ERROR |
| propia6_invalida_tipo | tipo fuera de dominio, solo ERROR |

### Traza manual contrastada (propia1)
Unidad 5, tipo 0, p = 20, muestras 80 60 100: máximo 80, 80, 100 → caídas 0, 20, 0
→ score 20; como 20 > 20 es falso, estado 0. Unidad 7, tipo 1, p = 29, muestras
40 70 50: mínimo 40 siempre → diferencias 0, 30, 10 → score 30; 30 > 29, estado 1.
TOTAL 50, ORDER 7 5, FIND 5 20. Coincide con lo obtenido.

### Fallo encontrado y corregido
(Escribe aquí un fallo REAL que tuviste durante el desarrollo, cómo lo
detectaste y cómo lo corregiste. Si no tuviste ninguno, borra esta sección y
conserva solo la traza manual de arriba.)

## Fuentes consultadas
- Corona Nakamura, M. A. y Ancona Valdez, M. de los Á. (2011). *Diseño de
  algoritmos y su codificación en lenguaje C*. McGraw-Hill.
- Enunciado del PMC12 (docente).
- (Añade aquí cualquier otra fuente o herramienta que realmente usaste.)

## Historial de commits
| # | Hash | Avance |
| --- | --- | --- |
| 1 | (pega el hash) | Estructura, interpretación y plan |
| 2 | (pega el hash) | Desarrollo parcial: lectura, validación y calcular |
| 3 | (pega el hash) | Total recursivo, ordenar, buscar, pruebas y validación |
| 4 | (pega el hash) | Correcciones finales y documentación |

El hash del commit final se entrega aparte, junto con la URL del repositorio.
