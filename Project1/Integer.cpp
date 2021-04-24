#include "Integer.h"
using std::reverse;

Integer::Integer() {
	flag = 1;
	Int.push_back(0);
}

Integer::Integer(string s) {
	flag = 1;
	if (s[0] == '-') {
		flag = -1;
		s = s.substr(1, s.size() - 1);
	}
	if (s[0] == '+') {
		flag = 1;
		s = s.substr(1, s.size() - 1);
	}
	for (auto i = s.rbegin(); i != s.rend(); i++) {
		Int.push_back(*i - '0');
	}
}

Integer::Integer(Integer& from) {
	flag = from.flag;
	Int = from.Int;
}

bool Integer::test() {
	bool test_pass = true;
	
	// test constructors
	Integer a("999999999999999999999999999999999999999999999999999999999999999999999999999999999"),
		b("333333333333333333333333333333333333333333333333333333333333333333333333333333333"),c;
	Integer d = a;
	d += d;
	if (d == a) {
		cout << "copy fail" << endl;
		test_pass = false;
	}

	// test operators
	/*if ((a + b) != Integer("1333333333333333333333333333333333333333333333333333333333333333333333333333333332")) {
		cout << "a + b fail" << endl;
		test_pass = false;
	}
	if ((a - b) != Integer("666666666666666666666666666666666666666666666666666666666666666666666666666666666")) {
		cout << "a - b fail" << endl;
		test_pass = false;
	}
	if ((a * b) != Integer("333333333333333333333333333333333333333333333333333333333333333333333333333333332666666666666666666666666666666666666666666666666666666666666666666666666666666667")) {
		cout << "a * b fail" << endl;
		test_pass = false;
	}*/

	return test_pass;
}

Integer Integer::operator+(Integer plusInt) {
	Integer sum;
	
	int plus = 0, index = 0;
	for (index; index < std::min(Int.size(), plusInt.Int.size()); index++) {

		int x = Int[index] + plusInt.Int[index] + plus; // x = each digit sum
		sum.Int.push_back(x % 10);
		plus = x / 10;
	}
	if (Int.size() > plusInt.Int.size()) {
		for (index = plusInt.Int.size(); index < Int.size(); index++) {
			int x = Int[index] + plus;
			sum.Int.push_back(x % 10);
			plus = x / 10;
		}
	}
	else if (Int.size() < plusInt.Int.size()) {
		for (index = Int.size(); index < plusInt.Int.size(); index++) {
			int x = plusInt.Int[index] + plus;
			sum.Int.push_back(x % 10);
			plus = x / 10;
		}
	}
	if (plus) {
		sum.Int.push_back(plus);
	}
	
	return sum;
}

