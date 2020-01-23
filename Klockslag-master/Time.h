// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs

#include <exception>
#include <string>
#include <sstream>

class Time {
 public:
  Time();
  Time(int h, int m, int s);
  
  int hour();
  int minute();
  int second();

  std::string to_string();
 private:
  int m_hour;
  int m_minute;
  int m_second;
};
