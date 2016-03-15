#include "stdafx.h"
#include "MyUtil.h"

string SaveIntToStr(int x)
{
   if(x > 9999)
      return "ERROR";
   string info;
   if(x < 1000)
      info.append("0");
   if(x < 100)
      info.append("0");
   if(x < 10)
      info.append("0");
   info.append(to_string(x));
   return info;
}