Integer Integer::operator-(Integer diffInt) {
	Integer difference;

	int minus = 0, index = 0;
	if (Int.size() > diffInt.Int.size()) {
		flag = 1; // flag = '+'
		for (index; index < diffInt.Int.size(); index++) {
			int x;
			if (Int[index] - diffInt.Int[index] - minus < 0) {
				x = 10 + Int[index] - diffInt.Int[index] - minus; // x = each digit difference
				minus = 1;
			}
			else {
				x = Int[index] - diffInt.Int[index] - minus;
				minus = 0;
			}
			
			difference.Int.push_back(x);
		}

		for (index = diffInt.Int.size(); index < Int.size(); index++) {
			int x;
			if (Int[index] - minus < 0) {
				x = 10 + Int[index] - minus; 
				minus = 1;
			}
			else {
				x = Int[index] - minus;
				minus = 0;
			}

			difference.Int.push_back(x);
		}
	}
	else if (Int.size() < diffInt.Int.size()) {
		flag = -1; // flag = '-'
		for (index; index < Int.size(); index++) {
			int x;
			if (diffInt.Int[index] - Int[index] - minus < 0) {
				x = 10 + diffInt.Int[index] - Int[index] - minus;
				minus = 1;
			}
			else {
				x = diffInt.Int[index] - Int[index] - minus;
				minus = 0;
			}

			difference.Int.push_back(x);
		}

		for (index = Int.size(); index < diffInt.Int.size(); index++) {
			int x;
			if (diffInt.Int[index] - minus < 0) {
				x = 10 + diffInt.Int[index] - minus;
				minus = 1;
			}
			else {
				x = diffInt.Int[index] - minus;
				minus = 0;
			}

			difference.Int.push_back(x);
		}
	}
	else {
		for (int i = Int.size() - 1; i > 0; i--) {
			if (Int[i] > diffInt.Int[i]) {
				flag = 1;
				for (index; index < diffInt.Int.size(); index++) {
					int x;
					if (Int[index] - diffInt.Int[index] - minus < 0) {
						x = 10 + Int[index] - diffInt.Int[index] - minus; 
						minus = 1;
					}
					else {
						x = Int[index] - diffInt.Int[index] - minus;
						minus = 0;
					}

					difference.Int.push_back(x);
				}
				break;
			}
			else if (Int[i] < diffInt.Int[i]) {
				flag = -1;
				for (index; index < Int.size(); index++) {
					int x;
					if (diffInt.Int[index] - Int[index] - minus < 0) {
						x = 10 + diffInt.Int[index] - Int[index] - minus;
						minus = 1;
					}
					else {
						x = diffInt.Int[index] - Int[index] - minus;
						minus = 0;
					}

					difference.Int.push_back(x);
				}
				break;
			}
		}
	}

	for (int i = difference.Int.size() - 1; i > 0; i--) {

		if (difference.Int[i] == 0) {
			difference.Int.erase(difference.Int.begin() + i);
		}
		else {
			break;
		}
	}

	if ((*this) == diffInt) {
		difference.Int.push_back(0);
	}

	return difference;
}

/*Integer Integer::operator*(Integer multiInt) {
	Integer product;

	return product;
}*/

bool Integer::operator>(Integer compareInt) {
	if (flag == 1 && compareInt.flag == -1) return true;
	if (flag == -1 && compareInt.flag == 1) return false;
	if (Int.size() > compareInt.Int.size()) return true;
	if (Int.size() < compareInt.Int.size()) return false;

	for (int i = Int.size() - 1; i >= 0; i--) {
		if (Int[i] > compareInt.Int[i]) return true;
		if (Int[i] < compareInt.Int[i]) return false;
	}
	return false; // ==
}

bool Integer::operator<(Integer compareInt) {
	if (flag == 1 && compareInt.flag == -1) return false;
	if (flag == -1 && compareInt.flag == 1) return true;
	if (Int.size() > compareInt.Int.size()) return false;
	if (Int.size() < compareInt.Int.size()) return true;

	for (int i = Int.size() - 1; i >= 0; i--) {
		if (Int[i] > compareInt.Int[i]) return false;
		if (Int[i] < compareInt.Int[i]) return true;
	}
	return false; // ==
}

bool Integer::operator>=(Integer compareInt) {
	if (flag == 1 && compareInt.flag == -1) return true;
	if (flag == -1 && compareInt.flag == 1) return false;
	if (Int.size() > compareInt.Int.size()) return true;
	if (Int.size() < compareInt.Int.size()) return false;

	for (int i = Int.size() - 1; i >= 0; i--) {
		if (Int[i] > compareInt.Int[i]) return true;
		if (Int[i] < compareInt.Int[i]) return false;
	}
	return true; // ==
}

bool Integer::operator<=(Integer compareInt) {
	if (flag == 1 && compareInt.flag == -1) return false;
	if (flag == -1 && compareInt.flag == 1) return true;
	if (Int.size() > compareInt.Int.size()) return false;
	if (Int.size() < compareInt.Int.size()) return true;

	for (int i = Int.size() - 1; i >= 0; i--) {
		if (Int[i] > compareInt.Int[i]) return false;
		if (Int[i] < compareInt.Int[i]) return true;
	}
	return true; // ==
}

bool Integer::operator==(Integer compareInt) {
	if (flag != compareInt.flag) return false;
	if (Int.size() != compareInt.Int.size()) return false;

	for (int i = Int.size() - 1; i >= 0; i--) {
		if (Int[i] != compareInt.Int[i]) return false;
	}

	return true; // ==
}

