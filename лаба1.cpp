
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include <limits>
#include <climits>

using namespace std;

void printSizes()
{
    cout << "\n========== РАЗМЕРЫ ТИПОВ ДАННЫХ ==========\n";

    cout << "bool:       " << sizeof(bool) << " byte(s)\n";
    cout << "char:       " << sizeof(char) << " byte(s)\n";
    cout << "short int:  " << sizeof(short int) << " byte(s)\n";
    cout << "int:        " << sizeof(int) << " byte(s)\n";
    cout << "long int:   " << sizeof(long int) << " byte(s)\n";
    cout << "float:      " << sizeof(float) << " byte(s)\n";
    cout << "double:     " << sizeof(double) << " byte(s)\n";
    cout << "long double:" << sizeof(long double) << " byte(s)\n";

    cout << "\nРазмер указателя: " << sizeof(void*) << " byte(s)\n";

    cout << "\nПримечание: размер некоторых типов зависит от платформы.\n";
}

void printIntegerBits(int32_t number)
{
    uint32_t bits;
    bits = static_cast<uint32_t>(number);

    cout << "\nЧисло: " << number << endl;
    cout << "Двоичное представление:\n";

    for (int i = 31; i >= 0; i--)
    {
        int bit = (bits >> i) & 1;

        if (i == 31)
        {
            cout << "[" << bit << "] ";
        }
        else
        {
            cout << bit;
        }

        if (i % 8 == 0 && i != 0)
        {
            cout << " ";
        }
    }

    cout << "\n[знак] [значащие разряды]\n";
}

void printFloatBits(float number)
{
    uint32_t bits;

    memcpy(&bits, &number, sizeof(float));

    cout << "\nFloat: " << number << endl;

    cout << "Биты: ";

    for (int i = 31; i >= 0; i--)
    {
        cout << ((bits >> i) & 1);

        if (i == 31 || i == 23)
        {
            cout << " ";
        }
    }

    cout << "\nЗнак:      " << ((bits >> 31) & 1);
    cout << "\nПорядок:   ";

    for (int i = 30; i >= 23; i--)
    {
        cout << ((bits >> i) & 1);
    }

    cout << "\nМантисса:  ";

    for (int i = 22; i >= 0; i--)
    {
        cout << ((bits >> i) & 1);
    }

    cout << "\n";
}

void printDoubleBits(double number)
{
    uint64_t bits;

    memcpy(&bits, &number, sizeof(double));

    cout << "\nDouble: " << number << endl;

    cout << "Биты: ";

    for (int i = 63; i >= 0; i--)
    {
        cout << ((bits >> i) & 1);

        if (i == 63 || i == 52)
        {
            cout << " ";
        }
    }

    cout << "\nЗнак:      " << ((bits >> 63) & 1);
    cout << "\nПорядок:   ";

    for (int i = 62; i >= 52; i--)
    {
        cout << ((bits >> i) & 1);
    }

    cout << "\nМантисса:  ";

    for (int i = 51; i >= 0; i--)
    {
        cout << ((bits >> i) & 1);
    }

    cout << "\n";
}

void print32Bits(uint32_t number)
{
    for (int i = 31; i >= 0; i--)
    {
        cout << ((number >> i) & 1);

        if (i % 8 == 0 && i != 0)
        {
            cout << " ";
        }
    }

    cout << endl;
}

void print64Bits(uint64_t number)
{
    for (int i = 63; i >= 0; i--)
    {
        cout << ((number >> i) & 1);

        if (i % 8 == 0 && i != 0)
        {
            cout << " ";
        }
    }

    cout << endl;
}

uint64_t changeBit(uint64_t number, int bit, int operation)
{
    uint64_t mask = 1ULL << bit;

    if (operation == 1)
    {
        // Установить бит в 1
        number = number | mask;
    }
    else if (operation == 2)
    {

        number = number & ~mask;
    }
    else if (operation == 3)
    {
    
        number = number ^ mask;
    }

    return number;
}

