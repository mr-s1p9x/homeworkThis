#include <iostream>
#include <string>
using namespace std;

//Задание 2.
//Разработать класс Reservoir (водоем). Класс должен обяза- тельно иметь поле «название».
//Класс должен содержать: конструктор по умолчанию, конструктор с параметрами,
//при необходимости реализовать деструктор и конструк- тор копирования.
//Добавить методы для:
//1. Определения приблизительного объема (ширина* длина*максимальная глубина);
//2. Определения площади водной поверхности;
//3. Метод для проверки относятся ли водоемы к одному типу (море-море; бассейн-пруд);
//4. Для сравнения площади водной поверхности водоемов одного типа;
//5. Для копирования объектов;
//6. Остальные методы на усмотрение разработчика (ме-
//тоды set и get).
//Написать интерфейс для работы с классом.
//Реализовать динамический массив объектов класса с возможностью добавления, удаления объектов из массива.


// Класс Reservoir (водоем)
class Reservoir
{
private:
    char* name; // Название водоема. Указатель на динамически выделенную строку
    double width; // Ширина водоема
    double length; // Длина водоема
    double maxDepth; // Максимальная глубина водоема
    char* type; // Тип водоема (например "море", "пруд"). Указатель на динамически выделенный массив

public:
    // Конструктор по умолчанию
    Reservoir() : name(nullptr), width(0), length(0), maxDepth(0), type(nullptr)
    {
        // Инициализация указателя на название пустой строкой
        name = new char[1]; // Выделяем память для пустой строки
        name[0] = '\0'; // Инициализируем пустую строку, чтобы не было ошибок при обращении

        // Инициализация указателя на тип пустой строкой
        type = new char[1]; // Выделяем память для пустой строки
        type[0] = '\0'; // Инициализируем пустую строку, чтобы не было ошибок при обращении
    }

    // Конструктор с параметрами
    Reservoir(const char* n, double w, double l, double md, const char* t) : width(w), length(l), maxDepth(md)
    {
        // Выделяем память под название и копируем его
        name = new char[strlen(n) + 1]; // Выделяем память для строки названия
        strcpy(name, n); // Копируем строку n в name

        // Выделяем память под тип и копируем его
        type = new char[strlen(t) + 1]; // Выделяем память для строки типа
        strcpy(type, t); // Копируем строку t в name
    }

    // Конструктор копирования
    Reservoir(const Reservoir& other) : width(other.width), length(other.length), maxDepth(other.maxDepth)
    {
        // Выделяем память под копию названия и копируем его
        name = new char[strlen(other.name) + 1]; // Выделяем память для строки названия
        strcpy(name, other.name); // Копируем строку other.name в name

        // Выделяем память под копию типа и копируем его
        type = new char[strlen(other.type) + 1]; // Выделяем память для строки типа
        strcpy(type, other.type); // Копируем строку other.type в type
    }

    // Деструктор
    ~Reservoir()
    {
        // Освобождаем память, выделенную под название
        delete[] name;

        // Освобождаем память, выделенную под тип
        delete[] type;
    }

    // Метод определения приблизительного объема водоема (ширина * длина * максимальная глубина)
    double calculateVolume() const
    {
        return width * length * maxDepth; // Возвращаем объем водоема
    }

    // Метод для определения площади водной поверхности (ширина * длина)
    double calculateSurfaceArea() const
    {
        return width * length; // Возвращаем площадь водной поверхности
    }

    // Метод для проверки, относятся ли водоемы к одному типу
    bool isSameType(const Reservoir& other) const
    {
        // Сравниваем строки, чтобы определить, одинаковые ли типы водоемов
        return strcmp(type, other.type) == 0; // Возвращаем true, если строки равны
    }

    // Метод для сравнения площади водной поверхности водоемов одного типа
    bool compareSurfaceArea(const Reservoir& other) const
    {
        // Если типы водоемов разные, выводим сообщение и возвращаем false
        if (!isSameType(other))
        {
            cout << "Reservoir have differ types" << endl;
            return false;
        }
        // Сравниваем площади водоемов одного типа
        return calculateSurfaceArea() > other.calculateSurfaceArea(); // Возвращаем true, если площадь текущего водоема больше
    }

    // Методы set и get для всех полей
    void setName(const char* n)
    {
        // Освобождаем старую память и выделяем новую под новое название.
        delete[] name; // Освобождаем старую память для name
        name = new char[strlen(n) + 1]; // Выделяем новую память для строки названия
        strcpy(name, n); // Копируем строку n в name
    }

    const char* getName() const
    {
        return name; // Возвращаем значение name
    }

    void setWidth(double w) {
        width = w; // Устанавливаем значение width.
    }

    double getWidth() const
    {
        return width; // Возвращаем значение width
    }

    void setLength(double l)
    {
        length = l; // Устанавливаем значение length
    }

    double getLength() const
    {
        return length; // Возвращаем значение length
    }

    void setMaxDepth(double md)
    {
        maxDepth = md; // Устанавливаем значение maxDepth
    }

    double getMaxDepth() const
    {
        return maxDepth; // Возвращаем значение maxDepth
    }

    void setType(const char* t)
    {
        // Освобождаем старую память и выделяем новую под новый тип
        delete[] type; // Освобождаем старую память для type
        type = new char[strlen(t) + 1]; // Выделяем новую память для строки типа
        strcpy(type, t); // Копируем значение type
    }

    const char* getType() const
    {
        return type; // Возвращаем значение type
    }

    // Метод копирования объектов
    Reservoir& operator=(const Reservoir& other)
    {
        if (this == &other) return *this; // Проверка на самоприсваивание

        // Освобождаем старую память
        delete[] name;
        delete[] type;

        // Копируем данные из другого объекта
        width = other.width; // Копируем значение width
        length = other.length; // Копируем значение length
        maxDepth = other.maxDepth; // Копируем значение maxDepth

        // Выделяем новую память и копируем название
        name = new char[strlen(other.name) + 1]; // Выделяем новую память для строки названия.
        strcpy(name, other.name); // Копируем строку other.name в name

        // Выделяем новую память и копируем тип
        type = new char[strlen(other.type) + 1]; // Выделяем новую память для строки типа
        strcpy(type, other.type); // Копируем строку other.type в type

        return *this; // Возвращаем текущий объект для цепочки присваиваний
    }
};

// Функция main для тестирования класса Reservoir
int main()
{
    // Создаем водоемы
    Reservoir lake("Lake", 2000, 3000, 50, "lake");
    Reservoir sea("Sea", 10000, 20000, 500, "sea");

    // Выводим информацию о водоемах
    cout << "Name: " << lake.getName() << endl;
    cout << "Volume: " << lake.calculateVolume() << endl;
    cout << "Square: " << lake.calculateSurfaceArea() << endl;

    // Проверяем, относятся ли водоемы к одному типу
    if (lake.isSameType(sea))
    {
        cout << "Both waters have the same type" << endl;
    }
    else
    {
        cout << "Waters have different types" << endl;
    }

    // Сравниваем площадь водной поверхности водоемов одного типа
    if (lake.compareSurfaceArea(sea))
    {
        cout << "First water has bigger square" << endl;
    }
    else
    {
        cout << "Second water has bigger square or equals first" << endl;
    }

    return 0;
}