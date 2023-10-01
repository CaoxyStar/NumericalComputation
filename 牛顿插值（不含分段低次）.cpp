#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

void Newton_File();
void Newton_Input(); //�ֶ����Ժ���
double Newton_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ����ǰ��ֵ
double Newton_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ������ֵ
double Newton_base(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ�ٻ�����ֵ


//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	Newton_File();    //�ֶ��������
	return 0;
}*/


//ţ����ǰ��ֵ
double Newton_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[0];
	double h = reference_x[1] - reference_x[0];
	double t = (x - reference_x[0]) / h;
	cout << "t=" << t << endl;
	if (n >= 2)
	{
		double error1 = reference_y[1] - reference_y[0];
		cout << "һ�ײ�֣�" << error1 << endl;
		y += t * error1;
		if (n >= 3)
		{
			double error2 = (reference_y[2] - reference_y[1]) - error1;
			cout << "���ײ�֣�" << error2 << endl;
			y += t * (t - 1) * error2 / 2;
			if (n == 4)
			{
				double error3 = (reference_y[3] - reference_y[2]) - (reference_y[2] - reference_y[1]) - error2;
				cout << "���ײ�֣�" << error3 << endl;
				y += t * (t - 1) * (t - 2) * error3 / 6;
			}
		}
		return y;
	}
}

//ţ������ֵ
double Newton_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[arrsize-1];
	double h = reference_x[arrsize-1] - reference_x[arrsize-2];
	double t = (x - reference_x[arrsize-1]) / h;
	cout << "t=" << t << endl;
	if (n >= 2)
	{
		double error1 = reference_y[arrsize-1] - reference_y[arrsize-2];
		cout << "һ�ײ�֣�" << error1 << endl;
		y += t * error1;
		if (n >= 3)
		{
			double error2 = error1 - (reference_y[arrsize - 2] - reference_y[arrsize - 3]);
			cout << "���ײ�֣�" << error2 << endl;
			y += t * (t + 1) * error2 / 2;
			if (n == 4)
			{
				double error3 = error2 - ((reference_y[arrsize - 2] - reference_y[arrsize - 3]) - (reference_y[arrsize - 3] - reference_y[arrsize - 4]));
				cout << "���ײ�֣�" << error3 << endl;
				y += t * (t + 1) * (t + 2) * error3 / 6;
			}
		}
		return y;
	}
}

//ţ�ٻ�����ֵ
double Newton_base(const double reference_x[], const double reference_y[], int arrsize, int n, double x)
{
	double y = reference_y[0];
	if (n >= 2)
	{
		double error1 = (reference_y[1] - reference_y[0]) / (reference_x[1] - reference_x[0]);
		cout << "һ�ײ��̣�" << error1 << endl;
		y += error1 * (x - reference_x[0]);
		if (n >= 3)
		{
			double error2 = ((reference_y[2] - reference_y[1]) / (reference_x[2] - reference_x[1]) - error1) / 
				(reference_x[2] - reference_x[0]);
			cout << "���ײ��̣�" << error2 << endl;
			y += error2 * (x - reference_x[0]) * (x - reference_x[1]);
			if (n == 4)
			{
				double error1_temp = (reference_y[2] - reference_y[1]) / (reference_x[2] - reference_x[1]);
				double error2_temp = ((reference_y[3] - reference_y[2]) / (reference_x[3] - reference_x[2]) - error1_temp) / 
					(reference_x[3] - reference_x[1]);
				double error3 = (error2_temp - error2) / (reference_x[3] - reference_x[0]);
				cout << "���ײ��̣�" << error3 << endl;
				y += error3 * (x - reference_x[0]) * (x - reference_x[1]) * (x - reference_x[2]);
			}
		}
		return y;
	}
}

//�ֶ�������Ժ���
void Newton_Input()
{
	int arrsize; //��ֵ�����
	double x; //����ֵ
	double y; //����ֵ
	int n;  //ѡ�����Բ�ֵ��������β�ֵ
	int choice; //ѡ������ţ�ٲ�ֵ�㷨����ǰ����󡢻�����
	cout << "please choose a algorithms : \n(enter 1 to Newton_Interpolation_front)\n(enter 2 to Newton_Interpolation_back)\n(enter 3 to Newton_Interpolation)" << endl;
	cin >> choice;
	cout << "Please enter the size of list����֪������� : ";
	cin >> arrsize;
	double* x_list = new double[arrsize];
	double* y_list = new double[arrsize];
	for (int i = 0; i < arrsize; i++)   //�����x��y����
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
		cout << "���Բ�ֵ����2�������ֵ����3�����β�ֵ����4��";
		cin >> n;
	}
	else
		cout << "Failure!" << endl;
	cout << "Please enter a number to estimate: ";
	cin >> x;
	switch (choice)   //ѡ����ǰ����󡢻�����ֵ
	{
	case 1: y = Newton_front(x_list, y_list, arrsize, n, x);
		break;
	case 2: y = Newton_back(x_list, y_list, arrsize, n, x);
		break;
	case 3: y = Newton_base(x_list, y_list, arrsize, n, x);
		break;
	}
	cout << "f(" << x << ")=" << y << endl;
}

//��ȡ�ļ����Ժ���
void Newton_File()
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
	switch (choice)   //ѡ����ǰ����󡢻�����ֵ
	{
	case 1: y = Newton_front(x_list, y_list, arrsize, n, x);
		break;
	case 2: y = Newton_back(x_list, y_list, arrsize, n, x);
		break;
	case 3: y = Newton_base(x_list, y_list, arrsize, n, x);
		break;
	}
	ofstream outFile;
	outFile.open("Newton_testingFile.txt", ios::out | ios::app);
	outFile << y << endl;
	outFile.close();
	cout << "Done!" << endl;
}