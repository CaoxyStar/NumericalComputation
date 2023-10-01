#include<iostream>
#include<iomanip>
using namespace std;

//΢�ֺ���
double Euler_formula(double x,double y)
{
	return -y;
}

//ŷ����ʽ
void Euler_Scheme(double x_begin,double x_end,int n,double y_start)
{
	double h = (x_end - x_begin) / n;
	double y1, y2;
	cout << "���ڵ���ƽ�Ϊ��" << endl;
	cout << "x\t\ty\t" << endl;
	cout << fixed << setprecision(7) << x_begin << "\t" << y_start << "\t" << endl;
	for (int i = 0; i < n; i++)
	{
		y1 = y_start + h * Euler_formula(x_begin, y_start);
		x_begin += h;
		y2 = y_start + h * Euler_formula(x_begin, y1);
		y_start = (y1 + y2) / 2;
		cout << fixed << setprecision(7) << x_begin << "\t" << y_start << "\t" << endl;
	}
}

//ȡ���·�ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double x_begin, x_end, y_start;
	int n;
	cout << "������������㣺";
	cin >> x_begin;
	cout << "�����������յ㣺";
	cin >> x_end;
	cout << "������ȷּ�������";
	cin >> n;
	cout << "��������㴦y��ֵ��";
	cin >> y_start;
	Euler_Scheme(x_begin, x_end, n, y_start);
	return 0;
}*/