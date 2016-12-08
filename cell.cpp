#include "cell.h"

Cell::Cell()
{
  reset();
}

void Cell::reset()
{
  is_mine = false;
  adjacent=0;
  is_hidden = true;
  flag = 0;
}

int Cell::getAdjacent()
{
  return adjacent;
}

void Cell::setAdjacent(int n)
{
  adjacent=n;
}

bool Cell::getIsMine()
{
  return is_mine;
}

void Cell::setIsMine(bool b)
{
  is_mine = b;
}

bool Cell::getIsHidden()
{
  return is_hidden;
}

void Cell::setIsHidden(bool h)
{
  is_hidden = h;
}

void Cell::toggleFlag()
{
  flag++;
  if(flag>2)
  {
    flag=0;
  }
}

int Cell::getFlag()
{
  return flag;
}

const char* Cell::getChar(bool end)
{
  if(is_mine && end)
  {
    return "#";
  }
  if(is_hidden)
  {
    switch(flag)
    {
      case 0: return "-";
      case 1: return "*";
      case 2: return "?";
    }
  }
  switch(adjacent)
  {
    case 0: return " ";
    case 1: return "1";
    case 2: return "2";
    case 3: return "3";
    case 4: return "4";
    case 5: return "5";
    case 6: return "6";
    case 7: return "7";
    case 8: return "8";
  }
}
