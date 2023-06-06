/*
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

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

bool isGoalState(const State& state, const vector<vector<int>>& goalBoard) {
    return state.board == goalBoard;
}

int calculateManhattanDistance(int value, int targetRow, int targetCol) {
    // Calcula la distancia de Manhattan para un número dado
    int row = (value - 1) / 5;
    int col = (value - 1) % 5;
    return abs(row - targetRow) + abs(col - targetCol);
}

int calculateTotalManhattanDistance(const vector<vector<int>>& board, const vector<vector<int>>& goalBoard) {
    // Calcula la suma de las distancias de Manhattan para todos los números en el tablero
    int totalDistance = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int value = board[i][j];
            if (value != 0) {
                int targetRow = (value - 1) / 5;
                int targetCol = (value - 1) % 5;
                totalDistance += calculateManhattanDistance(value, targetRow, targetCol);
            }
        }
    }
    return totalDistance;
}

vector<State> getNeighboringStates(const State& state, const vector<vector<int>>& goalBoard) {
    // Obtiene los estados vecinos válidos del estado actual
    vector<State> neighbors;

    // Movimientos válidos: arriba, abajo, izquierda, derecha
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    string directions[] = {"Arriba\n", "Abajo\n", "Izquierda\n", "Derecha\n"};

    for (int i = 0; i < 4; i++) {
        int newRow1 = state.emptyRow1 + dy[i];
        int newCol1 = state.emptyCol1 + dx[i];
        int newRow2 = state.emptyRow2 + dy[i];
        int newCol2 = state.emptyCol2 + dx[i];

        if (newRow1 >= 0 && newRow1 < 5 && newCol1 >= 0 && newCol1 < 5) {
            // Genera un nuevo estado al mover el primer espacio vacío
            State neighbor = state;
            swap(neighbor.board[state.emptyRow1][state.emptyCol1], neighbor.board[newRow1][newCol1]);
            neighbor.emptyRow1 = newRow1;
            neighbor.emptyCol1 = newCol1;
            neighbor.moves += directions[i];
            neighbor.cost = int(neighbor.moves.size() + calculateTotalManhattanDistance(neighbor.board, goalBoard));
            neighbors.push_back(neighbor);
        }

        if (newRow2 >= 0 && newRow2 < 5 && newCol2 >= 0 && newCol2 < 5) {
            // Genera un nuevo estado al mover el segundo espacio vacío
            State neighbor = state;
            swap(neighbor.board[state.emptyRow2][state.emptyCol2], neighbor.board[newRow2][newCol2]);
            neighbor.emptyRow2 = newRow2;
            neighbor.emptyCol2 = newCol2;
            neighbor.moves += directions[i];
            neighbor.cost = int(neighbor.moves.size() + calculateTotalManhattanDistance(neighbor.board, goalBoard));
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void solveSlidingPuzzle(const vector<vector<int>>& initialBoard, const vector<vector<int>>& goalBoard) {
    State initialState;
    initialState.board = initialBoard;
    initialState.emptyRow1 = -1;
    initialState.emptyCol1 = -1;
    initialState.emptyRow2 = -1;
    initialState.emptyCol2 = -1;
    initialState.moves = "";
    initialState.cost = calculateTotalManhattanDistance(initialBoard, goalBoard);

    int size = int(initialBoard.size());
    // Encontrar las posiciones iniciales de los espacios vacíos
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (initialBoard[i][j] == 0) {
                if (initialState.emptyRow1 == -1) {
                    initialState.emptyRow1 = i;
                    initialState.emptyCol1 = j;
                } else {
                    initialState.emptyRow2 = i;
                    initialState.emptyCol2 = j;
                }
            }
        }
    }

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

        if (isGoalState(currentState, goalBoard)) {
            cout << "Solución encontrada." << endl;
            cout << "Movimientos:\n" << currentState.moves << endl;
            return;
        }

        visitedStates.insert(currentState.moves);

        vector<State> neighbors = getNeighboringStates(currentState, goalBoard);

        for (const auto& neighbor : neighbors) {
            if (visitedStates.find(neighbor.moves) == visitedStates.end()) {
                statesQueue.push(neighbor);
            }
        }
    }

    cout << "No se encontró solución." << endl;
}

int main() {
    vector<vector<int>> initialBoard = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 0}
    };

    vector<vector<int>> goalBoard = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 0, 19, 20},
        {21, 22, 18, 23, 24}
    };

    solveSlidingPuzzle(initialBoard, goalBoard);
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

using namespace std;

struct State {
    vector<vector<int>> board;
    pair<int, int> empty1;  // Coordenadas del primer espacio vacío
    pair<int, int> empty2;  // Coordenadas del segundo espacio vacío
    string moves;
    int cost;  // Costo total (g + h)
};

bool isGoalState(const State& state, const vector<vector<int>>& goalBoard) {
    return state.board == goalBoard;
}

int calculateManhattanDistance(int value, int targetRow, int targetCol) {
    // Calcula la distancia de Manhattan para un número dado
    int row = (value - 1) / 5;
    int col = (value - 1) % 5;
    return abs(row - targetRow) + abs(col - targetCol);
}

int calculateTotalManhattanDistance(const vector<vector<int>>& board, const vector<vector<int>>& goalBoard) {
    // Calcula la suma de las distancias de Manhattan para todos los números en el tablero
    int totalDistance = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int value = board[i][j];
            if (value != 0) {
                int targetRow = (value - 1) / 5;
                int targetCol = (value - 1) % 5;
                totalDistance += calculateManhattanDistance(value, targetRow, targetCol);
            }
        }
    }
    return totalDistance;
}

vector<State> getNeighboringStates(const State& state, const vector<vector<int>>& goalBoard) {
    // Obtiene los estados vecinos válidos del estado actual
    vector<State> neighbors;

    // Movimientos válidos: arriba, abajo, izquierda, derecha
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    string directions[] = {"Arriba\n", "Abajo\n", "Izquierda\n", "Derecha\n"};

    for (int i = 0; i < 4; i++) {
        int newRow1 = state.empty1.first + dy[i];
        int newCol1 = state.empty1.second + dx[i];
        int newRow2 = state.empty2.first + dy[i];
        int newCol2 = state.empty2.second + dx[i];

        if (newRow1 >= 0 && newRow1 < 5 && newCol1 >= 0 && newCol1 < 5) {
            // Genera un nuevo estado al mover el primer espacio vacío
            State neighbor = state;
            swap(neighbor.board[state.empty1.first][state.empty1.second], neighbor.board[newRow1][newCol1]);
            neighbor.empty1 = make_pair(newRow1, newCol1);
            neighbor.moves += directions[i];
            neighbor.cost = int(neighbor.moves.size() + calculateTotalManhattanDistance(neighbor.board, goalBoard));
            neighbors.push_back(neighbor);
        }

        if (newRow2 >= 0 && newRow2 < 5 && newCol2 >= 0 && newCol2 < 5) {
            // Genera un nuevo estado al mover el segundo espacio vacío
            State neighbor = state;
            swap(neighbor.board[state.empty2.first][state.empty2.second], neighbor.board[newRow2][newCol2]);
            neighbor.empty2 = make_pair(newRow2, newCol2);
            neighbor.moves += directions[i];
            neighbor.cost = int(neighbor.moves.size() + calculateTotalManhattanDistance(neighbor.board, goalBoard));
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void solveSlidingPuzzle(const vector<vector<int>>& initialBoard, const vector<vector<int>>& goalBoard) {
    State initialState;
    initialState.board = initialBoard;
    initialState.moves = "";
    initialState.cost = calculateTotalManhattanDistance(initialBoard, goalBoard);

    int size = int(initialBoard.size());
    // Encontrar las posiciones iniciales de los espacios vacíos
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (initialBoard[i][j] == 0) {
                if (initialState.empty1.first == -1) {
                    initialState.empty1 = make_pair(i, j);
                } else {
                    initialState.empty2 = make_pair(i, j);
                }
            }
        }
    }

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

        if (isGoalState(currentState, goalBoard)) {
            cout << "Solución encontrada." << endl;
            cout << "Movimientos:\n" << currentState.moves << endl;
            return;
        }

        visitedStates.insert(currentState.moves);

        vector<State> neighbors = getNeighboringStates(currentState, goalBoard);

        for (const auto& neighbor : neighbors) {
            if (visitedStates.find(neighbor.moves) == visitedStates.end()) {
                statesQueue.push(neighbor);
            }
        }
    }

    cout << "No se encontró solución." << endl;
}

int main() {
    vector<vector<int>> initialBoard = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 0, 0}
    };

    vector<vector<int>> goalBoard = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 0, 0, 23}
    };

    solveSlidingPuzzle(initialBoard, goalBoard);
    return 0;
}
