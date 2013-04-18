#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>

namespace client {
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
  namespace phoenix = boost::phoenix;

  using qi::double_;
  using qi::_1;
  using ascii::space;
  using phoenix::ref;

  template <typename Iterator>
    bool adder( Iterator first, Iterator last, double &n )
    {
      bool r( qi::phrase_parse( first, last,
              (
                double_[ ref( n ) = _1 ] >> *( ',' >> double_[ ref( n ) += _1 ] )
              ),
              space ) );
      return ( first == last ? r : false );
    }
}

int main( int argc, char *argv[] )
{
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tA parser for summing a list of numbers...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  
  std::cout << "Give me a comma separated list of numbers.\n";
  std::cout << "The numbers are added using Phoenix.\n";
  std::cout << "Type [q or Q] to quit\n\n";
  
  std::string str;
  while ( getline( std::cin, str ) ) {
    if ( str.empty() || str[0] == 'q' || str[0] == 'Q' ) break;
    double n;
    if ( client::adder( str.begin(), str.end(), n ) ) {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << str << " Parses OK: " << std::endl;
      std::cout << "sum = " << n;
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
