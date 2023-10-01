#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

void Chasing_handInput();
void Chasing_fileInput();
double* Chasing(double a[], double b[], double c[], double res[], int n);

//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	//Chasing_handInput();  //�ֶ�����
	Chasing_fileInput();  //�ļ�����
	return 0;
}*/

//׷���㷨
double* Chasing(double a[], double b[], double c[], double res[], int n)
{
	double* y = new double[n];
	double* x = new double[n];
	for (int i = 0; i < n-1; i++)   //����ֽ�
	{
		c[i] = c[i] / b[i];
		b[i + 1] -= a[i] * c[i];
	}

	//����м���
	cout << "a: ";
	for (int i = 0; i < n - 1; i++)
		cout << a[i] << "\t";
	cout << endl;
	cout << "b: ";
	for (int i = 0; i < n; i++)
		cout << b[i] << "\t";
	cout << endl;
	cout << "c: ";
	for (int i = 0; i < n - 1; i++)
		cout << c[i] << "\t";
	cout << endl;
	cout << "**************" << endl;


	y[0] = res[0]/b[0];          //��y����
	for (int i = 1; i < n; i++)
		y[i] = (res[i] - a[i-1]*y[i - 1]) / b[i];

	//���y
	for (int i = 0; i < n; i++)
		cout << y[i] << "\t";
	cout << endl;
	cout << "*****************" << endl;


	x[n - 1] = y[n - 1];        //��x����
	for (int i = n - 2; i >= 0; i--)
		x[i] = y[i] - c[i] * x[i + 1];
	return x;
}

//�ֶ�����
void Chasing_handInput()
{
	cout << "### ׷�Ϸ���ⷽ�̸� ###" << endl;
	cout << "���������������ȣ�";
	int n;
	cin >> n;
	double* a = new double[n - 1];
	double* b = new double[n];
	double* c = new double[n - 1];
	double* res = new double[n];
	double* x = new double[n];
	cout << "����������a��Ԫ�ؼ��Կո�ָ�����";
	for (int i = 0; i < n - 1; i++)
		cin >> a[i];
	cout << "����������b��Ԫ�ؼ��Կո�ָ�����";
	for (int i = 0; i < n; i++)
		cin >> b[i];
	cout << "����������c��Ԫ�ؼ��Կո�ָ�����";
	for (int i = 0; i < n - 1; i++)
		cin >> c[i];
	cout << "����������res��Ԫ�ؼ��Կո�ָ�����";
	for (int i = 0; i < n; i++)
		cin >> res[i];
	x = Chasing(a, b, c, res, n);
	for (int i = 0; i < n; i++)
		cout << "x" << i + 1 << "=" << x[i] << endl;
	delete a, b, c, res, x;
}

//�ļ�����
void Chasing_fileInput()
{
	string str;
	int n;
	ifstream inFile;
	inFile.open("Chasing_testingFile.txt");
	getline(inFile, str);
	inFile >> n;
	inFile.get();
	double* a = new double[n - 1];
	double* b = new double[n];
	double* c = new double[n - 1];
	double* res = new double[n];
	double* x = new double[n];
	getline(inFile, str);
	for (int i = 0; i < n - 1; i++)
		inFile >> a[i];
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n; i++)
		inFile >> b[i];
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n - 1; i++)
		inFile >> c[i];
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n; i++)
		inFile >> res[i];
	inFile.close();
	x = Chasing(a, b, c, res, n);
	ofstream outFile;
	outFile.open("Chasing_testingFile.txt", ios::out | ios::app);
	for (int i = 0; i < n; i++)
		outFile << "x" << i + 1 << "=" << x[i] << endl;
	outFile.close();
	delete a, b, c, res, x;
	cout << "Done!" << endl;
}