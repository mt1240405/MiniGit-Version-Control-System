#pragma once

#include "Common.hpp"
#include "TreeNode.hpp"
#include "VersionIndex.hpp"

class FileVersion
{
private:

    string fileName;

    TreeNode* root;

    TreeNode* activeVersion;

    VersionIndex versionIndex;

    int totalVersions;

    int lastModified;

    void DeleteVersionTree(TreeNode* node);

    void SearchHistoryDfs(
    TreeNode* node,
    const string& pattern);

public:

    FileVersion();
    ~FileVersion();
    void SetFileName(
        const string& name);

    const string& GetFileName() const;

    int GetTotalVersions() const;

    int GetLastModified() const;

    const string& GetContent() const;

    void Insert(
        const string& content);

    void Update(
        const string& content);

    void Snapshot(
        const string& message);

    bool Rollback(
        int versionId = -1);

    void PrintHistory() const;

    void SearchPattern(
    const string& pattern);

    void SearchPatternHistory(
    const string& pattern);

    void PrintStatistics();
    
};

struct RecentFileComparator
{
    bool operator()(
        FileVersion* left,
        FileVersion* right) const;
};

struct LargestVersionComparator
{
    bool operator()(
        FileVersion* left,
        FileVersion* right) const;
};
