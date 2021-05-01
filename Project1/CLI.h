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
public:
	void start() {
		run_once();
		while (loop());
	}
	void run_once() {
		cout << "Big Number Calculatot CLI" << endl;
	}
	bool loop() {
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

		return true;
	}
	static bool validate() {
		return true;
	}
};

//�t�����X�k�r��
//
//�L�N�q
//
//��������0.5������
//
//�ܼƦW�٤��i������r
//
//�Ʀr���i���ܼƦW�٤��r��
//
