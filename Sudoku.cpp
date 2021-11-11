#include "Sudoku.h"

#include <sstream> // for toString()

Sudoku::Sudoku(const Board& board, char emptyCellChar) :
    m_board(board), m_emptyChar(emptyCellChar)
{
    if (emptyCellChar >= '0' && emptyCellChar <= '9')
        throw std::exception("Invalid emptyCellChar");

    if (board.size() != SIZE)
        throw std::exception("Invalid num of rows");
    
    for (const auto& row : board)
    {
        if (row.size() != SIZE)
        {
            throw std::exception("Invalid num of columns");
        }
        for (char val : row)
        {
            if (!isValidChar(val))
            {
                throw std::exception("Invalid char in board");
            }
        }
    }
        
}
bool Sudoku::solve()
{
    if (!isValid())
        return false;

    const auto& nextAvailable = findNextEmpty();
    if (nextAvailable == INVALID_POS)
        return true;


    for (char c = '1'; c <= '9'; c++)
    {
        m_board[nextAvailable.first][nextAvailable.second] = c;
        if (solve())
            return true;
    }

    m_board[nextAvailable.first][nextAvailable.second] = m_emptyChar;
    return false;
}

bool Sudoku::isValid() const
{
    for (int i = 0; i < SIZE; i++)
    {
        if (!checkRow(i) || !checkCol(i))
            return false;
    }

    for (int i = 0; i < SIZE; i += SIZE / 3)
        for (int j = 0; j < SIZE; j += SIZE / 3)
        {
            if (!checkSqr(i, j))
                return false;
        }

    return true;
}

Sudoku::String Sudoku::toString() const
{
    std::stringstream ss;
    for (int i = 0; i < SIZE; i++)
    {
        if (i != 0 && (i % (SIZE / 3) == 0))
            ss << "-------+--------+------" << std::endl;

        for (int j = 0; j < SIZE; j++)
        {
            if (j != 0 && (j % (SIZE / 3) == 0))
                ss << " | ";
            ss << m_board[i][j] << " ";
        }

        if (i != SIZE - 1)
            ss << std::endl;

    }
    ss << std::endl;
    ss << "is valid: " << (isValid() ? "True" : "False") << std::endl;
    return ss.str();
}


// Returns the value at index row, col. Be carefull not to insert invalid chars
char& Sudoku::at(int row, int col) 
{ 
    if (row < 0 || col < 0 || row > SIZE || col > SIZE)
        throw std::out_of_range("row or col out of bounds");

    return m_board[row][col]; 
}; 

char Sudoku::at(int row, int col) const
{
    if (row < 0 || col < 0 || row > SIZE || col > SIZE)
        throw std::out_of_range("row or col out of bounds");

    return m_board[row][col]; 
}; 

/* ============== private functions ============== */

bool Sudoku::checkRow(int row) const
{
    bool values[SIZE + 1] = { false };
    for (char val : m_board[row])
    {
        if (val == m_emptyChar) continue;
        if (values[charToNum(val)] == true)
            return false;
        values[charToNum(val)] = true;
    }

    return true;
}

bool Sudoku::checkCol(char col) const
{
    bool values[SIZE + 1] = { false };
    for (int row = 0; row < SIZE; row++)
    {

        char val = m_board[row][col];
        if (val == m_emptyChar) continue;
        if (values[charToNum(val)] == true)
            return false;

        values[charToNum(val)] = true;
    }

    return true;
}

// check a 3 X 3 sub table starting at row, col
bool Sudoku::checkSqr(int row, int col) const
{
    bool values[SIZE + 1] = { false };
    for (int i = row; i < row + SIZE / 3; i++)
        for (int j = col; j < col + SIZE / 3; j++)
        {
            char val = m_board[i][j];

            if (val == m_emptyChar) continue;
            if (values[charToNum(val)] == true)
                return false;

            values[charToNum(val)] = true;
        }
    return true;
}

Sudoku::Pos Sudoku::findNextEmpty() const
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (m_board[i][j] == '.')
                return { i,j };

    return INVALID_POS;
}

