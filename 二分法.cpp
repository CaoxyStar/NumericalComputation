#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//求根函数
double object_function(double x)
{
	return pow(x,6)-x-1;
}

//二分法
void myDichotomy(double a, double b, double sigma1, double sigma2, double N_max)
{
	double temp;
	double h;
	cout << "a=" << a << "\tb=" << b << "\t";
	for (int i = 1; i < N_max+1; i++)
	{
		temp = (a + b) / 2;
		cout << "x=" << temp << "\tf(x)="<<object_function(temp)<<endl;
		h = (b - a) / 2;
		if (abs(object_function(temp)) < sigma1 || h < sigma2)
		{
			cout << setprecision(7) << "第" << i << "次二分得到满足条件的近似根为" << temp;
			cout<<fixed<<setprecision(7)<<"，此时函数值为" << object_function(temp) << endl;
			return;
		}
		if (object_function(a) * object_function(temp) < 0)
			b = temp;
		else
			a = temp;
		cout << "a=" << a << "\tb=" << b << "\t";
	}
	cout << "分半" << N_max << "次没有得到符合精度要求的近似根。" << endl;
}

//取消下方main函数注释即可测试
/*
int main()
{
	double a, b, sigma1, sigma2;
	int N_max;
	cout << "请输入求根区间下限：";
	cin >> a;
	cout << "请输入求根区间上限：";
	cin >> b;
	cout << "请输入精度要求sigma1：";
	cin >> sigma1;
	cout << "请输入精度要求sigma2：";
	cin >> sigma2;
	cout << "请输入最大二分次数：";
	cin >> N_max;
	myDichotomy(a, b, sigma1, sigma2, N_max);
	return 0;
}*/