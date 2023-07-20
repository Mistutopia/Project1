#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
sbit ds = P2 ^ 2;//�¶ȴ������ź���
sbit beep = P2 ^ 3;// ����������
uint temp;
uchar seg;
float f_temp;
uint warn_11 = 270;//�¶�ֵ���� 10�Ľ��.
uint warn_12 = 250;
uint warn_h1 = 300;
uint warn_h2 = 320;
sbit dula = P2 ^ 6;/*�� ���һ����*/
sbit wela = P2 ^ 7;
sbit led0 = P1 ^ 0;/*ָʾ�����ڱ�������*/
sbit led1 = P1 ^ 1;
sbit led2 = P1 ^ 2;
sbit led3 = P1 ^ 3;
unsigned char table[] = {
0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,//���� �������0��9���벻��С����
0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef //���� �������0��9���벻��С����
};
void main()
{
	uchar buff[4], k;
	dula = 0; wela = 0; init_com();
	while (1)
	{
		tempchange();
		for (k = 10; k > 0; k--)
		{
			dis_temp(get_temp());
		}
		deal(temp);
		sprintf(buff, "%f", f_temp);
		for (k = 10; k > 0; k--)
		{
			dis_temp(get_temp());
		}
		comm(buff);
		for (k = 10; k > 0; k--)
		{
			dis_temp(get_temp());
		}
	}
}
void delayms(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for (y = 110; y > 0; y--);
}
void dsreset()//��λ����(�¶ȴ�����)��ʼ��
{
	uint k;
	ds = 0;
	k = 103;
	while (k > 0) k--;
	ds = 1;
	k = 4;
	while (k > 0) k--;
}
bit tempreadbit(void) //�� һλ���ݺ���
{
	uint k;
	bit dat;
	ds = 0;
	k++;
	ds = 1;
	k++; k++;//k++����ʱ����
	dat = ds;
	k = 8;
	while (k > 0)k--;
	return (dat);
}
uchar tempread()//��һ���ֽں���
{
	uchar k, l, dat;
	dat = 0;
	for (k = 1; k <= 8; k++)
	{
		l = tempreadbit();
		dat = (l << 7) | (dat >> 1);// �������������λ����ǰ�棬�����պ�һһ���ֽ���DAT��
	}
	return (dat);
}
void tempwritebyte(uchar dat)//��DS18B20дһ���ֽ�����
{
	uint k;
	uchar l;
	bit testb;
	for (l = 1; l <= 8; l++)
	{
		testb = dat & 0x01;
		dat = dat >> 1;
		if (testb)//д1
		{
			ds = 0;
			k++; k++;
			ds = 1;
			k = 8; while (k > 0)k--;
		}
		else//д0
		{
			ds = 0;
			k = 8; while (k > 0)k--;
			ds = 1;
			k++; k++;
		}
	}
}
void tempchange()//��ȡ�¶Ȳ�ת��
{
	dsreset();
	delayms(1);
	tempwritebyte(0xcc);//д������ROMָ��
	tempwritebyte(0x44);//д�¶�ת��ָ��
}
uint get_temp()
{
	uchar a, b;
	dsreset();
	delayms(1);
	tempwritebyte(0xcc);
	tempwritebyte(0xbe);
	a = tempread(); //���Ͱ�λ
	b = tempread();//���߰�λ
	temp = b;
	temp <<= 8;//�����ֽ����Ϊһ����
	temp = temp | a;
	f_temp = temp * 0.0625;// �¶��ڼĴ�����Ϊ12λ���ֱ���Ϊ0.0625��
	temp = f_temp * 10 + 0.5;// ����10��ʾС�������ֻȡ1λ����0.5����������
	f_temp = f_temp + 0.05;
	return temp;// temp������
}
void display(char num, uchar dat)
{
	uchar k; dula = 0;
	P0 = table[dat]; dula = 1;
	dula = 0; wela = 0; k = 0XFF; k = k & (~((0X01) << (num)));
	P0 = k;
	wela = 1; wela = 0;
	delayms(1);
}
void dis_temp(uint t)
{
	uchar k; k = t / 100;//�¶���ֵ��ʮλ
	display(0, k);
	k = t % 100 / 10;//�¶���ʾ�ĸ�λ
	display(1, k + 10);
	k = t % 100 % 10;//�¶���ʾ��С�����һλ
	display(2, k);
}
void warn(uint s, uchar led)//����������������˸
{
	uchar k; k = s;//S����������LED ���Ƶ�
	beep = 0;
	P1 = ~(led);//������Ӧ�ĵ���
	while (k--);
	{
		dis_temp(get_temp());//�¶� ��������ʱ����
	}
	beep = 1;///����������
	P1 = 0xff;//������Ӧ�ĵ�
	k = s;
	while (k--);
	{
		dis_temp(get_temp());//�¶Ⱥ�������ʱ����
	}
}
void deal(uint t)
{
	uchar k;
	if ((t > warn_12) && (t <= warn_11))//�¶� ������
	{
		warn(40, 0x01);//�¶ȴ���25�ȣ� С��27�ȣ���һ���������������������Ρ���
	}

	else if (t < warn_12)//�¶�С��25��
	{
		warn(40, 0x03);//��һ���͵ڶ����������������������Ρ���
	}
	else if (t < warn_h2 && (t > warn_h1))//�¶� С��32�ȶ�����30��
	{
		warn(40, 0x04);//�������������������������Ρ���
	}
	else if (t > warn_h2)//�¶ȴ���32��
	{
		warn(10, 0x0c);//�������������������������Ρ���
	}
	else
	{
		k = 40;//��27��30��֮��ֻ�ǵ�����ʾ������ʱ
		while (k--)
		{
			dis_temp(get_temp());
		}
	}
}
void init_com(void)
{
	TMOD = 0x20;//���ڳ�ʼ������
	PCON = 0x00;
	SCON = 0x50;
	TH1 = 0xfd;//������9600
	TL1 = 0xfd;
	TR1 = 1;
}
void comm(char* parr)//���� ���ݷ���
{
	do
	{
		SBUF = *parr++;//��������
		while (!TI);//�ȴ� ������ɱ�־Ϊ1
		TI = 0;//��־����
	} while (*parr);//����ѭ��ֱ���ַ�Ϊ'\0��
}
