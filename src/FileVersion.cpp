#include "../include/FileVersion.hpp"
#include "../include/KmpPatternMatcher.hpp"

namespace
{
    struct SnapshotComparator
    {
        bool operator()(
            TreeNode* left,
            TreeNode* right) const
        {
            return left->CreatedTimestamp >
                   right->CreatedTimestamp;
        }
    };
}

FileVersion::FileVersion()
    : versionIndex(100003)
{
    totalVersions = 0;

    root = new TreeNode(0, "");

    root->Message =
        "Initial snapshot";

    root->SnapshotTimestamp =
        time(nullptr);

    activeVersion = root;

    versionIndex.Put(
        0,
        root);

    lastModified =
        root->CreatedTimestamp;
}

void FileVersion::DeleteVersionTree(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    for (TreeNode* child : node->Children)
    {
        DeleteVersionTree(child);
    }

    delete node;
}

FileVersion::~FileVersion()
{
    DeleteVersionTree(root);
}

void FileVersion::SetFileName(
    const string& name)
{
    fileName = name;
}

const string&
FileVersion::GetFileName() const
{
    return fileName;
}

int FileVersion::GetTotalVersions() const
{
    return totalVersions;
}

int FileVersion::GetLastModified() const
{
    return lastModified;
}

const string&
FileVersion::GetContent() const
{
    return activeVersion->Content;
}

void FileVersion::Insert(
    const string& content)
{
    if (activeVersion->SnapshotTimestamp != 0)
    {
        totalVersions++;

        TreeNode* node =
            new TreeNode(
                totalVersions,
                activeVersion->Content +
                content,
                activeVersion);

        activeVersion
            ->Children
            .push_back(node);
        node->Parent = activeVersion;
        activeVersion = node;

        versionIndex.Put(
            totalVersions,
            node);

        lastModified =
            node->CreatedTimestamp;
    }
    else
    {
        activeVersion->Content +=
            content;

        lastModified =
            time(nullptr);
    }
}

void FileVersion::Update(
    const string& content)
{
    if (activeVersion->SnapshotTimestamp != 0)
    {
        totalVersions++;

        TreeNode* node =
            new TreeNode(
                totalVersions,
                content,
                activeVersion);
        
        node->Parent = activeVersion;
        activeVersion
            ->Children
            .push_back(node);

        activeVersion = node;

        versionIndex.Put(
            totalVersions,
            node);

        lastModified =
            node->CreatedTimestamp;
    }
    else
    {
        activeVersion->Content =
            content;

        lastModified =
            time(nullptr);
    }
}

void FileVersion::Snapshot(
    const string& message)
{
    activeVersion
        ->SnapshotTimestamp =
        time(nullptr);

    activeVersion
        ->Message =
        message;
}

bool FileVersion::Rollback(
    int versionId)
{
    if (versionId == -1)
    {
        if (activeVersion->Parent)
        {
            activeVersion =
                activeVersion->Parent;

            return true;
        }

        cout
            << "Already at root"
            << endl;

        return false;
    }

    TreeNode* node;

    if (
        versionIndex.Get(
            versionId,
            node))
    {
        activeVersion =
            node;

        return true;
    }

    cout
        << "Invalid version"
        << endl;

    return false;
}

void FileVersion::PrintHistory() const
{
    vector<TreeNode*> snapshots;

    TreeNode* current =
        activeVersion;

    while (current)
    {
        if (
            current
                ->SnapshotTimestamp
            != 0)
        {
            snapshots.push_back(
                current);
        }

        current =
            current->Parent;
    }

    sort(
        snapshots.begin(),
        snapshots.end(),
        SnapshotComparator());

    for (TreeNode* node : snapshots)
    {
        cout
            << "ID "
            << node->VersionId
            << " Time "
            << ctime(
                   &node
                        ->SnapshotTimestamp)
            << " Msg "
            << node->Message
            << endl;
    }
}

bool RecentFileComparator::operator()(
    FileVersion* left,
    FileVersion* right) const
{
    return
        left->GetLastModified()
        >
        right->GetLastModified();
}

bool LargestVersionComparator::operator()(
    FileVersion* left,
    FileVersion* right) const
{
    return
        left->GetTotalVersions()
        >
        right->GetTotalVersions();
}

void FileVersion::SearchPattern(
    const string& pattern)
{
    vector<int> matches =
        KmpPatternMatcher::Search(
            activeVersion->Content,
            pattern);

    if (matches.empty())
    {
        cout
            << "Pattern not found"
            << endl;

        return;
    }

    cout
        << "Found at indices: ";

    for (int position : matches)
    {
        cout
            << position
            << " ";
    }

    cout << endl;
}

void FileVersion::SearchHistoryDfs(
    TreeNode* node,
    const string& pattern)
{
    if (node == nullptr)
    {
        return;
    }

    vector<int> matches =
        KmpPatternMatcher::Search(
            node->Content,
            pattern);

    if (!matches.empty())
    {
        cout
            << "Version "
            << node->VersionId
            << endl;
    }

    for (TreeNode* child :
         node->Children)
    {
        SearchHistoryDfs(
            child,
            pattern);
    }
}

void FileVersion::SearchPatternHistory(
    const string& pattern)
{
    SearchHistoryDfs(
        root,
        pattern);
}

void FileVersion::PrintStatistics()
{
    int snapshotCount = 0;

    vector<TreeNode*> stack;

    stack.push_back(root);

    while (!stack.empty())
    {
        TreeNode* current =
            stack.back();

        stack.pop_back();

        if (
            current->SnapshotTimestamp != 0)
        {
            snapshotCount++;
        }

        for (
            TreeNode* child :
            current->Children)
        {
            stack.push_back(child);
        }
    }

    cout
        << "File Name: "
        << fileName
        << endl;

    cout
        << "Versions: "
        << totalVersions + 1
        << endl;

    cout
        << "Snapshots: "
        << snapshotCount
        << endl;

    cout
        << "Current Version: "
        << activeVersion->VersionId
        << endl;

    cout
        << "Content Length: "
        << activeVersion->Content.size()
        << endl;
}
