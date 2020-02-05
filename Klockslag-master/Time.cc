// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#ifndef __TIME_H__
#define __TIME_H__

#include "Time.h"

#include <iostream>
#include <stdlib.h>

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

Time::Time(string const & s) : m_hour{0}, m_minute{0}, m_second{0} {
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
  if (am_pm && !is_am()) {
    hour -= 12;
  }
  stringstream ss{};
  ss << extra_0s(hour) << hour
     << ':'
     << extra_0s(m_minute) << m_minute
     << ':'
     << extra_0s(m_second) << m_second;
  if (am_pm) {
    ss << ' ';
    if (is_am()) {
      ss << "am";
    } else {
      ss << "pm";
    }
  }
  string s{};
  getline(ss, s);
  return s;
}

Time::operator string() {
  return to_string();
}

int real_mod(int a, int b) {
  return ((a%b)+b)%b;
}

Time Time::operator+(int x) {
  int seconds = (x + m_second);
  int minutes = ((seconds / 60) + m_minute);
  if (seconds < 0) {
    minutes--;
  }
  int hours = ((minutes / 60) + m_hour);
  if (minutes < 0) {
    hours--;
  }
  return Time{real_mod(hours, 24), real_mod(minutes, 60), real_mod(seconds, 60)};
}

Time Time::operator-(int x) {
  return (*this)+(-x);
}

Time Time::operator++() {
  return (*this)+1;
}

Time Time::operator--() {
  return (*this)-1;
}

bool Time::operator<(Time that) {
  return
  (hour() < that.hour())
  ||
  (
    (hour() == that.hour()) && (
      (minute() < that.minute())
      ||
      (
        (minute() == that.minute()) && (second() < that.second())
      )
    )
  );
}

bool Time::operator==(Time that) {
  return
  (hour() == that.hour()) &&
  (minute() == that.minute()) &&
  (second() == that.second());
}

bool Time::operator>Time that {
  return (that<(*this));
}

#endif
