#include <fstream>
#include <iostream>
#include <windows.h>

enum class Format
{
    undefined,
    kText,
    kHTML,
    kJSON
};

class Printable 
{
protected:
    Format PrintableFormat = Format::undefined;
public:
    virtual void SetPrintFormat() = 0;
    Format GetFormat() const { return PrintableFormat; }
    virtual ~Printable() = default;
    virtual std::string PrintClient(std::string& data) const = 0;
};

class AsHTML: public Printable
{
public:
    AsHTML() { SetPrintFormat(); }

    virtual void SetPrintFormat()override
    {
        PrintableFormat = Format::kHTML;
    }
    virtual std::string PrintClient(std::string& data) const override
    {
        return "<html>" + data + "<html/>";
    }
};

class AsText : public Printable
{
public:
    AsText() { SetPrintFormat(); }

    virtual void SetPrintFormat()override
    {
        PrintableFormat = Format::kText;
    }

    virtual std::string PrintClient(std::string& data) const override
    {        
        return data;
    }
};

class AsJSON : public Printable
{
public:
    AsJSON() { SetPrintFormat(); }

    virtual void SetPrintFormat()override
    {
        PrintableFormat = Format::kJSON;
    }

    virtual std::string PrintClient( std::string& data) const override
    {
        return "{ \"data\": \"" + data + "\"}";
    }
};

class PrintFactory
{
public:
    static std::unique_ptr<Printable> Create(Format format)
    {
        switch (format)
        {
        case Format::kHTML:
            return std::make_unique<AsHTML>();
        case Format::kJSON:
            return std::make_unique<AsJSON>();
        case Format::kText:
            return std::make_unique<AsText>();   
        default:
            throw std::runtime_error("Invalid format");
        }        
    }
};

class Data
{   
    std::string data_;
public:
    Data(std::string data):data_(data) {}
    std::string get_Data()
    {
        return data_;
    }
};

class Saver
{
public:
    void saveTo(std::ofstream& file, const Printable& printable, std::string& data)
    {        
        auto P = PrintFactory::Create(printable.GetFormat());
        file << printable.PrintClient(data);
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "Russian");

    std::cout << "¬ведите сообщение: " << std::endl;
    std::string Text;
    std::cin >> Text;

    Data data(Text);
    Saver saver;

    std::ofstream text_stream("output.txt");
    AsText as_text;
    saver.saveTo(text_stream, as_text, Text);

    std::ofstream html_stream("output.html");
    AsHTML as_html;
    saver.saveTo(html_stream, as_html, Text);

    std::ofstream json_stream("output.json");
    AsJSON as_json;
    saver.saveTo(json_stream, as_json, Text);
}