bool Integer::operator!=(Integer compareInt) {
	if (*this == compareInt) return false;
	return true;
}

Integer& Integer::operator=(Integer assignInt) {
	flag = assignInt.flag;
	Int = assignInt.Int;
	return *this;
}

Integer& Integer::operator+=(Integer plusInt) {

	int plus = 0, index = 0;
	for (index; index < std::min(Int.size(), plusInt.Int.size()); index++) {

		int x = Int[index] + plusInt.Int[index] + plus; // x = each digit sum
		Int[index] = x % 10;
		plus = x / 10;
	}
	if (Int.size() > plusInt.Int.size()) {
		for (index = plusInt.Int.size(); index < Int.size(); index++) {
			int x = Int[index] + plus;
			Int[index] = x % 10;
			plus = x / 10;
		}
	}
	else if (Int.size() < plusInt.Int.size()) {
		for (index = Int.size(); index < plusInt.Int.size(); index++) {
			int x = plusInt.Int[index] + plus;
			Int[index] = x % 10;
			plus = x / 10;
		}
	}
	if (plus) {
		Int.push_back(plus);
	}
	
	return *this;
}

Integer& Integer::operator-=(Integer diffInt) {
	int minus = 0, index = 0;
	if (Int.size() > diffInt.Int.size()) {
		flag = 1; // flag = '+'
		for (index; index < diffInt.Int.size(); index++) {

			if (Int[index] - diffInt.Int[index] - minus < 0) {
				Int[index] = 10 + Int[index] - diffInt.Int[index] - minus; // x = each digit difference
				minus = 1;
			}
			else {
				Int[index] = Int[index] - diffInt.Int[index] - minus;
				minus = 0;
			}

		}

		for (index = diffInt.Int.size(); index < Int.size(); index++) {

			if (Int[index] - minus < 0) {
				Int[index] = 10 + Int[index] - minus;
				minus = 1;
			}
			else {
				Int[index] = Int[index] - minus;
				minus = 0;
			}

		}
	}
	else if (Int.size() < diffInt.Int.size()) {
		flag = -1; // flag = '-'
		for (index; index < Int.size(); index++) {

			if (diffInt.Int[index] - Int[index] - minus < 0) {
				Int[index] = 10 + diffInt.Int[index] - Int[index] - minus;
				minus = 1;
			}
			else {
				Int[index] = diffInt.Int[index] - Int[index] - minus;
				minus = 0;
			}

		}

		for (index = Int.size(); index < diffInt.Int.size(); index++) {

			if (diffInt.Int[index] - minus < 0) {
				Int[index] = 10 + diffInt.Int[index] - minus;
				minus = 1;
			}
			else {
				Int[index] = diffInt.Int[index] - minus;
				minus = 0;
			}

		}
	}
	else {
		for (int i = Int.size() - 1; i > 0; i--) {
			if (Int[i] > diffInt.Int[i]) {
				flag = 1;
				for (index; index < diffInt.Int.size(); index++) {

					if (Int[index] - diffInt.Int[index] - minus < 0) {
						Int[index] = 10 + Int[index] - diffInt.Int[index] - minus;
						minus = 1;
					}
					else {
						Int[index] = Int[index] - diffInt.Int[index] - minus;
						minus = 0;
					}

				}
				break;
			}
			else if (Int[i] < diffInt.Int[i]) {
				flag = -1;
				for (index; index < Int.size(); index++) {
					int x;
					if (diffInt.Int[index] - Int[index] - minus < 0) {
						x = 10 + diffInt.Int[index] - Int[index] - minus;
						minus = 1;
					}
					else {
						x = diffInt.Int[index] - Int[index] - minus;
						minus = 0;
					}

				}
				break;
			}
		}
	}

	for (int i = Int.size() - 1; i > 0; i--) {

		if (Int[i] == 0) {
			Int.erase(Int.begin() + i);
		}
		else {
			break;
		}
	}

	if ((*this) == diffInt) {
		Int.clear();
		Int.push_back(0);
	}

	return *this;
}

/*Integer& Integer::operator*=(Integer multiInt) {

}

Integer& Integer::operator/=(Integer Int) {

}*/