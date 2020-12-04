#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct text_characteristic {
	int NL,
		NS,
		NW,
		words,
		len;
};


void info_msg();
void charac_out(text_characteristic);


enum sw_ch{	
	read = 1,
	write,
	out,
	syllable,
	stop };


int int_number_input();

void show(char *arr, text_characteristic);

void in_file(char *&, text_characteristic);

void file_charac(text_characteristic &);

void out_file(text_characteristic);

void text_syllable(char *arr, text_characteristic);

void separator(text_characteristic, char *arr, char **words_list);

void syllables_sort(int words, int *num_syllables, char **words_list);

void syllables_count(int words, char **words_list, int *num_syllables);

void final_out(char **words_list, int *num_syllables, char *arr, text_characteristic);


void input_type(text_characteristic);

void file_manual();

char Y_N();

void fail();

int main() {

	setlocale(LC_ALL, "RUS");
	system("chcp 1251");

	text_characteristic ch = {};
	char *text = new char[ch.len];

	bool loop = true;
	while (loop) {
		system("cls");

		info_msg();
		int i{};
		cout << "������� ����� ������ ����: ";
		i = int_number_input();

		switch (i) {
		case read:

			input_type(ch);

			break;
		case write:

			file_charac(ch);
			in_file(text, ch);

			charac_out(ch);

			break;
		case out:

			show(text, ch);
			break;
		case syllable:

			text_syllable(text, ch);

			break;
		case stop:

			cout << "������ ����������.\n";
			loop = false;
			break;
		default:
			cout << "������������ ������.\n";
		}
		system("pause");
	}

	delete[] text;


}



void info_msg() {

	cout << "��������� ������������� ��� ���������� ���� �� ����������� ������ � ������ ������.\n";
	cout << "� ������ ����������� ������ ���� � ��������� ����.\n\n";

	cout << "------------------------------------------------------------------------------------------------------------\n\n";

	cout << "���� ���������:\n";
	cout << " - ��� ������ ������ ������ � ���� ������� 1\n";
	cout << " - ��� �������� ������ �� ����� ������� 2\n";
	cout << " - ��� ������ ������ � ������� ������� 3\n";
	cout << " - ��� ����������, �������� � ���������� � ����� ���� ��������������� �� ���������� ������ ���� ������� 4\n";
	cout << " - ��� ���������� ������ ������� 5\n\n";

}



void file_manual() {

	cout << "����� �������������� ����� ��������� ��� � ��������� ( 2 ������ )\n";
	system("file.txt");

}



void input_type(text_characteristic ch) {

	int q;
	cout << "����� ���� �����: \n";
	cout << "1 - ����� �������\n";
	cout << "2 - �������������� ����\n";
	cout << "����� ���� �������� ��� ������.\n";
	cout << "�������� ���: ";
	q = int_number_input();
	
	switch (q) {
	case 1:

		out_file(ch);
		break;
	case 2:

		file_manual();
		break;
	default:
		cout << "������ ����������\n";
		break;
	}

}



void charac_out(text_characteristic x) {

	if (x.len && x.NL) {

		cout << "�������������� ������������ ������: \n\n";
		cout << "����� ������: \t" << x.len - x.NL << " ��������\n";
		cout << "���-�� �����: \t" << x.NL << " ������\n";
		cout << "���-�� ����: \t" << x.words << " ����\n";
		cout << "���-�� �������� � ������ (����.): \t" << x.NS << " ��������\n";
		cout << "���������� ���� � ����� (����.): \t" << x.NW << " ��������\n\n";

	}

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
			cout << "������ �����, ��������� ���� (Y/N): ";
	}
}



void fail() {

	if (cin.fail()) {

		cin.clear();
		cin.ignore(32767, '\n');

	}
}



int int_number_input() { // �������������� ������ � int �������� (������ �� ������������� �����).

	char buff[255];
	cin.getline(buff, 255);

	return atoi(buff);
}



void out_file(text_characteristic x) { // ������ ������ � ����.
	
	cout << "������� ���-�� �����: ";
	x.NL = fabs(int_number_input());

	cout << "������� ���-�� �������� � ������: ";
	x.NS = fabs(int_number_input());

	char *buff = new char[2555];

	fstream out("file.txt", ios::out);

	for (int i = 0; i < x.NL; i++) {
		cin.getline(buff, x.NS);
		out << buff;
		if (i < x.NL-1) {
			out << '\n';
		}
		fail();
	}


	out.close();
	delete[] buff;


	if (x.NL && x.NS)
		cout << "��������� ������ �����, ��� ����������� ������ � ������� ��� ���������� ��������� (������ 2).\n";
	else
		cout << "������ ����������, ������������ ������.\n";
}



void show(char *arr, text_characteristic x) { // ����� ������ �� �����.

	if (x.len) {
		cout << "����� ������ �� �����.\n\n";
		cout << arr << "\n\n";
	}
	else
		cout << "����� �����������/�� ��������, ����� ����������.\n";


}



