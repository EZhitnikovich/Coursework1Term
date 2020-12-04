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
		cout << "Введите номер пункта меню: ";
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

			cout << "Работа прекращена.\n";
			loop = false;
			break;
		default:
			cout << "Некорректный индекс.\n";
		}
		system("pause");
	}

	delete[] text;


}



void info_msg() {

	cout << "Программа предназначена для сортировки слов по колличеству слогов в разные строки.\n";
	cout << "И записи полученного списка слов в отдельный файл.\n\n";

	cout << "------------------------------------------------------------------------------------------------------------\n\n";

	cout << "Меню программы:\n";
	cout << " - Для записи нового текста в файл введите 1\n";
	cout << " - Для загрузки текста из файла введите 2\n";
	cout << " - Для вывода текста в косноль введите 3\n";
	cout << " - Для сортировки, подсчёта и сохранения в новый файл отсортированных по количеству слогов слов введите 4\n";
	cout << " - Для завершения работы введите 5\n\n";

}



void file_manual() {

	cout << "После редактирования файла сохраните его и загрузите ( 2 индекс )\n";
	system("file.txt");

}



void input_type(text_characteristic ch) {

	int q;
	cout << "Выбор типа ввода: \n";
	cout << "1 - через консоль\n";
	cout << "2 - отредактировав файл\n";
	cout << "Любое иное значение для отмены.\n";
	cout << "Выберите тип: ";
	q = int_number_input();
	
	switch (q) {
	case 1:

		out_file(ch);
		break;
	case 2:

		file_manual();
		break;
	default:
		cout << "Отмена перезаписи\n";
		break;
	}

}



void charac_out(text_characteristic x) {

	if (x.len && x.NL) {

		cout << "Характеристика загруженного текста: \n\n";
		cout << "Динна текста: \t" << x.len - x.NL << " символов\n";
		cout << "Кол-во строк: \t" << x.NL << " строки\n";
		cout << "Кол-во слов: \t" << x.words << " слов\n";
		cout << "Кол-во символов в строке (макс.): \t" << x.NS << " символов\n";
		cout << "Количество букв в слове (макс.): \t" << x.NW << " символов\n\n";

	}

}



char Y_N()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
	{
		char y_n;
		cin >> y_n;

		cin.ignore(32767, '\n');

		// Проверка пользовательского ввода
		if (y_n == 'Y' || y_n == 'N')
			return y_n;
		else // в противном случае, сообщаем пользователю что что-то пошло не так
			cout << "Ошибка ввода, повторите ввод (Y/N): ";
	}
}



void fail() {

	if (cin.fail()) {

		cin.clear();
		cin.ignore(32767, '\n');

	}
}



int int_number_input() { // преобразование текста в int значение (защита от некорректного ввода).

	char buff[255];
	cin.getline(buff, 255);

	return atoi(buff);
}



void out_file(text_characteristic x) { // запись текста в файл.
	
	cout << "Введите кол-во строк: ";
	x.NL = fabs(int_number_input());

	cout << "Введите кол-во символов в строке: ";
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
		cout << "Произошла запись файла, для продолжения работы с текстом его необходимо загрузить (индекс 2).\n";
	else
		cout << "Отмена перезаписи, некорректный размер.\n";
}



void show(char *arr, text_characteristic x) { // вывод текста на экран.

	if (x.len) {
		cout << "Вывод текста на экран.\n\n";
		cout << arr << "\n\n";
	}
	else
		cout << "Текст некорректен/не загружен, вывод невозможен.\n";


}



void file_charac(text_characteristic &x) { // сбор информации о тексте.

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

			if (!(buff >= 0  && buff <= '@') && read) // подсчёт максимальной длины слова.
				buff_word_len++;
			else {
				if (buff_word_len > 0) // подсчёт кол-ва слов.
					x.words++;
				x.NW = max(buff_word_len, x.NW);
				buff_word_len = 0;
			}

			if (!(buff >= 0 && buff < ' ') && read) { // подсчёт максимальной длины строки.
				buff_line_len++;
			}
			else {
				if (buff_line_len >= 0) // подсчёт кол-ва строк.
					x.NL++;
				x.NS = max(x.NS, buff_line_len);
				buff_line_len = 0;
			}

			x.len++; // подсчёт общего кол-ва символов.
		}
	}

	in.close();
}



void in_file(char *&arr, text_characteristic x) {

	fstream in("file.txt", ios::in);

	if (!in) {
		cout << "Ошибка, файл не обнаружен.\n";
	}
	else {
		delete[] arr;
		// Создание массива новой размерности для загрузки текста из файла.
		char *newArr = new char[x.len];

		in.getline(newArr, x.len, '\0');
		arr = newArr;
		cout << "Текст загружен.\n";
	}

	in.close();
}



void syllables_count(int words, char **words_list, int *num_syllables) { // функция заполнения списка кол-ва слогов относительно списка слов.

	char vowels[] = "ауоыиэяюёе";

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



void syllables_sort(int words, int *num_syllables, char **words_list) { // сортировка массива слов по возрастанию кол-ва слогов

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

	cout << "Ограничить длинну слов для вывода? Y/N: ";

	char q;
	q = Y_N();

	unsigned int max_len;

	if (q == 'Y') {
		cout << "Введите максимальную длинну: ";
		max_len = int_number_input();
	}
	else if (q == 'N')
		max_len = x.NW;

	fstream out("ans.txt", ios::out);

	cout << "Результат работы программы: \n\n";

	cout << "\n" << arr << "\n";
	out << arr << "\n";


	for (int i = 0; i < x.words; i++) { // запись в файл и дублирование на консоль.
		

		if (num_syllables[i] != 0) {

			if (num_syllables[i] != num_syllables[i - 1]) {

				cout << "\nCлогов: " << num_syllables[i] << ": ";
				out << "\nCлогов: " << num_syllables[i] << ": ";

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

	char *text = new char[x.len]; // создание дубликата текста из которого будут вырезаны слова (т.к. strtok_s изменяет основной массив, в нем останется только первое слово).
	strcpy_s(text, x.len, arr);

	char sep[] = "();: -.,=?!_'`^—+/\\\n\t\0"; // список разделителей слов.

	char *token;

	char *word = strtok_s(text, sep, &token);

	for (int i = 0; i < x.words; i++) {
		strcpy_s(words_list[i], x.NW, word);
		word = strtok_s(NULL, sep, &token);
	}

	delete[] text; // удаление дубликата текста.

}



void text_syllable(char *arr, text_characteristic x) {

	if (x.len) {
		x.NW++;

		char **words_list = new char*[x.words]; // массив для слов.
		for (int i = 0; i < x.words; i++) {
			words_list[i] = new char[x.NW]; // ячейки для слов.
		}

		int *num_syllables = new int[x.words]; // массив для хранения значения кол-ва слогов.

		separator(x, arr, words_list);

		syllables_count(x.words, words_list, num_syllables); // подсчёт кол-ва слогов в словах и заполнение массива кол-ва слогов.

		syllables_sort(x.words, num_syllables, words_list); // сортировка слов по кол-ву слогов ( по возрастанию ).

		final_out(words_list, num_syllables, arr, x); // вывод конечного результата в файл и на консоль.

		for (int i = 0; i < x.words; i++)
			delete[] words_list[i];

		delete[] words_list;

		delete[] num_syllables;
	}
	else
		cout << "Текст некорректен/не загружен.\n";

}