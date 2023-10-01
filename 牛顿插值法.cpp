#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void Newton_Hand_Input(); //�ֶ����Ժ���
void Newton_File_Input(); //��ȡ�ļ����Ժ���
int Get_Midpoint(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //�ֶεʹβ�ֵ��ȡ��ֵ��
double Newton_Interpolation_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ����ǰ��ֵ
double Newton_Interpolation_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ������ֵ
double Newton_Interpolation(const double reference_x[], const double reference_y[], int arrsize, int n, double x); //ţ�ٻ�����ֵ


//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	//Newton_File_Input();     //�ļ��������
	Newton_Hand_Input();    //�ֶ��������
	return 0;
}*/

//�ֶεʹβ�ֵѡȡ��ֵ�㺯��
int Get_Midpoint(const double reference_x[], const double reference_y[], int arrsize, int n, double x)     
{
	if (n == 2)    //���Բ�ֵ
	{
		for (int i = 0; i < arrsize; i++)
		{
			if ((reference_x[i] <= x) and (reference_x[i + 1] > x))
			{
				return i;
			}
		}
		cout << "Please enter the number which in range." << endl;
	}
	else if (n == 3)    //�����ֵ
	{
		if ((x < (reference_x[1] + reference_x[2]) / 2) and (x>=reference_x[0]))
			return 1;
		else if ((x >=( reference_x[arrsize-2]+reference_x[arrsize-3])/2) and (x<=reference_x[arrsize-1]))
			return arrsize - 2;
		else
		{
			for (int i = 1; i < arrsize-1; i++)
			{
				if ((x >= (reference_x[i - 1] + reference_x[i]) / 2) and (x < (reference_x[i] + reference_x[i + 1]) / 2))
					return i;
			}
			cout << "Please enter the number which in range." << endl;
		}
	}
}

//ţ����ǰ��ֵ
double Newton_Interpolation_front(const double reference_x[], const double reference_y[], int arrsize, int n, double x)    
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2) //���Բ�ֵ
	{
		double h = reference_x[midpoint + 1] - reference_x[midpoint];
		double t = (x - reference_x[midpoint]) / h;
		double distance_1 = reference_y[midpoint + 1] - reference_y[midpoint];
		return reference_y[midpoint] + t * distance_1;
	}
	if (n == 3)    //�����ֵ
	{
		double h = reference_x[midpoint] - reference_x[midpoint - 1];
		double t = (x - reference_x[midpoint - 1]) / h;
		double distance_1 = reference_y[midpoint] - reference_y[midpoint - 1];
		double distance_2 = reference_y[midpoint + 1] - reference_y[midpoint] - distance_1;
		return reference_y[midpoint - 1] + t * distance_1 + t * (t - 1) * distance_2 / 2;
	}
}

//ţ������ֵ
double Newton_Interpolation_back(const double reference_x[], const double reference_y[], int arrsize, int n, double x)  
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2)     //���Բ�ֵ
	{
		double h = reference_x[midpoint + 1] - reference_x[midpoint];
		double t = (x - reference_x[midpoint+1]) / h;
		double distance_1 = reference_y[midpoint + 1] - reference_y[midpoint];
		return reference_y[midpoint+1] + t * distance_1;
	}
	if (n == 3)     //�����ֵ
	{
		double h = reference_x[midpoint] - reference_x[midpoint - 1];
		double t = (x - reference_x[midpoint + 1]) / h;
		double distance_1 = reference_y[midpoint+1] - reference_y[midpoint];
		double distance_2 = distance_1 - (reference_y[midpoint] - reference_y[midpoint - 1]);
		return reference_y[midpoint + 1] + t * distance_1 + t * (t + 1) * distance_2 / 2;
	}
}

//ţ�ٻ�����ֵ
double Newton_Interpolation(const double reference_x[], const double reference_y[], int arrsize, int n, double x)    
{
	int midpoint = Get_Midpoint(reference_x, reference_y, arrsize, n, x);
	if (n == 2)     //���Բ�ֵ
	{
		double k = (reference_y[midpoint + 1] - reference_y[midpoint]) / (reference_x[midpoint + 1] - reference_x[midpoint]);
		return reference_y[midpoint] + k * (x - reference_x[midpoint]);
	}
	if (n == 3)     //�����ֵ
	{
		double k1 = (reference_y[midpoint] - reference_y[midpoint - 1]) / (reference_x[midpoint] - reference_x[midpoint - 1]);
		double k2 = (reference_y[midpoint + 1] - reference_y[midpoint]) / (reference_x[midpoint + 1] - reference_x[midpoint]);
		double f1 = (k2 - k1) / (reference_x[midpoint + 1] - reference_x[midpoint - 1]);
		return reference_y[midpoint - 1] + k1 * (x - reference_x[midpoint - 1]) + f1 * (x - reference_x[midpoint - 1]) * (x - reference_x[midpoint]);
	}
}

//�ֶ�������Ժ���
void Newton_Hand_Input()
{
	int arrsize; //��ֵ�����
	double x; //����ֵ
	double y; //����ֵ
	int n;  //ѡ�����Բ�ֵ���������ֵ
	int choice; //ѡ������ţ�ٲ�ֵ�㷨����ǰ����󡢻�����
	cout << "Please enter the size of list����֪������� : ";
	cin >> arrsize;
	cout << "please choose a algorithms : \n(enter 1 to Newton_Interpolation_front)\n(enter 2 to Newton_Interpolation_back)\n(enter 3 to Newton_Interpolation)" << endl;
	cin >> choice;
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
		cout << "���Բ�ֵ����2�������ֵ����3��";
		cin >> n;
	}
	else
		cout << "Failure!" << endl;
	cout << "Please enter a number to estimate: ";
	cin >> x;
	switch (choice)   //ѡ����ǰ����󡢻�����ֵ
	{
	case 1: y = Newton_Interpolation_front(x_list, y_list, arrsize, n, x);
	case 2: y = Newton_Interpolation_back(x_list, y_list, arrsize, n, x);
	case 3: y = Newton_Interpolation(x_list, y_list, arrsize, n, x);
	}
	cout << "f(" << x << ")=" << y << endl;
}

//��ȡ�ļ����Ժ���
void Newton_File_Input()
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
	switch (choice)
	{
	case 1: y = Newton_Interpolation_front(x_list, y_list, arrsize, n, x);
	case 2: y = Newton_Interpolation_back(x_list, y_list, arrsize, n, x);
	case 3: y = Newton_Interpolation(x_list, y_list, arrsize, n, x);
	}
	ofstream outFile;
	outFile.open("Newton_testingFile.txt", ios::out | ios::app);
	outFile << y << endl;
	outFile.close();
	cout << "Done!" << endl;
}