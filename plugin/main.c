#include <stdio.h>

int main()
{
  struct test_t {
      unsigned int a : 1;
      unsigned int b : 1;
      unsigned int c : 1;
      unsigned int d : 1;
      unsigned int e : 1;
      unsigned int f : 1;
      unsigned int g : 1;
      unsigned int h : 1;
      unsigned int i : 1;
      unsigned int j : 1;
};

  struct test_t test __attribute__((bit_band(5))); //Apply bit banding to this struct
  int i __attribute__((bit_band())); //Apply to an int to test plugin's type detection
  int j;
  volatile int k;

  test.i = 0;
  test.j = 1;

  printf("i = %d\tj = %d\n", test.i, test.j);

  return 0;
}
