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
		cout << "Введите номер пункта меню: ";
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

			cout << "Работа прекращена." << endl;
			loop = false;
			break;
		default:

			cout << "Некорректный индекс" << endl;
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

	cout << "Тип создания матрицы: \n";
	cout << "1 - Вручную;\n";
	cout << "2 - Сгенерировать.\n";
	cout << "Иное значение для отмены.\n";
	cout << "Выберите тип: ";
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
		cout << "Отмена перезаписи.\n";
		break;
	}

	if (show_arr && x.cols && x.rows) {
		out_arr(arr, x);

		cout << "Записать данный массив в файл? Y/N: ";
		q = Y_N();

		if (q == 'Y') {
			cout << "Массив будет сохранен в файл\n\n";
			out_file(arr, x);
		}
		else if (q == 'N')
			cout << "Массив не будет записан в файл.\n\n";
	}
	else {
		cout << "Недоступна перезапись файла\n";
		cout << "Некорректный размер или перезапись отменена.\n";
	}

}


void info() {

	cout << "Программа предназначена для перестановки строк в матрице в соответствии с ростом характеристик\n";
	cout << "Характеристикой строки матрицы является сумма её положительных элементов, имеющих четные значения индексов\n\n";

	cout << "---------------------------------------------------------------------------------------------------------------\n\n";

	cout << "Меню программы:\n";
	cout << "Для загрузки заготовленной матрицы из файла введите 1\n";
	cout << "Для генерации/ввода новой матрицы и записи её в файл введите 2\n";
	cout << "Для вывода матрицы в косноль введите 3\n";
	cout << "Для перестановки строк в матрице в соответствии с ростом характеристик введите 4\n";
	cout << "Для завершения работы введите 5\n\n";

}



int int_number_input() { // преобразование текста в int значение.

	const int buff_size = 255;
	char buff[buff_size];
	cin.getline(buff, buff_size);

	return atoi(buff);
}



double double_number_input() { // преобразование текста в int значение.

	const int buff_size = 255;
	char buff[buff_size];
	cin.getline(buff, buff_size);

	return atof(buff);
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
			cout << "Ошибка ввода, повторите ввод (Y/N): \n";
	}
}



void in_arr(double **&arr, arr_characteristic &x) {

	//Удалением массива освобождением памяти на случай если он уже содержал данные/не правильного размера.
	for (int i = 0; x.rows > 0 && i < x.rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	cout << "Введите кол-во строк: ";
	x.rows = fabs(int_number_input());

	cout << "Введите кол-во столбцов: ";
	x.cols = fabs(int_number_input());

	//Создание нового массива, нового размера.
	double **newArr = new double*[x.rows];
	for (int i = 0; i < x.rows; i++) {
		newArr[i] = new double[x.cols];
	}

	for (int i = 0; i < x.rows; i++) {
		cout << "Элементы строки " << i << "\n";
		for (int j = 0; j < x.cols; j++) {
			newArr[i][j] = double_number_input();
		}
	}

	arr = newArr;
}



void gen(double **&arr, arr_characteristic &x) { // параметр arr передается по ссылке.

	//Удалением массива освобождением памяти на случай если он уже содержал данные/не правильного размера.
	for (int i = 0; x.rows > 0 && i < x.rows; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	cout << "Введите кол-во строк: ";
	x.rows = fabs(int_number_input());

	cout << "Введите кол-во столбцов: ";
	x.cols = fabs(int_number_input());

	double start, end;

	cout << "Введите начальное значение диапазона чисел: ";
	start = double_number_input();

	cout << "Введите конечное значение диапазона чисел: ";
	end = double_number_input();

	//Создание нового массива, нового размера.
	double **newArr = new double*[x.rows];

	for (int i = 0; i < x.rows; i++) {
		newArr[i] = new double[x.cols];
	}

	//Заполнение массива числами типа double.
	for (int i = 0; i < x.rows; i++) {
		for (int j = 0; j < x.cols; j++) {
			newArr[i][j] = (double)rand() / RAND_MAX * (end - start) + start;
		}
	}

	arr = newArr; // указатель теперь указывает на адрес памяти newArr, а не arr.

	cout << "Массив сгенерирован.\n\n";
}



void out_arr(double **arr, arr_characteristic x) {

	if (x.cols && x.rows) {
		cout << "Массив размерностью " << x.rows << "x" << x.cols << "\n";
		cout << "Вывод массива: \n";

		for (int i = 0; i < x.rows; i++) {
			for (int j = 0; j < x.cols; j++) {
				cout << setw(10) << arr[i][j] << " ";
			}
			cout << "\n";
		}

		cout << "\n";
	}
	else
		cout << "Недопустимое кол-во строк для вывода, кол-во строк: " << x.rows << " кол-во столбцов: " << x.cols << "\n";
}



void out_file(double **arr, arr_characteristic x) {

	fstream out("file.dat", ios::binary | ios::out);

	//Запись размерности массива в файл.
	out.write((char*)&x.rows, sizeof(int));
	out.write((char*)&x.cols, sizeof(int));

	//Запись значений в файл.
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
		cout << "Файл не обнаружен.\n";
	}
	else {
		//Удалением массива освобождение памяти на случай если он уже содержал данные.
		for (int i = 0; x.rows > 0 && i < x.rows; i++) {
			delete[] arr[i];
		}

		delete[] arr;

		//Чтение размерности массива из файла.
		in.read((char*)&x.rows, sizeof(int));
		in.read((char*)&x.cols, sizeof(int));

		//Создание нового массива, нового размера.
		double **newArr = new double*[x.rows];

		for (int i = 0; i < x.rows; i++) {
			newArr[i] = new double[x.cols];
		}

		//Чтение значений из файла.
		for (int i = 0; i < x.rows; i++) {
			for (int j = 0; j < x.cols; j++) {
				in.read((char*)&newArr[i][j], sizeof(double));
			}
		}

		cout << "Файл загружен.\n";

		arr = newArr; // указатель теперь указывает на адрес памяти newArr, а не arr.
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
		cout << "Характеристика строки: " << buff[i] << "\n";
	}

}



void sort_arr(double **&arr, arr_characteristic x) {

	if (x.rows && x.cols) {
		double *buff = new double[x.rows];

		line_determinants(arr, buff, x); // заполнение массива характеристиками строк.

		line_sort(arr, buff, x); // перестановка строк матрицы в соответствии с ростом характеристик.

		final_out(arr, buff, x); // вывод отсортированного массива и характеристик строк.

		cout << "Массив отсортирован.\n\n";

		delete[] buff;
	}
	else
		cout << "Массив не загружен или не корректен. \n";

}