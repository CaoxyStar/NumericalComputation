#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<math.h>
using namespace std;

vector<double> Chasing(vector<double>a, vector<double>b, vector<double>c, vector<double>res, int n);
double CubicSpline_interpolation(int n, vector<double>x, vector<double>y, int choice, double condition_1, double condition_2,double x_try);
void CubicSpline_handInput();
void CubicSpline_fileInput();

//ȥ���·�main����ע�ͼ��ɿ�ʼ���ԣ��뽫�ֶ��������ȡ�ļ��ֿ�����
/*
int main()
{
	//CubicSpline_handInput();  //�ֶ�����
	CubicSpline_fileInput();   //�ļ��������
	return 0;
}*/

//����������ֵ��
double CubicSpline_interpolation(int n, vector<double>x, vector<double>y, int choice, double condition_1, double condition_2,double x_try)
{
	vector<double>h(n - 1);
	vector<double>f(n - 1);
	vector<double>u(n - 2);
	vector<double>v(n - 2);
	vector<double>g(n - 2);
	vector<double>M(n);
	vector<double>medium(n, 2);
	for (int i = 0; i < n - 1; i++)
	{
		h[i] = x[i + 1] - x[i];
		f[i] = (y[i + 1] - y[i]) / h[i];
	}

	//���h��f
	cout << "h:\t";
	for (int i = 0; i < n - 1; i++)
		cout << h[i] << " ";
	cout << endl;
	cout << "f:\t";
	for (int i = 0; i < n - 1; i++)
		cout << f[i] << " ";
	cout << endl;

	for (int i = 0; i < n - 2; i++)
	{
		u[i] = h[i] / (h[i] + h[i + 1]);
		v[i] = 1 - u[i];
		g[i] = 6 / (h[i] + h[i + 1]) * (f[i + 1] - f[i]);
	}
	switch (choice)            //ѡ���һ��������ڶ�������
	{
	case 1:
		u.push_back(1);
		v.insert(v.begin(), 1);
		g.push_back(6 / h[n - 2] * (condition_2 - f[n - 2]));
		g.insert(g.begin(), 6 / h[0] * (f[0] - condition_1));
		
		//���u,v,g
		cout << "u:\t";
		for (int i = 0; i < n - 1; i++)
			cout << u[i] << " ";
		cout << endl;
		cout << "v:\t";
		for (int i = 0; i < n - 1; i++)
			cout << v[i] << " ";
		cout << endl;
		cout << "g:\t";
		for (int i = 0; i < n; i++)
			cout << g[i] << " ";
		cout << endl;

		M = Chasing(u, medium, v, g, n);
		break;
	case 2:
		double temp1 = u[0];
		u.erase(u.begin(), u.begin() + 1);
		double temp2 = v.back();
		v.pop_back();
		medium.pop_back();
		medium.pop_back();
		g[0] -= temp1 * condition_1;
		g[n - 3] -= temp2 * condition_2;
		cout << "u1=" << temp1 << "\tv_last=" << temp2 << endl;
		//���u,v,g
		cout << "u:\t";
		for (int i = 0; i < n - 3; i++)
			cout << u[i] << " ";
		cout << endl;
		cout << "v:\t";
		for (int i = 0; i < n - 3; i++)
			cout << v[i] << " ";
		cout << endl;
		cout << "g:\t";
		for (int i = 0; i < n - 2; i++)
			cout << g[i] << " ";
		cout << endl;

		M.erase(M.begin(), M.begin() + 1);
		M.pop_back();
		M = Chasing(u, medium, v, g, n - 2);
		M.insert(M.begin(), condition_1);
		M.push_back(condition_2);
		break;
	}

	//���M
	cout << "M:\t";
	for (int i = 0; i < n; i++)
		cout << M[i] << " ";
	cout << endl;

	int node;
	double y_1,y_2,y_3,y_4;
	double a, b, c, d;
	for (int i = 0; i < n-1; i++)             //����xֵѡȡ��ֵ����
	{
		if ((x_try >= x[i]) && ((x_try < x[i + 1])))
		{
			node = i;
			break;
		}
		else if (x_try == x[n - 1])
		{
			node = n - 2;
			break;
		}
	}
	//���㺯��ֵ
	a = (M[node + 1] - M[node]) / (6 * h[node]);
	b = (M[node] * x[node + 1] - M[node + 1] * x[node]) / (2 * h[node]);
	c = (M[node + 1] * pow(x[node], 2) - M[node] * pow(x[node + 1], 2))/(2*h[node]) + (y[node + 1] - y[node] + (M[node] - M[node + 1]) * pow(h[node], 2) / 6) / h[node];
	d = (M[node] * pow(x[node + 1], 3) - M[node + 1] * pow(x[node], 3)) / (6 * h[node]) + (y[node] - M[node] * pow(h[node], 2) / 6) * x[node + 1] / h[node] - (y[node + 1] - M[node + 1] * pow(h[node], 2) / 6) * x[node] / h[node];
	cout << "a=" << a << ",b=" << b << ",c=" << c << ",d=" << d << endl;

	y_1 = M[node] / (6 * h[node]) * pow(x[node + 1] - x_try, 3);
	y_2 = M[node + 1] / (6 * h[node]) * pow(x_try - x[node], 3);
	y_3 = (y[node] - M[node] * pow(h[node], 2) / 6) * (x[node + 1] - x_try) / h[node];
	y_4 = (y[node + 1] - M[node + 1] * pow(h[node], 2) / 6) * (x_try - x[node]) / h[node];
	return y_1 + y_2 + y_3 + y_4;
}

