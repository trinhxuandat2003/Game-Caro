#include<iostream>
#include"console.h"
#include <cstdlib>
#include <string>
#include <cmath>
#include <conio.h>
using namespace std;
struct moto
{
 char kytu;
 int mau;
};
moto buffer[25][77];
void gano(int x,int y,char c,int mamau=13)
{
 buffer[y][x].kytu=c;
 buffer[y][x].mau=mamau;
}
void khoi_tao_buffer()
{
 for(int i=0;i<25;i++)
  for(int j=0;j<77;j++)
   gano(j,i,' ');
}
void ve_ban_co()
{
 for(int i=0;i<25;i++)
 {
  if(i%2==0)
  {
   for(int j=0;j<77;j++)
    if(j%4==0) gano(j,i,197);
    else gano(j,i,196);
  }
  else
  {
   for(int j=0;j<77;j++)
    if(j%4==0) gano(j,i,179);
  }
 }
}
char ban_co[12][19];
void khoi_tao_ban_co()
{
 for(int i=0;i<12;i++)
  for(int j=0;j<19;j++)
   ban_co[i][j]=' ';
}
void hien_thi(int x,int y)
{
 //reset buffer
 khoi_tao_buffer();
 //ve ban co len buffer
 ve_ban_co();
 //in cac quan co cua ban co len buffer
 for(int i=0;i<12;i++)
  for(int j=0;j<19;j++)
   gano(2+j*4,1+i*2,ban_co[i][j]);
 //in con tro len buffer
 gano(x-1,y,buffer[y][x-1].kytu,176);
 gano(x,y,buffer[y][x].kytu,176);
 gano(x+1,y,buffer[y][x+1].kytu,176);
 //in buffer ra console
 gotoXY(0,0);
 for(int i=0;i<25;i++)
 {
  for(int j=0;j<77;j++)
  {
   TextColor(buffer[i][j].mau);
   putchar(buffer[i][j].kytu);
  }
  if(i<24) putchar('\n');
 }
}
int dieu_khien(int &x,int &y,int &nguoi)
{
 int key=inputKey();
 if(key==key_Up && y>=3){ y-=2;return 1;}
 else if(key==key_Down && y<=21){ y+=2;return 1;}
 else if(key==key_Left && x>=6){ x-=4;return 1;}
 else if(key==key_Right&& x<=70){ x+=4;return 1;}
 else if(key==13)
 {
  if(nguoi==1 && ban_co[(y-1)/2][(x-2)/4]==' ')
  {
   ban_co[(y-1)/2][(x-2)/4]='X';
   nguoi=0;
   return 1;
  }
  else if(ban_co[(y-1)/2][(x-2)/4]==' ')
  {
   ban_co[(y-1)/2][(x-2)/4]='O';
   nguoi=1;
   return 1;
  }
  return 0;
 }
 return 0;
}
int xet_thang_thua(int x ,int y)
{
 int dem,i,j,h,c;
 c=(x-2)/4;
 h=(y-1)/2;
 if(ban_co[h][c]==' ') return 2;
 //xet hang ngang
 dem=0;
 for(j=c;j>=0;j--){
  if(ban_co[h][j]!=ban_co[h][c]) break;
  else dem++;
 }
 for(j=c+1;j<19;j++){
  if(ban_co[h][j]!=ban_co[h][c]) break;
  else dem++;
 }
 if(dem>=5)
 {
  if(ban_co[h][c]=='X') return 1;
  else return 0;
 }
 //xet hang doc
 dem=0;
 for(int i=h;i>=0;i--){
  if(ban_co[i][c]!=ban_co[h][c]) break;
  else dem++;
 }
 for(i=h+1;i<12;i++){
  if(ban_co[i][c]!=ban_co[h][c]) break;
  else dem++;
 }
 if(dem>=5)
 {
  if(ban_co[h][c]=='X') return 1;
  else return 0;
 }
 //xet duong cheo len
 dem=0;
 for(i=h,j=c;i>=0 && j<19;i--,j++){
  if(ban_co[i][j]!=ban_co[h][c]) break;
  else dem++;
 }
 for(i=h+1,j=c-1;i<12,j>=0;i++,j--){
  if(ban_co[i][j]!=ban_co[h][c]) break;
  else dem++;
 }
 if(dem>=5)
 {
  if(ban_co[h][c]=='X') return 1;
  else return 0;
 }
 //xet duong cheo xuong
 dem=0;
 for(i=h,j=c;i<120 && j<19;i++,j++){
  if(ban_co[i][j]!=ban_co[h][c]) break;
  else dem++;
 }
 for(i=h-1,j=c-1;i>=0,j>=0;i--,j--){
  if(ban_co[i][j]!=ban_co[h][c]) break;
  else dem++;
 }
 if(dem>=5){
  if(ban_co[h][c]=='X') return 1;
  else return 0;
 }
 for(i=0;i<12;i++)
  for(j=0;j<19;j++)
   if(ban_co[i][j]==' ') return 2;
 return 3;
}
//
void resizeConsole(int width, int height) //Với width là chiều rộng, heigth là chiều cao
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//
void playgame(int &thoat);
void khungplay();
void help(int &thoat);
void about(int &thoat);
int main()//ham main
{
    int k,kt,nguoi,x,y,van_moi;
    char c;
    resizeConsole(620,480);
    int thoat = 0;
    system("cls");
    if(thoat == 0){
        playgame(thoat);
    }
    loop:;
    khoi_tao_ban_co();
    van_moi=1;
    clrscr();
    nguoi=1;
    x=42;
    y=13;

 while(1)
 {
  hien_thi(x,y);
  if(van_moi){ kt=2;van_moi=0;}
  else kt=xet_thang_thua(x,y);
  if(kt==1)
  {
   gotoXY(30,7);
   TextColor(Color_Yellow);
   cout<<"NGUOI CHOI X THANG!";
   gotoXY(30,9);
   cout<<"choi lai? y:yes  n:no";
   do{c=getch();}while(c!='y' && c!='n');
   if(c=='y') goto loop;
   else goto ketthuc;
  }
  else if(kt==0)
  {
   gotoXY(30,7);
   TextColor(Color_Yellow);
   cout<<"NGUOI CHOI O THANG!";
   gotoXY(30,9);
   cout<<"choi lai? y:yes  n:no";
   do{c=getch();}while(c!='y' && c!='n');
   if(c=='y') goto loop;
   else goto ketthuc;
  }
  else if(kt==3)
  {
   gotoXY(30,7);
   TextColor(Color_Yellow);
   cout<<"VAN CO NAY HOA!";
   gotoXY(30,9);
   cout<<"choi lai? y:yes  n:no";
   do{c=getch();}while(c!='y' && c!='n');
   if(c=='y') goto loop;
   else goto ketthuc;
  }
loop1:;
  k=dieu_khien(x,y,nguoi);
  if(k==0) goto loop1;
 }
ketthuc:;
 return 0;
}
void playgame(int &thoat)
{
    khungplay();
    TextColor(14);
    TextColor(202);
    gotoXY(33, 15);
    cout<< (char) 175<< " PLAY GAME  " ;
    TextColor(14);
    gotoXY(35, 16);
    cout << "HELP";
    gotoXY(35, 17);
    cout << "ABOUT";
    //gotoXY(35, 18);
   // cout << "EXIT";
    int chon = 0;
    int toado = 15;
    do{
        char a = getch();
        if(a == 80 ||a == 's'||a=='S'||a=='2') chon = 1;
        else if(a == 72 || a == 'w'||a=='W'||a=='8') chon = 2;
        else if(a == 13 ||a =='e'||a=='e' ||a=='5') chon = 3;
        else chon = 0;
        if(chon == 1 && toado < 18) toado++;
        else if(chon == 2 && toado >15) toado--;
        if(toado == 15)
        {
            TextColor(202);
            gotoXY(33, 15);
            cout<< (char) 175<< " PLAY GAME  " ;
            TextColor(14);
            gotoXY(33, 16);
            cout << "  HELP         ";
            gotoXY(33, 17);
            cout << "  ABOUT        ";

            TextColor(0);
        }
        if(toado == 16)
        {
            TextColor(14);
            gotoXY(33, 15);
            cout<<"  PLAY GAME    ";
            TextColor(202);
            gotoXY(33, 16);
            cout<<(char) 175<<"  HELP      ";
            TextColor(14);
            gotoXY(33, 17);
            cout<<"  ABOUT        ";
            //gotoXY(33, 18);
            //cout<<"  EXIT         ";
            TextColor(0);
        }
        if(toado == 17)
        {
            TextColor(14);
            gotoXY(33, 15);
            cout<<"  PLAY GAME    ";
            gotoXY(33, 16);
            cout<<"  HELP         ";
            TextColor(202);
            gotoXY(33, 17);
            cout<<(char) 175<<" ABOUT      ";
            TextColor(14);

            TextColor(0);
        }

    }while(chon != 3);
    system("cls");
    if(toado == 16) help(thoat);
    else if(toado == 17) about(thoat);
    else if(toado == 18) {
        thoat =0;
    }
}

