/*��һ��100Ԫ������һ���5�顢10�顢20���ֽ�ң�ÿ��ֽ������һ�ţ������ļ��ֻ�����*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>
int main()
{
	int n5, n10, n20;
	int m5, m10, m20;
	int min, count = 0;
		for (n5 = 1; n5 < 20; n5++)
		{
			for (n10 = 1; n10 < 10; n10++)
			{
				for (n20 = 1; n20 < 5; n20++)
				{
					if (n5 * 5 + n10 * 10 + n20 * 20 == 100)
					{
						if (count == 0)
						{
							min = n5 + n20 + n10;
							count++;
							m5 = n5; m10 = n10; m20 = n20;
						}
						else if (min > n5 + n20 + n10)
						{
							min = n5 + n20 + n10;
							m5 = n5; m10 = n10; m20 = n20;
						}
					}
					printf("$5--%d, $10--%d, $20--%d\n", n5, n10, n20);
				}
			}
		}
		return 0;
}