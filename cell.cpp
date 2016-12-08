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
  const char* retval;

  if(is_mine && end)
  {
    retval = "#";
  }
  else if(is_hidden)
  {
    switch(flag)
    {
      case 0: retval = "-"; break;
      case 1: retval = "*"; break;
      case 2: retval = "?"; break;
    }
  }
  else switch(adjacent)
  {
    case 0: retval = " "; break;
    case 1: retval = "1"; break;
    case 2: retval = "2"; break;
    case 3: retval = "3"; break;
    case 4: retval = "4"; break;
    case 5: retval = "5"; break;
    case 6: retval = "6"; break;
    case 7: retval = "7"; break;
    case 8: retval = "8"; break;
  }
  return retval;
}
