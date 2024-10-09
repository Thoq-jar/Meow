#include "main.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <csignal>

using namespace std;

string command;
string name = "Meowlang REPL";
string help = " Help:\n  purr <args> - print out args\n  nap - quit\n  scratch - also quit\n  meow - show this screen\n  play <expression> - evaluate a mathematical expression";

void signalHandler(int signum) {
  cout << " Meow? Purr..." << endl;
  exit(signum);
}

double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 != 0) return num1 / num2;
            else {
                cout << "Error: Division by zero!" << endl;
                return 0;
            }
        default:
            cout << "Error: Invalid operator!" << endl;
            return 0;
    }
}

double eval(const string& expression) {
    stringstream ss(expression);
    double num1, num2;
    char op;

    ss >> num1 >> op >> num2;

    return calculate(num1, num2, op);
}

void parse(string userInput, CommandMap& commandMap) {
    string commandName;
    string args;

    stringstream ss(userInput);
    ss >> commandName;
    getline(ss, args);

    double result;

    switch (commandMap.getCommandCode(commandName)) {
        case 1:
            cout << args << endl;
            break;
        case 2:
            cout << " Meow? Purr..." << endl;
            exit(0);
        case 3:
            cout << help << endl;
            break;
        case 4:
            result = eval(args.substr(5));
            cout << "Result: " << result << endl;
            break;
        default:
            cout << " " << name << ": " << userInput << " is not a command!" << endl;
            break;
    }
}

void input(CommandMap& commandMap) {
    command = "";
    cout << " >> ";
    
    getline(cin, command);
    parse(command, commandMap);
}

int main() {
    signal(SIGINT, signalHandler);

    CommandMap commandMap;
    commandMap.addCommand("purr", 1);
    commandMap.addCommand("nap", 2);
    commandMap.addCommand("scratch", 2);
    commandMap.addCommand("meow", 3);
    commandMap.addCommand("play", 4);

    cout << " Welcome to " << name << "!" << endl;
    while (true) input(commandMap);
    return 0;
}