#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void Doolittle_analysis(vector<vector<double>>& matrix_A, double x[], double b[], int n);
void Doolittle_handInput();
void Doolittle_fileInput();


//去掉下方main函数注释即可开始测试，请将手动输入与读取文件分开测试
/*
int main()
{
	//Doolittle_handInput();    //手动输入
	Doolittle_fileInput();    //文件输入
	system("pause");
	return 0;
}*/

//LU分解算法
void Doolittle_analysis(vector<vector<double>> &matrix_A, double x[], double b[],int n)
{
	double* y = new double[n];
	for (int i = 0; i < n - 1; i++)         //矩阵分解
		for (int j = i + 1; j < n; j++)
		{
			matrix_A[j][i] = matrix_A[j][i] / matrix_A[i][i];
			for (int k = i + 1; k < n; k++)
				matrix_A[j][k] = matrix_A[j][k] - matrix_A[j][i] * matrix_A[i][k];
		}

	//输出LU分解后矩阵
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matrix_A[i][j] << "\t";
		cout << endl;
	}
	cout << "**************" << endl;

	for (int i = 0; i < n; i++)            //求解中间向量y
	{
		y[i] = b[i];
		for (int j = 0; j < i; j++)
			y[i] -= y[j] * matrix_A[i][j];
	}

	//输出中间量y
	for (int i = 0; i < n; i++)
	{
		cout << y[i] << "\t";
	}
	cout << "**************" << endl;

	for (int i = n - 1; i >= 0; i--)         //求解方程根
	{
		for (int j = i + 1; j < n; j++)
			y[i] -= x[j] * matrix_A[i][j];
		x[i] = y[i] / matrix_A[i][i];
	}
	delete y;
}

//手动输入
void Doolittle_handInput()
{
	cout << "请输入参数矩阵的秩：";
	int n;
	cin >> n;
	vector<vector<double>>matrix_A;
	vector<double>line(n);
	double* x = new double[n];
	double* b = new double[n];
	for (int i = 0; i < n; i++)
	{
		cout << "请输入参数矩阵A第" << i + 1 << "行（各元素以空格隔开）：";
		for (int j = 0; j < n; j++)
			cin >> line[j];
		matrix_A.push_back(line);
	}
	cout << "请输入向量b（元素间以空格隔开）：";
	for (int i = 0; i < n; i++)
		cin >> b[i];
	Doolittle_analysis(matrix_A, x, b, n);
	for (int i = 0; i < n; i++)
		cout <<"x"<<i+1<<"="<< x[i] << endl;
}

//文件输入
void Doolittle_fileInput()
{
	string str;
	ifstream inFile;
	inFile.open("Doolittle_testingFile.txt");
	getline(inFile, str);
	int n;
	inFile >> n;
	inFile.get();
	vector<vector<double>>matrix_A;
	vector<double>line(n);
	double* x = new double[n];
	double* b = new double[n];
	getline(inFile, str);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			inFile >> line[j];
		matrix_A.push_back(line);
	}
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n; i++)
		inFile >> b[i];
	inFile.close();
	Doolittle_analysis(matrix_A, x, b, n);
	ofstream outFile;
	outFile.open("Doolittle_testingFile.txt", ios::out | ios::app);
	for (int i = 0; i < n; i++)
		outFile << "x" << i + 1 << "=" << x[i] << endl;
	outFile.close();
	cout << "Done!" << endl;
}