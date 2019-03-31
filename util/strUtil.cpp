#include "strUtil.h"
#include <sstream>
#include <algorithm>
#include "uLog.h"
//#include <windows.h>
//#include "util/platform.h"

#define  _stricmp strcasecmp

using namespace std;

std::vector<std::string> SUtil::split(const std::string& str, const std::string& pattern)
{
	std::vector<std::string> result;
	if (pattern.empty() || str.empty() || str.length() < pattern.length()) {
		return result;
	}

	std::string::size_type pos, prev = 0;
	do {
		pos = str.find(pattern, prev);
		if (pos != std::string::npos) {
			result.push_back(str.substr(prev, pos - prev));
			prev = pos + pattern.size();
		}
	} while (pos != std::string::npos);
	result.push_back(str.substr(prev));
	return result;
}

string SUtil::Format(const char* fmt, ...)
{
	std::string rStr;

	va_list ap;
	va_start(ap, fmt);

    size_t LOG_MAX_SIZE = 0;
#if 0
    LOG_MAX_SIZE = _vscprintf(fmt, ap); //内容长度，根据它给size赋值
#else
    {
        va_list apLen;
        va_copy(apLen, ap);
        LOG_MAX_SIZE = vsnprintf(NULL, 0, fmt, apLen);
        va_end(apLen);
    }
#endif

    if(LOG_MAX_SIZE>0) {
        rStr.reserve(LOG_MAX_SIZE + 2);
        rStr.resize(LOG_MAX_SIZE);
        vsnprintf((char *) rStr.data(), rStr.capacity(), fmt, ap);
    }

	va_end(ap);

	return rStr;
}

int SUtil::Find(const string& s, char f, int offsetStart, size_t offsetEnd)
{
	int start = offsetStart < 0 ? 0 : offsetStart;
	size_t end = s.size() < offsetEnd ? s.size() : offsetEnd;

	for (size_t i = start; i < end; i++)
	{
		if (s[i] == f)
		{
			return i;
		}
	}

	return -1;
}

string SUtil::ToString(bool b)
{
	return b ? "true" : "false";
}

static char *itoa(int64_t num,char *str,int size,int radix)
//num是输入数字，str是存放对应的字符串，radix是进制
{
    //char *temp = new char[size];
    int a, i = 0, j = 0;
    if (num < 0) {
        str[i++] = '-';
        num *= -1;
    }
    char *temp = str+i;
    while (num > 0 && j<size) {
        a = num % radix;
//        if (a > 9)
//            temp[j++] = a - 10 + 'A';
//        else
//            temp[j++] = a + '0';
        temp[j++] = a + (a>9?'A'-10:'0');
        num /= radix;
    }
    temp[j]='\0';
    //while (j > 0) {
    //    str[i++] = temp[--j];
    //}
    //delete []temp;
    //str[i] = '\0';
    return str;
}
#define _itoa_s itoa

string SUtil::ToString(int i, int base/*=10*/)
{
	std::stringstream ss;
	switch(base) {
	case 2: //从2 进制
	    {
		char buf[64];
		_itoa_s(i, buf, 64, 2);
		ss << buf;
	    }
		break;
	case 8: //从8 进制
		ss << std::oct << i;
		break;
	case 16: //从16 进制
		//ss << "0x";
		//ss << ss.width(sizeof(void*)) << ss.fill('0');
		ss << std::hex << i;
		break;
	case 10: //从10 进制
	default:
		ss << std::dec << i;
		break;
	}
	return ss.str();
}

string SUtil::ToString(uint32_t i, int base/*=10*/)
{
	std::stringstream ss;
	switch(base) {
	case 2: //从2 进制
	{
		char buf[64];
		_itoa_s(i, buf, 64, 2);
		//_itoa(l,buf , 2);
		ss << buf;
	}
		break;
	case 8: //从8 进制
		ss << std::oct << i;
		break;
	case 16: //从16 进制
		//ss << "0x";
		//ss << ss.width(sizeof(void*)) << ss.fill('0');
		ss << std::hex << i;
		break;
	case 10: //从10 进制
	default:
		ss << std::dec << i;
		break;
	}

	return ss.str();
}

