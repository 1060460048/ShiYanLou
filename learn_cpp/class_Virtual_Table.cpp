#include <iostream>
using namespace std;
 
//���� Base1
class Base1 {
public:
            virtual void f() { cout << "Base1::f" << endl; }
            virtual void g() { cout << "Base1::g" << endl; }
            virtual void h() { cout << "Base1::h" << endl; }
 
};

//���� Base2 
class Base2 {
public:
            virtual void f() { cout << "Base2::f" << endl; }
            virtual void g() { cout << "Base2::g" << endl; }
            virtual void h() { cout << "Base2::h" << endl; }
};

//���� Base3 
class Base3 {
public:
            virtual void f() { cout << "Base3::f" << endl; }
            virtual void g() { cout << "Base3::g" << endl; }
            virtual void h() { cout << "Base3::h" << endl; }
};
 
//���� �̳��� ���� Base1  Base2  Base3 
class Derive : public Base1, public Base2, public Base3 {
public:
            virtual void f() { cout << "Derive::f" << endl; }  //������ ����� ����f()
            virtual void g1() { cout << "Derive::g1" << endl; }//���е�  ���� ����
};
 
 
typedef void(*Fun)(void);//����ָ��
 
int main()
{
            Fun pFun = NULL;
 
            Derive d;//����
            int** pVtab = (int**)&d;// �麯���� ����ָ������
 
//����Base1�� �麯���� Base1's vtable
//  |Derive::f()|Base1::g()|Base1::h()|Derive::g1()|.|

            //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
            pFun = (Fun)pVtab[0][0];
            pFun();
 
            //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
            pFun = (Fun)pVtab[0][1];
            pFun();
 
            //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
            pFun = (Fun)pVtab[0][2];
            pFun();
 
   
            //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
            pFun = (Fun)pVtab[0][3];
            pFun();
 
           //�麯���� β�� ������ |.|
            pFun = (Fun)pVtab[0][4];
            cout<<pFun<<endl;
 
 // ���� Base2 �麯����
 //|Derive::f()|Base2::g()|Base2::h()|.|
 //Base2's vtable
            //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
            pFun = (Fun)pVtab[1][0];
            pFun();
 
            //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
            pFun = (Fun)pVtab[1][1];
            pFun();

            //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+2);
            pFun = (Fun)pVtab[1][2];
            pFun();

            pFun = (Fun)pVtab[1][3];
            cout<<pFun<<endl;
 

 // ���� Base3 �麯����
 //|Derive::f()|Base3::g()|Base3::h()|.|
 //Base3's vtable
            //pFun = (Fun)*((int*)*(int*)((int*)&d+2)+0);
            pFun = (Fun)pVtab[2][0];
            pFun();
 
            //pFun = (Fun)*((int*)*(int*)((int*)&d+2)+1);
            pFun = (Fun)pVtab[2][1];
            pFun();
            //pFun = (Fun)*((int*)*(int*)((int*)&d+2)+2);
            pFun = (Fun)pVtab[2][2];
            pFun();
           //�麯���� β�� ������ |.|
            pFun = (Fun)pVtab[2][3];
            cout<<pFun<<endl;
 
            return 0;
}

