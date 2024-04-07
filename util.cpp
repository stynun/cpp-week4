#include <iostream>
#include <string>
#include <cstring>
#include "database.h"

std::string enterCommand() {
    std::string command;
    std::cout << "command (list, add, get, del, exit): ";
    std::cin >> command;

    return command;
}

void printArray(Array &arr) {
    std::cout << "[";
    if (arr.type == INT) {
        int* items = (int*)arr.items;
        for (int i = 0; i < arr.size; i++) {
            if (i != 0) {
                std::cout << ", ";
            } 
            std::cout << items[i];
        }
    }
    else if (arr.type == DOUBLE) {
        double* items = (double*)arr.items;
        for (int i = 0; i< arr.size; i++) {\
            if (i != 0) {
                std::cout << ", ";
            } 
            std::cout << items[i];
        }
    }
    else if (arr.type == STRING) {
        std::string* items = (std::string*)arr.items;
        for (int i = 0; i < arr.size; i++) {
            if (i != 0) {
                std::cout << ", ";
            } 
            std::cout << items[i];
        }
    }
    else if (arr.type == ARRAY) {
        Array* items = (Array*)arr.items;
        for (int i = 0; i < arr.size; ++i) {
            if (i != 0) {
                std::cout << ", ";
            } 
            printArray(items[i]);
        }
    }
    std::cout << "]";
}

void listCommand(Database &database) {
    for (int i = 0; i < database.count; i++) {
        std::cout << database.entries[i].key << ": ";
        
        if (database.entries[i].type == INT) {
            std::cout << *((int*)database.entries[i].value) << std::endl;
        }
        else if (database.entries[i].type == DOUBLE) {
            std::cout << *((double*)database.entries[i].value) << std::endl;
        }
        else if (database.entries[i].type == STRING) {
            std::cout << *((std::string*)database.entries[i].value) << std::endl;
        }
        else if (database.entries[i].type == ARRAY) {
            Array& arr = *(Array*)(database.entries[i].value);
            printArray(arr);
            std::cout << std::endl;
        }
    }
    
}

Array addArray(Array &arr) {
    std::cout << "value: ";
    std::cout << "type (int, double, string, array): ";
    std::string detailTypeStr;
    std::cin >> detailTypeStr;

    int size;
    std::cout << "size: ";
    std::cin >> arr.size;

    if (detailTypeStr == "int") {
        arr.type = INT;
        arr.items = new int[arr.size];
        int* items = (int*)(arr.items);
        for (int i = 0; i < arr.size; i++) {
        std::cout << "item[" << i << "]: ";

        std::cin >> items[i];
        }
    }
    else if (detailTypeStr == "double") {
        arr.type = DOUBLE;
        arr.items = new double[arr.size];
        double* items = (double*)(arr.items);
        for (int i = 0; i < arr.size; i++) {
        std::cout << "item[" << i << "]: ";

        std::cin >> items[i];
        }
    }
    else if (detailTypeStr == "string") {
        arr.type = STRING;
        arr.items = new char*[arr.size];
        char** items = (char**)(arr.items);
        for (int i = 0; i < arr.size; i++) {
            std::cout << "item[" << i << "]: ";
            std::string str;
            std::cin >> str;
            items[i] = new char[str.length() + 1];
            std::strcpy(items[i], str.c_str());
        }
    }
    else if (detailTypeStr == "array") {
        arr.type = ARRAY;
        arr.items = new Array[arr.size];

        Array* items = (Array*)(arr.items);
        for (int i = 0; i < arr.size; i++) {
            addArray(items[i]);
        }
    }
    else {
        std::cout << "invalid type";
        std::cout << std::endl;
    }
}

void addCommand(Database &database) {
    std::string typeStr;
    std::string key;
    Type type;

    std::cout << "key: ";
    std::cin >> key;
    
    std::cout << "type (int, double, string, array): ";
    std::cin >> typeStr;

    if (typeStr == "int") {
         std::cout << "value: ";

        type = INT;
        int tmp;
        std::cin >> tmp;
        int* value = new int(tmp);
        add(database, create(type, key, value));
    }
    else if (typeStr == "double") {
         std::cout << "value: ";

        type = DOUBLE;
        double tmp;
        std::cin >> tmp;
        double* value = new double(tmp);
        add(database, create(type, key, value));
    }
    else if (typeStr == "string") {
         std::cout << "value: ";

        type = STRING;
        std::string tmp;
        std::cin.ignore();
        getline(std::cin, tmp);
        std::string* value = new std::string(tmp);
        add(database, create(type, key, value));
    }
    else if (typeStr == "array") {  
        type = ARRAY;
        Array* arr = new Array;
        addArray(*arr);
        add(database, create(type, key, arr));
    }
    else {
         std::cout << "invalid type";
         std::cout << std::endl;
    }
}

void getCommand(Database &database) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;
    
    Entry *entry = get(database, key);
    if (entry == nullptr) {
        std::cout << "not found" << std::endl;
    }
    else {
        std::cout << entry->key << ": ";
        if (entry->type == INT) {
            std::cout << *((int*)entry->value) << std::endl;
        }
        else if (entry->type == DOUBLE) {
            std::cout << *((double*)entry->value) << std::endl;
        }
        else if (entry->type == STRING) {
            std::cout << *((std::string*)entry->value) << std::endl;
        }
        else if (entry->type == ARRAY) {
            Array& arr = *(Array*)entry->value;
            printArray(arr);
            std::cout << std::endl;
        }
    }
   
}

void delCommand(Database &database) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;

    remove(database, key);

}

