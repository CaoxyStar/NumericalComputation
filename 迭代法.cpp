#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//��������
double Iteration_function(double x)
{
	return log(x+2);
}

//����������Ƹ�
void Iteration(double x, double sigma, int N_max)
{
	double temp;
	for (int i = 0; i < N_max; i++)
	{
		temp = Iteration_function(x);
		cout << setprecision(8) << x << endl;
		//������֤
		if (abs(temp - x) < sigma)
		{
			cout << "��" << i << "�ε����õ����㾫��Ҫ��ĸ�Ϊ��";
			cout << setprecision(8) << x << endl;
			cout << "��ʱԭ�����ľ���ֵΪ��" << abs(Iteration_function(x) - x) << endl;
			return;
		}
		x = temp;
	}
	cout << "������������" << N_max << "�λ�û�еõ����㾫��Ҫ�����Ϣ��" << endl;
}

//ȡ��main����ע�ͼ��ɿ�ʼ����
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
	Iteration(x, sigma, N_max);
	return 0;
}*/