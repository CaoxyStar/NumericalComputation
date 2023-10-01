#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//迭代函数
double Iteration_function(double x)
{
	return log(x+2);
}

//迭代法求近似根
void Iteration(double x, double sigma, int N_max)
{
	double temp;
	for (int i = 0; i < N_max; i++)
	{
		temp = Iteration_function(x);
		cout << setprecision(8) << x << endl;
		//精度验证
		if (abs(temp - x) < sigma)
		{
			cout << "第" << i << "次迭代得到满足精度要求的根为：";
			cout << setprecision(8) << x << endl;
			cout << "此时原函数的绝对值为：" << abs(Iteration_function(x) - x) << endl;
			return;
		}
		x = temp;
	}
	cout << "给定迭代次数" << N_max << "次还没有得到满足精度要求的信息！" << endl;
}

//取消main函数注释即可开始测试
/*
int main()
{
	double x, sigma;
	int N_max;
	cout << "请输入初值：";
	cin >> x;
	cout << "请输入精度要求：";
	cin >> sigma;
	cout << "请输入最大迭代次数：";
	cin >> N_max;
	Iteration(x, sigma, N_max);
	return 0;
}*/