#include <iostream>
#include "database.h"

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value) {
    Entry* entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;
    return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database) {
    database.entries = nullptr;
    database.count = 0;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry) {
    int index = -1;
    for (int i = 0; i < database.count; i++) {
        if (entry->key == database.entries[i].key) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        database.entries[index] = *entry;
    }
    else {
        Entry* tmp = new Entry[database.count + 1];
        for (int i = 0; i < database.count; i++) {
            tmp[i] = database.entries[i];
        }
        delete[] database.entries;
        database.entries = tmp;

        database.entries[database.count] = *entry;
        database.count++;
    }
    
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key) {
    for (int i = 0; i < database.count; i++) {
        if (key == database.entries[i].key) {
            return &database.entries[i];
        }
    }

    return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key) {
    int index = -1;
    for (int i = 0; i < database.count; i++) {
        if (key == database.entries[i].key) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < database.count - 1; i++) {
            database.entries[i] = database.entries[i + 1];
        }
        database.count--;

        Entry* tmp = new Entry[database.count];
        for (int i = 0; i < database.count; i++) {
            tmp[i] = database.entries[i];
        }
        delete[] database.entries;
        database.entries = tmp;
    }
    else {
        std::cout << "not found" << std::endl;
    }
}

// 데이터베이스를 해제한다.
void destroy(Database &database) {
    delete[] database.entries;
    database.count = 0;
}