void khungplay()
{
    TextColor(12);
    for(int i = 0; i<78; i++)
    {
        gotoXY(1+i, 0);
        cout << (char)220;
    }
        for(int i = 0; i<78; i++)
    {
        gotoXY(1+i, 26);
        cout<< (char)205;
    }
    for(int j = 0; j<25; j++)
    {
        gotoXY(0, j+1);
        cout << (char) 186;
    }
        for(int j = 0; j<25; j++)
    {
        gotoXY(79, j+1);
        cout << (char) 186;
    }
    gotoXY(0,0);
    cout << (char) 201;
    gotoXY(0,26);
    cout << (char) 200;
    gotoXY(79,0);
    cout << (char) 187;
    gotoXY(79,26);
    cout << (char) 188;
    gotoXY(34, 0);
    TextColor(13);
    cout<<" GAME CO CARO ";
    TextColor(13);
    for(int i = 0; i<55; i++)
    {
        gotoXY(13+i, 22);
        cout << (char) 205;
    }
        for(int i = 0; i<55; i++)
    {
        gotoXY(13+i, 24);
        cout << (char) 205;
    }

    TextColor(11);
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 14);
        cout << (char) 205;
    }
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 18);
        cout << (char) 205;
    }
    TextColor(2);
}
void help(int &thoat)
{
    khungplay();
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 11);
        cout << " ";
    }
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 21);
        cout << " ";
    }
    gotoXY(33, 5);
    TextColor(12);
    cout << "DIEU KHIEN";
    TextColor(14);
    gotoXY(12,7);
    cout << "NGUOI CHOI X";
    gotoXY(16, 9);
    cout <<"Mui ten trai: Sang Trai";
    gotoXY(16, 10);
    cout <<"Mui ten phai: Sang Phai";
    gotoXY(16, 11);
    cout <<"Mui ten len: Len Tren";
    gotoXY(16, 12);
    cout <<"Mui ten xuong: Xuong Duoi";
    gotoXY(16, 13);
    cout <<"Enter: Thuc hien nuoc di";
    gotoXY(12,23);
    cout <<"Sau khi nguoi choi X di thi nuoc di se danh cho nguoi choi O ";
    gotoXY(27,25);
    cout <<"Nhan Enter de quay lai ";
    TextColor(0);
    char a;
    do
    {
        a = getch();
    }while(a!=13 && a != 'e' && a != 'E' && a !='5' && a !=8);
    system("cls");
    fflush(stdin);
    playgame(thoat);
}
void about(int &thoat)
{
 khungplay();
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 11);
        cout << " ";
    }
        for(int i = 0; i<45; i++)
    {
        gotoXY(18+i, 21);
        cout << " ";
    }
 gotoXY(22, 10);
 TextColor(12);
 cout<<"Name:";
 gotoXY(34, 10);
 TextColor(15);
 cout<<"TRINH XUAN DAT";
 gotoXY(22, 11);
 TextColor(12);
 cout<<"Birthday:";
 gotoXY(34, 11);
 TextColor(10);
 cout<<"12/02/2003";

 gotoXY(22, 12);
 TextColor(12);
 cout<<"Class:";
 gotoXY(34, 12);
 TextColor(10);
 cout<<"K66-CA-CLC-3";

     gotoXY(27,25);
     TextColor(15);
     cout<<"  Nhan Enter de quay lai  ";
    gotoXY(51,25);
    TextColor(0);
 char a;
    do
    {
        a = getch();
    }while(a!=13 && a != 'e' && a != 'E' && a !='5' && a != 8);
    system("cls");
    fflush(stdin);
    playgame(thoat);
}
