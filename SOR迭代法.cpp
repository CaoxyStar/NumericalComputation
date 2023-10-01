#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;


//超松弛迭代法
void SOR_iteration(vector<vector<double>>matrix_a, double* x, double* b, double w,double sigma, int N_max)
{
	double temp, errorMax;
	int n = matrix_a.size();
	for (int k = 0; k < N_max; k++)
	{
		errorMax = 0;
		for (int i = 0; i < n; i++)
		{
			temp = 0;
			for (int j = 0; j < n; j++)
				temp += matrix_a[i][j] * x[j];
			temp = b[i] - temp;
			if (abs(temp) > errorMax)
				errorMax = abs(temp);
			x[i] = x[i] + w * temp / matrix_a[i][i];
		}
		if (errorMax < sigma)
		{
			cout << "迭代" << k + 1 << "次得到满足精度要求的解如下：" << endl;
			for (int i = 0; i < n; i++)
				cout << fixed << setprecision(8) << x[i] << " ";
			cout << "   ///    error: " << errorMax << endl;
			return;
		}
		for (int i = 0; i < n; i++)
			cout << fixed << setprecision(8) << x[i] << " ";
		cout <<"   ///    error: "<<errorMax <<endl;
	}
	cout << "在给定迭代次数内未找到满足精度要求的解！" << endl;
}

//取消下方注释即可测试使用
/*
int main()
{
	ifstream inFile;
	inFile.open("SORiteration_testingFile.txt");
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
	inFile.get();
	getline(inFile, str);
	double w;
	inFile >> w;
	inFile.close();
	SOR_iteration(matrix_A, x, b, w,sigma, N_max);
	return 0;
}*/