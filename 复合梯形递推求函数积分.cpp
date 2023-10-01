#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

double integrand(double x);            //��������,������Ҫ�޸�
void CompoundTrapezoidal(double start, double end, double theta, int k);   //�������ι�ʽ�����

//ȡ��main����ע�ͼ���ʹ��
/*
int main()
{
	double start, end, theta;
	int k;            
	cout << "������������ޣ�";
	cin >> start;
	cout << "������������ޣ�";
	cin >> end;
	cout << "������ض�����ޣ�";
	cin >> theta;
	cout << "�����������ִ�����";
	cin >> k;
	CompoundTrapezoidal(start, end, theta, k);
	return 0;
}*/

//�������ι�ʽ�����
void CompoundTrapezoidal(double start, double end, double theta, int k)
{
	double y_start = integrand(start);
	double y_end = integrand(end);
	double Tk_1 = (end - start) * (y_start + y_end) / 2;
	cout << "n=1   T=" << Tk_1 << endl;
	double Tk;
	for (int i = 1; i < k+1; i++)
	{
		double value_plus = 0;
		for (int j = 1; j < pow(2, i - 1) + 1; j++)
			value_plus += integrand(start + (2 * double(j) - 1) * (end - start) / pow(2, i));
		Tk = Tk_1 / 2 + (end - start) * value_plus / pow(2, i);
		if (abs(Tk - Tk_1) < 3*theta)
		{
			cout << fixed << setprecision(8) <<"���㾫��Ҫ��ĵĽ���ֵΪ" <<Tk <<",��"<< (int)pow(2, i) <<"�ȷֵõ�"<< endl;
			return;
		}
		Tk_1 = Tk;
		cout << "n="<<(int)pow(2,i)<<"   T=" << Tk_1 << endl;
	}
	cout<<setprecision(8) << "����������δ�ҵ����㾫��Ҫ��Ľ���ֵ,�����ִ������ý���ֵΪ"<<Tk << endl;
	return;
}

//��������
double integrand(double x)
{
	return 4/(1+x*x);
}