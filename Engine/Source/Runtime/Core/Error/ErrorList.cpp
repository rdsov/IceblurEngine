// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "ErrorList.h"

namespace Iceblur
{
    static const std::string ErrorTypes[] =
            {
                    "None",
                    "Multiple instances of %0 detected! This is not allowed. %1 %2"
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

    std::string Error::ToString(Error::ETypes error, const std::vector<std::string>& args)
    {
        std::string_view errorString = ErrorTypes[static_cast<int>(error)];
        std::string resultString = std::string(errorString);

        //Index that comes after the '%' character
        std::string indexStr;
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
                    //Start from indexStr
                    for (std::string::size_type j = i + 1 ; j < errorString.size() ; j++)
                    {
                        //If it's a digit, add it to the indexStr string, because it can have many digits
                        //If not, stop scanning any further and continue looping
                        if (isdigit(errorString[j]))
                        {
                            indexStr += errorString[j];
                        }
                        else
                        {
                            shouldBreak = true;
                            goto skip;
                        }
                    }

                    shouldBreak = true;
                }

                char* index;
                long argIndex = strtol(indexStr.c_str(), &index, 10);

                //Check if conversion was successful
                if (index)
                {
                    //Check if arguments are valid
                    if (!args.empty() && args.size() > argIndex)
                    {
                        //Replace %x with the corresponding argument
                        size_t replacePos = 0;
                        std::string searchStr = "%" + indexStr;
                        replacePos = resultString.find(searchStr, replacePos);
                        if (replacePos != std::string::npos)
                        {
                            resultString.replace(replacePos, indexStr.length() + 1, args[argIndex]);
                        }
                    }
                }

                indexStr.clear();
            }
        }

        return "";
    }

    std::string Error::ToString(Error::EFailed error, const std::string args[])
    {
        return FailedTypes[static_cast<int>(error)];
    }
}
