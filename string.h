/*
В этой задаче запрещено пользоваться какими-либо стандартными контейнерами. Выделения памяти нужно делать вручную. 
Разрешается подключать только <iostream> и <cstring> (можно подключить <algorithm> для использования std::fill и std::copy).
Напишите класс String - упрощенный аналог библиотечного std::string. 

Необходимо поддержать следующий функционал:
Конструктор от C-style строки (const char*).
Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
Конструктор по умолчанию, копирующий конструктор и оператор присваивания. Оператор присваивания должен корректно 
обрабатывать присваивание самому себе.
Оператор ==, позволяющий проверять строки на совпадение, оператор !=, а также операторы < > <= >= для лексикографического 
сравнения строк.
Квадратные скобки, корректно работающие как для константных, так и для неконстантных строк.
Метод length(), возвращающий размер строки. А также методы size() и capacity(), возвращающие соответственно размер и
текущую емкость. Терминирующий символ 0 ни там, ни там не учитывается.
Методы push_back(char) и pop_back(). Амортизированное время работы push_backдолжно быть O(1). Метод pop_back должен 
работать за гарантированное O(1), то есть не перевыделять память.
Методы front() и back(), возвращающие ссылку на начальный и на последний символы строки соответственно. Должны корректно
работать и для константных, и для неконстантных строк.
Оператор +=, позволяющий добавить к строке символ или другую строку. Добавление символа должно работать за амортизированное
O(1).
Оператор +, позволяющий складывать строки с символами, символы со строками и строки со строками.
Методы find(substring) и rfind(substring), позволяющие найти самое левое и самое правое вхождение подстроки substring 
в данную строку. Возвращают индекс найденного вхождения. Если вхождений не найдено, нужно вернуть length() (фиктивный
индекс).
Метод substr(start, count), возвращающий подстроку начиная с индекса start и состоящую из count символов.
Метод empty(), проверяющий, пуста ли строка. Метод clear(), позволяющий очистить строку. В методе clear делается 
только обнуление размера, но не освобождение памяти.
Метод shrink_to_fit(), освобождающий лишнюю использованную память.
Операторы вывода в поток « и ввода из потока ».
Метод data(), возвращающий указатель на начало строки. Корректно должен работать как для константных, так и для 
неконстантных строк.
  Дополнительные замечания:
Строка должна заканчиваться символом с кодом 0. (Стандартный std::string тоже обладает этим свойством.) 
Это нужно, чтобы в случае использования data() можно было корректно работать с полученной сишной строкой.
Количество вызовов new нужно стараться свести к минимуму. В частности, в операторе += нельзя добавлять символ за символом,
надо сразу выделить память на всю добавляемую строку. Аналогично в методе substring. В операторе присваивания, если
текущая строка длиннее присваиваемой, стоит обойтись без перевыделения памяти.
Для заполнения строки символами, а также для копирования строк не надо использовать цикл с поэлементным присваиванием.
Надо использовать memset и memcpy, а еще лучше – std::fill и std::copy.
В вашем файле должна отсутствовать функция main(), а сам файл должен называться string.h. 
В качестве компилятора необходимо указывать Make C++17. Ваш код будет вставлен посредством команды #include "string.h" 
в программу, содержащую тесты; вследствие этого код необходимо отправлять в файле со строго соответствующим именем!
*/

#pragma once
#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>

