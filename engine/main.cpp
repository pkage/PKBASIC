#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <cmath>

#ifndef PKBASIC_VER
#define PKBASIC_VER 1.0
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
Parsedcmd parsecmd(string str);
bool runcmd(Parsedcmd pcmd);
int chartovarindex(char &ch);
void iprompt();
void fprompt(string file);
void stripQuotes(string &in);
void inlinate_functions(PFile &pf);
int get_label(PFile &pf, int number);
int get_label(PFile &pf, char ivar);

// Variable registers
string sreg[52];
double ireg[52];
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string NM = "0123456789";

// Flags
bool ERROR_THROWN = false;
string ERROR_TYPE = "NONE";
bool IPROMPT = false; // goto & lbl directives disabled in liveprompt mode
void throw_error(string err) {ERROR_THROWN = true; ERROR_TYPE = err;}

// Auxillary function prototypes
namespace aux {
	void print(string s);
	void system(string s);
	void set_int(char var, int val);
	void set_string(char var, string val);
	void gets(char var);
	void intops(Parsedcmd pcmd);
	void getint(char var);
	bool ifstatement(string stmt);
	void syscall(string cmd);
}

// main
int main(int argc, char* argv[]) {
	srand(time(0));
	if (argc == 1) {
		IPROMPT = true;
		cout << "PKBasic interactive prompt enabled.";
		iprompt();
	}
	if (argc == 2) {
		//cout << "One argument! : " << argv[1] << "\nThis is a file we should run.\n";
		fprompt(string(argv[1]));
	}
	cout << "\n";
	return 0;
}

// Interactive prompt
void iprompt() {
	cout << "\ntype \"exit\" to exit";
	string line;
	while (true) {
		ERROR_THROWN = false;
		cin.clear();
		cout << "\n] ";
		getline(cin, line);
		if (line == "exit") {
			break;
		}
		if (!runcmd(parsecmd(line))) {
			cout << "\nCOMMAND NOT FOUND";
		} else {
			//cout << "\nCOMMAND RUN";
		}
		if (ERROR_THROWN) {
			cout << "ERROR: " << ERROR_TYPE;
		}
	}
	return;
}

// Command parser
Parsedcmd parsecmd(string str) {
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
/*	if (pcmd.cmd == "system") {
		cout << "System commanded!";
		aux::system(pcmd.get_arg(0));
		return true;
 	} */
	if (pcmd.cmd == "get") {
		if (pcmd.get_arg(0)[0] == '#') {
			aux::getint(pcmd.get_arg(0)[1]);
		} else if (pcmd.get_arg(0)[0] == '$') {
			aux::gets(pcmd.get_arg(0)[1]);
		} else {
			throw_error("INVALID GET CALL: NO RECEPTACLE");
		}
		return true;
	}
	if (pcmd.cmd[0] == '$') {
		if (pcmd.arg_count() == 0) {
			ERROR_THROWN = true;
			ERROR_TYPE = "UNUSED_VALUE";
			return true;
		}
		Parsedcmd tmp = parsecmd(pcmd.get_arg(0));
		if (tmp.cmd != "=") {
			throw_error("INVALID OPERAND ON STRING");
		} else {
			string temp = tmp.get_arg(0);
			if (temp[0] != '\"') {
			//	cout << temp[0];
				throw_error("INVALID TYPE");
				return true;
			}
			stripQuotes(temp);
			aux::set_string(pcmd.cmd[1], temp);
			return true;
		}
		return true;
	}
	if (pcmd.cmd[0] == '#') {
		aux::intops(pcmd);
		return true;
	}
	if (pcmd.cmd == "sys") {
		std::system(pcmd.get_arg(0).c_str());
	}
	return false;
}

void stripQuotes(string &in) {
	if (in.at(0) == '\"') {in.erase(0,1);}
	if (in.at(in.length() - 1) == '\"') {in.erase(in.length() - 1, 1);}
	return;
}

int chartovarindex(char &ch) {
	return letters.find(ch);
}

// BEGIN AUXILLARY DEFINITIONS
void aux::print(string s) {
	if (s[0] == '\"') {
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
	} else if (s[0] == '$') {
		int index = chartovarindex(s[1]);
		if (index == -1) {
			throw_error("VARIABLE NOT FOUND");
		} else {
			cout << sreg[index];
		}
	} else if (s[0] == '#') {
		int index = chartovarindex(s[1]); if (index == -1) {throw_error("VARIABLE NOT FOUND"); return;}
		stringstream ss; ss.clear(); ss << ireg[index];
		cout << ss.str();
	}
}

