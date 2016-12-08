class Cell
{
  public:
    Cell();
    void reset();
    int getAdjacent();
    void setAdjacent(int);
    bool getIsMine();
    void setIsMine(bool);
    bool getIsHidden();
    void setIsHidden(bool);
    void toggleFlag();
    int getFlag();
    const char* getChar(bool=false);

  private:
    int adjacent;
    bool is_mine;
    bool is_hidden;
    int flag;
};
