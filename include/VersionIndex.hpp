#pragma once
#include "Common.hpp"
#include "TreeNode.hpp"
// VersionIndex maps VersionId -> TreeNode
class VersionIndex
{
    vector<TreeNode *> table;

public:
    explicit VersionIndex(int initialCapacity = 10000);

    bool Put(int versionId, TreeNode *node);

    bool Get(int versionId, TreeNode *&result);
    
};
