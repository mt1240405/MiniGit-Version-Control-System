#include "../include/VersionIndex.hpp"

VersionIndex::VersionIndex(int initialCapacity)
{
    table.resize(initialCapacity, nullptr);
}

bool VersionIndex::Put(
    int versionId,
    TreeNode* node)
{
    if (versionId >= static_cast<int>(table.size()))
    {
        table.resize(versionId * 2, nullptr);
    }

    table[versionId] = node;

    return true;
}

bool VersionIndex::Get(
    int versionId,
    TreeNode*& result)
{
    if (versionId < 0)
    {
        return false;
    }

    if (versionId >= static_cast<int>(table.size()))
    {
        return false;
    }

    if (table[versionId] == nullptr)
    {
        return false;
    }

    result = table[versionId];

    return true;
}
