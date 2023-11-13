#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<math.h>
#define aaa printf("a\n");
#define bbb printf("b\n");
#define ccc printf("c\n");
typedef long long int LL;
using namespace std;

LL*o;
int*a,adl,*b,bdl,odl;
int wczytaj(int*&n);
int oblicz();
LL* sprawdz(LL*n,LL*e);
void wypisz(LL*n,int ndl);

int main()
{
	adl=wczytaj(a);
	bdl=wczytaj(b);
	o=new LL[adl+bdl];
	for(LL*w=o+adl+bdl-1; w>=o; w--)     *w=0;
	odl=oblicz();
	wypisz(o,odl);
	printf("\n");
	delete[]a;
	delete[]b;
    delete[]o;
	return 0;
}

int oblicz()
{
    LL*wo=o,*wwo,*oe;
    for(int*wb=b;wb<b+bdl;wb++,wo++)
    {
        wwo=wo;
        for(int*wa=a;wa<a+adl;wa++,wwo++)   *wwo+=*wa**wb;
        oe=sprawdz(wo,wwo);
    }
    return oe-o+1;
}

LL* sprawdz(LL*n,LL*e)
{
    for(;n<e;n++)
        if(*n>999)
        {
            *(n+1)+=*n/1000;
            *n=*n%1000;
        }
    if(*n==0)   return n-1;
    for(;*n>999;n++)
        if(*n>999)
        {
            *(n+1)+=*n/1000;
            *n=*n%1000;
        }
    return n;
}

int wczytaj(int*&n)          //zera wiodoce
{
    char*s=new char[10010];
    scanf("%10005s",s);
    char*se=s;
    for(;*se!='\0';se++);
    int sdl=se-s;
    n=new int[sdl/2];
    int*w=n;
    for(char*wc=s+sdl-1; wc>=s+2; wc-=3,w++)    *w=*(wc-2)*100+*(wc-1)*10+*wc-5328;
    if(sdl%3==0)        w--;
    else if(sdl%3==1)   *w=*s-48;
    else if(sdl%3==2)   *w=(*s-48)*10+*(s+1)-48;
    return w-n+1;
}

void wypisz(LL*n,int ndl)
{
    printf("%lld",*(n+ndl-1));
    for(LL*w=n+ndl-2;w>=n;w--)
        printf("%03lld",*w);
}
