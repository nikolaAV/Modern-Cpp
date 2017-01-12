#include <string>
#include <iostream>
#include "greeting.h"

using namespace std;

int main()
{
	cout << compiler::greeting() << endl;
    cout << "Press any key + <enter> to exit" << endl;
	cin.get();
}
