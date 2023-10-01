#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//求根函数
double SecantFunction(double x)
{
	return pow(x, 4) - 3 * x + 1;
}

//正割法
void Secant(double x_0, double x_1, double sigma1, double sigma2)
{
	double temp,res;
	int n = 2;
	cout << "0\t" << x_0 << "\t" << SecantFunction(x_0) << endl;
	cout << "1\t" << x_1 << "\t" << SecantFunction(x_1) << endl;
	while (1)
	{
		temp = x_1 - SecantFunction(x_1) * (x_1 - x_0) / (SecantFunction(x_1) - SecantFunction(x_0));
		res = SecantFunction(temp);
		//残差精度判断
		if (abs(res) < sigma2)
		{
			cout << fixed << setprecision(8) << "满足残差要求的根为" << temp << "，其函数返回值为" << res;
			cout << "，为第" << n << "个根" << endl;
			return;
		}
		//根误差精度判断
		if (abs(temp - x_1) < sigma1)
		{
			cout << fixed << setprecision(8) << "满足根误差精度要求的根为" << temp << "，其函数返回值为" << res;
			cout << "，为第" << n << "个根" << endl;
			return;
		}

		//中间量输出
		cout << n<<"\t" << temp << "\t" << SecantFunction(temp) << endl;

		n = n + 1;
		x_0 = x_1;
		x_1 = temp;
	}
}

//取消下方注释即可测试使用
/*
int main()
{
	double x_0, x_1, sigma1, sigma2;
	cout << "请输入根x_0:";
	cin >> x_0;
	cout << "请输入根x_1:";
	cin >> x_1;
	cout << "请输入根误差精度要求：";
	cin >> sigma1;
	cout << "请输入残差精度要求：";
	cin >> sigma2;
	Secant(x_0, x_1, sigma1, sigma2);
	return 0;
}*/