string SUtil::ToString(int64_t l, int base/*=10*/)
{
	std::stringstream ss;
	switch(base) {
	case 2: //从2 进制
	{
		char buf[128];
		_itoa_s(l, buf, 128, 2);
		//_itoa(l,buf , 2);
		ss << buf;
	}
	break;
	case 8: //从8 进制
		ss << std::oct << l;
		break;
	case 16: //从16 进制
		//ss << "0x";
		//ss << ss.width(sizeof(void*)) << ss.fill('0');
		ss << std::hex << l;
		break;
	case 10: //从10 进制
	default:
		ss << std::dec << l;
		break;
	}
	return ss.str();
}

string SUtil::ToString(uint64_t l, int base/*=10*/)
{
	std::stringstream ss;
	switch(base) {
	case 2: //从2 进制
	{
		char buf[128];
		_itoa_s(l,buf,128 , 2);
		//_itoa(l,buf , 2);
		ss << buf;
	}
		break;
	case 8: //从8 进制
		ss << std::oct << l;
		break;
	case 16: //从16 进制
		//ss << "0x";
		//ss << ss.width(sizeof(void*)) << ss.fill('0');
		ss << std::hex << l;
		break;
	case 10: //从10 进制
	default:
		ss << std::dec << l;
		break;
	}
	return ss.str();
}

string SUtil::ToString(double d)
{
	std::stringstream ss;
	ss << d;
	return ss.str();
}

bool SUtil::ToBool(const string& b, bool def)
{
	if (0 == _stricmp(STR(b), "true")) {
		return true;
	} else if (0 == _stricmp(STR(b), "false")) {
		return false;
	} else {
		return def;
	}
}

int SUtil::ToInt(const string& i, int base/*=10*/)
{
	int ret;
	std::stringstream ss(i);
	switch(base) {
	case 2: //从2 进制
		ret = (int)strtol(i.c_str(), NULL, 2);
		break;
	case 8: //从8 进制
		ss >> std::oct >> ret;
		break;
	case 16: //从16 进制
		ss >> std::hex >> ret;
		break;
	case 10: //从10 进制
	default:
		ss >> std::dec >> ret;
		break;
	}
	return ret;
}

uint32_t SUtil::ToUInt(const std::string& i, int base/*=10*/)
{
	uint32_t ret=0;
	std::stringstream ss(i);
	switch(base) {
	case 2: //从2 进制
		ret = strtoul(i.c_str(), NULL, 2);
		break;
	case 8: //从8 进制
		ss >> std::oct >> ret;
		break;
	case 16: //从16 进制
		ss >> std::hex >> ret;
		break;
	case 10: //从10 进制
	default:
		ss >> std::dec >> ret;
		break;
	}

	return ret;
}

int64_t SUtil::ToLong(const string& l, int base/*=10*/)
{
	int64_t ret;
	std::stringstream ss(l);
	switch(base) {
	case 2: //从2 进制
		ret = strtoll(l.c_str(), NULL, 2);
		break;
	case 8: //从8 进制
		ss >> std::oct >> ret;
		break;
	case 16: //从16 进制
		ss >> std::hex >> ret;
		break;
	case 10: //从10 进制
	default:
		ss >> std::dec >> ret;
		break;
	}
	return ret;
}

uint64_t SUtil::ToULong(const string& l, int base/*=10*/)
{
	uint64_t ret;
	std::stringstream ss(l);
	switch(base) {
	case 2: //从2 进制
		ret = strtoull(l.c_str(), NULL, 2);
		break;
	case 8: //从8 进制
		ss >> std::oct >> ret;
		break;
	case 16: //从16 进制
		ss >> std::hex >> ret;
		break;
	case 10: //从10 进制
	default:
		ss >> std::dec >> ret;
		break;
	}
	return ret;
}

double SUtil::ToDouble(const string& d)
{
	std::stringstream ss;
	ss << d;
	double ret;
	ss >> ret;
	return ret;
}
