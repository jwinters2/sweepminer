#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <ncurses.h>
#include "board.h"

Board::Board(int width_a,int height_a,int number_of_mines_a)
{
  width = width_a;
  height = height_a;
  number_of_mines = number_of_mines_a;

  cursor_x = width / 2;
  cursor_y = height / 2;

  still_going = true;
  board_is_untouched = true;

  cells = new Cell**[width];
  for(int i=0;i<width;i++)
  {
    cells[i] = new Cell*[height];
  }

  srand(time(NULL));
  clearBoard();
}

Board::~Board()
{
  endwin();
  for(int x=0;x<width;x++)
  {
    for(int y=0;y<height;y++)
    {
      delete cells[x][y];
    }
    delete [] cells[x];
  }
  delete [] cells;
}

void Board::start()
{
  initscr();
  curs_set(0);
  start_color();

  init_pair('1',COLOR_CYAN,COLOR_BLACK);
  init_pair('2',COLOR_GREEN,COLOR_BLACK);
  init_pair('3',COLOR_YELLOW,COLOR_BLACK);
  init_pair('4',COLOR_MAGENTA,COLOR_BLACK);
  init_pair('5',COLOR_CYAN,COLOR_BLACK);
  init_pair('6',COLOR_GREEN,COLOR_BLACK);
  init_pair('7',COLOR_YELLOW,COLOR_BLACK);
  init_pair('8',COLOR_MAGENTA,COLOR_BLACK);

  init_pair('#',COLOR_RED,COLOR_BLACK);

  keypad(stdscr,true);
  int ch = 0;

  while(still_going)
  {
    switch(ch)
    {
      case KEY_UP:
      case 'k':
        cursor_y--;
        if(cursor_y < 0)
        {
          cursor_y++;
        }
        break;
        
      case KEY_DOWN:
      case 'j':
        cursor_y++;
        if(cursor_y >= height)
        {
          cursor_y--;
        }
        break;

      case KEY_LEFT:
      case 'h':
        cursor_x--;
        if(cursor_x < 0)
        {
          cursor_x++;
        }
        break;

      case KEY_RIGHT:
      case 'l':
        cursor_x++;
        if(cursor_x >= width)
        {
          cursor_x--;
        }
        break;

      case 'f':
        if(!sweepCell())
        {
          clear();
          printBoard(true);
          printw("\n");
          for(int i=0;i<(COLS/2)-9;i++)
          {
            printw(" ");
          }
          attron(COLOR_PAIR('#') | A_BOLD);
          printw("YOU LOSE DUMBFUCK!!!");
          attroff(COLOR_PAIR('#') | A_BOLD);
          getch();
          return;
        }
        break;

      case 'g':
        cells[cursor_x][cursor_y]->toggleFlag();
        break;

      case 'q':
        return;
    }
    if(isVictory())
    {
      clear();
      printBoard();
      printw("\n");
      for(int i=0;i<(COLS/2)-7;i++)
      {
        printw(" ");
      }
      attron(COLOR_PAIR('1') | A_BOLD);
      printw("YOU'RE WINNER!!!");
      attroff(COLOR_PAIR('1') | A_BOLD);
      getch();
      return;
    }
    printBoard();
    refresh();
    ch = getch();
  }
}

void Board::clearBoard()
{
  for(int x=0;x<width;x++)
  {
    for(int y=0;y<height;y++)
    {
      if(cells[x][y] == NULL)
      {
        cells[x][y] = new Cell();
      }
      else
      {
        cells[x][y]->reset();
      }
    }
  }
}

void Board::generateMines()
{
  if(number_of_mines >= (width*height))
  {
    for(int x=0;x<width;x++)
    {
      for(int y=0;y<height;y++)
      {
        cells[x][y]->setIsMine(true);
      }
    }
    return;
  }

  int rand_x;
  int rand_y;
  for(int i=0;i<number_of_mines;i++)
  {
    rand_x = rand() % width;
    rand_y = rand() % height;

    if(rand_x < 0)
    {
      rand_x *= -1;
    }
    if(rand_y < 0)
    {
      rand_y *= -1;
    }

    if(cells[rand_x][rand_y]->getIsMine() || 
      (cursor_x == rand_x && cursor_y == rand_y))
    {
      i--;
    }
    else
    {
      cells[rand_x][rand_y]->setIsMine(true);
    }
  }
}

