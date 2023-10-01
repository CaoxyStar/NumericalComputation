#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void Lagrange_Hand_Input(); //�ֶ�������Ժ���
void Lagrange_File_Input(); //��ȡ�ļ�Lagrange_testingFile.txt���Ժ���
double Lagrange_Interpolation(const double x_list[], const double y_list[], int arrsize, double x);

//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	Lagrange_Hand_Input();  //�ֶ�����
	//Lagrange_File_Input();  //��ȡ�ļ�����
	return 0;
}*/

//�������ղ�ֵ�㷨
double Lagrange_Interpolation(const double x_list[], const double y_list[], int arrsize, double x)
{
	double y = 0;
	double temp;
	for (int k = 0; k < arrsize; k++)
	{
		temp = y_list[k];
		for (int i = 0; i < arrsize; i++)
		{
			if (i == k)
				continue;
			else
				temp *= (x - x_list[i]) / (x_list[k] - x_list[i]);
		}
		y += temp;
	}
	return y;
}

//�ֶ�������Ժ���
void Lagrange_Hand_Input()
{
	int arrsize;
	double x;
	cout << "Please enter the size of list : ";
	cin >> arrsize;
	double* x_list = new double[arrsize];
	double* y_list = new double[arrsize];
	for (int i = 0; i < arrsize; i++)
	{
		cout << "Enter x and y :" << endl;
		cout << "x" << i + 1 << "=";
		cin >> x_list[i];
		cout << "y" << i + 1 << "=";
		cin >> y_list[i];
	}
	cout << "Please enter a number to estimate: ";
	cin >> x;
	double y = Lagrange_Interpolation(x_list, y_list, arrsize, x);
	cout << "f(" << x << ")=" << y << endl;
}


//��ȡ�ļ����Ժ���
void Lagrange_File_Input()
{
	int arrsize;
	double x;
	string str;
	ifstream inFile;
	inFile.open("Lagrange_testingFile.txt");
	getline(inFile,str);
	inFile >> arrsize;
	inFile.get();
	double* x_list = new double[arrsize];
	double* y_list = new double[arrsize];
	getline(inFile, str);
	for (int i = 0; i < arrsize; i++)
	{
		inFile >> x_list[i];
		inFile >> y_list[i];
	}
	inFile.get();
	getline(inFile, str);
	inFile >> x;
	inFile.get();
	inFile.close();
	double y = Lagrange_Interpolation(x_list, y_list, arrsize, x);
	ofstream outFile;
	outFile.open("Lagrange_testingFile.txt",ios::out|ios::app);
	outFile << y;   //���н����ӡ���ļ���
	outFile.close();
	cout << "Done!" << endl;
}