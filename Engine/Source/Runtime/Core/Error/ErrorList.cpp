// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "ErrorList.h"

namespace Iceblur
{
    static const std::string ErrorTypes[] =
            {
                    "None",
                    "Multiple instances of %0 detected! This is not allowed. %1 %50"
            };

    static const std::string FailedTypes[] =
            {
                    "Failed to initialize GLAD!",
                    "Failed to initialize GLFW!",
                    "Failed to create window!",
                    "Failed to cast event!"
            };

    ICE_ASSERT_ARRAY_ENUM(ErrorTypes, Error::ETypes);
    ICE_ASSERT_ARRAY_ENUM(FailedTypes, Error::EFailed)

    std::string Error::ToString(Error::ETypes error, const std::string args[])
    {
        std::string_view errorString = ErrorTypes[static_cast<int>(error)];

        //Index that comes after the '%' character
        std::string index;
        for (std::string::size_type i = 0 ; i < errorString.size() ; i++)
        {
            //If the current character is '%' and we haven't
            //reached the penultimate character, keep looping
            if (errorString[i] == '%' && i != errorString.size() - 1)
            {
                bool shouldBreak = false;
                skip:
                while (!shouldBreak)
                {
                    //Start from the index
                    for (std::string::size_type j = i + 1 ; j < errorString.size() ; j++)
                    {
                        //If it's a digit, add it to the index string, because it can have many digits
                        //If not, stop scanning any further and continue looping
                        if (isdigit(errorString[j]))
                        {
                            index += errorString[j];
                        }
                        else
                        {
                            shouldBreak = true;
                            goto skip;
                        }
                    }

                    shouldBreak = true;
                }

                index.clear();
            }
        }

        return "";
    }

    std::string Error::ToString(Error::EFailed error, const std::string args[])
    {
        return FailedTypes[static_cast<int>(error)];
    }
}