void Board::calculateNumbers()
{
  for(int x=0;x<width;x++)
  {
    for(int y=0;y<height;y++)
    {
      int count = 0;
      for(int i=-1;i<=1;i++)
      {
        for(int j=-1;j<=1;j++)
        {
          if( !(i==0 && j==0) && isMine(x+i,y+j))
          {
            count++;
          }
        }
      }

      cells[x][y]->setAdjacent(count);
    }
  }
}

bool Board::isMine(int x,int y)
{
  if(IsInvalidCoord(x,y))
  {
    return false;
  }
  return cells[x][y]->getIsMine();
}

bool Board::sweepCell()
{
  if(board_is_untouched)
  {
    clearBoard();
    generateMines();
    calculateNumbers();
    board_is_untouched = false;
  }
  return sweepCell(cursor_x,cursor_y);
}

bool Board::sweepCell(int x,int y)
{
  if(IsInvalidCoord(x,y))
  {
    return false;
  }

  bool recursive = cells[x][y]->getIsHidden();

  cells[x][y]->setIsHidden(false);
  if(cells[x][y]->getIsMine())
  {
    still_going = false;
    return false;
  }
  else if(cells[x][y]->getAdjacent() == 0 && recursive)
  {
    for(int i=-1;i<=1;i++)
    {
      for(int j=-1;j<=1;j++)
      {
        if( !(i==0 && j==0) )
        {
          sweepCell(x+i,y+j);
        }
      }
    }
  }
  return true;
}

void Board::printBoard(bool end)
{
  clear();
  printw("  CONTROLS:\n");
  printw("  ARROW KEYS + HJKL : MOVE\n");
  printw("  F : CLICK A MINE\n");
  printw("  G : PLACE FLAG\n");
  printw("  Q : QUIT\n");
  printw("\n");

  for(int i=0;i<(COLS/2)-width;i++)
  {
    printw(" ");
  }
  printw("+-");
  for(int x=0;x<width;x++)
  {
    printw("--");
  }
  printw("+\n");
  for(int y=0;y<height;y++)
  {
    for(int i=0;i<(COLS/2)-width;i++)
    {
      printw(" ");
    }
    printw("| ");
    for(int x=0;x<width;x++)
    {
      char c = cells[x][y]->getChar(end)[0];
      if( (c>='1' && c<='8') || c=='#')
      {
        attron(COLOR_PAIR(c));
        if( c>='5' || c=='#')
        {
          attron(A_BOLD);
          printw(cells[x][y]->getChar(end));
          attroff(A_BOLD);
        }
        else
        {
          printw(cells[x][y]->getChar(end));
        }
        attroff(COLOR_PAIR(c));
      }
      else
      {
        printw(cells[x][y]->getChar(end));
      }
      if(x==cursor_x && y==cursor_y)
      {
        printw("]");
      }
      else
      {
        printw(" ");
      }
    }
    printw("|\n");
  }
  for(int i=0;i<(COLS/2)-width;i++)
  {
    printw(" ");
  }
  printw("+-");
  for(int x=0;x<width;x++)
  {
    printw("--");
  }
  printw("+\n");
  for(int i=0;i<(COLS/2)-width;i++)
  {
    printw(" ");
  }
  printw("Mines Found: %d/%d",countFlags(),number_of_mines);
}

Cell* Board::getCell(int x,int y)
{
  if(IsInvalidCoord(x,y))
  {
    return NULL;
  }
  if(cells == NULL)
  {
    return NULL;
  }
  if(cells[x] == NULL)
  {
    return NULL;
  }
  return cells[x][y];
}

int Board::countFlags()
{
  int retval = 0;
  for(int x=0;x<width;x++)
  {
    for(int y=0;y<height;y++)
    {
      if(cells[x][y]->getFlag() == 1 && cells[x][y]->getIsHidden())
      {
        retval++;
      }
    }
  }
  return retval;
}

bool Board::IsInvalidCoord(int x,int y)
{
  return (x<0 || x>= width || y<0 || y>=height);
}

bool Board::isVictory()
{
  if(countFlags() != number_of_mines)
  {
    return false;
  }

  for(int y=0;y<height;y++)
  {
    for(int x=0;x<width;x++)
    {
      if(!cells[x][y]->getIsMine() && cells[x][y]->getIsHidden())
      {
        return false;
      }
    }
  }
  return true;
}
