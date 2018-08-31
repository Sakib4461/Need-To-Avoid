
# include "iGraphics.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/* 
	function iDraw() is called again and again by the system.
*/
void collision();
void gameover();
void setscore();
void setname(int nameindex);
void point();
int Height=480;  //Screen Height
int Width=640;   //Screen Width
int Car_Speed=3; //Car speed for enemy car
int Car_Speed2=7;//car speed for player's car
int CarX=52;
int CarY=0;
int ScarX=rand() %402+52; //X cordinate for Standing car using random function , car will come from 52 pix to 454 pix
int ScarY=600; //Y cordinate for Standing car
int EcarX=rand() %155+52; //X cordinate for police car 1(Right) using random function , car will come from 52 pix to 207 pix
int EcarY=600; //Y cordinate for police car
int Ecar2X=rand() %75+277; //X cordinate for police car 2(left) using random function , car will come from 277 pix to 352 pix
int Ecar2Y=600; //Y cordinate for police car2
int score; //Score variable 
bool carLeft=false;
bool carRight=false;
int choice=0; // choice will control start ,highscore, credit , help page 
int life=3;  //control player's life
int HScore[5];  //for setting player's score in file 
int readscr[5];  //for taking data from file
char readnamep[5][40];  //for taking name from file 
char readname2[5][40];  //for seeting new name in file 
int timer1;  // timer for left police car
int timer2;  // timer for right police car
int timer3;  // timer for oil decrement after 1 sec
int timer4;  // timer for level up after 1 min 
int timer5;  // timer for new oil after 1 min
int timer6;  // timer for standing police car after every 15 sec
int timer7;  // timer for oil coming from top of the screen 
int level=1;  // variable for level 
int newflag=0;
int on=0;
int petrol=100; //variable for pretrol showing in screen 
int oilX=rand() %402+52;  //X cordinate for new oil image using random function , car will come from 52 pix to 454 pix
int oilY=600;  //Y cordinate for new oil image
char strinput[100], strstore[100];  // for taking name input
int len;  // using in taking name input
int mode;  // using in taking new input
int flag2=0;  //using for checking the game is staring new
bool oilbool=false;  // boolean variable that control new oil come 
bool scar=false;  // booleab variable that control new standing car come
int index=0;
int tempvalue=0;
int value=score*10;




//usnig for drawing text input box
void drawTextBox()
{
	iSetColor(150, 150, 150);
	iRectangle(50, 250, 250, 30);
}

// usning for police car (left)
void Ecar()
{
	
	EcarY-=Car_Speed;

	if(EcarY<=0)
	{
		EcarY=600;
		EcarX=rand() %155+52;
		score++;
	}
	
}


// usning for police car (Right)
void Ecar2()
{
	
	Ecar2Y-=Car_Speed+1;

	if(Ecar2Y<=0)
	{
		Ecar2Y=600;
		Ecar2X=rand() %75+277;
		score++;

	}
	if(scar)
	{
	ScarY-=Car_Speed;
	if(ScarY<=0)
	{
		ScarY=600;
		score=score+2;
		scar=false;
	}
	}

}


// usning for oil decrement 
void oil()
{
	petrol--;
	
	
}

// usning for new oil come
void oilcome()
{
	if(oilbool)
	{
		oilY--;
		 while(oilY<=60)
	 {
		 oilY=60;
		 oilbool=false;
	 }
		 
	}
}
void newoil()
{ 
	 oilX=rand() %402+52;
	 oilY=600;
	 oilbool=true;
    
	

}


// usning for showing credit page
void Credit()
{
	iShowBMP(0,0,"creditcar.bmp");
}

// usning for showing help page
void Help()
{
	iShowBMP(0,0,"help detail.bmp");
}

// usning for showing mainmenu page
void mainmenu()
{
	
	iShowBMP(0, 0, "menu.bmp");
	iShowBMP2(20,174,"Start.bmp",0);
    iShowBMP2(20,138,"high score.bmp",0);
	iShowBMP2(20,105,"Credit.bmp",0);
	iShowBMP2(20,67,"Help.bmp",0);
	iShowBMP2(20,30,"exit.bmp",0);
	

}

