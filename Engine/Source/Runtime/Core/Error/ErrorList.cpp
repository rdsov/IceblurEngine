// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "ErrorList.h"

#include "Core/IO/Log.h"

namespace Iceblur
{
	static const std::string ErrorTypes[] =
			{
					"None",
					"Multiple instances of %0 detected! This is not allowed.",
					"%0 must be greater than zero!",
					"Unknown %0!",
					"No rendering pipeline found!",
					"Path was not found: %0",
					"%0 was not found!",
					"%0 is nullptr"
			};

	static const std::string FailedTypes[] =
			{
					"Failed to initialize GLAD!",
					"Failed to initialize GLFW!",
					"Failed to create window!",
					"Failed to cast %0 to %1!",
					"Failed to compile %0 shader! Path: %1",
					"Failed to link shader!",
			};

	ICE_ASSERT_ARRAY_ENUM(ErrorTypes, Error::ETypes);
	ICE_ASSERT_ARRAY_ENUM(FailedTypes, Error::EFailed)

	std::string Error::ToString(Error::ETypes error, const ErrorArgs& args)
	{
		std::string_view errorStr = ErrorTypes[static_cast<int>(error)];
		std::string result = std::string(errorStr);

		ProcessArgs(errorStr, result, args);

		return result;
	}

	std::string Error::ToString(Error::EFailed error, const ErrorArgs& args)
	{
		std::string_view errorStr = FailedTypes[static_cast<int>(error)];
		std::string result = std::string(errorStr);

		ProcessArgs(errorStr, result, args);

		return result;
	}

	void Error::ProcessArgs(std::string_view sourceStr, std::string& outResult, const ErrorArgs& args)
	{
		//Index that comes after the '%' character
		std::string indexStr;

		//Are any arguments provided?
		if (!args.empty())
		{
			for (std::string::size_type i = 0 ; i < sourceStr.size() ; i++)
			{
				//If the current character is '%' and we haven't
				//reached the penultimate character, keep looping
				if (sourceStr[i] == '%' && i != sourceStr.size() - 1)
				{
					bool shouldBreak = false;
					skip:
					while (!shouldBreak)
					{
						//Start from indexStr
						for (std::string::size_type j = i + 1 ; j < sourceStr.size() ; j++)
						{
							//If it's a digit, add it to the indexStr string, because it can have many digits
							//If not, stop scanning any further and continue looping
							if (isdigit(sourceStr[j]))
							{
								indexStr += sourceStr[j];
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
							replacePos = outResult.find(searchStr, replacePos);
							if (replacePos != std::string::npos)
							{
								outResult.replace(replacePos, indexStr.length() + 1, args[argIndex]);
							}
						}
						else
						{
							ICE_ERROR("Invalid arguments! Provided: " + ICE_TOS(args.size()));
						}
					}

					indexStr.clear();
				}
			}
		}
	}
}
