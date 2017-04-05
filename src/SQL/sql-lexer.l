%option noyywrap nodefault yylineno case-insensitive
%{
#include "SQLParserContext.h"
#include "SQLObjectList.h"
#include "SQLTable.h"
#include "SQLColumn.h"
#include "SQLComparision.h"
#include "sql-parser.hpp"
#include <stdarg.h>
#include <string.h>
using namespace yy;
void yyerror(yy::SQLParser::location_type* yylloc, SQLParserContext &ctx, const char *s, ...);
void adjustLines(yy::SQLParser::location_type *location, char *text);

#define YY_DECL int yylex(yy::SQLParser::semantic_type *yylval, \
    yy::SQLParser::location_type *yylloc, SQLParserContext &ctx)

# define YY_USER_ACTION  yylloc->columns (yyleng);

typedef yy::SQLParser::token token;
int oldstate;

%}

%x XCOMMENT
%s BTWMODE

%%

%{
     yylloc->step ();
%}
  /* keywords */

ADD { return token::ADD; }
ALL { return token::ALL; }
ALTER { return token::ALTER; }
ANALYZE { return token::ANALYZE; }

  /* Hack for BETWEEN ... AND ...
   * return special AND token if BETWEEN seen
   */
<BTWMODE>AND { BEGIN INITIAL; return token::AND; }
AND { return token::ANDOP; }
ANY     { return token::ANY; }
AS { return token::AS; }
ASC { return token::ASC; }
AUTO_INCREMENT { return token::AUTO_INCREMENT; }
BEFORE { return token::BEFORE; }
BETWEEN { BEGIN BTWMODE; return token::BETWEEN; }
INT8|BIGINT { return token::BIGINT; }
BINARY { return token::BINARY; }
BIT { return token::BIT; }
BLOB { return token::BLOB; }
BOTH { return token::BOTH; }
BY { return token::BY; }
CALL { return token::CALL; }
CASCADE { return token::CASCADE; }
CASE { return token::CASE; }
CHANGE { return token::CHANGE; }
CHAR(ACTER)? { return token::CHAR; }
CHECK { return token::CHECK; }
COLLATE { return token::COLLATE; }
COLUMN { return token::COLUMN; }
COMMENT { return token::COMMENT; }
CONDITION { return token::CONDITION; }
CONSTRAINT { return token::CONSTRAINT; }
CONTINUE { return token::CONTINUE; }
CONVERT { return token::CONVERT; }
CREATE { return token::CREATE; }
CROSS { return token::CROSS; }
CURRENT_DATE { return token::CURRENT_DATE; }
CURRENT_TIME { return token::CURRENT_TIME; }
CURRENT_TIMESTAMP { return token::CURRENT_TIMESTAMP; }
CURRENT_USER { return token::CURRENT_USER; }
CURSOR { return token::CURSOR; }
DATABASE { return token::DATABASE; }
DATABASES { return token::DATABASES; }
DATE { return token::DATE; }
DATETIME { return token::DATETIME; }
DAY_HOUR { return token::DAY_HOUR; }
DAY_MICROSECOND { return token::DAY_MICROSECOND; }
DAY_MINUTE { return token::DAY_MINUTE; }
DAY_SECOND { return token::DAY_SECOND; }
NUMERIC|DEC|DECIMAL { return token::DECIMAL; }
DECLARE { return token::DECLARE; }
DEFAULT { return token::DEFAULT; }
DELAYED { return token::DELAYED; }
DELETE { return token::DELETE; }
DESC { return token::DESC; }
DESCRIBE { return token::DESCRIBE; }
DETERMINISTIC { return token::DETERMINISTIC; }
DISTINCT { return token::DISTINCT; }
DISTINCTROW { return token::DISTINCTROW; }
DIV { return token::DIV; }
FLOAT8|DOUBLE { return token::DOUBLE; }
DROP { return token::DROP; }
DUAL { return token::DUAL; }
EACH { return token::EACH; }
ELSE { return token::ELSE; }
ELSEIF { return token::ELSEIF; }
END { return token::END; }
ENUM { return token::ENUM; }
ESCAPED { return token::ESCAPED; }
EXISTS { yylval->subtok = 0; return token::EXISTS; }
NOT[ \t]+EXISTS { yylval->subtok = 1; return token::EXISTS; }
EXIT { return token::EXIT; }
EXPLAIN { return token::EXPLAIN; }
FETCH { return token::FETCH; }
FLOAT4? { return token::FLOAT; }
FOR { return token::FOR; }
FORCE { return token::FORCE; }
FOREIGN { return token::FOREIGN; }
FROM { return token::FROM; }
FULLTEXT { return token::FULLTEXT; }
GRANT { return token::GRANT; }
GROUP { return token::GROUP; }
HAVING { return token::HAVING; }
HIGH_PRIORITY { return token::HIGH_PRIORITY; }
HOUR_MICROSECOND { return token::HOUR_MICROSECOND; }
HOUR_MINUTE { return token::HOUR_MINUTE; }
HOUR_SECOND { return token::HOUR_SECOND; }
IF { return token::IF; }
IGNORE { return token::IGNORE; }
IN { return token::IN; }
INFILE { return token::INFILE; }
INNER { return token::INNER; }
INOUT { return token::INOUT; }
INSENSITIVE { return token::INSENSITIVE; }
INSERT { return token::INSERT; }
INT4?|INTEGER { return token::INTEGER; }
INTERVAL { return token::INTERVAL; }
INTO { return token::INTO; }
IS { return token::IS; }
ITERATE { return token::ITERATE; }
JOIN { return token::JOIN; }
INDEX|KEY { return token::KEY; }
KEYS { return token::KEYS; }
KILL { return token::KILL; }
LEADING { return token::LEADING; }
LEAVE { return token::LEAVE; }
LEFT { return token::LEFT; }
LIKE { return token::LIKE; }
LIMIT { return token::LIMIT; }
LINES { return token::LINES; }
LOAD { return token::LOAD; }
LOCALTIME { return token::LOCALTIME; }
LOCALTIMESTAMP { return token::LOCALTIMESTAMP; }
LOCK { return token::LOCK; }
LONG { return token::LONG; }
LONGBLOB { return token::LONGBLOB; }
LONGTEXT { return token::LONGTEXT; }
LOOP { return token::LOOP; }
LOW_PRIORITY { return token::LOW_PRIORITY; }
MATCH { return token::MATCH; }
MEDIUMBLOB { return token::MEDIUMBLOB; }
MIDDLEINT|MEDIUMINT { return token::MEDIUMINT; }
MEDIUMTEXT { return token::MEDIUMTEXT; }
MINUTE_MICROSECOND { return token::MINUTE_MICROSECOND; }
MINUTE_SECOND { return token::MINUTE_SECOND; }
MOD { return token::MOD; }
MODIFIES { return token::MODIFIES; }
NATURAL { return token::NATURAL; }
NOT { return token::NOT; }
NO_WRITE_TO_BINLOG { return token::NO_WRITE_TO_BINLOG; }
NULL { return token::NULLX; }
NUMBER { return token::NUMBER; }
ON { return token::ON; }
ON[ \t]+DUPLICATE { return token::ONDUPLICATE; } /* hack due to limited lookahead */
OPTIMIZE { return token::OPTIMIZE; }
OPTION { return token::OPTION; }
OPTIONALLY { return token::OPTIONALLY; }
OR { return token::OR; }
ORDER { return token::ORDER; }
OUT { return token::OUT; }
OUTER { return token::OUTER; }
OUTFILE { return token::OUTFILE; }
PRECISION { return token::PRECISION; }
PRIMARY { return token::PRIMARY; }
PROCEDURE { return token::PROCEDURE; }
PURGE { return token::PURGE; }
QUICK { return token::QUICK; }
READ { return token::READ; }
READS { return token::READS; }
REAL { return token::REAL; }
REFERENCES { return token::REFERENCES; }
REGEXP|RLIKE { return token::REGEXP; }
RELEASE { return token::RELEASE; }
RENAME { return token::RENAME; }
REPEAT { return token::REPEAT; }
REPLACE { return token::REPLACE; }
REQUIRE { return token::REQUIRE; }
RESTRICT { return token::RESTRICT; }
RETURN { return token::RETURN; }
REVOKE { return token::REVOKE; }
RIGHT { return token::RIGHT; }
ROLLUP { return token::ROLLUP; }
SCHEMA { return token::SCHEMA; }
SCHEMAS { return token::SCHEMAS; }
SECOND_MICROSECOND { return token::SECOND_MICROSECOND; }
SELECT { return token::SELECT; }
SENSITIVE { return token::SENSITIVE; }
SEPARATOR { return token::SEPARATOR; }
SET { return token::SET; }
SHOW { return token::SHOW; }
INT2|SMALLINT { return token::SMALLINT; }
SOME { return token::SOME; }
SONAME { return token::SONAME; }
SPATIAL { return token::SPATIAL; }
SPECIFIC { return token::SPECIFIC; }
SQL { return token::SQL; }
SQLEXCEPTION { return token::SQLEXCEPTION; }
SQLSTATE { return token::SQLSTATE; }
SQLWARNING { return token::SQLWARNING; }
SQL_BIG_RESULT { return token::SQL_BIG_RESULT; }
SQL_CALC_FOUND_ROWS { return token::SQL_CALC_FOUND_ROWS; }
SQL_SMALL_RESULT { return token::SQL_SMALL_RESULT; }
SSL { return token::SSL; }
STARTING { return token::STARTING; }
STRAIGHT_JOIN { return token::STRAIGHT_JOIN; }
TABLE { return token::TABLE; }
TEMPORARY { return token::TEMPORARY; }
TERMINATED { return token::TERMINATED; }
TEXT { return token::TEXT; }
THEN { return token::THEN; }
TIME { return token::TIME; }
TIMESTAMP { return token::TIMESTAMP; }
INT1|TINYINT { return token::TINYINT; }
TINYTEXT { return token::TINYTEXT; }
TO { return token::TO; }
TRAILING { return token::TRAILING; }
TRIGGER { return token::TRIGGER; }
UNDO { return token::UNDO; }
UNION { return token::UNION; }
UNIQUE { return token::UNIQUE; }
UNLOCK { return token::UNLOCK; }
UNSIGNED { return token::UNSIGNED; }
UPDATE { return token::UPDATE; }
USAGE { return token::USAGE; }
USE { return token::USE; }
USING { return token::USING; }
UTC_DATE { return token::UTC_DATE; }
UTC_TIME { return token::UTC_TIME; }
UTC_TIMESTAMP { return token::UTC_TIMESTAMP; }
VALUES? { return token::VALUES; }
VARBINARY { return token::VARBINARY; }
VARCHAR(ACTER)? { return token::VARCHAR; }
VARYING { return token::VARYING; }
WHEN { return token::WHEN; }
WHERE { return token::WHERE; }
WHILE { return token::WHILE; }
WITH { return token::WITH; }
WRITE { return token::WRITE; }
XOR { return token::XOR; }
YEAR { return token::YEAR; }
YEAR_MONTH { return token::YEAR_MONTH; }
ZEROFILL { return token::ZEROFILL; }
DELIMITER { return token::DELIMITER; }
BINLOG { return token::BINLOG; }
BEGIN { return token::TBEGIN; }
ROLLBACK { return token::ROLLBACK; }
COMMIT { return token::COMMIT; }

   /* numbers */

