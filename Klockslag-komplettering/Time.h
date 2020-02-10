// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs

#include <exception>
#include <string>
#include <sstream>

//TODO: Parametrar som inte modifieras ska vara const alt. const reference.
class Time {
 public:
  Time();
  Time(int h, int m, int s);
  Time(std::string const & s);

  int hour() const;
  int minute() const;
  int second() const;

  bool is_am() const;

  std::string to_string(bool am_pm = false) const;

  operator std::string() const;
  Time operator+(int x) const;
  Time operator-(int x) const;

  Time operator++(int);
  Time& operator++();
  Time operator--(int);
  Time& operator--();

  bool operator<(Time that) const;
  bool operator>(Time that) const;
  bool operator==(Time that) const;
 private:
  int m_hour;
  int m_minute;
  int m_second;
};

std::ostream& operator <<(std::ostream & lhs, Time const& rhs);
std::istream& operator >>(std::istream & lhs, Time & rhs);
