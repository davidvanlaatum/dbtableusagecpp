//
// Created by David van Laatum on 9/4/17.
//

#ifndef DBTABLEUSAGECPP_TEESTREAM_H
#define DBTABLEUSAGECPP_TEESTREAM_H
#include <ostream>

template<typename char_type,
  typename traits = std::char_traits<char_type> >
class basic_TeeStream :
  public std::basic_streambuf<char_type, traits> {
public:
    typedef typename traits::int_type int_type;

    basic_TeeStream ( std::basic_streambuf<char_type, traits> *sb1, std::basic_streambuf<char_type, traits> *sb2 )
      : sb1 ( sb1 ), sb2 ( sb2 ) {
    }

private:
    virtual int sync () {
      int const r1 = sb1->pubsync ();
      int const r2 = sb2->pubsync ();
      return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    virtual int_type overflow ( int_type c ) {
      int_type const eof = traits::eof ();

      if ( traits::eq_int_type ( c, eof ) ) {
        return traits::not_eof ( c );
      } else {
        char_type const ch = traits::to_char_type ( c );
        int_type const r1 = sb1->sputc ( ch );
        int_type const r2 = sb2->sputc ( ch );

        return
          traits::eq_int_type ( r1, eof ) ||
          traits::eq_int_type ( r2, eof ) ? eof : c;
      }
    }

private:
    std::basic_streambuf<char_type, traits> *sb1;
    std::basic_streambuf<char_type, traits> *sb2;
};

typedef basic_TeeStream<char> TeeBuffer;

class TeeStream : public std::ostream {
public:
    TeeStream ( std::ostream &o1, std::ostream &o2 );
private:
    TeeBuffer tbuf;
};

TeeStream::TeeStream ( std::ostream &o1, std::ostream &o2 )
  : std::ostream ( &tbuf ), tbuf ( o1.rdbuf (), o2.rdbuf () ) {
}

#endif //DBTABLEUSAGECPP_TEESTREAM_H
