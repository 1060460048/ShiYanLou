#include<stdio.h>
int main()
{
//����һ��ָ������洢�·�����
    char *months[12]={"January","February","March","April","May","June","July","August","September","October","December"};
//���������洢�·ݺŵı���
    int number; 
    printf("Please enter the month number:\n");
    scanf("%d",&number);
//ʵ���������еĴ�����·ݺ���1
    number--;
    printf("The month's name is:");
//����·�����
    printf("%s",*(months+number));//monthsΪ�����׵�ַ   *( ) ȡ��Ӧ��ַ�ڵ�ֵ 
    return 0;
}
