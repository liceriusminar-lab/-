#include <iostream>
#include <vector>

using namespace std;

// Игровое поле (массив 3x3)
char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Вывод поля на экран
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << "   " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
        if (i < 2) cout << "  -----------\n";
    }
    cout << "\n";
}

// Проверка победы
bool checkWin(char player) {
    // Горизонтали
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // Вертикали
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Диагонали
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    
    return false;
}

// Проверка, что поле заполнено (ничья)
bool isFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9')
                return false;
        }
    }
    return true;
}

int main() {
    char currentPlayer = 'X';
    int position;
    
    cout << "=== ИГРА КРЕСТИКИ-НОЛИКИ ===\n";
    cout << "Игрок X ходит первым.\n";
    cout << "Введите номер клетки (1-9):\n\n";
    
    while (true) {
        printBoard();
        
        cout << "Ход игрока " << currentPlayer << ". Введите номер (1-9): ";
        cin >> position;
        
        // Проверка корректности ввода
        if (position < 1 || position > 9) {
            cout << "Ошибка! Введите число от 1 до 9.\n";
            continue;
        }
        
        // Преобразуем номер в индексы массива
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        
        // Проверка, свободна ли клетка
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Эта клетка уже занята! Попробуйте другую.\n";
            continue;
        }
        
        // Ставим символ
        board[row][col] = currentPlayer;
        
        // Проверка победы
        if (checkWin(currentPlayer)) {
            printBoard();
            cout << "🎉 Игрок " << currentPlayer << " ПОБЕДИЛ! 🎉\n";
            break;
        }
        
        // Проверка ничьей
        if (isFull()) {
            printBoard();
            cout << "🤝 Ничья! Поле заполнено.\n";
            break;
        }
        
        // Смена игрока
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    cout << "Спасибо за игру! 👋\n";
    return 0;
}