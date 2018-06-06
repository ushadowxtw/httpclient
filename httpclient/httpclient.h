#pragma once;  
#include <string>
using namespace std;
//该宏完成在dll项目内部使用__declspec(dllexport)导出  
//在dll项目外部使用时，用__declspec(dllimport)导入  
//宏DLL_IMPLEMENT在SimpleDLL.cpp中定义  
#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif  
DLL_API int add(int x, int y); //简单方法  
DLL_API int http_client_init(); //初始化
DLL_API int http_client_post( string& Urlstr,string& Pdata , string& Rdata);
DLL_API int http_client_get( string& Urlstr, string& Rdata);