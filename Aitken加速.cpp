#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//加速求根函数
double Acc_func(double x)
{
	return exp(-x);
}

//加速迭代Steffensen
void AitkenAcc(double x, double sigma,int N_max)
{
	double x1, x2,temp;
	for(int i =0;i<N_max;i++)
	{
		x1 = Acc_func(x);
		x2 = Acc_func(x1);
		temp = x - pow(x1 - x, 2) / (x2 - 2 * x1 + x);
		cout << i << "\t";
		cout<< fixed << setprecision(8) << x << "\t" << x1 << "\t" << x2 << endl;
		if (abs(x1 - x) < sigma)
		{
			cout << fixed << setprecision(8) << "第" << i+1 << "次迭代得到满足精度要求的根为" << temp << endl;
			return;
		}
		x = temp;
	}
	cout << "给定迭代次数内为找到满足精度要求的近似根！" << endl;
}

//取消下方注释即可测试使用
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
	AitkenAcc(x, sigma, N_max);
	return 0;
}*/