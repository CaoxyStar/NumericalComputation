#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//�������
double Function1(double x)
{
	return 3*x*x-exp(x);
}

//�������������
double Function2(double x)
{
	return 6*x-exp(x);
}

//ţ�ٵ������
void Newton_Iteration(double x, double sigma, int N_max)
{
	double temp1;      //������ֵ
	double temp2;      //������x��ֵ
	cout << "0\t" << x << endl;
	for (int i = 1; i <= N_max; i++)
	{
		temp1 = Function2(x);
		//��֤����һ
		if (temp1 == 0)
		{
			cout << "������Ϊ0�������жϣ�" << endl;
			return;
		}
		temp2 = x - Function1(x) / temp1;
		//������֤
		if (abs(temp2 - x) < sigma)
		{
			cout << fixed<<setprecision(5) << "���̸�Ϊ" << temp2 << "����ʱ����ֵ����" << Function1(temp2);
			cout<< "����������Ϊ" << i << endl;
			return;
		}
		x = temp2;
		cout << i << "\t" << x << endl;
	}
	cout << "����������������δ�ҵ����㾫��Ҫ��ĸ���" << endl;
	return;
}

//ȡ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double x, sigma;
	int N_max;
	cout << "�������ֵ��";
	cin >> x;
	cout << "������������������";
	cin >> N_max;
	cout << "�����뾫��Ҫ��";
	cin >> sigma;
	Newton_Iteration(x, sigma, N_max);
	return 0;
}*/
