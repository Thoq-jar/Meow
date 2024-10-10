#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "main.hh"
#include "utils.hh"

using namespace std;

string command;
string name = "Meowlang REPL";
string help = R"( 
 Help:
  purr <args> - print out args
  nap - quit
  scratch - also quit
  meow! - show this screen
  play <expression> - evaluate a mathematical expression
)";

void signalHandler(int signum) {
  cout << "\n Meow? Purr..." << endl;
  exit(signum);
}

double calculate(double num1, double num2, char op) {
  switch (op) {
    case '+':
      return num1 + num2;
    case '-':
      return num1 - num2;
    case '*':
      return num1 * num2;
    case '/':
      if (num2 != 0)
        return num1 / num2;
      else {
        error("division by zero!\n");
        return 0;
      }
    default:
      error("invalid operator!\n");
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
      error("Meowlang: '" + command + "' is not a command!\n Enter 'meow!' for help");
      break;
  }
}

void input(CommandMap& commandMap) {
  command = "";
  cout << " >> ";

  getline(cin, command);
  parse(command, commandMap);
}

void executeFile(const string& filename, CommandMap& commandMap) {
  ifstream file(filename);
  if (!file.is_open()) {
    error("could not open file " + filename + "\n");
    return;
  }

  string line;
  while (getline(file, line)) {
    parse(line, commandMap);
  }

  file.close();
}

int main(int argc, char* argv[]) {
  signal(SIGINT, signalHandler);

  CommandMap commandMap;
  commandMap.addCommand("purr", 1);
  commandMap.addCommand("nap", 2);
  commandMap.addCommand("scratch", 2);
  commandMap.addCommand("meow!", 3);
  commandMap.addCommand("play", 4);

  if (argc > 1) {
    string filename = argv[1];
    executeFile(filename, commandMap);
  } else {
    cout << " Welcome to " << name << "!" << endl;
    while (true) input(commandMap);
  }

  return 0;
}