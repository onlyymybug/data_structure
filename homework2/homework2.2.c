#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
int isMatch(const char *s, const char *p)
{
    assert(s != NULL && p != NULL);
    if(*p == '*')
    {
        while(*p=='*'){p++;}
        if(*p == '\0'){return 1;}
        while(*s != '\0' && !isMatch(s,p)){s++;}
        if(*s=='\0'){return 0;}
		else{return 1;}
    }
    else if(*p == '\0' || *s == '\0')
    {
        return (*p==*s);
    }
    else if(*p==*s ||*p=='?')
    {
        return isMatch(++s,++p);
    }
    else 
    {
        return 0;
    }
}
int main()
{
    int i=0;
    char a[100],b[100];
    scanf("%s",a);
    scanf("%s",b);
    i=isMatch(a,b);
    if(i==1)
    {
        printf("yes\n");
    }
    else
        printf("no\n");
    system("pause");
    return 0;
}