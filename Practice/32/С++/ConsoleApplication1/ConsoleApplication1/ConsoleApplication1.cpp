#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Passenger {
	int passengerid;
	bool survival;
	int pclass;
	string name;
	string sex;
	double age;
	int sibsp;
	int parch;
	string ticket;
	double fare;
	string cabin;
	string embarked;
};

// перегрузка оператора > нужна для сортировки по возрастанию
bool operator> (Passenger chel_1, Passenger chel_2)
{
	return chel_1.age > chel_2.age;
}

ostream& operator<< (ostream& out, vector<Passenger>& v) // выводим вектор с пассажирами в файл
{
	out << "PassengerId, Survived, Pclass, Name, Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked" << '\r';
	for (size_t i = 0; i < v.size(); i++)
	{
		out << v[i].passengerid << ",";
		out << v[i].survival << ",";
		out << v[i].pclass << ",";
		out << v[i].name << ",";
		out << v[i].sex << ",";
		out << v[i].age << ",";
		out << v[i].sibsp << ",";
		out << v[i].parch << ",";
		out << v[i].ticket << ",";
		out << v[i].fare << ",";
		out << v[i].cabin << ",";
		out << v[i].embarked << '\r';
	}
	return out;
}

// получение подстроки из целой строки
string get_sub(string& line, int& i, vector<int>& zpt, string repl = "", int zpt_name_sdvig = 0) {
	string str = "";
	str = line.substr(zpt[i] + 1, zpt[i + 1 + zpt_name_sdvig] - zpt[i] - 1);
	i = i + 1 + zpt_name_sdvig;
	return ((str.size()) ? str : repl);
}

istream& operator>> (istream& in_data, vector<Passenger>& v)
{
	string line;
	Passenger chelovek;
	vector <int> zpt;
	int zpt_name_sdvig = 0; // учитывет, сколько запятых найдено в имени пассажира
	size_t found = std::string::npos;
	int i = 0; // индексная переменная для вектора запятых
	string k = R"("")"; // двойные кавычки, чтобы удалять из некоторых имён
	string name = ""; // временная переменная для имени пассажира

	while (getline(in_data, line, '\r')) // пока не закончился файл, получаем строки: конец строки \r
	{
		if (line.find("PassengerId") != string::npos) continue; // пропускаем обработку колонтитулов из файла

		found = line.find(",");
		while (found != std::string::npos) // подсчитываем количество запятых в строке
		{
			zpt.push_back(found);
			found = line.find(",", found + 1);
		}

		zpt_name_sdvig = zpt.size() - 11; // 11 это количество запятых между 12-ю полями данных
										  // больше 11 это запятые в имени пассажира. их сохраняем


		chelovek.passengerid = stoi(line.substr(0, zpt[0])); // получаем субстроки и заполняем структуру
		i = 0;
		chelovek.survival = !!stoi(get_sub(line, i, zpt));
		chelovek.pclass = stoi(get_sub(line, i, zpt));
		name = get_sub(line, i, zpt, "", zpt_name_sdvig);
		chelovek.sex = get_sub(line, i, zpt);
		chelovek.age = stod(get_sub(line, i, zpt, "0.0"));
		chelovek.sibsp = stoi(get_sub(line, i, zpt, "0"));
		chelovek.parch = stoi(get_sub(line, i, zpt, "0"));
		chelovek.ticket = get_sub(line, i, zpt);
		chelovek.fare = stod(get_sub(line, i, zpt, "0.0"));
		chelovek.cabin = get_sub(line, i, zpt);
		chelovek.embarked = line.substr(zpt[zpt.size() - 1] + 1);

		if (name[0] == '"') name.erase(0, 1); // убираем кавычки в начале строки
		if (name[name.size() - 1] == '"') name.erase(name.size() - 1, 1); // убираем кавычки в конце строки
		while (name.find(k) != string::npos) // убираем все случаи двойных кавычек: ""
		{
			name.erase(name.find(k), 1);
		}
		chelovek.name = name; // почищенное от кавычек имя вносим в структуру
		v.push_back(chelovek); // сохраняем в основном векторе
		zpt.clear(); // очищаем вектор с позициями запятых. в новой строке могут быть в другом месте
	}
	return in_data;
}

template <typename T>
void sorting(vector<T*> v)
{
	T vect;	// временная переменная для структуры
	int ids = 0; // временная переменная для номера пассажира - целое число
	bool sort = true;
	while (sort) // сортируем, пока не будет отсортировано
	{
		sort = false;
		for (auto i = 0; i < v.size() - 1; i++)
		{
			if (*v[i] > *v[i + 1]) // если несортировано, меняем местами
			{
				vect = *v[i];		// меняем местами данные пассажира через временную переменную
				*v[i] = *v[i + 1];
				*v[i + 1] = vect;

				ids = (*v[i]).passengerid; // но вместе с этим ещё и номера поменялись и список стал
				(*v[i]).passengerid = (*v[i + 1]).passengerid; // несортированным
				(*v[i + 1]).passengerid = ids; // устанавливаю номер назад
				sort = true; // была хотя бы одна перестановка, нужно продолжать сортировку
			}
		}
	}
}

int main()
{
	vector<Passenger> train_vect;
	ifstream train("train.csv");
	train >> train_vect; // загружаем из файла, используя перегруженный опреатор >>

	vector<Passenger*> women; // создаём вектор с указателями на выживших пассажирок 1 класса
	for (size_t i = 0; i < train_vect.size(); i++)
	{
		if ((train_vect[i].pclass == 1) && (train_vect[i].sex == "female") && train_vect[i].survival)
		{
			women.push_back(&train_vect[i]); // добавляем ссылку на пассажирку в вектор
		}
	}

	sorting(women); // сортируем данные, на которые указывают указатели
	ofstream save_file("save.csv");
	save_file << train_vect; // сохраняем в файл, использую перегруженный оператор <<
	save_file.close();

	return 0;
}
