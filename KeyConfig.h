#pragma once

/*
 *      Copyright (C) 2013 Mitchell Draves
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
#include <string>

class KeyConfig
{

  public: 
    enum Action
    {
        ACTION_DECREASE_SPEED = 1,
        ACTION_INCREASE_SPEED,
        ACTION_REWIND,
        ACTION_FAST_FORWARD,
        ACTION_SHOW_INFO,
        ACTION_PREVIOUS_AUDIO,
        ACTION_NEXT_AUDIO,
        ACTION_PREVIOUS_CHAPTER,
        ACTION_NEXT_CHAPTER,
        ACTION_PREVIOUS_SUBTITLE,
        ACTION_NEXT_SUBTITLE,
        ACTION_TOGGLE_SUBTITLE,
        ACTION_DECREASE_SUBTITLE_DELAY,
        ACTION_INCREASE_SUBTITLE_DELAY,
        ACTION_EXIT,
        ACTION_PAUSE,
        ACTION_DECREASE_VOLUME,
        ACTION_INCREASE_VOLUME,
        ACTION_SEEK_BACK_SMALL,
        ACTION_SEEK_FORWARD_SMALL,
        ACTION_SEEK_BACK_LARGE,
        ACTION_SEEK_FORWARD_LARGE,
        ACTION_STEP,
        ACTION_BLANK
    };

    #define KEY_LEFT 0x5b44
    #define KEY_RIGHT 0x5b43
    #define KEY_UP 0x5b41
    #define KEY_DOWN 0x5b42
    #define KEY_ESC 27

    static std::map<int, int> buildDefaultKeymap();
    static std::map<int, int> parseConfigFile(std::string filepath);
};
