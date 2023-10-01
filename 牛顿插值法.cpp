#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void Newton_Hand_Input(); //手动测试函数
void Newton_File_Input(); //读取文件测试函数
int Get_Midpoint(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //分段低次插值获取插值点
double Newton_Interpolation_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿向前插值
double Newton_Interpolation_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿向后插值
double Newton_Interpolation(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //牛顿基本插值


//去掉下方main函数注释即可开始测试，请将手动输入与读取文件分开测试
/*
int main()
{
	//Newton_File_Input();     //文件输入测试
	Newton_Hand_Input();    //手动输入测试
	return 0;
}*/

//分段低次插值选取插值点函数
int Get_Midpoint(const double reference_x[], const double reference_y[], int arrsize, int n, double x)     
{
	if (n == 2)    //线性插值
	{
		for (int i = 0; i < arrsize; i++)
		{
			if ((reference_x[i] <= x) and (reference_x[i + 1] > x))
			{
				return i;
			}
		}
		cout << "Please enter the number which in range." << endl;
	}
	else if (n == 3)    //抛物插值
	{
		if ((x < (reference_x[1] + reference_x[2]) / 2) and (x>=reference_x[0]))
			return 1;
		else if ((x >=( reference_x[arrsize-2]+reference_x[arrsize-3])/2) and (x<=reference_x[arrsize-1]))
			return arrsize - 2;
		else
		{
			for (int i = 1; i < arrsize-1; i++)
			{
				if ((x >= (reference_x[i - 1] + reference_x[i]) / 2) and (x < (reference_x[i] + reference_x[i + 1]) / 2))
					return i;
			}
			cout << "Please enter the number which in range." << endl;
		}
	}
}

//牛顿向前插值
double Newton_Interpolation_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x)    
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2) //线性插值
	{
		double h = reference_x[midpoint + 1] - reference_x[midpoint];
		double t = (x - reference_x[midpoint]) / h;
		double distance_1 = reference_y[midpoint + 1] - reference_y[midpoint];
		return reference_y[midpoint] + t * distance_1;
	}
	if (n == 3)    //抛物插值
	{
		double h = reference_x[midpoint] - reference_x[midpoint - 1];
		double t = (x - reference_x[midpoint - 1]) / h;
		double distance_1 = reference_y[midpoint] - reference_y[midpoint - 1];
		double distance_2 = reference_y[midpoint + 1] - reference_y[midpoint] - distance_1;
		return reference_y[midpoint - 1] + t * distance_1 + t * (t - 1) * distance_2 / 2;
	}
}

//牛顿向后插值
double Newton_Interpolation_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x)  
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2)     //线性插值
	{
		double h = reference_x[midpoint + 1] - reference_x[midpoint];
		double t = (x - reference_x[midpoint+1]) / h;
		double distance_1 = reference_y[midpoint + 1] - reference_y[midpoint];
		return reference_y[midpoint+1] + t * distance_1;
	}
	if (n == 3)     //抛物插值
	{
		double h = reference_x[midpoint] - reference_x[midpoint - 1];
		double t = (x - reference_x[midpoint + 1]) / h;
		double distance_1 = reference_y[midpoint+1] - reference_y[midpoint];
		double distance_2 = distance_1 - (reference_y[midpoint] - reference_y[midpoint - 1]);
		return reference_y[midpoint + 1] + t * distance_1 + t * (t + 1) * distance_2 / 2;
	}
}

//牛顿基本插值
double Newton_Interpolation(const double reference_x[], const double reference_y[], int arrsize, int n, double x)    
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2)     //线性插值
	{
		double k = (reference_y[midpoint + 1] - reference_y[midpoint]) / (reference_x[midpoint + 1] - reference_x[midpoint]);
		return reference_y[midpoint] + k * (x - reference_x[midpoint]);
	}
	if (n == 3)     //抛物插值
	{
		double k1 = (reference_y[midpoint] - reference_y[midpoint - 1]) / (reference_x[midpoint] - reference_x[midpoint - 1]);
		double k2 = (reference_y[midpoint + 1] - reference_y[midpoint]) / (reference_x[midpoint + 1] - reference_x[midpoint]);
		double f1 = (k2 - k1) / (reference_x[midpoint + 1] - reference_x[midpoint - 1]);
		return reference_y[midpoint - 1] + k1 * (x - reference_x[midpoint - 1]) + f1 * (x - reference_x[midpoint - 1]) * (x - reference_x[midpoint]);
	}
}

//手动输入测试函数
void Newton_Hand_Input()
{
	int arrsize; //插值点个数
	double x; //测试值
	double y; //返回值
	int n;  //选择线性插值还是抛物插值
	int choice; //选择哪种牛顿插值算法（向前、向后、基本）
	cout << "Please enter the size of list（已知点个数） : ";
	cin >> arrsize;
	cout << "please choose a algorithms : \n(enter 1 to Newton_Interpolation_front)\n(enter 2 to Newton_Interpolation_back)\n(enter 3 to Newton_Interpolation)" << endl;
	cin >> choice;
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
		cout << "线性插值输入2，抛物插值输入3：";
		cin >> n;
	}
	else
		cout << "Failure!" << endl;
	cout << "Please enter a number to estimate: ";
	cin >> x;
	switch (choice)   //选择向前、向后、基本插值
	{
	case 1: y = Newton_Interpolation_front(x_list, y_list, arrsize, n, x);
	case 2: y = Newton_Interpolation_back(x_list, y_list, arrsize, n, x);
	case 3: y = Newton_Interpolation(x_list, y_list, arrsize, n, x);
	}
	cout << "f(" << x << ")=" << y << endl;
}

//读取文件测试函数
void Newton_File_Input()
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
	switch (choice)
	{
	case 1: y = Newton_Interpolation_front(x_list, y_list, arrsize, n, x);
	case 2: y = Newton_Interpolation_back(x_list, y_list, arrsize, n, x);
	case 3: y = Newton_Interpolation(x_list, y_list, arrsize, n, x);
	}
	ofstream outFile;
	outFile.open("Newton_testingFile.txt", ios::out | ios::app);
	outFile << y << endl;
	outFile.close();
	cout << "Done!" << endl;
}