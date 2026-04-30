#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "solution.cpp"
using namespace std;

void imprimirTablero(const vector<vector<char>>& tablero) {
    for (int fila = 0; fila < 9; fila++) {
        for (int columna = 0; columna < 9; columna++) {
            cout << tablero[fila][columna];
            if (columna < 8) cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool tablerosIguales(const vector<vector<char>>& tableroA, const vector<vector<char>>& tableroB) {
    for (int fila = 0; fila < 9; fila++)
        for (int columna = 0; columna < 9; columna++)
            if (tableroA[fila][columna] != tableroB[fila][columna]) return false;
    return true;
}

bool tableroCompleto(const vector<vector<char>>& tablero) {
    for (int fila = 0; fila < 9; fila++)
        for (int columna = 0; columna < 9; columna++)
            if (tablero[fila][columna] == '.') return false;
    return true;
}

bool solucionEsValida(const vector<vector<char>>& tablero) {
    for (int fila = 0; fila < 9; fila++) {
        vector<bool> vistoEnFila(10, false);
        vector<bool> vistoEnColumna(10, false);
        for (int columna = 0; columna < 9; columna++) {
            int digitoFila    = tablero[fila][columna] - '0';
            int digitoColumna = tablero[columna][fila] - '0';
            if (vistoEnFila[digitoFila])    return false;
            if (vistoEnColumna[digitoColumna]) return false;
            vistoEnFila[digitoFila]       = true;
            vistoEnColumna[digitoColumna] = true;
        }
    }
    for (int bloqueFilas = 0; bloqueFilas < 3; bloqueFilas++) {
        for (int bloqueColumnas = 0; bloqueColumnas < 3; bloqueColumnas++) {
            vector<bool> vistoEnCaja(10, false);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int digito = tablero[bloqueFilas * 3 + i][bloqueColumnas * 3 + j] - '0';
                    if (vistoEnCaja[digito]) return false;
                    vistoEnCaja[digito] = true;
                }
            }
        }
    }
    return true;
}

void ejecutarCaso(const string& nombreCaso, vector<vector<char>> tableroEntrada, const vector<vector<char>>& solucionEsperada) {
    Solution solucion;
    solucion.solveSudoku(tableroEntrada);

    bool pasaCompleto   = tableroCompleto(tableroEntrada);
    bool pasaValido     = solucionEsValida(tableroEntrada);
    bool pasaEsperado   = tablerosIguales(tableroEntrada, solucionEsperada);

    cout << "[" << nombreCaso << "]\n";
    imprimirTablero(tableroEntrada);

    assert(pasaCompleto  && "El tablero no fue completado");
    assert(pasaValido    && "La solucion contiene conflictos");
    assert(pasaEsperado  && "La solucion no coincide con la esperada");

    cout << "PASO\n\n";
}

int main() {
    {
        string nombre = "Caso del enunciado de LeetCode";

        vector<vector<char>> entrada = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };

        vector<vector<char>> esperado = {
            {'5','3','4','6','7','8','9','1','2'},
            {'6','7','2','1','9','5','3','4','8'},
            {'1','9','8','3','4','2','5','6','7'},
            {'8','5','9','7','6','1','4','2','3'},
            {'4','2','6','8','5','3','7','9','1'},
            {'7','1','3','9','2','4','8','5','6'},
            {'9','6','1','5','3','7','2','8','4'},
            {'2','8','7','4','1','9','6','3','5'},
            {'3','4','5','2','8','6','1','7','9'}
        };

        ejecutarCaso(nombre, entrada, esperado);
    }

    {
        string nombre = "Tablero casi completo, una sola celda vacia";

        vector<vector<char>> entrada = {
            {'5','3','4','6','7','8','9','1','2'},
            {'6','7','2','1','9','5','3','4','8'},
            {'1','9','8','3','4','2','5','6','7'},
            {'8','5','9','7','6','1','4','2','3'},
            {'4','2','6','8','5','3','7','9','1'},
            {'7','1','3','9','2','4','8','5','6'},
            {'9','6','1','5','3','7','2','8','4'},
            {'2','8','7','4','1','9','6','3','5'},
            {'3','4','5','2','8','6','1','7','.'}
        };

        vector<vector<char>> esperado = {
            {'5','3','4','6','7','8','9','1','2'},
            {'6','7','2','1','9','5','3','4','8'},
            {'1','9','8','3','4','2','5','6','7'},
            {'8','5','9','7','6','1','4','2','3'},
            {'4','2','6','8','5','3','7','9','1'},
            {'7','1','3','9','2','4','8','5','6'},
            {'9','6','1','5','3','7','2','8','4'},
            {'2','8','7','4','1','9','6','3','5'},
            {'3','4','5','2','8','6','1','7','9'}
        };

        ejecutarCaso(nombre, entrada, esperado);
    }

    {
        string nombre = "Tablero ya resuelto, sin celdas vacias";

        vector<vector<char>> entrada = {
            {'5','3','4','6','7','8','9','1','2'},
            {'6','7','2','1','9','5','3','4','8'},
            {'1','9','8','3','4','2','5','6','7'},
            {'8','5','9','7','6','1','4','2','3'},
            {'4','2','6','8','5','3','7','9','1'},
            {'7','1','3','9','2','4','8','5','6'},
            {'9','6','1','5','3','7','2','8','4'},
            {'2','8','7','4','1','9','6','3','5'},
            {'3','4','5','2','8','6','1','7','9'}
        };

        vector<vector<char>> esperado = entrada;

        ejecutarCaso(nombre, entrada, esperado);
    }

    {
        string nombre = "Tablero minimo con 17 pistas (minimo teorico para solucion unica)";

        vector<vector<char>> entrada = {
            {'.','.','.','.','.','.','.','1','.'},
            {'.','.','.','.','.','2','.','.','3'},
            {'.','.','.','4','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.','.'},
            {'.','3','.','.','.','.','.','.','.'},
            {'5','.','.','3','.','.','.','.','6'},
            {'.','.','.','.','.','1','.','.','4'},
            {'.','.','.','.','.','.','.','.','.'}
        };

        Solution solucion;
        solucion.solveSudoku(entrada);

        bool pasaCompleto = tableroCompleto(entrada);
        bool pasaValido   = solucionEsValida(entrada);

        cout << "[" << nombre << "]\n";
        imprimirTablero(entrada);
        assert(pasaCompleto && "El tablero no fue completado");
        assert(pasaValido   && "La solucion contiene conflictos");
        cout << "PASO\n\n";
    }

    {
        string nombre = "Tablero dificil con maxima profundidad de backtracking";

        vector<vector<char>> entrada = {
            {'.','.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','3','.','8','5'},
            {'.','.','.','1','.','2','.','.','.',},
            {'.','.','.','5','.','7','.','.','.'},
            {'.','.','.','4','.','.','.','1','.',},
            {'.','9','.','.','.','.','.','.','.'},
            {'5','.','.','.','.','.','.','7','3'},
            {'.','.','.','2','.','1','.','.','.',},
            {'.','.','.','.','4','.','.','.','.'}
        };

        Solution solucion;
        solucion.solveSudoku(entrada);

        bool pasaCompleto = tableroCompleto(entrada);
        bool pasaValido   = solucionEsValida(entrada);

        cout << "[" << nombre << "]\n";
        imprimirTablero(entrada);
        assert(pasaCompleto && "El tablero no fue completado");
        assert(pasaValido   && "La solucion contiene conflictos");
        cout << "PASO\n\n";
    }

    cout << "Todos los casos pasaron correctamente.\n";
    return 0;
}
