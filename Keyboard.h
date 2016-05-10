
#include <map>

class Keyboard
{
public:
  Keyboard();
  ~Keyboard();
  void Close();
  void setKeymap(std::map<int,int> keymap);
  int getEvent();
private:
  struct termios orig_termios;
  int orig_fl;
  std::map<int,int> m_keymap;
  void restore_term();
};
