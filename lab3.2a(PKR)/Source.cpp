#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Spec { PhIT, ME, СS };

string strSpec[] = { "Фiзика та iнформатика", "Математика та економiка", "Iнформатика" };

struct Student
{
    string lname;
    int kurs;
    Spec spec;
    int physics;
    int math;
    int comscience;
};

void create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "Прiзвище: ";
        cin >> s[i].lname;
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спецiальнiсть (0 - Фiзика та iнформатика, 1 - Математика та економiка, 2 - Iнформатика) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "Оцiнка з фiзики: ";
        cin >> s[i].physics;
        cout << "Оцiнка з математики: ";
        cin >> s[i].math;
        cout << "Оцінка з інформатики: ";
        cin >> s[i].comscience;
    }
}

void print(Student* s, int amSt)
{
    cout << "========================================================================================="
        << endl;
    cout << "| № |    Прiзвище   | Курс |      Спецiальнiсть     | Фiзика | Математика | Інформатика |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++) {

        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[i].lname
            << "| " << setw(5) << right << s[i].kurs
            << "| " << setw(23) << left << strSpec[s[i].spec]
            << "| " << setw(7) << s[i].physics
            << "| " << setw(11) << right << s[i].math
            << "| " << setw(12) << left << s[i].comscience << "| " << endl;

    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}

double avgGrade(Student* s, const int i) {
    return (s[i].math + s[i].physics + s[i].comscience) / 3;
}

void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) //BubbleSort
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((avgGrade(p, i1) > avgGrade(p, i1 + 1))
                ||
                (avgGrade(p, i1) == avgGrade(p, i1 + 1) &&
                    p[i1].lname < p[i1 + 1].lname)
                ||
                (avgGrade(p, i1) == avgGrade(p, i1 + 1) &&
                    p[i1].lname == p[i1 + 1].lname &&
                    p[i1].kurs > p[i1 + 1].kurs))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* indexSort(Student* s, int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && ((avgGrade(s, I[j]) > avgGrade(s, value))//за значенням середнього балу
            ||
            (avgGrade(s, I[j]) == avgGrade(s, value) &&
                s[I[j]].lname < s[value].lname)// (для однакових середніх балів) – за прізвищем за спаданням – в зворотному до алфавітного порядку
            ||
            (avgGrade(s, I[j]) == avgGrade(s, value) &&
                s[I[j]].lname == s[value].lname &&
                s[I[j]].kurs > s[value].kurs));
            j--)//(для однакових середніх балів і прізвищ) – за номером курсу
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* s, int* I, const int amSt)
{
    cout << "========================================================================================="
        << endl;
    cout << "| № |    Прiзвище   | Курс |      Спецiальнiсть     | Фiзика | Математика | Інформатика |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++) {

        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[I[i]].lname
            << "| " << setw(5) << right << s[I[i]].kurs
            << "| " << setw(23) << left << strSpec[s[I[i]].spec]
            << "| " << setw(7) << s[I[i]].physics
            << "| " << setw(11) << right << s[I[i]].math
            << "| " << setw(12) << left << s[I[i]].comscience << "| " << endl;

    }
    cout << "------------------------------------------------------------------------------------------"
        << endl;
}

int binSearch(Student* p, const int N, const string prizv, int kurs)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].lname == prizv && p[m].kurs == kurs && avgGrade(p, m) == avgGrade(p, m))
            return m;
        if ((p[m].lname < prizv)
            ||
            (p[m].lname == prizv &&
                p[m].kurs < kurs)
            ||
            p[m].lname == prizv && p[m].kurs == kurs &&
            avgGrade(p, m) < avgGrade(p, m))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int amSt;
    string lastName;
    Spec spec;
    int specNo, found;
    double avgGrade;
    cout << "Кількість студентів: ";
    cin >> amSt;
    Student* s = new Student[amSt];

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури " << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних " << endl;
        cout << " [4] - індексне впорядкування та вивід даних " << endl;
        cout << " [5] - бінарний пошук для визначення, чи навчається студент " << endl;
        cout << " із вказаним користувачем прізвищем на вказаній спеціальності та вказаним середнім балом." << endl;
        cout << " [0] - вихід та завершення програми " << endl;
        cout << "Введіть значеня: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            create(s, amSt);
            break;
        case 2:
            print(s, amSt);
            break;
        case 3:
            Sort(s, amSt);
            break;
        case 4:
            PrintIndexSorted(s, indexSort(s, amSt), amSt);
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " Прізвище: "; cin >> lastName;
            cout << endl;
            cout << " Спецiальнiсть (0 - Фiзика та iнформатика, 1 - Математика та економiка, 2 - Iнформатика) ";
            cin >> specNo;
            spec = (Spec)specNo;
            cout << " Середній бал: ";
            cin >> avgGrade;
            cin.get();
            cin.sync();

            if ((found = binSearch(s, amSt, lastName, spec)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}
