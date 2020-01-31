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

Time::Time(int h, int m, int s): m_hour{h}, m_minute{m}, m_second{s} {
  if (h < 0 || h > 23
      || m < 0 || m > 59
      || s < 0 || s > 59) {
    throw std::exception();
  }
}

string extra_0(int n) {
  if (n < 10) {
    return "0";
  }
  else {
    return "";
  }
}

string Time::to_string() {
  stringstream ss{};
  ss << extra_0(m_hour) << m_hour
     << extra_0(m_minute) << m_minute
     << extra_0(m_second) << m_second;
  string s{};
  ss >> s;
  return s;
}

#endif
