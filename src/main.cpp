#include "../include/CommandProcessor.hpp"

int main()
{
    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    CommandProcessor processor;

     ifstream logFile("commands.log");
     auto *CinBuffer = cin.rdbuf();
     cin.rdbuf(logFile.rdbuf());

    processor.SetReplayMode(true);
    processor.Run(cin);
    cin.rdbuf(CinBuffer);
    processor.SetReplayMode(false);
    processor.Run(cin);

    return 0;
}
