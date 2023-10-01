#include<iostream>
#include<iomanip>
using namespace std;

//΢�ֺ���
double Runge_formula(double x, double y)
{
	return -2/(y-x);
}

//�����Ľ������������
void Runge_Kutta(double a, double b, int n, double y_init)
{
	double h = (b - a) / n;
	double x = a;
	double y = y_init;
	double K1, K2, K3, K4;
	cout << "x\t\ty\n" << x << "\t\t" << y << endl;
	for (int i = 0; i < n; i++)
	{
		K1 = Runge_formula(x, y);
		K2 = Runge_formula(x + h / 2, y + h * K1 / 2);
		K3 = Runge_formula(x + h / 2, y + h * K2 / 2);
		K4 = Runge_formula(x + h, y + h * K3);
		x += h;
		y += h * (K1 + 2 * K2 + 2 * K3 + K4) / 6;
		cout<<fixed<<setprecision(9) << x << "\t" << y << endl;
	}
}

//��������ȥ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double a, b, y_init;
	int n;
	cout << "������������㣺";
	cin >> a;
	cout << "�����������յ㣺";
	cin >> b;
	cout << "������ȷּ�������";
	cin >> n;
	cout << "��������㴦y��ֵ��";
	cin >> y_init;
	Runge_Kutta(a, b, n, y_init);
	return 0;
}*/