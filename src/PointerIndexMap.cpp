#include "../include/PointerIndexMap.hpp"

PointerIndexMap::Entry::Entry()
{
    key = 0;
    value = -1;

    used = false;
    tomb = false;
}

PointerIndexMap::PointerIndexMap(
    int initialCapacity)
{
    capacity = initialCapacity;
    size = 0;

    table.resize(capacity);
}

size_t PointerIndexMap::MixHash(
    uintptr_t value) const
{
    value ^= value >> 33;
    value *= 0xff51afd7ed558ccdULL;

    value ^= value >> 33;
    value *= 0xc4ceb9fe1a85ec53ULL;

    value ^= value >> 33;

    return static_cast<size_t>(value);
}

void PointerIndexMap::Rehash(
    int newCapacity)
{
    vector<Entry> oldTable = move(table);

    table.clear();
    table.resize(newCapacity);

    capacity = newCapacity;
    size = 0;

    for (auto &entry : oldTable)
    {
        if (entry.used && !entry.tomb)
        {
            size_t index =
                MixHash(entry.key) % capacity;

            while (table[index].used)
            {
                index =
                    (index + 1) % capacity;
            }

            table[index].key = entry.key;
            table[index].value = entry.value;

            table[index].used = true;
            table[index].tomb = false;

            ++size;
        }
    }
}

bool PointerIndexMap::Contains(
    void *pointer) const
{
    int dummy;

    return Get(pointer, dummy);
}

bool PointerIndexMap::Get(
    void *pointer,
    int &result) const
{
    uintptr_t key =
        reinterpret_cast<uintptr_t>(pointer);

    size_t index =
        MixHash(key) % capacity;

    size_t start = index;

    while (table[index].used)
    {
        if (
            !table[index].tomb &&
            table[index].key == key)
        {
            result = table[index].value;

            return true;
        }

        index =
            (index + 1) % capacity;

        if (index == start)
        {
            break;
        }
    }

    return false;
}

void PointerIndexMap::Put(
    void *pointer,
    int value)
{
    if ((size + 1) * 2 >= capacity)
    {
        Rehash(capacity * 2);
    }

    uintptr_t key =
        reinterpret_cast<uintptr_t>(pointer);

    size_t index =
        MixHash(key) % capacity;

    while (
        table[index].used &&
        !table[index].tomb &&
        table[index].key != key)
    {
        index =
            (index + 1) % capacity;
    }

    bool insertingNew =
        !(table[index].used &&
          !table[index].tomb &&
          table[index].key == key);

    table[index].key = key;
    table[index].value = value;

    table[index].used = true;
    table[index].tomb = false;

    if (insertingNew)
    {
        ++size;
    }
}

bool PointerIndexMap::Remove(
    void *pointer)
{
    uintptr_t key =
        reinterpret_cast<uintptr_t>(pointer);

    size_t index =
        MixHash(key) % capacity;

    size_t start = index;

    while (table[index].used)
    {
        if (
            !table[index].tomb &&
            table[index].key == key)
        {
            table[index].tomb = true;

            --size;

            return true;
        }

        index =
            (index + 1) % capacity;

        if (index == start)
        {
            break;
        }
    }

    return false;
}
