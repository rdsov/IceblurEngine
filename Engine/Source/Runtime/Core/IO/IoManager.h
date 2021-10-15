// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

namespace Iceblur
{
    class ICE_API IOManager
    {
    public:
        //Returns true if the given file path/directory exists
        static bool Exists(const char* path)
        {
            return std::filesystem::exists(path);
        }

        //Returns the full path to the engine folder.
        //Returns an empty string if the path was not found.
        static std::string GetEngineLocation()
        {
            if (!Exists("InstallLocation.txt"))
            {
                return "";
            }

            std::ifstream file;
            file.open("InstallLocation.txt");
            std::string location;
            file >> location;
            file.close();

            return location;
        }
    };
}
