#pragma once
#include "Common.hpp"

struct TreeNode
{
    int VersionId;
    string Content;
    string Message;
    time_t CreatedTimestamp;
    time_t SnapshotTimestamp;
    TreeNode *Parent;
    vector<TreeNode *> Children;

    TreeNode(int versionId, string content ="", TreeNode *parent = nullptr);
};

