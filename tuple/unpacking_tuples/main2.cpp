#include <string>
#include <iostream>
#include "tuple_utils.h"

using namespace std;

struct event_1
{
   static string name() { return "event_1"; } 
};

struct event_2
{
   static string name() { return "event_2"; } 
};

struct event_3
{
   static string name() { return "event_3"; } 
};

struct event_4
{
   static string name() { return "event_4"; } 
};

auto list = std::make_tuple(
    event_1{}
   ,event_2{}
   ,event_3{}
   ,event_4{}
); 

void handle(const event_1&)
{
   cout << "1111" << endl;
}

void handle(const event_2&)
{
   cout << "2222" << endl;
}

void handle(const event_3&)
{
   cout << "3333" << endl;
}

void handle(const event_4&)
{
   cout << "4444" << endl;
}


void dispatch(const char* name)
{
   tu::for_each([name](auto e){
      if(e.name()==name)
         handle(e);
   }
   ,list);
}


int main2()
{
   dispatch("event_1");
   dispatch("event_3");
   dispatch("<unknown>");

   std::cout << "Press any key + <enter> to exit" << std::endl;
   std::cin.get();
   return 0;
}
