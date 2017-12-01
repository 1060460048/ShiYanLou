#include <stdio.h>
#include <stdlib.h>

int n;
/*
���������Ƕ�ð������ĸĽ���
���Ļ���˼����ͨ��һ���������ݷֳ������֣�
һ�����е����ݶ�����һ�����е�����С��
�ٶ����������е�����������ֱ��������������
*/ 


/*
 * �ָ�ʹ�����¼�����Ԫ�ر��ұ�Ԫ��С
 */
int Partition(int *array, int low, int high)
{
    int pivotkey = array[low];//��ʼ�� ��ֵԪ��   
    array[0] = array[low];//�����м����  �������±�  Ԫ�� 
    while (low < high)
    {
        while (low < high && array[high] >= pivotkey)//��ֵԪ�� �ҵ���  pivotkey= array[low]С��Ԫ�� 
        {
            high--;//
        }
        array[low] = array[high];//��  pivotkey= array[low]С��Ԫ�� 
        while (low < high && array[low] <= pivotkey)//�ҵ���  pivotkey= array[low]���Ԫ�� 
        {
            low++;//
        }
        array[high] = array[low];//��ķ��ڸ߳� 
    }
    array[low] = array[0];
    return low;
}

/*
 * ��������ݹ�ʵ��
 */
void QuickSort(int *array, int low, int high)
{
    if (low < high)
    {
        int pivotloc = Partition(array, low, high);
        QuickSort(array, low, pivotloc - 1);//�ݹ���ߵ����� 
        QuickSort(array, pivotloc + 1, high);//�ݹ��ұߵ����� 
    }
}

int main()
{
    int i;
    int *array;
    printf("����������Ĵ�С��");
    scanf("%d", &n);
    array = (int*) malloc(sizeof(int) * (n + 1));// ��һ��Ԫ�� ���������м���� 
    printf("���������ݣ��ÿո�ָ�����");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &array[i]);
    }
    QuickSort(array, 1, n);
    printf("�����Ϊ��");
    for (i = 1; i <= n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
