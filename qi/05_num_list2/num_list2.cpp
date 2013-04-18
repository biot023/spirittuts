#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client {
  using namespace std;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
  namespace phoenix = boost::phoenix;

  template <typename Iterator>
    bool parse_numbers( Iterator first, Iterator last, vector<double> &v )
    {
      using qi::double_;
      using qi::phrase_parse;
      using qi::_1;
      using ascii::space;
      using phoenix::push_back;

      bool r( phrase_parse( first, last,
              (
               double_[ push_back( phoenix::ref( v ), _1 ) ]
               >> *( ',' >> double_[ push_back( phoenix::ref( v ), _1 ) ] )
              ),
                            space ) );
      return ( first == last ? r : false );
    }
}

int main( int argc, char *argv[] )
{
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tA comma separated list parser for Spirit...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  
  std::cout << "Give me a comma separated list of numbers.\n";
  std::cout << "The numbers will be inserted in a vector of numbers\n";
  std::cout << "Type [q or Q] to quit\n\n";
  
  std::string str;
  while ( getline( std::cin, str ) ) {
    if ( str.empty() || str[0] == 'q' || str[0] == 'Q' ) break;
    std::vector<double> v;
    if ( client::parse_numbers( str.begin(), str.end(), v ) ) {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << str << " Parses OK: " << std::endl;
      for ( const auto &n : v )
        std::cout << "\t- " << n << "\n";
      
      std::cout << "\n-------------------------\n";
    } else {
      std::cout << "-------------------------\n";
      std::cout << "Parsing failed\n";
      std::cout << "-------------------------\n";
    }
  }
  std::cout << "Byee!\n";
  return 0;
}
