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

#define OMXPLAYER_DBUS_NAME "org.mpris.MediaPlayer2.omxplayer"
#define OMXPLAYER_DBUS_PATH_SERVER "/org/mpris/MediaPlayer2"  
#define OMXPLAYER_DBUS_INTERFACE_ROOT "org.mpris.MediaPlayer2"
#define OMXPLAYER_DBUS_INTERFACE_PLAYER "org.mpris.MediaPlayer2.Player"

#include <dbus/dbus.h>
#include "OMXClock.h"
#include "OMXPlayerAudio.h"

#include "KeyConfig.h"

class OMXControl
{
protected:
  DBusConnection *bus;
  OMXClock       *clock;
  OMXPlayerAudio *audio;
public:
  OMXControl();
  ~OMXControl();
  void Open(OMXClock *m_av_clock, OMXPlayerAudio *m_player_audio);
  void Close();
  KeyConfig::Action GetEvent();
private:
  void dispatch();
  int dbus_connect();
  void dbus_disconnect();
  DBusHandlerResult dbus_respond_ok(DBusMessage *m);
  DBusHandlerResult dbus_respond_int64(DBusMessage *m, int64_t i);
  DBusHandlerResult dbus_respond_double(DBusMessage *m, double d);
  DBusHandlerResult dbus_respond_boolean(DBusMessage *m, int b);
  DBusHandlerResult dbus_respond_string(DBusMessage *m, const char *text);
  DBusHandlerResult dbus_respond_array(DBusMessage *m, const char *array[], int size);
};

