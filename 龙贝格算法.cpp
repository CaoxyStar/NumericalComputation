#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

double integrand_formula(double x);   //��������
void Romberg(double start, double end, double theta);    //�������㷨
double compute_Tk(double tk, int start, int end, int i); //�������ι�ʽ

//ȡ���·�main����ע�ͼ��ɲ���ʹ��
/*
int main()
{
	double start, end, theta;
	cout << "������������ޣ�";
	cin >> start;
	cout << "������������ޣ�";
	cin >> end;
	cout << "������ض�����ޣ�";
	cin >> theta;
	Romberg(start, end, theta);
	return 0;
}*/


//��������
double integrand_formula(double x)
{
	return 4/(1+x*x);
}

//�������㷨
const int MAX = 10;
void Romberg(double start, double end, double theta)
{
	double y_start = integrand_formula(start);
	double y_end = integrand_formula(end);
	double Tk[MAX + 1][2];
	Tk[0][0] = (end - start) * (y_start + y_end) / 2;
	cout << Tk[0][0] << endl;
	for (int i = 1; i < MAX + 1; i++)
	{
		Tk[0][1] = compute_Tk(Tk[0][0], start, end, i);
		for (int j = 1; j < i + 1; j++)
			Tk[j][1] = (pow(4, j) * Tk[j - 1][1] - Tk[j - 1][0]) / (pow(4, j)-1);

		if (abs(Tk[i][1] - Tk[i - 1][0]) < theta)
		{
			cout<<setprecision(7) << "����ֵΪ"<<Tk[i][1] <<endl;
			return;
		}
		
		for (int k = 0; k < i + 1; k++)
		{
			Tk[k][0] = Tk[k][1];
			cout << fixed << setprecision(6) << Tk[k][0] << "\t";
		}

		cout << endl;
	}
	cout << "����������δ�ҵ����㾫��Ҫ��Ľ���ֵ" << endl;
}

//�������ι�ʽ
double compute_Tk(double tk,int start,int end,int i)
{
	double value_plus = 0;
	for (int j = 1; j < pow(2, i - 1) + 1; j++)
		value_plus += integrand_formula(start + (2 * double(j) - 1) * (end - start) / pow(2, i));
	return tk / 2 + (end - start) * value_plus / pow(2, i);
}
