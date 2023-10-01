#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

void Gaussion_File_Input();  //用于文件输入测试
void Gaussion_Hand_Input();  //用于手动输入测试
double Gaussian_elimination(int n, vector<vector<double>> &A_matric,double x_matric[], double b_matric[],double base); //列主元高斯消去法

//去掉下方main函数注释即可开始测试，请将手动输入与读取文件分开测试

int main()
{
	Gaussion_File_Input();   //文件输入数据测试
	//Gaussion_Hand_Input();   //测试手动输入时请将此行取消注释，同时注释上一行
	return 0;
}


//列主元高斯消去法
double Gaussian_elimination(int n, vector<vector<double>>& A_matric, double x_matric[], double b_matric[], double base)
{
	double det_a = 1;
	double max_num;
	int max_line;
	double temp_a;
	double temp_b;
	double change_num;
	for (int i = 0; i < n-1 ; i++)               //选出列最大主元
	{
		max_num = 0;
		max_line = 0;
		for (int j = i; j < n; j++)
		{
			if (abs(A_matric[j][i]) > max_num)
			{
				max_num = A_matric[j][i];
				max_line = j;
			}
		}

		//if (max_num < base)
			//return 0;

		if (max_line != i)                      //行交换
		{
			for (int k = i; k < n; k++)
			{
				temp_a = A_matric[i][k];
				A_matric[i][k] = A_matric[max_line][k];
				A_matric[max_line][k] = temp_a;
			}
			temp_b = b_matric[i];
			b_matric[i] = b_matric[max_line];
			b_matric[max_line] = temp_b;
			det_a *= -1;
		}

		for (int m = i + 1; m < n; m++)                 //消元
		{
			change_num = A_matric[m][i] / A_matric[i][i];
			for (int p = i; p < n; p++)
			{
				A_matric[m][p] -= A_matric[i][p] * change_num;
			}
			b_matric[m] -= b_matric[i] * change_num;
		}

		for (int m = 0; m < n; m++)
		{
			for (int k = 0; k < n; k++)
				cout << A_matric[m][k] << "\t";
			cout << b_matric[m] << endl;
		}
		cout << "****************************" << endl;
	}
	for (int i = 0; i < n; i++)                   //判断是否为奇异矩阵
	{
		det_a *= A_matric[i][i];
	}

	for (int i = n - 1; i >= 0; i--)                   //回代
	{
		double value = b_matric[i];
		for (int j = i + 1; j < n; j++)
			value -= x_matric[j] * A_matric[i][j];
		x_matric[i] = value / A_matric[i][i];
	}

	return det_a;
}


//手动输入
void Gaussion_Hand_Input()
{
	cout << "请输入方程个数：";
	int n;
	cin >> n;
	vector<vector<double>> A_matric;
	vector<double>a_line(n);
	double* x_matric = new double[n];
	double* b_matric = new double[n];
	cout << "#输入参数矩阵#" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "请输入参数矩阵第" << i + 1 << "行 (每个数之间空格隔开）：" << endl;
		for (int j = 0; j < n; j++)
		{
			cin >> a_line[j];
		}
		A_matric.push_back(a_line);
	}
	cout << "#输入值b矩阵(每个数之间空格隔开）#" << endl;
	for (int i = 0; i < n; i++)
		cin >> b_matric[i];
	double base = 0.001;
	double det = Gaussian_elimination(n, A_matric, x_matric, b_matric, base);
	/*if (det == 0)
	{
		cout << "det(A)接近0；方程无解！" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (abs(x_matric[i]) < base)
				cout << "x" << i + 1 << " = 0" << endl;
			else
				cout << "x" << i + 1 << " = " << x_matric[i] << endl;
		}
		cout << "det(A) = " << det << endl;
	}*/
	for (int i = 0; i < n; i++)
	{
		if (abs(x_matric[i]) < base)
			cout << "x" << i + 1 << " = 0" << endl;
		else
			cout << "x" << i + 1 << " = " << x_matric[i] << endl;
	}
	cout << "det(A) = " << det << endl;
}

//文件输入
void Gaussion_File_Input()
{
	ifstream inFile;
	inFile.open("Gaussion_testingFile.txt");
	string str;
	int n;
	getline(inFile, str);
	inFile >> n;
	inFile.get();
	vector<vector<double>> A_matric;
	vector<double>a_line(n);
	double* x_matric = new double[n];
	double* b_matric = new double[n];
	getline(inFile, str);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inFile >> a_line[j];
		}
		A_matric.push_back(a_line);
	}
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n; i++)
		inFile >> b_matric[i];
	inFile.get();
	inFile.close();
	double base = 0.001;
	double det = Gaussian_elimination(n, A_matric, x_matric, b_matric, base);
	ofstream outFile;
	outFile.open("Gaussion_testingFile.txt", ios::out | ios::app);
	for (int i = 0; i < n; i++)
	{
		if (abs(x_matric[i]) < base)
			outFile << "x" << i + 1 << " = 0" << endl;
		else
			outFile << "x" << i + 1 << " = " << x_matric[i] << endl;
	}
	outFile << "det(A) = " << det << endl;
	if (det == 0)
	{
		outFile << "det(A)接近0；方程无解！" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (abs(x_matric[i]) < base)
				outFile << "x" << i + 1 << " = 0" << endl;
			else
				outFile << "x" << i + 1 << " = " << x_matric[i] << endl;
		}
		outFile << "det(A) = " << det << endl;
	}
	cout << "Done!" << endl;
}