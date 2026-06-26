#include "../include/TreeNode.hpp"

TreeNode::TreeNode(int versionId, string content, TreeNode *parent)
{
    VersionId = versionId;
    Content = content;
    Message = "";

    CreatedTimestamp = time(nullptr);
    SnapshotTimestamp = 0;
    Parent = parent;
}
