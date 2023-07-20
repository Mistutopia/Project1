#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	double p, w, s, d=0,f;//p：表示每吨每千米货物的基本运费 w：表示货物重量 s：运输距离 d：折扣 f：总运费//
	printf("基本运费=\n货物重量=\n运输距离=\n");
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
	printf("总运费=%.2lf", f);
	return 0;
}