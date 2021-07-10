#include <iostream>
using namespace std;
void changeMe(int);
int main()
{
int number=12;
cout<<"number is"<<number<<endl;
changeMe(number);
cout<<"back in main";
cout<<"number is"<<number<<endl;
return 0;
}
void changeMe(int myVal)
{
myVal=0;
cout<<"The value is"<<myVal;
}
