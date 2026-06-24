#pragma once

#include "Common.hpp"

#include "FileRegistry.hpp"
#include "FileVersion.hpp"
#include "BinaryHeap.hpp"

class CommandProcessor
{
private:

    FileRegistry fileRegistry;

    BinaryHeap<RecentFileComparator>
        recentFiles;

    BinaryHeap<LargestVersionComparator>
        largestFiles;

    void HandleCreate();

    void HandleRead();

    void HandleInsert();

    void HandleUpdate();

    void HandleSnapshot();

    void HandleRollback();

    void HandleHistory();

    void HandleRecentFiles();

    void HandleLargestFiles();

    void HandleSearch();

    void HandleSearchHistory();

    void HandleStats();

public:

    CommandProcessor();

    void Run();
};