// usning for  level up
void levelup()
{
	level++;
	Car_Speed+=2;
}

// usning for game over checking 
void gameover()
{
	if(life<=0||petrol<=0||level>=4||choice==1)
	{
		iPauseTimer(timer1);
		iPauseTimer(timer2);
		iPauseTimer(timer3);
		iPauseTimer(timer4);
		iPauseTimer(timer5);
		iPauseTimer(timer6);
		iPauseTimer(timer7);
		value=score*10;
		
	    choice=6;
	
	}
}

// usning for showing gameover page
void gameover2()
{
	if(choice==6)
	{
	flag2=1;
	
	if(level>=4)
	{
	iShowBMP(0,0,"gameover.bmp");
	char strshow[40],strshow2[40];
	sprintf_s(strshow,40,"%s Your Score is:%d",strstore,score*10);
	sprintf_s(strshow2,40,"Congratulations Rob is now home");
	iSetColor(255, 255, 255);
	iText(220,100 , strshow2, GLUT_BITMAP_HELVETICA_18);
	iText(220,80 , strshow, GLUT_BITMAP_HELVETICA_18);
	}
	else
	{
	iShowBMP(0,0,"gameover.bmp");
	char strshow[40],strshow2[40];
	sprintf_s(strshow,40,"%s Your Score is:%d",strstore,score*10);
	iSetColor(255, 255, 255);
	iText(220,100 , strshow, GLUT_BITMAP_HELVETICA_18);
	}
	
	setscore();  // calling set score function
	
	}
}

// using for collision 
void collision(){
		
			if (EcarX >= CarX && EcarX <= CarX + 60 || EcarX + 60 >= CarX && EcarX + 60 <= CarX + 60)
			{
				if ( EcarY >= CarY && EcarY <= CarY + 100 || EcarY + 100 >= CarY && EcarY + 100 <= CarY + 100) {
					
					
					life--;
					EcarY=600;
		            EcarX=rand() %155+52;
					gameover();
					
				}
			}
		
		if (Ecar2X >= CarX && Ecar2X <= CarX + 60 || Ecar2X + 60 >= CarX && Ecar2X + 60 <= CarX + 60)
		{
			if (Ecar2Y >= CarY && Ecar2Y <= CarY + 100 || Ecar2Y + 100 >= CarY && Ecar2Y + 100 <= CarY + 100) {
				
				life--;
				Ecar2Y=600;
		        Ecar2X=rand() %75+277;
				gameover();
				
			}
		}
		if (ScarX >= CarX && ScarX <= CarX + 60 || ScarX + 100 >= CarX && ScarX + 100 <= CarX + 60||ScarX  <= CarX && ScarX + 100 >= CarX + 60)
		{
			if (ScarY >= CarY && ScarY <= CarY + 100 || ScarY + 60 >= CarY && ScarY + 60 <= CarY + 100) {
				
				life--;
				ScarY=600;
		        scar=false;
				score=score-2;
				gameover();
				
			}
		}
		if (oilX >= CarX && oilX <= CarX + 60 || oilX + 20 >= CarX && oilX + 20 <= CarX + 60)
		{
			if (oilY >= CarY && oilY <= CarY + 100 || oilY + 20 >= CarY && oilY + 20 <= CarY + 100) {
				
				petrol=100;
				oilY=-100;
				oilbool=false;
				
			}
		}
		
		}
		
		
