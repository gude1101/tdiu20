// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#ifndef __TIME_H__
#define __TIME_H__

#include "Time.h"

#include <iostream>
#include <stdlib.h>

using namespace std;



int Time::hour() const {
  return m_hour;
}

int Time::minute() const {
  return m_minute;
}

int Time::second() const {
  return m_second;
}

Time::Time() : m_hour{0}, m_minute{0}, m_second{0} {
}

void Time::validate_params() {
  int h = m_hour;
  int m = m_minute;
  int s = m_second;
  if (h < 0 || h > 23
      || m < 0 || m > 59
      || s < 0 || s > 59) {
    throw std::invalid_argument("Wrong time format.");
  }
}

Time::Time(int h, int m, int s): m_hour{h}, m_minute{m}, m_second{s} {
  validate_params();
}

Time::Time(string const & s) : m_hour{0}, m_minute{0}, m_second{0} {
  stringstream ss{};
  ss << s;
  char c;
  ss >> m_hour >> c >> m_minute >> c >> m_second;

  validate_params();
}
const
string extra_0s(int n) {
  if (n < 10) {
    return "0";
  }
  else {
    return "";
  }
}

bool Time::is_am() const {
  return m_hour < 12;
}

string Time::to_string(bool am_pm ) const {
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

  //Kommentar: stringstream har en funktion som heter str()
  //Ni hade kunnat skriva "return ss.str();"
  return ss.str();
}

Time::operator string() const {
  return to_string();
}

int Time::real_mod(int a, int b) const {
  return ((a%b)+b)%b;
}

Time Time::operator+(int x) const {
  int seconds = (x + m_second);
  int minutes = ((seconds / 60) + m_minute);
  if (seconds < 0) {
    minutes--;
  }
  int hours = ((minutes / 60) + m_hour);
  if (minutes < 0) {
    hours--;
  }
  return Time{(*this).real_mod(hours, 24), (*this).real_mod(minutes, 60), (*this).real_mod(seconds, 60)};
}

Time Time::operator-(int x) const {
  return (*this)+(-x);
}

Time Time::operator++(int) {
  Time old = *this;
  *this = (*this)+1;
  return old;
}

Time& Time::operator++() {
  (*this)++;
  return *this;
}

Time Time::operator--(int) {
  Time old = *this;
  *this = (*this)-1;
  return old;
}

Time& Time::operator--() {
  (*this)--;
  return *this;
}

//TODO: Den här funktionen är väldigt svårt att läsa. Försök att fixa till den
// så att den blir lättare att förstå.

// Kanske fixat nu?
bool Time::operator<(Time that) const {
  return
  (hour() < that.hour()) || (
    (hour() == that.hour()) && (
      (minute() < that.minute()) || (
        (minute() == that.minute()) &&
        (second() < that.second())
      )
    )
  );
}

bool Time::operator==(Time that) const {
  return
  (hour() == that.hour()) &&
  (minute() == that.minute()) &&
  (second() == that.second());
}

bool Time::operator>(Time that) const {
  return (that<(*this));
}

ostream& operator<<(ostream & lhs, Time const& rhs) {
  return lhs << rhs.to_string();
}

//TODO: Om användaren matar in ett felaktigt värde ska fail flaggan sättas.
// Fortfarande inte fixat för tex "12:12:#"
istream& operator>>(istream & lhs, Time & rhs) {
  string s;
  lhs >> s;
  try {
    rhs = Time{s};
  } catch (exception e) {
    lhs.setstate(std::ios::failbit);
  }
  return lhs;
}

#endif
