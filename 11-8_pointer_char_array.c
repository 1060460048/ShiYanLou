#include<stdio.h>
int main()
{
   char a[]="I am a programmer",b[20];
   int i;
   for(i=0;*(a+i)!='\0';i++)
   *(b+i)=*(a+i);
   *(b+i)='\0';//��ӽ����� 

   printf("string a is:%s\n",a);
   printf("string b is:");
   
   for(i=0;b[i]!='\0';i++) //   printf("string b is:%s\n",b);
   printf("%c",b[i]);


   char c[]="I am a programmer",d[20],*p1,*p2;
   p1=c,p2=d;//��ַ 
   for(;*p1!='\0';p1++,p2++)
   *p2=*p1;//���� 
   *p2='\0';// ��ӽ����� 

   printf("string a is:%s\n",c);
   printf("string b is:%s\n",d);//������������ֹͣ 

   printf("\n");
   return 0;
}
