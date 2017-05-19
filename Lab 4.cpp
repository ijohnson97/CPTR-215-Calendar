/*
        Program: Better Calendar
        Developer: Ian Johnson
        Date Modified: 2017.02.14

        References:
        Lab 1 -> Lab 2 -> This lab
        https://en.wikipedia.org/wiki/Zeller's_congruence
*/

#include <iomanip>
#include <iostream>
#include <vector>

// Allows test cases
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std; // Makes life easier

bool isLeapYear(int year)
// Used to determine if February gets 28 days or 29
{
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    return true;
  } else {
    return false;
  }
}

int dayOfWeek(int monthNum, int year)
/*
                                Converstion Table:
                                Return | Day of Week
                                --------------------
                                        0    | 7 (Sabbath)
                                        1    | 1 (Sunday)
                                        2    | 2 (Monday)
                                        3    | 3 (Tuesday)
                                        4    | 4 (Wednesday)
                                        5    | 5 (Thursday)
                                        6    | 6 (Friday)
*/
{
  if (monthNum == 1 || monthNum == 2) // I have forgotten why this is important,
                                      // but I'm pretty sure it is...
  {
    year -= 1;
    monthNum += 12;
  }
  return (1 + (13 * (monthNum + 1) / 5) + year + (year / 4) - (year / 100) +
          (year / 400)) %
         7; // Does the actual math
}

int daysInMonth(int monthNum, int year) {
  vector<int> monthLength{-9999, 31, 28, 31, 30, 31, 30,
                          31,    31, 30, 31, 30, 31};
  if (isLeapYear(year)) {
    monthLength.at(2) = 29;
  }

  return monthLength.at(monthNum);
}

int main() {
  int result = (new doctest::Context())->run();

  int monthNum, year;
  vector<string> months{
      "Hello",       "    January", "   February", "     March", "     April",
      "      May",   "     June",   "     July",   "    August", "   September",
      "    October", "   November", "   December"};

  // Get user input
  cout << "Please enter a month and year (mm yyyy):";
  cin >> monthNum;
  cin >> year;
  cout << endl;

  cout << months.at(monthNum) << " " << year << endl;
  cout << "Su Mo Tu We Th Fr Sa\n";

  int firstDay = dayOfWeek(
      monthNum, year); // define which day of the week the month starts on
  int days = daysInMonth(monthNum, year); // define length of month

  if (firstDay == 0) {
    firstDay = 7;
  }

  if (firstDay != 1) // If the first day of the month is not Sunday, add the
                     // appriopriate leading spaces
  {
    cout << "  "; // This one is necessary to get things lined up right
    for (int i = 2; i < firstDay;
         ++i) // For however many days into the week the month starts...
    {
      cout << "   "; // Add enough spaces to account for one day.
    }
    cout << ' '; // Another space is required here. Don't ask why.
  }

  for (int day = 1; day <= days; day++) // Output days as normal.
  {
    cout << setw(2) << day;
    if ((day + firstDay) % 7 == 1) {
      cout << endl;
    } else if (day == days) {
      cout << endl;
    } else {
      cout << ' ';
    }
  }

  return result;
}

TEST_CASE("isLeapYear") {
  CHECK(isLeapYear(2000) == bool(true));  // re-leap year
  CHECK(isLeapYear(2001) == bool(false)); // non-leap year
  CHECK(isLeapYear(1900) == bool(false)); // un-leap year
  CHECK(isLeapYear(2004) == bool(true));  // leap year
}

