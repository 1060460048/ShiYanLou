#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ���� �洢�������еĳ��� 
// taskmgr window��  
//  ps -ef  linux�� 
// exec + l / v / p /e ���� ��һ�������滻һ������ PID���� ������
// l list �����б� �� v vector ��������/���� ��p ·�� path ; e �������� environment 
//  C������ʹ�� getenv("������") ��ȡ����������ֵ
// char *my_env[] = {"������=ֵ",NULL}; //�������� ���һ������Ϊ NULL
// execle("diner_info", "diner_info", "4", NULL, my_env);//ʹ�� diner_info�滻��ǰ���� 
// ִ�е�״̬ �����ڱ��� errno ��  puts(strderror(errno));��ѯ������Ϣ
// #include <unistd.h>  // execXXX()���� 
// #include <errno.h>   // errno ���� 
// #include <string.h>  // strerron() ��ʾ������Ϣ
// ����鿴 ������Ϣ
/*
#include <unistd.h>  // execXXX()���� 
#include <errno.h>   // errno ���� 
#include <string.h>

int main(){// exec()���������������̳ɹ� ���������о������� 
  if(execl("/sbin/ifconfig","/sbin/ifconfig", NULL)==-1){
  	if(execl("ipconfig","ipconfig", NULL)==-1)
  	  fprintf(stderr,"�������� ipconfig: %s", strerron(erron));
  	  return 1;
  }
  return 0;
} 
*/ 

 
/*
struct tm {
   int tm_sec; //�룬��Χ�� 0 �� 59 //
   int tm_min; //�֣���Χ�� 0 �� 59 //
   int tm_hour;//Сʱ����Χ�� 0 �� 23/
   int tm_mday;//һ���еĵڼ��죬��Χ�� 1 �� 31//
   int tm_mon; //�·ݣ���Χ�� 0 �� 11 //
   int tm_year; //�� 1900 �������//
   int tm_wday; //һ���еĵڼ��죬��Χ�� 0 �� 6//
   int tm_yday; //һ���еĵڼ��죬��Χ�� 0 �� 365 //
   int tm_isdst;//����ʱ// 
};
*/
char * now_time(){
	time_t t;
	time (&t);
	return asctime (localtime (&t));	//C++ �� asctime����ȫ������ʹ��asctime_s���档��localtime_s���ʹ��
}

int main(){
	char comment[80];//��¼���ı�
	char cmd[120];//system ִ�е�����
	fgets(comment,80,stdin);//��ȡ��¼���ı�
	sprintf(cmd,"echo '%s %s' >> report.log",comment,now_time());
	system(cmd);//ϵͳ���� 
	
	return 0;
}