void aux::system(string s) {
	stripQuotes(s);
	cout << "\nExecuting: [" << s << "]\n";
	cout.clear();
	system("clear");
	cout << "\nFinished execute.";
}

void aux::set_int(char var, int val) {
	int index = chartovarindex(var);
	if (index != -1) {
		ireg[index] = val;
	} else {
		ERROR_THROWN = true;
		ERROR_TYPE = "VARIABLE NOT FOUND";
	}
}

void aux::set_string(char var, string str) {
	int index = chartovarindex(var);
        if (index != -1) {
                sreg[index] = str;
        } else {
                ERROR_THROWN = true;
                ERROR_TYPE = "STRING NOT FOUND";
        }
}

void aux::gets(char var) {
	int index = chartovarindex(var);
	if (index != -1) {
		cin >> sreg[index];
	} else {
		throw_error("VARIABLE NOT FOUND");
	}
}

void aux::intops(Parsedcmd pcmd) {
	int index = chartovarindex(pcmd.cmd[1]);
	if (index == -1) {
		throw_error("VARIABLE NOT FOUND");
		return;
	}
	Parsedcmd dref = parsecmd(pcmd.get_arg(0));
	if (NM.find(dref.get_arg(0)[0]) != -1) {
		if (dref.cmd == "=") {
			ireg[index] = atof(dref.get_arg(0).c_str());
		}
		if (dref.cmd == "+=") {
			ireg[index] = ireg[index] + atof(dref.get_arg(0).c_str());
		}
		if (dref.cmd == "-=") {
			ireg[index] = ireg[index] - atof(dref.get_arg(0).c_str());
		}
		if (dref.cmd == "*=") {
			ireg[index] = ireg[index] * atof(dref.get_arg(0).c_str());
		}
		if (dref.cmd == "floor") {
			ireg[index] = floor(ireg[index]);
		}
		if (dref.cmd == "ceil") {
			ireg[index] = ceil(ireg[index]);
		}
		if (dref.cmd == "^=") {
			ireg[index] = pow(ireg[index], atof(dref.get_arg(0).c_str()));
		}
		if (dref.cmd == "%=") {
			ireg[index] = (int)ireg[index]%(int)floor(atoi(dref.get_arg(0).c_str()));
		}
		if (dref.cmd == "~~") {
			ireg[index] = rand()%atoi(dref.get_arg(0).c_str());;
		}
		if (dref.cmd == "/=") {
                        ireg[index] = ireg[index]/atof(dref.get_arg(0).c_str());
                }
	} else if (dref.get_arg(0)[0] == '#') {
		int i2 = chartovarindex(dref.get_arg(0)[1]);
		if (i2 == -1) {
			throw_error("VARIABLE NOT FOUND");
			return;
		}
		if (dref.cmd == "=") {
                        ireg[index] = ireg[i2];
                }
                if (dref.cmd == "+=") {
                        ireg[index] = ireg[index] + ireg[i2];
                }
                if (dref.cmd == "-=") {
                        ireg[index] = ireg[index] - ireg[i2];
                }
                if (dref.cmd == "*=") {
                        ireg[index] = ireg[index] * ireg[i2];
                }
		if (dref.cmd == "/=") {
			ireg[index] = ireg[index]/ireg[i2];
		}
		if (dref.cmd == "^=") {
                        ireg[index] = pow(ireg[index], ireg[i2]);
                }
                if (dref.cmd == "%=") {
                        ireg[index] = (int)ireg[index]%(int)floor(ireg[i2]);
                }
		if (dref.cmd == "~~") {
			ireg[index] = rand()%(int)floor(ireg[i2]);
		}
	} else {
		throw_error("INVALID OPERAND ON INTEGER");
	}
}

void aux::getint(char var) {
	int index = chartovarindex(var);
	if (index == -1) {
		throw_error("VARIABLE NOT FOUND");
		return;
	}
	string tmp;
	cin >> tmp;
	ireg[index] = atof(tmp.c_str());
	return;
}

