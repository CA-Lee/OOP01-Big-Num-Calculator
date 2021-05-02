#pragma once

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "Calculator.h"
#include "NumberObject.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;

struct var_404:std::exception {};

class CLI {
	const string prefix = ">>> ";
	const string unknown_error = "���������~";
	const string division_zero = "�L�N�q";
	const string illegal_character = "�t�����X�k�r��";
	const string Power_error = "��������0.5������";
	const string variable_error = "�ܼƦW�٤��X�k";
	const string variable_not_found = "�L���ܼ�";
	map<string, Number> vars = {};

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
			if (validate(cmd)) {
				if (cmd.find("Set") != -1) {
					cmd = cmd.substr(cmd.find("Set") + 4,
						cmd.size() - (cmd.find("Set") + 4));
					string type;
					if (cmd.find("Integer") != -1) {
						cmd = cmd.substr(cmd.find("Integer") + 8,
							cmd.size() - (cmd.find("Integer") + 8));
						type = "Integer";
					}
					else if (cmd.find("Decimal") != -1) {
						cmd = cmd.substr(cmd.find("Decimal") + 8,
							cmd.size() - (cmd.find("Decimal") + 8));
						type = "Decimal";
					}
					string name = cmd.substr(0, cmd.find('='));
					while (name[0] == ' ')
					{
						name.erase(0, 1);
					}
					while (name[name.size()-1] == ' ')
					{
						name.pop_back();
					}

					cmd = cmd.substr(cmd.find('=') + 1, cmd.size() - (cmd.find('=') + 1));

					Number r = evaluate(cmd);
					if (type == "Integer") {
						if (r.type != Number::INTEGER)r = Integer(r.decimal.to_integer());
					}
					else {
						if (r.type != Number::DECIMAL)r = Decimal(r.integer);
					}
					vars[name] = r;

				}
				else if (cmd.find('=') != -1) {
					string name = cmd.substr(0, cmd.find('='));
					while (name[0] == ' ')
					{
						name.erase(0, 1);
					}
					while (name[name.size() - 1] == ' ')
					{
						name.pop_back();
					}

					cmd = cmd.substr(cmd.find('=') + 1, cmd.size() - (cmd.find('=') + 1));

					Number r = evaluate(cmd);
					if (vars[name].type == Number::INTEGER) {
						if (r.type != Number::INTEGER)r = Integer(r.decimal.to_integer());
					}
					else {
						if (r.type != Number::DECIMAL)r = Decimal(r.integer);
					}
					vars[name] = r;

				}
				else {
					cout << evaluate(cmd) << endl;
				}
			}
			else
			{
				cout << illegal_character << endl;
			}
		}
		catch (var_404 e) {
			cout << variable_error << endl;	
		}
		catch (dvide_zero_err e) {
			cout << division_zero << endl;
		}
		catch (...) {
			cout << unknown_error << endl;
		}

		return true;
	}
	static bool validate(string s) {
		// check char
		for (auto& c : s) {
			if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
				c == ' ' || c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' ||
				c == ')' || c == '^' || c == '!' || c == '='))
				return false;
		}
		

		// check () pair
		// check last char 
		return true;
	}

	Number evaluate(string cmd) {
		for (int i = 0; i < cmd.size(); i++) {
			if ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z')) {
				int c = 0;
				while (((i + c) < cmd.size()) && (cmd[i + c] >= 'a' && cmd[i + c] <= 'z') ||
					(cmd[i + c] >= 'A' && cmd[i + c] <= 'Z') ||
					(cmd[i + c] >= '0' && cmd[i + c] <= '9'))
				{
					c++;
				}
				if (vars.find(cmd.substr(i, c)) != vars.end()) {
					std::stringstream ss;
					ss << vars[cmd.substr(i, c)];
					cmd.replace(i, c, ss.str());
					i += ss.str().size();
				}
				else {
					throw var_404();
				}
			}
		}

		return Calculator::evaluate(cmd);
	}
};

