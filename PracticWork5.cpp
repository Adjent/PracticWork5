#define NOMINMAX
#include <iostream>
#include <fstream>
#include <limits>
#include <Windows.h>

using namespace std;

struct Student {
    int number;
    char name[100];
    int group;
    bool isMale;
    int marks[8];
};

//загрузка студентов из файла
int load(Student arr[]) {
    int count = 0;
    ifstream file("students.txt");

    if (!file)
        return 0;

    while (true) {
        file >> arr[count].number;
        if (file.fail())break;
        file.get();
        file.getline(arr[count].name, 100, '|');
        file >> arr[count].group >> arr[count].isMale;
        for (int i = 0; i < 8; i++)file >> arr[count].marks[i];
        count++;
    }
    file.close();
    return count;
}

//сохранение списка студентов в текстовый файл
void save(Student arr[], int count) {
    ofstream file("students.txt");

    for (int i = 0; i < count; i++) {
        file << arr[i].number << ' ' << arr[i].name << "|" << arr[i].group << ' ' << arr[i].isMale << ' ';
        for (int j = 0; j < 8; j++)
            file << arr[i].marks[j] << ' ';
        file << "\n";
    }

    file.close();
}

//добавление новой записи о студенте
void addStudent(Student arr[], int& count) {
    arr[count].number = count + 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//очистка буфера ввода
    cout << "Добавление новой записи о студенте.\nВведите ФИО: ";
    cin.getline(arr[count].name, 100);
    cout << "Группа: ";
    cin >> arr[count].group;
    cout << "Пол (1 - муж, 0 - жен): ";
    cin >> arr[count].isMale;
    cout << "Введите 8 оценок:\n";
    for (int i = 0; i < 8; i++)
        cin >> arr[count].marks[i];
    count++;
    save(arr, count);
    cout << "Запись о студенте добавлена\n";
}

//изменение записи о студенте
void editStudent(Student arr[], int count) {
    int num;
    int choice;
    cout << "Введите номер студента: ";
    cin >> num;
    if (num <= 0 || num > count) {
        cout << "Студент не найден!\n";
        return;
    }
    Student& s = arr[num - 1];
    

    cout << "Что необходимо изменить?\n"\
        << "1.ФИО студента\n"\
        << "2.Номер группы\n"\
        << "3.Пол\n"\
        << "4.Оценки\n";
    cin >> choice;
    switch (choice) {

    case 1:
        cout << "ФИО: ";
        cin.ignore();
        cin.getline(s.name, 100);
        break;

    case 2:
        cout << "Номер группы: ";
        cin >> s.group;
        break;

    case 3:
        cout << "Пол (1-муж, 0-жен): ";
        cin >> s.isMale;
        break;

    case 4:
        cout << "Введите оценки за 3 экзамена и 5 зачетов:\n";
        for (int i = 0; i < 8; i++)
            cin >> s.marks[i];
        break;
    }
    save(arr, count);
    cout << "Данные о студенте обновлены.\n";
}

//вывод информации о всех студентах
void showAll(Student arr[], int count) {
    cout << "Все студенты:\n";
    for (int i = 0; i < count; i++) {
        cout << arr[i].number << ' ' << arr[i].name << ' ' << arr[i].group << ' ' << (arr[i].isMale ? 'М' : 'Ж') << ' ';
        for (int j = 0; j < 8; j++)
            cout << arr[i].marks[j] << ' ';
        cout << '\n';
    }
}

//вывод студентов по номеру группы
void showGroup(Student arr[], int count) {
    int g;

    cout << "Введите номер группы: ";
    cin >> g;
    cout << "\nВсе студенты группы " << g << '\n';
    for (int i = 0; i < count; i++) {
        if (arr[i].group == g) {
            cout << arr[i].name << ' ' << arr[i].group << ' ' << (arr[i].isMale ? 'М' : 'Ж') << ' ';
            for (int j = 0; j < 8; j++)cout << arr[i].marks[j] << ' ';
            cout << '\n';
        }
    }
}

//подсчет кол-ва стуентов по полу
void countGender(Student arr[], int count) {
    int male = 0;
    for (int i = 0; i < count; i++) {
        male += int(arr[i].isMale);
    }
    cout << "Кол-во студентов каждого пола.\nМужчин: " << male \
        << "\nЖенщин: " << count - male << "\n";
}

//подсчет среднего значения
double averageScore(Student s) {
    double sum = 0;
    for (int i = 0; i < 8; i++)
        sum += s.marks[i];
    return sum / 8.0;
}

