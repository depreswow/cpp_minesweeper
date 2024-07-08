#include "square.h"
#include <vector>


Square::Square()
    : type(0), closed(true) {}

Square::Square(int in_type)
    : type(in_type), closed(true) {}

const int Square::getType() const {
    return type;
}

const bool Square::isClosed() const {
    return closed;
}

int openSquare(std::vector<std::vector<Square>>& field, std::pair<int, int> openedSquare) {
    int i = openedSquare.first;
    int j = openedSquare.second;
    if (field[i][j].isClosed()) {
        field[i][j].closed = false;
        if (field[i][j].type == -1)
            return -1;
        if (field[i][j].type > 0)
            return 1;

        int answer = 1;
        
        if (i > 0 && field[i-1][j].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i - 1, j));

        if (i > 0 && j < field[i].size()-1 && field[i-1][j+1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i - 1, j + 1));

        if (j < field[i].size()-1 && field[i][j+1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i, j + 1));

        if (i < field.size()-1 && j < field[i].size()-1 && field[i+1][j+1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i + 1, j + 1));

        if (i < field.size()-1 && field[i+1][j].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i + 1, j));

        if (i < field.size()-1 && j > 0 && field[i+1][j-1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i + 1, j - 1));

        if (j > 0 && field[i][j-1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i, j - 1));

        if (i > 0 && j > 0 && field[i-1][j-1].getType() != -1)
            answer += openSquare(field, std::pair<int, int>(i - 1, j - 1));

        return answer;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Square& in_square) {
    if (in_square.isClosed())
        out << '#';
    else {
        switch (in_square.getType()) {
        case -1:
            out << '*';
            break;
        case 0:
            out << ' ';
            break;
        default:
            out << in_square.getType();
            break;
        }
    }
    return out;
}

void generateMines(std::vector<std::vector<Square>>& in_field, int mines, std::pair<int, int> openedSquare) {
    srand(time(0));

    std::pair<int, int> mine_coords;

    for (int k = 0; k < mines; k++) {

        do {
            mine_coords = std::pair<int, int>(rand()%in_field.size(), rand()%in_field[0].size());
        } while (in_field[mine_coords.first][mine_coords.second].getType() == -1 || (mine_coords == openedSquare));

        int i = mine_coords.first, j = mine_coords.second;

        in_field[i][j] = Square(-1);

        if (i > 0 && in_field[i - 1][j].getType() != -1)
            in_field[i - 1][j].type++;

        if (i > 0 && j < in_field[i].size() - 1 && in_field[i - 1][j + 1].getType() != -1)
            in_field[i - 1][j + 1].type++;

        if (j < in_field[i].size() - 1 && in_field[i][j + 1].getType() != -1)
            in_field[i][j + 1].type++;

        if (i < in_field.size() - 1 && j < in_field[i].size() - 1 && in_field[i + 1][j + 1].getType() != -1)
            in_field[i + 1][j + 1].type++;

        if (i < in_field.size() - 1 && in_field[i + 1][j].getType() != -1)
            in_field[i + 1][j].type++;

        if (i < in_field.size() - 1 && j > 0 && in_field[i + 1][j - 1].getType() != -1)
            in_field[i + 1][j - 1].type++;

        if (j > 0 && in_field[i][j - 1].getType() != -1)
            in_field[i][j - 1].type++;

        if (i > 0 && j > 0 && in_field[i - 1][j - 1].getType() != -1)
            in_field[i - 1][j - 1].type++;

    }
}