void fprompt(string file) {
	Parsedcmd pcmd;
	int tmp; bool temp;
//	cout << "GETTING PFile FROM " << file << "\n";
	PFile pf;
	if (!pf.get_from_file(file)) {
		cout << "ERROR: UNABLE TO OPEN FILE\n";
		return;
	}
//	cout << "STARTING MAIN LOOP";
	for (int c = 0; c < pf.lines.size(); c++) {
		pcmd = parsecmd(pf.lines.at(c));
		if (pcmd.cmd == "goto") {
			if (pcmd.get_arg(0)[0] == '#') {
				tmp = get_label(pf, pcmd.get_arg(0)[1]);
				if (tmp == -2) {
					throw_error("VARIABLE NOT FOUND");
				}
			} else {
				tmp = get_label(pf, atoi(pcmd.get_arg(0).c_str()));
			}
			if (tmp == -1) {
				throw_error("LABEL NOT FOUND");
			}
			if (tmp >= 0) {
				c = tmp;
			}
		} else if (pcmd.cmd == "label") {
			// do nothing
		} else if (pcmd.cmd == "if") {
			temp = aux::ifstatement(pcmd.get_arg(0));
			if (!ERROR_THROWN) {
				if (!temp) {
					c++;
				}
			}
		} else if (pcmd.cmd[0] == '/' && pcmd.cmd[1] == '/') {
			// don't do shit
		} else {
			runcmd(pcmd);
		}
		if (ERROR_THROWN) {
			stringstream ss; ss.clear(); ss << c;
			cout << "\nERROR: " << ERROR_TYPE << "\nLINE: " << ss.str();
		}
	}

}

int get_label(PFile &pf, int label) {
	Parsedcmd pc;
	for (int c = 0; c < pf.lines.size(); c++) {
		pc = parsecmd(pf.lines.at(c));
		if (pc.cmd == "label") {
			if (label == atoi(pc.get_arg(0).c_str())) {
				return c;
			}
		}
	}
	return -1;
}


int get_label(PFile &pf, char ivar) {
	int index = chartovarindex(ivar);
	if (index == -1) {
		return -2;
	}
	Parsedcmd pc;
        for (int c = 0; c < pf.lines.size(); c++) {
                pc = parsecmd(pf.lines.at(c));
                if (pc.cmd == "label") {
                        if (ireg[index] == atof(pc.get_arg(0).c_str())) {
                                return c;
                        }
                }
        }
        return -1;
}

bool aux::ifstatement(string stmt) {
	Parsedcmd t1, t2;
	t1 = parsecmd(stmt);
	t2 = parsecmd(t1.get_arg(0));
	string bit1, bit2, operand;
	bit1 = t1.cmd;
	bit2 = t2.get_arg(0);
	operand = t2.cmd;
	int i1, i2;
	if (bit1[0] == '$' && bit2[0] == '$') {
		i1 = chartovarindex(bit1[1]);
		i2 = chartovarindex(bit2[1]);
		if (i1 == -1 || i2 == -1) {
			throw_error("VARIABLE NOT FOUND");
			return false;
		}
		if (operand == "==") {
			if (sreg[i1] == sreg[12]) {
				return true;
			} else {
				return false;
			}
		} else {
			throw_error("ILLEGAL OPERATION ON STRING");
		}
	} else
	if (bit1[0] == '#' && bit2[0] == '#') {
		i1 = chartovarindex(bit1[1]);
		i2 = chartovarindex(bit2[1]);
		if (i1 == -1 || i2 == -1) {
			throw_error("VARIABLE NOT FOUND");
			return false;
		} else
		if (operand == "==") {
			return (ireg[i1] == ireg[i2]);
		} else
		if (operand == ">") {
			return (ireg[i1] > ireg[i2]);
		} else
		if (operand == "<") {
			return (ireg[i1] < ireg[i2]);
		} else
		if (operand == ">=") {
			return (ireg[i1] >= ireg[i2]);
		} else
		if (operand == "<=") {
			return (ireg[i1] <= ireg[i2]);
		} else
		if (operand == "!=") {
			return (ireg[i1] != ireg[i2]);
		} else {
			return false;
			throw_error("ILLEGAL OPERAND ON NUMBER");
		}
	}
	if (bit1[0] != bit2[0]) {
		throw_error("TYPE MISMATCH");
	} else {
		throw_error("INVALID TYPE");
	}
	return false;
}

void aux::syscall(string cmd) {
	system(cmd.c_str());
}
