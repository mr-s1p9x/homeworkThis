#include <iostream>
#include <string>
using namespace std;

//Задание 1.
//Создайте программу, имитирующую многоквартирный дом. Необходимо иметь классы «Человек», «Квартира», «Дом».
//Класс «Квартира» содержит динамический массив объектов класса «Человек».
//Класс «Дом» содержит массив объектов класса «Квартира».
//Каждый из классов содержит переменные-члены и функ- ции-члены, которые необходимы для предметной области класса.
//Обращаем ваше внимание, что память под стро- ковые значения выделяется динамически. Например, для ФИО в классе «Человек».
//Не забывайте обеспечить классы различными конструкторами (конструктор копирования обязателен),
//деструкторами. В main протестировать ра- боту полученного набора классов.


// Класс Person описывает человека, включая его имя
class Person
{
private:
    char* name; // Имя человека, хранится как строка

public:
    // Конструктор по умолчанию инициализирует имя как "Unknown"
    Person()
    {
        name = new char[8]; // Выделяем память под строку "Unknown" (7 символов + 1 нуль-терминатор).
        strcpy(name, "Unknown"); // Копируем строку "Unknown" в выделенную память.
    }

    // Конструктор с параметром позволяет задать имя при создании объекта
    Person(const char* n)
    {
        name = new char[strlen(n) + 1]; // Выделяем память под строку n (длина строки + 1 для нуль-терминатора).
        strcpy(name, n);  // Копируем строку n в выделенную память.
    }

    // Конструктор копирования создает новый объект Person на основе существующего
    Person(const Person& other)
    {
        name = new char[strlen(other.name) + 1]; // Выделяем память под копию строки (длина строки + 1).
        strcpy(name, other.name);  // Копируем строку из другого объекта.
    }

    // Присваивания для корректного копирования объектов
    Person& operator=(const Person& other)
    {
        if (this == &other) return *this; // Проверка на самоприсваивание
        delete[] name; // Освобождаем старую память.
        name = new char[strlen(other.name) + 1]; // Выделяем новую память под копию строки.
        strcpy(name, other.name); // Копируем строку из другого объекта
        return *this; // Возвращаем текущий объект для цепочки присваиваний
    }

    // Деструктор для объекта Person, вызывается при удалении объекта
    ~Person()
    {
        delete[] name;
    }

    // Функция для вывода имени человека
    void print() const
    {
        cout << "Name: " << name << endl;
    }
};

// Класс Apartment содержит массив жителей
class Apartment
{
private:
    Person* residents; // указатель на массив объектов Person
    int numResidents;  // текущее колв-о жителей в массиве
    int capacity;      // максимальное кол-во жителей, которое может хранить массив

public:
    // Конструктор инициализирует пустой массив жителей
    Apartment() : residents(nullptr), numResidents(0), capacity(0) {}

    // Конструктор копирования
    Apartment(const Apartment& other) : numResidents(other.numResidents), capacity(other.capacity)
    {
        residents = new Person[capacity];  // Выделяем память под массив жителей
        for (int i = 0; i < numResidents; i++)
        {
            residents[i] = other.residents[i]; // Копируем каждого жителя
        }
    }

    // Оператор присваивания
    Apartment& operator=(const Apartment& other)
    {
        if (this == &other) return *this; // Проверка на самоприсваивание
        delete[] residents; // Освобождаем старую память
        numResidents = other.numResidents;
        capacity = other.capacity;
        residents = new Person[capacity]; // Выделяем память под массив жителей
        for (int i = 0; i < numResidents; i++)
        {
            residents[i] = other.residents[i]; // Копируем каждого жителя
        }
        return *this; // Возвращаем текущий объект для цепочки присваиваний
    }

    // Деструктор освобождает память, выделенную под массив жителей
    ~Apartment()
    {
        delete[] residents;
    }

    // Метод добавляет нового жителя в квартиру
    void addResident(const Person& p)
    {
        if (numResidents == capacity)
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;  // Увеличиваем вместимость массива.
            Person* newResidents = new Person[capacity];  // Выделяем новую память под массив.
            for (int i = 0; i < numResidents; i++)
            {
                newResidents[i] = residents[i]; // Копируем старых жителей в новый массив.
            }
            delete[] residents; // Освобождаем старую память
            residents = newResidents; // Устанавливаем указатель на новый массив
        }
        residents[numResidents++] = p; // Добавляем нового жителя и увеличиваем счетчик.
    }

    // Вывод информацию о всех жителях квартиры
    void printResidents() const
    {
        for (int i = 0; i < numResidents; i++)
        {
            residents[i].print();
        }
    }
};

// Класс House содержит массив квартир
class House
{
private:
    Apartment* apartments;  // Указатель на массив объектов Apartment
    int numApartments;      // Текущее количество квартир в доме
    int capacity;           // Максимальное количество квартир, которое может хранить массив

public:
    // Конструктор инициализирует пустой массив квартир.
    House() : apartments(nullptr), numApartments(0), capacity(0) {}

    // Конструктор копирования.
    House(const House& other) : numApartments(other.numApartments), capacity(other.capacity)
    {
        apartments = new Apartment[capacity]; // Выделяем память под массив квартир
        for (int i = 0; i < numApartments; i++)
        {
            apartments[i] = other.apartments[i]; // Копируем каждую квартиру
        }
    }

    // Оператор присваивания.
    House& operator=(const House& other)
    {
        if (this == &other) return *this;  // Проверка на самоприсваивание
        delete[] apartments; // Освобождаем старую память
        numApartments = other.numApartments;
        capacity = other.capacity;
        apartments = new Apartment[capacity];  // Выделяем память под массив квартир
        for (int i = 0; i < numApartments; i++)
        {
            apartments[i] = other.apartments[i]; // Копируем каждую квартиру
        }
        return *this; // Возвращаем текущий объект для цепочки присваиваний
    }

    // Деструктор освобождает память, выделенную для массива квартир.
    ~House()
    {
        delete[] apartments;
    }

    // Метод добавляет новую квартиру в дом.
    void addApartment(const Apartment& apt)
    {
        if (numApartments == capacity)
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;  // Увеличиваем вместимость массива
            Apartment* newApartments = new Apartment[capacity];  // Выделяем новую память под массив.
            for (int i = 0; i < numApartments; i++)
            {
                newApartments[i] = apartments[i];  // Копируем старые квартиры в новый массив.
            }
            delete[] apartments; // Освобождаем старую память
            apartments = newApartments; // Устанавливаем указатель на новый массив.
        }
        apartments[numApartments++] = apt;  // Добавляем новую квартиру и увеличиваем счетчик.
    }

    // Выводит информацию о всех квартирах в доме
    void printApartments() const
    {
        for (int i = 0; i < numApartments; i++)
        {
            cout << "Apartment " << i + 1 << ":" << endl;
            apartments[i].printResidents(); // Вызываем метод printResidents для каждой квартиры.
        }
    }
};

int main()
{
    // Создание и тестирование классов Person, Apartment и House.
    Person p1("John Doe");
    Person p2("Jane Doe");

    Apartment apt1;
    apt1.addResident(p1);
    apt1.addResident(p2);

    House house;
    house.addApartment(apt1);

    // Вывод информации о доме и его жителях.
    house.printApartments();

    return 0;
}
