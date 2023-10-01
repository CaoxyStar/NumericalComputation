#include<iostream>
#include<iomanip>
using namespace std;

//΢�ֺ���
double Adams_formula(double x, double y)
{
	return y-2*x/y;
}

//����ķ˹Ԥ��У������
void Adams(double a, double b, int n, double y_init)
{
	double h = (b - a) / n;
	double x = a;
	double y = y_init;
	double f[4];
	double K1, K2, K3, K4;
	f[0]= Adams_formula(x, y_init);
	cout << "x\ty" << endl;
	for (int i = 0; i < 3; i++)
	{
		K1 = Adams_formula(x, y);
		K2 = Adams_formula(x + h / 2, y + h * K1 / 2);
		K3 = Adams_formula(x + h / 2, y + h * K2 / 2);
		K4 = Adams_formula(x + h, y + h * K3);
		x += h;
		y += h * (K1 + 2 * K2 + 2 * K3 + K4) / 6;
		f[i + 1] = Adams_formula(x, y);
		cout << fixed << setprecision(4) << x << "\t" << y << endl;
	}
	double y_predict, f_predict;
	for (int i = 0; i < n - 3; i++)
	{
		y_predict = y + h * (55 * f[3] - 59 * f[2] + 37 * f[1] - 9 * f[0])/24;
		x += h;
		f_predict = Adams_formula(x, y_predict);
		y += h * (9 * f_predict + 19 * f[3] - 5 * f[2] + f[1])/24;
		for (int j = 0; j < 3; j++)
			f[j] = f[j + 1];
		f[3] = Adams_formula(x, y);
		cout << fixed << setprecision(4) << x << "\t" << y << endl;
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
	Adams(a, b, n, y_init);
	return 0;
}*/