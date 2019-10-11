%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

// Include malloc.h to satisfy reference to "alloca" in bison-generated
// code on win32 platforms

#ifdef _WIN32
#   include <malloc.h>
#endif

#include "dcomplex.h"

#include "Fractal.h"

#include "DoubleNodeStack.h"
#include "BinaryDoubleNode.h"
#include "UnaryDoubleNode.h"
#include "VariableDoubleNode.h"
#include "ConstantDoubleNode.h"
#include "AttributeDoubleNode.h"
#include "OneArgFunctionDoubleNode.h"
#include "TwoArgFunctionDoubleNode.h"
#include "ThreeArgFunctionDoubleNode.h"
#include "MapColorFunctionDoubleNode.h"
#include "TernaryDoubleNode.h"
#include "TextIntersectNode.h"
#include "MapColorFunctionDoubleNodeStack.h"
#include "AssignmentDoubleNode.h"
#include "GetEntryDoubleNode.h"

#include "ComplexNodeStack.h"
#include "BinaryComplexNode.h"
#include "UnaryComplexNode.h"
#include "NumericComplexNode.h"
#include "VariableComplexNode.h"
#include "OneArgFunctionComplexNode.h"
#include "TwoArgFunctionComplexNode.h"
#include "MixedThreeArgFunctionComplexNode.h"
#include "TernaryComplexNode.h"
#include "AssignmentComplexNode.h"

#include "BooleanNodeStack.h"
#include "BooleanNode.h"
#include "ConditionalBooleanNode.h"
#include "RelationalBooleanNode.h"
#include "TrueBooleanNode.h"
#include "FalseBooleanNode.h"
#include "NotBooleanNode.h"

#include "ColorNodeStack.h"
#include "ColorStack.h"
#include "ColorsColorNode.h"
#include "Counter.h"
#include "DefineColorNode.h"
#include "GradientColorNode.h"
#include "RepeatColorNode.h"
#include "SingleColorColorNode.h"
#include "ColorTable.h"

#include "ConditionalStatement.h"
#include "CompoundStatement.h"
#include "CompoundStatementStack.h"
#include "ComplexAssignmentStatement.h"
#include "DoubleAssignmentStatement.h"
#include "RGBSetColorStatement.h"
#include "HSVSetColorStatement.h"
#include "IndexedSetColorStatement.h"
#include "ForStatement.h"
#include "NullStatement.h"
#include "PrintStatement.h"
#include "BreakStatement.h"
#include "ContinueStatement.h"
#include "ComplexNodePrintArg.h"
#include "DoubleNodePrintArg.h"
#include "LiteralPrintArg.h"
#include "FlagStack.h"
#include "SwitchStatement.h"
#include "SwitchStatementStack.h"

#include "InsideBooleanNode.h"
#include "RegionNodeStack.h"
#include "CircleRegionNode.h"
#include "EllipseRegionNode.h"
#include "RectRegionNode.h"
#include "PolyRegionNode.h"
#include "SPolyRegionNode.h"
#include "CrossRegionNode.h"
#include "NotRegionNode.h"
#include "AndRegionNode.h"
#include "OrRegionNode.h"
#include "XorRegionNode.h"

#include "dmemory.h"

#include "FractalLexer.h"
#include "fractal_parse.h"

#define YYERROR_VERBOSE (1)
#define YYDEBUG         (0)
#define YYPARSE_PARAM   voidPointer
#define ENV(x)          ((FractalParse *)voidPointer)->x

// A little trickiness to allow an additional variable to be passed
// to fractal_yyerror when it is called - this avoids the need for
// static (or global) data to record fractal_yyerror's error messages

#define fractal_yyerror(message) handleError(message, voidPointer)

extern "C" {
   int yylex(...);
}

// Local class representing parsing environment

struct FractalParse
{
   Fractal *fractalPtr;

   ComplexNodeStack                  complexNodeStack;
   BooleanNodeStack                  booleanNodeStack;
   DoubleNodeStack                   doubleNodeStack;
   RegionNodeStack                   regionNodeStack;
   ColorStack                        colorStack;
   ColorNodeStack                    colorNodeStack;
   CompoundStatementStack            compoundStack;
   MapColorFunctionDoubleNodeStack   mapStack;
   const DoubleAssignmentStatement  *currentDoubleAssign;
   const ComplexAssignmentStatement *currentComplexAssign;
   Counter                           theCounter;
   Counter                           conditionalCounter;
   Counter                           pointCounter;
   PrintStatement                   *printStatement;
   ostringstream                     errStream;
   FlagStack                         breakContinueAllowed;
   SwitchStatementStack              switchStack;

   int                    insideGradient;
   int                    mappingSectionStartOffset;
   int                    mappingSectionEndOffset;
   int                    errorLineNumber;

   FractalParse() :
      fractalPtr(0),
      currentDoubleAssign(0),
      currentComplexAssign(0),
      printStatement(0),
      insideGradient(0),
      mappingSectionStartOffset(0),
      mappingSectionEndOffset(0),
      errorLineNumber(0)
   {
      // Nothing to do
   }
};

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static int handleError(const char *s, void *voidPointer);

static Fractal *fractal_createFromText(
   const char *text,
   FractalParse &env,
   char **errorMessagePointer,
   int *errorLineNumberPointer
);

static void copyFromStream(ostringstream &theStream, char **dest);

static int handleComplexOperatorAssign(
   void *voidPointer,
   char *id,
   char *token,
   BinaryComplexNode::Operator op,
   int isPostAssign = FALSE
);

static void doubleToComplex(void *voidPointer, int reverseOrder = 0);

static int handleDoubleOperatorAssign(
   void *voidPointer,
   char *id,
   char *token,
   BinaryDoubleNode::Operator op,
   int isPostAssign = FALSE
);

%}

%pure_parser

%union
{
   double dvalue;
   int ivalue;
   char *identifier;
   char *complexAttribute;
   char *literal;
}

%token <dvalue>       REAL
%token <ivalue>       INTEGER
%token <identifier>   IDENTIFIER
%token <literal>      LITERAL

%token FRACTAL
%token MAPPING
%token POINTTO
%token FORMULA
%token WHILE
%token FOR
%token COLORS
%token DEFINE
%token REPEAT
%token GRADIENT
%token COMPLEX
%token SET_COLOR
%token SET_COLOR_HSV

%token EQUALS
%token PLUS_EQUALS
%token MINUS_EQUALS
%token TIMES_EQUALS
%token DIVIDE_EQUALS
%token DOT

%token TOKEN_TRUE
%token TOKEN_FALSE
%token TOKEN_NULL

%token PLUS_PLUS
%token MINUS_MINUS

%token PRINT
%token PRINTLN
%token MAP_COLOR
%token BREAK
%token CONTINUE

%token R_CIRCLE
%token R_ELLIPSE
%token R_RECT
%token R_POLY
%token R_SPOLY
%token R_CROSS
%token R_NOT
%token R_AND
%token R_OR
%token R_XOR
%token INSIDE
%token TEXT_INTERSECT
%token SWITCH
%token CASE
%token DEFAULT

%token <complexAttribute> ATTRIBUTE_REAL
%token <complexAttribute> ATTRIBUTE_IMAGINARY
%token <complexAttribute> ATTRIBUTE_DEGREES
%token <complexAttribute> ATTRIBUTE_OLD_DEGREES
%token <complexAttribute> ATTRIBUTE_RADIANS
%token <complexAttribute> ATTRIBUTE_OLD_RADIANS
%token <complexAttribute> ATTRIBUTE_MAGNITUDE
%token <complexAttribute> ATTRIBUTE_SUM_OF_SQUARES

%token LT
%token GT
%token LE
%token GE
%token NE
%token EQ
%token OR
%token AND

%token IF
%token ELSE
%token ELSEIF

