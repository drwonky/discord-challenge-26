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

	auto atos = [] (char t) {	// convert ASCII into strings of the same length as each ASCII numeral
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

	auto stoa = [] (string& t) {	// convert a string of a given length into an ASCII numeral equivalent of the length of the string
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

	auto inrange = [] (string& t) {	// check to see if a string is 9 digits or less, implements carry checking
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

	/*
	 * Theory of operation:
	 *
	 * There are 4 pipelined functions happening in this loop:
	 *
	 * a) Calculating the addition of the ASCII strings by conversion of ASCII to strings of length 0-9 and handling overflow
	 * b) Formatting the answer via prepending digits
	 * c) Formatting the right justified input numbers so they are the same length as the answer
	 * d) Creating a line/bar the same length as the answer, for full justification
	 *
	 * Each string of ASCII numerals is iterated from right to left using reverse iterators.
	 * Each column is read, the ASCII numeral converted into a string representing that quantity.
	 *
	 * 1 represents 1 period, 5 represents 5 periods, etc
	 *
	 * The number of periods per column is summed together by appending strings.
	 *
	 * Then the string is checked for overflow by comparing it to a list of strings of a known length less than 10
	 *
	 * If the string overflows, first we take 1 digit from the string and check if it still overflows, this
	 * allows us to handle the 10ths transition without underflowing to 9 when it should be zero.
	 *
	 * After handling the 10ths transition, if the modulus doesn't come out to zero, then we continue subtracting digits from the column,
	 * the number of digits subtracted is the modulus, which becomes the new column value.
	 *
	 * example:
	 *
	 * 12 sub 1 is 11
	 *
	 * Is 11 within 0 to 9?
	 *
	 * No, sub 1 and append 1 to modulus
	 *
	 * Is 10 within 0 to 9?
	 *
	 * No, sub 1 and append 1 to modulus
	 *
	 * Is 9 within 0 to 9?
	 *
	 * Yes, prepend the ASCII numeral equivalent of 2 to the answer.
	 *
	 * The use of reverse iterators allows us to process the input strings from right to left.  When an iterator hits the end, the
	 * value of the iterator is empty, so therefore there is no real value associated with it and the atos lambda returns an empty string.
	 *
	 * This allows us to process strings of arbitrary length, while carrying any overflows to the furthest most left column of the answer.
	 *
	 * Take for instance this special condition:
	 *
	 * 999 + 9999 = 10998
	 *
	 * 999 is shorter than 9999, which is also shorter than 10998, so therefore we must propagate the carry beyond the length of the original strings.
	 *
	 * This is accomplished by the 3 tests at the end of the loop, which cause the loop to break:
	 *
	 * a) If we've processed all digits of string a
	 * b) If we've processed all digits of string b
	 * c) If there is no modulus to carry to the final digit of the answer
	 *
	 * The final test handles the scenario where the answer is longer than the longest input term.
	 *
	 */

	auto ai = a.rbegin();
	auto bi = b.rbegin();
	string answer,mod,fa,fb,line;

	while(true) {
		string j,k;

		j = atos(*ai);	// convert ASCII to string of length represented by numeral
		k = atos(*bi);
		j.append(k);	// append strings, summing the ASCII numerals together

		if (!mod.empty()) {	// handle carry from previous loop iteration
			j.append(mod);	// adds "10" to value by adding 1 digit to string
			mod.clear();	// reset carry flag
		}

		if (!inrange(j)) {	// if string length is greater than 9 digits, handle carrying
			j.pop_back();	// this handles the 10->0 case so it doesn't underflow to 9

			while(!inrange(j)) {	// if this wasn't a 10->0 carry, process the rest of digits to produce a modulus
				j.pop_back();
				mod.push_back('.');
			}

			answer = stoa(mod) + answer;	// this processes the carry from the previous loop, either prepending an empty string, or a number, handles 12->2
			mod=".";						// this is the 10ths carry for the next loop iteration
		} else {
			answer = stoa(j) + answer;		// no carry, so simply prepend the sum 2+3->5
		}

		fa = (ai == a.rend() ? ' ' : (*ai)) + fa;	// this formats the input strings to right justify the output result
		fb = (bi == b.rend() ? ' ' : (*bi)) + fb;
		line.push_back('=');						// the bar/line of the output

		if (ai != a.rend()) ai = std::next(ai);		// iterator mechanics
		if (bi != b.rend()) bi = std::next(bi);
		if (ai == a.rend() && bi == b.rend() && mod.empty()) break;	// this processes input numbers of different length and carrying of final result 999+9999->10998
	}

	cout << endl;	// formatting to make Ideone display properly
	cout << fa << endl;
	cout << fb << " +" << endl;
	cout << line << endl;
	cout << answer << endl;

	return 0;
}
