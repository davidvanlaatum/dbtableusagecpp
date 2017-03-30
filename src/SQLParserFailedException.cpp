//
// Created by David van Laatum on 29/3/17.
//

#include "SQLParserFailedException.h"

SQLParserFailedException::SQLParserFailedException ( const std::string &msg ) : runtime_error ( msg ) {

}

SQLParserFailedException::SQLParserFailedException ( const char *msg ) : runtime_error ( msg ) {

}

SQLParserFailedException::SQLParserFailedException ( const std::runtime_error &e ) : runtime_error ( e ) {

}
