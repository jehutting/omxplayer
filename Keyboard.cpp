#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "utils/log.h"
#include "Keyboard.h"
#include "KeyConfig.h"


Keyboard::Keyboard() 
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
}

Keyboard::~Keyboard() 
{
  Close();
}

void Keyboard::Close()
{
  restore_term();
}

void Keyboard::restore_term() 
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

int Keyboard::getEvent()
{
  int ch[8];
  int chnum = 0;

  while ((ch[chnum] = getchar()) != EOF) chnum++;

  if (chnum > 1) ch[0] = ch[chnum - 1] | (ch[chnum - 2] << 8);

  if (chnum > 0)
  {
    CLog::Log(LOGDEBUG, "Keyboard: character %c (0x%x)", ch[0], ch[0]);

    return m_keymap[ch[0]];
  }

  return -1;
}

void Keyboard::setKeymap(std::map<int,int> keymap) 
{
  m_keymap = keymap;
}

