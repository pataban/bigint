#include<stdio.h>
#include<cstdlib>
#include<math.h>
#define prt(a) printf("%d\n",a);
#define aaa printf("a\n");
#define bbb printf("b\n");
#define ccc printf("c\n");
typedef long long int LL;
typedef unsigned long long int LLU;

class bigint
{
    static const LL sys=1e+9;
    int ndl;
    LL*n;
public:
    void get();//zapisuje wielkosc n
    void put();
    int dl()const{return ndl;}
    LL*begin()const{return n;}
    LL*end()const{return n+ndl;}
    void operator+=(const bigint&);
    void operator-=(const bigint&);
    void operator*=(const bigint&);
    void operator/=(const bigint&);
    void operator%=(const bigint&);
    bigint&operator++();//pre       //bledne
    bigint&operator--();//pre
    bool operator>(const bigint&);
    bool operator<(const bigint&);
    bool operator==(const bigint&);
    bool operator!=(const bigint&);
    bool operator>=(const bigint&);
    bool operator<=(const bigint&);
    bool is_zero();
    static bool bigger(LL*a,const int&adl,LL*b,const int&bdl);
    static void substract(LL*a,int&adl,LL*b,int&bdl);
};


int main()
{
    bigint a,b;
    a.get();
    b.get();
    a%=b;
    a.put();
	return 0;
}


void bigint::operator%=(const bigint&b)     //blad dla 999999999999999999123456789123456789123456789123456789%333333333333333333
{
    int bdl=b.dl(),adl=bdl-1;
    LL*a=n+ndl-bdl+1;
    while(*this>=b)
    {
        do
        {
            a--;
            adl++;
        }while(adl<bdl);
        while(!bigger(b.begin(),bdl,a,adl))
            substract(a,adl,b.begin(),bdl);
        if((adl==1)&&(!(*a)))   adl--;
        ndl=a-n+adl;
    }
}

void bigint::operator/=(const bigint&b)     ////////    zle dla 999999999999999999123456789123456789123456789123456789/333333333333333333
{
    int bdl=b.dl();
    LL*o=new LL[ndl+10];
	for(LL*w=o+ndl+9; w>=o; w--)     *w=0;
	LL*wo=o,*oe,*a=n+ndl-bdl+1;
	int adl=bdl-1;
	while(*this>=b)
    {
        do
        {
            a--;
            adl++;
        }while(adl<bdl);
        while(!bigger(b.begin(),bdl,a,adl))
        {
            substract(a,adl,b.begin(),bdl);
            (*wo)++;
            for(oe=wo;*oe==sys;oe++)
            {
                *oe=0;
                (*(oe+1))++;
            }
        }
        if((adl==1)&&(!(*a)))   adl--;
        ndl=a-n+adl;
        wo++;
    }
    if(!(*oe))  oe--;
    ndl=oe-o+1;
    if(!(*o))   ndl--;
    delete[]n;
    n=new LL[ndl+10];
    for(LL*w=n+ndl+9; w>=n; w--)     *w=0;
    for(LL*wn=n;wn<n+ndl;oe--,wn++)  *wn=*oe;
    delete[]o;
}

void bigint::operator*=(const bigint&b)
{
    LL*o=new LL[ndl+b.dl()];
	for(LL*w=o+ndl+b.dl()-1; w>=o; w--)     *w=0;
	LL*oe,*wwo;
	for(LL*wo=o,*wb=b.begin();wb<b.end();wb++,wo++)
	{
        wwo=wo;
        for(LL*wn=n;wn<n+ndl;wn++,wwo++)
        {
            *wwo+=*wn**wb;
            if(*wwo>sys-1)
            {
                *(wwo+1)+=*wwo/sys;
                *wwo%=sys;
            }
        }
        for(oe=wwo;*oe>sys-1;oe++)
        {
            *(oe+1)+=*oe/sys;
            *oe%=sys;
        }
    }
    if(*oe) ndl=oe-o+1;
    else    ndl=oe-o;
    delete[]n;
    n=o;
}

void bigint::operator-=(const bigint&b)
{
    LL*wn=n;
    for(LL*wb=b.begin();wb<b.end();wn++,wb++)
    {
        *wn-=*wb;
        if(*wn<0)
        {
            *wn+=sys;
            (*(wn+1))--;
        }
    }
    for(;*wn<0;wn++)
    {
        *wn+=sys;
        (*(wn+1))--;
    }
    if(*wn) ndl=wn-n+1;
    else    ndl=wn-n;
}

