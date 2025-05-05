#include<iostream>
#include<windows.h>
#include<thread>
using namespace std;
void timer(){
    Sleep(1000);
}
int main()
{
    thread test(timer);
    test.join();
    cout<<"Finish";
    return 0;
}
