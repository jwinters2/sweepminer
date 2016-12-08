#include "keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
  current = new ALLEGRO_KEYBOARD_STATE();
  old = new ALLEGRO_KEYBOARD_STATE();
  al_get_keyboard_state(current);
}

Keyboard::~Keyboard()
{
  delete current;
  delete old;
}

void Keyboard::update()
{
  buffer = old;
  old = current;
  current = buffer;
  al_get_keyboard_state(current);
}

bool Keyboard::up()
{
  int key = ALLEGRO_KEY_UP;
  return (al_key_down(current,key) && !al_key_down(old,key));
}

bool Keyboard::down()
{
  int key = ALLEGRO_KEY_DOWN;
  return (al_key_down(current,key) && !al_key_down(old,key));
}

bool Keyboard::left()
{
  int key = ALLEGRO_KEY_LEFT;
  return (al_key_down(current,key) && !al_key_down(old,key));
}

bool Keyboard::right()
{
  int key = ALLEGRO_KEY_RIGHT;
  return (al_key_down(current,key) && !al_key_down(old,key));
}

bool Keyboard::enter()
{
  int key = ALLEGRO_KEY_ENTER;
  return (al_key_down(current,key) && !al_key_down(old,key));
}

bool Keyboard::space()
{
  int key = ALLEGRO_KEY_SPACE;
  return (al_key_down(current,key) && !al_key_down(old,key));
}
