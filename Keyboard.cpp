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
  /* JEHUTTING */ printf("Keyboard::Keyboard()\n");
}

Keyboard::~Keyboard() 
{
  /* JEHUTTING */ printf("Keyboard::~Keyboard()\n");
}

void Keyboard::Open()
{
  /* JEHUTTING */ printf("Keyboard::Open()\n");
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
  /* JEHUTTING */ printf("Keyboard::Close()\n");
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
  int ch[8];
  int chnum = 0;

  while((ch[chnum] = getchar()) != EOF)
    chnum++;

  if (chnum == 0)
    return KeyConfig::ACTION_BLANK;

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

