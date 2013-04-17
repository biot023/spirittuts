#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace client {
  using complex_t = std::complex<double>;

  template <typename Iterator>
    bool parse_complex( Iterator first, Iterator last, complex_t &c )
    {
      using boost::spirit::qi::double_;
      using boost::spirit::qi::_1;
      using boost::spirit::qi::phrase_parse;
      using boost::spirit::ascii::space;
      using boost::phoenix::ref;

      double r_n( 0.0 );
      double i_n( 0.0 );
      bool r( phrase_parse
              ( first, last,
                ( '(' >> double_[ ref( r_n ) = _1 ]
                      >> -( ',' >> double_[ ref( i_n ) = _1 ] ) >> ')'
                  | double_[ ref( r_n ) = _1 ]
                ),
                space ) );
      if ( ! r || first != last )
        return false;
      else {
        c = complex_t( r_n, i_n );
        return true;
      } // fi
    }
}

int main( int argc, char *argv[] )
{
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tA complex number micro parser for Spirit...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "Give me a complex number of the form r or (r) or (r,i) \n";
  std::cout << "Type [q or Q] to quit\n\n";

  std::string str;
  while ( getline( std::cin, str ) ) {
    if ( str.empty() || str[0] == 'q' || str[0] == 'Q' ) break;
    client::complex_t c;
    if ( client::parse_complex( str.begin(), str.end(), c ) ) {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << "got: " << c << std::endl;
      std::cout << "\n-------------------------\n";
    } else {
      std::cout << "-------------------------\n";
      std::cout << "Parsing failed\n";
      std::cout << "-------------------------\n";
    } // fi
  } // wend
  
  std::cout << "Bye!" << std::endl;
  return 0;
}
