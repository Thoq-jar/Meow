#include <string>

using namespace std;

struct CommandNode {
    string command;
    int code;
    CommandNode* next;
};

class CommandMap {
public:
    CommandNode* head;

    CommandMap() : head(nullptr) {}

    void addCommand(const string& command, int code) {
        CommandNode* newNode = new CommandNode{command, code, head};
        head = newNode;
    }

    int getCommandCode(const string& commandName) {
        CommandNode* current = head;
        while (current != nullptr) {
            if (current->command == commandName) {
                return current->code;
            }
            current = current->next;
        }
        return 0;
    }

    ~CommandMap() {
        while (head != nullptr) {
            CommandNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
