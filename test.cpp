#include <iostream>
using namespace std;

int main(void)
{
    int num;
    std::cout<<"enter a number: ";
    std::cin>>num;
    if(num%2==0)
    {
        std::cout<<"the number is divisible by 2\n";
        if(num>10)
        {
            std::cout<<"it is greater than 10";
        }
    }
    else
    {
        std::cout<<"it is not divisible by 2\n";
    }
    return 0;
}