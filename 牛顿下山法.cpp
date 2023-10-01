#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

//求根函数
double objectFunction(double x)
{
	return pow(x,3)-x-1;
}

//求根函数导函数
double derivativeFunction(double x)
{
	return 3*x*x-1;
}

//牛顿下山法
void Newton_Gradient(double x, double sigma1, double sigma2,double sigma3)
{
	double returnValue1, returnValue2, temp, x1;
	int n = 1;
	double t = 1;
	cout << "n=0\t\tx=" << x << "\tf(x)=" << objectFunction(x) << endl;
	while(1)
	{
		returnValue1 = objectFunction(x);
		temp = derivativeFunction(x);
		//导函数合理性判断
		if (temp == 0)
		{
			cout << "导函数返回值为0，计算中断！" << endl;
			return;
		}
		x1 = x - t * returnValue1 / temp;
		returnValue2 = objectFunction(x1);
		//残差精度判读
		if (abs(returnValue2) <= sigma2)
		{
			cout <<setprecision(7)<< "满足残差精度要求的根为" << x1 << "，函数值为" << returnValue2;
			cout << "迭代次数为" << n << endl;
			return;
		}
		if (abs(returnValue2) < abs(returnValue1))
		{
			//根误差精度判断
			if (abs(x1 - x) < sigma1)
			{
				cout << fixed<<setprecision(6) << "满足根误差精度要求精度要求的根为" << x1 << "，函数值为" << returnValue2;
				cout << "迭代次数为" << n << endl;
				return;
			}
			//中间量输出
			cout << "n=" << n << "\tt=" << t << "\tx=" << x1 << "\tf(x)=" << returnValue2 << endl;

			x = x1;
			n = n + 1;
			t = 1;
			continue;
		}
		else               //下山因子更新
		{
			if (t < sigma3)
			{
				cout << "t值已低于下山因子下界，结算中断！" << endl;
				return;
			}
			t = t / 2;
		}
	}

}

//取消下方注释即可测试使用
/*
int main()
{
	double x, sigma1, sigma2, sigma3;
	cout << "请输入初值：";
	cin >> x;
	cout << "请输入近似根精度要求：";
	cin >> sigma1;
	cout << "请输入残差精度要求：";
	cin >> sigma2;
	cout << "请输入下山因子下界：";
	cin >> sigma3;
	Newton_Gradient(x, sigma1,sigma2,sigma3);
	return 0;
}*/

