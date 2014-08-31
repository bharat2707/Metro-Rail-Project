#include<reg51.h>
sbit col1=P1^0;
sbit col2=P1^1;
sbit col3=P1^2;
sbit row1=P1^3;
sbit row2=P1^4;
sbit row3=P1^5;
sbit row4=P1^6;
sfr ldata1=0xb0;
sbit rs=P1^7;
sbit en=P2^7;
sfr dacvalue1=0x80;
sfr dacvalue2=0xa0;
unsigned char cnt='*';
unsigned char value[2]={0,0};
unsigned char order=0;
unsigned int l=0;
unsigned int j=0;
unsigned char R0;
unsigned char col;
unsigned char row;
void col43();
void row43();
void lcdinput();
void delay(unsigned int itime);
void keypadinput();
void sert(unsigned char x);
void lcdinit();
void lcdcmd(unsigned char value1);
void lcddata(unsigned char value1);
void keypadpressed();
void sertx(unsigned char x);
void tempdisp(unsigned char value1);
void valuepressed(unsigned char temp);
void searchorder();
void dacvalue();
void befdec();
void aftdec();
unsigned char keypad[4][3]={'1','2','3',
                            '4','5','6',
							'7','8','9',
							'*','0','#'};
unsigned char tempe[10][2]={0,0x10,
                            0,0x20,
							0,0x50,
							0x00,0x10,
							0x00,0x20,
							0x00,0x50,
							0x00,0x80,
							0x00,0x10,
							0x00,0x11,
							0x00,0x12};
unsigned char dacno[10][2]={1,4,
							2,11,
							5,46,
							10,124,
							20,213,
							52,217,
							85,47,
							105,166,
							115,129,
							125,6};
unsigned char befdeci[10]={0,
						   0,
						   2,
						   4,
						   8,
						   20,
						   33,
						   41,
						   45,
						   48};
unsigned char aftdeci[10][2]={1,141,
							  3,30,
							  0,23,
							  0,96,
							  0,138,
							  2,132,
							  1,19,
							  1,22,
							  0,119,
							  3,70};


void main()
{ while(cnt=='*')
  {	 cnt=0;
  lcdinput();
  keypadinput();
  delay(100);
  lcdinit();
  delay(50);
  if(cnt<=4)
  {
  lcdcmd(0x87);
  for(l=0;l<cnt;l++)
  { 
    keypadpressed();
	delay(100);
  }
  lcddata('^');
  delay(100);
  lcddata('C');
  searchorder();
  dacvalue();
  befdec();
  aftdec();
  }
  keypadinput();
  }
}

void lcdinput()
{ delay(100);
  lcdcmd(0x38);
  lcdcmd(0x0e);
  lcdcmd(0x01);
  lcdcmd(0x06);
  lcdcmd(0x80);
  delay(100);
  lcddata('N');
  lcddata('o');
  lcddata('.');
  delay(100);
  lcddata(' ');
  lcddata('o');
  lcddata('f');
  delay(100);
  lcddata(' ');
  lcddata('D');
  lcddata('i');
  lcddata('g');
  delay(100);
  lcddata('i');
  lcddata('t');
  lcddata('s');
  delay(100);
  lcddata(' ');
  lcddata('i');
  lcddata('n');
  delay(100);
  lcdcmd(0xc0);
  delay(100);
  lcddata(' ');
  lcddata('t');
  lcddata('e');
  delay(100);
  lcddata('m');
  lcddata('p');
  lcddata('.');
  delay(100);
  lcddata(' ');
  lcddata('I');
  lcddata('/');
  lcddata('P');
  delay(100);
}

void lcdcmd(unsigned char value1)
{ ldata1=value1;
  rs=0;
  en=1;
  delay(1);
  en=0;
  return;
}

void lcddata(unsigned char value1)
{ ldata1=value1;
  rs=1;
  en=1;
  delay(1);
  en=0;
  return;
}

void delay(unsigned int itime)
{ unsigned int i,j;
  for(i=0;i<itime;i++)
  for(j=0;j<1275;j++);
}

void col43()
{ col=0x00|col1;
  col=col<<1;
  col=col|col2;
  col=col<<1;
  col=col|col3;
}

void row43()
{ row=0x00|row1;
  row=row<<1;
  row=row|row2;
  row=row<<1;
  row=row|row3;
  row=row<<1;
  row=row|row4;
}

void keypadinput()
{ unsigned char colloc,rowloc;
  col1=1;
  col2=1;
  col3=1;
  col43();
  while(!cnt)
   	{
	do
	  {
	  row1=row2=row3=row4=0;
	  row43();
	  col43();
	  colloc=col;
	  colloc&=0X07;
	  }while(colloc!=0X07);
	do
	 {
	  do
	    {
		delay(20);
		col43();
		colloc=col;
		colloc&=0X07;
		}while(colloc==0X07);
	delay(20);
	col43();
	colloc=col;
	colloc&=0X07;
	}while(colloc==0X07);
		while(1)
		{
		  row1=row2=row3=1; row4=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=3;
			  break;
            }
          row1=row2=row4=1; row3=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=2;
			  break;
			}
		  row1=row3=row4=1; row2=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=1;
			  break;
			}
		  row3=row2=row4=1; row1=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0x07)
		  {
		      rowloc=0;
		      break;
		  }
		}
		if(colloc==0X03)
		  sert(keypad[rowloc][0]);
		else if(colloc==0X05)
		  sert(keypad[rowloc][1]);
		else
		   sert(keypad[rowloc][2]);
		
		  
	}
	
}

