#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

double integrand(double x);            //被积函数,根据需要修改
void CompoundTrapezoidal(double start, double end, double theta, int k);   //复合梯形公式求积分

//取消main函数注释即可使用
/*
int main()
{
	double start, end, theta;
	int k;            
	cout << "请输入积分下限：";
	cin >> start;
	cout << "请输入积分上限：";
	cin >> end;
	cout << "请输入截断误差限：";
	cin >> theta;
	cout << "请输入最大二分次数：";
	cin >> k;
	CompoundTrapezoidal(start, end, theta, k);
	return 0;
}*/

//复合梯形公式求积分
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
			cout << fixed << setprecision(8) <<"满足精度要求的的近似值为" <<Tk <<",由"<< (int)pow(2, i) <<"等分得到"<< endl;
			return;
		}
		Tk_1 = Tk;
		cout << "n="<<(int)pow(2,i)<<"   T=" << Tk_1 << endl;
	}
	cout<<setprecision(8) << "给定次数内未找到满足精度要求的近似值,最大积分次数所得近似值为"<<Tk << endl;
	return;
}

//被积函数
double integrand(double x)
{
	return 4/(1+x*x);
}