void demonstrateFloatDoubleBits()
{
    float f = 3.14f;
    double d = 3.14;

    uint32_t floatBits;
    uint64_t doubleBits;

    memcpy(&floatBits, &f, sizeof(float));
    memcpy(&doubleBits, &d, sizeof(double));

    cout << "\n========== ИЗМЕНЕНИЕ БИТОВ FLOAT ==========\n";

    cout << "Исходные биты:\n";
    print32Bits(floatBits);

    floatBits = static_cast<uint32_t>(
        changeBit(floatBits, 0, 3)
    );

    cout << "После инверсии младшего бита:\n";
    print32Bits(floatBits);

    cout << "\n========== ИЗМЕНЕНИЕ БИТОВ DOUBLE ==========\n";

    cout << "Исходные биты:\n";
    print64Bits(doubleBits);

    doubleBits = changeBit(doubleBits, 0, 3);

    cout << "После инверсии младшего бита:\n";
    print64Bits(doubleBits);
}

void bitManipulation()
{
    uint64_t number;
    int bit;
    int operation;

    cout << "\n========== МАНИПУЛЯЦИЯ БИТАМИ ==========\n";

    cout << "Введите целое положительное число: ";
    cin >> number;

    cout << "Введите номер бита (от 0 до 63): ";
    cin >> bit;

    if (bit < 0 || bit > 63)
    {
        cout << "Ошибка! Номер бита должен быть от 0 до 63.\n";
        return;
    }

    cout << "\nВыберите операцию:\n";
    cout << "1 - установить бит в 1\n";
    cout << "2 - установить бит в 0\n";
    cout << "3 - инвертировать бит\n";

    cout << "Ваш выбор: ";
    cin >> operation;

    if (operation < 1 || operation > 3)
    {
        cout << "Неправильная операция!\n";
        return;
    }

    cout << "\nИсходное число в двоичном виде:\n";
    print64Bits(number);

    number = changeBit(number, bit, operation);

    cout << "\nРезультат в двоичном виде:\n";
    print64Bits(number);

    cout << "Результат в десятичном виде: " << number << endl;
}

void checkEven()
{
    long long number;

    cout << "\n========== ПРОВЕРКА ЧЕТНОСТИ ==========\n";

    cout << "Введите целое число: ";
    cin >> number;

    cout << "Исходное число: " << number << endl;

    cout << "Двоичное представление до изменения:\n";
    printIntegerBits(static_cast<int32_t>(number));

    long long result = number & ~1LL;

    cout << "\nПосле обнуления младшего бита:\n";
    cout << "Результат: " << result << endl;

    cout << "Двоичное представление после изменения:\n";
    printIntegerBits(static_cast<int32_t>(result));

    cout << "\nРезультат всегда является четным числом.\n";
}

int main()
{
    setlocale(LC_ALL, "RU");

    if (sizeof(float) != 4 || sizeof(double) != 8 ||
        !numeric_limits<float>::is_iec559 ||
        !numeric_limits<double>::is_iec559)
    {
        cout << "На данной платформе не поддерживается "
             << "ожидаемый формат IEEE 754.\n";
        return 1;
    }

    cout << "============================================\n";
    cout << "       РАБОТА С ДВОИЧНЫМИ ЧИСЛАМИ\n";
    cout << "============================================\n";


    printSizes();


    cout << "\n========== ЦЕЛЫЕ ЧИСЛА ==========\n";

    printIntegerBits(25);
    printIntegerBits(-25);
    printIntegerBits(0);

    cout << "\n========== FLOAT ==========\n";

    printFloatBits(3.14f);
    printFloatBits(-2.5f);
    printFloatBits(0.0f);
    printFloatBits(numeric_limits<float>::denorm_min());
    printFloatBits(numeric_limits<float>::infinity());

    cout << "\n========== DOUBLE ==========\n";

    printDoubleBits(3.14);
    printDoubleBits(-2.5);
    printDoubleBits(0.0);
    printDoubleBits(numeric_limits<double>::denorm_min());
    printDoubleBits(numeric_limits<double>::infinity());

    bitManipulation();

    demonstrateFloatDoubleBits();

    checkEven();

    cout << "\n============================================\n";
    cout << "          ПРОГРАММА ЗАВЕРШЕНА\n";
    cout << "============================================\n";

    return 0;
}
