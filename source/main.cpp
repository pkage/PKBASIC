#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

#ifndef PBASIC_VER
#define PBASIC_VER 1.0
#endif

using namespace std;

class Parsedcmd {
public:
	string cmd;
	vector<string> args;
	void add_arg(string arg) {
		args.push_back(arg);
	}
	int arg_count() {return args.size();}
	string get_arg(int n) {
		if (n > args.size() || n < 0) {
			return "";
		}
		return args.at(n);
	}
};

class PFile {
public:
	vector<string> lines;
	bool get_from_file(string fname) {
		ifstream file; file.open(fname.c_str());
		if (!file) {
			return false; // file not found
		}
		string tmp;
		while (!file.eof()) {
			getline(file, tmp);
			lines.push_back(tmp);
		}
		return true;
	}
	string line(int n) {return lines.at(n - 1);}
};

// Core function prototypes
Parsedcmd parsecmd(string &str);
bool runcmd(Parsedcmd pcmd);
int chartovarindex(char &ch);
void iprompt();
void fprompt() {}
void stripQuotes(string &in);

// Auxillary function prototypes
namespace aux {
	void print(string s);
	void system(string s);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "PBasic interactive prompt enabled.";
		iprompt();
	}
	if (argc == 2) {
		cout << "One argument! : " << argv[1] << "\nThis is a file we should run.\n";
	}
	cout << "\n";
	return 0;
}

// Interactive prompt
void iprompt() {
	cout << "\ntype \"exit\" to exit";
	string line;
	while (true) {
		cin.clear();
		cout << "\n] ";
		getline(cin, line);
		if (line == "exit") {
			break;
		}
		if (!runcmd(parsecmd(line))) {
			cout << "\nCOMMAND NOT FOUND";
		} else {
			cout << "\nCOMMAND RUN";
		}
	}
	return;
}

// Command parser
Parsedcmd parsecmd(string &str) {
	int spos = str.find(" ");
	string cmd, arg;
	if (spos == -1) {
		cmd = str;
		arg = "";
	} else {
		cmd = str.substr(0, spos);
		arg = str.substr(spos + 1);
	}
	//cout << "Parsed command as: [" << cmd << "]";
	//cout << "\nParsed argument as [" << arg << "]";
	Parsedcmd pcmd;
	pcmd.cmd = cmd;
	pcmd.add_arg(arg);
	return pcmd;
}

// Command director
bool runcmd(Parsedcmd pcmd) {
	if (pcmd.cmd == "print") {
		aux::print(pcmd.get_arg(0));
		return true;
	}
	if (pcmd.cmd == "system") {
		cout << "System commanded!";
		aux::system(pcmd.get_arg(0));
		return true;
	}
	return false;
}

void stripQuotes(string &in) {
	if (in.at(0) == '\"') {in.erase(0,1);}
	if (in.at(in.length() - 1) == '\"') {in.erase(in.length() - 1, 1);}
	return;
}

// BEGIN AUXILLARY DEFINITIONS
void aux::print(string s) {
	stripQuotes(s);
	string final = "";
	for (int c = 0; c < s.length(); c++) {
		// HOLY SHIT ESCAPE CHARACTERS
		if (s.at(c) == '\\' && (c + 1 != s.length())) {
			if (s.at(c+1) == 'n') {
				final += '\n';
				c++;
				continue;
			}
		}
		final += s.at(c);
	}
	cout << final;
}

void aux::system(string s) {
	stripQuotes(s);
	cout << "\nExecuting: [" << s << "]\n";
	cout.clear();
	system("clear");
	cout << "\nFinished execute";
}
