#include<stdio.h>
/*
int a=100;
int *pointer_1;
pointer_1=&a;     ȡ��ַ&a
 *pointer_1;      ȡֵ 
*/ 
int main()
{
 int a=100,b=10;
 int *pointer_1,*pointer_2; //����ָ���������ݵ�ָ�����pionter_1,pionter_2 �����*�Ƕ��� ָ����� 
 pointer_1=&a;              //�ѱ���a�ĵ�ַ����ָ�����pointer_1
 pointer_2=&b; 
 printf("a=%d,b=%d\n",a,b);
 printf("%p,%p\n",pointer_1,pointer_2); //���a��b���ڴ��еĵ�ַ
 printf("*pointer_1=%d,*pointer_2=%d\n",*pointer_1,*pointer_2);//�������a��b��ֵ  �����*��ȡָ�����ָ���ֵ 

 return 0;

}
