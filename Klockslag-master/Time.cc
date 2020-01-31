// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#ifndef __TIME_H__
#define __TIME_H__

#include "Time.h"

using namespace std;



int Time::hour() {
  return m_hour;
}

int Time::minute() {
  return m_minute;
}

int Time::second() {
  return m_second;
}

Time::Time() : m_hour{0}, m_minute{0}, m_second{0} {
}

void validate_params(int h, int m, int s) {
  if (h < 0 || h > 23
      || m < 0 || m > 59
      || s < 0 || s > 59) {
    throw std::exception();
  }
}

void validate_params(Time & t) {
  validate_params(t.hour(), t.minute(), t.second());
}

Time::Time(int h, int m, int s): m_hour{h}, m_minute{m}, m_second{s} {
  validate_params(*this);
}

Time::Time(string const & s) {
  stringstream ss{};
  ss << s;
  char c;
  ss >> m_hour >> c >> m_minute >> c >> m_second;

  validate_params(m_hour, m_minute, m_second);
}

string extra_0s(int n) {
  if (n < 10) {
    return "0";
  }
  else {
    return "";
  }
}

bool Time::is_am() {
  return m_hour < 12;
}

string Time::to_string(bool am_pm ) {
  int hour = m_hour;
  if (am_pm) {
    hour %= 12;
  }
  stringstream ss{};
  ss << extra_0s(hour) << hour
     << ':'
     << extra_0s(m_minute) << m_minute
     << ':'
     << extra_0s(m_second) << m_second
     << ' '
     << am_pm ? (is_am() ? "am" : "pm") : "";
  string s{};
  ss >> s;
  return s;
}

#endif
