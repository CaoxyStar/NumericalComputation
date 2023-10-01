#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//�������
double objectFunction(double x)
{
	return pow(x,3)-x-1;
}

//�������������
double derivativeFunction(double x)
{
	return 3*x*x-1;
}

//ţ����ɽ��
void Newton_Gradient(double x, double sigma1, double sigma2,double sigma3)
{
	double returnValue1, returnValue2, temp, x1;
	int n = 1;
	double t = 1;
	cout << "n=0\t\tx=" << x << "\tf(x)=" << objectFunction(x) << endl;
	while(1)
	{
		returnValue1 = objectFunction(x);
		temp = derivativeFunction(x);
		//�������������ж�
		if (temp == 0)
		{
			cout << "����������ֵΪ0�������жϣ�" << endl;
			return;
		}
		x1 = x - t * returnValue1 / temp;
		returnValue2 = objectFunction(x1);
		//�в���ж�
		if (abs(returnValue2) <= sigma2)
		{
			cout <<setprecision(7)<< "����в��Ҫ��ĸ�Ϊ" << x1 << "������ֵΪ" << returnValue2;
			cout << "��������Ϊ" << n << endl;
			return;
		}
		if (abs(returnValue2) < abs(returnValue1))
		{
			//�������ж�
			if (abs(x1 - x) < sigma1)
			{
				cout << fixed<<setprecision(6) << "���������Ҫ�󾫶�Ҫ��ĸ�Ϊ" << x1 << "������ֵΪ" << returnValue2;
				cout << "��������Ϊ" << n << endl;
				return;
			}
			//�м������
			cout << "n=" << n << "\tt=" << t << "\tx=" << x1 << "\tf(x)=" << returnValue2 << endl;

			x = x1;
			n = n + 1;
			t = 1;
			continue;
		}
		else               //��ɽ���Ӹ���
		{
			if (t < sigma3)
			{
				cout << "tֵ�ѵ�����ɽ�����½磬�����жϣ�" << endl;
				return;
			}
			t = t / 2;
		}
	}

}

//ȡ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double x, sigma1, sigma2, sigma3;
	cout << "�������ֵ��";
	cin >> x;
	cout << "��������Ƹ�����Ҫ��";
	cin >> sigma1;
	cout << "������в��Ҫ��";
	cin >> sigma2;
	cout << "��������ɽ�����½磺";
	cin >> sigma3;
	Newton_Gradient(x, sigma1,sigma2,sigma3);
	return 0;
}*/

