// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

//Logs an error to the console if the pointer is null.
//Error message: 'Name' is nullptr
#define ICE_CHECK_NULL(ptr, name)   \
if (!ptr) \
{ \
ICE_ERROR(Error::ETypes::A_NULLPTR, { name }); \
return; \
} \

//Defines a singleton instance class which is used together with the ICE_SINGLETON macro.
#define ICE_SINGLETON_DEF(VarName, Class) static inline Class* VarName = nullptr;

//Checks if string is empty (only works for non-static functions).
//Inside static functions, use VIO::Empty() instead.
#define ICE_EMPTY(str) std::string::empty(str)

//Returns the class type as a string.
#define ICE_CLASS_TYPE(x) std::string(typeid(x).name())

template <typename T, typename P>
inline static bool FindInVector(const std::vector<T>& vector, P* pointer)
{
	auto it = std::find(vector.begin(), vector.end(), pointer);
	return it != vector.end();
}

//Returns true if item was found in vector.
#define FIND_IN_VECTOR(vector, item) std::find(vector.begin(), vector.end(), item) != vector.end()

//Returns true if item was not found in vector.
#define FIND_NOT_IN_VECTOR(vector, item) std::find(vector.begin(), vector.end(), item) == vector.end()

#define REMOVE_FROM_VECTOR(vector, item) vector.erase(std::remove(vector.begin(), vector.end(), item))

typedef const std::string& IceString;

typedef uint32_t VID;
