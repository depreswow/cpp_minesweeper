#include "Windows.h"
#include "square.h"
#include <iomanip>

void generateMines(std::vector<std::vector<Square>>&, int mines, std::pair<int, int> opened);

void printLogo() {
    system("cls");
    std::cout << R"(  __  __ _                                                   
 |  \/  (_)                                                  
 | \  / |_ _ __   ___  _____      _____  ___ _ __   ___ _ __ 
 | |\/| | | '_ \ / _ \/ __\ \ /\ / / _ \/ _ \ '_ \ / _ \ '__|
 | |  | | | | | |  __/\__ \\ V  V /  __/  __/ |_) |  __/ |   
 |_|  |_|_|_| |_|\___||___/ \_/\_/ \___|\___| .__/ \___|_|   
                                            | |              
                                            |_|              )" << std::endl << std::endl;
}

void printField(const std::vector<std::vector<Square>>& in_field) {
    printLogo();

    std::cout << "\t   "; //numbers on top
    for (int i = 0; i < in_field[0].size(); i++)
        std::cout << std::setw(2) << i << " ";
    std::cout << std::endl;

    std::cout << "\t  "; //line on top
    for (int i = 0; i < in_field[0].size(); i++)
        std::cout << "---";
    std::cout << "--" << std::endl;

    for (int i = 0; i < in_field.size(); i++) {
        std::cout << "\t" << std::setw(2) << i << "|";
        for (int j = 0; j < in_field[i].size(); j++)
            std::cout << std::setw(2) << in_field[i][j] << " ";
        std::cout << "|" << std::endl;
    }

    std::cout << "\t  "; //line at the bottom
    for (int i = 0; i < in_field[0].size(); i++)
        std::cout << "---";
    std::cout << "--" << std::endl << std::endl;
}

std::vector<std::vector<Square>> createField(int width, int height) {
    std::vector<std::vector<Square>> field(height);
    for (int i = 0; i < height; i++)
        field[i] = std::vector<Square>(width);
    return field;
}

void openField(std::vector<std::vector<Square>>& in_field) {
    for (int i = 0; i < in_field.size(); i++) {
        for (int j = 0; j < in_field[0].size(); j++)
            openSquare(in_field, std::pair<int, int>(i, j));
    }
}

std::pair<int, int> inputCoordinates(int width, int height) {
    int i, j;
    std::cout << "Enter coordinates of a square to open (-7, -8 to leave): ";
    do {
        std::cin >> i >> j;
        if (i == -7 && j == -8) {
            break;
        }
    } while (i < 0 || j < 0 || i >= height || j >= width);
    return std::pair<int, int>(i, j);
}

int main() {

    int WIDTH;
    int HEIGHT;
    int MINES;

    printLogo();

    std::cout << "Enter width, height, mines: " << std::endl;
    do {
        std::cin >> WIDTH >> HEIGHT >> MINES;
    } while (WIDTH < 1 || HEIGHT < 1 || MINES < 1 || MINES >= (WIDTH*HEIGHT));

    std::vector<std::vector<Square>> field = createField(WIDTH, HEIGHT);
    bool game_on = true;
    int openSquares = 0;
    int opened;
    char restart = ' ';
    std::pair<int, int> coordinates;

    while (game_on) {
        printField(field);
        
        coordinates = inputCoordinates(WIDTH, HEIGHT);

        if (coordinates.first == -7 && coordinates.second == -8)
            break;

        if (openSquares == 0) {
            generateMines(field, MINES, coordinates);
        }

        opened = openSquare(field, coordinates);

        if (opened == -1) {
            openField(field);
            printField(field);
            std::cout << "You lost bozo" << std::endl << std::endl;
            game_on = false;
        }
        else {
            openSquares += opened;
        }

        if (openSquares == (WIDTH * HEIGHT - MINES)) {
            printField(field);
            std::cout << "Yot won yipee" << std::endl;
            game_on = false;
        }

        if (game_on == false) {
            std::cout << "Try again(y/n): ";
            do {
                std::cin >> restart;
            } while (std::tolower(restart) != 'y' && std::tolower(restart) != 'n');
            if (std::tolower(restart) == 'y') {
                game_on = true;
                openSquares = 0;
                field = createField(WIDTH, HEIGHT);
            }
        }
    
    }
    system("pause");
}