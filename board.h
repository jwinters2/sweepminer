#include "cell.h"

class Board
{
  public:
    Board(int,int,int);
    ~Board();
    void start();

  private:
    int width;
    int height;
    int number_of_mines;
    int cursor_x;
    int cursor_y;
    bool still_going;
    bool board_is_untouched;

    Cell*** cells;

    void clearBoard();
    void generateMines();
    bool sweepCell();
    bool sweepCell(int,int);
    void printBoard(bool=false); 
    void calculateNumbers();
    bool isMine(int,int);
    int countFlags();
    bool IsInvalidCoord(int,int);
    bool isVictory();
    Cell* getCell(int,int);
};
