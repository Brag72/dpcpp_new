#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class OutConsole:public LogCommand
{
public:
    virtual void print(const std::string& message) override
    {
        std::cout << message;
    }
};

class OutFile:public LogCommand
{
    std::string FilePath;
public:
    explicit OutFile(const std::string& path) : FilePath(path){}

    virtual void print(const std::string& message) override
    {
        std::ofstream out(FilePath);      
        if (out.is_open())
        {
            out << message << std::endl;
            out.close();
        }
    }
};

void print(LogCommand& command)
{
    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);
    command.print(text);
    std::cout << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "Russian");

    OutConsole console;
    OutFile file("1.txt");

    std::cout << "Логирование в консоль" << std::endl;
    print(console);

    std::cout << "Логирование в файл" << std::endl;
    print(file);
}