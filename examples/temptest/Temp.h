#pragma once

class Temp
{
public:
	template<typename T> void AddObj();

	//void DestroyObj();
};

#ifndef TMP
#include "Temp.cpp"
#include "Temp_temp.cpp"
#endif // !TMP

