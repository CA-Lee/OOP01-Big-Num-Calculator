#pragma once

#include <iostream>
#include <string>
#include "Calculator.h"
#include "NumberObject.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class CLI {
	const string prefix = ">>> ";
	const string unknow_error /*division_zero*/ = "�L�N�q";
	const string  illegal_character = "�t�����X�k�r��";
	const string  Power_error = "��������0.5������";
	const string  variable_error = "�ܼƦW�٤��i������r";
//�t�����X�k�r��
//
//�L�N�q
//
//��������0.5������
//
//�ܼƦW�٤��i������r
//
//�Ʀr���i���ܼƦW�٤��r��
public:
	void start() {
		run_once();
		while (loop());
	}
	void run_once() {
		cout << "Big Number Calculatot CLI" << endl;
	}
	bool loop() {
		try {
			cout << prefix;
			string cmd;
			if (!getline(cin, cmd))return false;
			if (validate()) {
				cout << Calculator::evaluate(cmd) << endl;
			}
			else
			{
				cout << "Invalid input." << endl;
			}
		}
		catch (...) {
			cout << unknow_error << endl;
		}

		return true;
	}
	static bool validate() {
		return true;
	}
};