%right DOT
%right PLUS_EQUALS MINUS_EQUALS TIMES_EQUALS DIVIDE_EQUALS
%right EQUALS
%right '?' ':'
%left OR
%left AND
%left LT GT LE GE NE EQ
%left '-' '+'
%left '*' '/'
%left '%'
%right '^'
%nonassoc '!'
%nonassoc UMINUS

%type <dvalue>           number
%type <dvalue>           numeric_expression
%type <complexAttribute> complex_attribute

%%

begin: FRACTAL
       {
          // Create our fractal object

          DNEW(ENV(fractalPtr), Fractal());
       }
       '{'
          sections
       '}'
   ;

sections: mapping colors formula | mapping formula
   ;

mapping: MAPPING
          {
            ENV(mappingSectionStartOffset) =
            FractalLexer::getInstance()->getFileOffset();
          }
        '{'
           '('
              numeric_expression ','
              numeric_expression ','
              numeric_expression ','
              numeric_expression
           ')'
           POINTTO
           '('
              numeric_expression ',' numeric_expression
           ')'
        '}'
         {
            ENV(mappingSectionEndOffset) =
            FractalLexer::getInstance()->getFileOffset();

            // Set our complex coordinates and our dimension values

            ENV(fractalPtr)->setComplexCoordinates(
               $5, $7, $9, $11
            );

            // Ensure both the height and width are > 0 (after rounding
            // them to the nearest integer)

            {
               int width  = (int)($15 < 0.0 ? $15 - 0.5 : $15 + 0.5);
               int height = (int)($17 < 0.0 ? $17 - 0.5 : $17 + 0.5);

               if(width <= 0 || height <= 0)
               {
                  ostringstream temp;

                  temp << "Width and height must be > 0: ["
                     << $15 << ", " << $17 << "]";

                  handleError(temp.str().c_str(), voidPointer);
                  return(-1);
               }

               ENV(fractalPtr)->setDimensions(width, height);
            }
         }
   ;

colors: COLORS
         '{'
            { ENV(theCounter).beginCount(); }
            entries
         '}'
         {
            ColorsColorNode *colorsPtr = 0;

            DNEW(
               colorsPtr,
              ColorsColorNode(
                  ENV(colorNodeStack), ENV(theCounter).endCount()
               )
            );

            colorsPtr->process(ENV(fractalPtr)->getColorTable());

            DDELETE(colorsPtr);
         }
   ;

entries: entry
   |     entries entry
   ;

entry: DEFINE '(' INTEGER ')'
      '{'
         { ENV(theCounter).beginCount(); }
         color_entries
      '}'
      {
         DefineColorNode *d = 0;

         DNEW(
            d,
            DefineColorNode(
               $3, ENV(colorNodeStack), ENV(theCounter).endCount()
            )
         );

         ENV(colorNodeStack).push(d);

         ENV(theCounter).increment();
      }
   |   DEFINE
      '{'
         { ENV(theCounter).beginCount(); }
         color_entries
      '}'
      {
         DefineColorNode *d = 0;

         DNEW(
            d,
            DefineColorNode(
               ENV(colorNodeStack), ENV(theCounter).endCount()
            )
         );

         ENV(colorNodeStack).push(d);

         ENV(theCounter).increment();
      }
   ;

color_entries: color_entry
   |           color_entries color_entry
   ;

color_entry: REPEAT '(' INTEGER ')' 
            '{'
               { ENV(theCounter).beginCount(); }
               color_entries
            '}'
            {
               RepeatColorNode *r = 0;

               DNEW(
                  r,
                  RepeatColorNode(
                     $3, ENV(colorNodeStack), ENV(theCounter).endCount()
                  )
               );

               ENV(colorNodeStack).push(r);

               ENV(theCounter).increment();
            }
   |         GRADIENT '(' INTEGER ')'
            '{'
               { ENV(insideGradient) = 1; ENV(theCounter).beginCount(); }
               gradient
               { ENV(insideGradient) = 0; }
            '}'
            {
               string errMsg;

               GradientColorNode *nodePtr =
                  GradientColorNode::create(
                     $3, ENV(colorStack), ENV(theCounter).endCount(), errMsg
                  );

               if(nodePtr)
               {
                  ENV(colorNodeStack).push(nodePtr);
                  ENV(theCounter).increment();
               }
               else
               {
                  handleError(errMsg.c_str(), voidPointer);
                  return(-1);
               }
            }
   |         single_color_entry
   ;

gradient: single_color_entry single_color_entries
   ;

single_color_entries: single_color_entry
   |                  single_color_entries single_color_entry
   ;

single_color_entry: '[' INTEGER INTEGER INTEGER ']'
                     {
                        if(ENV(insideGradient))
                        {
                           int *values = 0;

                           DNEW(values, int[3]);

                           values[0]   = $2;
                           values[1]   = $3;
                           values[2]   = $4;

                           ENV(colorStack).push(values);
                        }
                        else
                        {
                           SingleColorColorNode *s = 0;

                           DNEW(
                              s,
                              SingleColorColorNode(
                                 $2, $3, $4
                              )
                           );

                           ENV(colorNodeStack).push(s);
                        }

                        ENV(theCounter).increment();
                     }
   ;

zero_or_more_statements: /* empty */
   |                     statements;

statement_body: '{' zero_or_more_statements '}'
   ;

formula: FORMULA
         '{'
            {
               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
               ENV(breakContinueAllowed).push(FALSE);
            }

         zero_or_more_statements

            {
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setBeforeStatement(ptr);
            }

         WHILE
         '('
            boolean_expression
            {
               ENV(fractalPtr)->setCondition(ENV(booleanNodeStack).pop());
            }
         ')'
            {
               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
               ENV(breakContinueAllowed).push(TRUE);
            }
          statement_body
            {
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setStatement(ptr);
               ENV(breakContinueAllowed).pop();

               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
            }

         zero_or_more_statements
            {
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setAfterStatement(ptr);
               ENV(breakContinueAllowed).pop();
            }
         '}'
   ;

statements: statement
   |        statements statement
   ;

simple_statement: complex_assignment_statement
                  {
                     const Statement *s        = ENV(currentComplexAssign);
                     ENV(currentComplexAssign) = NULL;

                     ENV(compoundStack).top()->add(s);
                  }
   |              double_assignment_statement
                  {
                     const Statement *s       = ENV(currentDoubleAssign);
                     ENV(currentDoubleAssign) = NULL;

                     ENV(compoundStack).top()->add(s);
                  }
   |              set_color_statement
   |              null_statement
   |              print_statement
   |              break_statement
   |              continue_statement
   ;

statement: simple_statement ';'
   |       conditional_statement
   |       for_statement
   |       switch_statement
   ;

