#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <functional>
using namespace std;

struct State {
    vector<vector<int>> board;
    int emptyRow1;
    int emptyCol1;
    int emptyRow2;
    int emptyCol2;
    string moves;
    int cost;  // Costo total (g + h)
};

bool isGoalState(const State& state) {
    // Comprueba si el estado es el estado objetivo
    // (todos los números en orden ascendente)
    int num = 1;
    for (const auto& row : state.board) {
        for (int col : row) {
            if (col != num) {
                return false;
            }
            num++;
        }
    }
    return true;
}

int calculateManhattanDistance(const vector<vector<int>>& board, int row, int col) {
    // Calcula la distancia de Manhattan para una posición dada
    int value = board[row][col];
    int targetRow = (value - 1) / 5;
    int targetCol = (value - 1) % 5;
    return abs(row - targetRow) + abs(col - targetCol);
}

int calculateTotalManhattanDistance(const vector<vector<int>>& board) {
    // Calcula la suma de las distancias de Manhattan para todos los números en el tablero
    int totalDistance = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int value = board[i][j];
            if (value != 0) {
                totalDistance += calculateManhattanDistance(board, i, j);
            }
        }
    }
    return totalDistance;
}

vector<State> getNeighboringStates(const State& state) {
    // Obtiene los estados vecinos válidos del estado actual
    vector<State> neighbors;

    // Movimientos válidos: arriba, abajo, izquierda, derecha
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    string directions[] = {"U", "D", "L", "R"};

    for (int i = 0; i < 4; i++) {
        int newRow1 = state.emptyRow1 + dy[i];
        int newCol1 = state.emptyCol1 + dx[i];
        int newRow2 = state.emptyRow2 + dy[i];
        int newCol2 = state.emptyCol2 + dx[i];

        if (newRow1 >= 0 && newRow1 < 5 && newCol1 >= 0 && newCol1 < 5 &&
            newRow2 >= 0 && newRow2 < 5 && newCol2 >= 0 && newCol2 < 5) {
            // Genera un nuevo estado al intercambiar los números en los espacios vacíos
            State neighbor = state;
            swap(neighbor.board[state.emptyRow1][state.emptyCol1], neighbor.board[newRow1][newCol1]);
            swap(neighbor.board[state.emptyRow2][state.emptyCol2], neighbor.board[newRow2][newCol2]);
            neighbor.emptyRow1 = newRow1;
            neighbor.emptyCol1 = newCol1;
            neighbor.emptyRow2 = newRow2;
            neighbor.emptyCol2 = newCol2;
            neighbor.moves += directions[i];
            neighbor.cost = neighbor.moves.size() + calculateTotalManhattanDistance(neighbor.board);
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void solveSlidingPuzzle() {
    vector<vector<int>> initialBoard = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 0, 0, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    State initialState;
    initialState.board = initialBoard;
    initialState.emptyRow1 = 2;
    initialState.emptyCol1 = 2;
    initialState.emptyRow2 = 2;
    initialState.emptyCol2 = 3;
    initialState.moves = "";
    initialState.cost = calculateTotalManhattanDistance(initialBoard);

    priority_queue<State, vector<State>, function<bool(const State&, const State&)>> statesQueue(
        [](const State& a, const State& b) {
            // Ordena los estados en función de su costo total (g + h)
            return a.cost > b.cost;
        }
    );

    unordered_set<string> visitedStates;

    statesQueue.push(initialState);

    while (!statesQueue.empty()) {
        State currentState = statesQueue.top();
        statesQueue.pop();

        if (isGoalState(currentState)) {
            cout << "Solución encontrada." << endl;
            cout << "Movimientos: " << currentState.moves << endl;

            // Guarda los movimientos en un archivo de texto
            ofstream outputFile("movimientos.txt");
            if (outputFile.is_open()) {
                outputFile << currentState.moves;
                outputFile.close();
            } else {
                cout << "No se pudo abrir el archivo de salida." << endl;
            }
            return;
        }

        visitedStates.insert(currentState.moves);

        vector<State> neighbors = getNeighboringStates(currentState);

        for (const auto& neighbor : neighbors) {
            if (visitedStates.find(neighbor.moves) == visitedStates.end()) {
                statesQueue.push(neighbor);
            }
        }
    }

    cout << "No se encontró solución." << endl;
}

int main() {
    solveSlidingPuzzle();
    return 0;
}
