/*按键功能说明：
矩阵键盘：
第1到第10个按键分别对应数字0-9；
独立按键：
Key1短按切换模式；
Key2按下则进行时钟和闹钟的设置；
Key3短按确认输入时间，长按清零；
Key4按下则停止闹铃*/
#include <reg52.h> 
#include <stdio.h> 
#include <intrins.h> 
#define uchar unsigned char 
#define uint unsigned int 
sbit DS = P2 ^ 2;   //DS18B20单总线
sbit key1 = P3 ^ 4;//按键
sbit key2 = P3 ^ 5;
sbit key3 = P3 ^ 6;
sbit key4 = P3 ^ 7;
sbit buff = P2 ^ 3;//蜂鸣器
sbit DU = P2 ^ 6;//段选
sbit WE = P2 ^ 7;//位选
sbit led0 = P1 ^ 0;/*指示灯用于报警控制*/
sbit led1 = P1 ^ 1;
sbit led2 = P1 ^ 2;
sbit led3 = P1 ^ 3;
uint warn_11 = 270;//温度值乘以10的结果
uint warn_12 = 250;
uint warn_h1 = 300;
uint warn_h2 = 320;
uchar bitdata[] = { 0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f };//数码管1-8
uchar segdata[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40 };//段选0-9以及-
uchar segdata_dp[] = { 0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef };//带小数点数段选0-9
uchar table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,//共阴 极数码管0到9编码不带小数点
0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef };//共阴 极数码管0到9编码不带小数点
uchar dis_arr[] = { 10,10,10,10,10,10 };//时钟显示数组 默认为-
uchar time[] = { 0,0,0 };//时钟 时分秒
uchar time_In[] = { 0,0,0,0,0,0 };
uchar time_clk[] = { 0,0,0 };//闹钟 时分秒
uchar t = 0;
uchar num = 0;
uchar mode = 0;
uchar keydown = 0;
uchar keyIn, keyvalue, i, temp;//矩阵键盘读入
uint temp_t;
float f_temp;
void key();
void init();
uchar keyscan();//矩阵键盘扫描函数
void delayms(uint x);//延时函数
void display(uchar duan1, uchar duan2, uchar duan3, uchar duan4, uchar duan5, uchar duan6);
void display_1(uchar wei, uchar duan);
void display_2(uchar wei, uchar duan);
void input();
void soundTime();
void dis_temp(uint t);
void deal(uint t);
void comm(char* parr);
void tempchange();
uint get_temp();
void init_com();
void main()
{
	input();
	if (mode == 0)
	{ 
		init();
	}
	else if (mode == 1)
	{ 
		init();
	}
	else if (mode == 2)
	{ 
		init_com(); 
	}
	while (1)
	{
		key();
		if (mode == 0)//时钟
		{
			display(time[0] / 10, time[0] % 10, time[1] / 10, time[1] % 10, time[2] / 10, time[2] % 10);
		}
		else if (mode == 1)//闹钟
		{
			display(time_clk[0] / 10, time_clk[0] % 10, time_clk[1] / 10, time_clk[1] % 10, time_clk[2] / 10, time_clk[2] % 10);
		}	
		else if (mode == 2)//温度
		{
			uchar buff[4], k;
			DU = 0; WE = 0;
			tempchange();
			for (k = 10; k > 0; k--)
			{
				dis_temp(get_temp());
			}
			deal(temp_t); 
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
			if (key1==0)
			{
				delayms(5);
				if (key1==0)
				mode = -1;
			}
		}
	}
}
void init_com(void)
{
	TMOD = 0x20;//串口初始化函数 T1工作在方式2
	PCON = 0x00;
	SCON = 0x50;
	TH1 = 0xfd;//波特率9600
	TL1 = 0xfd;
	TR1 = 1;
}
void init()//初始化函数
{
	P3 = 0xff;//给高电平
	TMOD = 0x01;//定时器工作方式选择1 T0工作在方式1
	TH0 = (65536 - 45872) / 256;
	TL0 = (65536 - 45872) % 256;
	EA = 1; //开总中断
	ET0 = 1;//允许定时器0中断
	TR0 = 1;//开始计数
	//P1=1;
}
void delayms(uint x)//延时函数
{
	uint i, j;
	for (i = x; i > 0; i--)
		for (j = 110; j > 0; j--);
}
void key()/*模式切换函数*/
{
	if (key1 == 0)
	{
		delayms(200);
		if (key1 == 0)//按压时不进行任何操作
		{
			delayms(1);
		}
		else if (key1 == 1)//松开后切换模式
		{
			mode++;
			if (mode == 3)mode = 0;
		}
	}
	if (key2 == 0)
	{
		delayms(100);
		if (key2 == 0)
		{
			delayms(500);
			input();
		}
	}
	if (key3 == 0)
	{
		delayms(200);
		if (key3 == 0)
		{
			if (mode == 0) {
				time[0] = 0;
				time[1] = 0;
				time[2] = 0;
				num = 0;
				while (!key3)display(time[0] / 10, time[0] % 10, time[1] / 10, time[1] % 10, time[2] / 10, time[2] % 10);
			}
			else if (mode == 1) {
				time_clk[0] = 0;
				time_clk[1] = 0;
				time_clk[2] = 0;
				while (!key3)display(time_clk[0] / 10, time_clk[0] % 10, time_clk[1] / 10, time_clk[1] % 10, time_clk[2] / 10, time_clk[2] % 10);
			}
		}
	}
	if (key4 == 0)
	{
		delayms(200);
		if (key4 == 0)
		{
			buff = 1;
		}
	}
}
uchar keyscan()//矩阵键盘扫描函数
{
	keyvalue = 99;
	P3 = 0xfe;
	temp = P3;
	temp = temp & 0xf0;//判断是否还等于0xf0
	while (temp != 0xf0)
	{
		delayms(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xee: {keyvalue = 0; keydown = 1; break; }
			case 0xde: {keyvalue = 1; keydown = 1; break; }
			case 0xbe: {keyvalue = 2; keydown = 1; break; }
			case 0x7e: {keyvalue = 3; keydown = 1; break; }
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}
	P3 = 0xfd;
	temp = P3;
	temp = temp & 0xf0;//判断是否还等于0xf0
	while (temp != 0xf0)
	{
		delayms(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xed: {keyvalue = 4; keydown = 1; break; }
			case 0xdd: {keyvalue = 5; keydown = 1; break; }
			case 0xbd: {keyvalue = 6; keydown = 1; break; }
			case 0x7d: {keyvalue = 7; keydown = 1; break; }
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}
	P3 = 0xfb;
	temp = P3;
	temp = temp & 0xf0;//判断是否还等于0xf0
	while (temp != 0xf0)
	{
		delayms(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xeb: {keyvalue = 8; keydown = 1; break; }
			case 0xdb: {keyvalue = 9; keydown = 1; break; }
			case 0xbb: {keyvalue = 10; keydown = 1; break; }
			case 0x7b: {keyvalue = 11; keydown = 1; break; }
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}
	P3 = 0xf7;
	temp = P3;
	temp = temp & 0xf0;//判断是否还等于0xf0
	while (temp != 0xf0)
	{
		delayms(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xe7: {keyvalue = 12; keydown = 1; break; }
			case 0xd7: {keyvalue = 13; keydown = 1; break; }
			case 0xb7: {keyvalue = 14; keydown = 1; break; }
			case 0x77: {keyvalue = 15; keydown = 1; break; }
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}
	return keyvalue;
}
void display(uchar duan1, uchar duan2, uchar duan3, uchar duan4, uchar duan5, uchar duan6)
{
	display_1(0, duan1);
	delayms(1);
	display_2(1, duan2);
	delayms(1);
	display_1(2, duan3);
	delayms(1);
	display_2(3, duan4);
	delayms(1);
	display_1(4, duan5);
	delayms(1);
	display_1(5, duan6);
	delayms(1);
}

void display_1(uchar wei, uchar duan)/*用于控制数码管显示。*/
{
	DU = 1;
	P0 = segdata[duan];
	DU = 0;
	P0 = 0xff;
	WE = 1;
	P0 = bitdata[wei];
	WE = 0;
	P0 = 0x00;
}
void display_2(uchar wei, uchar duan)/*同上 段选带小数点*/
{
	DU = 1;
	P0 = segdata_dp[duan];
	DU = 0;
	P0 = 0xff;
	WE = 1;
	P0 = bitdata[wei];
	WE = 0;
	P0 = 0x00;
}
void input()/*输入 input()函数，其作用是接收用户从数字键盘输入的时间数据，并存储在数组time_In[]中*/
{
	for (i = 0; i < 8; i++)//重置为-便于下次使用
	{
		dis_arr[i] = 10;
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)//检测到按键被按下
		{
			keydown = 0;
			dis_arr[0] = keyIn;
			time_In[0] = keyIn;
			if (time_In[0] >= 0 && time_In[0] <= 2)
				break;
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)
		{
			keydown = 0;
			dis_arr[1] = keyIn;
			time_In[1] = keyIn;
			if ((time_In[1] >= 0 && time_In[1] <= 9) && (time_In[0] * 10 + time_In[1]) < 24)
				break;
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)
		{
			keydown = 0;
			dis_arr[2] = keyIn;
			time_In[2] = keyIn;
			if (time_In[2] >= 0 && time_In[2] <= 5)
				break;
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)
		{
			keydown = 0;
			dis_arr[3] = keyIn;
			time_In[3] = keyIn;
			if ((time_In[3] >= 0 && time_In[3] <= 9) && (time_In[2] * 10 + time_In[3]) < 60)
				break;
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)
		{
			keydown = 0;
			dis_arr[4] = keyIn;
			time_In[4] = keyIn;
			if (time_In[4] >= 0 && time_In[4] <= 5)
				break;
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)
		{
			keydown = 0;
			dis_arr[5] = keyIn;
			time_In[5] = keyIn;
			if ((time_In[5] >= 0 && time_In[5] <= 9) && (time_In[4] * 10 + time_In[5]) < 60)
			{
				if (mode == 0)
				{
					time[0] = time_In[0] * 10 + time_In[1];
					time[1] = time_In[2] * 10 + time_In[3];
					time[2] = time_In[4] * 10 + time_In[5];
				}
				else if (mode == 1)
				{
					time_clk[0] = time_In[0] * 10 + time_In[1];
					time_clk[1] = time_In[2] * 10 + time_In[3];
					time_clk[2] = time_In[4] * 10 + time_In[5];
				}
				break;
			}
		}
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		if (key3 == 0)
		{
			delayms(10);
			if (key3 == 0)
			{
				EA = 1;
				break;
			}
		}
	}
}
void T0_time() interrupt 1//中断函数 此部分实现时钟的基本功能
{
	TH0 = (65536 - 45872) / 256;
	TL0 = (65536 - 45872) % 256;
	num++;
	if (num == 20)//循环20次为一秒
	{
		num = 0;
		time[2]++;//秒加一
		if (time[2] == 60)//秒到60进位
		{
			time[2] = 0;//秒清零分钟加一
			time[1]++;
			if (time[1] == 60)//分钟到60进位
			{
				time[1] = 0;//分钟清零小时加一
				time[0]++;
				soundTime();//整点报时
				if (time[0] == 24)//小时满24清零
					time[0] = 0;
			}
		}
		if ((time[0] == time_clk[0]) && (time[1] == time_clk[1]) && (time[2] == time_clk[2]))//闹钟响起
		{
			buff = 0;/*P1=0;*/
		}
	}
}
void soundTime()//蜂鸣响一次
{
	buff = 0;
	delayms(500);
	buff = 1;
}
void dsreset()//复位函数(温度传感器)初始化
{
	uint k;
	DS = 0;
	k = 103;
	while (k > 0) k--;
	DS = 1;
	k = 4;
	while (k > 0) k--;
}
bit tempreadbit(void) //读一位数据函数
{
	uint k;
	bit dat;
	DS = 0;
	k++;
	DS = 1;
	k++;//k++起延时作用
	dat = DS;
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
			DS = 0;
			k++; k++;
			DS = 1;
			k = 8; while (k > 0)k--;
		}
		else//写0
		{
			DS = 0;
			k = 8; while (k > 0)k--;
			DS = 1;
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
	temp_t = b;
	temp_t <<= 8;//两个字节组合为一个字
	temp_t = temp_t | a;
	f_temp = temp_t * 0.0625;// 温度在寄存器中为12位，分辨率为0.0625度
	temp_t = f_temp * 10 + 0.5;// 乘以10表示小数点后面只取1位，加0.5是四舍五入
	f_temp = f_temp + 0.05;
	return temp_t;// temp_t是整型
}
void display_t(char num, uchar dat)
{
	uchar k; 
	DU = 0;
	P0 = table[dat];
	DU = 1;
	DU = 0;
	WE = 0;
	k = 0XFF; 
	k = k & (~((0X01) << (num)));
	P0 = k;
	WE = 1;
	WE = 0;
	delayms(1);
}
void dis_temp(uint t)
{
	uchar k; 
	k = t / 100;//温度数值的十位
	display_t(0, k);
	k = t % 100 / 10;//温度显示的个位
	display_t(1, k + 10);
	k = t % 100 % 10;//温度显示的小数点后一位
	display_t(2, k);
}
void warn(uint s, uchar led)//蜂鸣器报警，灯闪烁
{
	uchar k; k = s;//S控制音调，LED 控制灯
	buff = 0;
	P1 = ~(led);//控制相应的灯亮
	while (k--);
	{
		dis_temp(get_temp());//温度 函数起延时作用
	}
	buff = 1;///蜂鸣器不响
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
void comm(char* parr)//串口 数据发送
{
	do
	{
		SBUF = *parr++;//发送数据
		while (!TI);//等待 发送完成标志为1
		TI = 0;//标志清零
	} while (*parr);//保持循环直到字符为'\0’
}

