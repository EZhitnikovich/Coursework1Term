#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


struct arr_characteristic {
	int cols;
	int rows;
};



enum sw_main {
	read = 1,
	generate,
	out,
	sort,
	stop };



enum sw_type {
	manual = 1,
	gen_type };



void gen(double **&arr, arr_characteristic &);

void in_arr(double **&arr, arr_characteristic &);

void out_arr(double **arr, arr_characteristic);

void out_file(double **arr, arr_characteristic);

void in_file(double **&arr, arr_characteristic &);

void sort_arr(double **&arr, arr_characteristic);

void line_determinants(double **arr, double *buff, arr_characteristic);

void line_sort(double **arr, double *buff, arr_characteristic);

void final_out(double **arr, double *buff, arr_characteristic);


void info();

double double_number_input();

int int_number_input();

char Y_N();

void input_type(double **&arr, arr_characteristic &);



int main() {
	setlocale(LC_ALL, "rus");

	bool loop = true;
	arr_characteristic ch = {};
	double **arr = new double*[ch.rows];

	while (loop) {
		system("cls");
		info();
		cout << "������� ����� ������ ����: ";
		int i;
		i = int_number_input();

		switch (i) {

		case read:

			in_file(arr, ch);

			break;
		case generate:

			input_type(arr, ch);
			break;
		case out:

			out_arr(arr, ch);

			break;
		case sort:

			sort_arr(arr, ch);

			break;
		case stop:

			cout << "������ ����������." << endl;
			loop = false;
			break;
		default:

			cout << "������������ ������" << endl;
			break;
		}
		system("pause");
	}

	for (int i = 0; ch.rows > 0 && i < ch.rows; i++) {
		delete[] arr[i];
	}

	delete[] arr;

}



void input_type(double **&arr, arr_characteristic &x) {

	cout << "��� �������� �������: \n";
	cout << "1 - �������;\n";
	cout << "2 - �������������.\n";
	cout << "���� �������� ��� ������.\n";
	cout << "�������� ���: ";
	int q;
	q = int_number_input();

	bool show_arr = false;

	switch (q) {
	case manual:
		in_arr(arr, x);
		show_arr = true;
		break;
	case gen_type:
		gen(arr, x);
		show_arr = true;
		break;
	default:
		cout << "������ ����������.\n";
		break;
	}

	if (show_arr && x.cols && x.rows) {
		out_arr(arr, x);

		cout << "�������� ������ ������ � ����? Y/N: ";
		q = Y_N();

		if (q == 'Y') {
			cout << "������ ����� �������� � ����\n\n";
			out_file(arr, x);
		}
		else if (q == 'N')
			cout << "������ �� ����� ������� � ����.\n\n";
	}
	else {
		cout << "���������� ���������� �����\n";
		cout << "������������ ������ ��� ���������� ��������.\n";
	}

}


void info() {

	cout << "��������� ������������� ��� ������������ ����� � ������� � ������������ � ������ �������������\n";
	cout << "��������������� ������ ������� �������� ����� � ������������� ���������, ������� ������ �������� ��������\n\n";

	cout << "---------------------------------------------------------------------------------------------------------------\n\n";

	cout << "���� ���������:\n";
	cout << "��� �������� ������������� ������� �� ����� ������� 1\n";
	cout << "��� ���������/����� ����� ������� � ������ � � ���� ������� 2\n";
	cout << "��� ������ ������� � ������� ������� 3\n";
	cout << "��� ������������ ����� � ������� � ������������ � ������ ������������� ������� 4\n";
	cout << "��� ���������� ������ ������� 5\n\n";

}



int int_number_input() { // �������������� ������ � int ��������.

	const int buff_size = 255;
	char buff[buff_size];
	cin.getline(buff, buff_size);

	return atoi(buff);
}



double double_number_input() { // �������������� ������ � int ��������.

	const int buff_size = 255;
	char buff[buff_size];
	cin.getline(buff, buff_size);

	return atof(buff);
}



char Y_N()
{
	while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ����� ���������� ��������
	{
		char y_n;
		cin >> y_n;

		cin.ignore(32767, '\n');

		// �������� ����������������� �����
		if (y_n == 'Y' || y_n == 'N')
			return y_n;
		else // � ��������� ������, �������� ������������ ��� ���-�� ����� �� ���
			cout << "������ �����, ��������� ���� (Y/N): \n";
	}
}



