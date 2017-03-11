#include "stdafx.h"
#include "MyUtil.h"

string SaveIntToStr(int x)
{
   if(x > 9999)
      return "9999";
   if(x < -999)
      return "-999";

   string info;
   if(x >= 0)
   {
      if(x < 1000)
         info.append("0");
      if(x < 100)
         info.append("0");
      if(x < 10)
         info.append("0");
      info.append(to_string(x));
   }
   else // x < 0
   {
      info.append("-");
      if(x > -100)
         info.append("0");
      if(x > -10)
         info.append("0");
      info.append(to_string(abs(x)));
   }
   return info;
}

int InRange(int value, int min, int max)
{
   if(min > max)
      return value;
   if(value < min)
      return min;
   if(value > max)
      return max;
   return value;
}
