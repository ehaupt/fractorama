%{

// For prototype of "strdup"
#include <string.h>

#include "fractal.yacc.h"
#include "FractalLexer.h"
#include "dmemory.h"

/*****************************************************************************
 * Definitions for class "FractalLexer"
 *****************************************************************************/

FractalLexer::FractalLexer()
   : mLineNumber(1), mText(0), mTextIndex(0), mTextLength(0),
     mFileOffset(0), mLineOffset(0)
{}

FractalLexer *FractalLexer::getInstance()
{
   static FractalLexer theInstance;
   return(&theInstance);
}

int FractalLexer::parseInteger(char *theText)
{
   int base = 10;

   // Is 'theText' a hex value?  If so we'll treat it as such ...

   if(strncmp(theText, "0x", 2) == 0 ||
      strncmp(theText, "0X", 2) == 0)
   {
      base = 16;
   }

   return(strtol(theText, 0, base));
}

void FractalLexer::begin(const char *text)
{
   YY_NEW_FILE;

   mLineNumber = 1;
   mTextLength = strlen(text);
   mTextIndex  = 0;
   mFileOffset = 0;
   mLineOffset = 0;

   DNEW(mText, char[mTextLength]);

   memcpy(mText, text, mTextLength);
}

void FractalLexer::end()
{
   DADELETE(mText);
}

int FractalLexer::getLineNumber()
{
   return(mLineNumber);
}

void FractalLexer::nextLine()
{
   ++mLineNumber;
   mLineOffset = 0;
}

int FractalLexer::getText(char *dest, int maxSize)
{
   int bytesRemaining = mTextLength - mTextIndex;
   int count          = bytesRemaining > maxSize ? maxSize : bytesRemaining;

   memcpy(dest, mText, count);

   mTextIndex += count;

   return(count);
}

int FractalLexer::getFileOffset()
{
   return(mFileOffset);
}

int FractalLexer::getLineOffset()
{
   return(mLineOffset);
}

void FractalLexer::getCurrentLine(char *line)
{
   // Grab the current line until we reach a \n or MAX_LINE_LENGTH
   // characters, whichever is smaller

   int offset = getFileOffset() - getLineOffset();
   int i      = 0;

   for(i = 0; offset + i < mTextLength && i < MAX_LINE_LENGTH; i ++)
   {
      if(mText[offset + i] == '\n')
         break;

      line[i] = mText[offset + i];
   }

   line[i] = '\0';
}

void FractalLexer::advance(char *theText)
{
   int nChars = strlen(theText);

   mFileOffset += nChars;
   mLineOffset += nChars;
}

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static int my_yyinput(char *buffer, int maxsize);

extern "C"
{
   int yylex(YYSTYPE *yylval);
}

#undef YY_INPUT

#define YY_INPUT(buffer, count, maxsize) (count = my_yyinput(buffer, maxsize))

#define YY_DECL int yylex(YYSTYPE *yylval)

// Define this symbol so that the generated
// source does not contain a reference to "isatty" (a unix-specific function)

#define YY_ALWAYS_INTERACTIVE (1)

%}

integer    ([0-9]+|0[xX][0-9a-zA-Z]+)
real       ({integer}|[0-9]*\.[0-9]+|[0-9]+\.[0-9]*)([eE]([+-]?)[0-9]+)?
identifier [a-zA-Z_][a-zA-Z0-9_]*
literal    \"[^\"]*\"

   /* -- Use flex's "exclusive start states" feature to avoid having to
         prefix <INITIAL> to all tokens that should be recognized
         while in the default state, note "%x" rather than "%s" -- */

%x STATE_MULTI_LINE_COMMENT
%x STATE_SINGLE_LINE_COMMENT

%%

   /* -- Token handling for the default state -- */

