#include<stdio.h>
int main()
{
   void copy_string(char from[],char to[])��
   char a[]="I am a teacher";  //�ַ��������� 
   // char *a="I an a teacher";//�ַ���ָ�� 
   char b[]="You are a programmer";
   printf("string a=%s\nstring b=%s\n",a,b);
   printf("copy string a to string b:\n");
   
   copy_string(a,b);//1)���ַ���������Ϊ����ʵ����
    
  //char *from=a,*to=b;  2)���ַ���ָ�����������ʵ��
  //copy_string(from,to);
  
   printf("\nstring a=%s\nstring b=%s\n",a,b);
   return 0;

}

// �ַ������������� �β� 
void copy_string(char from[],char to[])
{
   int i=0;
   while(from[i]!='\0')
   {
      to[i]=from[i];
      i++;
   }
   to[i]='\0';
}

// �ַ���ָ�������� �β� 
void copy_string(char *from,char *to)
{
   for(;*from!='\0';from++,to++)
   {*to=*from;}
   *to='\0';
}
