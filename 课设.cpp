/*��������˵����
������̣�
��1����10�������ֱ��Ӧ����0-9��
����������
Key1�̰��л�ģʽ��
Key2���������ʱ�Ӻ����ӵ����ã�
Key3�̰�ȷ������ʱ�䣬�������㣻
Key4������ֹͣ����*/
#include <reg52.h> 
#include <stdio.h> 
#include <intrins.h> 
#define uchar unsigned char 
#define uint unsigned int 
sbit DS = P2 ^ 2;   //DS18B20������
sbit key1 = P3 ^ 4;//����
sbit key2 = P3 ^ 5;
sbit key3 = P3 ^ 6;
sbit key4 = P3 ^ 7;
sbit buff = P2 ^ 3;//������
sbit DU = P2 ^ 6;//��ѡ
sbit WE = P2 ^ 7;//λѡ
sbit led0 = P1 ^ 0;/*ָʾ�����ڱ�������*/
sbit led1 = P1 ^ 1;
sbit led2 = P1 ^ 2;
sbit led3 = P1 ^ 3;
uint warn_11 = 270;//�¶�ֵ����10�Ľ��
uint warn_12 = 250;
uint warn_h1 = 300;
uint warn_h2 = 320;
uchar bitdata[] = { 0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f };//�����1-8
uchar segdata[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40 };//��ѡ0-9�Լ�-
uchar segdata_dp[] = { 0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef };//��С��������ѡ0-9
uchar table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,//���� �������0��9���벻��С����
0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef };//���� �������0��9���벻��С����
uchar dis_arr[] = { 10,10,10,10,10,10 };//ʱ����ʾ���� Ĭ��Ϊ-
uchar time[] = { 0,0,0 };//ʱ�� ʱ����
uchar time_In[] = { 0,0,0,0,0,0 };
uchar time_clk[] = { 0,0,0 };//���� ʱ����
uchar t = 0;
uchar num = 0;
uchar mode = 0;
uchar keydown = 0;
uchar keyIn, keyvalue, i, temp;//������̶���
uint temp_t;
float f_temp;
void key();
void init();
uchar keyscan();//�������ɨ�躯��
void delayms(uint x);//��ʱ����
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
		if (mode == 0)//ʱ��
		{
			display(time[0] / 10, time[0] % 10, time[1] / 10, time[1] % 10, time[2] / 10, time[2] % 10);
		}
		else if (mode == 1)//����
		{
			display(time_clk[0] / 10, time_clk[0] % 10, time_clk[1] / 10, time_clk[1] % 10, time_clk[2] / 10, time_clk[2] % 10);
		}	
		else if (mode == 2)//�¶�
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
	TMOD = 0x20;//���ڳ�ʼ������ T1�����ڷ�ʽ2
	PCON = 0x00;
	SCON = 0x50;
	TH1 = 0xfd;//������9600
	TL1 = 0xfd;
	TR1 = 1;
}
void init()//��ʼ������
{
	P3 = 0xff;//���ߵ�ƽ
	TMOD = 0x01;//��ʱ��������ʽѡ��1 T0�����ڷ�ʽ1
	TH0 = (65536 - 45872) / 256;
	TL0 = (65536 - 45872) % 256;
	EA = 1; //�����ж�
	ET0 = 1;//����ʱ��0�ж�
	TR0 = 1;//��ʼ����
	//P1=1;
}
void delayms(uint x)//��ʱ����
{
	uint i, j;
	for (i = x; i > 0; i--)
		for (j = 110; j > 0; j--);
}
void key()/*ģʽ�л�����*/
{
	if (key1 == 0)
	{
		delayms(200);
		if (key1 == 0)//��ѹʱ�������κβ���
		{
			delayms(1);
		}
		else if (key1 == 1)//�ɿ����л�ģʽ
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
uchar keyscan()//�������ɨ�躯��
{
	keyvalue = 99;
	P3 = 0xfe;
	temp = P3;
	temp = temp & 0xf0;//�ж��Ƿ񻹵���0xf0
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
	temp = temp & 0xf0;//�ж��Ƿ񻹵���0xf0
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
	temp = temp & 0xf0;//�ж��Ƿ񻹵���0xf0
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
	temp = temp & 0xf0;//�ж��Ƿ񻹵���0xf0
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

void display_1(uchar wei, uchar duan)/*���ڿ����������ʾ��*/
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
void display_2(uchar wei, uchar duan)/*ͬ�� ��ѡ��С����*/
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
void input()/*���� input()�������������ǽ����û������ּ��������ʱ�����ݣ����洢������time_In[]��*/
{
	for (i = 0; i < 8; i++)//����Ϊ-�����´�ʹ��
	{
		dis_arr[i] = 10;
	}
	while (1)
	{
		display(dis_arr[0], dis_arr[1], dis_arr[2], dis_arr[3], dis_arr[4], dis_arr[5]);
		keyIn = keyscan();
		if (keydown == 1)//��⵽����������
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
void T0_time() interrupt 1//�жϺ��� �˲���ʵ��ʱ�ӵĻ�������
{
	TH0 = (65536 - 45872) / 256;
	TL0 = (65536 - 45872) % 256;
	num++;
	if (num == 20)//ѭ��20��Ϊһ��
	{
		num = 0;
		time[2]++;//���һ
		if (time[2] == 60)//�뵽60��λ
		{
			time[2] = 0;//��������Ӽ�һ
			time[1]++;
			if (time[1] == 60)//���ӵ�60��λ
			{
				time[1] = 0;//��������Сʱ��һ
				time[0]++;
				soundTime();//���㱨ʱ
				if (time[0] == 24)//Сʱ��24����
					time[0] = 0;
			}
		}
		if ((time[0] == time_clk[0]) && (time[1] == time_clk[1]) && (time[2] == time_clk[2]))//��������
		{
			buff = 0;/*P1=0;*/
		}
	}
}
void soundTime()//������һ��
{
	buff = 0;
	delayms(500);
	buff = 1;
}
void dsreset()//��λ����(�¶ȴ�����)��ʼ��
{
	uint k;
	DS = 0;
	k = 103;
	while (k > 0) k--;
	DS = 1;
	k = 4;
	while (k > 0) k--;
}
bit tempreadbit(void) //��һλ���ݺ���
{
	uint k;
	bit dat;
	DS = 0;
	k++;
	DS = 1;
	k++;//k++����ʱ����
	dat = DS;
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
			DS = 0;
			k++; k++;
			DS = 1;
			k = 8; while (k > 0)k--;
		}
		else//д0
		{
			DS = 0;
			k = 8; while (k > 0)k--;
			DS = 1;
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
	temp_t = b;
	temp_t <<= 8;//�����ֽ����Ϊһ����
	temp_t = temp_t | a;
	f_temp = temp_t * 0.0625;// �¶��ڼĴ�����Ϊ12λ���ֱ���Ϊ0.0625��
	temp_t = f_temp * 10 + 0.5;// ����10��ʾС�������ֻȡ1λ����0.5����������
	f_temp = f_temp + 0.05;
	return temp_t;// temp_t������
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
	k = t / 100;//�¶���ֵ��ʮλ
	display_t(0, k);
	k = t % 100 / 10;//�¶���ʾ�ĸ�λ
	display_t(1, k + 10);
	k = t % 100 % 10;//�¶���ʾ��С�����һλ
	display_t(2, k);
}
void warn(uint s, uchar led)//����������������˸
{
	uchar k; k = s;//S����������LED ���Ƶ�
	buff = 0;
	P1 = ~(led);//������Ӧ�ĵ���
	while (k--);
	{
		dis_temp(get_temp());//�¶� ��������ʱ����
	}
	buff = 1;///����������
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
void comm(char* parr)//���� ���ݷ���
{
	do
	{
		SBUF = *parr++;//��������
		while (!TI);//�ȴ� ������ɱ�־Ϊ1
		TI = 0;//��־����
	} while (*parr);//����ѭ��ֱ���ַ�Ϊ'\0��
}

