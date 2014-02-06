#include <iostream>
#include "pkb_plib.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "invocation failed\n";
		return 1;
	}
	cout << "\nvardump: " << argv[1] << "\ninvocation: " << argv[2] << "\n";
	return 0;
}