void sert(unsigned char x)
	   { 
	     cnt=x;
		 cnt=cnt&0x0f;
	   }

void lcdinit()
{ delay(100);
  lcdcmd(0x38);
  lcdcmd(0x0e);
  lcdcmd(0x01);
  lcdcmd(0x06);
  lcdcmd(0x82);
  delay(100);
  lcddata('T');
  lcddata('E');
  lcddata('M');
  lcddata('P');
  lcddata(':');
  delay(100);
  lcdcmd(0xc2);
  delay(100);
  lcddata('V');
  lcddata('O');
  lcddata('L');
  lcddata('T');
  lcddata(':');
  delay(100);
}

void keypadpressed()
{ unsigned char colloc,rowloc,k=0;
  col1=1;
  col2=1;
  col3=1;
  col43();
  while(k==0)
   	{
	do
	  {
	  row1=row2=row3=row4=0;
	  row43();
	  col43();
	  colloc=col;
	  colloc&=0X07;
	  }while(colloc!=0X07);
	do
	 {
	  do
	    {
		delay(20);
		col43();
		colloc=col;
		colloc&=0X07;
		}while(colloc==0X07);
	delay(20);
	col43();
	colloc=col;
	colloc&=0X07;
	}while(colloc==0X07);
		while(1)
		{
		  row1=row2=row3=1; row4=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=3;
			  break;
            }
          row1=row2=row4=1; row3=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=2;
			  break;
			}
		  row1=row3=row4=1; row2=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0X07)
		    {
			  rowloc=1;
			  break;
			}
		  row3=1;
		  row2=1;
		  row4=1; 
		  row1=0;
		  row43();
		  col43();
		  colloc=col;
		  colloc&=0X07;
		  if(colloc!=0x07)
		  {
		      rowloc=0;
		      break;
		  }
		}
		if(colloc==0X03)
		  sertx(keypad[rowloc][0]);
		else if(colloc==0X05)
		  sertx(keypad[rowloc][1]);
		else
		   sertx(keypad[rowloc][2]);
		
	k++;	  
	}
}

void sertx(unsigned char x)
	   {
	     R0=x;
		 tempdisp(R0);
		 valuepressed(R0);
	   }

void tempdisp(unsigned char value1)
{ 
  delay(50);
  value1=(value1|0X30);
  lcddata(value1);
}

void valuepressed(unsigned char temp)
{ temp=temp&0x0f;
  if(cnt==1)
  { 
    value[0]=temp;
	value[1]=0;
  }
  if(cnt==2)
  { 
    if(l==0)
	{value[0]=temp;
	 value[0]=value[0]<<4;
	}
	if(l==1)
	{value[0]=value[0]|temp;
	 value[1]=0;
	}
  }
  if(cnt==3)
  {
    if(l==0)
	{value[0]=temp;
	 value[0]=value[0]<<4;
	}
	if(l==1)
	{value[0]=value[0]|temp;
	}
	if(l==2)
	{value[1]=temp;
	}
  }
  if(cnt==4)
  {
    if(l==0)
	{value[0]=temp;
	 value[0]=value[0]<<4;
	}
	if(l==1)
	{value[0]=value[0]|temp;
	}
	if(l==2)
	{value[1]=temp;
	 value[1]=value[1]<<4;
	}
	if(l==3)
	{value[1]=value[1]|temp;
	}
  }
}

void searchorder()
{ 
  for(j=0;j<10;j++)
  { 
    if((value[0]==tempe[j][1])&&(value[1]==tempe[j][0]))
	{  
	  order=j;
	  break;
	}
  }
}

void dacvalue()
{
   dacvalue1=dacno[order][1];
   dacvalue2=dacno[order][0];
}

void befdec()
{ unsigned char temp,value1;
  value1=befdeci[j];
  lcdcmd(0xc7);
  delay(50);
  if(value1>=10)
  { temp=value1/10;
    value1=value1-(temp*10);
	temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
  if(value1>=0)
  { temp=value1;
    temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
}

void aftdec()
{ unsigned char temp,value1[2];
  value1[0]=aftdeci[order][1];
  value1[1]=aftdeci[order][0];  
  lcdcmd(0xc9);
  delay(50);
  lcddata('.');
  if(value1[0]>=10)
  { temp=value1[0]/10;
    value1[0]=value1[0]-(temp*10);
	temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
  if(value1[0]>=0)
  { temp=value1[0];
    temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
  if(value1[1]>=10)
  { temp=value1[1]/10;
    value1[1]=value1[1]-(temp*10);
	temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
  if(value1[1]>=0)
  { temp=value1[1];
    temp=temp|0x30;
	lcddata(temp);
	delay(50);
  }
  lcddata('m');
  lcddata('V');
}