#pragma once


#define X_OBJ_RELEASE(x){ delete x; x = NULL;}
#define X_ARR_RELEASE(x){ delete[] x; x = NULL;}


namespace XUtils {

	void XLogToFile();

#pragma region Ä£°åÊµÏÖ 
	template<typename T1, typename T2>
	struct XSameType
	{
		operator bool()
		{
			return false;
		}
	};

	template<typename T1>
	struct XSameType<T1, T1>
	{
		operator bool()
		{
			return true;
		}
	};

#pragma endregion

}

using namespace XUtils;





