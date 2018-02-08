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
#ifndef SICT_DATE_H
#define SICT_DATE_H

namespace sict {
	const int min_year = 2000;
	const int max_year = 2030;
  class Date {
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
	int year;
	int month;
	int day;
	int compval;
	int error_state;
    int mdays(int, int)const;
	void errCode(int);
	void setempty();	//sets the object to an empty state
  public:
	  Date();
	  Date(int, int, int);
	  bool operator==(const Date& rhs) const;
	  bool operator!=(const Date& rhs) const;
	  bool operator<(const Date& rhs) const;
	  bool operator>(const Date& rhs) const;
	  bool operator<=(const Date& rhs) const;
	  bool operator>=(const Date& rhs) const;
	  int errCode() const;
	  bool bad() const;
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr) const;
	  Date & operator=(const Date& rhs); //copy assign operator written to be used in ms5
  };
	std::ostream& operator<<(std::ostream& ostr, const Date& s);
	std::istream& operator>>(std::istream& istr, Date& s);
}
#endif