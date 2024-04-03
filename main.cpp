#include <iostream>
#include <string>
#include "database.h"

//void enterCommand();
std::string enterCommand();
void runCommand(Database &database);
void listCommand(Database &database);
void addCommand(Database &database);
void getCommand(Database &database);
void delCommand(Database &database);

int main() {
    Database database;
    init(database);

    std::string command;
    while (true) {
        command = enterCommand();

        if (command == "list") {
            listCommand(database);
            std::cout << std::endl;
        }
        else if (command == "add") {
            addCommand(database);
            std::cout << std::endl;
        }
        else if (command == "get") {
            getCommand(database);
            std::cout << std::endl;
        }
        else if (command == "del") {
            delCommand(database);
            std::cout << std::endl;
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "invalid command" << std::endl;
            std::cout << std::endl;
        }
    }

    destroy(database);

    return 0;
}