-?[0-9]+         { yylval->intval = atoi(yytext); return token::INTNUM; }

-?[0-9]+"."[0-9]* |
-?"."[0-9]+ |
-?[0-9]+E[-+]?[0-9]+ |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
-?"."[0-9]*E[-+]?[0-9]+ { yylval->floatval = atof(yytext) ;
                                  return token::APPROXNUM; }
    /* booleans */
TRUE { yylval->intval = 1; return token::BOOL; }
UNKNOWN { yylval->intval = -1; return token::BOOL; }
FALSE { yylval->intval = 0; return token::BOOL; }

   /* strings */

'(\\.|''|[^'])*' |
\"(\\.|\"\"|[^"])*\"  { yylval->strval = strdup(yytext); adjustLines(yylloc,yytext); return token::STRING; }

'(\\.|[^'])*$         { yyerror(yylloc,ctx,"Unterminated string %s", yytext); }
\"(\\.|[^"])*$ { yyerror(yylloc,ctx,"Unterminated string %s", yytext); }

   /* hex strings */
X'[0-9A-F]+' |
0X[0-9A-F]+  { yylval->strval = strdup(yytext); return token::STRING; }

   /* bit strings */

0B[01]+      |
B'[01]+'     { yylval->strval = strdup(yytext); return token::STRING; }


   /* operators */
