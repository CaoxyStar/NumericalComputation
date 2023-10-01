#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

vector<vector<double>> Matrix_multiplication(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2);   //矩阵乘法
vector<vector<double>> Matrix_transpose(vector<vector<double>> matrix);     //矩阵转置
void LeastSquare_HandInput();      //手动输入测试函数
void LeastSquare_FileInput();      //文件输入测试函数
void Doolittle_analysis(vector<vector<double>>& matrix_A, double x[], vector<vector<double>>b, int n);        //杜利特尔分解求解方程组

//去掉下方main函数注释即可开始测试，请将手动输入与文件输入分开测试
/*
int main()
{
	//LeastSquare_HandInput();
	LeastSquare_FileInput();
	return 0;
}*/


//读取文件数据测试函数
void LeastSquare_FileInput()
{
	ifstream inFile;
	inFile.open("LeastMulti_testingFile.txt");
	string str;
	getline(inFile, str);
	int m;
	inFile >> m;
	inFile.get();
	getline(inFile, str);
	vector<double>x(m);
	vector<vector<double>>y(m);
	double* weight = new double[m];
	for (int i = 0; i < m; i++)
	{
		inFile >> x[i];
		y[i].resize(1);
		inFile >> y[i][0];
		inFile >> weight[i];
	}
	inFile.get();
	getline(inFile, str);
	int n;
	inFile >> n;
	inFile.close();

	vector<vector<double>>matrix_C;
	vector<double>matrix_line(n + 1, 1);
	for (int i = 0; i < m; i++)                   //由x得C矩阵
	{
		for (int j = 1; j < n + 1; j++)
			matrix_line[j] = pow(x[i], j);
		matrix_C.push_back(matrix_line);
	}
	vector<vector<double>>C_transpose = Matrix_transpose(matrix_C);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n + 1; j++)
			C_transpose[j][i] *= weight[i];
	}
	vector<vector<double>>matrix_A = Matrix_multiplication(C_transpose, matrix_C);   //求得方程组系数矩阵A
	vector<vector<double>>vector_b = Matrix_multiplication(C_transpose, y);          //求得方程组常向量b
	
	//输出
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			cout << matrix_A[i][j] << " ";
		}
		cout << vector_b[i][0] << endl;
	}

	double* parameter = new double[n + 1];
	Doolittle_analysis(matrix_A, parameter, vector_b, n + 1);               //求得函数系数parameter
	ofstream outFile;
	outFile.open("LeastMulti_testingFile.txt", ios::out | ios::app);
	for (int i = 0; i < n + 1; i++)
		outFile << parameter[i] << " ";
	outFile << endl;
	outFile.close();
	cout << "Done!" << endl;
}

//手动输入测试函数
void LeastSquare_HandInput()
{
	int m, n;
	cout << "请输入已知拟合点个数：";
	cin >> m;
	vector<double>x(m);
	vector<vector<double>>y(m);
	double* weight = new double[m];
	cout << "###请输入已知点###" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << "x" << i + 1 << "=";
		cin >> x[i];
		y[i].resize(1);
		cout << "y" << i + 1 << "=";
		cin >> y[i][0];
	}
	cout << "请输入是否加权（若加权请输入1，不加权输入0）：";
	int choice;
	cin >> choice;
	if (choice)
	{
		cout << "请输入各点加权系数（以空格分隔）：" << endl;
		for (int i = 0; i < m; i++)
			cin >> weight[i];
	}
	cout << "请输入拟合曲线项最高次数：";
	cin >> n;
	vector<vector<double>>matrix_C;
	vector<double>matrix_line(n + 1, 1);
	for (int i = 0; i < m; i++)                  //由x得到C矩阵
	{
		for (int j = 1; j < n + 1; j++)
			matrix_line[j] = pow(x[i], j);
		matrix_C.push_back(matrix_line);
	}
	vector<vector<double>>C_transpose = Matrix_transpose(matrix_C);
	//若加权，处理转置后的矩阵
	if (choice)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n + 1; j++)
				C_transpose[j][i] *= weight[i];
		}
	}
	vector<vector<double>>matrix_A = Matrix_multiplication(C_transpose, matrix_C);  //求得方程组系数矩阵A
	vector<vector<double>>vector_b = Matrix_multiplication(C_transpose, y);			//求得方程组常向量b
	double* parameter = new double[n+1];
	Doolittle_analysis(matrix_A, parameter, vector_b, n+1);   //利用杜利特尔分解求方程组得函数系数parameter
	for (int i = 0; i < n + 1; i++)
		cout << parameter[i] << endl;
}

//矩阵乘法
vector<vector<double>> Matrix_multiplication(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2)
{
	int line = matrix_1.size();
	int range = matrix_2[0].size();
	int n = matrix_2.size();
	vector<vector<double>>matrix_res;
	vector<double>line_res(range);
	double temp;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < range; j++)
		{
			temp = 0;
			for (int k = 0; k < n; k++)
			{
				temp += matrix_1[i][k] * matrix_2[k][j];
			}
			line_res[j] = temp;
		}
		matrix_res.push_back(line_res);
	}
	return matrix_res;
}

//矩阵转置
vector<vector<double>> Matrix_transpose(vector<vector<double>> matrix)
{
	int line = matrix[0].size();
	int range = matrix.size();
	vector<vector<double>>matrix_new(line);
	for (int i = 0; i < line; i++)
		matrix_new[i].resize(range);
	for (int i = 0; i < line; i++)
		for (int j = 0; j < range; j++)
			matrix_new[i][j] = matrix[j][i];
	return matrix_new;
}

//杜利特尔分解求方程组
void Doolittle_analysis(vector<vector<double>>& matrix_A, double x[], vector<vector<double>>b, int n)
{
	double* y = new double[n];
	for (int i = 0; i < n - 1; i++)         //矩阵分解
		for (int j = i + 1; j < n; j++)
		{
			matrix_A[j][i] = matrix_A[j][i] / matrix_A[i][i];
			for (int k = i + 1; k < n; k++)
				matrix_A[j][k] = matrix_A[j][k] - matrix_A[j][i] * matrix_A[i][k];
		}
	for (int i = 0; i < n; i++)            //求解中间向量y
	{
		y[i] = b[i][0];
		for (int j = 0; j < i; j++)
			y[i] -= y[j] * matrix_A[i][j];
	}
	for (int i = n - 1; i >= 0; i--)         //求解方程根
	{
		for (int j = i + 1; j < n; j++)
			y[i] -= x[j] * matrix_A[i][j];
		x[i] = y[i] / matrix_A[i][i];
	}
	delete y;
}