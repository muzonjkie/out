#include <stdio.h>
#include <setjmp.h>



void b(jmp_buf envbuf)
{
	printf("I am b func\n");
	longjmp(envbuf, 5);//5会作为setjmp的返回值
}

void a(jmp_buf envbuf)
{
	printf("before b(),I am a func\n");
	b(envbuf);
	printf("after b(),I am a func\n");
}

int main()
{
	int ret;
	//程序执行的现场，就是当时的寄存器的状态
	jmp_buf envbuf;
	ret=setjmp(envbuf);//setjmp第一次保存现场返回值为0
	if (0 == ret)
	{
		a(envbuf);
	}
	return 0;
}