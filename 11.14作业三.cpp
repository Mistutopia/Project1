#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	double p, w, s, d=0,f;//p����ʾÿ��ÿǧ�׻���Ļ����˷� w����ʾ�������� s��������� d���ۿ� f�����˷�//
	printf("�����˷�=\n��������=\n�������=\n");
	scanf("%lf%lf%lf", &p, &w, &s);	
	if(250<=s<500)
	{
		d = 0.02;
	}
	if (500 <= s < 1000)
	{
		d = 0.05;
	}
	if (1000<= s < 2000)
	{
		d = 0.08;
	}
	if (2000 <= s < 3000)
	{
		d = 0.1;
	}
	if (3000 <= s)
	{
		d = 0.15;
	}
	f = p * w * s * (1 - d);
	printf("���˷�=%.2lf", f);
	return 0;
}