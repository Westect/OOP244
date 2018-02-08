// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include<iostream>
#include "Date.h"

namespace sict {

  // number of days in month mon_ and year year_
  //
  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

  void Date::errCode(int errorCode)
  {
	  error_state = errorCode;
  }

  void Date::setempty()
  {
	  year = 0000;
	  month = 00;
	  day = 00;
	  compval = 0;
	  error_state = NO_ERROR;
  }

  Date::Date()
  {
	  setempty();
  }

  Date::Date(int cYear, int cMonth, int cDay)
  {
	  if (cYear > min_year && cYear < max_year)
	  {
		  year = cYear;
	  }
	  else
	  {
		  setempty();
		  error_state = YEAR_ERROR;
		  return;
	  }
	  if (cMonth > 0 && cMonth < 13)
	  {
		  month = cMonth;
	  }
	  else
	  {
		  setempty();
		  error_state = MON_ERROR;
		  return;
	  }
	  if (cDay <= mdays(month, year))
	  {
		  day = cDay;
		  compval = year * 372 + month * 13 + day;
		  error_state = NO_ERROR;
	  }
	  else
	  {
		  setempty();
		  error_state = DAY_ERROR;
		  return;
	  }
  }

  bool Date::operator==(const Date & rhs) const
  {
	  if (this->compval == rhs.compval) 
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  bool Date::operator!=(const Date & rhs) const
  {
	  if (this->compval != rhs.compval)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  bool Date::operator<(const Date & rhs) const
  {
	  if (this->compval < rhs.compval)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  bool Date::operator>(const Date & rhs) const
  {
	  if (this->compval > rhs.compval)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  bool Date::operator<=(const Date & rhs) const
  {
	  if (this->compval <= rhs.compval)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  bool Date::operator>=(const Date & rhs) const
  {
	  if (this->compval >= rhs.compval)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  }

  int Date::errCode() const 
  {
	  return this->error_state;
  }

  bool Date::bad() const
  {
	  if (this->error_state != NO_ERROR)
	  {
		  return true;
	  }
	  return false;
  }


  std::istream & Date::read(std::istream& istr)
  {
	  char slash = '/';
	  istr >> year >> slash >> month >> slash >> day;
	  if (istr.fail())
	  {
		  error_state = CIN_FAILED;
		  return istr;
	  }
	  if (year < min_year || year > max_year)
	  {
		  setempty();
		  error_state = YEAR_ERROR;
	  }
	  if (month < 0 || month > 12)
	  {
		  setempty();
		  error_state = MON_ERROR;
	  }
	  if (day > mdays(month, year))
	  {
		  setempty();
		  error_state = DAY_ERROR;
	  }
	  return istr;
  }

  std::ostream & Date::write(std::ostream& ostr) const
  {
	  char slash = '/';
	  ostr << year << slash;
	  if (month < 10)
	  {
		  ostr << 0;
	  }
	  ostr << month << slash;
	  if (day < 10)
	  {
		  ostr << 0;
	  }
	  ostr << day;
	  return ostr;
  }

  Date & Date::operator=(const Date& rhs)
  {
	if (&rhs == this) return *this;
	year = rhs.year;
	month = rhs.month;
	day = rhs.day;
	compval = rhs.compval;
	error_state = rhs.error_state;
	return *this;
  }

  std::ostream& operator<<(std::ostream& ostr, const Date& s)
  {
	  s.write(ostr);
	  return ostr;
  }

  std::istream& operator>>(std::istream& istr, Date& s)
  {
	  s.read(istr);
	  return istr;
  }
}
