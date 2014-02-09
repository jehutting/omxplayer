/*
 *      Copyright (C) 2013 Harry Collard
 *                    2014 Jozef Hutting
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "Keyboard.h"

Keyboard::Keyboard() 
{
}

Keyboard::~Keyboard() 
{
}

void Keyboard::Open()
{
  if (isatty(STDIN_FILENO)) 
  {
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, &orig_termios);

    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO | ECHOCTL | ECHONL);
    new_termios.c_cflag |= HUPCL;
    new_termios.c_cc[VMIN] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
  } 
  else 
  {    
    orig_fl = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, orig_fl | O_NONBLOCK);
  }

  m_keymap = KeyConfig::buildDefaultKeymap();
}

void Keyboard::Close()
{
  RestoreTerm();
}

void Keyboard::RestoreTerm() 
{
  if (isatty(STDIN_FILENO)) 
  {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
  } 
  else 
  {
    fcntl(STDIN_FILENO, F_SETFL, orig_fl);
  }
}

KeyConfig::Action Keyboard::GetEvent() 
{
  // An arrow key consists of a three character sequence:
  //   0x1b (=ESC), 0x5b (='[') and ARROW
  // where ARROW = 0x41 (='A') for arrow up
  //             = 0x42 (='B') for arrow down
  //             = 0x42 (='C') for arrow right
  //             = 0x42 (='D') for arrow left
  int ch[3]; // Handle max ONE arrow key at a time.
  int chnum = 0;

  while((chnum < 3) && ((ch[chnum] = getchar()) != EOF))
    chnum++;

  if (chnum == 0)
    return KeyConfig::ACTION_BLANK;

  // KeyConfig uses only the last two characters of an arrow key
  if (chnum > 1) 
    ch[0] = ch[chnum - 1] | (ch[chnum - 2] << 8);

  auto it = m_keymap.find(ch[0]);
  if(it != m_keymap.end())
    return (enum KeyConfig::Action)it->second;
  else
    return KeyConfig::ACTION_BLANK;
}

void Keyboard::SetKeymap(std::string filepath) 
{
  m_keymap = KeyConfig::parseConfigFile(filepath);
}