void in_arr(double **&arr, arr_characteristic &x) {

	//��������� ������� ������������� ������ �� ������ ���� �� ��� �������� ������/�� ����������� �������.
	for (int i = 0; x.rows > 0 && i < x.rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	cout << "������� ���-�� �����: ";
	x.rows = fabs(int_number_input());

	cout << "������� ���-�� ��������: ";
	x.cols = fabs(int_number_input());

	//�������� ������ �������, ������ �������.
	double **newArr = new double*[x.rows];
	for (int i = 0; i < x.rows; i++) {
		newArr[i] = new double[x.cols];
	}

	for (int i = 0; i < x.rows; i++) {
		cout << "�������� ������ " << i << "\n";
		for (int j = 0; j < x.cols; j++) {
			newArr[i][j] = double_number_input();
		}
	}

	arr = newArr;
}



void gen(double **&arr, arr_characteristic &x) { // �������� arr ���������� �� ������.

	//��������� ������� ������������� ������ �� ������ ���� �� ��� �������� ������/�� ����������� �������.
	for (int i = 0; x.rows > 0 && i < x.rows; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	cout << "������� ���-�� �����: ";
	x.rows = fabs(int_number_input());

	cout << "������� ���-�� ��������: ";
	x.cols = fabs(int_number_input());

	double start, end;

	cout << "������� ��������� �������� ��������� �����: ";
	start = double_number_input();

	cout << "������� �������� �������� ��������� �����: ";
	end = double_number_input();

	//�������� ������ �������, ������ �������.
	double **newArr = new double*[x.rows];

	for (int i = 0; i < x.rows; i++) {
		newArr[i] = new double[x.cols];
	}

	//���������� ������� ������� ���� double.
	for (int i = 0; i < x.rows; i++) {
		for (int j = 0; j < x.cols; j++) {
			newArr[i][j] = (double)rand() / RAND_MAX * (end - start) + start;
		}
	}

	arr = newArr; // ��������� ������ ��������� �� ����� ������ newArr, � �� arr.

	cout << "������ ������������.\n\n";
}



void out_arr(double **arr, arr_characteristic x) {

	if (x.cols && x.rows) {
		cout << "������ ������������ " << x.rows << "x" << x.cols << "\n";
		cout << "����� �������: \n";

		for (int i = 0; i < x.rows; i++) {
			for (int j = 0; j < x.cols; j++) {
				cout << setw(10) << arr[i][j] << " ";
			}
			cout << "\n";
		}

		cout << "\n";
	}
	else
		cout << "������������ ���-�� ����� ��� ������, ���-�� �����: " << x.rows << " ���-�� ��������: " << x.cols << "\n";
}



void out_file(double **arr, arr_characteristic x) {

	fstream out("file.dat", ios::binary | ios::out);

	//������ ����������� ������� � ����.
	out.write((char*)&x.rows, sizeof(int));
	out.write((char*)&x.cols, sizeof(int));

	//������ �������� � ����.
	for (int i = 0; i < x.rows; i++) {
		for (int j = 0; j < x.cols; j++) {
			out.write((char*)&arr[i][j], sizeof(double));
		}
	}

	out.close();
}


void in_file(double **&arr, arr_characteristic &x) {

	fstream in("file.dat", ios::binary | ios::in);

	if (!in) {
		cout << "���� �� ���������.\n";
	}
	else {
		//��������� ������� ������������ ������ �� ������ ���� �� ��� �������� ������.
		for (int i = 0; x.rows > 0 && i < x.rows; i++) {
			delete[] arr[i];
		}

		delete[] arr;

		//������ ����������� ������� �� �����.
		in.read((char*)&x.rows, sizeof(int));
		in.read((char*)&x.cols, sizeof(int));

		//�������� ������ �������, ������ �������.
		double **newArr = new double*[x.rows];

		for (int i = 0; i < x.rows; i++) {
			newArr[i] = new double[x.cols];
		}

		//������ �������� �� �����.
		for (int i = 0; i < x.rows; i++) {
			for (int j = 0; j < x.cols; j++) {
				in.read((char*)&newArr[i][j], sizeof(double));
			}
		}

		cout << "���� ��������.\n";

		arr = newArr; // ��������� ������ ��������� �� ����� ������ newArr, � �� arr.
	}
	in.close();
}



void line_determinants(double **arr, double *buff, arr_characteristic x) {

	for (int i = 0; i < x.rows; i++) {

		double line_sum = 0;

		for (int j = 0; j < x.cols; j++) {

			if (j % 2 == 0 && arr[i][j] > 0) {

				line_sum += arr[i][j];

			}

		}

		buff[i] = line_sum;
	}

}



void line_sort(double **arr, double *buff, arr_characteristic x) {

	for (int i = 0; i < x.rows - 1; i++) {

		for (int j = 0; j < x.rows - i - 1; j++) {

			if (buff[j] > buff[j + 1]) {

				swap(buff[j], buff[j + 1]);
				swap(arr[j], arr[j + 1]);

			}

		}

	}

}



void final_out(double **arr, double *buff, arr_characteristic x) {

	for (int i = 0; i < x.rows; i++) {
		for (int j = 0; j < x.cols; j++) {
			cout << setw(10) << arr[i][j] << " ";
		}
		cout << "�������������� ������: " << buff[i] << "\n";
	}

}



void sort_arr(double **&arr, arr_characteristic x) {

	if (x.rows && x.cols) {
		double *buff = new double[x.rows];

		line_determinants(arr, buff, x); // ���������� ������� ���������������� �����.

		line_sort(arr, buff, x); // ������������ ����� ������� � ������������ � ������ �������������.

		final_out(arr, buff, x); // ����� ���������������� ������� � ������������� �����.

		cout << "������ ������������.\n\n";

		delete[] buff;
	}
	else
		cout << "������ �� �������� ��� �� ���������. \n";

}