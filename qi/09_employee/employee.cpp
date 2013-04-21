#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
// #include <boost/fustion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace client {
  using namespace std;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
  
  struct employee
  {
    int age;
    string surname;
    string forename;
    double salary;
  };
}

// Must be in global scope.
BOOST_FUSION_ADAPT_STRUCT( client::employee,
                           ( int, age )
                           ( std::string, surname )
                           ( std::string, forename )
                           ( double, salary ) )

namespace client {
  template <typename Iterator>
    struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>
    {
      employee_parser() : employee_parser::base_type( start )
      {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        qstring %= lexeme[ '"' >> +( char_ - '"' ) >> '"' ];

        start %=
          lit( "employee" )
          >> '{'
          >> int_ >> ','
          >> qstring >> ','
          >> qstring >> ','
          >> double_
          >> '}'
          ;
      }
      
      qi::rule<Iterator, string(), ascii::space_type> qstring;
      qi::rule<Iterator, employee(), ascii::space_type> start;
    };
}

int main( int argc, char *argv[] )
{
  using boost::spirit::ascii::space;
  using iterator_t = std::string::const_iterator;
  using parser_t = client::employee_parser<iterator_t>;
  
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tAn employee parser for Spirit...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout
    << "Give me an employee of the form :"
    << "employee{age, \"surname\", \"forename\", salary } \n";
  std::cout << "Type [q or Q] to quit\n\n";

  parser_t grammar;
  std::string str;
  while ( getline( std::cin, str ) ) {
    if ( str.empty() || str[0] == 'q' || str[0] == 'Q' ) break;
    client::employee emp;
    iterator_t iter( str.cbegin() ), end( str.cend() );
    bool r( phrase_parse( iter, end, grammar, space, emp ) );
    if ( r && iter == end ) {
      std::cout << boost::fusion::tuple_open('[');
      std::cout << boost::fusion::tuple_close(']');
      std::cout << boost::fusion::tuple_delimiter(", ");
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << "got: " << boost::fusion::as_vector(emp) << "\n";
      std::cout << "\n-------------------------" << std::endl;
    } else {
      std::cout << "-------------------------\n";
      std::cout << "Parsing failed\n";
      std::cout << "-------------------------" << std::endl;
    } // fi
  } // wend

  std::cout << "Byee!\n";
  return 0;
}
