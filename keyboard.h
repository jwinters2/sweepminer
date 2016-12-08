class Keyboard
{
  public:
    Keyboard();
    ~Keyboard();
    void update();
    bool up();
    bool down();
    bool left();
    bool right();
    bool enter();
    bool space();

  private:
    ALLEGRO_KEYBOARD_STATE *current;
    ALLEGRO_KEYBOARD_STATE *old;
    ALLEGRO_KEYBOARD_STATE *buffer;
};