{integer} {
   yylval->ivalue = FractalLexer::parseInteger(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(INTEGER);
}

{real} {
   yylval->dvalue = atof(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(REAL);
}

"fractal" {
   FractalLexer::getInstance()->advance(yytext);
   return(FRACTAL);
}

"mapping" {
   FractalLexer::getInstance()->advance(yytext);
   return(MAPPING);
}

"=>" {
   FractalLexer::getInstance()->advance(yytext);
   return(POINTTO);
}

"formula" {
   FractalLexer::getInstance()->advance(yytext);
   return(FORMULA);
}

"while" {
   FractalLexer::getInstance()->advance(yytext);
   return(WHILE);
}

"colors" {
   FractalLexer::getInstance()->advance(yytext);
   return(COLORS);
}

"complex" {
   FractalLexer::getInstance()->advance(yytext);
   return(COMPLEX);
}

"define" {
   FractalLexer::getInstance()->advance(yytext);
   return(DEFINE);
}

"else" {
   FractalLexer::getInstance()->advance(yytext);
   return(ELSE);
}

"elseif"|"elif" {
   FractalLexer::getInstance()->advance(yytext);
   return(ELSEIF);
}

"if" {
   FractalLexer::getInstance()->advance(yytext);
   return(IF);
}

"for" {
   FractalLexer::getInstance()->advance(yytext);
   return(FOR);
}

"print" {
   FractalLexer::getInstance()->advance(yytext);
   return(PRINT);
}

"println" {
   FractalLexer::getInstance()->advance(yytext);
   return(PRINTLN);
}

"map_color" {
   FractalLexer::getInstance()->advance(yytext);
   return(MAP_COLOR);
}

"break" {
   FractalLexer::getInstance()->advance(yytext);
   return(BREAK);
}

"continue" {
   FractalLexer::getInstance()->advance(yytext);
   return(CONTINUE);
}

"=" {
   FractalLexer::getInstance()->advance(yytext);
   return(EQUALS);
}

"+=" {
   FractalLexer::getInstance()->advance(yytext);
   return(PLUS_EQUALS);
}

"-=" {
   FractalLexer::getInstance()->advance(yytext);
   return(MINUS_EQUALS);
}

"*=" {
   FractalLexer::getInstance()->advance(yytext);
   return(TIMES_EQUALS);
}

"/=" {
   FractalLexer::getInstance()->advance(yytext);
   return(DIVIDE_EQUALS);
}

"." {
   FractalLexer::getInstance()->advance(yytext);
   return(DOT);
}

"repeat" {
   FractalLexer::getInstance()->advance(yytext);
   return(REPEAT);
}

"gradient" {
   FractalLexer::getInstance()->advance(yytext);
   return(GRADIENT);
}

   /***********************************************************************
    * Note that for the majority of the complex attributes
    * (real, imaginary, etc.) there is a long and short form of the
    * attribute.  These long and short forms *must* be kept in sync with
    * the strings listed in AttributeDoubleNode::lookup().  It would have
    * been nice to not have had to make the attributes into tokens but
    * going that route ended up causing ambiguity problems with the
    * grammar
    ***********************************************************************/
      
"real" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_REAL);
}

"imaginary"|"imag" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_IMAGINARY);
}

"degrees"|"deg" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_DEGREES);
}

"old_degrees"|"old_deg" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_OLD_DEGREES);
}

"radians"|"rad" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_RADIANS);
}

"old_radians"|"old_rad" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_OLD_RADIANS);
}

"sum_of_squares"|"ssq" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_SUM_OF_SQUARES);
}

"magnitude"|"mag" {
   yylval->complexAttribute = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(ATTRIBUTE_MAGNITUDE);
}

"set_color" {
   FractalLexer::getInstance()->advance(yytext);
   return(SET_COLOR);
}

"set_color_hsv" {
   FractalLexer::getInstance()->advance(yytext);
   return(SET_COLOR_HSV);
}

"true" {
   FractalLexer::getInstance()->advance(yytext);
   return(TOKEN_TRUE);
}

"false" {
   FractalLexer::getInstance()->advance(yytext);
   return(TOKEN_FALSE);
}

"null" {
   FractalLexer::getInstance()->advance(yytext);
   return(TOKEN_NULL);
}

"r_circle" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_CIRCLE);
}

"r_ellipse" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_ELLIPSE);
}

"r_rect" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_RECT);
}

"r_poly" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_POLY);
}

"r_spoly" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_SPOLY);
}

