//============================================================================
// Name        : discord-challenge-26.cpp
// Author      : Perry Harrington
// Version     : 1
// Copyright   : Your copyright notice
// Description : Challenge #26
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
	string a,b;

	cout << "Shall we play a game? (Y/N) ";
	cin >> a;
	if (a != "Y") return 0;
	cout << endl;
	cout << "Enter 2 numbers separated by a space: ";
	cin >> a >> b;

	if (a=="" || b=="") {
		cout << "You must enter 2 numbers!"<<endl;
		return 0;
	}

	auto atos = [] (char t) {
		if (t == '1') return string(".");
		if (t == '2') return string("..");
		if (t == '3') return string("...");
		if (t == '4') return string("....");
		if (t == '5') return string(".....");
		if (t == '6') return string("......");
		if (t == '7') return string(".......");
		if (t == '8') return string("........");
		if (t == '9') return string(".........");
		return string("");
	};

	auto stoa = [] (string& t) {
		if (t == ".") return string("1");
		if (t == "..") return string("2");
		if (t == "...") return string("3");
		if (t == "....") return string("4");
		if (t == ".....") return string("5");
		if (t == "......") return string("6");
		if (t == ".......") return string("7");
		if (t == "........") return string("8");
		if (t == ".........") return string("9");
		return string("0");
	};

	auto inrange = [] (string& t) {
		if (
		t == "" ||
		t == "." ||
		t == ".." ||
		t == "..." ||
		t == "...." ||
		t == "....." ||
		t == "......" ||
		t == "......." ||
		t == "........" ||
		t == "........."
				) return true;
		return false;
	};

	auto ai = a.rbegin();
	auto bi = b.rbegin();
	string answer,mod,fa,fb,line;

	while(true) {
		string j,k;

		j = ai == a.rend() ? string("") : atos(*ai);
		k = bi == b.rend() ? string("") : atos(*bi);
		j.append(k);

		if (!mod.empty()) {
			j.append(mod);
			mod.clear();
		}

		if (!inrange(j)) {
			while(!inrange(j)) {
				j.pop_back();
				if (!inrange(j)) mod.push_back('.');
			}

			answer = stoa(mod) + answer;
			mod=".";
		} else {
			answer = stoa(j) + answer;
		}

		fa = (ai == a.rend() ? ' ' : (*ai)) + fa;
		fb = (bi == b.rend() ? ' ' : (*bi)) + fb;
		line.push_back('=');

		if (ai != a.rend()) ai = std::next(ai);
		if (bi != b.rend()) bi = std::next(bi);
		if (ai == a.rend() && bi == b.rend()) break;
	}

	if (!mod.empty()) {
		answer = stoa(mod) + answer;
		line.push_back('=');
		fa = ' '+fa;
		fb = ' '+fb;
	}

	cout << endl;
	cout << fa << endl;
	cout << fb << " +" << endl;
	cout << line << endl;
	cout << answer << endl;

	return 0;
}
