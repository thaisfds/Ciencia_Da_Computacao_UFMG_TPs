/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */
/*
   The two statements below are here just so this program will compile.
   You may need to change or remove them on your final code.
*/
#define yywrap() 1
#define YY_SKIP_YYWRAP

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
*/
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
*/

std::string readString = "";
int readNull = 0;
static int level = 0;


%}

/*
 * Define names for regular expressions here.
 */

/* ---- Starts ---- */ 
%START STRING
%START INLINE_COMMENT
%START MULTILINE_COMMENT


/* ---- Init ---- */
CLASS          (?i:class)
LET            (?i:let)
NEW            (?i:new)

/* ---- Condicional ---- */
IF             (?i:if)
ELSE           (?i:else)
CASE           (?i:case)
THEN           (?i:then)

/* ---- Loop ---- */
LOOP           (?i:loop)
WHILE          (?i:while)

/* ---- Bool ---- */
TRUE           (?i:true)
FALSE          (?i:false)
NOT            (?i:not)

/* ---- Etc... ---- */
IN             (?i:in)
OF             (?i:of)
INHERITS       (?i:inherits)
ISVOID         (?i:isvoid)

ESAC           (?i:esac)
FI             (?i:fi)
POOL           (?i:pool)

/* ---- Symbols ---- */

DARROW          =>
LE              <=
ASSIGN          <-

OPERATORS       ("+"|"-"|"*"|"/")
PUNCTUATION     ("."|","|";"|":")
SYMBOLS         ("("|")"|"{"|"}"|"@"|"~"|"<"|"=")
INVALIDS        ("!"|"#"|"$"|"%"|"&"|"_"|"`"|"["|"]"|"^"|"|"|"\\"|">"|"?"|"'")

WHITESPACE      (" "|"\t"|"\r"|"\f"|"\v")
NEWLINE         \n
NUMBER          [0-9]
TYPEID          [A-Z][0-9a-zA-Z_]*
OBJECTID        [a-z][0-9a-zA-Z_]*

%%


 /*
  *  Nested comments
 */

 /* ---- All Comment ---- */ 

 /* Começo de qualquer comentário */
<INITIAL,MULTILINE_COMMENT,INLINE_COMMENT>"(*" {
  level++;
  BEGIN MULTILINE_COMMENT;
}

 /* Comentario de uma linha só */
<INITIAL>"--" { BEGIN INLINE_COMMENT; }

 /* Se ver \ começa a sting */
<INITIAL>\" {
  readString = "";
  readNull = 0;
  BEGIN STRING;
}

 /* ---- In Line Comment ---- */ 

<INLINE_COMMENT>[^\n]* { }

 /* \n termina o comentário */
<INLINE_COMMENT>\n {
  curr_lineno++;
  BEGIN INITIAL;
}

 /* ---- Multi Line Comment ---- */ 

<MULTILINE_COMMENT>[^\n(*]* { }

<MULTILINE_COMMENT>[()*] { }

<MULTILINE_COMMENT>"*)" {
  level--;
  if (level == 0){
    BEGIN INITIAL;
  }
}

 /* erro no comentario */
<MULTILINE_COMMENT><<EOF>> {
  BEGIN INITIAL;
  yylval.error_msg = "EOF in comment";
  return (ERROR);
}


 /* ---- All Comment ---- */ 

 /* Fim de qualquer comentario */
"*)" {
  yylval.error_msg = "Unmatched *)";
  return (ERROR);
}

 /* ---- String ---- */
  /* Leitura da string e erro de null e size */
<STRING>\" {
  BEGIN INITIAL;

  if(readNull == 1) {
    yylval.error_msg = "String contains null character";
    return (ERROR);
  }

  if(readString.length() >= MAX_STR_CONST) {
    yylval.error_msg = "String constant too long";
    return (ERROR);
  }

  yylval.symbol = stringtable.add_string((char *) readString.c_str());
  return (STR_CONST);
}

 /* Nao pode-se ler os simbolos abaixo */
<STRING>[^\n\0"\\]* {
  readString += yytext;
}

 /* Encontrar um \n no meio da string é erro */
<STRING>\n {
  BEGIN INITIAL;
  curr_lineno++;
  yylval.error_msg = "Unterminated string constant";
  return (ERROR);
}

 /* String vazia */
<STRING>\0 {
  readNull = 1;
}

 /* Tratamento dos / alguma coisa (n,t,b,f,0) */
<STRING>\\(.|\n) {
  switch(yytext[1]) {
    case '\n':
      curr_lineno++;
      readString += '\n';
      break; 
    case 'n':
      readString += '\n';
      break; 
    case 't':
      readString += '\t';
      break; 
    case 'b':
      readString += '\b';
      break; 
    case 'f':
      readString += '\f';
      break; 
    case '\0': 
      readNull = 1;
      break;
    default:
      readString += yytext[1];
      break;
  }
}

 /* Erro */
<STRING><<EOF>> {
  BEGIN INITIAL;
  yylval.error_msg = "EOF in string constant";
  return (ERROR);
}




 /*
  *  The multiple-character operators.
 */

 /* ---- Symbols ---- */


"=>"		      { return (DARROW); }
"<="		      { return (LE); }
"<-"		      { return (ASSIGN); }

{OPERATORS}   {return yytext[0];}
{PUNCTUATION} {return yytext[0];}
{SYMBOLS}     {return yytext[0];}
{INVALIDS}    { 
  yylval.error_msg = yytext; return (ERROR);
}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
 */

 /* ---- Init ---- */
{CLASS}       { return (CLASS);}
{LET}         {return (LET);}
{NEW}         {return (NEW);}

 /* ---- Condicional ---- */
{IF}          {return (IF);}
{ELSE}        {return (ELSE);}
{CASE}        {return (CASE);}
{THEN}        {return (THEN);}

 /* ---- Loop ---- */
{LOOP}        {return (LOOP);}
{WHILE}       {return (WHILE);}

 /* ---- Bool ---- */
{TRUE}        {
  yylval.boolean = 1;
  return (BOOL_CONST);
}
{FALSE}       {
  yylval.boolean = 0;
  return (BOOL_CONST);
}
{NOT}         {return (NOT);}

 /* ---- Etc... ---- */
{IN}          {return (IN);}
{OF}          {return (OF);}
{INHERITS}    {return (INHERITS);}
{ISVOID}      {return (ISVOID);}

{ESAC}        {return (ESAC);}
{FI}          {return (FI);}
{POOL}        {return (POOL);}

 /* ---- Symbols ---- */
{WHITESPACE}+ { }
{NEWLINE}     {curr_lineno++;}
{NUMBER}+     {
  yylval.symbol = inttable.add_string(yytext);
  return (INT_CONST);
}
{TYPEID}     {
  yylval.symbol = stringtable.add_string(yytext);
  return (TYPEID);
}
{OBJECTID}   {
  yylval.symbol = stringtable.add_string(yytext);
  return (OBJECTID);
}


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
 */


%%
