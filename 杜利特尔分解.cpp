#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void Doolittle_analysis(vector<vector<double>>& matrix_A, double x[], double b[], int n);
void Doolittle_handInput();
void Doolittle_fileInput();


//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	//Doolittle_handInput();    //�ֶ�����
	Doolittle_fileInput();    //�ļ�����
	system("pause");
	return 0;
}*/

//LU�ֽ��㷨
void Doolittle_analysis(vector<vector<double>> &matrix_A, double x[], double b[],int n)
{
	double* y = new double[n];
	for (int i = 0; i < n - 1; i++)         //����ֽ�
		for (int j = i + 1; j < n; j++)
		{
			matrix_A[j][i] = matrix_A[j][i] / matrix_A[i][i];
			for (int k = i + 1; k < n; k++)
				matrix_A[j][k] = matrix_A[j][k] - matrix_A[j][i] * matrix_A[i][k];
		}

	//���LU�ֽ�����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matrix_A[i][j] << "\t";
		cout << endl;
	}
	cout << "**************" << endl;

	for (int i = 0; i < n; i++)            //����м�����y
	{
		y[i] = b[i];
		for (int j = 0; j < i; j++)
			y[i] -= y[j] * matrix_A[i][j];
	}

	//����м���y
	for (int i = 0; i < n; i++)
	{
		cout << y[i] << "\t";
	}
	cout << "**************" << endl;

	for (int i = n - 1; i >= 0; i--)         //��ⷽ�̸�
	{
		for (int j = i + 1; j < n; j++)
			y[i] -= x[j] * matrix_A[i][j];
		x[i] = y[i] / matrix_A[i][i];
	}
	delete y;
}

//�ֶ�����
void Doolittle_handInput()
{
	cout << "���������������ȣ�";
	int n;
	cin >> n;
	vector<vector<double>>matrix_A;
	vector<double>line(n);
	double* x = new double[n];
	double* b = new double[n];
	for (int i = 0; i < n; i++)
	{
		cout << "�������������A��" << i + 1 << "�У���Ԫ���Կո��������";
		for (int j = 0; j < n; j++)
			cin >> line[j];
		matrix_A.push_back(line);
	}
	cout << "����������b��Ԫ�ؼ��Կո��������";
	for (int i = 0; i < n; i++)
		cin >> b[i];
	Doolittle_analysis(matrix_A, x, b, n);
	for (int i = 0; i < n; i++)
		cout <<"x"<<i+1<<"="<< x[i] << endl;
}

//�ļ�����
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