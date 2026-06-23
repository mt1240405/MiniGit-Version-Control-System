#include "../include/CommandProcessor.hpp"

CommandProcessor::CommandProcessor()
{
}

void CommandProcessor::HandleCreate()
{
    string fileName;

    cin >> fileName;

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        cout
            << "File already exists"
            << endl;

        return;
    }

    file = new FileVersion();

    file->SetFileName(
        fileName);

    fileRegistry.Put(
        fileName,
        file);
}

void CommandProcessor::HandleRead()
{
    string fileName;

    cin >> fileName;

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        cout
            << file->GetContent()
            << endl;

        return;
    }

    cout
        << "No such file"
        << endl;
}

void CommandProcessor::HandleInsert()
{
    string fileName;
    string content;

    cin
        >> fileName
        >> content;

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        file->Insert(content);

        recentFiles.Push(file);

        largestFiles.Push(file);

        return;
    }

    cout
        << "No such file"
        << endl;
}

void CommandProcessor::HandleUpdate()
{
    string fileName;
    string content;

    cin
        >> fileName
        >> content;

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        file->Update(content);

        recentFiles.Push(file);

        largestFiles.Push(file);

        return;
    }

    cout
        << "No such file"
        << endl;
}

void CommandProcessor::HandleSnapshot()
{
    string fileName;

    cin >> fileName;

    string message;

    getline(
        cin,
        message);

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        file->Snapshot(
            message);

        recentFiles.Push(file);

        largestFiles.Push(file);

        return;
    }

    cout
        << "No such file"
        << endl;
}

void CommandProcessor::HandleRollback()
{
    string fileName;

    cin >> fileName;

    FileVersion* file = nullptr;

    if (
        !fileRegistry.Get(
            fileName,
            file))
    {
        cout
            << "No such file"
            << endl;

        return;
    }

    if (cin.peek() == '\n')
    {
        file->Rollback();
    }
    else
    {
        int versionId;

        cin >> versionId;

        file->Rollback(
            versionId);
    }

    recentFiles.Push(file);

    largestFiles.Push(file);
}

void CommandProcessor::HandleHistory()
{
    string fileName;

    cin >> fileName;

    FileVersion* file = nullptr;

    if (
        fileRegistry.Get(
            fileName,
            file))
    {
        file->PrintHistory();

        return;
    }

    cout
        << "No such file"
        << endl;
}

void CommandProcessor::HandleRecentFiles()
{
    int count;

    cin >> count;

    vector<FileVersion*> popped;

    for (
        int index = 0;
        index < count &&
        !recentFiles.Empty();
        ++index)
    {
        FileVersion* file =
            recentFiles.Top();

        cout
            << file->GetFileName()
            << endl;

        popped.push_back(
            file);

        recentFiles.Pop();
    }

    for (
        FileVersion* file
        : popped)
    {
        recentFiles.Push(
            file);
    }
}

void CommandProcessor::HandleLargestFiles()
{
    int count;

    cin >> count;

    vector<FileVersion*> popped;

    for (
        int index = 0;
        index < count &&
        !largestFiles.Empty();
        ++index)
    {
        FileVersion* file =
            largestFiles.Top();

        cout
            << file->GetFileName()
            << endl;

        popped.push_back(
            file);

        largestFiles.Pop();
    }

    for (
        FileVersion* file
        : popped)
    {
        largestFiles.Push(
            file);
    }
}

void CommandProcessor::Run()
{
    string command;

    while (cin >> command)
    {
        if (command == "CREATE")
        {
            HandleCreate();
        }
        else if (command == "READ")
        {
            HandleRead();
        }
        else if (command == "INSERT")
        {
            HandleInsert();
        }
        else if (command == "UPDATE")
        {
            HandleUpdate();
        }
        else if (command == "SNAPSHOT")
        {
            HandleSnapshot();
        }
        else if (command == "ROLLBACK")
        {
            HandleRollback();
        }
        else if (command == "HISTORY")
        {
            HandleHistory();
        }
        else if (command == "RECENT_FILES")
        {
            HandleRecentFiles();
        }
        else if (command == "BIGGEST_FILES")
        {
            HandleLargestFiles();
        }
        else
        {
            cout
                << "Unknown command"
                << endl;
        }
    }
}
