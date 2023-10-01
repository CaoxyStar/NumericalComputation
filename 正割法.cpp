#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//�������
double SecantFunction(double x)
{
	return pow(x, 4) - 3 * x + 1;
}

//���
void Secant(double x_0, double x_1, double sigma1, double sigma2)
{
	double temp,res;
	int n = 2;
	cout << "0\t" << x_0 << "\t" << SecantFunction(x_0) << endl;
	cout << "1\t" << x_1 << "\t" << SecantFunction(x_1) << endl;
	while (1)
	{
		temp = x_1 - SecantFunction(x_1) * (x_1 - x_0) / (SecantFunction(x_1) - SecantFunction(x_0));
		res = SecantFunction(temp);
		//�в���ж�
		if (abs(res) < sigma2)
		{
			cout << fixed << setprecision(8) << "����в�Ҫ��ĸ�Ϊ" << temp << "���亯������ֵΪ" << res;
			cout << "��Ϊ��" << n << "����" << endl;
			return;
		}
		//�������ж�
		if (abs(temp - x_1) < sigma1)
		{
			cout << fixed << setprecision(8) << "���������Ҫ��ĸ�Ϊ" << temp << "���亯������ֵΪ" << res;
			cout << "��Ϊ��" << n << "����" << endl;
			return;
		}

		//�м������
		cout << n<<"\t" << temp << "\t" << SecantFunction(temp) << endl;

		n = n + 1;
		x_0 = x_1;
		x_1 = temp;
	}
}

//ȡ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double x_0, x_1, sigma1, sigma2;
	cout << "�������x_0:";
	cin >> x_0;
	cout << "�������x_1:";
	cin >> x_1;
	cout << "�����������Ҫ��";
	cin >> sigma1;
	cout << "������в��Ҫ��";
	cin >> sigma2;
	Secant(x_0, x_1, sigma1, sigma2);
	return 0;
}*/