TEST_CASE("dayOfWeek") {
  /*
          Converstion Table:
          Return | Day of Week
          --------------------
            0    | 7 (Sabbath)
            1    | 1 (Sunday)
            2    | 2 (Monday)
            3    | 3 (Tuesday)
            4    | 4 (Wednesday)
            5    | 5 (Thursday)
            6    | 6 (Friday)
  */

  // JANURARY
  CHECK(dayOfWeek(1, 2017) == 1); // Check for Sunday
  CHECK(dayOfWeek(1, 2007) == 2); // Check for Monday
  CHECK(dayOfWeek(1, 2013) == 3); // Check for Tuesday
  CHECK(dayOfWeek(1, 2014) == 4); // Check for Wednesday
  CHECK(dayOfWeek(1, 2015) == 5); // Check for Thursday
  CHECK(dayOfWeek(1, 2016) == 6); // Check for Friday
  CHECK(dayOfWeek(1, 2011) == 0); // Check for Saturday

  // FEBRUARY (non-leap)
  CHECK(dayOfWeek(2, 2015) == 1); // Check for Sunday
  CHECK(dayOfWeek(2, 2010) == 2); // Check for Monday
  CHECK(dayOfWeek(2, 2011) == 3); // Check for Tuesday
  CHECK(dayOfWeek(2, 2017) == 4); // Check for Wednesday
  CHECK(dayOfWeek(2, 2007) == 5); // Check for Thursday
  CHECK(dayOfWeek(2, 2013) == 6); // Check for Friday
  CHECK(dayOfWeek(2, 2014) == 0); // Check for Saturday

  // FEBRUARY (leap year)
  CHECK(dayOfWeek(2, 2004) == 1); // Check for Sunday
  CHECK(dayOfWeek(2, 2016) == 2); // Check for Monday
  CHECK(dayOfWeek(2, 2000) == 3); // Check for Tuesday
  CHECK(dayOfWeek(2, 2012) == 4); // Check for Wednesday
  CHECK(dayOfWeek(2, 1996) == 5); // Check for Thursday
  CHECK(dayOfWeek(2, 2008) == 6); // Check for Friday
  CHECK(dayOfWeek(2, 1992) == 0); // Check for Saturday

  // MARCH
  CHECK(dayOfWeek(3, 2015) == 1); // Check for Sunday
  CHECK(dayOfWeek(3, 2010) == 2); // Check for Monday
  CHECK(dayOfWeek(3, 2016) == 3); // Check for Tuesday
  CHECK(dayOfWeek(3, 2017) == 4); // Check for Wednesday
  CHECK(dayOfWeek(3, 2012) == 5); // Check for Thursday
  CHECK(dayOfWeek(3, 2013) == 6); // Check for Friday
  CHECK(dayOfWeek(3, 2014) == 0); // Check for Saturday

  // APRIL
  CHECK(dayOfWeek(4, 2012) == 1); // Check for Sunday
  CHECK(dayOfWeek(4, 2013) == 2); // Check for Monday
  CHECK(dayOfWeek(4, 2014) == 3); // Check for Tuesday
  CHECK(dayOfWeek(4, 2015) == 4); // Check for Wednesday
  CHECK(dayOfWeek(4, 2010) == 5); // Check for Thursday
  CHECK(dayOfWeek(4, 2016) == 6); // Check for Friday
  CHECK(dayOfWeek(4, 2017) == 0); // Check for Saturday

  // MAY
  CHECK(dayOfWeek(5, 2016) == 1); // Check for Sunday
  CHECK(dayOfWeek(5, 2017) == 2); // Check for Monday
  CHECK(dayOfWeek(5, 2012) == 3); // Check for Tuesday
  CHECK(dayOfWeek(5, 2013) == 4); // Check for Wednesday
  CHECK(dayOfWeek(5, 2014) == 5); // Check for Thursday
  CHECK(dayOfWeek(5, 2015) == 6); // Check for Friday
  CHECK(dayOfWeek(5, 2010) == 0); // Check for Saturday

  // JUNE
  CHECK(dayOfWeek(6, 2014) == 1); // Check for Sunday
  CHECK(dayOfWeek(6, 2015) == 2); // Check for Monday
  CHECK(dayOfWeek(6, 2010) == 3); // Check for Tuesday
  CHECK(dayOfWeek(6, 2016) == 4); // Check for Wednesday
  CHECK(dayOfWeek(6, 2017) == 5); // Check for Thursday
  CHECK(dayOfWeek(6, 2012) == 6); // Check for Friday
  CHECK(dayOfWeek(6, 2013) == 0); // Check for Saturday

  // JULY
  CHECK(dayOfWeek(7, 2012) == 1); // Check for Sunday
  CHECK(dayOfWeek(7, 2013) == 2); // Check for Monday
  CHECK(dayOfWeek(7, 2014) == 3); // Check for Tuesday
  CHECK(dayOfWeek(7, 2015) == 4); // Check for Wednesday
  CHECK(dayOfWeek(7, 2010) == 5); // Check for Thursday
  CHECK(dayOfWeek(7, 2016) == 6); // Check for Friday
  CHECK(dayOfWeek(7, 2017) == 0); // Check for Saturday

  // AUGUST
  CHECK(dayOfWeek(8, 2010) == 1); // Check for Sunday
  CHECK(dayOfWeek(8, 2016) == 2); // Check for Monday
  CHECK(dayOfWeek(8, 2017) == 3); // Check for Tuesday
  CHECK(dayOfWeek(8, 2012) == 4); // Check for Wednesday
  CHECK(dayOfWeek(8, 2013) == 5); // Check for Thursday
  CHECK(dayOfWeek(8, 2014) == 6); // Check for Friday
  CHECK(dayOfWeek(8, 2015) == 0); // Check for Saturday

  // SEPTEMBER
  CHECK(dayOfWeek(9, 2013) == 1); // Check for Sunday
  CHECK(dayOfWeek(9, 2014) == 2); // Check for Monday
  CHECK(dayOfWeek(9, 2015) == 3); // Check for Tuesday
  CHECK(dayOfWeek(9, 2010) == 4); // Check for Wednesday
  CHECK(dayOfWeek(9, 2016) == 5); // Check for Thursday
  CHECK(dayOfWeek(9, 2017) == 6); // Check for Friday
  CHECK(dayOfWeek(9, 2012) == 0); // Check for Saturday

  // OCTOBER
  CHECK(dayOfWeek(10, 2017) == 1); // Check for Sunday
  CHECK(dayOfWeek(10, 2012) == 2); // Check for Monday
  CHECK(dayOfWeek(10, 2013) == 3); // Check for Tuesday
  CHECK(dayOfWeek(10, 2014) == 4); // Check for Wednesday
  CHECK(dayOfWeek(10, 2015) == 5); // Check for Thursday
  CHECK(dayOfWeek(10, 2010) == 6); // Check for Friday
  CHECK(dayOfWeek(10, 2016) == 0); // Check for Saturday

  // NOVEMBER
  CHECK(dayOfWeek(11, 2015) == 1); // Check for Sunday
  CHECK(dayOfWeek(11, 2010) == 2); // Check for Monday
  CHECK(dayOfWeek(11, 2016) == 3); // Check for Tuesday
  CHECK(dayOfWeek(11, 2017) == 4); // Check for Wednesday
  CHECK(dayOfWeek(11, 2012) == 5); // Check for Thursday
  CHECK(dayOfWeek(11, 2013) == 6); // Check for Friday
  CHECK(dayOfWeek(11, 2014) == 0); // Check for Saturday

  // DECEMBER
  CHECK(dayOfWeek(12, 2013) == 1); // Check for Sunday
  CHECK(dayOfWeek(12, 2014) == 2); // Check for Monday
  CHECK(dayOfWeek(12, 2015) == 3); // Check for Tuesday
  CHECK(dayOfWeek(12, 2010) == 4); // Check for Wednesday
  CHECK(dayOfWeek(12, 2016) == 5); // Check for Thursday
  CHECK(dayOfWeek(12, 2017) == 6); // Check for Friday
  CHECK(dayOfWeek(12, 2012) == 0); // Check for Saturday
}

TEST_CASE("daysInMonth") {
  CHECK(daysInMonth(1, 2017) == 31);  // Check Janurary (01)
  CHECK(daysInMonth(2, 2000) == 29);  // Check February (leap year: 02 2000)
  CHECK(daysInMonth(2, 1900) == 28);  // Check February (non-leap year: 02 1900)
  CHECK(daysInMonth(3, 2017) == 31);  // Check March (03)
  CHECK(daysInMonth(4, 2017) == 30);  // Check April (04)
  CHECK(daysInMonth(5, 2017) == 31);  // Check May (05)
  CHECK(daysInMonth(6, 2017) == 30);  // Check June (06)
  CHECK(daysInMonth(7, 2017) == 31);  // Check July (07)
  CHECK(daysInMonth(8, 2017) == 31);  // Check August (08)
  CHECK(daysInMonth(9, 2017) == 30);  // Check September (09)
  CHECK(daysInMonth(10, 2017) == 31); // Check October (10)
  CHECK(daysInMonth(11, 2017) == 30); // Check November (11)
  CHECK(daysInMonth(12, 2017) == 31); // Check December (12)
}
