#pragma once

#include "Common.hpp"

class KmpPatternMatcher
{
public:

    static vector<int> Search(
        const string& text,
        const string& pattern);

private:

    static vector<int> BuildLps(
        const string& pattern);
};
