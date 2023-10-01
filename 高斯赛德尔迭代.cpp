#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

//牛顿赛德尔迭代法
void GS_iteration(vector<vector<double>>matrix_a, double* x, double* b, double sigma, int N_max)
{
	double temp1, temp2, x_new, errorMax;
	int n = matrix_a.size();
	for (int k = 0; k < N_max; k++)
	{
		errorMax = 0;
		for (int i = 0; i < n; i++)
		{
			temp1 = 0;
			temp2 = 0;
			for (int j = 0; j < i; j++)
				temp1 += matrix_a[i][j] * x[j];
			for (int j = i + 1; j < n; j++)
				temp2 += matrix_a[i][j] * x[j];
			x_new = (b[i] - temp1 - temp2) / matrix_a[i][i];
			if (abs(x_new - x[i]) > errorMax)
				errorMax = abs(x_new - x[i]);
			x[i] = x_new;
		}
		for (int i = 0; i < n; i++)
			cout << fixed << setprecision(4) << x[i] << " ";
		cout << "    ////    error: " << errorMax << endl;
		if (errorMax < sigma)
		{
			cout << "迭代" << k + 1 << "次得到满足精度要求的解如下：" << endl;
			for (int i = 0; i < n; i++)
				cout<<fixed<< setprecision(4)<< x[i] << " ";
			return;
		}
	}
	cout << "在给定迭代次数内未找到满足精度要求的解！" << endl;
}

//取消下方注释即可测试使用
/*
int main()
{
	ifstream inFile;
	inFile.open("GSiteration_testingFile.txt");
	string str;
	int m;
	getline(inFile, str);
	inFile >> m;
	inFile.get();
	getline(inFile, str);
	vector<vector<double>>matrix_A;
	vector<double>vec(m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
			inFile >> vec[j];
		matrix_A.push_back(vec);
	}
	inFile.get();
	getline(inFile, str);
	double* x = new double[m];
	for (int i = 0; i < m; i++)
		inFile >> x[i];
	inFile.get();
	getline(inFile, str);
	double* b = new double[m];
	for (int i = 0; i < m; i++)
		inFile >> b[i];
	inFile.get();
	getline(inFile, str);
	double sigma;
	inFile >> sigma;
	inFile.get();
	getline(inFile, str);
	int N_max;
	inFile >> N_max;
	inFile.close();
	GS_iteration(matrix_A, x, b, sigma, N_max);
	return 0;
}
*/
