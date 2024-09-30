#include <stdio.h>

//GLOBAL VARIABlES
char g_car_right[]="\a\a\a##\n\a\a\a##\n\a\a\a##"
char g_car_left[]="##\n##\n##"
char g_car_center[]="\a\a##\n\a\a##\n\a\a##"
//END DECLARATION
void change_position(int direction)
{
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  switch(direction)
    {
      case 1: printf("%s",g_car_left);break;
      case 2: printf("%s",g_car_center);break;
      case 3: printf("%s",g_car_right);break;
    };
}




int main()
{
int direction=2;
while(direction!=0)
{
  scanf("%d",&direction);
  change_position(direction);
}  
return 0;
}
