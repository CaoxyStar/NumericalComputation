#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//求根函数
double Function1(double x)
{
	return 3*x*x-exp(x);
}

//求根函数导函数
double Function2(double x)
{
	return 6*x-exp(x);
}

//牛顿迭代求解
void Newton_Iteration(double x, double sigma, int N_max)
{
	double temp1;      //导函数值
	double temp2;      //迭代后x新值
	cout << "0\t" << x << endl;
	for (int i = 1; i <= N_max; i++)
	{
		temp1 = Function2(x);
		//验证条件一
		if (temp1 == 0)
		{
			cout << "导函数为0，计算中断！" << endl;
			return;
		}
		temp2 = x - Function1(x) / temp1;
		//精度验证
		if (abs(temp2 - x) < sigma)
		{
			cout << fixed<<setprecision(5) << "方程根为" << temp2 << "，此时函数值等于" << Function1(temp2);
			cout<< "，迭代次数为" << i << endl;
			return;
		}
		x = temp2;
		cout << i << "\t" << x << endl;
	}
	cout << "给定最大迭代次数内未找到满足精度要求的根！" << endl;
	return;
}

//取消下方注释即可测试使用
/*
int main()
{
	double x, sigma;
	int N_max;
	cout << "请输入初值：";
	cin >> x;
	cout << "请输入最大迭代次数：";
	cin >> N_max;
	cout << "请输入精度要求：";
	cin >> sigma;
	Newton_Iteration(x, sigma, N_max);
	return 0;
}*/