[-+&~|^/%*(),.!]   { return yytext[0]; }
";" { int c = 0;
  while ( (c = yyinput()) == '\n' ) {
    yylloc->lines(1);
    yylloc->step();
  }
  unput(c);
  return yytext[0];
}

"&&"  { return token::ANDOP; }
"||"            { return token::OR; }

"=" { yylval->subtok = EQUALTO; return token::COMPARISON; }
"<=>" { yylval->subtok = NULL_EQUALS; return token::COMPARISON; }
">=" { yylval->subtok = GREATERTHAN_OR_EQUALTO; return token::COMPARISON; }
">" { yylval->subtok = GREATERTHAN; return token::COMPARISON; }
"<=" { yylval->subtok = LESSTHAN_OR_EQUALTO; return token::COMPARISON; }
"<" { yylval->subtok = LESSTHAN; return token::COMPARISON; }
"!=" |
"<>" { yylval->subtok = NOTEQUALTO; return token::COMPARISON; }

"<<" { yylval->subtok = 1; return token::SHIFT; }
">>" { yylval->subtok = 2; return token::SHIFT; }

        /* functions */

SUBSTR(ING)?/"(" { return token::FSUBSTRING; }
TRIM/"(" { return token::FTRIM; }
DATE_ADD/"(" { return token::FDATE_ADD; }
DATE_SUB/"(" { return token::FDATE_SUB; }

 /*
         * peek ahead and return function if name(
         */
