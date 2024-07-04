#include <iostream>
#include <vector>
#include <sstream>
#include <regex>


//разделение на строки
std::vector<std::string> Split(const std::string& line) {
    std::vector<std::string> result;
    std::regex lineRegex(R"(([^,"]*(?:\" [^\"]*\"[^,"]*)*|[^,]*))");
    std::sregex_token_iterator iter(line.begin(), line.end(), lineRegex);
    std::sregex_token_iterator end;
    //накопление элементов
    std::string element = "";
    bool q = false;
    //проход по строчкам и добавление 
    for (; iter != end; ++iter) {
        std::string field = iter->str();

        bool startsWithQuote = (!field.empty() && field.front() == '"');
        bool endsWithQuote = (!field.empty() && field.back() == '"');

        if (q) {
            element += "," + field;
            if (endsWithQuote) {
                q = false;
                result.push_back(element);
            }
        }
        else {
            if (startsWithQuote && endsWithQuote && field.size() > 1) {
                result.push_back(field);
            }
            else if (startsWithQuote) {
                element += field;
                q = true;
            }
            else {
                result.push_back(field);
            }
        }
    }

    return result;
}

std::string removeQuotes(const std::string& field) {
    if (field.front() == '"' && field.back() == '"') {
        std::string inner = field.substr(1, field.size() - 2);
        inner = std::regex_replace(inner, std::regex(R"("")"), "\"");
        return inner;
    }
    return field;
}

int main() {
    std::string line = "Ten Thousand,10000,2710, ,\"10,000\",\"It's \"\"10 Grand\"\", baby\",10K";
    std::cout << line;
    std::vector<std::string> fields = Split(line);
    bool isEmpty = false;

    for (const auto& field : fields) {
        if (isEmpty) {
            isEmpty = false;
            continue;
        }
        std::string finalField = removeQuotes(field);
        if (finalField == "") {
            std::cout << "empty field\n";
        }
        else {
            std::cout << finalField << std::endl;
        }
        if (finalField == "" && !isEmpty) {
            isEmpty = false;
        }
        else {
            isEmpty = true;
        }
    }
    return 0;
}