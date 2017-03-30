%option noyywrap nodefault yylineno case-insensitive
%{
# include <cstdlib>
# include "SQLParserContext.h"
# include "sql-parser.hpp"
using namespace yy;
void yyerror(yy::SQLParser::location_type* yylloc, SQLParserContext &ctx, const char *s, ...);
void adjustLines(yy::SQLParser::location_type *location, char *text);

#define YY_DECL int yylex(yy::SQLParser::semantic_type *yylval, \
    yy::SQLParser::location_type *yylloc, SQLParserContext &ctx)

# define YY_USER_ACTION  yylloc->columns (yyleng);

typedef yy::SQLParser::token token;
int oldstate;

%}

%x COMMENT

%%

%{
     yylloc->step ();
%}

BINLOG { return token::BINLOG; }
DELIMITER { return token::DELIMITER; }
DEFAULT { return token::DEFAULT; }
SET { return token::SET; }
TIMESTAMP { return token::TIMESTAMP; }
BEGIN { return token::TBEGIN; }
ROLLBACK { return token::ROLLBACK; }
COMMIT { return token::COMMIT; }
INSERT { return token::INSERT; }
REPLACE { return token::REPLACE; }
DELETE { return token::DELETE; }
INTO { return token::INTO; }
FROM { return token::FROM; }
VALUES? { return token::VALUES; }
USE { return token::USE; }
COLLATE { return token::COLLATE; }
WHERE { return token::WHERE; }
[0-9]+	{ yylval->ival = atoi(yytext); return token::NUMBER; }
@+[a-zA-Z0-9_\.]+ { yylval->sval = strdup(yytext); return token::USERVAR; }
[-+&~|^/%*(),.;!=]   { yylloc->step (); return yytext[0]; }

`(\\.|[^`])*`	{yylval->sval = strdup(yytext); return token::IDENTIFIER; }

'(\\.|''|[^'])*'	|
\"(\\.|\"\"|[^"])*\"  { adjustLines(yylloc,yytext);
  yylval->sval = strdup(yytext);
  return token::STRING; }

\n      { yylloc->lines(1); yylloc->begin = yylloc->end;}

  /* skip over comments and white space */
"//".*  |
[ \t]   {  yylloc->step (); }
#.* { ctx.parseComment(yytext); }
"--"[ \t].*	;

"/*"            { oldstate = YY_START; BEGIN COMMENT; }
<COMMENT>"*/"   { BEGIN oldstate; }
<COMMENT>.      { yylloc->step ();};
<COMMENT>\n     { yylloc->lines(1);}
<COMMENT><<EOF>> { yyerror(yylloc,ctx,"unclosed comment"); return 0; }

[a-zA-Z0-9_]+ {yylval->sval = strdup(yytext); return token::IDENTIFIER; }

.	{ yyerror(yylloc,ctx,"Mystery char %c", *yytext); }
%%
void adjustLines ( yy::SQLParser::location_type *location, char *text ) {
  char *pos = NULL;
  int lines = 0;
  while ( ( pos = index ( text, '\n' ) ) != NULL ) {
    lines++;
    text = pos + 1;
  }
  if ( lines ) {
    location->lines ( lines );
    location->columns ( (int) strlen ( text ) );
  }
}


