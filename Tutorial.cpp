#include <iostream>  // Для вывода в консоль
#include <conio.h>  // Для _kbhit() и _getch() (чтение клавиш без нажатия Enter)
#include <Windows.h> // Для управления консолью Windows


// попробую здесь


// Установка курсора в конкретную позицию (избавляет от мерцания экрана)
void SetCursor() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}



int main() {

    // Устанавливаем UTF-8 для вывода в консоль
    SetConsoleOutputCP(CP_UTF8);

    // Также устанавливаем локаль для корректной работы с русскими строками
    setlocale(LC_ALL, "Russian");

    // размер арты 20 на 20
    char player = '@';  // символ для игрока
    int xp = 10;   // x координата игрока
    int yp = 10;   // y координата игрока

    std::cout << "Управление: WASD / Стрелки. ESC - выход." << std::endl;
    
    // Главный игровой цикл (Game Loop) 
    // бесконечный цикл
    while (true) {
        if (_kbhit()) { // Проверяем, была ли нажата клавиша
            int key = _getch();
            int dx = 0, dy = 0;

            // WASD
            if (key == 'w' || key == 'W') dy = -1;
            else if (key == 's' || key == 'S') dy = 1;
            else if (key == 'a' || key == 'A') dx = -1;
            else if (key == 'd' || key == 'D') dx = 1;


            // Расчет новой позиции
            int newX = xp + dx;
            int newY = yp + dy;

            // Проверка столкновений (коллизия со стенами)
            if (newX >= 0 && newX < 20 && newY >= 0 && newY < 20) {
                if (newY < 20 || newX < 20) { // Если не стена, двигаемся
                    // устанавливаем координаты
                    xp = newX;
                    yp = newY;
                }
            }

            //устанавливаем курсуор в начало и поверх старого
            SetCursor();

            // отрисовываем карту
            // проходим в цикле по x и y
            for (int y = 0; y <= 20; ++y) {
                for (int x = 0; x <= 20; ++x) {
                    if (x == xp && y == yp) {
                        //игрок
                        std::cout << player;
                    }
                    else if (y == 20 || x == 20) {
                        std::cout << "#";  // стены
                    }
                    else {
                        std::cout << " ";  // пол
                    }
                }
                std::cout << '\n';
            }
            std::cout << "Управление: WASD / Стрелки. ESC - выход." << std::endl;
        }
    }

    return 0;
}