COUNT    { int c = yyinput(); unput(c);
           if(c == '(') return token::FCOUNT;
           yylval->strval = strdup(yytext);
           return token::NAME; }
_[A-Za-z][A-Za-z0-9_]+ { yylval->strval = strdup(yytext);
                          return token::INTRODUCER; }
[A-Za-z][A-Za-z0-9_]* { yylval->strval = strdup(yytext);
                          return token::NAME; }
`[^`/\\.\n]+`           { yylval->strval = strdup(yytext+1);
                          yylval->strval[yyleng-2] = 0;
                          return token::NAME; }

`[^`\n]*$               { yyerror(yylloc,ctx,"unterminated quoted name %s", yytext); }

 /* user variables */
@@?[0-9a-z_.$]+ |
@@?\"[^"\n]+\" |
@@?`[^`\n]+` |
@@?'[^'\n]+' { yylval->strval = strdup(yytext); return token::USERVAR; }

@\"[^"\n]*$ { yyerror(yylloc,ctx,"unterminated quoted user variable %s", yytext); }
@`[^`\n]*$ { yyerror(yylloc,ctx,"unterminated quoted user variable %s", yytext); }
@'[^'\n]*$ { yyerror(yylloc,ctx,"unterminated quoted user variable %s", yytext); }


":="     { return token::ASSIGN; }

 /* comments */
#.*"\n"  { ctx.parseComment(yytext); yylloc->lines(1); yylloc->step();};
"--"[ \t].*"\n" { yylloc->lines(1); yylloc->step(); };

"/*"            { oldstate = YY_START; BEGIN XCOMMENT; }
<XCOMMENT>"*/"   { BEGIN oldstate; }
<XCOMMENT>.
<XCOMMENT>\n     { yylloc->lines(1);yylloc->step();}
<XCOMMENT><<EOF>> { yyerror(yylloc,ctx,"unclosed comment"); return 0; }

         /* everything else */
[ \t]           /* white space */
\n      { yylloc->lines(1); yylloc->step(); }
.               { yyerror(yylloc,ctx,"mystery character '%c'", *yytext); }

%%
extern "C" void flushLex() {
  YY_FLUSH_BUFFER;
}
