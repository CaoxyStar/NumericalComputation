#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

//�ſɱȵ�����
int Jacobi_Iteration(vector<vector<double>>matrix_A, double* x,double* x1,double* b, double sigma,int m)
{
	double maxium;
	double temp;
	int n = 1;
	while(1)
	{
		maxium = 0;
		//����x1����
		for (int i = 0; i < m; i++)
		{
			temp = 0;
			for (int j = 0; j < m; j++)
				temp += matrix_A[i][j] * x[j];
			temp -= matrix_A[i][i] * x[i];
			x1[i] = (b[i] - temp) / matrix_A[i][i];
			if (abs(x1[i] - x[i]) > maxium)
				maxium = abs(x1[i] - x[i]);
		}
		//����Ҫ���ж�
		if (maxium < sigma)
		{
			cout << maxium << endl;
			return n;
		}
			
		//x��������
		for (int i = 0; i < m; i++)
			x[i] = x1[i];
		for (int i = 0; i < m; i++)
			cout << fixed << setprecision(4) << x1[i] << " ";
		cout << "     ////////   error:" << maxium;
		cout << endl;
		n += 1;
	}
}
//ȡ���·�ע�ͣ���Jacobi_testingFile.txt�ļ���д�����ݼ��ɲ���
/*
int main()
{
	ifstream inFile;
	inFile.open("Jacobi_testingFile.txt");
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
	double* x1 = new double[m];
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
	inFile.close();
	int n = Jacobi_Iteration(matrix_A, x, x1, b,sigma, m);
	ofstream outFile;
	outFile.open("Jacobi_testingFile.txt", ios::out | ios::app);
	outFile << "����" << n << "�κ�õ����㾫��Ҫ��ĸ�����Ϊ��";
	for (int i = 0; i < m; i++)
		outFile << x1[i] << " ";
	outFile << endl;
	outFile.close();
	cout << "Done!" << endl;
	return 0;
}*/