void bigint::operator+=(const bigint&b)
{
    LL*wn=n;
    for(LL*wb=b.begin();wb<b.end();wn++,wb++)
    {
        *wn+=*wb;
        if(*wn>sys-1)
        {
            *wn-=sys;
            (*(wn+1))++;
        }
    }
    for(;*wn>sys-1;wn++)
    {
        *wn-=sys;
        (*(wn+1))++;
    }
    if(*wn) ndl=wn-n+1;
    else    ndl=wn-n;
}

bigint&bigint::operator++()     //bledne
{
    LL*wn=n;
    while(*wn+1==sys)   wn++;
    (*wn)++;
    return *this;
}

bigint&bigint::operator--()
{
    LL*wn=n;
    while(!(*wn))   wn++;
    (*wn)--;
    return *this;
}

bool bigint::is_zero()
{
    if((ndl==1)&&(!(*n)))   return true;
    return false;
}

bool bigint::operator>(const bigint&b)
{
    if(ndl>b.dl())    return true;
    if(b.dl()>ndl)    return false;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
    {
        if(*wn>*wb) return true;
        if(*wn<*wb) return false;
    }
    return false;
}

bool bigint::operator<(const bigint&b)
{
    if(ndl>b.dl())    return false;
    if(b.dl()>ndl)    return true;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
    {
        if(*wn>*wb) return false;
        if(*wn<*wb) return true;
    }
    return false;
}

bool bigint::operator==(const bigint&b)
{
    if(ndl!=b.dl())    return false;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
        if(*wn!=*wb)    return false;
    return true;
}

bool bigint::operator!=(const bigint&b)
{
    if(ndl!=b.dl())    return true;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
        if(*wn!=*wb)    return true;
    return false;
}

bool bigint::operator>=(const bigint&b)
{
    if(ndl>b.dl())    return true;
    if(b.dl()>ndl)    return false;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
    {
        if(*wn>*wb) return true;
        if(*wn<*wb) return false;
    }
    return true;
}

bool bigint::operator<=(const bigint&b)
{
    if(ndl>b.dl())    return false;
    if(b.dl()>ndl)    return true;
    for(LL*wn=n+ndl-1,*wb=b.end()-1;wn>=n;wn--,wb--)
    {
        if(*wn>*wb) return false;
        if(*wn<*wb) return true;
    }
    return true;
}

void bigint::get()
{
    char*s=new char[10010];
    scanf("%10005s",s);
    char*se=s;
    for(;*se!='\0';se++);
    int sdl=se-s;
    n=new LL[sdl/9+10];
    for(LL*wn=n+sdl/9+9;wn>=n;wn--)   *wn=0;
    LL*w=n;
    char*wc=s+sdl-1;
    for(;wc>s+7;w++)
        for(LL i=1;i<sys;i*=10,wc--)
            *w+=(*wc-48)*i;
    for(LL i=1;wc>=s;i*=10,wc--)
        *w+=(*wc-48)*i;
    if(sdl%9)   w++;
    ndl=w-n;
}

void bigint::put()
{
    printf("%lld",*(n+ndl-1));
    for(LL*w=n+ndl-2;w>=n;w--)
        printf("%09lld",*w);
}


void bigint::substract(LL*a,int&adl,LL*b,int&bdl)
{
    LL*wa=a;
    for(LL*wb=b;wb<b+bdl;wa++,wb++)
    {
        *wa-=*wb;
        if(*wa<0)
        {
            *wa+=sys;
            (*(wa+1))--;
        }
    }
    for(;*wa<0;wa++)
    {
        *wa+=sys;
        (*(wa+1))--;
    }
    if(*wa) adl=wa-a+1;
    else    adl=wa-a;
}

bool bigint::bigger(LL*a,const int&adl,LL*b,const int&bdl)
{
    if(adl>bdl) return true;
    if(bdl>adl) return false;
    for(LL*wa=a+adl-1,*wb=b+bdl-1;wa>=a;wa--,wb--)
    {
        if(*wa>*wb) return true;
        if(*wa<*wb) return false;
    }
    return false;
}



