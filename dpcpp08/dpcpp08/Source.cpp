#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Printer
{
public:
    virtual ~Printer() = default;

    // Оборачивание одного элемента
    virtual std::string wrapElement(const std::string& data) const = 0;

    // Оборачивание отчёта
    virtual std::string wrapReport(const std::vector<std::string>& elements) const = 0;
};

class PrinterHTML : public Printer
{
public:
    std::string wrapElement(const std::string& data) const override
    {
        return "<p>" + data + "</p>";
    }

    std::string wrapReport(const std::vector<std::string>& elements) const override
    {
        std::string result = "<html>\n";
        for (const auto& element : elements)
        {
            result += wrapElement(element) + "\n";
        }
        result += "</html>";
        return result;
    }
};

class PrinterJSON : public Printer
{
public:
    std::string wrapElement(const std::string& data) const override
    {
        return "{ \"item\": \"" + data + "\" }";
    }

    std::string wrapReport(const std::vector<std::string>& elements) const override
    {
        std::string result = "[\n";
        for (size_t i = 0; i < elements.size(); ++i)
        {
            result += wrapElement(elements[i]);
            if (i < elements.size() - 1)
            {
                result += ",";
            }
            result += "\n";
        }
        result += "]";
        return result;
    }
};

class PrinterText : public Printer
{
public:
    std::string wrapElement(const std::string& data) const override
    {
        return data;
    }

    std::string wrapReport(const std::vector<std::string>& elements) const override
    {
        std::string result;
        for (const auto& element : elements)
        {
            result += wrapElement(element) + "\n";
        }
        return result;
    }
};

class Report
{
public:
    std::string date;
    std::string title;
    std::string content;

    Report(std::string d, std::string t, std::string c)
        : date(std::move(d)), title(std::move(t)), content(std::move(c)) {}
};

class ReportFormatter
{
public:
    static void saveReportToFile(std::ofstream& file, const Report& report, const std::shared_ptr<Printer>& printer)
    {
        std::vector<std::string> elements;
        elements.push_back(printer->wrapElement(report.date));
        elements.push_back(printer->wrapElement(report.title));
        elements.push_back(printer->wrapElement(report.content));

        file << printer->wrapReport(elements);
    }
};

int main()
{
    std::cout << "Введите дату отчёта: ";
    std::string date;
    std::cin >> date;

    std::cout << "Введите заголовок отчёта: ";
    std::string title;
    std::cin >> title;

    std::cout << "Введите содержание отчёта: ";
    std::string content;
    std::cin >> content;

    Report report(date, title, content);

    // Сохранение в текстовый файл
    std::ofstream textFile("report.txt");
    auto textPrinter = std::make_shared<PrinterText>();
    ReportFormatter::saveReportToFile(textFile, report, textPrinter);

    // Сохранение в HTML файл
    std::ofstream htmlFile("report.html");
    auto htmlPrinter = std::make_shared<PrinterHTML>();
    ReportFormatter::saveReportToFile(htmlFile, report, htmlPrinter);

    // Сохранение в JSON файл
    std::ofstream jsonFile("report.json");
    auto jsonPrinter = std::make_shared<PrinterJSON>();
    ReportFormatter::saveReportToFile(jsonFile, report, jsonPrinter);

    std::cout << "Отчёты сохранены." << std::endl;

    return 0;
}