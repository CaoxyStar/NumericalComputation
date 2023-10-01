#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

void Gaussion_File_Input();  //�����ļ��������
void Gaussion_Hand_Input();  //�����ֶ��������
double Gaussian_elimination(int n, vector<vector<double>> &A_matric,double x_matric[], double b_matric[],double base); //����Ԫ��˹��ȥ��

//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����

int main()
{
	Gaussion_File_Input();   //�ļ��������ݲ���
	//Gaussion_Hand_Input();   //�����ֶ�����ʱ�뽫����ȡ��ע�ͣ�ͬʱע����һ��
	return 0;
}


//����Ԫ��˹��ȥ��
double Gaussian_elimination(int n, vector<vector<double>>& A_matric, double x_matric[], double b_matric[], double base)
{
	double det_a = 1;
	double max_num;
	int max_line;
	double temp_a;
	double temp_b;
	double change_num;
	for (int i = 0; i < n-1 ; i++)               //ѡ���������Ԫ
	{
		max_num = 0;
		max_line = 0;
		for (int j = i; j < n; j++)
		{
			if (abs(A_matric[j][i]) > max_num)
			{
				max_num = A_matric[j][i];
				max_line = j;
			}
		}

		//if (max_num < base)
			//return 0;

		if (max_line != i)                      //�н���
		{
			for (int k = i; k < n; k++)
			{
				temp_a = A_matric[i][k];
				A_matric[i][k] = A_matric[max_line][k];
				A_matric[max_line][k] = temp_a;
			}
			temp_b = b_matric[i];
			b_matric[i] = b_matric[max_line];
			b_matric[max_line] = temp_b;
			det_a *= -1;
		}

		for (int m = i + 1; m < n; m++)                 //��Ԫ
		{
			change_num = A_matric[m][i] / A_matric[i][i];
			for (int p = i; p < n; p++)
			{
				A_matric[m][p] -= A_matric[i][p] * change_num;
			}
			b_matric[m] -= b_matric[i] * change_num;
		}

		for (int m = 0; m < n; m++)
		{
			for (int k = 0; k < n; k++)
				cout << A_matric[m][k] << "\t";
			cout << b_matric[m] << endl;
		}
		cout << "****************************" << endl;
	}
	for (int i = 0; i < n; i++)                   //�ж��Ƿ�Ϊ�������
	{
		det_a *= A_matric[i][i];
	}

	for (int i = n - 1; i >= 0; i--)                   //�ش�
	{
		double value = b_matric[i];
		for (int j = i + 1; j < n; j++)
			value -= x_matric[j] * A_matric[i][j];
		x_matric[i] = value / A_matric[i][i];
	}

	return det_a;
}


//�ֶ�����
void Gaussion_Hand_Input()
{
	cout << "�����뷽�̸�����";
	int n;
	cin >> n;
	vector<vector<double>> A_matric;
	vector<double>a_line(n);
	double* x_matric = new double[n];
	double* b_matric = new double[n];
	cout << "#�����������#" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "��������������" << i + 1 << "�� (ÿ����֮��ո��������" << endl;
		for (int j = 0; j < n; j++)
		{
			cin >> a_line[j];
		}
		A_matric.push_back(a_line);
	}
	cout << "#����ֵb����(ÿ����֮��ո������#" << endl;
	for (int i = 0; i < n; i++)
		cin >> b_matric[i];
	double base = 0.001;
	double det = Gaussian_elimination(n, A_matric, x_matric, b_matric, base);
	/*if (det == 0)
	{
		cout << "det(A)�ӽ�0�������޽⣡" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (abs(x_matric[i]) < base)
				cout << "x" << i + 1 << " = 0" << endl;
			else
				cout << "x" << i + 1 << " = " << x_matric[i] << endl;
		}
		cout << "det(A) = " << det << endl;
	}*/
	for (int i = 0; i < n; i++)
	{
		if (abs(x_matric[i]) < base)
			cout << "x" << i + 1 << " = 0" << endl;
		else
			cout << "x" << i + 1 << " = " << x_matric[i] << endl;
	}
	cout << "det(A) = " << det << endl;
}

//�ļ�����
void Gaussion_File_Input()
{
	ifstream inFile;
	inFile.open("Gaussion_testingFile.txt");
	string str;
	int n;
	getline(inFile, str);
	inFile >> n;
	inFile.get();
	vector<vector<double>> A_matric;
	vector<double>a_line(n);
	double* x_matric = new double[n];
	double* b_matric = new double[n];
	getline(inFile, str);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inFile >> a_line[j];
		}
		A_matric.push_back(a_line);
	}
	inFile.get();
	getline(inFile, str);
	for (int i = 0; i < n; i++)
		inFile >> b_matric[i];
	inFile.get();
	inFile.close();
	double base = 0.001;
	double det = Gaussian_elimination(n, A_matric, x_matric, b_matric, base);
	ofstream outFile;
	outFile.open("Gaussion_testingFile.txt", ios::out | ios::app);
	for (int i = 0; i < n; i++)
	{
		if (abs(x_matric[i]) < base)
			outFile << "x" << i + 1 << " = 0" << endl;
		else
			outFile << "x" << i + 1 << " = " << x_matric[i] << endl;
	}
	outFile << "det(A) = " << det << endl;
	if (det == 0)
	{
		outFile << "det(A)�ӽ�0�������޽⣡" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (abs(x_matric[i]) < base)
				outFile << "x" << i + 1 << " = 0" << endl;
			else
				outFile << "x" << i + 1 << " = " << x_matric[i] << endl;
		}
		outFile << "det(A) = " << det << endl;
	}
	cout << "Done!" << endl;
}