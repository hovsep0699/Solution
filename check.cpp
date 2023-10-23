#include "HugeInt.h"

std::string  print(HugeInt num, const std::map<HugeInt, std::string, std::greater<HugeInt>>& map)
{
    if (num == HugeInt(0))
    {
        return map.at("0");
    }

    std::string result;
    auto it = map.lower_bound(num);

    if (it != map.end())
    {
        if (!result.empty())
        {
            result += " ";
        }

        HugeInt quotient = num / it->first;
        if (quotient > HugeInt(1))
        {
            result += print(quotient, map) + " ";
        }

        result += it->second;

        num = num % it->first;

        if (num > HugeInt(0))
        {
            result += " ";
            result += print(num, map);
        }
    }
    return result;
}

int main(int argc, char** argv) try {

std::string centillion(304, '0');
centillion[0] = '1';
std::string googol(100, '0');
googol[0] = '1';
std::map<HugeInt, std::string, std::greater<HugeInt>> m = {
        {"0", "zero"},
        {"1", "one"},
        {"2", "two"},
        {"3", "three"},
        {"4", "four"},
        {"5", "five"},
        {"6", "six"},
        {"7", "seven"},
        {"8", "eight"},
        {"9", "nine"},
        {"10", "ten"},
        {"11", "eleven"},
        {"12", "twelve"},
        {"13", "thirteen"},
        {"14", "forteen"},
        {"15", "fifteen"},
        {"16", "sixten"},
        {"17", "seventeen"},
        {"18", "eighteen"},
        {"19", "nineteen"},
        {"20", "twenty"},
        {"30", "thirty"},
        {"40", "forty"},
        {"50", "fifty"},
        {"60", "sixty"},
        {"70", "seventy"},
        {"80", "eighty"},
        {"90", "ninety"},
        {"100", "hundred"},
        {"1000", "thousand"},
        {"1000000", "million"},
        {"1000000000", "billion"},
        {"1000000000000", "trillion"},
        {"1000000000000000", "quadrillion"},
        {"1000000000000000000", "quintillion"},
        {"1000000000000000000000", "sextillion"},
        {"1000000000000000000000000", "septillion"},
        {"1000000000000000000000000000", "octillion"},
        {"1000000000000000000000000000000", "nonillion"},
        {"1000000000000000000000000000000000", "decillion"},
        {"1000000000000000000000000000000000000", "undecillion"},
        {"1000000000000000000000000000000000000000", "duodecillion"},
        {"1000000000000000000000000000000000000000000", "tredecillion"},
        {"1000000000000000000000000000000000000000000000", "quattuordecillion"},
        {"1000000000000000000000000000000000000000000000000", "quindecillion"},
        {"1000000000000000000000000000000000000000000000000000", "sexdecillion"},
        {"1000000000000000000000000000000000000000000000000000000", "septendecillion"},
        {"1000000000000000000000000000000000000000000000000000000000", "octodecillion"},
        {"1000000000000000000000000000000000000000000000000000000000000", "novemdecillion"},
        {"1000000000000000000000000000000000000000000000000000000000000000", "vigintillion"},
        {centillion, "centillion"},
        {googol, "googol"}
    };


    if (argc >= 2)
    {
        std::string arg(argv[1]);
        auto it = arg.find('.');
        HugeInt num1(arg.c_str(), arg.c_str() + (it == std::string::npos ? arg.size() : it));
        auto res = print(num1, m);
        if (it != std::string::npos)
        {
            HugeInt num2(arg.c_str() + it + 1, arg.c_str() + arg.size());
            if (num2 > HugeInt(0))
                res += " and " + print(num2, m) + " cents";
        }
        std::cout << arg << " - " << res << "\n";
    }
    return 0;
}
catch(...)
{
    std::cerr << "Invalid Argument" << std::endl;
}
