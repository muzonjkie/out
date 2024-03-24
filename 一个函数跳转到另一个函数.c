#include <stdio.h>
#include <setjmp.h>



void b(jmp_buf envbuf)
{
	printf("I am b func\n");
	longjmp(envbuf, 5);//5����Ϊsetjmp�ķ���ֵ
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
	//����ִ�е��ֳ������ǵ�ʱ�ļĴ�����״̬
	jmp_buf envbuf;
	ret=setjmp(envbuf);//setjmp��һ�α����ֳ�����ֵΪ0
	if (0 == ret)
	{
		a(envbuf);
	}
	return 0;
}