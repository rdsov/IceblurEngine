// Copyright (c) 2021 Futureblur. All rights reserved.

#include <iostream>

namespace Iceblur
{
    __declspec(dllimport) void Hello();
}

int main()
{
    Iceblur::Hello();
    std::cin.get();
    return 0;
}