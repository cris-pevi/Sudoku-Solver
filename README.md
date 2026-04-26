# Sudoku Solver

Problema [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) de LeetCode, implementada en C++ usando **backtracking recursivo**.

---

## Descripción del problema

Dado un tablero de Sudoku 9×9 parcialmente lleno (las celdas vacías se representan con `'.'`), se debe rellenar el tablero de modo que cumpla las reglas del Sudoku:

- Cada fila debe contener los dígitos del `1` al `9` sin repetición.
- Cada columna debe contener los dígitos del `1` al `9` sin repetición.
- Cada una de las 9 subcuadrículas de 3×3 debe contener los dígitos del `1` al `9` sin repetición.

Se garantiza que el tablero tiene solución única.

---

## Algoritmo: Backtracking

La técnica que se utiliza para resolver este problema es el **backtracking**, una forma de búsqueda exhaustiva que prueba valores y retrocede cuando detecta que un camino no puede llevar a una solución válida.

### Idea general

1. Recorrer el tablero celda por celda.
2. Cuando se encuentra una celda vacía (`.`), intentar colocar los dígitos del `'1'` al `'9'` uno por uno.
3. Antes de colocar un dígito, verificar que sea válido en esa posición.
4. Si es válido, colocarlo y continuar recursivamente con el resto del tablero.
5. Si la recursión lleva a una solución, retornar `true` y propagar el éxito hacia atrás.
6. Si ningún dígito funciona en esa celda, restaurarla a `'.'` y retornar `false` para que la llamada anterior pruebe con otro dígito (**retroceso**).
7. Si se recorre todo el tablero sin encontrar celdas vacías, el tablero está resuelto.

---

## Funciones principales

### `solveSudoku`

Punto de entrada público. Simplemente delega la lógica a la función privada `resolver`.

### `resolver`

Función recursiva que implementa el backtracking:

- Itera sobre todas las celdas del tablero en orden (fila por fila, columna por columna).
- Al encontrar una celda vacía, prueba cada dígito del `'1'` al `'9'`.
- Por cada dígito válido, lo coloca y llama a `resolver` recursivamente.
  - Si la llamada recursiva retorna `true`, la solución fue encontrada.
  - Si retorna `false`, deshace el movimiento (restaura `.`) y prueba el siguiente dígito.
- Si ningún dígito es válido, retorna `false` para desencadenar el retroceso.
- Si no hay más celdas vacías, retorna `true` indicando que el tablero está completo.

### `esValido`

Verifica si colocar un dígito en `(fila, columna)` es legal según las reglas del Sudoku. En una sola iteración de 0 a 8 comprueba simultáneamente:

- **Fila:** que el dígito no aparezca en otra columna de la misma fila.
- **Columna:** que el dígito no aparezca en otra fila de la misma columna.
- **Subcuadrícula 3×3:** usando las fórmulas:
  ```
  filaCaja    = 3 * (fila / 3)    + i / 3
  columnaCaja = 3 * (columna / 3) + i % 3
  ```
  estas expresiones mapean el índice `i` a cada una de las 9 celdas de la caja correspondiente.

---

## Complejidad

| | Complejidad |
|---|---|
| **Tiempo** | O(9^m), donde *m* es el número de celdas vacías en el tablero. En el peor caso se exploran todas las combinaciones posibles. |
| **Espacio** | O(m) por la pila de llamadas recursivas|

En la práctica, el algoritmo es muy eficiente gracias a la poda que realiza `esValido` al descartar dígitos inválidos antes de explorar esa rama.

---
