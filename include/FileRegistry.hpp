#pragma once
#include "common.hpp"
class FileVersion;
class FileRegistry
{
    struct Entry
    {
        string key;
        FileVersion *value;
        bool used;
        bool tomb;
        Entry();
    };

    vector<Entry> table;
    int capacity;
    int size;

    unsigned long long HashKey(const string &key) const;

public:
    explicit FileRegistry(int initialCapacity = 10007);

    bool Put(const string &key, FileVersion *value);

    bool Get(const string &key, FileVersion *&result);
};
