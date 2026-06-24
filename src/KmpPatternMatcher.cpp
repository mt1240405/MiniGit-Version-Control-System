#include "../include/KmpPatternMatcher.hpp"

vector<int> KmpPatternMatcher::BuildLps(
    const string& pattern)
{
    vector<int> lps(
        pattern.size(),
        0);

    int length = 0;

    int index = 1;

    while (index < pattern.size())
    {
        if (pattern[index] == pattern[length])
        {
            length++;

            lps[index] = length;

            index++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[index] = 0;

                index++;
            }
        }
    }

    return lps;
}

vector<int> KmpPatternMatcher::Search(
    const string& text,
    const string& pattern)
{
    vector<int> matches;

    if (pattern.empty())
    {
        return matches;
    }

    vector<int> lps =
        BuildLps(pattern);

    int textIndex = 0;

    int patternIndex = 0;

    while (textIndex < text.size())
    {
        if (
            text[textIndex] ==
            pattern[patternIndex])
        {
            textIndex++;

            patternIndex++;
        }

        if (
            patternIndex ==
            pattern.size())
        {
            matches.push_back(
                textIndex - patternIndex);

            patternIndex =
                lps[patternIndex - 1];
        }
        else if (
            textIndex < text.size() &&
            text[textIndex] !=
            pattern[patternIndex])
        {
            if (patternIndex != 0)
            {
                patternIndex =
                    lps[patternIndex - 1];
            }
            else
            {
                textIndex++;
            }
        }
    }

    return matches;
}