//топ студентов по среднему баллу 
void topRating(Student arr[], int count) {
    Student temp[100];
    for (int i = 0; i < count; i++)
        temp[i] = arr[i];
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (averageScore(temp[i]) < averageScore(temp[j])) {
                Student t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
    cout << "Топ студентов по среднему баллу за сессию:\n";
    for (int i = 0; i < count; i++)cout << i + 1 << '.' << temp[i].name << ' ' << "Средний балл: " << averageScore(temp[i]) << "\n";
}

//вывод информации о студенте по номеру в списке
void showStudent(Student arr[], int count) {
    int num;

    cout << "Введите номер студента: ";
    cin >> num;
    num--;
    if (num > count) { 
        cout << "Студента с таким номером еще нет.\n"; 
        return;
    }
    else cout << arr[num].name << ' ' << arr[num].group << ' ' << (arr[num].isMale ? 'М' : 'Ж') << ' ';
    for (int i = 0; i < 8; i++)cout << arr[num].marks[i] << ' ';
    cout << '\n';
}

//проверка оценок на наличие 3
bool averageStudents(Student s) {
    for (int i = 0; i < 8; i++) if (s.marks[i] <= 3)return true;
    return false;
}

//проверка на отличника
bool excellentStudents(Student s) {
    for (int i = 0; i < 8; i++)if (s.marks[i] != 5) return false;
    return true;
}

//вывод студентов группами по успеваемости
void studentsGrade(Student arr[], int count) {
    int choice;

    cout << "Информацию о каких стужентах необходимо вывести?\n"\
        << "1.Отличники\n"\
        << "2.Ударники\n"\
        << "3.Без стипендии\n";
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Все студенты сдавшие сессию только на Отлично\n";
        for (int i = 0; i < count; i++) {
            if (excellentStudents(arr[i])) {
                cout << arr[i].name << ' ' << arr[i].group << ' ' << (arr[i].isMale ? 'М' : 'Ж') << ' ';
                for (int j = 0; j < 8; j++)
                    cout << arr[i].marks[j] << ' ';
                cout << '\n';
            }
        }
        break;
    case 2:
        cout << "Все студенты сдавшие сессию только на Хорошо и Отлично\n";
        for (int i = 0; i < count; i++) {
            if (!excellentStudents(arr[i]) && !averageStudents(arr[i])) {
                cout << arr[i].name << ' ' << arr[i].group << ' ' << (arr[i].isMale ? 'М' : 'Ж') << ' ';
                for (int j = 0; j < 8; j++)
                    cout << arr[i].marks[j] << ' ';
                cout << '\n';
            }
        }
        break;
    case 3:
        cout << "Все студенты оставшиеся без стипендии\n";
        for (int i = 0; i < count; i++) {
            if (averageStudents(arr[i])) {
                cout << arr[i].name << ' ' << arr[i].group << ' ' << (arr[i].isMale ? 'М' : 'Ж') << ' ';
                for (int j = 0; j < 8; j++)
                    cout << arr[i].marks[j] << ' ';
                cout << '\n';
            }
        }
        break;
    default:
        cout << "Некорректный выбор.\n";
        return;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Student students[100];
    int count = load(students);
    int choice;

    do {
        cout << "1.Создать новую запись\n"\
            << "2.Внести изменение\n"\
            << "3.Вывод информации о всех студентах\n"\
            << "4.Вывод информации о студентах группы по номеру\n"\
            << "5.Вывести топ студентов по среднему балу за сессию\n"\
            << "6.Вывести кол-во сутдентов мужского и женского пола\n"\
            << "7.Вывод информации о студентах по уровню успеваемости\n"\
            << "8.Вывод информации о стуенте по номеру в списке.\n"\
            << "0.Выход\n";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1: 
            addStudent(students, count); 
            break;
        case 2: 
            showAll(students, count);
            editStudent(students, count); 
            break;
        case 3: 
            showAll(students, count); 
            break;
        case 4: 
            showGroup(students, count); 
            break;
        case 5: 
            topRating(students, count); 
            break;
        case 6: 
            countGender(students, count); 
            break;
        case 7:
            studentsGrade(students, count);
            break;
        case 8:
            showStudent(students, count);
            break;
        default:
            cout << "Некорректный номер операции. Введите корректный номер.\n\n";
            break;
        }
        system("pause");
        system("cls");
    } while (choice != 0);
    return 0;
}