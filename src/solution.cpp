#include <vector>
using namespace std;
 
class Solution {
public:
    void solveSudoku(vector<vector<char>>& tablero) {
        resolver(tablero);
    }
 
private:
    bool resolver(vector<vector<char>>& tablero) {
        for (int fila = 0; fila < 9; fila++) {
            for (int columna = 0; columna < 9; columna++) {
                if (tablero[fila][columna] == '.') {
                    for (char digito = '1'; digito <= '9'; digito++) {
                        if (esValido(tablero, fila, columna, digito)) {
                            tablero[fila][columna] = digito;
 
                            if (resolver(tablero)) return true;
 
                            tablero[fila][columna] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
 
    bool esValido(vector<vector<char>>& tablero, int fila, int columna, char digito) {
        for (int i = 0; i < 9; i++) {
            if (tablero[fila][i] == digito) return false;
 
            if (tablero[i][columna] == digito) return false;
 
            int filaCaja    = 3 * (fila / 3) + i / 3;
            int columnaCaja = 3 * (columna / 3) + i % 3;
            if (tablero[filaCaja][columnaCaja] == digito) return false;
        }
        return true;
    }
};
