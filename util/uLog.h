//
// Created by lance on 2019-03-31.
//

#ifndef __CPPTEST_ULOG_H
#define __CPPTEST_ULOG_H



#ifdef LOG_FFLM
//log file,function,line,msg
#define LE(fmt, ...)   do{ __GETFILE_FUNC__;__GETFUNC_FUNC__; blog(LOG_ERROR  , "[f:%s::%s:%d][ERROR] " fmt,  gfile(__FILE__), gFunc(__FUNCTION__),__LINE__, ##__VA_ARGS__); }while(0)
#define LD(fmt, ...)   do{ __GETFILE_FUNC__;__GETFUNC_FUNC__; blog(LOG_DEBUG  , "[f:%s::%s:%d][DEBUG] " fmt,  gfile(__FILE__), gFunc(__FUNCTION__),__LINE__, ##__VA_ARGS__); }while(0)
#define LI(fmt, ...)   do{ __GETFILE_FUNC__;__GETFUNC_FUNC__; blog(LOG_INFO   , "[f:%s::%s:%d][INFO] "  fmt,  gfile(__FILE__), gFunc(__FUNCTION__),__LINE__, ##__VA_ARGS__); }while(0)
#define LW(fmt, ...)   do{ __GETFILE_FUNC__;__GETFUNC_FUNC__; blog(LOG_WARNING, "[f:%s::%s:%d][WARN] "  fmt,  gfile(__FILE__), gFunc(__FUNCTION__),__LINE__, ##__VA_ARGS__); }while(0)
#define LV(fmt, ...)   do{ __GETFILE_FUNC__;__GETFUNC_FUNC__; blog(LOG_VVV    , "[f:%s::%s:%d][VVVV] "  fmt,  gfile(__FILE__), gFunc(__FUNCTION__),__LINE__, ##__VA_ARGS__); }while(0)
#elif defined LOG_FLM
//log file,line,msg
#define LE(fmt, ...)   do{ __GETFILE_FUNC__; blog(LOG_ERROR  , "[f:%s:%d][ERROR] " fmt,  gfile(__FILE__), __LINE__, ##__VA_ARGS__); }while(0)
#define LD(fmt, ...)   do{ __GETFILE_FUNC__; blog(LOG_DEBUG  , "[f:%s:%d][DEBUG] " fmt,  gfile(__FILE__), __LINE__, ##__VA_ARGS__); }while(0)
#define LI(fmt, ...)   do{ __GETFILE_FUNC__; blog(LOG_INFO   , "[f:%s:%d][INFO] "  fmt,  gfile(__FILE__), __LINE__, ##__VA_ARGS__); }while(0)
#define LW(fmt, ...)   do{ __GETFILE_FUNC__; blog(LOG_WARNING, "[f:%s:%d][WARN] "  fmt,  gfile(__FILE__), __LINE__, ##__VA_ARGS__); }while(0)
#define LV(fmt, ...)   do{ __GETFILE_FUNC__; blog(LOG_VVV    , "[f:%s:%d][VVVV] "  fmt,  gfile(__FILE__), __LINE__, ##__VA_ARGS__); }while(0)
#else
//log msg
//#define LE(fmt, ...)   do{ printf(LOG_ERROR  , "[ERROR] " fmt "\n",  ##__VA_ARGS__); }while(0)
//#define LD(fmt, ...)   do{ printf(LOG_DEBUG  , "[DEBUG] " fmt "\n",  ##__VA_ARGS__); }while(0)
//#define LI(fmt, ...)   do{ printf(LOG_INFO   , "[INFO] "  fmt "\n",  ##__VA_ARGS__); }while(0)
//#define LW(fmt, ...)   do{ printf(LOG_WARNING, "[WARN] "  fmt "\n",  ##__VA_ARGS__); }while(0)
//#define LV(fmt, ...)   do{ printf(LOG_VVV    , "[VVVV] "  fmt "\n",  ##__VA_ARGS__); }while(0)

#define LE(fmt, ...)   do{ printf("[ERROR] " fmt "\n",  ##__VA_ARGS__); }while(0)
#define LD(fmt, ...)   do{ printf("[DEBUG] " fmt "\n",  ##__VA_ARGS__); }while(0)
#define LI(fmt, ...)   do{ printf("[INFO] "  fmt "\n",  ##__VA_ARGS__); }while(0)
#define LW(fmt, ...)   do{ printf("[WARN] "  fmt "\n",  ##__VA_ARGS__); }while(0)
#define LV(fmt, ...)   do{ printf("[VVVV] "  fmt "\n",  ##__VA_ARGS__); }while(0)
#endif
//#undef __GETFILE_FUNC__
//#undef LOG_VVV

#define LVV(m,...)    LV(m, ##__VA_ARGS__)
#define LDB(m,...)    LD(m, ##__VA_ARGS__)
#define LIF(m,...)    LI(m, ##__VA_ARGS__)
#define LWN(m,...)    LW(m, ##__VA_ARGS__)
#define LER(m,...)    LE(m, ##__VA_ARGS__)

#define LIE(b,m,...)  do{if(b){LIF(m,##__VA_ARGS__);}else{LER(m,##__VA_ARGS__);}}while (0)
#define LIW(b,m,...)  do{if(b){LIF(m,##__VA_ARGS__);}else{LWN(m,##__VA_ARGS__);}}while (0)
#define RET_SF_STR(r)   ((r)?"success":"failed")
#define BOOL_STR(b) 	((b)?"true":"false")


#define STR(s)   ((s).c_str())

#endif //__CPPTEST_ULOG_H
