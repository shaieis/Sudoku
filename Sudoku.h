#pragma once

#include <vector>
#include <utility> // for std::pair
#include <string>





class Sudoku {
public:

    using String = std::string;
    using Pos = std::pair<int, int>;
    using Board = std::vector<std::vector<char>>;

    Sudoku(const Board& board, char emptyCellChar = DEF_EMPTY_CELL_CHAR);

    // Tries to solve the board. if successful, returns true. 
    bool solve();

    // Checks if the board is in a valid state. a valid board may still be unsolvable.
    bool isValid() const;

    String toString() const;
    operator String() const { return toString(); };

    // Returns the value at index row, col.
    char& at(int row, int col); // non-const variant. Be carefull not to insert invalid chars
    char at(int row, int col) const;  // const variant

private:

    Board m_board;
    char m_emptyChar;

    static constexpr int SIZE = 9;
    static constexpr Pos INVALID_POS = { -1,-1 };
    static constexpr char DEF_EMPTY_CELL_CHAR = '.';

    bool checkRow(int row) const;
    bool checkCol(char col) const;
    bool checkSqr(int row, int col) const;

    Pos findNextEmpty() const;
    inline bool isValidChar(char c) const { return (c == m_emptyChar || (c >= '0' && c <= '9')); }
    inline int charToNum(char ch) const { return ch - '0'; };


};

