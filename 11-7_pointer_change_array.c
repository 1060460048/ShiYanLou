/*
1���βκ�ʵ�ζ��������������磺
int main()     
{
   int a[10];
   .
   f(a,10);           // aʵ��  ʵ����������  aΪ��ַ &a[0] 
}
int f(int x[],int n)  // x[]�β� 
{
   .
}

2��ʵ�������������β���ָ����������磺
int main()
{
   int a[10];
   .
   f(a��10)��
}
void f(int *x,int n)//�β�  *x ָ�����
{
  .
}

3��ʵ���βζ���ָ����������磺
int main()
{
    int a[10],*p=a;//ָ�����  ,p��ֵ��&a[0]
    .
    f(p,10);
}
void f(int *x,int n) // x�ĳ�ʼֵҲ��&a[0]
{
   .
}


4�� ʵ��Ϊָ��������β�Ϊ�����������磺
int main����
 {
    int a[10],*p=a;//ָ�����  ,p��ֵ��&a[0]
    .
    f(p,10);
 }
void f(int x[],int n)
{
   .
}
*/ 
#include<stdio.h>
int main()
{
   void change(int *x,int n);
   int i,a[10]={3,7,9,11,0,6,7,5,4,2};
   printf("the original array:\n");
   for(i=0;i<10;i++)
      printf("%d\t",a[i]);
   printf("\n");

   change(a,10);
   printf("the array has been inverted:\n");
   for(i=0;i<10;i++)
     printf("%d\t",a[i]);

   return 0;
}

void change(int *x,int n)
{
   int *p,temp,*i,*j,m=(n-1)/2;
   i=x;j=x+n-1;p=x+m;//x�׵�ַ   x+n-1β��ַ  p=x+m�м�ĵ�ַ 
   for(;i<=p;i++,j--)
   {
      temp=*i;//��ַָ��ı���ֵ  
      *i=*j;
      *j=temp;
    }
}
