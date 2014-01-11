#pragma once

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

#include <map>
#include "KeyConfig.h"

class Keyboard
{
  public:
    Keyboard();
    ~Keyboard();
    void Open();
    void Close();
    KeyConfig::Action GetEvent();
    void SetKeymap(std::string filepath);
  private:
    void RestoreTerm();

    struct termios orig_termios;
    int orig_fl;
    std::map<int,int> m_keymap;
};
