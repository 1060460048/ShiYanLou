#include<stdio.h>
int main()
{
    int max(int x,int y);//����max���� Ϊ�˵��� 
    int a[10],m,n,i;
    printf("please enter 10 integer number:");
    for(i=0;i<10;i++)
       scanf("%d",&a[i]);
    printf("\n");

    for(i=1,m=a[0],n=0;i<10��i++)   
    {
        if(max(m,a[i])>m)          //��max��������ֵ����m
        {
            m=max(m,a[i]);        //max�����ķ���ֵȡ��m
            n=i;                  //������Ԫ�ص���ż��������ŵ�n��
        }
    }

    printf("the largest number is %d\n it is the %dth number \n",m,n+1);
}

int max(int x,int y)
{
    return(x>y?x:y);
}