"r_cross" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_CROSS);
}

"r_not" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_NOT);
}

"r_and" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_AND);
}

"r_or" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_OR);
}

"r_xor" {
   FractalLexer::getInstance()->advance(yytext);
   return(R_XOR);
}

"inside" {
   FractalLexer::getInstance()->advance(yytext);
   return(INSIDE);
}

"text_intersect" {
   FractalLexer::getInstance()->advance(yytext);
   return(TEXT_INTERSECT);
}

"switch" {
   FractalLexer::getInstance()->advance(yytext);
   return(SWITCH);
}

"case" {
   FractalLexer::getInstance()->advance(yytext);
   return(CASE);
}

"default" {
   FractalLexer::getInstance()->advance(yytext);
   return(DEFAULT);
}

"++" {
   FractalLexer::getInstance()->advance(yytext);
   return(PLUS_PLUS);
}

"--" {
   FractalLexer::getInstance()->advance(yytext);
   return(MINUS_MINUS);
}


"<" {
   FractalLexer::getInstance()->advance(yytext);
   return(LT);
}

">" {
   FractalLexer::getInstance()->advance(yytext);
   return(GT);
}

"<=" {
   FractalLexer::getInstance()->advance(yytext);
   return(LE);
}

">=" {
   FractalLexer::getInstance()->advance(yytext);
   return(GE);
}

"!=" {
   FractalLexer::getInstance()->advance(yytext);
   return(NE);
}

"==" {
   FractalLexer::getInstance()->advance(yytext);
   return(EQ);
}

"||" {
   FractalLexer::getInstance()->advance(yytext);
   return(OR);
}

"&&" {
   FractalLexer::getInstance()->advance(yytext);
   return(AND);
}

{identifier} {
   yylval->identifier = strdup(yytext);
   FractalLexer::getInstance()->advance(yytext);
   return(IDENTIFIER);
}

{literal} {

   // Strip the quotes from around 'literal'

   yylval->literal = strdup(yytext + 1);
   yylval->literal[strlen(yytext) - 2] = '\0';

   FractalLexer::getInstance()->advance(yytext);
   return(LITERAL);
}

[ \t\r] {
   /* -- Ignore whitespace -- */
   FractalLexer::getInstance()->advance(yytext);
}

\n {
   FractalLexer::getInstance()->advance(yytext);
   FractalLexer::getInstance()->nextLine();
}
      
"/*" {
   FractalLexer::getInstance()->advance(yytext);
   BEGIN STATE_MULTI_LINE_COMMENT;
}

"//" {
   FractalLexer::getInstance()->advance(yytext);
   BEGIN STATE_SINGLE_LINE_COMMENT;
}

"#" {
   FractalLexer::getInstance()->advance(yytext);
   BEGIN STATE_SINGLE_LINE_COMMENT;
}

. {
   FractalLexer::getInstance()->advance(yytext);
   return(*yytext);
}

   /* -- Token handling for STATE_MULTI_LINE_COMMENT  -- */

<STATE_MULTI_LINE_COMMENT>\n {
   FractalLexer::getInstance()->advance(yytext);
   FractalLexer::getInstance()->nextLine();
}

<STATE_MULTI_LINE_COMMENT>. {
   /* -- Ignore -- */
   FractalLexer::getInstance()->advance(yytext);
}

<STATE_MULTI_LINE_COMMENT>"*/" {
   FractalLexer::getInstance()->advance(yytext);
   BEGIN INITIAL;
}

   /* -- Token handling for STATE_SINGLE_LINE_COMMENT  -- */

<STATE_SINGLE_LINE_COMMENT>\n {
   FractalLexer::getInstance()->advance(yytext);
   FractalLexer::getInstance()->nextLine();
   BEGIN INITIAL;
}

<STATE_SINGLE_LINE_COMMENT>. {
   /* -- Ignore -- */
   FractalLexer::getInstance()->advance(yytext);
}

%%

int yywrap() { return(1); }

static int my_yyinput(char *buffer, int maxsize)
{
   return(
      FractalLexer::getInstance()->getText(buffer, maxsize)
   );
}
