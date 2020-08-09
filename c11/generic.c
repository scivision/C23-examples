// https://www.ibm.com/support/knowledgecenter/en/SSGH2K_13.1.2/com.ibm.xlc131.aix.doc/language_ref/genericselection.html
#include <stdio.h>

#define myfunction(X) _Generic((X), long double:myfunction_longdouble, default:myfunction_double, float:myfunction_float)(X)
void myfunction_longdouble(long double x){printf("call %s",__func__);}
void myfunction_double(double x){printf("call %s",__func__);}
void myfunction_float(float x){printf("call %s",__func__);}

int main()
{
  long double ld;
  double d;
  float f;
  myfunction(ld);
  myfunction(d);
  myfunction(f);
}