class String {
    size_t size_;
    size_t capacity_;
    char* array;
    void swap(String& str);
    void memory_allocation(size_t newcapacity_);
public:
    String() : size_(0), capacity_(0), array(new char[1]) { array[0] = '\0'; }
    String(char x);
    String(const char* str);
    String(size_t n, char ch);
    String(const String& str)
        : size_(str.size_),
          capacity_(str.capacity_),
          array(new char[str.capacity_ + 1]) {
        memcpy(array, str.array, size_ + 1);
    }
    ~String() { delete[] array; };
    String& operator=(String str);
    String& operator+=(const String& str);
    String& operator+=(char a);
    char& operator[](size_t i) { return array[i]; }
    const char& operator[](size_t i) const { return array[i]; }
    size_t length() const { return size_; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    char& front() { return array[0]; }
    const char& front() const { return array[0]; }
    char& back() { return array[size_ - 1]; }
    const char& back() const { return array[size_ - 1]; }
    char* data() { return array; }
    const char* data() const { return array; }
    void push_back(char a);
    void pop_back() { array[--size_] = '\0'; }
    bool is_substring(const String& substr, size_t begin) const;
    size_t find(const String& substr) const;
    size_t rfind(const String& substr) const;
    String substr(size_t start, size_t count) const;
    void clear();
    void shrink_to_fit();
};
String::String(char x) : size_(1), capacity_(1), array(new char[2]) {
    array[0] = x;
    array[1] = '\0';
}
void String::swap(String& str) {
    std::swap(array, str.array);
    std::swap(size_, str.size_);
    std::swap(capacity_, str.capacity_);
}
String::String(const char* str) : size_(strlen(str)), capacity_(size_), array(new char[capacity_ + 1]) {
    memcpy(array, str, size_);
    array[size_] = '\0';
}
String::String(size_t n, char ch) : size_(n), capacity_(n), array(new char[n + 1]) {
    memset(array, ch, n);
    array[n] = '\0';
}
String& String::operator=(String str) {
    swap(str);
    return *this;
}
void String::push_back(char a) {
    array[size_] = a;
    ++size_;
    if (size_ >= capacity_) {
        memory_allocation(capacity_ * 2);
    }
    array[size_] = '\0';
}
void String::memory_allocation(size_t newcapacity_) {
    capacity_ = newcapacity_;
    char* array_copy = new char[capacity_ + 1];
    memcpy(array_copy, array, size_);
    array_copy[size_] = '\0';
    delete[] array;
    array = array_copy;
}
String& String::operator+=(const String& str) {
    size_t size_new = size_ + str.size();
    if (size_new > capacity_) {
        memory_allocation(size_new);
    }
    memcpy(array + size_, str.array, str.size());
    size_ = size_new;
    array[size_] = '\0';
    return *this;
}
String& String::operator+=(char a) {
    push_back(a);
    return *this;
}
void String::shrink_to_fit() {
    if (size_ == capacity_) { return; }
    memory_allocation(size_);
}
void String::clear() {
    size_ = 0;
    array[0] = '\0';
}
String String::substr(size_t start, size_t count) const {
    String ans(count, '\0');
    memcpy(ans.array, array + start, count);
    return ans;
}
bool String::is_substring(const String& substr, size_t begin) const{
    for (size_t i = 0; i < substr.size_; ++i){
        if (substr[i] != array[begin + i]) { return false; }
    }
    return true;
}
size_t String::find(const String& substr) const {
    if (substr.size_ > size_) { return size_; }
    for (size_t i = 0; i <= size_ - substr.size_; ++i){
        if (is_substring(substr, i)) { return i; }
    }
    return size_;
}
size_t String::rfind(const String& substr) const {
    if (substr.size_ > size_) { return size_; }

    for (int i = size_ - substr.size_; i >= 0; --i){
        if (is_substring(substr, i)) { return i; }
    }
    return size_;
}
String operator+(String a, const String& b) {
    a += b;
    return a;
}
bool operator<(const String& a, const String& b) { return strcmp(a.data(), b.data()) < 0; };
bool operator==(const String& a, const String& b) {
    if (a.size() != b.size()) { return false; };
    return strcmp(a.data(), b.data()) == 0;
}
bool operator>=(const String& a, const String& b) { return !(a < b); }
bool operator>(const String& a, const String& b) { return b < a; }
bool operator<=(const String& a, const String& b) { return !(a > b); }
bool operator!=(const String& a, const String& b) { return !(a == b); }
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.data();
    return os;
}
std::istream& operator>>(std::istream& is, String& str) {
    char elem;
    is.get(elem);
    while (!isspace(elem) && !iscntrl(elem) && !is.eof()) {
        str.push_back(elem);
        is.get(elem);
    }
    return is;
}
