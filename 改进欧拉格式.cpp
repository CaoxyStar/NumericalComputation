#include<iostream>
#include<iomanip>
using namespace std;

//微分函数
double Euler_formula(double x,double y)
{
	return -y;
}

//欧拉格式
void Euler_Scheme(double x_begin,double x_end,int n,double y_start)
{
	double h = (x_end - x_begin) / n;
	double y1, y2;
	cout << "各节点近似解为：" << endl;
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

//取消下方注释即可测试使用
/*
int main()
{
	double x_begin, x_end, y_start;
	int n;
	cout << "请输入区间起点：";
	cin >> x_begin;
	cout << "请输入区间终点：";
	cin >> x_end;
	cout << "请输入等分间距个数：";
	cin >> n;
	cout << "请输入起点处y的值：";
	cin >> y_start;
	Euler_Scheme(x_begin, x_end, n, y_start);
	return 0;
}*/