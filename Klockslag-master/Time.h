// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs

#include <exception>
#include <string>
#include <sstream>

class Time {
 public:
  Time();
  Time(int h, int m, int s);
  Time(std::string const & s);

  int hour() const;
  int minute() const;
  int second() const;

  bool is_am();

  std::string to_string(bool am_pm = false);

  operator std::string();
  Time operator+(int x);
  Time operator-(int x);

  Time operator++();
  Time operator--();

  bool operator<(Time that) const;
  bool operator>(Time that) const;
  bool operator==(Time that) const;
 private:
  int m_hour;
  int m_minute;
  int m_second;
};
