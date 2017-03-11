#ifndef MYUTIL_H
#define MYUTIL_H

namespace MR
{
   const float WIN_HEIGHT = 600.0f;
   const float WIN_WIDTH = 800.0f;
   const int MAX_BOTS_IN_PARTY = 6;
}

//-----------------------------------------------------------------------------
// This function takes an integer and returns a string representation of it
// that is exactly four characters long. If it is bigger than 9999, 9999 is
// returned. If it is smaller than -999, then -999 is returned.
//-----------------------------------------------------------------------------
std::string SaveIntToStr(int x);

//-----------------------------------------------------------------------------
// This function takes a value, a minimum, and a maximum, and checks to see if
// the value is between the latter two. If the value is equal to or between the
// the two, the value is returned. Otherwise, if value is less than min, min
// is returned; if value is greater than max, then max is returned. 
//
// If min is greater than max, value is returned.
//-----------------------------------------------------------------------------
int InRange(int value, int min, int max);

#endif