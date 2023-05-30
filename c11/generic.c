// https://www.ibm.com/support/knowledgecenter/en/SSGH2K_13.1.2/com.ibm.xlc131.aix.doc/language_ref/genericselection.html
#include <stdio.h>
#include <stdlib.h>

#define myfunction(X) _Generic((X), long double:myfunction_longdouble, default:myfunction_double, float:myfunction_float)(X)
void myfunction_longdouble(long double x){printf("call %s(%Lf)", __func__, x);}
void myfunction_double(double x){printf("call %s %f", __func__, x);}
void myfunction_float(float x){printf("call %s %f", __func__, x);}

int main(void)
{
  long double ld=0;
  double d=0;
  float f=0;
  myfunction(ld);
  myfunction(d);
  myfunction(f);

  return EXIT_SUCCESS;
}
