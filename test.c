#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int iter(int ori, int obj)
{
  printf("enter\r\n");
  if(ori <= 0)
  {
    printf("ori == 0\r\n");
    return 0;
  }
  if(ori == obj)
  {
    printf("match obj\r\n");
    return 1;
  }
  iter(ori - 1, obj);

  printf("exit\r\n");
  return 2;
}

int main(int argc, char *argv[])
{
  int i;
  int ori, obj;
  if(argc >= 3)
  {
    ori = strtoul(argv[1], NULL, 10);
    obj = strtoul(argv[2], NULL, 10);
  }
  i = iter(ori, obj);
  printf("final i:%d\r\n", i);
}