// usning for starting new game		
void Start()
{
	    
	 if(flag2==1)  
	 {  iResumeTimer(timer1);
		iResumeTimer(timer2);
		iResumeTimer(timer3);
		iResumeTimer(timer4);
		iResumeTimer(timer5);
		life=3;
		score=0;
	    level=1;
        petrol=100;
	    Car_Speed=3;
	    Car_Speed2=5;
	    flag2=0;
	 }


     Width=445;
	 iShowBMP(0,0,"road.bmp");
     iShowBMP2(CarX,CarY,"car.bmp",0);
	 iShowBMP(oilX,oilY,"oil.bmp");
	
	if(CarX<=52)
	{
		CarX=52;
	}
	if(CarX>Width)
	{
		CarX=Width-60;
	}
	
	iShowBMP2(EcarX,EcarY,"police.bmp",0);
	
	iShowBMP2(Ecar2X,Ecar2Y,"police.bmp",0);
	iShowBMP2(ScarX,ScarY,"police standing.bmp",0);
	
	

	
	char strscore[40],strlife[40],strlevel[40],strpetrol[40];
	sprintf(strscore,"Score:%d",score*10);
	iSetColor(255, 255, 255);
	iText(510,460 , strscore, GLUT_BITMAP_HELVETICA_18);
	sprintf(strlife,"life:%d",life);
	iSetColor(255, 255, 255);
	iText(510,420 , strlife, GLUT_BITMAP_HELVETICA_18);
	sprintf(strlevel,"Level:%d",level);
	iSetColor(255, 255, 255);
	iText(510,380 , strlevel, GLUT_BITMAP_HELVETICA_18);
	sprintf(strpetrol,"petrol:%d",petrol);
	iSetColor(255, 255, 255);
	iText(510,340 , strpetrol, GLUT_BITMAP_HELVETICA_18);
	
	
	
	

	collision();  //calling collision 
}

// usning for seeting new highscore
void setscore()
{
    int i, count=0,count1=0,flag=0;
    FILE *fread,*freadname;
	
    
    fread= (fopen("Newscore.txt", "r"));
    for(i=0;i<5;i++)
    {
       fscanf(fread,"%d",&HScore[i]);

    }
    fclose(fread);
	
	
    for(i=0;i<5;i++)
    {
		
        if(HScore[i]<value)
        {
		index=i;
		setname(index);  // calling setname function for setting newname 
		tempvalue=value;
		value=0;
		break;
		}
	}
	       
            int temp=0;
            for(index;index<5;index++)
            { 
			   temp=HScore[index];
		       HScore[index]=tempvalue;
               tempvalue=temp;
			   printf("index=%d",index);
			  
			}
			
			       
	FILE *fwrite;
    fwrite= (fopen("Newscore.txt", "w"));
    for(i=0;i<5;i++)
    {
        fprintf(fwrite,"%d ",HScore[i]);
    }
    fclose(fwrite);
	 

    
}

// usning for setting new name 
void setname(int nameindex)
{
	
	FILE*freadname;
	int i=0;

	freadname= (fopen("Name.txt", "r"));
    for(i=0;i<5;i++)
    {
       fscanf(freadname,"%s ",&readname2[i]);

    }
    fclose(freadname);
	
	char strtemp[100];
			 for(nameindex;nameindex<5;nameindex++)
            { 
			   strcpy(strtemp,readname2[nameindex]);
			   strcpy(readname2[nameindex],strstore);
		       strcpy(strstore,strtemp);
			   printf("index2=%d",index);
              }
	
	FILE *fwrite2;
    fwrite2= (fopen("Name.txt", "w"));
    for(i=0;i<5;i++)
    {
        fprintf(fwrite2,"%s ",readname2[i]);
    }
    fclose(fwrite2);
}

