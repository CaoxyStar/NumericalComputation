#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//�������
double object_function(double x)
{
	return pow(x,6)-x-1;
}

//���ַ�
void myDichotomy(double a, double b, double sigma1, double sigma2, double N_max)
{
	double temp;
	double h;
	cout << "a=" << a << "\tb=" << b << "\t";
	for (int i = 1; i < N_max+1; i++)
	{
		temp = (a + b) / 2;
		cout << "x=" << temp << "\tf(x)="<<object_function(temp)<<endl;
		h = (b - a) / 2;
		if (abs(object_function(temp)) < sigma1 || h < sigma2)
		{
			cout << setprecision(7) << "��" << i << "�ζ��ֵõ����������Ľ��Ƹ�Ϊ" << temp;
			cout<<fixed<<setprecision(7)<<"����ʱ����ֵΪ" << object_function(temp) << endl;
			return;
		}
		if (object_function(a) * object_function(temp) < 0)
			b = temp;
		else
			a = temp;
		cout << "a=" << a << "\tb=" << b << "\t";
	}
	cout << "�ְ�" << N_max << "��û�еõ����Ͼ���Ҫ��Ľ��Ƹ���" << endl;
}

//ȡ���·�main����ע�ͼ��ɲ���
/*
int main()
{
	double a, b, sigma1, sigma2;
	int N_max;
	cout << "����������������ޣ�";
	cin >> a;
	cout << "����������������ޣ�";
	cin >> b;
	cout << "�����뾫��Ҫ��sigma1��";
	cin >> sigma1;
	cout << "�����뾫��Ҫ��sigma2��";
	cin >> sigma2;
	cout << "�����������ִ�����";
	cin >> N_max;
	myDichotomy(a, b, sigma1, sigma2, N_max);
	return 0;
}*/