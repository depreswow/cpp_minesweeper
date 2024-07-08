#pragma once
#include <iostream>
#include <vector>
#include <time.h>

class Square {
private:

    int type; //-1 - mine, 0-8 - empty
    bool closed;

    

public:

    Square();
    Square(int in_type);

    const int getType() const;
    const bool isClosed() const;

    friend int openSquare(std::vector<std::vector<Square>>& field, std::pair<int, int> openedSquare);

    friend std::ostream& operator<<(std::ostream& out, const Square& in_square);

    friend void generateMines(std::vector<std::vector<Square>>&, int mines, std::pair<int, int> opened);
};