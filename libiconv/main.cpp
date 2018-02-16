#undef LIBICONV_TEST
#ifdef LIBICONV_TEST
#include "iconv.h"
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{
	iconv_t pIconv = iconv_open("gb2312", "utf-8");
	if (pIconv == (iconv_t)-1)
	{
		printf("iconv初始化失败\n");
		_getch();
		return -1;
	}
	const char* text = u8"这是一段utf-8测试文本";
	char buf[1024] = {};
	char* pOut = buf;
	size_t outLen = sizeof(buf);
	const char* pIn = text;
	size_t inLen = strlen(text);
	size_t result = iconv(pIconv, &pIn, &inLen, &pOut, &outLen);
	if (result == -1)
	{
		size_t errcode = errno;
		printf("iconv转换失败: %d\n", errcode);

		char error[1024] = {};
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, LANG_USER_DEFAULT, error, sizeof(error), NULL);
		printf("%s\n", error);
		_getch();
		return -1;
	}

	printf("%s\n", buf);
	iconv_close(pIconv);
	_getch();
	return 0;
}
#endif