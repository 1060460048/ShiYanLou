#include <stdio.h>
#include <stdlib.h>
// ÿ���ҵ�ʣ����������С��Ԫ�� ����ǰ������������� 
int n;
/*
�������˼����ͨ��n-1������Ԫ�صıȽϣ���n-i+1����¼��ѡ����С�����ݣ�
�����i�����ݽ��н���������ʱ�临�Ӷ���O(n^2)��
������������öѵ�������������������ʱ�临�Ӷ���O(nlogn)
*/ 
/*
 * ѡ������
 */
void SelectSort(int *array)
{
    int i, j, k, temp;
    for (i = 0; i < n; i++)//�ӵ�һ��ԭ�ؿ�ʼ 
    {
        k = i;//��ǰ Ԫ�� �±� 
        for (j = i + 1; j < n; j++)// һ�� ѡȡ��һ��Ԫ�ؽ��бȽ� 
        {
            if (array[j] < array[k])//��С�� 
            {
                k = j;//��¼��С�� Ԫ�� λ�� 
            }
        }
        if (k != i)//���ΰ� С��Ԫ�ط���ǰ�������������  ��С��Ԫ��С�귢���˱仯 
        {//
            temp = array[i];
            array[i] = array[k];
            array[k] = temp;
        }
    }
}

int main()
{
    int i;
    int *array;
    printf("����������Ĵ�С��");
    scanf("%d", &n);
    array = (int*) malloc(sizeof(int) * n);
    printf("���������ݣ��ÿո�ָ�����");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    SelectSort(array);
    printf("�����Ϊ��");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
