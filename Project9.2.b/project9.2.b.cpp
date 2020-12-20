#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;
enum Specialty { ComputerScience, Informatics, Mathematics, Physics, Work };
string specialtyStr[] = { "����'����� �����", "�����������", "�����.�� ������.","Գ���� �� ������.","������� ��������" };
struct Student
{
	string prizv;
	unsigned course;
	Specialty specialty;
	unsigned grades_in_physics;
	unsigned grades_in_mathematics;
	union
	{
		unsigned grades_in_programming;
		unsigned grades_in_numerical_methods;
		unsigned grades_in_pedagogy;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned course, int grade_third_predmet);
int main()
{
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

	int N;
	cout << "������ ������� �������� N: "; cin >> N;
	Student* p = new Student[N];
	unsigned course;
	string prizv;
	int found;
	int grade_third_predmet;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl << endl;
		cout << " [4] - �������� ������������� �� ���� �����"
			<< endl << endl;
		cout << " [5] - ������� ����� ���������� �� ������� �� ��������"
			<< endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			Print(p, N);
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "������ ����� ������:" << endl;
			cout << " ������ �  � �������� ��������: ";
			cin >> grade_third_predmet;
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� ����
			cout << " ����: ";
			cin >> course;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, course, grade_third_predmet)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int specialty;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].course;
		cout << "  ������������ (0 -����'����� ����� , 1 -�����������, 2 -�����. �� ������., 3 - Գ���� �� ������., 4 - ������� ��������): ";
		cin >> specialty;
		cout << "  ������ � ������: "; cin >> p[i].grades_in_physics;
		cout << "  ������ � ����������: "; cin >> p[i].grades_in_mathematics;
		p[i].specialty = (Specialty)specialty;
		switch (p[i].specialty)
		{
		case ComputerScience:
			cout << "������ � �������������  : "; cin >> p[i].grades_in_programming;
			break;
		case Informatics:
			cout << "������ � ��������� ������  : "; cin >> p[i].grades_in_numerical_methods;
			break;
		case Mathematics:
		case Physics:
		case Work:
			cout << " ������ � ��������� : "; cin >> p[i].grades_in_pedagogy;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "=================================================================================================================================================="
		<< endl;
	cout << "|�  |�������  |����|C�����������    |O����� � ������|O����� � ����������|O����� � �������������|O����� � ��������� ������|O����� � ���������|"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "|" << setw(10) << left << p[i].prizv
			<< "|" << setw(3) << right << p[i].course << " "
			<< "|" << setw(17) << left << specialtyStr[p[i].specialty]
			<< "|" << setw(14) << right << p[i].grades_in_physics << " "
			<< "|" << setw(18) << right << p[i].grades_in_mathematics << " ";
		switch (p[i].specialty)
		{
		case ComputerScience:
			cout << "| " << setw(20) << setprecision(2) << fixed << right
				<< p[i].grades_in_programming << " |" << setw(27) << right << "|" << setw(20) << right << "|" << endl;
			break;
		case Informatics:
			cout << "|" << setw(23) << " |" << setw(25) << setprecision(2) << fixed << right
				<< p[i].grades_in_numerical_methods << " |" << setw(20) << right << "|" << endl;
			break;
		case Mathematics:
		case Physics:
		case Work:
			cout << "| " << setw(23) << "| " << setw(26) << right << "|" << " " << setw(17) << right
				<< p[i].grades_in_pedagogy << " |" << endl;
			break;
		}
	}
	cout << "=================================================================================================================================================="
		<< endl;
	cout << endl;
}
int GradeProfPedmet(Student p)
{
	int result;
	switch (p.specialty)
	{
	case ComputerScience:
		result = p.grades_in_programming;
		break;
	case Informatics:
		result = p.grades_in_numerical_methods;
		break;
	case Mathematics:
	case Physics:
	case Work:
		result =p.grades_in_pedagogy;
	}
	return result;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((GradeProfPedmet(p[i1]) < GradeProfPedmet(p[i1 + 1]))
				||
				(GradeProfPedmet(p[i1]) == GradeProfPedmet(p[i1 + 1]) &&
					p[i1].course < p[i1 + 1].course)
				||
				(p[i1].course == p[i1 + 1].course && GradeProfPedmet(p[i1]) == GradeProfPedmet(p[i1 + 1])
					&& p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((GradeProfPedmet(p[I[j]]) < GradeProfPedmet(p[value])) ||
				(GradeProfPedmet(p[I[j]]) == GradeProfPedmet(p[value]) &&
					p[I[j]].course < p[value].course)
				||
				(p[I[j]].course == p[value].course && GradeProfPedmet(p[I[j]]) == GradeProfPedmet(p[value])
					&& p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "=================================================================================================================================================="
		<< endl;
	cout << "|�  |�������  |����|C�����������    |O����� � ������|O����� � ����������|O����� � �������������|O����� � ��������� ������|O����� � ���������|"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{

		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "|" << setw(10) << left << p[I[i]].prizv;
		cout << "|" << setw(3) << right << p[I[i]].course << " ";
		cout << "|" << setw(17) << left << specialtyStr[p[I[i]].specialty];
		cout << "|" << setw(14) << right << p[I[i]].grades_in_physics << " ";
		cout << "|" << setw(18) << right << p[I[i]].grades_in_mathematics << " ";
		switch (p[I[i]].specialty)
		{
		case ComputerScience:
			cout << "| " << setw(20) << setprecision(2) << fixed << right
				<< p[I[i]].grades_in_programming << " |" << setw(27) << right << "|" << setw(20) << right << "|" << endl;
			break;
		case Informatics:
			cout << "|" << setw(23) << " |" << setw(25) << setprecision(2) << fixed << right
				<< p[I[i]].grades_in_numerical_methods << " |" << setw(20) << right << "|" << endl;
			break;
		case Mathematics:
		case Physics:
		case Work:
			cout << "| " << setw(23) << "| " << setw(26) << right << "|" << " " << setw(17) << right
				<< p[I[i]].grades_in_pedagogy << " |" << endl;
			break;
		}
	}
	cout << "=================================================================================================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const unsigned course, int grade_third_predmet)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (GradeProfPedmet(p[m]) < grade_third_predmet)
		{
			R = m - 1;
		}
		else if (GradeProfPedmet(p[m]) > grade_third_predmet)
		{
			L = m + 1;
		}
		else
		{
			// (p[m].grades_in_informatic == grades_in_informatic)
			if (p[m].course < course)
			{
				R = m - 1;
			}
			else if (p[m].course > course)
			{
				L = m + 1;
			}
			else
			{
				if (p[m].prizv > prizv)
				{
					L = m + 1;
				}
				else if (p[m].prizv < prizv)
				{
					R = m - 1;
				}
				else
				{
					return m;
				}
			}
		}

	} while (L <= R);
	return -1;
}