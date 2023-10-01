#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

void Newton_File();
void Newton_Input(); //手动测试函数
double Newton_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿向前插值
double Newton_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿向后插值
double Newton_base(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿基本插值


//去掉下方main函数注释即可开始测试，请将手动输入与读取文件分开测试
/*
int main()
{
	Newton_File();    //手动输入测试
	return 0;
}*/


//牛顿向前插值
double Newton_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[0];
	double h = reference_x[1] - reference_x[0];
	double t = (x - reference_x[0]) / h;
	cout << "t=" << t << endl;
	if (n >= 2)
	{
		double error1 = reference_y[1] - reference_y[0];
		cout << "一阶差分：" << error1 << endl;
		y += t * error1;
		if (n >= 3)
		{
			double error2 = (reference_y[2] - reference_y[1]) - error1;
			cout << "二阶差分：" << error2 << endl;
			y += t * (t - 1) * error2 / 2;
			if (n == 4)
			{
				double error3 = (reference_y[3] - reference_y[2]) - (reference_y[2] - reference_y[1]) - error2;
				cout << "三阶差分：" << error3 << endl;
				y += t * (t - 1) * (t - 2) * error3 / 6;
			}
		}
		return y;
	}
}

//牛顿向后插值
double Newton_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[arrsize-1];
	double h = reference_x[arrsize-1] - reference_x[arrsize-2];
	double t = (x - reference_x[arrsize-1]) / h;
	cout << "t=" << t << endl;
	if (n >= 2)
	{
		double error1 = reference_y[arrsize-1] - reference_y[arrsize-2];
		cout << "一阶差分：" << error1 << endl;
		y += t * error1;
		if (n >= 3)
		{
			double error2 = error1 - (reference_y[arrsize - 2] - reference_y[arrsize - 3]);
			cout << "二阶差分：" << error2 << endl;
			y += t * (t + 1) * error2 / 2;
			if (n == 4)
			{
				double error3 = error2 - ((reference_y[arrsize - 2] - reference_y[arrsize - 3]) - (reference_y[arrsize - 3] - reference_y[arrsize - 4]));
				cout << "三阶差分：" << error3 << endl;
				y += t * (t + 1) * (t + 2) * error3 / 6;
			}
		}
		return y;
	}
}

//牛顿基本插值
double Newton_base(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[0];
	if (n >= 2)
	{
		double error1 = (reference_y[1] - reference_y[0]) / (reference_x[1] - reference_x[0]);
		cout << "一阶差商：" << error1 << endl;
		y += error1 * (x - reference_x[0]);
		if (n >= 3)
		{
			double error2 = ((reference_y[2] - reference_y[1]) / (reference_x[2] - reference_x[1]) - error1) / 
				(reference_x[2] - reference_x[0]);
			cout << "二阶差商：" << error2 << endl;
			y += error2 * (x - reference_x[0]) * (x - reference_x[1]);
			if (n == 4)
			{
				double error1_temp = (reference_y[2] - reference_y[1]) / (reference_x[2] - reference_x[1]);
				double error2_temp = ((reference_y[3] - reference_y[2]) / (reference_x[3] - reference_x[2]) - error1_temp) / 
					(reference_x[3] - reference_x[1]);
				double error3 = (error2_temp - error2) / (reference_x[3] - reference_x[0]);
				cout << "三阶差商：" << error3 << endl;
				y += error3 * (x - reference_x[0]) * (x - reference_x[1]) * (x - reference_x[2]);
			}
		}
		return y;
	}
}

//手动输入测试函数
void Newton_Input()
{
	int arrsize; //插值点个数
	double x; //测试值
	double y; //返回值
	int n;  //选择线性插值、抛物、三次插值
	int choice; //选择哪种牛顿插值算法（向前、向后、基本）
	cout << "please choose a algorithms : \n(enter 1 to Newton_Interpolation_front)\n(enter 2 to Newton_Interpolation_back)\n(enter 3 to Newton_Interpolation)" << endl;
	cin >> choice;
	cout << "Please enter the size of list（已知点个数） : ";
	cin >> arrsize;
	double* x_list = new double[arrsize];
	double* y_list = new double[arrsize];
	for (int i = 0; i < arrsize; i++)   //输入点x、y坐标
	{
		cout << "Enter x and y :" << endl;
		cout << "x" << i + 1 << "=";
		cin >> x_list[i];
		cout << "y" << i + 1 << "=";
		cin >> y_list[i];
	}
	if (arrsize == 2)
	{
		n = arrsize;
	}
	else if (arrsize > 2) {
		cout << "线性插值输入2，抛物插值输入3，三次插值输入4：";
		cin >> n;
	}
	else
		cout << "Failure!" << endl;
	cout << "Please enter a number to estimate: ";
	cin >> x;
	switch (choice)   //选择向前、向后、基本插值
	{
	case 1: y = Newton_front(x_list, y_list, arrsize, n, x);
		break;
	case 2: y = Newton_back(x_list, y_list, arrsize, n, x);
		break;
	case 3: y = Newton_base(x_list, y_list, arrsize, n, x);
		break;
	}
	cout << "f(" << x << ")=" << y << endl;
}

//读取文件测试函数
void Newton_File()
{
	int arrsize;
	double x;
	double y;
	int n;
	int choice;
	string str;
	ifstream inFile;
	inFile.open("Newton_testingFile.txt");
	getline(inFile, str);
	inFile >> arrsize;
	inFile.get();
	double* x_list = new double[arrsize];
	double* y_list = new double[arrsize];
	getline(inFile, str);
	inFile >> n;
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < arrsize; i++)
	{
		inFile >> x_list[i];
		inFile >> y_list[i];
	}
	inFile.get();
	getline(inFile, str);
	inFile >> choice;
	inFile.get();
	getline(inFile, str);
	inFile >> x;
	inFile.get();
	inFile.close();
	switch (choice)   //选择向前、向后、基本插值
	{
	case 1: y = Newton_front(x_list, y_list, arrsize, n, x);
		break;
	case 2: y = Newton_back(x_list, y_list, arrsize, n, x);
		break;
	case 3: y = Newton_base(x_list, y_list, arrsize, n, x);
		break;
	}
	ofstream outFile;
	outFile.open("Newton_testingFile.txt", ios::out | ios::app);
	outFile << y << endl;
	outFile.close();
	cout << "Done!" << endl;
}