//׷�Ϸ�������Է�����
vector<double> Chasing(vector<double>a, vector<double>b, vector<double>c, vector<double>res, int n)
{
	double* y = new double[n];
	vector<double>x(n);
	for (int i = 0; i < n - 1; i++)
	{
		c[i] = c[i] / b[i];
		b[i + 1] -= a[i] * c[i];
	}

	y[0] = res[0] / b[0];
	for (int i = 1; i < n; i++)
		y[i] = (res[i] - a[i-1]*y[i - 1]) / b[i];

	x[n - 1] = y[n - 1];
	for (int i = n - 2; i >= 0; i--)
		x[i] = y[i] - c[i] * x[i + 1];
	return x;
}

//�ֶ�������Ժ���
void CubicSpline_handInput()
{
	cout << "�������׼�������";
	int n;
	cin >> n;
	vector<double>x(n);
	vector<double>y(n);
	cout << "��������֪�㣺" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << "=";
		cin >> x[i];
		cout << "y" << i + 1 << "=";
		cin >> y[i];
	}
	cout << "�����벹����������(����1��2��3����\n1.��һ�ಹ������\n2.�ڶ��ಹ������\n3.�����ಹ������" << endl;
	int choice;
	double condition_1;
	double condition_2;
	cin >> choice;
	cout << "����������1��";
	cin >> condition_1;
	cout << "����������2��";
	cin >> condition_2;
	double x_try;
	cout << "���������ֵx���Բ�ֵ������";
	cin >> x_try;
	double output = CubicSpline_interpolation(n, x, y, choice, condition_1, condition_2, x_try);
	cout << "��ֵ������x=" << x_try << "��Ӧ y=" << output << endl;
}

//��ȡ�ļ����뺯��
void CubicSpline_fileInput()
{
	ifstream inFile;
	inFile.open("CubicSpline_testingFile.txt");
	string str;
	int n;
	getline(inFile, str);
	inFile >> n;
	inFile.get();
	getline(inFile, str);
	vector<double>x(n);
	vector<double>y(n);
	for (int i = 0; i < n; i++)
	{
		inFile >> x[i];
		inFile >> y[i];
	}
	inFile.get();
	getline(inFile, str);
	int choice;
	inFile >> choice;
	inFile.get();
	getline(inFile, str);
	double condition_1, condition_2;
	inFile >> condition_1;
	inFile >> condition_2;
	inFile.get();
	getline(inFile, str);
	double x_try;
	inFile >> x_try;
	inFile.close();
	ofstream outFile;
	outFile.open("CubicSpline_testingFile.txt", ios::out | ios::app);
	double output = CubicSpline_interpolation(n, x, y, choice, condition_1, condition_2, x_try);
	outFile << output << endl;
	outFile.close();
	cout << "Done!" << endl;
}