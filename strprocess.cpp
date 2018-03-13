#include <regex>

class strprocess
{
  private:
    std::vector<std::string> strs;
    std::string input_str;

  public:
    strprocess(std::string *);
    std::vector<std::string> to_vector();
};

strprocess::strprocess(std::string *str)
{
    this->input_str = *str;
};

std::vector<std::string> strprocess::to_vector()
{
    std::regex pattern("(\\d\\.?)");
    const std::sregex_token_iterator end;
    int j = 0;
    std::string *istr_p = &(this->input_str);
    for (std::sregex_token_iterator i(istr_p->begin(), istr_p->end(), pattern);
         i != end;
         ++i)
    {
        std::cout << *i << std::endl;
        if (j < 4)
        {
            // show.push_back(*i);
            this->strs[j] = *i;
        }
        j++;
    }
    return this->strs;
};