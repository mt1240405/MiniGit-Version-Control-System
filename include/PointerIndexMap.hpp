#pragma once

#include "Common.hpp"

class PointerIndexMap
{
private:

    struct Entry
    {
        uintptr_t key;
        int value;

        bool used;
        bool tomb;

        Entry();
    };

    vector<Entry> table;

    int capacity;
    int size;

    size_t MixHash(uintptr_t value) const;

    void Rehash(int newCapacity);

public:

    explicit PointerIndexMap(
        int initialCapacity = 16384);

    bool Contains(
        void* pointer) const;

    bool Get(
        void* pointer,
        int& result) const;

    void Put(
        void* pointer,
        int value);

    bool Remove(
        void* pointer);
};
