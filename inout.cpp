#include<iostream>
#include<stdio.h>
#define prt(a) printf("%d\n",a)
#define aaa printf("a\n")
#define bbb printf("b\n")

using namespace std;

int wczytaj(long long int*&n);

int main(void)
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
    {
        long long int*a;
        int adl=wczytaj(a);
        printf("%d:  ",adl);
        printf("%lld",a[adl-1]);
        for(long long int*w=a+adl-2;w>=a;w--)     printf("%09lld",*w);
        printf("\n");
        delete[]a;
    }
}


int wczytaj(long long int*&n)       //zakaz liczb ujemnych    //brak zabespieczenia przed literami       //blad dla zera
{
    string s;
    cin>>s;
    while((s.length()>1)&&(s[0]=='0'))      s.erase(0);
    int sdl=s.length();
    n=new long long int [sdl/9+100];
    for(long long int*w=n+(sdl/9+100)-1;w>=n;w--)  *w=0;

    long long int*w=n;
    for(char*i=&s[sdl-1];i>=&s[8];w++)
        for(int j=1;j<=100000000;j*=10,i--)
            *w+=((int)*i-48)*j;
    if(sdl%9>0)
        for(int i=sdl%9-1,j=1;i>=0;j*=10,i--)
            *w+=((int)s[i]-48)*j;

    return (sdl%9==0)?sdl/9:sdl/9+1;
}