// usning for showing highscore page
void highscore(){
		iShowBMP(0,0,"highscore.bmp");
		FILE *readscore,*readname;
		
		int i,j=10,d=0;
		readscore = fopen("Newscore.txt", "r");
	    for(i=0;i<5;i++)
		{
		
		fscanf(readscore, "%d ", &readscr[i]);
		
		}
		readname = fopen("Name.txt", "r");
	    for(i=0;i<5;i++)
		{
		
		fscanf(readname, "%s ", &readnamep[i]);
		
		
		}
		fclose(readscore);
		fclose(readname);
		char sv1[40],sv2[40],sv3[40],sv4[40],sv5[40];
		sprintf(sv1, "%s:%d \n",readnamep[0], readscr[0]);
		sprintf(sv2, "%s:%d \n",readnamep[1], readscr[1]);
		sprintf(sv3, "%s:%d \n",readnamep[2], readscr[2]);
		sprintf(sv4, "%s:%d \n",readnamep[3], readscr[3]);
		sprintf(sv5, "%s:%d \n",readnamep[4], readscr[4]);
		
	   iSetColor(0,0, 255);
	   iText(330, (Height/2), sv5, GLUT_BITMAP_HELVETICA_18);
	   iSetColor(255,255, 255);
	   iText(330, (Height/2)+20, sv4, GLUT_BITMAP_HELVETICA_18);
	   iSetColor(0,0, 255);
	   iText(330, (Height/2)+40, sv3, GLUT_BITMAP_HELVETICA_18);
	   iSetColor(255,255, 255);
	   iText(330, (Height/2)+60, sv2, GLUT_BITMAP_HELVETICA_18);
	   iSetColor(0,0, 255);
	   iText(330, (Height/2)+80, sv1, GLUT_BITMAP_HELVETICA_18);
		}	




void iDraw()
{
	//place your drawing codes here	
	iClear();
	if(choice==0)
	{
	drawTextBox();   //drawing text box
	if(mode == 1)
	{
		iSetColor(255, 255, 255);
		iText(55, 260, strinput);
	}
	iText(10, 10, "Please Enter Your name...");
	}
	if(choice==1)
	{   on=1;
		mainmenu();
	}
	if(choice==2)
	{   on=2;
		Start();
		
	}
	if(choice==3)
	{
		highscore();
	}
	if(choice==4)
	{
		Credit();
	}
	if(choice==5)
	{
		Help();
	}
	if(choice==6)
	{
		gameover2();
	}
	


	
}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(choice==0)
		{
			 if(mx >= 50 && mx <= 300 && my >= 250 && my <= 280 && mode == 0)
		{
			mode = 1;
		}
		}
		if (choice == 1){ 
			if (mx >= 20 && mx <= 96 && my >= 174 && my <= 200)
				choice = 2;
			else if (mx >= 20 && mx <= 135 && my >= 139 && my <= 173)
				choice = 3;
			else if (mx >= 20 && mx <= 97 && my >= 105 && my <= 138)
				choice = 4;
			else if (mx >= 20 && mx <= 87 && my >= 67 && my <= 104)
				choice = 5;
	        else if (mx >= 20 && mx <= 82 && my >= 30 && my <= 66)
				exit(0);
		
		}
		
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}
/*iPassiveMouseMove is called to detect and use 
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here
	
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/
 
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == 'm')
	{
		choice =1;  // for going main menu 
	}
	int i;

	// for taking input 
	if(mode == 1)
	{
		if(key == '\r')
		{
			choice=1;
			mode = 0;
			strcpy(strstore, strinput);
			printf("%s\n", strstore);
			for(i = 0; i < len; i++)
				strinput[i] = 0;
			len = 0;
		}
		else
		{
			strinput[len] = key;
			len++;
		}
	}
	
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_RIGHT)
	{
		carRight=true;
		
	    CarX+=Car_Speed2;
	   if(CarX==140)
	   {
			CarX-=Car_Speed2;
	   }
		
	}

	if(key == GLUT_KEY_LEFT)
	{
		carLeft=true;
		
		CarX-=Car_Speed2;
        if(CarX==0)
	{
		carLeft=false;
	}
	}


	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	//place your codes for other keys here
}
int main()
{
	//PlaySound("music\\mp3.wav", NULL, SND_LOOP | SND_ASYNC);
	timer1=iSetTimer(10,Ecar);
	timer2=iSetTimer(10,Ecar2);
	timer3=iSetTimer(1000,oil);
	timer4=iSetTimer(60000,levelup);
	timer5=iSetTimer(60000,newoil);
	timer7=iSetTimer(10,oilcome);
	
	
	
	//place your own initialization codes here. 
	iInitialize(Width, Height, "Need To Avoid");
	return 0;
}	