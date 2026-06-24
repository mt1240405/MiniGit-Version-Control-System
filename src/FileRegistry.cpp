#include "../include/FileRegistry.hpp"
#include "../include/FileVersion.hpp"

FileRegistry::Entry::Entry()
{
    value = nullptr;
    used = false;
    tomb = false;
}

unsigned long long FileRegistry::HashKey(
    const string& key) const
{
    const unsigned long long prime = 131;

    unsigned long long hash = 0;

    for (char character : key)
    {
        hash = hash * prime + character;
    }

    return hash;
}

FileRegistry::FileRegistry(
    int initialCapacity)
{
    capacity = initialCapacity;
    size = 0;

    table.resize(capacity);
}

bool FileRegistry::Put(
    const string& key,
    FileVersion* value)
{
    unsigned long long hash = HashKey(key);

    int index = hash % capacity;

    while (
        table[index].used &&
        !table[index].tomb &&
        table[index].key != key)
    {
        index = (index + 1) % capacity;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].used = true;
    table[index].tomb = false;

    return true;
}

bool FileRegistry::Get(
    const string& key,
    FileVersion*& result)
{
    unsigned long long hash = HashKey(key);

    int index = hash % capacity;
    int start = index;

    while (table[index].used)
    {
        if (
            !table[index].tomb &&
            table[index].key == key)
        {
            result = table[index].value;

            return true;
        }

        index = (index + 1) % capacity;

        if (index == start)
        {
            break;
        }
    }

    return false;
}

void FileRegistry::Clear()
{
    for (Entry& entry : table)
    {
        if (
            entry.used &&
            !entry.tomb &&
            entry.value)
        {
            delete entry.value;
        }
    }

    table.clear();

    table.resize(capacity);

    size = 0;
}