complex_assignment_statement: IDENTIFIER EQUALS complex_expression
   {
      dcomplex *ptr =
         ENV(fractalPtr)->getComplexVariables().assign($1);

      ComplexAssignmentStatement *statement = 0;

      DNEW(
         statement,
         ComplexAssignmentStatement(
            ptr, $1, ENV(complexNodeStack).pop()
         )
      );

      ENV(currentComplexAssign) = statement;

      free($1);
   }
   | IDENTIFIER EQUALS double_expression
   {
      doubleToComplex(voidPointer);

      dcomplex *ptr =
         ENV(fractalPtr)->getComplexVariables().assign($1);

      ComplexAssignmentStatement *statement = 0;

      DNEW(
         statement,
         ComplexAssignmentStatement(
            ptr, $1, ENV(complexNodeStack).top()
         )
      );

      ENV(currentComplexAssign) = statement;

      free($1);
   }
   |
   IDENTIFIER PLUS_EQUALS complex_expression
   {
      int status = handleComplexOperatorAssign(
         voidPointer, $1, "+=", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER PLUS_EQUALS double_expression
   {
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "+=", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER MINUS_EQUALS complex_expression
   {
      int status = handleComplexOperatorAssign(
         voidPointer, $1, "-=", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER MINUS_EQUALS double_expression
   {
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "-=", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER TIMES_EQUALS complex_expression
   {
      int status = handleComplexOperatorAssign(
         voidPointer, $1, "*=", BinaryComplexNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER TIMES_EQUALS double_expression
   {
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "*=", BinaryComplexNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER DIVIDE_EQUALS complex_expression
   {
      int status = handleComplexOperatorAssign(
         voidPointer, $1, "/=", BinaryComplexNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER DIVIDE_EQUALS double_expression
   {
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "/=", BinaryComplexNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER PLUS_PLUS
   {
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "++", BinaryComplexNode::_PLUS_, TRUE
      );

      if(status == -1)
         return(-1);
   }
   |
   PLUS_PLUS IDENTIFIER
   {
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, $2, "++", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   IDENTIFIER MINUS_MINUS
   {
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, $1, "--", BinaryComplexNode::_MINUS_, TRUE
      );

      if(status == -1)
         return(-1);
   }
   |
   MINUS_MINUS IDENTIFIER
   {
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, $2, "--", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   }
   ;

double_assignment_statement: '$' IDENTIFIER EQUALS double_expression
   {
      double *ptr = ENV(fractalPtr)->getDoubleVariables().assign($2);
      const DoubleNode *node = ENV(doubleNodeStack).pop();

      DoubleAssignmentStatement *statement = 0;
      DNEW(statement, DoubleAssignmentStatement(ptr, $2, node));

      ENV(currentDoubleAssign) = statement;

      free($2);
   }
  |
   '$' IDENTIFIER PLUS_EQUALS double_expression
   {
      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "+=", BinaryDoubleNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   '$' IDENTIFIER MINUS_EQUALS double_expression
   {
      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "-=", BinaryDoubleNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   '$' IDENTIFIER TIMES_EQUALS double_expression
   {
      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "*=", BinaryDoubleNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   }
   |
   '$' IDENTIFIER DIVIDE_EQUALS double_expression
   {
      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "/=", BinaryDoubleNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   }
   |
   '$' IDENTIFIER PLUS_PLUS
   {
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "++", BinaryDoubleNode::_PLUS_, TRUE
      );

      if(status == -1)
         return(-1);
   }
   |
   PLUS_PLUS '$' IDENTIFIER
   {
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, $3, "++", BinaryDoubleNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   }
   |
   '$' IDENTIFIER MINUS_MINUS
   {
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, $2, "--", BinaryDoubleNode::_MINUS_, TRUE
      );

      if(status == -1)
         return(-1);
   }
   |
   MINUS_MINUS '$' IDENTIFIER
   {
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, $3, "--", BinaryDoubleNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   }
   ;

set_color_statement: indexed_set_color_statement
   |                 rgb_set_color_statement
   |                 hsv_set_color_statement
   ;

indexed_set_color_statement: SET_COLOR '(' double_expression ')'
   {
      const DoubleNode *index = ENV(doubleNodeStack).pop();
      Statement *s = 0;
      DNEW(s, IndexedSetColorStatement(index, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(s);
   }
   ;

rgb_set_color_statement: SET_COLOR
                            '('
                               double_expression ','
                               double_expression ','
                               double_expression
                            ')'
   {
      const DoubleNode *blue   = ENV(doubleNodeStack).pop();
      const DoubleNode *green  = ENV(doubleNodeStack).pop();
      const DoubleNode *red    = ENV(doubleNodeStack).pop();

      Statement *s = 0;
      DNEW(s, RGBSetColorStatement(red, green, blue, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(s);
   }
   ;

hsv_set_color_statement: SET_COLOR_HSV
                            '('
                               double_expression ','
                               double_expression ','
                               double_expression
                            ')'
   {
      const DoubleNode *v = ENV(doubleNodeStack).pop();
      const DoubleNode *s = ENV(doubleNodeStack).pop();
      const DoubleNode *h = ENV(doubleNodeStack).pop();

      HSVSetColorStatement *st = 0;
      DNEW(st, HSVSetColorStatement(h, s, v, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(st);
   }
   ;

null_statement: TOKEN_NULL
   {
      NullStatement *n = 0;
      DNEW(n, NullStatement());
      ENV(compoundStack).top()->add(n);
   }
   ;

break_statement: BREAK
   {
      if(ENV(breakContinueAllowed).top())
      {
         BreakStatement *b = 0;
         DNEW(b, BreakStatement());

         ENV(compoundStack).top()->add(b);
      }
      else
      {
         handleError(
            "Illegal use of: 'break' statement", voidPointer
         );

         return(-1);
      }
   }
   ;

continue_statement: CONTINUE
   {
      if(ENV(breakContinueAllowed).top())
      {
         ContinueStatement *c = 0;
         DNEW(c, ContinueStatement());
         ENV(compoundStack).top()->add(c);
      }
      else
      {
         handleError(
            "Illegal use of: 'continue' statement", voidPointer
         );

         return(-1);
      }
   }
   ;

map_color:  MAP_COLOR '('
            {
               MapColorFunctionDoubleNode *m = 0;
               DNEW(m, MapColorFunctionDoubleNode());
               ENV(mapStack).push(m);
            }
            map_color_arg     ':'
            map_color_args    ':'
            map_color_args ')'
            {
               // Make sure we got at least 4 arguments and that the
               // total number of arguments is even

               const MapColorFunctionDoubleNode *node = ENV(mapStack).pop();

               int size = node->size();

               if(size < 4 || size % 2 != 0)
               {
                  ostringstream temp;

                  temp << "map_color: invalid number of " <<
                          "arguments (" << size << ")\n"  <<
                          "expected an even number of arguments >= 4";

                  handleError(temp.str().c_str(), voidPointer);
                  return(-1);
               }

               // Ok, all's cool - push our node onto doubleNodeStack

               ENV(doubleNodeStack).push(node);
            }
   ;

map_color_args: map_color_args ',' map_color_arg
   |            map_color_arg
   ;

map_color_arg: double_expression
               {
                  ENV(mapStack).top()->addArgument(
                     ENV(doubleNodeStack).pop()
                  );
               }
   ;

print_function: PRINT
               {
                  DNEW(ENV(printStatement), PrintStatement());
               }
|               PRINTLN
               {
                  DNEW(ENV(printStatement), PrintStatement(1));
               }
   ;

print_statement:  print_function '('
                  print_statement_args ')'
                  {
                     const Statement *statement = ENV(printStatement);
                     ENV(compoundStack).top()->add(statement);
                     ENV(printStatement) = NULL;
                  }
   ;

print_statement_args:  print_dest ',' print_args
   |                   print_args
   ;

print_args: print_args DOT print_arg
   |        print_arg
   ;

print_arg: double_expression
   {
      const DoubleNode *node = ENV(doubleNodeStack).pop();

      DoubleNodePrintArg *a = 0;
      DNEW(a, DoubleNodePrintArg(node));

      ENV(printStatement)->addPrintArg(a);
   }
   | complex_expression
   {
      const ComplexNode *node = ENV(complexNodeStack).pop();
      ComplexNodePrintArg *c = 0;
      DNEW(c, ComplexNodePrintArg(node));

      ENV(printStatement)->addPrintArg(c);
   }
   | LITERAL
   {
      LiteralPrintArg *a = 0;
      DNEW(a, LiteralPrintArg($1));
      ENV(printStatement)->addPrintArg(a);
      free($1);
   }
   ;

print_dest: LITERAL
            {
               ENV(printStatement)->setDestination($1);
               free($1);
            }
   ;

if_statement: IF '(' boolean_expression ')'
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());

                  ENV(compoundStack).push(c);

                  ENV(conditionalCounter).beginCount();
                  ENV(conditionalCounter).increment();
               }
               statement_body
   ;

else_statement: ELSE
                  {
                     CompoundStatement *c = 0;
                     DNEW(c, CompoundStatement());

                     ENV(compoundStack).push(c);
                  }
                statement_body
   ;

elseif_statement: ELSEIF '(' boolean_expression ')'
                  {
                     CompoundStatement *c = 0;
                     DNEW(c, CompoundStatement());

                     ENV(compoundStack).push(c);

                     ENV(conditionalCounter).increment();
                  }
                  statement_body
   ;

start_conditional_statement: if_statement
   |                         if_statement elseif_statements
   ;

elseif_statements: elseif_statements elseif_statement
   |               elseif_statement
   ;

conditional_statement: start_conditional_statement
                        {
                           int size = ENV(conditionalCounter).endCount();

                           const Statement **statements = 0;
                           DNEW(statements, const Statement *[size]);

                           const BooleanNode **conditions = 0;
                           DNEW(conditions, const BooleanNode *[size]);

                           for(int i = 0, j = size - 1; i < size; i ++, j --)
                           {
                              statements[j] = ENV(compoundStack).pop();
                              conditions[j] = ENV(booleanNodeStack).pop();
                           }

                           ConditionalStatement *c = 0;

                           DNEW(
                              c,
                              ConditionalStatement(
                                 statements, conditions, size
                              )
                           );

                           ENV(compoundStack).top()->add(c);
                       }
|                      start_conditional_statement else_statement
                       {
                           int size = ENV(conditionalCounter).endCount();

                           // The first statement on our stack will be
                           // our else statement - grab it now

                           const Statement *elseStatement =
                              ENV(compoundStack).pop();

                           const Statement **statements = 0;
                           DNEW(statements, const Statement *[size]);

                           const BooleanNode **conditions = 0;
                           DNEW(conditions, const BooleanNode *[size]);

                           for(int i = 0, j = size - 1; i < size; i ++, j --)
                           {
                              statements[j] = ENV(compoundStack).pop();
                              conditions[j] = ENV(booleanNodeStack).pop();
                           }

                           ConditionalStatement *s = 0;

                           DNEW(
                              s,
                              ConditionalStatement(
                                 statements, conditions, size, elseStatement
                              )
                           );

                           ENV(compoundStack).top()->add(s);
                       }
   ;

for_statement_list: /* empty */
   |                simple_statement
   |                for_statement_list ',' simple_statement
   ;

for_statement: FOR '('
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               }
               for_statement_list ';'
               boolean_expression ';'
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               }
               for_statement_list
               ')'
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
                  ENV(breakContinueAllowed).push(TRUE);
               }
               statement_body
               {
                  const CompoundStatement *bodyStatement =
                     ENV(compoundStack).pop();

                  const CompoundStatement *incrementStatement =
                     ENV(compoundStack).pop();

                  const CompoundStatement *initializeStatement =
                     ENV(compoundStack).pop();

                  const BooleanNode *condition =
                     ENV(booleanNodeStack).pop();

                  Statement *s = 0;

                  DNEW(
                     s,
                     ForStatement(
                        initializeStatement,
                        condition,
                        incrementStatement,
                        bodyStatement
                     )
                  );

                  ENV(compoundStack).top()->add(s);
                  ENV(breakContinueAllowed).pop();
               }
   ;

switch_statement: SWITCH '(' double_expression ')'
                  {
                     SwitchStatement *sw = 0;
                     DNEW(sw, SwitchStatement(ENV(doubleNodeStack).pop()));

                     ENV(switchStack).push(sw);
                     ENV(breakContinueAllowed).push(FALSE);
                  }
                  '{'
                      switch_body
                  '}'
                  {
                     const SwitchStatement *sw = ENV(switchStack).pop();
                     ENV(compoundStack).top()->add(sw);
                     ENV(breakContinueAllowed).pop();
                  }
   ;

switch_body: /* empty */
   |         case_statements
   |         case_statements default_statement
   |         default_statement
   ;

case_statements: case_statement
   |             case_statements case_statement
   ;

case_statement:
               {
                  ENV(switchStack).top()->caseBegin();
               }
               case_entries
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());

                  ENV(compoundStack).push(c);
               }
               case_body
               {
                  ENV(switchStack).top()->caseAddStatements(
                     ENV(compoundStack).pop()
                  );
               }
   ;

case_entries: case_entries case_entry
   |          case_entry
   ;

case_entry: CASE double_expression ':'
            {
               ENV(switchStack).top()->caseAddNode(
                  ENV(doubleNodeStack).pop()
               );
            }
   ;

default_statement:
               {
                  ENV(switchStack).top()->caseBegin();
               }
               default_entry
               {
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               }
               case_body
               {
                  ENV(switchStack).top()->caseAddStatements(
                     ENV(compoundStack).pop()
                  );
               }
   ;

default_entry: DEFAULT ':'
   ;

case_body: '{' zero_or_more_statements '}'
   |       '{' zero_or_more_statements '}' BREAK ';'
            {
               ENV(switchStack).top()->caseSetBreak();
            }
   ;

boolean_expression: TOKEN_TRUE
                     {
                        TrueBooleanNode *t = 0;
                        DNEW(t, TrueBooleanNode());
                        ENV(booleanNodeStack).push(t);
                     }
|
                    TOKEN_FALSE
                     {
                        FalseBooleanNode *f = 0;
                        DNEW(f, FalseBooleanNode());
                        ENV(booleanNodeStack).push(f);
                     }
|
                    boolean_expression AND boolean_expression
                     {
                        const BooleanNode *right = ENV(booleanNodeStack).pop();
                        const BooleanNode *left  = ENV(booleanNodeStack).pop();

                        ConditionalBooleanNode *c = 0;

                        DNEW(
                           c,
                           ConditionalBooleanNode(
                              left,
                              ConditionalBooleanNode::_AND_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(c);
                     }
   |                boolean_expression OR  boolean_expression
                     {
                        const BooleanNode *right = ENV(booleanNodeStack).pop();
                        const BooleanNode *left  = ENV(booleanNodeStack).pop();

                        ConditionalBooleanNode *c = 0;

                        DNEW(
                           c,
                           ConditionalBooleanNode(
                              left,
                              ConditionalBooleanNode::_OR_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(c);
                     }
   |                '(' boolean_expression ')'
                     {
                        /* -- Nothing to do -- */
                     }
   |                double_expression LT double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_LT_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                double_expression LE double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_LE_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                double_expression GT double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_GT_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                double_expression GE double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_GE_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                double_expression EQ double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_EQ_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                double_expression NE double_expression
                     {
                        const DoubleNode *right = ENV(doubleNodeStack).pop();
                        const DoubleNode *left  = ENV(doubleNodeStack).pop();

                        RelationalBooleanNode *r = 0;

                        DNEW(
                           r,
                           RelationalBooleanNode(
                              left,
                              RelationalBooleanNode::_NE_,
                              right
                           )
                        );

                        ENV(booleanNodeStack).push(r);
                     }
   |                inside_boolean_expression
   |                '!' boolean_expression
                    {
                        NotBooleanNode *n = 0;

                        DNEW(
                           n, NotBooleanNode(ENV(booleanNodeStack).pop())
                        );

                        ENV(booleanNodeStack).push(n);
                    }
   ;

double_ternary_expression:  boolean_expression '?'
                            double_expression ':' double_expression
   |                        '{' double_ternary_expression '}'
   ;

double_expression: double_expression '+' double_expression
            {
               const DoubleNode *right = ENV(doubleNodeStack).pop();
               const DoubleNode *left  = ENV(doubleNodeStack).pop();

               BinaryDoubleNode *b = 0;

               DNEW(
                  b,
                  BinaryDoubleNode(
                     left,
                     BinaryDoubleNode::_PLUS_,
                     right
                  )
               );

               ENV(doubleNodeStack).push(b);
            }
   |        double_expression '-' double_expression
            {
               const DoubleNode *right = ENV(doubleNodeStack).pop();
               const DoubleNode *left  = ENV(doubleNodeStack).pop();

               BinaryDoubleNode *b = 0;

               DNEW(
                  b,
                  BinaryDoubleNode(
                     left,
                     BinaryDoubleNode::_MINUS_,
                     right
                  )
               );

               ENV(doubleNodeStack).push(b);
            }
   |        double_expression '*' double_expression
            {
               const DoubleNode *right = ENV(doubleNodeStack).pop();
               const DoubleNode *left  = ENV(doubleNodeStack).pop();

               BinaryDoubleNode *b = 0;

               DNEW(
                  b,
                  BinaryDoubleNode(
                     left,
                     BinaryDoubleNode::_MULTIPLY_,
                     right
                  )
               );

               ENV(doubleNodeStack).push(b);
            }
   |        double_expression '/' double_expression
            {
               const DoubleNode *right = ENV(doubleNodeStack).pop();
               const DoubleNode *left  = ENV(doubleNodeStack).pop();

               BinaryDoubleNode *b = 0;

               DNEW(
                  b,
                  BinaryDoubleNode(
                     left,
                     BinaryDoubleNode::_DIVIDE_,
                     right
                  )
               );

               ENV(doubleNodeStack).push(b);
            }
   |        double_expression '%' double_expression
            {
               // We just map this to 'mod', so acquire that function
               // pointer

               const char *mod = TwoArgFunctionDoubleNode::MOD;

               TwoArgFunctionDoublePointer fPtr =
                  TwoArgFunctionDoubleNode::lookup(mod);

               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               TwoArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionDoubleNode(
                     mod, fPtr, first, second
                  )
               );

               ENV(doubleNodeStack).push(t);
            }
   |        double_expression '^' double_expression
            {
               // We just map this to 'pow', so acquire that function
               // pointer

               const char *pow = TwoArgFunctionDoubleNode::POW;

               TwoArgFunctionDoublePointer fPtr =
                  TwoArgFunctionDoubleNode::lookup(pow);

               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               TwoArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionDoubleNode(
                     pow, fPtr, first, second
                  )
               );

               ENV(doubleNodeStack).push(t);
            }
   |        '-' double_expression %prec UMINUS
            {
               UnaryDoubleNode *u = 0;

               DNEW(
                  u,
                  UnaryDoubleNode(
                     ENV(doubleNodeStack).pop()
                  )
               );

               ENV(doubleNodeStack).push(u);
            }
   |        '(' double_expression ')'
            {
               /* -- Nothing to do -- */
            }
   |        number
            {
               ConstantDoubleNode *c = 0;
               DNEW(c, ConstantDoubleNode($1));
               ENV(doubleNodeStack).push(c);
            }
   |        '$' IDENTIFIER
            {
               // Ensure this variable has been defined

               const double *ptr =
                  ENV(fractalPtr)->getDoubleVariables().lookup($2);

               if(ptr == NULL)
               {
                  ostringstream temp;

                  temp << "Undefined double variable: [$" << $2 << "]";

                  handleError(temp.str().c_str(), voidPointer);

                  free($2);
                  return(-1);
               }

               VariableDoubleNode *v = 0;
               DNEW(v, VariableDoubleNode($2, ptr));

               ENV(doubleNodeStack).push(v);
               free($2);
            }
   |        complex_attribute '(' complex_expression ')'
            {
               AttributeDoubleNode *ptr =
                  AttributeDoubleNode::create(
                     $1, ENV(complexNodeStack).pop()
                  );

               if(!ptr)
               {
                  /**********************************************
                   * This really shouldn't be possible unless
                   * the set of tokens (ATTRIBUTE_REAL,
                   * ATTRIBUTE_IMAGINARY, etc.) and the set of
                   * attribute functions in the source file
                   * AttributeDoubleNode.cpp have gotten out
                   * of sync
                   **********************************************/

                  ostringstream temp;

                  temp << "No matching attribute: " << $1 <<
                     "(complex_expression)";

                  handleError(temp.str().c_str(), voidPointer);

                  free($1);
                  return(-1);
               }

               free($1);

               ENV(doubleNodeStack).push(ptr);
            }
   |        map_color
            {
               /* -- Nothing to do -- */
            }
   |        IDENTIFIER '(' double_expression ')'
            {
               /* -- Attempt to look up the function requested -- */

               int error = FALSE;

               OneArgFunctionDoublePointer fPtr =
                  OneArgFunctionDoubleNode::lookup($1);

               if(!fPtr)
               {
                  // This could also be a GetEntryDoubleNode so
                  // try that as well

                  GetEntryDoubleNode::WhichEntry entry =
                     GetEntryDoubleNode::lookup($1);

                  if(entry == GetEntryDoubleNode::INVALID)
                  {
                     ostringstream temp;

                     temp << "No matching function: " << $1 <<
                        "(double)";

                     handleError(temp.str().c_str(), voidPointer);
                     error = TRUE;
                  }
                  else
                  {
                     GetEntryDoubleNode *g = 0;

                     DNEW(
                        g,
                        GetEntryDoubleNode(
                           $1,
                           entry,
                           ENV(doubleNodeStack).pop(),
                           *ENV(fractalPtr)
                        )
                     );

                     ENV(doubleNodeStack).push(g);
                  }
               }
               else
               {
                  OneArgFunctionDoubleNode *o = 0;

                  DNEW(
                     o,
                     OneArgFunctionDoubleNode(
                        $1, fPtr, ENV(doubleNodeStack).pop()
                     )
                  );

                  ENV(doubleNodeStack).push(o);
               }

               free($1);

               if(error)
                  return(-1);
            }
   |        IDENTIFIER '(' double_expression ',' double_expression ')'
            {
               /* -- Attempt to look up the function requested -- */

               TwoArgFunctionDoublePointer fPtr =
                  TwoArgFunctionDoubleNode::lookup($1);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << $1 <<
                     "(double, double)";
                
                  handleError(temp.str().c_str(), voidPointer);

                  free($1);
                  return(-1);
               }

               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               TwoArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionDoubleNode(
                     $1, fPtr, first, second
                  )
               );

               ENV(doubleNodeStack).push(t);

               free($1);
            }
   |        IDENTIFIER '('
               double_expression ',' double_expression ',' double_expression
            ')'
            {
               /* -- Attempt to look up the function requested -- */

               ThreeArgFunctionDoublePointer fPtr =
                  ThreeArgFunctionDoubleNode::lookup($1);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << $1 <<
                     "(double, double, double)";
                
                  handleError(temp.str().c_str(), voidPointer);

                  free($1);
                  return(-1);
               }

               const DoubleNode *third  = ENV(doubleNodeStack).pop();
               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               ThreeArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  ThreeArgFunctionDoubleNode(
                     $1, fPtr, first, second, third
                  )
               );

               ENV(doubleNodeStack).push(t);

               free($1);
            }
   |        TEXT_INTERSECT '('
               LITERAL            ','
               complex_expression ','
               double_expression  ','
               double_expression  ','
               complex_expression
            ')'
            {
               const ComplexNode *point  = ENV(complexNodeStack).pop();
               const DoubleNode  *thick  = ENV(doubleNodeStack).pop();
               const DoubleNode  *height = ENV(doubleNodeStack).pop();
               const ComplexNode *origin = ENV(complexNodeStack).pop();

               TextIntersectNode *t = 0;

               DNEW(
                  t,
                  TextIntersectNode(
                     $3, origin, height, thick, point
                  )
               );

               ENV(doubleNodeStack).push(t);

               free($3);
            }
   |        double_ternary_expression
            {
               const BooleanNode *test   = ENV(booleanNodeStack).pop();
               const DoubleNode  *second = ENV(doubleNodeStack).pop();
               const DoubleNode  *first  = ENV(doubleNodeStack).pop();

               TernaryDoubleNode *t = 0;
               DNEW(t, TernaryDoubleNode(test, first, second));

               ENV(doubleNodeStack).push(t);
            }
   |        double_assignment_statement
            {
               const DoubleAssignmentStatement *s =
                  ENV(currentDoubleAssign);

               ENV(currentDoubleAssign) = NULL;

               AssignmentDoubleNode *a = 0;
               DNEW(a, AssignmentDoubleNode(s));
               ENV(doubleNodeStack).push(a);
            }
   ;

complex_attribute: ATTRIBUTE_REAL
   |               ATTRIBUTE_IMAGINARY
   |               ATTRIBUTE_DEGREES
   |               ATTRIBUTE_OLD_DEGREES
   |               ATTRIBUTE_RADIANS
   |               ATTRIBUTE_OLD_RADIANS
   |               ATTRIBUTE_SUM_OF_SQUARES
   |               ATTRIBUTE_MAGNITUDE
   ;

mixed_add_expression: complex_expression '+' double_expression
                     { doubleToComplex(voidPointer);    }
   |                  double_expression  '+' complex_expression
                     { doubleToComplex(voidPointer, 1); }
   ;

complex_add_expression: complex_expression '+' complex_expression
   |                    mixed_add_expression
   ;

mixed_subtract_expression: complex_expression '-' double_expression
                           { doubleToComplex(voidPointer);    }
   |                       double_expression  '-' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_subtract_expression: complex_expression '-' complex_expression
   |                         mixed_subtract_expression
   ;

mixed_multiply_expression: complex_expression '*' double_expression
                           { doubleToComplex(voidPointer);    }
   |                       double_expression  '*' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_multiply_expression: complex_expression '*' complex_expression
   |                         mixed_multiply_expression
   ;

mixed_divide_expression: complex_expression '/' double_expression
                           { doubleToComplex(voidPointer);    }
   |                     double_expression  '/' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_divide_expression: complex_expression '/' complex_expression
   |                       mixed_divide_expression
   ;

mixed_power_expression: complex_expression '^' double_expression
                           { doubleToComplex(voidPointer);    }
   |                    double_expression '^' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_power_expression: complex_expression '^' complex_expression
   |                      mixed_power_expression
   ;

mixed_two_arg_expression: complex_expression ',' double_expression
                           { doubleToComplex(voidPointer);    }
   |                      double_expression  ',' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_two_arg_expression: complex_expression ',' complex_expression
   |                        mixed_two_arg_expression
   ;

mixed_ternary_arguments:  complex_expression ':' double_expression
                           { doubleToComplex(voidPointer);    }
   |                      double_expression  ':' complex_expression
                           { doubleToComplex(voidPointer, 1); }
   ;

complex_ternary_arguments: complex_expression ':' complex_expression
   |                        mixed_ternary_arguments
   ;

complex_ternary_expression: boolean_expression '?' complex_ternary_arguments
   |                        '{' complex_ternary_expression '}'
   ;

complex_expression: complex_add_expression
            {
               const ComplexNode *right = ENV(complexNodeStack).pop();
               const ComplexNode *left  = ENV(complexNodeStack).pop();

               BinaryComplexNode *b = 0;

               DNEW(
                  b,
                  BinaryComplexNode(
                     left,
                     BinaryComplexNode::_PLUS_,
                     right
                  )
               );

               ENV(complexNodeStack).push(b);
            }
   |        complex_subtract_expression
            {
               const ComplexNode *right = ENV(complexNodeStack).pop();
               const ComplexNode *left  = ENV(complexNodeStack).pop();

               BinaryComplexNode *b = 0;

               DNEW(
                  b,
                  BinaryComplexNode(
                     left,
                     BinaryComplexNode::_MINUS_,
                     right
                  )
               );

               ENV(complexNodeStack).push(b);
            }
   |        complex_multiply_expression
            {
               const ComplexNode *right = ENV(complexNodeStack).pop();
               const ComplexNode *left  = ENV(complexNodeStack).pop();

               BinaryComplexNode *b = 0;

               DNEW(
                  b,
                  BinaryComplexNode(
                     left,
                     BinaryComplexNode::_MULTIPLY_,
                     right
                  )
               );

               ENV(complexNodeStack).push(b);
            }
   |        complex_divide_expression
            {
               const ComplexNode *right = ENV(complexNodeStack).pop();
               const ComplexNode *left  = ENV(complexNodeStack).pop();

               BinaryComplexNode *b = 0;

               DNEW(
                  b,
                  BinaryComplexNode(
                     left,
                     BinaryComplexNode::_DIVIDE_,
                     right
                  )
               );

               ENV(complexNodeStack).push(b);
            }
   |        complex_power_expression
            {
               // We just map this to 'pow', so acquire that function
               // pointer

               const char *pow = TwoArgFunctionDoubleNode::POW;

               TwoArgFunctionComplexPointer fPtr =
                  TwoArgFunctionComplexNode::lookup(pow);

               const ComplexNode *second = ENV(complexNodeStack).pop();
               const ComplexNode *first  = ENV(complexNodeStack).pop();

               TwoArgFunctionComplexNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionComplexNode(
                     pow, fPtr, first, second
                  )
               );

               ENV(complexNodeStack).push(t);
            }
   |        '-' complex_expression %prec UMINUS
            {
               UnaryComplexNode *u = 0;

               DNEW(
                  u,
                  UnaryComplexNode(
                     ENV(complexNodeStack).pop()
                  )
               );

               ENV(complexNodeStack).push(u);
            }
   |        '(' complex_expression ')'
            {
               /* -- Nothing to do -- */
            }
   |        COMPLEX '(' double_expression ')'
            {
               // Strictly speaking, we don't actually need COMPLEX
               // at all anymore now that we've revamped the automatic
               // double -> complex conversions but there's no harm
               // in supporting it for compatibility reasons

               doubleToComplex(voidPointer);
            }
   |        '[' double_expression ',' double_expression ']'
            {
               const DoubleNode *imaginaryPart = ENV(doubleNodeStack).pop();
               const DoubleNode *realPart      = ENV(doubleNodeStack).pop();

               NumericComplexNode *n = 0;
               DNEW(n, NumericComplexNode(realPart, imaginaryPart));

               ENV(complexNodeStack).push(n);
            }
   |        IDENTIFIER
            {
               /* -- Ensure this variable has been defined -- */

               dcomplex *ptr =
                  ENV(fractalPtr)->getComplexVariables().lookup($1);

               if(ptr == NULL)
               {
                  ostringstream temp;

                  temp << "Undefined variable: [" << $1 << "]";

                  handleError(temp.str().c_str(), voidPointer);

                  free($1);
                  return(-1);
               }

               VariableComplexNode *v = 0;
               DNEW(v, VariableComplexNode($1, ptr));
               ENV(complexNodeStack).push(v);

               free($1);
            }
   |        IDENTIFIER '(' complex_expression ')'
            {
               /* -- Attempt to look up the function requested -- */

               OneArgFunctionComplexPointer fPtr =
                  OneArgFunctionComplexNode::lookup($1);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << $1
                     << "(complex)";

                  handleError(temp.str().c_str(), voidPointer);

                  free($1);
                  return(-1);
               }

               OneArgFunctionComplexNode *o = 0;

               DNEW(
                  o,
                  OneArgFunctionComplexNode(
                     $1, fPtr, ENV(complexNodeStack).pop()
                  )
               );

               ENV(complexNodeStack).push(o);

               free($1);
            }
   |        IDENTIFIER '(' complex_two_arg_expression ')'
            {
               /* -- Attempt to look up the function requested -- */

               TwoArgFunctionComplexPointer fPtr =
                  TwoArgFunctionComplexNode::lookup($1);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << $1
                       << "(complex, complex)";

                  handleError(temp.str().c_str(), voidPointer);
                  
                  free($1);
                  return(-1);
               }

               const ComplexNode *second = ENV(complexNodeStack).pop();
               const ComplexNode *first  = ENV(complexNodeStack).pop();

               TwoArgFunctionComplexNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionComplexNode(
                     $1, fPtr, first, second
                  )
               );

               ENV(complexNodeStack).push(t);

               free($1);
            }
   |        IDENTIFIER '('
               complex_two_arg_expression ',' double_expression
            ')'
            {
               /* -- Attempt to look up the function requested -- */

               MixedThreeArgFunctionComplexPointer fPtr =
                  MixedThreeArgFunctionComplexNode::lookup($1);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << $1
                       << "(complex, complex, double)";

                  handleError(temp.str().c_str(), voidPointer);
                  
                  free($1);
                  return(-1);
               }

               const ComplexNode *second = ENV(complexNodeStack).pop();
               const ComplexNode *first  = ENV(complexNodeStack).pop();
               const DoubleNode *third   = ENV(doubleNodeStack).pop();

               MixedThreeArgFunctionComplexNode *m = 0;

               DNEW(
                  m,
                  MixedThreeArgFunctionComplexNode(
                     $1, fPtr, first, second, third
                  )
               );

               ENV(complexNodeStack).push(m);

               free($1);
            }
   |        complex_ternary_expression
            {
               const BooleanNode *test    = ENV(booleanNodeStack).pop();
               const ComplexNode  *second = ENV(complexNodeStack).pop();
               const ComplexNode  *first  = ENV(complexNodeStack).pop();

               TernaryComplexNode *t = 0;
               DNEW(t, TernaryComplexNode(test, first, second));

               ENV(complexNodeStack).push(t);
            }
   |        complex_assignment_statement
            {
               const ComplexAssignmentStatement *s =
                  ENV(currentComplexAssign);

               ENV(currentComplexAssign) = NULL;

               AssignmentComplexNode *a = 0;
               DNEW(a, AssignmentComplexNode(s));

               ENV(complexNodeStack).push(a);
            }
   ;

number: REAL
         {
            $$ = $1;
         }
   |    INTEGER
         {
            $$ = (double)$1;
         }
   ;

numeric_expression: numeric_expression '+' numeric_expression
                     {
                        $$ = $1 + $3;
                     }
   |                numeric_expression '-' numeric_expression
                     {
                        $$ = $1 - $3;
                     }
   |                numeric_expression '*' numeric_expression
                     {
                        $$ = $1 * $3;
                     }
   |                numeric_expression '/' numeric_expression
                     {
                        $$ = $1 / $3;
                     }
   |                '-' numeric_expression %prec UMINUS
                     {
                        $$ = -$2;
                     }
   |                 '(' numeric_expression ')'
                     {
                        $$ = $2;
                     }
   |                 number
                     {
                        $$ = $1;
                     }
   ;

more_r_poly_points: more_r_poly_points ',' complex_expression
               {
                  ENV(pointCounter).increment();
               }
   |         complex_expression
               {
                  ENV(pointCounter).increment();
               }
   ;


region: R_CIRCLE '(' complex_expression ',' double_expression ')'
         {
            const ComplexNode *center = ENV(complexNodeStack).pop();
            const DoubleNode  *radius = ENV(doubleNodeStack).pop();

            CircleRegionNode *c = 0;
            DNEW(c, CircleRegionNode(center, radius));
            ENV(regionNodeStack).push(c);
         }
|       R_ELLIPSE '(' complex_expression ','
           double_expression ',' double_expression ')'
         {
            const ComplexNode *center  = ENV(complexNodeStack).pop();
            const DoubleNode  *yradius = ENV(doubleNodeStack).pop();
            const DoubleNode  *xradius = ENV(doubleNodeStack).pop();

            EllipseRegionNode *e = 0;
            DNEW(e, EllipseRegionNode(center, xradius, yradius));

            ENV(regionNodeStack).push(e);
         }
   |    R_RECT '(' complex_expression ',' complex_expression ')'
         {
            const ComplexNode *second = ENV(complexNodeStack).pop();
            const ComplexNode *first  = ENV(complexNodeStack).pop();

            RectRegionNode *r = 0;
            DNEW(r, RectRegionNode(first, second));
            ENV(regionNodeStack).push(r);
         }
   |    R_POLY '(' complex_expression ',' complex_expression ','
         {
            ENV(pointCounter).beginCount();
            ENV(pointCounter).increment();
            ENV(pointCounter).increment();
         }
         more_r_poly_points
        ')'
         {
            int size = ENV(pointCounter).endCount();

            const ComplexNode **points = 0;
            DNEW(points, const ComplexNode *[size]);

            for(int i = 0, j = size - 1; i < size; i ++, j --)
               points[j] = ENV(complexNodeStack).pop();

            PolyRegionNode *n = 0;

            DNEW(n, PolyRegionNode(points, size));

            ENV(regionNodeStack).push(n);
         }
   |    R_SPOLY '(' complex_expression ',' double_expression ','
                    double_expression  ',' double_expression ')'
         {
            const ComplexNode *center = ENV(complexNodeStack).pop();
            const DoubleNode  *angle  = ENV(doubleNodeStack).pop();
            const DoubleNode  *radius = ENV(doubleNodeStack).pop();
            const DoubleNode  *nSides = ENV(doubleNodeStack).pop();

            SPolyRegionNode *s = 0;
            DNEW(s, SPolyRegionNode(center, nSides, radius, angle));
            ENV(regionNodeStack).push(s);
         }
   |    R_CROSS '(' complex_expression ',' complex_expression ','
                    double_expression  ',' double_expression ')'
                 
         {
            const ComplexNode *p2     = ENV(complexNodeStack).pop();
            const ComplexNode *p1     = ENV(complexNodeStack).pop();
            const DoubleNode  *height = ENV(doubleNodeStack).pop();
            const DoubleNode  *width  = ENV(doubleNodeStack).pop();

            CrossRegionNode *c = 0;
            DNEW(c, CrossRegionNode(p1, p2, width, height));
            ENV(regionNodeStack).push(c);
         }
   |    R_NOT '(' region ')'
         {
            const RegionNode *node = ENV(regionNodeStack).pop();

            NotRegionNode *n = 0;
            DNEW(n, NotRegionNode(node));
            ENV(regionNodeStack).push(n);
         }
   |    R_AND '(' region ',' region ')'
         {
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            AndRegionNode *a = 0;
            DNEW(a, AndRegionNode(first, second));
            ENV(regionNodeStack).push(a);
         }
   |    R_OR  '(' region ',' region ')'
   {
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            OrRegionNode *o = 0;
            DNEW(o, OrRegionNode(first, second));
            ENV(regionNodeStack).push(o);
   }
   |    R_XOR '(' region ',' region ')'
   {
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            XorRegionNode *x = 0;
            DNEW(x, XorRegionNode(first, second));
            ENV(regionNodeStack).push(x);
   }
   ;

inside_boolean_expression: INSIDE '(' complex_expression ',' region ')'
   {
      const ComplexNode *point = ENV(complexNodeStack).pop();
      const RegionNode *region = ENV(regionNodeStack).pop();

      InsideBooleanNode *i = 0;
      DNEW(i, InsideBooleanNode(point, region));
      ENV(booleanNodeStack).push(i);
   }
   ;

%%

/*****************************************************************************
 * Local functions
 *****************************************************************************/

static int handleError(const char *s, void *voidPointer)
{
   char currentLine[FractalLexer::MAX_LINE_LENGTH + 1];
   FractalLexer *env = FractalLexer::getInstance();

   // Record the line number where the error took place

   ENV(errorLineNumber) = env->getLineNumber();

   env->getCurrentLine(currentLine);

   ENV(errStream) << "line " << ENV(errorLineNumber) << ": " << s << "\n";
   ENV(errStream) << currentLine << "\n";

   int lineOffset = env->getLineOffset();

   for(int i = 0; i < lineOffset; i ++)
   {
      ENV(errStream) << ' ';
   }

   ENV(errStream) << '^' << '\0';

   return(0);
}

static Fractal *fractal_createFromText(
   const char *text,
   FractalParse &env,
   char **errorMessagePointer,
   int *errorLineNumberPointer
)
{
#if YYDEBUG != 0
   yydebug = 1;
#endif

   *errorMessagePointer    = 0;
   *errorLineNumberPointer = 0;

   FractalLexer::getInstance()->begin(text);

   int success = (yyparse(&env) == 0);

   FractalLexer::getInstance()->end();

   if(success)
   {
      // Uncomment the following for debugging output
      // cout << *env.fractalPtr << "\n";

      return(env.fractalPtr);
   }

   // Delete fractalPtr as it is very likely in some intermediate state

   DDELETE(env.fractalPtr);

   // Ensure any error messages make their way to the client

   copyFromStream(env.errStream, errorMessagePointer);

   // Also grab the line number of the error

   *errorLineNumberPointer = env.errorLineNumber;

   // Return null indicating an unsuccessful parse

   return(0);
}

static void copyFromStream(ostringstream &theStream, char **dest)
{
   string s        = theStream.str();
   const char *ptr = s.c_str();

   DNEW(*dest, char[strlen(ptr) + 1]);

   strcpy(*dest, ptr);
}

static int handleComplexOperatorAssign(
   void *voidPointer,
   char *id,
   char *token,
   BinaryComplexNode::Operator op,
   int isPostAssign
)
{
   dcomplex *ptr =
      ENV(fractalPtr)->getComplexVariables().lookup(id);

   if(ptr == NULL)
   {
      ostringstream temp;

      temp << "Undefined variable: [" << id << "] "
           << "used with " << token;

      handleError(temp.str().c_str(), voidPointer);

      free(id);
      return(-1);
   }

   const ComplexNode *rhs           = ENV(complexNodeStack).pop();
   VariableComplexNode *value = 0;

   DNEW(value, VariableComplexNode(id, ptr));

   ComplexNode *node = 0;

   DNEW(node, BinaryComplexNode(value, op, rhs));

   ComplexAssignmentStatement *statement = 0;
   DNEW(
      statement, ComplexAssignmentStatement(ptr, id, node, isPostAssign)
   );

   ENV(currentComplexAssign) = statement;

   return(0);
}

static void doubleToComplex(void *voidPointer, int reverseOrder)
{
   NumericComplexNode *n = 0;
   DNEW(n, NumericComplexNode(ENV(doubleNodeStack).pop()));

   ENV(complexNodeStack).push(n);

   if(reverseOrder)
   {
      const ComplexNode *first  = ENV(complexNodeStack).pop();
      const ComplexNode *second = ENV(complexNodeStack).pop();

      ENV(complexNodeStack).push(first);
      ENV(complexNodeStack).push(second);
   }
}

static int handleDoubleOperatorAssign(
   void *voidPointer,
   char *id,
   char *token,
   BinaryDoubleNode::Operator op,
   int isPostAssign
)
{
   double *ptr = ENV(fractalPtr)->getDoubleVariables().lookup(id);

   if(ptr == NULL)
   {
      ostringstream temp;

      temp << "Undefined variable: [" << id << "] "
           << "used with " << token;

      handleError(temp.str().c_str(), voidPointer);

      free(id);
      return(-1);
   }

   const DoubleNode *rhs = ENV(doubleNodeStack).pop();

   VariableDoubleNode *value = 0;
   DNEW(value, VariableDoubleNode(id, ptr));

   DoubleNode *node = 0;
   DNEW(node, BinaryDoubleNode(value, op, rhs));

   DoubleAssignmentStatement *statement = 0;
   DNEW(
      statement, DoubleAssignmentStatement(ptr, id, node, isPostAssign)
   );

   ENV(currentDoubleAssign) = statement;

   free(id);

   return(0);
}

/*****************************************************************************
 * Globally exported functions
 *****************************************************************************/

char *fractal_slurpFile(const char *fileName, char **errorMessagePointer)
{
   ostringstream errStream;
   FILE *f = 0;

   if((f = fopen(fileName, "rb")) == 0)
   {
      errStream << "Unable to open input file: [" << fileName << "]";
      copyFromStream(errStream, errorMessagePointer);

      return(0);
   }

   fseek(f, 0, 2);
   int size = ftell(f);
   fseek(f, 0, 0);

   char *text = 0;
   DNEW(text, char[size + 1]);

   int count  = fread(text, size, 1, f);
   text[size] = '\0';
   fclose(f);

   if(count != 1)
   {
      errStream << "Error reading: [" << size <<
         "] bytes from file: [" << fileName << "]" << '\0';

      copyFromStream(errStream, errorMessagePointer);

      DADELETE(text);
      return(0);
   }

   return(text);
}

Fractal *fractal_createFromText(
   const char *text,
   char **errorMessagePointer,
   int *errorLineNumberPointer
)
{
   FractalParse env;

   return(
      fractal_createFromText(
         text,
         env,
         errorMessagePointer,
         errorLineNumberPointer
      )
   );
}

int fractal_createZoomBuffer(
   const char *buffer,
   char **zoomBufferPtr,
   double x0, double y0, double x1, double y1,
   char **errorMessagePointer,
   int *errorLineNumberPointer,
   void *clientData,
   void (*mapFunction)(
      FractalDefinition *parent,
      FractalDefinition *child,
      double x0, double y0, double x1, double y1,
      void *clientData
   )
)
{
   FractalParse env;

   int returnValue = 0;

   Fractal *fractalPtr = fractal_createFromText(
      buffer,
      env,
      errorMessagePointer,
      errorLineNumberPointer
   );

   if(fractalPtr)
   {
      // Create and fill out our parent FractalDefinition structure

      FractalDefinition parent;

      parent.xStart      = fractalPtr->getXStart();
      parent.yStart      = fractalPtr->getYStart();
      parent.xEnd        = fractalPtr->getXEnd();
      parent.yEnd        = fractalPtr->getYEnd();
      parent.pixelWidth  = fractalPtr->getWidth();
      parent.pixelHeight = fractalPtr->getHeight();

      // 'mapFunction' will fill out child

      FractalDefinition child;

      child.xStart      = 0.0;
      child.yStart      = 0.0;
      child.xEnd        = 0.0;
      child.yEnd        = 0.0;
      child.pixelWidth  = 0.0;
      child.pixelHeight = 0.0;

      mapFunction(
         &parent,
         &child,
         x0, y0, x1, y1,
         clientData
      );

      char newMapping[1024];

      sprintf(
         newMapping,
         " {\n"
         "      (%.20f,\n"
         "       %.20f,\n"
         "       %.20f,\n"
         "       %.20f) => (%d, %d)\n"
         "   }",
         child.xStart, child.yStart,
         child.xEnd,   child.yEnd,
         (int)(child.pixelWidth  + 0.5),
         (int)(child.pixelHeight + 0.5)
      );

      int leadingChars  = env.mappingSectionStartOffset;
      int trailingChars = strlen(buffer) - env.mappingSectionEndOffset;

      // Here we seemingly allocate our buffer one byte too small but
      // in reality this is correct as we're going to leave off the
      // last byte of our trailing chars as otherwise we end up with
      // a spurious '\n' and our text grows longer by one (blank) line
      // each time we alter our mapping section via this function

      DNEW(
         *zoomBufferPtr,
         char[leadingChars + trailingChars + strlen(newMapping)]
      );

      // Note the use of 'trailingChars - 1' as per the above comment ...

      sprintf(
         *zoomBufferPtr,
         "%.*s%s%.*s",
         leadingChars, buffer,
         newMapping,
         trailingChars - 1,
         buffer + env.mappingSectionEndOffset
      );

      DDELETE(fractalPtr);

      returnValue = 1;
   }

   return(returnValue);
}
