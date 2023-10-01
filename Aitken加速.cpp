#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//�����������
double Acc_func(double x)
{
	return exp(-x);
}

//���ٵ���Steffensen
void AitkenAcc(double x, double sigma,int N_max)
{
	double x1, x2,temp;
	for(int i =0;i<N_max;i++)
	{
		x1 = Acc_func(x);
		x2 = Acc_func(x1);
		temp = x - pow(x1 - x, 2) / (x2 - 2 * x1 + x);
		cout << i << "\t";
		cout<< fixed << setprecision(8) << x << "\t" << x1 << "\t" << x2 << endl;
		if (abs(x1 - x) < sigma)
		{
			cout << fixed << setprecision(8) << "��" << i+1 << "�ε����õ����㾫��Ҫ��ĸ�Ϊ" << temp << endl;
			return;
		}
		x = temp;
	}
	cout << "��������������Ϊ�ҵ����㾫��Ҫ��Ľ��Ƹ���" << endl;
}

//ȡ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double x, sigma;
	int N_max;
	cout << "�������ֵ��";
	cin >> x;
	cout << "�����뾫��Ҫ��";
	cin >> sigma;
	cout << "������������������";
	cin >> N_max;
	AitkenAcc(x, sigma, N_max);
	return 0;
}*/