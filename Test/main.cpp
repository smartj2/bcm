#include <boost/regex.hpp>

int main()
{
	boost::regex reg("chenchen");
	boost::regex_match("chenchen", reg);
	return 0;
}