/* testlib.cpp
 * pkbasic test library
 * increments var by 4
 * useless, but it's a test
 */


#include <iostream>
#include "pkb_plib.h"

using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "invocation failed\n";
		return 1;
	}
	cout << "\nvardump: " << argv[1] << "\ninvocation: " << argv[2] << "\noutput: " << argv[3] << '\n';
	string vd = argv[1], invoc = argv[2];
	if (!plib::import_varlist(vd)) {
		cout << "\nfailed to read variables";
		return 1;
	}
	plib::Parsedcmd pcmd = plib::parsecmd(invoc);
	for (int c = 0; c < letters.size(); c++) {
		cout << "register [" << letters.at(c) << "] | $(" << plib::sreg[c] << ") | #(" << plib::ireg[c] << ")\n";
	}
	ofstream ofile;
	ofile.open(argv[3]);
	ofile << "skip";
	ofile.close();
	return 0;
}
