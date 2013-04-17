#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

#include <iostream>

namespace client {
  using namespace std;
  namespace qi = boost::spirit::qi;

  // A plain function
  void print( const int i )
  {
    cout << i << endl;
  }

  // A member function
  struct writer
  {
    void print( const int i ) const
    {
      cout << i << endl;
    }
  };

  // A function object
  struct print_action
  {
    void operator() ( const int i, qi::unused_type, qi::unused_type ) const
    {
      cout << i << endl;
    }
  };
}

int main( int argc, char *argv[] )
{
  using std::strlen;
  using boost::spirit::qi::int_;
  using boost::spirit::qi::parse;
  using client::print;
  using client::writer;
  using client::print_action;

  { // Example using plain function
    const char *first = "{42}", *last = first + strlen( first );
    parse( first, last, '{' >> int_[&print] >> '}' );
  }

  { // Example using simple function object
    const char *first = "{43}", *last = first + strlen( first );
    parse( first, last, '{' >> int_[print_action()] >> '}' );
  }

  { // Example using Boost.Bind with a plain function
    const char *first = "{44}", *last = first + strlen( first );
    parse( first, last, '{' >> int_[boost::bind( &print, _1 )] >> '}' );
  }

  { // Example using Boost.Bind with a member function
    const char *first = "{45}", *last = first + strlen( first );
    writer w;
    parse( first, last, '{' >> int_[boost::bind( &writer::print, &w, _1 )] >> '}' );
  }

  { // Example using Boost.Lambda
    namespace lambda = boost::lambda;
    const char *first = "{46}", *last = first + strlen( first );
    using lambda::_1;
    parse( first, last, '{' >> int_[std::cout << _1 << '\n'] >> '}' );
  }

  { // Example using C++11 lambda expression
    const char *first = "{47}", *last = first + strlen( first );
    parse( first, last,
           '{' >> int_[ [] ( const int i ) { std::cout << i << std::endl; } ] >> '}' );
  }

  return 0;
}
