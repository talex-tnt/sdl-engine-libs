#pragma once
#include "Compiler/Warning.h"
namespace utils
{
template<class T> 
inline T&& Placeholder(T&& i_placeholder)
{
	#pragma message WARN("Placeholder") // ... we don't have a stack trace yet
	return std::forward<T>(i_placeholder);
}
}