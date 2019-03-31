
#ifndef ___STRING_UTIL_H___
#define ___STRING_UTIL_H___

#include <string>
#include <vector>
#include <map>

class SUtil
{
public:
	/* 生成唯一 无符号整数 字串 */

	static std::vector<std::string> split(const std::string& str, const std::string& pattern);

	static std::string Format(const char* format, ...);

	//在s中查找f，查找区间为[offsetStart, offsetEnd)
	static int Find(const std::string& s, char f, int offsetStart, size_t offsetEnd);

	//字符串与其他类型互转
	static std::string ToString(bool b);//转换为'true'/'false'
	static std::string ToString(int i, int base=10);
	static std::string ToString(uint32_t i, int base=10);
	static std::string ToString(int64_t l, int base=10);
	static std::string ToString(uint64_t l, int base=10);
	static std::string ToString(double d);
	static bool ToBool(const std::string& b, bool def = false);//解析'true'/'false'，忽略大小写
	static int ToInt(const std::string& i, int base=10);
	static uint32_t ToUInt(const std::string& i, int base=10);
	static int64_t ToLong(const std::string& l, int base=10);
	static uint64_t ToULong(const std::string& l, int base=10);
	static double ToDouble(const std::string& d);


};

#endif /*___STRING_UTIL_H___*/

