#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
sbit ds = P2 ^ 2;//温度传感器信号线
sbit beep = P2 ^ 3;// 蜂鸣器引脚
uint temp;
uchar seg;
float f_temp;
uint warn_11 = 270;//温度值乘以 10的结果.
uint warn_12 = 250;
uint warn_h1 = 300;
uint warn_h2 = 320;
sbit dula = P2 ^ 6;/*数 码管一控制*/
sbit wela = P2 ^ 7;
sbit led0 = P1 ^ 0;/*指示灯用于报警控制*/
sbit led1 = P1 ^ 1;
sbit led2 = P1 ^ 2;
sbit led3 = P1 ^ 3;
unsigned char table[] = {
0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,//共阴 极数码管0到9编码不带小数点
0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef //共阴 极数码管0到9编码不带小数点
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
void dsreset()//复位函数(温度传感器)初始化
{
	uint k;
	ds = 0;
	k = 103;
	while (k > 0) k--;
	ds = 1;
	k = 4;
	while (k > 0) k--;
}
bit tempreadbit(void) //读 一位数据函数
{
	uint k;
	bit dat;
	ds = 0;
	k++;
	ds = 1;
	k++; k++;//k++起延时作用
	dat = ds;
	k = 8;
	while (k > 0)k--;
	return (dat);
}
uchar tempread()//读一个字节函数
{
	uchar k, l, dat;
	dat = 0;
	for (k = 1; k <= 8; k++)
	{
		l = tempreadbit();
		dat = (l << 7) | (dat >> 1);// 读出的数据最低位在最前面，这样刚好一一个字节在DAT里
	}
	return (dat);
}
void tempwritebyte(uchar dat)//向DS18B20写一个字节数据
{
	uint k;
	uchar l;
	bit testb;
	for (l = 1; l <= 8; l++)
	{
		testb = dat & 0x01;
		dat = dat >> 1;
		if (testb)//写1
		{
			ds = 0;
			k++; k++;
			ds = 1;
			k = 8; while (k > 0)k--;
		}
		else//写0
		{
			ds = 0;
			k = 8; while (k > 0)k--;
			ds = 1;
			k++; k++;
		}
	}
}
void tempchange()//获取温度并转换
{
	dsreset();
	delayms(1);
	tempwritebyte(0xcc);//写跳过读ROM指令
	tempwritebyte(0x44);//写温度转换指令
}
uint get_temp()
{
	uchar a, b;
	dsreset();
	delayms(1);
	tempwritebyte(0xcc);
	tempwritebyte(0xbe);
	a = tempread(); //读低八位
	b = tempread();//读高八位
	temp = b;
	temp <<= 8;//两个字节组合为一个字
	temp = temp | a;
	f_temp = temp * 0.0625;// 温度在寄存器中为12位，分辨率为0.0625度
	temp = f_temp * 10 + 0.5;// 乘以10表示小数点后面只取1位，加0.5是四舍五入
	f_temp = f_temp + 0.05;
	return temp;// temp是整型
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
	uchar k; k = t / 100;//温度数值的十位
	display(0, k);
	k = t % 100 / 10;//温度显示的个位
	display(1, k + 10);
	k = t % 100 % 10;//温度显示的小数点后一位
	display(2, k);
}
void warn(uint s, uchar led)//蜂鸣器报警，灯闪烁
{
	uchar k; k = s;//S控制音调，LED 控制灯
	beep = 0;
	P1 = ~(led);//控制相应的灯亮
	while (k--);
	{
		dis_temp(get_temp());//温度 函数起延时作用
	}
	beep = 1;///蜂鸣器不响
	P1 = 0xff;//控制相应的灯
	k = s;
	while (k--);
	{
		dis_temp(get_temp());//温度函数起延时作用
	}
}
void deal(uint t)
{
	uchar k;
	if ((t > warn_12) && (t <= warn_11))//温度 处理函数
	{
		warn(40, 0x01);//温度大于25度， 小于27度，第一个灯亮，蜂鸣器发出“滴”声
	}

	else if (t < warn_12)//温度小于25度
	{
		warn(40, 0x03);//第一个和第二个灯亮，蜂鸣器发出“滴”声
	}
	else if (t < warn_h2 && (t > warn_h1))//温度 小于32度而大于30度
	{
		warn(40, 0x04);//第三个灯亮，蜂鸣器发出“滴”声
	}
	else if (t > warn_h2)//温度大于32度
	{
		warn(10, 0x0c);//第三个灯亮，蜂鸣器发出“滴”声
	}
	else
	{
		k = 40;//在27到30度之间只是调用显示函数延时
		while (k--)
		{
			dis_temp(get_temp());
		}
	}
}
void init_com(void)
{
	TMOD = 0x20;//串口初始化函数
	PCON = 0x00;
	SCON = 0x50;
	TH1 = 0xfd;//波特率9600
	TL1 = 0xfd;
	TR1 = 1;
}
void comm(char* parr)//串口 数据发送
{
	do
	{
		SBUF = *parr++;//发送数据
		while (!TI);//等待 发送完成标志为1
		TI = 0;//标志清零
	} while (*parr);//保持循环直到字符为'\0’
}