void file_charac(text_characteristic &x) { // ���� ���������� � ������.

	fstream in("file.txt", ios::in);

	char buff;

	bool read = true;

	x = {};


	int buff_word_len = 0, buff_line_len = 0;

	if (!in) {
		x.len = NULL;
	}
	else {
		while (read)
		{
			in.get(buff);
			
			if (in.eof())
				read = false;

			if (!(buff >= 0  && buff <= '@') && read) // ������� ������������ ����� �����.
				buff_word_len++;
			else {
				if (buff_word_len > 0) // ������� ���-�� ����.
					x.words++;
				x.NW = max(buff_word_len, x.NW);
				buff_word_len = 0;
			}

			if (!(buff >= 0 && buff < ' ') && read) { // ������� ������������ ����� ������.
				buff_line_len++;
			}
			else {
				if (buff_line_len >= 0) // ������� ���-�� �����.
					x.NL++;
				x.NS = max(x.NS, buff_line_len);
				buff_line_len = 0;
			}

			x.len++; // ������� ������ ���-�� ��������.
		}
	}

	in.close();
}



void in_file(char *&arr, text_characteristic x) {

	fstream in("file.txt", ios::in);

	if (!in) {
		cout << "������, ���� �� ���������.\n";
	}
	else {
		delete[] arr;
		// �������� ������� ����� ����������� ��� �������� ������ �� �����.
		char *newArr = new char[x.len];

		in.getline(newArr, x.len, '\0');
		arr = newArr;
		cout << "����� ��������.\n";
	}

	in.close();
}



void syllables_count(int words, char **words_list, int *num_syllables) { // ������� ���������� ������ ���-�� ������ ������������ ������ ����.

	char vowels[] = "����������";

	for (int i = 0; i < words; i++) {
		int syllables = 0;
		for (unsigned int j = 0; j < strlen(words_list[i]); j++) {

			words_list[i][j] = tolower(words_list[i][j]);

			for (unsigned int k = 0; k < strlen(vowels); k++) {

				if (vowels[k] == words_list[i][j]) {
					syllables++;
					break;
				}

			}

		}
		num_syllables[i] = syllables;

	}

}



void syllables_sort(int words, int *num_syllables, char **words_list) { // ���������� ������� ���� �� ����������� ���-�� ������

	for (int i = 0; i < words - 1; i++) {

		for (int j = 0; j < words - i - 1; j++) {

			if (num_syllables[j] > num_syllables[j + 1]) {

				swap(num_syllables[j], num_syllables[j + 1]);
				swap(words_list[j], words_list[j + 1]);

			}

		}

	}

}



void final_out(char **words_list, int *num_syllables, char *arr, text_characteristic x) {

	cout << "���������� ������ ���� ��� ������? Y/N: ";

	char q;
	q = Y_N();

	unsigned int max_len;

	if (q == 'Y') {
		cout << "������� ������������ ������: ";
		max_len = int_number_input();
	}
	else if (q == 'N')
		max_len = x.NW;

	fstream out("ans.txt", ios::out);

	cout << "��������� ������ ���������: \n\n";

	cout << "\n" << arr << "\n";
	out << arr << "\n";


	for (int i = 0; i < x.words; i++) { // ������ � ���� � ������������ �� �������.
		

		if (num_syllables[i] != 0) {

			if (num_syllables[i] != num_syllables[i - 1]) {

				cout << "\nC�����: " << num_syllables[i] << ": ";
				out << "\nC�����: " << num_syllables[i] << ": ";

			}

			if (strlen(words_list[i]) <= max_len) {

				cout << words_list[i] << ", ";
				out << words_list[i] << ", ";

			}

		}

	}


	out.close();

	cout << "\n\n";
}



void separator(text_characteristic x, char *arr, char **words_list) {

	char *text = new char[x.len]; // �������� ��������� ������ �� �������� ����� �������� ����� (�.�. strtok_s �������� �������� ������, � ��� ��������� ������ ������ �����).
	strcpy_s(text, x.len, arr);

	char sep[] = "();: -.,=?!_'`^�+/\\\n\t\0"; // ������ ������������ ����.

	char *token;

	char *word = strtok_s(text, sep, &token);

	for (int i = 0; i < x.words; i++) {
		strcpy_s(words_list[i], x.NW, word);
		word = strtok_s(NULL, sep, &token);
	}

	delete[] text; // �������� ��������� ������.

}



void text_syllable(char *arr, text_characteristic x) {

	if (x.len) {
		x.NW++;

		char **words_list = new char*[x.words]; // ������ ��� ����.
		for (int i = 0; i < x.words; i++) {
			words_list[i] = new char[x.NW]; // ������ ��� ����.
		}

		int *num_syllables = new int[x.words]; // ������ ��� �������� �������� ���-�� ������.

		separator(x, arr, words_list);

		syllables_count(x.words, words_list, num_syllables); // ������� ���-�� ������ � ������ � ���������� ������� ���-�� ������.

		syllables_sort(x.words, num_syllables, words_list); // ���������� ���� �� ���-�� ������ ( �� ����������� ).

		final_out(words_list, num_syllables, arr, x); // ����� ��������� ���������� � ���� � �� �������.

		for (int i = 0; i < x.words; i++)
			delete[] words_list[i];

		delete[] words_list;

		delete[] num_syllables;
	}
	else
		cout << "����� �����������/�� ��������.\n";

}