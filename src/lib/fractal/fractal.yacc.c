/* A Bison parser, made from fractal.yacc
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse fractal_yyparse
#define yylex fractal_yylex
#define yyerror fractal_yyerror
#define yylval fractal_yylval
#define yychar fractal_yychar
#define yydebug fractal_yydebug
#define yynerrs fractal_yynerrs
# define	REAL	257
# define	INTEGER	258
# define	IDENTIFIER	259
# define	LITERAL	260
# define	FRACTAL	261
# define	MAPPING	262
# define	POINTTO	263
# define	FORMULA	264
# define	WHILE	265
# define	FOR	266
# define	COLORS	267
# define	DEFINE	268
# define	REPEAT	269
# define	GRADIENT	270
# define	COMPLEX	271
# define	SET_COLOR	272
# define	SET_COLOR_HSV	273
# define	EQUALS	274
# define	PLUS_EQUALS	275
# define	MINUS_EQUALS	276
# define	TIMES_EQUALS	277
# define	DIVIDE_EQUALS	278
# define	DOT	279
# define	TOKEN_TRUE	280
# define	TOKEN_FALSE	281
# define	TOKEN_NULL	282
# define	PLUS_PLUS	283
# define	MINUS_MINUS	284
# define	PRINT	285
# define	PRINTLN	286
# define	MAP_COLOR	287
# define	BREAK	288
# define	CONTINUE	289
# define	R_CIRCLE	290
# define	R_ELLIPSE	291
# define	R_RECT	292
# define	R_POLY	293
# define	R_SPOLY	294
# define	R_CROSS	295
# define	R_NOT	296
# define	R_AND	297
# define	R_OR	298
# define	R_XOR	299
# define	INSIDE	300
# define	TEXT_INTERSECT	301
# define	SWITCH	302
# define	CASE	303
# define	DEFAULT	304
# define	ATTRIBUTE_REAL	305
# define	ATTRIBUTE_IMAGINARY	306
# define	ATTRIBUTE_DEGREES	307
# define	ATTRIBUTE_OLD_DEGREES	308
# define	ATTRIBUTE_RADIANS	309
# define	ATTRIBUTE_OLD_RADIANS	310
# define	ATTRIBUTE_MAGNITUDE	311
# define	ATTRIBUTE_SUM_OF_SQUARES	312
# define	LT	313
# define	GT	314
# define	LE	315
# define	GE	316
# define	NE	317
# define	EQ	318
# define	OR	319
# define	AND	320
# define	IF	321
# define	ELSE	322
# define	ELSEIF	323
# define	UMINUS	324

#line 1 "fractal.yacc"


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


#line 201 "fractal.yacc"
#ifndef YYSTYPE
typedef union
{
   double dvalue;
   int ivalue;
   char *identifier;
   char *complexAttribute;
   char *literal;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		554
#define	YYFLAG		-32768
#define	YYNTBASE	89

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 324 ? yytranslate[x] : 193)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,     2,     2,    88,    76,     2,     2,
      82,    84,    74,    73,    83,    72,     2,    75,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    71,    87,
       2,     2,     2,    70,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,    81,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    79
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     7,    11,    14,    15,    35,    36,    42,
      44,    47,    48,    57,    58,    64,    66,    69,    70,    79,
      80,    81,    91,    93,    96,    98,   101,   107,   108,   110,
     114,   115,   116,   117,   118,   119,   120,   137,   139,   142,
     144,   146,   148,   150,   152,   154,   156,   159,   161,   163,
     165,   169,   173,   177,   181,   185,   189,   193,   197,   201,
     205,   208,   211,   214,   217,   222,   227,   232,   237,   242,
     246,   250,   254,   258,   260,   262,   264,   269,   278,   287,
     289,   291,   293,   294,   304,   308,   310,   312,   314,   316,
     321,   325,   327,   331,   333,   335,   337,   339,   341,   342,
     349,   350,   354,   355,   362,   364,   367,   370,   372,   374,
     377,   378,   380,   384,   385,   386,   387,   400,   401,   410,
     411,   413,   416,   418,   420,   423,   424,   425,   430,   433,
     435,   439,   440,   441,   446,   449,   453,   459,   461,   463,
     467,   471,   475,   479,   483,   487,   491,   495,   499,   501,
     504,   510,   514,   518,   522,   526,   530,   534,   538,   541,
     545,   547,   550,   555,   557,   562,   569,   578,   591,   593,
     595,   597,   599,   601,   603,   605,   607,   609,   611,   615,
     619,   623,   625,   629,   633,   637,   639,   643,   647,   651,
     653,   657,   661,   665,   667,   671,   675,   679,   681,   685,
     689,   693,   695,   699,   703,   707,   709,   713,   717,   719,
     721,   723,   725,   727,   730,   734,   739,   745,   747,   752,
     757,   764,   766,   768,   770,   772,   776,   780,   784,   788,
     791,   795,   797,   801,   803,   810,   819,   826,   827,   837,
     848,   859,   864,   871,   878,   885
};
static const short yyrhs[] =
{
      -1,     7,    90,    80,    91,    81,     0,    92,    94,   110,
       0,    92,   110,     0,     0,     8,    93,    80,    82,   188,
      83,   188,    83,   188,    83,   188,    84,     9,    82,   188,
      83,   188,    84,    81,     0,     0,    13,    80,    95,    96,
      81,     0,    97,     0,    96,    97,     0,     0,    14,    82,
       4,    84,    80,    98,   100,    81,     0,     0,    14,    80,
      99,   100,    81,     0,   101,     0,   100,   101,     0,     0,
      15,    82,     4,    84,    80,   102,   100,    81,     0,     0,
       0,    16,    82,     4,    84,    80,   103,   105,   104,    81,
       0,   107,     0,   107,   106,     0,   107,     0,   106,   107,
       0,    85,     4,     4,     4,    86,     0,     0,   117,     0,
      80,   108,    81,     0,     0,     0,     0,     0,     0,     0,
      10,    80,   111,   108,   112,    11,    82,   167,   113,    84,
     114,   109,   115,   108,   116,    81,     0,   119,     0,   117,
     119,     0,   120,     0,   121,     0,   122,     0,   126,     0,
     134,     0,   127,     0,   128,     0,   118,    87,     0,   147,
       0,   149,     0,   153,     0,     5,    20,   186,     0,     5,
      20,   169,     0,     5,    21,   186,     0,     5,    21,   169,
       0,     5,    22,   186,     0,     5,    22,   169,     0,     5,
      23,   186,     0,     5,    23,   169,     0,     5,    24,   186,
       0,     5,    24,   169,     0,     5,    29,     0,    29,     5,
       0,     5,    30,     0,    30,     5,     0,    88,     5,    20,
     169,     0,    88,     5,    21,   169,     0,    88,     5,    22,
     169,     0,    88,     5,    23,   169,     0,    88,     5,    24,
     169,     0,    88,     5,    29,     0,    29,    88,     5,     0,
      88,     5,    30,     0,    30,    88,     5,     0,   123,     0,
     124,     0,   125,     0,    18,    82,   169,    84,     0,    18,
      82,   169,    83,   169,    83,   169,    84,     0,    19,    82,
     169,    83,   169,    83,   169,    84,     0,    28,     0,    34,
       0,    35,     0,     0,    33,    82,   130,   132,    71,   131,
      71,   131,    84,     0,   131,    83,   132,     0,   132,     0,
     169,     0,    31,     0,    32,     0,   133,    82,   135,    84,
       0,   138,    83,   136,     0,   136,     0,   136,    25,   137,
       0,   137,     0,   169,     0,   186,     0,     6,     0,     6,
       0,     0,    67,    82,   167,    84,   140,   109,     0,     0,
      68,   142,   109,     0,     0,    69,    82,   167,    84,   144,
     109,     0,   139,     0,   139,   146,     0,   146,   143,     0,
     143,     0,   145,     0,   145,   141,     0,     0,   118,     0,
     148,    83,   118,     0,     0,     0,     0,    12,    82,   150,
     148,    87,   167,    87,   151,   148,    84,   152,   109,     0,
       0,    48,    82,   169,    84,   154,    80,   155,    81,     0,
       0,   156,     0,   156,   162,     0,   162,     0,   157,     0,
     156,   157,     0,     0,     0,   158,   160,   159,   166,     0,
     160,   161,     0,   161,     0,    49,   169,    71,     0,     0,
       0,   163,   165,   164,   166,     0,    50,    71,     0,    80,
     108,    81,     0,    80,   108,    81,    34,    87,     0,    26,
       0,    27,     0,   167,    66,   167,     0,   167,    65,   167,
       0,    82,   167,    84,     0,   169,    59,   169,     0,   169,
      61,   169,     0,   169,    60,   169,     0,   169,    62,   169,
       0,   169,    64,   169,     0,   169,    63,   169,     0,   192,
       0,    78,   167,     0,   167,    70,   169,    71,   169,     0,
      80,   168,    81,     0,   169,    73,   169,     0,   169,    72,
     169,     0,   169,    74,   169,     0,   169,    75,   169,     0,
     169,    76,   169,     0,   169,    77,   169,     0,    72,   169,
       0,    82,   169,    84,     0,   187,     0,    88,     5,     0,
     170,    82,   186,    84,     0,   129,     0,     5,    82,   169,
      84,     0,     5,    82,   169,    83,   169,    84,     0,     5,
      82,   169,    83,   169,    83,   169,    84,     0,    47,    82,
       6,    83,   186,    83,   169,    83,   169,    83,   186,    84,
       0,   168,     0,   121,     0,    51,     0,    52,     0,    53,
       0,    54,     0,    55,     0,    56,     0,    58,     0,    57,
       0,   186,    73,   169,     0,   169,    73,   186,     0,   186,
      73,   186,     0,   171,     0,   186,    72,   169,     0,   169,
      72,   186,     0,   186,    72,   186,     0,   173,     0,   186,
      74,   169,     0,   169,    74,   186,     0,   186,    74,   186,
       0,   175,     0,   186,    75,   169,     0,   169,    75,   186,
       0,   186,    75,   186,     0,   177,     0,   186,    77,   169,
       0,   169,    77,   186,     0,   186,    77,   186,     0,   179,
       0,   186,    83,   169,     0,   169,    83,   186,     0,   186,
      83,   186,     0,   181,     0,   186,    71,   169,     0,   169,
      71,   186,     0,   186,    71,   186,     0,   183,     0,   167,
      70,   184,     0,    80,   185,    81,     0,   172,     0,   174,
       0,   176,     0,   178,     0,   180,     0,    72,   186,     0,
      82,   186,    84,     0,    17,    82,   169,    84,     0,    85,
     169,    83,   169,    86,     0,     5,     0,     5,    82,   186,
      84,     0,     5,    82,   182,    84,     0,     5,    82,   182,
      83,   169,    84,     0,   185,     0,   120,     0,     3,     0,
       4,     0,   188,    73,   188,     0,   188,    72,   188,     0,
     188,    74,   188,     0,   188,    75,   188,     0,    72,   188,
       0,    82,   188,    84,     0,   187,     0,   189,    83,   186,
       0,   186,     0,    36,    82,   186,    83,   169,    84,     0,
      37,    82,   186,    83,   169,    83,   169,    84,     0,    38,
      82,   186,    83,   186,    84,     0,     0,    39,    82,   186,
      83,   186,    83,   191,   189,    84,     0,    40,    82,   186,
      83,   169,    83,   169,    83,   169,    84,     0,    41,    82,
     186,    83,   186,    83,   169,    83,   169,    84,     0,    42,
      82,   190,    84,     0,    43,    82,   190,    83,   190,    84,
       0,    44,    82,   190,    83,   190,    84,     0,    45,    82,
     190,    83,   190,    84,     0,    46,    82,   186,    83,   190,
      84,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   307,   307,   318,   318,   321,   321,   371,   371,   392,
     393,   396,   396,   415,   415,   436,   437,   440,   440,   459,
     459,   459,   484,   487,   490,   491,   494,   526,   527,   529,
     532,   532,   532,   532,   532,   532,   532,   581,   582,   585,
     592,   599,   600,   601,   602,   603,   606,   607,   608,   609,
     612,   630,   650,   660,   672,   682,   694,   704,   716,   726,
     738,   756,   774,   792,   812,   824,   834,   844,   854,   864,
     879,   894,   909,   926,   927,   928,   931,   941,   959,   977,
     985,  1005,  1024,  1024,  1059,  1060,  1063,  1071,  1075,  1081,
    1090,  1091,  1094,  1095,  1098,  1107,  1115,  1124,  1131,  1131,
    1144,  1144,  1154,  1154,  1166,  1167,  1170,  1171,  1174,  1201,
    1236,  1237,  1238,  1241,  1241,  1241,  1241,  1293,  1293,  1311,
    1312,  1313,  1314,  1317,  1318,  1321,  1321,  1321,  1340,  1341,
    1344,  1352,  1352,  1352,  1370,  1373,  1374,  1380,  1386,  1393,
    1412,  1430,  1434,  1452,  1470,  1488,  1506,  1524,  1542,  1543,
    1555,  1557,  1560,  1578,  1596,  1614,  1632,  1656,  1680,  1693,
    1697,  1703,  1728,  1761,  1765,  1828,  1864,  1903,  1929,  1940,
    1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,  1963,  1965,
    1969,  1970,  1973,  1975,  1979,  1980,  1983,  1985,  1989,  1990,
    1993,  1995,  1999,  2000,  2003,  2005,  2009,  2010,  2013,  2015,
    2019,  2020,  2023,  2025,  2029,  2030,  2033,  2034,  2037,  2055,
    2073,  2091,  2109,  2133,  2146,  2150,  2159,  2169,  2194,  2227,
    2263,  2302,  2313,  2327,  2331,  2337,  2341,  2345,  2349,  2353,
    2357,  2361,  2367,  2371,  2378,  2387,  2399,  2408,  2408,  2431,
    2443,  2456,  2464,  2473,  2482,  2493
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "REAL", "INTEGER", "IDENTIFIER", "LITERAL", 
  "FRACTAL", "MAPPING", "POINTTO", "FORMULA", "WHILE", "FOR", "COLORS", 
  "DEFINE", "REPEAT", "GRADIENT", "COMPLEX", "SET_COLOR", "SET_COLOR_HSV", 
  "EQUALS", "PLUS_EQUALS", "MINUS_EQUALS", "TIMES_EQUALS", 
  "DIVIDE_EQUALS", "DOT", "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_NULL", 
  "PLUS_PLUS", "MINUS_MINUS", "PRINT", "PRINTLN", "MAP_COLOR", "BREAK", 
  "CONTINUE", "R_CIRCLE", "R_ELLIPSE", "R_RECT", "R_POLY", "R_SPOLY", 
  "R_CROSS", "R_NOT", "R_AND", "R_OR", "R_XOR", "INSIDE", 
  "TEXT_INTERSECT", "SWITCH", "CASE", "DEFAULT", "ATTRIBUTE_REAL", 
  "ATTRIBUTE_IMAGINARY", "ATTRIBUTE_DEGREES", "ATTRIBUTE_OLD_DEGREES", 
  "ATTRIBUTE_RADIANS", "ATTRIBUTE_OLD_RADIANS", "ATTRIBUTE_MAGNITUDE", 
  "ATTRIBUTE_SUM_OF_SQUARES", "LT", "GT", "LE", "GE", "NE", "EQ", "OR", 
  "AND", "IF", "ELSE", "ELSEIF", "'?'", "':'", "'-'", "'+'", "'*'", "'/'", 
  "'%'", "'^'", "'!'", "UMINUS", "'{'", "'}'", "'('", "','", "')'", "'['", 
  "']'", "';'", "'$'", "begin", "@1", "sections", "mapping", "@2", 
  "colors", "@3", "entries", "entry", "@4", "@5", "color_entries", 
  "color_entry", "@6", "@7", "@8", "gradient", "single_color_entries", 
  "single_color_entry", "zero_or_more_statements", "statement_body", 
  "formula", "@9", "@10", "@11", "@12", "@13", "@14", "statements", 
  "simple_statement", "statement", "complex_assignment_statement", 
  "double_assignment_statement", "set_color_statement", 
  "indexed_set_color_statement", "rgb_set_color_statement", 
  "hsv_set_color_statement", "null_statement", "break_statement", 
  "continue_statement", "map_color", "@15", "map_color_args", 
  "map_color_arg", "print_function", "print_statement", 
  "print_statement_args", "print_args", "print_arg", "print_dest", 
  "if_statement", "@16", "else_statement", "@17", "elseif_statement", 
  "@18", "start_conditional_statement", "elseif_statements", 
  "conditional_statement", "for_statement_list", "for_statement", "@19", 
  "@20", "@21", "switch_statement", "@22", "switch_body", 
  "case_statements", "case_statement", "@23", "@24", "case_entries", 
  "case_entry", "default_statement", "@25", "@26", "default_entry", 
  "case_body", "boolean_expression", "double_ternary_expression", 
  "double_expression", "complex_attribute", "mixed_add_expression", 
  "complex_add_expression", "mixed_subtract_expression", 
  "complex_subtract_expression", "mixed_multiply_expression", 
  "complex_multiply_expression", "mixed_divide_expression", 
  "complex_divide_expression", "mixed_power_expression", 
  "complex_power_expression", "mixed_two_arg_expression", 
  "complex_two_arg_expression", "mixed_ternary_arguments", 
  "complex_ternary_arguments", "complex_ternary_expression", 
  "complex_expression", "number", "numeric_expression", 
  "more_r_poly_points", "region", "@27", "inside_boolean_expression", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    90,    89,    91,    91,    93,    92,    95,    94,    96,
      96,    98,    97,    99,    97,   100,   100,   102,   101,   103,
     104,   101,   101,   105,   106,   106,   107,   108,   108,   109,
     111,   112,   113,   114,   115,   116,   110,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   122,   123,   124,   125,   126,
     127,   128,   130,   129,   131,   131,   132,   133,   133,   134,
     135,   135,   136,   136,   137,   137,   137,   138,   140,   139,
     142,   141,   144,   143,   145,   145,   146,   146,   147,   147,
     148,   148,   148,   150,   151,   152,   149,   154,   153,   155,
     155,   155,   155,   156,   156,   158,   159,   157,   160,   160,
     161,   163,   164,   162,   165,   166,   166,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   171,   171,
     172,   172,   173,   173,   174,   174,   175,   175,   176,   176,
     177,   177,   178,   178,   179,   179,   180,   180,   181,   181,
     182,   182,   183,   183,   184,   184,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   187,   187,   188,   188,   188,   188,   188,
     188,   188,   189,   189,   190,   190,   190,   191,   190,   190,
     190,   190,   190,   190,   190,   192
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     5,     3,     2,     0,    19,     0,     5,     1,
       2,     0,     8,     0,     5,     1,     2,     0,     8,     0,
       0,     9,     1,     2,     1,     2,     5,     0,     1,     3,
       0,     0,     0,     0,     0,     0,    16,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     1,     1,     1,     4,     8,     8,     1,
       1,     1,     0,     9,     3,     1,     1,     1,     1,     4,
       3,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     3,     0,     6,     1,     2,     2,     1,     1,     2,
       0,     1,     3,     0,     0,     0,    12,     0,     8,     0,
       1,     2,     1,     1,     2,     0,     0,     4,     2,     1,
       3,     0,     0,     4,     2,     3,     5,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       5,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     2,     4,     1,     4,     6,     8,    12,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     2,     3,     4,     5,     1,     4,     4,
       6,     1,     1,     1,     1,     3,     3,     3,     3,     2,
       3,     1,     3,     1,     6,     8,     6,     0,     9,    10,
      10,     4,     6,     6,     6,     6
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     1,     0,     0,     5,     0,     0,     0,     2,     0,
       0,     0,     4,     0,    30,     7,     3,     0,    27,     0,
     223,   224,     0,     0,   231,     0,     0,     0,     0,     0,
      79,     0,     0,    87,    88,    80,    81,     0,     0,     0,
      31,    28,     0,    37,    39,    40,    41,    73,    74,    75,
      42,    44,    45,     0,    43,   104,   108,    47,    48,    49,
       0,     0,     9,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    62,   113,     0,     0,
      61,     0,    63,     0,     0,     0,     0,     0,    38,    46,
       0,     0,   107,   105,   100,   109,    13,     0,     8,    10,
     230,   226,   225,   227,   228,     0,   217,     0,   137,   138,
       0,     0,     0,   170,   171,   172,   173,   174,   175,   177,
     176,     0,     0,     0,     0,     0,     0,   222,   169,   163,
       0,   168,    51,     0,   181,   208,   185,   209,   189,   210,
     193,   211,   197,   212,   221,    50,   160,   148,    53,    52,
      55,    54,    57,    56,    59,    58,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,    72,     0,     0,
       0,     0,     0,     0,     0,     0,    69,    71,     0,    96,
       0,    91,    93,     0,    94,    95,     0,   106,     0,     0,
       0,     0,     0,     0,    82,     0,     0,   158,   213,   149,
     168,     0,     0,     0,     0,     0,   161,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,   117,    98,    64,    65,    66,    67,    68,
       0,    89,     0,     0,     0,    27,   101,     0,     0,     0,
       0,    15,    22,     0,     0,     0,   201,     0,     0,     0,
       0,     0,     0,     0,   151,   207,   141,   159,   214,     0,
     140,   139,     0,   205,   206,     0,   142,   144,   143,   145,
     147,   146,   153,   183,   152,   179,   154,   187,   155,   191,
     156,   157,   195,     0,   182,   184,   178,   180,   186,   188,
     190,   192,   194,   196,     0,     0,     0,     0,   153,   152,
     154,   155,   157,     0,     0,     0,     0,    32,    96,    92,
      90,   102,     0,     0,     0,     0,    14,    16,    11,     0,
       0,   164,     0,   219,     0,   218,   215,     0,    86,     0,
       0,     0,     0,     0,   162,   112,     0,     0,     0,     0,
       0,   119,    99,     0,     0,    29,     0,     0,     0,     0,
       0,     0,   199,     0,   198,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
     150,   203,   202,   204,   114,     0,   150,     0,     0,     0,
     120,   123,     0,   122,     0,    33,   103,     0,     0,     0,
       0,     0,     0,   165,   220,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   245,     0,   110,
      77,    78,   118,   124,   121,     0,   126,   129,     0,   132,
       0,    17,    19,    26,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   134,     0,    34,     0,     0,     0,
     166,     0,    84,     0,     0,     0,     0,     0,     0,   241,
       0,     0,     0,     0,   115,   130,    27,   127,   133,    27,
       0,    20,     0,     0,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    18,     0,
      23,    24,     0,   234,     0,   236,   237,     0,     0,   242,
     243,   244,     0,   116,   135,     0,    21,    25,     0,     0,
       0,     0,     0,     0,     0,    36,     0,   235,   233,     0,
       0,     0,   167,   136,     6,     0,   238,     0,     0,   232,
     239,   240,     0,     0,     0
};

static const short yydefgoto[] =
{
     552,     2,     5,     6,     7,    11,    19,    61,    62,   369,
     189,   260,   261,   467,   468,   509,   491,   510,   262,    40,
     256,    12,    18,    87,   363,   440,   489,   525,    41,    42,
      43,   127,   128,    46,    47,    48,    49,    50,    51,    52,
     129,   270,   415,   416,    53,    54,   180,   181,   182,   183,
      55,   326,    95,   188,    92,   364,    56,    93,    57,   229,
      58,   156,   429,   505,    59,   325,   399,   400,   401,   402,
     462,   436,   437,   403,   404,   465,   439,   487,   163,   131,
     271,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   266,   267,   283,   284,   144,   185,   146,    25,
     539,   387,   530,   147
};

static const short yypact[] =
{
      28,-32768,   -52,    37,-32768,   -13,    76,   -21,-32768,    -8,
       8,    84,-32768,    23,-32768,-32768,-32768,    34,   484,   116,
  -32768,-32768,    34,    34,-32768,   464,   733,    26,    43,    51,
  -32768,    13,    14,-32768,-32768,-32768,-32768,    60,    63,   142,
  -32768,   484,    65,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,    75,-32768,   104,   107,-32768,-32768,-32768,
     -22,     9,-32768,-32768,   245,    34,    34,    34,    34,    34,
     713,   713,   713,   713,   713,-32768,-32768,-32768,    66,    66,
  -32768,   184,-32768,   191,    66,    66,   852,   194,-32768,-32768,
     258,   128,-32768,   104,-32768,-32768,-32768,   208,-32768,-32768,
  -32768,    81,    81,-32768,-32768,   752,   161,   137,-32768,-32768,
     151,   155,   160,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   713,    66,   321,   713,    66,   239,-32768,-32768,-32768,
      44,-32768,  1419,   163,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   788,-32768,-32768,  1419,   788,
    1419,   788,  1419,   788,  1419,   788,    12,   170,   178,   186,
      66,    66,    66,   143,   794,  1125,-32768,-32768,   933,   141,
    1438,    66,    66,    66,    66,    66,-32768,-32768,   174,   189,
     192,   253,-32768,   198,  1419,   788,    66,-32768,   203,    18,
     209,    34,   713,    66,-32768,   713,   290,-32768,-32768,-32768,
     216,   225,   150,   939,   260,  1150,   852,    66,    66,   713,
      66,    66,    66,    66,    66,    66,   713,   713,   713,   713,
      66,   713,   713,   713,   713,   713,   713,   713,-32768,    49,
      66,-32768,   181,   965,    66,    66,    66,    66,    66,    66,
      66,-32768,    66,-32768,-32768,  1438,  1438,  1438,  1438,  1438,
      66,-32768,   611,   611,   183,   484,-32768,   241,   246,   303,
       6,-32768,-32768,   228,   756,   829,-32768,    94,   196,   971,
      66,  1419,   491,   238,-32768,-32768,-32768,-32768,-32768,    66,
     265,-32768,  1375,-32768,-32768,   715,  1438,  1438,  1438,  1438,
    1438,  1438,   226,   330,   226,   330,   111,   262,   111,   262,
     264,   275,   262,   308,   446,   330,   446,   330,    21,   262,
      21,   262,    21,   262,    12,    66,   855,  1394,   354,   354,
     122,   122,   264,  1175,  1200,   273,   203,   143,-32768,-32768,
     253,-32768,   261,   352,   361,   362,-32768,-32768,-32768,    34,
     713,-32768,    66,-32768,   713,-32768,-32768,   298,  1438,  1480,
     713,   746,   713,   713,-32768,-32768,   106,    66,    66,    66,
      66,   168,-32768,   286,   203,-32768,   287,   300,   386,    18,
     322,   881,   788,   997,  1419,   788,    66,   318,   320,   326,
     328,   329,   333,   334,   337,   339,   356,   365,   552,-32768,
    1419,   788,  1419,   788,-32768,   907,  1438,  1003,  1029,   331,
     168,-32768,   387,-32768,   395,-32768,-32768,   366,   370,   372,
      46,   442,    66,-32768,-32768,   -47,-32768,   713,   713,   713,
     713,   713,   713,  1480,  1480,  1480,  1480,-32768,    66,    12,
  -32768,-32768,-32768,-32768,-32768,    66,   387,-32768,   384,-32768,
     203,-32768,-32768,-32768,-32768,   374,  1035,    66,    66,   559,
     577,   598,   605,   629,   661,   376,   378,   379,   380,  1225,
     152,  1413,   389,-32768,-32768,   389,-32768,    18,   390,    34,
  -32768,   171,-32768,    66,    66,   713,   713,    66,   713,-32768,
    1480,  1480,  1480,    66,-32768,-32768,   484,-32768,-32768,   484,
      58,-32768,   390,   776,-32768,  1061,  1250,   314,   675,  1275,
     700,   392,   394,   398,  1300,   203,   403,-32768,-32768,   404,
     390,-32768,    34,-32768,    66,-32768,-32768,    66,    66,-32768,
  -32768,-32768,   713,-32768,   445,   405,-32768,-32768,   393,  1067,
     713,  1325,  1350,   360,   401,-32768,   416,-32768,   788,   206,
      66,    66,-32768,-32768,-32768,   713,-32768,  1093,  1099,   788,
  -32768,-32768,   498,   499,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   440,-32768,
  -32768,  -360,  -240,-32768,-32768,-32768,-32768,-32768,  -357,  -248,
    -325,   493,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -152,
     470,   -16,   -15,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    70,  -262,-32768,-32768,-32768,   271,   274,-32768,
  -32768,-32768,-32768,-32768,   432,-32768,-32768,-32768,-32768,    99,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   133,-32768,
  -32768,-32768,    98,   145,-32768,-32768,-32768,    83,   -58,   -94,
     369,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   423,     5,   -17,   -12,
  -32768,  -222,-32768,-32768
};


#define	YYLAST		1525


static const short yytable[] =
{
      24,   362,    44,    45,   228,    24,    24,   332,   347,   410,
      63,    64,   130,   130,   130,   130,   130,    26,    80,    82,
     337,   257,   258,    60,   447,    44,    45,   169,     3,   200,
      28,    29,   130,   257,   258,     1,   448,    20,    21,   406,
      30,    31,    32,    33,    34,     4,    35,    36,    24,    24,
      24,    24,    24,   101,   102,   103,   104,   105,    96,    13,
      97,   257,   258,   130,   199,   130,   202,   200,     8,    20,
      21,   157,    14,   257,   258,   145,   149,   151,   153,   155,
     210,   211,   212,   213,   214,   215,     9,   336,    15,    10,
      98,   259,   108,   109,     9,   158,   159,   220,   221,   110,
      39,    81,    83,   259,   232,    17,    22,   490,    77,   207,
     208,   492,   111,   112,   209,   466,    23,   113,   114,   115,
     116,   117,   118,   119,   120,    78,   198,   444,   254,   204,
      60,   259,   314,    79,   130,   511,   315,   130,   160,   508,
      44,    45,    84,   259,   122,    85,   161,    86,   162,   280,
     281,   130,    89,   527,   126,    67,    68,    90,   130,   130,
     130,   130,   355,   130,   130,   130,   130,   130,   130,   130,
     337,   207,   208,    91,    24,    94,   234,   342,   343,   264,
     523,    70,    71,    72,    73,    74,   472,   220,   221,   166,
      75,    76,   327,   394,   130,   130,   167,   268,   220,   239,
     272,   455,   456,   457,   458,   178,   207,   208,   207,   208,
     186,   234,   190,   234,   285,   207,   208,  -125,  -131,   193,
     209,   293,   295,   297,   299,   244,   302,   303,   305,   307,
     309,   311,   313,   194,   276,   314,   484,   195,   506,    44,
      45,   507,   196,   192,   206,   222,   207,   208,   207,   208,
     337,   234,   230,   234,   448,   494,   250,   356,   501,   502,
     503,    20,    21,   106,   179,   276,    81,   331,   223,   224,
     225,   226,   -97,   227,    83,   107,   251,   228,   252,   344,
     345,   253,   130,   255,   108,   109,   130,    31,    32,   545,
     546,   110,   130,   263,   130,   130,   273,   274,    44,    45,
     218,   219,   220,   221,   111,   112,   275,   335,   338,   113,
     114,   115,   116,   117,   118,   119,   120,    65,    66,    67,
      68,   350,    24,   333,    20,    21,   157,   370,   334,   100,
     121,   208,   223,   224,   225,   226,   122,   227,   123,   227,
     124,   239,   365,   125,   278,   372,   126,   108,   109,   375,
     158,   159,   221,   361,   110,   388,   366,   391,   393,   130,
     130,   130,   130,   130,   130,   367,   368,   111,   112,   376,
     405,   407,   113,   114,   115,   116,   117,   118,   119,   120,
     223,   224,   225,   226,   408,   227,   223,   224,   225,   226,
     409,   227,   354,   160,    65,    66,    67,    68,   515,   122,
     417,   123,   418,   162,   225,   226,   411,   227,   419,   126,
     420,   421,   432,    44,    45,   422,   423,   130,   130,   424,
     130,   425,   449,   450,   451,   452,   453,   454,   237,   238,
     220,   239,   223,   224,   225,   226,   435,   227,   426,   132,
     148,   150,   152,   154,   542,   438,   441,   164,   165,   427,
     442,   445,    24,   168,   170,   464,   469,   493,   443,   184,
     479,   480,   481,   482,   130,    65,    66,    67,    68,   486,
      44,    45,   130,    44,    45,   259,   519,   536,   520,   534,
     497,   498,   521,   500,   524,   526,   535,   130,   543,    26,
     197,   170,   170,   203,   205,    24,    27,   544,   553,   554,
     528,    99,    28,    29,    16,   210,   211,   212,   213,   214,
     215,    88,    30,    31,    32,    33,    34,   471,    35,    36,
     218,   219,   220,   221,   330,   187,   329,   533,   460,   231,
     170,   233,    37,   433,   463,   538,    65,    66,    67,    68,
     245,   246,   247,   248,   249,   434,   201,    69,   488,     0,
     549,    38,     0,     0,     0,   170,     0,     0,     0,     0,
       0,   265,   269,   223,   224,   225,   226,     0,   227,     0,
       0,     0,    39,     0,   349,     0,   170,   170,   282,   286,
     287,   288,   289,   290,   291,   292,   294,   296,   298,   300,
     301,     0,   304,   306,   308,   310,   312,     0,     0,   316,
       0,     0,     0,   317,   318,   319,   320,   321,   322,   323,
       0,   324,     0,     0,    20,    21,   106,   328,     0,   170,
       0,   184,   184,     0,   223,   224,   225,   226,   107,   227,
       0,   223,   224,   225,   226,   428,   227,   108,   109,   348,
      31,    32,   473,     0,   110,     0,     0,     0,   351,   223,
     224,   225,   226,     0,   227,     0,     0,   111,   112,     0,
     474,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     223,   224,   225,   226,     0,   227,     0,   223,   224,   225,
     226,   475,   227,   121,   170,     0,     0,     0,   476,   122,
       0,   123,     0,   124,     0,     0,   125,     0,     0,   126,
       0,   223,   224,   225,   226,     0,   227,     0,     0,   371,
       0,   373,   477,   374,     0,     0,    20,    21,   106,     0,
       0,   390,   392,     0,     0,     0,   395,   396,   397,   398,
     107,     0,     0,   223,   224,   225,   226,     0,   227,   108,
     109,     0,    31,    32,   478,   348,   110,   223,   224,   225,
     226,     0,   227,    70,    71,    72,    73,    74,   516,   111,
     112,     0,    75,    76,   113,   114,   115,   116,   117,   118,
     119,   120,   223,   224,   225,   226,     0,   227,     0,     0,
       0,   446,     0,   518,     0,   121,   353,   223,   224,   225,
     226,   122,   227,   123,     0,   124,     0,   459,   125,     0,
       0,   126,     0,     0,   461,   210,   211,   212,   213,   214,
     215,     0,     0,     0,     0,     0,   348,   348,   235,   236,
     237,   238,   220,   239,    65,    66,    67,    68,    65,    66,
      67,    68,   389,     0,     0,   191,     0,     0,     0,   339,
       0,     0,   495,   496,     0,     0,   499,     0,    65,    66,
      67,    68,   504,   210,   211,   212,   213,   214,   215,   512,
     223,   224,   225,   226,     0,   227,   235,   236,   237,   238,
     220,   239,   171,   172,   173,   174,   175,   240,   241,     0,
       0,   176,   177,   529,     0,     0,   531,   532,   210,   211,
     212,   213,   214,   215,     0,     0,     0,     0,     0,     0,
       0,   216,   217,   218,   219,   220,   221,     0,     0,   547,
     548,     0,   340,   341,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   357,   341,
     210,   211,   212,   213,   214,   215,     0,     0,     0,     0,
       0,     0,     0,   216,   217,   218,   219,   220,   221,     0,
       0,     0,     0,     0,   412,   413,   210,   211,   212,   213,
     214,   215,     0,     0,     0,     0,     0,     0,     0,   235,
     236,   237,   238,   220,   239,     0,     0,     0,     0,     0,
     412,   413,   210,   211,   212,   213,   214,   215,   210,   211,
     212,   213,   214,   215,     0,   235,   236,   237,   238,   220,
     239,   216,   217,   218,   219,   220,   221,   243,     0,     0,
       0,     0,     0,   277,   210,   211,   212,   213,   214,   215,
     210,   211,   212,   213,   214,   215,     0,   235,   236,   237,
     238,   220,   239,   235,   236,   237,   238,   220,   239,   277,
       0,     0,     0,     0,     0,   346,   210,   211,   212,   213,
     214,   215,   210,   211,   212,   213,   214,   215,     0,   235,
     236,   237,   238,   220,   239,   235,   236,   237,   238,   220,
     239,   414,     0,     0,     0,     0,     0,   430,   210,   211,
     212,   213,   214,   215,   210,   211,   212,   213,   214,   215,
       0,   235,   236,   237,   238,   220,   239,   235,   236,   237,
     238,   220,   239,   431,     0,     0,     0,     0,     0,   470,
     210,   211,   212,   213,   214,   215,   210,   211,   212,   213,
     214,   215,     0,   235,   236,   237,   238,   220,   239,   235,
     236,   237,   238,   220,   239,   513,     0,     0,     0,     0,
       0,   537,   210,   211,   212,   213,   214,   215,   210,   211,
     212,   213,   214,   215,     0,   235,   236,   237,   238,   220,
     239,   235,   236,   237,   238,   220,   239,   550,     0,     0,
       0,     0,     0,   551,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   242,   210,
     211,   212,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   235,   236,   237,   238,   220,   239,     0,     0,
       0,     0,     0,   279,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   359,   210,
     211,   212,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   235,   236,   237,   238,   220,   239,     0,     0,
       0,     0,     0,   360,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   483,   210,
     211,   212,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   235,   236,   237,   238,   220,   239,     0,     0,
       0,     0,     0,   514,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   517,   210,
     211,   212,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   235,   236,   237,   238,   220,   239,     0,     0,
       0,     0,     0,   522,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,     0,   235,   236,   237,
     238,   220,   239,     0,     0,     0,     0,     0,   540,   210,
     211,   212,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   235,   236,   237,   238,   220,   239,     0,     0,
       0,     0,     0,   541,   210,   211,   212,   213,   214,   215,
       0,     0,     0,     0,     0,     0,   352,   216,   217,   218,
     219,   220,   221,   210,   211,   212,   213,   214,   215,     0,
       0,     0,     0,     0,     0,   358,   235,   236,   237,   238,
     220,   239,   210,   211,   212,   213,   214,   215,   210,   211,
     212,   213,   214,   215,   485,   235,   236,   237,   238,   220,
     239,   216,   217,   218,   219,   220,   221,   210,   211,   212,
     213,   214,   215,     0,     0,     0,     0,     0,     0,     0,
     235,   236,   237,   238,   220,   239,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386
};

static const short yycheck[] =
{
      17,   326,    18,    18,   156,    22,    23,   255,   270,   369,
      22,    23,    70,    71,    72,    73,    74,     5,     5,     5,
     260,    15,    16,    14,    71,    41,    41,    85,    80,   123,
      18,    19,    90,    15,    16,     7,    83,     3,     4,   364,
      28,    29,    30,    31,    32,     8,    34,    35,    65,    66,
      67,    68,    69,    65,    66,    67,    68,    69,    80,    80,
      82,    15,    16,   121,   122,   123,   124,   161,    81,     3,
       4,     5,    80,    15,    16,    70,    71,    72,    73,    74,
      59,    60,    61,    62,    63,    64,    10,    81,    80,    13,
      81,    85,    26,    27,    10,    29,    30,    76,    77,    33,
      88,    88,    88,    85,   162,    82,    72,   467,    82,    65,
      66,   468,    46,    47,    70,   440,    82,    51,    52,    53,
      54,    55,    56,    57,    58,    82,   121,    81,   186,   124,
      14,    85,    83,    82,   192,   492,    87,   195,    72,    81,
     156,   156,    82,    85,    78,    82,    80,     5,    82,   207,
     208,   209,    87,   510,    88,    74,    75,    82,   216,   217,
     218,   219,   314,   221,   222,   223,   224,   225,   226,   227,
     410,    65,    66,    69,   191,    68,    70,    83,    84,   191,
     505,    20,    21,    22,    23,    24,   448,    76,    77,     5,
      29,    30,   250,    87,   252,   253,     5,   192,    76,    77,
     195,   423,   424,   425,   426,    11,    65,    66,    65,    66,
      82,    70,     4,    70,   209,    65,    66,    49,    50,    82,
      70,   216,   217,   218,   219,    84,   221,   222,   223,   224,
     225,   226,   227,    82,    84,    83,    84,    82,   486,   255,
     255,   489,    82,    82,     5,    82,    65,    66,    65,    66,
     490,    70,    82,    70,    83,    84,    82,   315,   480,   481,
     482,     3,     4,     5,     6,    84,    88,    84,    72,    73,
      74,    75,    83,    77,    88,    17,    84,   429,    25,    83,
      84,    83,   340,    80,    26,    27,   344,    29,    30,    83,
      84,    33,   350,    84,   352,   353,     6,    81,   314,   314,
      74,    75,    76,    77,    46,    47,    81,     4,    80,    51,
      52,    53,    54,    55,    56,    57,    58,    72,    73,    74,
      75,    83,   339,    82,     3,     4,     5,   339,    82,    84,
      72,    66,    72,    73,    74,    75,    78,    77,    80,    77,
      82,    77,    81,    85,    84,   340,    88,    26,    27,   344,
      29,    30,    77,    80,    33,   350,     4,   352,   353,   417,
     418,   419,   420,   421,   422,     4,     4,    46,    47,    71,
      84,    84,    51,    52,    53,    54,    55,    56,    57,    58,
      72,    73,    74,    75,    84,    77,    72,    73,    74,    75,
       4,    77,    84,    72,    72,    73,    74,    75,    84,    78,
      82,    80,    82,    82,    74,    75,    84,    77,    82,    88,
      82,    82,    81,   429,   429,    82,    82,   475,   476,    82,
     478,    82,   417,   418,   419,   420,   421,   422,    74,    75,
      76,    77,    72,    73,    74,    75,    49,    77,    82,    70,
      71,    72,    73,    74,    84,    50,    80,    78,    79,    84,
      80,     9,   469,    84,    85,    71,    82,   469,    86,    90,
      84,    83,    83,    83,   522,    72,    73,    74,    75,    80,
     486,   486,   530,   489,   489,    85,    84,    84,    84,    34,
     475,   476,    84,   478,    81,    81,    81,   545,    87,     5,
     121,   122,   123,   124,   125,   512,    12,    81,     0,     0,
     512,    61,    18,    19,    11,    59,    60,    61,    62,    63,
      64,    41,    28,    29,    30,    31,    32,   447,    34,    35,
      74,    75,    76,    77,   253,    93,   252,   522,   429,   160,
     161,   162,    48,   400,   436,   530,    72,    73,    74,    75,
     171,   172,   173,   174,   175,   400,   123,    83,   465,    -1,
     545,    67,    -1,    -1,    -1,   186,    -1,    -1,    -1,    -1,
      -1,   192,   193,    72,    73,    74,    75,    -1,    77,    -1,
      -1,    -1,    88,    -1,    83,    -1,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,    -1,   223,   224,   225,   226,   227,    -1,    -1,   230,
      -1,    -1,    -1,   234,   235,   236,   237,   238,   239,   240,
      -1,   242,    -1,    -1,     3,     4,     5,     6,    -1,   250,
      -1,   252,   253,    -1,    72,    73,    74,    75,    17,    77,
      -1,    72,    73,    74,    75,    83,    77,    26,    27,   270,
      29,    30,    83,    -1,    33,    -1,    -1,    -1,   279,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    46,    47,    -1,
      83,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      72,    73,    74,    75,    -1,    77,    -1,    72,    73,    74,
      75,    83,    77,    72,   315,    -1,    -1,    -1,    83,    78,
      -1,    80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,
      -1,    72,    73,    74,    75,    -1,    77,    -1,    -1,   340,
      -1,   342,    83,   344,    -1,    -1,     3,     4,     5,    -1,
      -1,   352,   353,    -1,    -1,    -1,   357,   358,   359,   360,
      17,    -1,    -1,    72,    73,    74,    75,    -1,    77,    26,
      27,    -1,    29,    30,    83,   376,    33,    72,    73,    74,
      75,    -1,    77,    20,    21,    22,    23,    24,    83,    46,
      47,    -1,    29,    30,    51,    52,    53,    54,    55,    56,
      57,    58,    72,    73,    74,    75,    -1,    77,    -1,    -1,
      -1,   412,    -1,    83,    -1,    72,    71,    72,    73,    74,
      75,    78,    77,    80,    -1,    82,    -1,   428,    85,    -1,
      -1,    88,    -1,    -1,   435,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,   447,   448,    72,    73,
      74,    75,    76,    77,    72,    73,    74,    75,    72,    73,
      74,    75,    86,    -1,    -1,    83,    -1,    -1,    -1,    83,
      -1,    -1,   473,   474,    -1,    -1,   477,    -1,    72,    73,
      74,    75,   483,    59,    60,    61,    62,    63,    64,    83,
      72,    73,    74,    75,    -1,    77,    72,    73,    74,    75,
      76,    77,    20,    21,    22,    23,    24,    83,    84,    -1,
      -1,    29,    30,   514,    -1,    -1,   517,   518,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    -1,    -1,   540,
     541,    -1,    83,    84,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    84,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    83,    84,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      83,    84,    59,    60,    61,    62,    63,    64,    59,    60,
      61,    62,    63,    64,    -1,    72,    73,    74,    75,    76,
      77,    72,    73,    74,    75,    76,    77,    84,    -1,    -1,
      -1,    -1,    -1,    84,    59,    60,    61,    62,    63,    64,
      59,    60,    61,    62,    63,    64,    -1,    72,    73,    74,
      75,    76,    77,    72,    73,    74,    75,    76,    77,    84,
      -1,    -1,    -1,    -1,    -1,    84,    59,    60,    61,    62,
      63,    64,    59,    60,    61,    62,    63,    64,    -1,    72,
      73,    74,    75,    76,    77,    72,    73,    74,    75,    76,
      77,    84,    -1,    -1,    -1,    -1,    -1,    84,    59,    60,
      61,    62,    63,    64,    59,    60,    61,    62,    63,    64,
      -1,    72,    73,    74,    75,    76,    77,    72,    73,    74,
      75,    76,    77,    84,    -1,    -1,    -1,    -1,    -1,    84,
      59,    60,    61,    62,    63,    64,    59,    60,    61,    62,
      63,    64,    -1,    72,    73,    74,    75,    76,    77,    72,
      73,    74,    75,    76,    77,    84,    -1,    -1,    -1,    -1,
      -1,    84,    59,    60,    61,    62,    63,    64,    59,    60,
      61,    62,    63,    64,    -1,    72,    73,    74,    75,    76,
      77,    72,    73,    74,    75,    76,    77,    84,    -1,    -1,
      -1,    -1,    -1,    84,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    59,    60,    61,    62,    63,    64,    59,    60,
      61,    62,    63,    64,    71,    72,    73,    74,    75,    76,
      77,    72,    73,    74,    75,    76,    77,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 308 "fractal.yacc"
{
          // Create our fractal object

          DNEW(ENV(fractalPtr), Fractal());
       ;
    break;}
case 5:
#line 322 "fractal.yacc"
{
            ENV(mappingSectionStartOffset) =
            FractalLexer::getInstance()->getFileOffset();
          ;
    break;}
case 6:
#line 338 "fractal.yacc"
{
            ENV(mappingSectionEndOffset) =
            FractalLexer::getInstance()->getFileOffset();

            // Set our complex coordinates and our dimension values

            ENV(fractalPtr)->setComplexCoordinates(
               yyvsp[-14].dvalue, yyvsp[-12].dvalue, yyvsp[-10].dvalue, yyvsp[-8].dvalue
            );

            // Ensure both the height and width are > 0 (after rounding
            // them to the nearest integer)

            {
               int width  = (int)(yyvsp[-4].dvalue < 0.0 ? yyvsp[-4].dvalue - 0.5 : yyvsp[-4].dvalue + 0.5);
               int height = (int)(yyvsp[-2].dvalue < 0.0 ? yyvsp[-2].dvalue - 0.5 : yyvsp[-2].dvalue + 0.5);

               if(width <= 0 || height <= 0)
               {
                  ostringstream temp;

                  temp << "Width and height must be > 0: ["
                     << yyvsp[-4].dvalue << ", " << yyvsp[-2].dvalue << "]";

                  handleError(temp.str().c_str(), voidPointer);
                  return(-1);
               }

               ENV(fractalPtr)->setDimensions(width, height);
            }
         ;
    break;}
case 7:
#line 373 "fractal.yacc"
{ ENV(theCounter).beginCount(); ;
    break;}
case 8:
#line 376 "fractal.yacc"
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
         ;
    break;}
case 11:
#line 398 "fractal.yacc"
{ ENV(theCounter).beginCount(); ;
    break;}
case 12:
#line 401 "fractal.yacc"
{
         DefineColorNode *d = 0;

         DNEW(
            d,
            DefineColorNode(
               yyvsp[-5].ivalue, ENV(colorNodeStack), ENV(theCounter).endCount()
            )
         );

         ENV(colorNodeStack).push(d);

         ENV(theCounter).increment();
      ;
    break;}
case 13:
#line 417 "fractal.yacc"
{ ENV(theCounter).beginCount(); ;
    break;}
case 14:
#line 420 "fractal.yacc"
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
      ;
    break;}
case 17:
#line 442 "fractal.yacc"
{ ENV(theCounter).beginCount(); ;
    break;}
case 18:
#line 445 "fractal.yacc"
{
               RepeatColorNode *r = 0;

               DNEW(
                  r,
                  RepeatColorNode(
                     yyvsp[-5].ivalue, ENV(colorNodeStack), ENV(theCounter).endCount()
                  )
               );

               ENV(colorNodeStack).push(r);

               ENV(theCounter).increment();
            ;
    break;}
case 19:
#line 461 "fractal.yacc"
{ ENV(insideGradient) = 1; ENV(theCounter).beginCount(); ;
    break;}
case 20:
#line 463 "fractal.yacc"
{ ENV(insideGradient) = 0; ;
    break;}
case 21:
#line 465 "fractal.yacc"
{
               string errMsg;

               GradientColorNode *nodePtr =
                  GradientColorNode::create(
                     yyvsp[-6].ivalue, ENV(colorStack), ENV(theCounter).endCount(), errMsg
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
            ;
    break;}
case 26:
#line 495 "fractal.yacc"
{
                        if(ENV(insideGradient))
                        {
                           int *values = 0;

                           DNEW(values, int[3]);

                           values[0]   = yyvsp[-3].ivalue;
                           values[1]   = yyvsp[-2].ivalue;
                           values[2]   = yyvsp[-1].ivalue;

                           ENV(colorStack).push(values);
                        }
                        else
                        {
                           SingleColorColorNode *s = 0;

                           DNEW(
                              s,
                              SingleColorColorNode(
                                 yyvsp[-3].ivalue, yyvsp[-2].ivalue, yyvsp[-1].ivalue
                              )
                           );

                           ENV(colorNodeStack).push(s);
                        }

                        ENV(theCounter).increment();
                     ;
    break;}
case 30:
#line 534 "fractal.yacc"
{
               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
               ENV(breakContinueAllowed).push(FALSE);
            ;
    break;}
case 31:
#line 543 "fractal.yacc"
{
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setBeforeStatement(ptr);
            ;
    break;}
case 32:
#line 551 "fractal.yacc"
{
               ENV(fractalPtr)->setCondition(ENV(booleanNodeStack).pop());
            ;
    break;}
case 33:
#line 555 "fractal.yacc"
{
               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
               ENV(breakContinueAllowed).push(TRUE);
            ;
    break;}
case 34:
#line 562 "fractal.yacc"
{
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setStatement(ptr);
               ENV(breakContinueAllowed).pop();

               CompoundStatement *c = 0;
               DNEW(c, CompoundStatement());
               ENV(compoundStack).push(c);
            ;
    break;}
case 35:
#line 573 "fractal.yacc"
{
               const CompoundStatement *ptr = ENV(compoundStack).pop();
               ENV(fractalPtr)->setAfterStatement(ptr);
               ENV(breakContinueAllowed).pop();
            ;
    break;}
case 39:
#line 586 "fractal.yacc"
{
                     const Statement *s        = ENV(currentComplexAssign);
                     ENV(currentComplexAssign) = NULL;

                     ENV(compoundStack).top()->add(s);
                  ;
    break;}
case 40:
#line 593 "fractal.yacc"
{
                     const Statement *s       = ENV(currentDoubleAssign);
                     ENV(currentDoubleAssign) = NULL;

                     ENV(compoundStack).top()->add(s);
                  ;
    break;}
case 50:
#line 613 "fractal.yacc"
{
      dcomplex *ptr =
         ENV(fractalPtr)->getComplexVariables().assign(yyvsp[-2].identifier);

      ComplexAssignmentStatement *statement = 0;

      DNEW(
         statement,
         ComplexAssignmentStatement(
            ptr, yyvsp[-2].identifier, ENV(complexNodeStack).pop()
         )
      );

      ENV(currentComplexAssign) = statement;

      free(yyvsp[-2].identifier);
   ;
    break;}
case 51:
#line 631 "fractal.yacc"
{
      doubleToComplex(voidPointer);

      dcomplex *ptr =
         ENV(fractalPtr)->getComplexVariables().assign(yyvsp[-2].identifier);

      ComplexAssignmentStatement *statement = 0;

      DNEW(
         statement,
         ComplexAssignmentStatement(
            ptr, yyvsp[-2].identifier, ENV(complexNodeStack).top()
         )
      );

      ENV(currentComplexAssign) = statement;

      free(yyvsp[-2].identifier);
   ;
    break;}
case 52:
#line 652 "fractal.yacc"
{
      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "+=", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 53:
#line 662 "fractal.yacc"
{
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "+=", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 54:
#line 674 "fractal.yacc"
{
      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "-=", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 55:
#line 684 "fractal.yacc"
{
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "-=", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 56:
#line 696 "fractal.yacc"
{
      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "*=", BinaryComplexNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 57:
#line 706 "fractal.yacc"
{
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "*=", BinaryComplexNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 58:
#line 718 "fractal.yacc"
{
      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "/=", BinaryComplexNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 59:
#line 728 "fractal.yacc"
{
      doubleToComplex(voidPointer);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "/=", BinaryComplexNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 60:
#line 740 "fractal.yacc"
{
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-1].identifier, "++", BinaryComplexNode::_PLUS_, TRUE
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 61:
#line 758 "fractal.yacc"
{
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[0].identifier, "++", BinaryComplexNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 62:
#line 776 "fractal.yacc"
{
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[-1].identifier, "--", BinaryComplexNode::_MINUS_, TRUE
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 63:
#line 794 "fractal.yacc"
{
      ConstantDoubleNode *c = 0;
      NumericComplexNode *n = 0;

      DNEW(c, ConstantDoubleNode(1.0));
      DNEW(n, NumericComplexNode(c));

      ENV(complexNodeStack).push(n);

      int status = handleComplexOperatorAssign(
         voidPointer, yyvsp[0].identifier, "--", BinaryComplexNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 64:
#line 813 "fractal.yacc"
{
      double *ptr = ENV(fractalPtr)->getDoubleVariables().assign(yyvsp[-2].identifier);
      const DoubleNode *node = ENV(doubleNodeStack).pop();

      DoubleAssignmentStatement *statement = 0;
      DNEW(statement, DoubleAssignmentStatement(ptr, yyvsp[-2].identifier, node));

      ENV(currentDoubleAssign) = statement;

      free(yyvsp[-2].identifier);
   ;
    break;}
case 65:
#line 826 "fractal.yacc"
{
      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "+=", BinaryDoubleNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 66:
#line 836 "fractal.yacc"
{
      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "-=", BinaryDoubleNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 67:
#line 846 "fractal.yacc"
{
      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "*=", BinaryDoubleNode::_MULTIPLY_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 68:
#line 856 "fractal.yacc"
{
      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-2].identifier, "/=", BinaryDoubleNode::_DIVIDE_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 69:
#line 866 "fractal.yacc"
{
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-1].identifier, "++", BinaryDoubleNode::_PLUS_, TRUE
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 70:
#line 881 "fractal.yacc"
{
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[0].identifier, "++", BinaryDoubleNode::_PLUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 71:
#line 896 "fractal.yacc"
{
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[-1].identifier, "--", BinaryDoubleNode::_MINUS_, TRUE
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 72:
#line 911 "fractal.yacc"
{
      ConstantDoubleNode *n = 0;
      DNEW(n, ConstantDoubleNode(1.0));

      ENV(doubleNodeStack).push(n);

      int status = handleDoubleOperatorAssign(
         voidPointer, yyvsp[0].identifier, "--", BinaryDoubleNode::_MINUS_
      );

      if(status == -1)
         return(-1);
   ;
    break;}
case 76:
#line 932 "fractal.yacc"
{
      const DoubleNode *index = ENV(doubleNodeStack).pop();
      Statement *s = 0;
      DNEW(s, IndexedSetColorStatement(index, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(s);
   ;
    break;}
case 77:
#line 947 "fractal.yacc"
{
      const DoubleNode *blue   = ENV(doubleNodeStack).pop();
      const DoubleNode *green  = ENV(doubleNodeStack).pop();
      const DoubleNode *red    = ENV(doubleNodeStack).pop();

      Statement *s = 0;
      DNEW(s, RGBSetColorStatement(red, green, blue, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(s);
   ;
    break;}
case 78:
#line 965 "fractal.yacc"
{
      const DoubleNode *v = ENV(doubleNodeStack).pop();
      const DoubleNode *s = ENV(doubleNodeStack).pop();
      const DoubleNode *h = ENV(doubleNodeStack).pop();

      HSVSetColorStatement *st = 0;
      DNEW(st, HSVSetColorStatement(h, s, v, *ENV(fractalPtr)));

      ENV(compoundStack).top()->add(st);
   ;
    break;}
case 79:
#line 978 "fractal.yacc"
{
      NullStatement *n = 0;
      DNEW(n, NullStatement());
      ENV(compoundStack).top()->add(n);
   ;
    break;}
case 80:
#line 986 "fractal.yacc"
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
   ;
    break;}
case 81:
#line 1006 "fractal.yacc"
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
   ;
    break;}
case 82:
#line 1025 "fractal.yacc"
{
               MapColorFunctionDoubleNode *m = 0;
               DNEW(m, MapColorFunctionDoubleNode());
               ENV(mapStack).push(m);
            ;
    break;}
case 83:
#line 1033 "fractal.yacc"
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
            ;
    break;}
case 86:
#line 1064 "fractal.yacc"
{
                  ENV(mapStack).top()->addArgument(
                     ENV(doubleNodeStack).pop()
                  );
               ;
    break;}
case 87:
#line 1072 "fractal.yacc"
{
                  DNEW(ENV(printStatement), PrintStatement());
               ;
    break;}
case 88:
#line 1076 "fractal.yacc"
{
                  DNEW(ENV(printStatement), PrintStatement(1));
               ;
    break;}
case 89:
#line 1083 "fractal.yacc"
{
                     const Statement *statement = ENV(printStatement);
                     ENV(compoundStack).top()->add(statement);
                     ENV(printStatement) = NULL;
                  ;
    break;}
case 94:
#line 1099 "fractal.yacc"
{
      const DoubleNode *node = ENV(doubleNodeStack).pop();

      DoubleNodePrintArg *a = 0;
      DNEW(a, DoubleNodePrintArg(node));

      ENV(printStatement)->addPrintArg(a);
   ;
    break;}
case 95:
#line 1108 "fractal.yacc"
{
      const ComplexNode *node = ENV(complexNodeStack).pop();
      ComplexNodePrintArg *c = 0;
      DNEW(c, ComplexNodePrintArg(node));

      ENV(printStatement)->addPrintArg(c);
   ;
    break;}
case 96:
#line 1116 "fractal.yacc"
{
      LiteralPrintArg *a = 0;
      DNEW(a, LiteralPrintArg(yyvsp[0].literal));
      ENV(printStatement)->addPrintArg(a);
      free(yyvsp[0].literal);
   ;
    break;}
case 97:
#line 1125 "fractal.yacc"
{
               ENV(printStatement)->setDestination(yyvsp[0].literal);
               free(yyvsp[0].literal);
            ;
    break;}
case 98:
#line 1132 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());

                  ENV(compoundStack).push(c);

                  ENV(conditionalCounter).beginCount();
                  ENV(conditionalCounter).increment();
               ;
    break;}
case 100:
#line 1145 "fractal.yacc"
{
                     CompoundStatement *c = 0;
                     DNEW(c, CompoundStatement());

                     ENV(compoundStack).push(c);
                  ;
    break;}
case 102:
#line 1155 "fractal.yacc"
{
                     CompoundStatement *c = 0;
                     DNEW(c, CompoundStatement());

                     ENV(compoundStack).push(c);

                     ENV(conditionalCounter).increment();
                  ;
    break;}
case 108:
#line 1175 "fractal.yacc"
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
                       ;
    break;}
case 109:
#line 1202 "fractal.yacc"
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
                       ;
    break;}
case 113:
#line 1242 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               ;
    break;}
case 114:
#line 1249 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               ;
    break;}
case 115:
#line 1256 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
                  ENV(breakContinueAllowed).push(TRUE);
               ;
    break;}
case 116:
#line 1263 "fractal.yacc"
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
               ;
    break;}
case 117:
#line 1294 "fractal.yacc"
{
                     SwitchStatement *sw = 0;
                     DNEW(sw, SwitchStatement(ENV(doubleNodeStack).pop()));

                     ENV(switchStack).push(sw);
                     ENV(breakContinueAllowed).push(FALSE);
                  ;
    break;}
case 118:
#line 1304 "fractal.yacc"
{
                     const SwitchStatement *sw = ENV(switchStack).pop();
                     ENV(compoundStack).top()->add(sw);
                     ENV(breakContinueAllowed).pop();
                  ;
    break;}
case 125:
#line 1322 "fractal.yacc"
{
                  ENV(switchStack).top()->caseBegin();
               ;
    break;}
case 126:
#line 1326 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());

                  ENV(compoundStack).push(c);
               ;
    break;}
case 127:
#line 1333 "fractal.yacc"
{
                  ENV(switchStack).top()->caseAddStatements(
                     ENV(compoundStack).pop()
                  );
               ;
    break;}
case 130:
#line 1345 "fractal.yacc"
{
               ENV(switchStack).top()->caseAddNode(
                  ENV(doubleNodeStack).pop()
               );
            ;
    break;}
case 131:
#line 1353 "fractal.yacc"
{
                  ENV(switchStack).top()->caseBegin();
               ;
    break;}
case 132:
#line 1357 "fractal.yacc"
{
                  CompoundStatement *c = 0;
                  DNEW(c, CompoundStatement());
                  ENV(compoundStack).push(c);
               ;
    break;}
case 133:
#line 1363 "fractal.yacc"
{
                  ENV(switchStack).top()->caseAddStatements(
                     ENV(compoundStack).pop()
                  );
               ;
    break;}
case 136:
#line 1375 "fractal.yacc"
{
               ENV(switchStack).top()->caseSetBreak();
            ;
    break;}
case 137:
#line 1381 "fractal.yacc"
{
                        TrueBooleanNode *t = 0;
                        DNEW(t, TrueBooleanNode());
                        ENV(booleanNodeStack).push(t);
                     ;
    break;}
case 138:
#line 1388 "fractal.yacc"
{
                        FalseBooleanNode *f = 0;
                        DNEW(f, FalseBooleanNode());
                        ENV(booleanNodeStack).push(f);
                     ;
    break;}
case 139:
#line 1395 "fractal.yacc"
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
                     ;
    break;}
case 140:
#line 1413 "fractal.yacc"
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
                     ;
    break;}
case 141:
#line 1431 "fractal.yacc"
{
                        /* -- Nothing to do -- */
                     ;
    break;}
case 142:
#line 1435 "fractal.yacc"
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
                     ;
    break;}
case 143:
#line 1453 "fractal.yacc"
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
                     ;
    break;}
case 144:
#line 1471 "fractal.yacc"
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
                     ;
    break;}
case 145:
#line 1489 "fractal.yacc"
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
                     ;
    break;}
case 146:
#line 1507 "fractal.yacc"
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
                     ;
    break;}
case 147:
#line 1525 "fractal.yacc"
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
                     ;
    break;}
case 149:
#line 1544 "fractal.yacc"
{
                        NotBooleanNode *n = 0;

                        DNEW(
                           n, NotBooleanNode(ENV(booleanNodeStack).pop())
                        );

                        ENV(booleanNodeStack).push(n);
                    ;
    break;}
case 152:
#line 1561 "fractal.yacc"
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
            ;
    break;}
case 153:
#line 1579 "fractal.yacc"
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
            ;
    break;}
case 154:
#line 1597 "fractal.yacc"
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
            ;
    break;}
case 155:
#line 1615 "fractal.yacc"
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
            ;
    break;}
case 156:
#line 1633 "fractal.yacc"
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
            ;
    break;}
case 157:
#line 1657 "fractal.yacc"
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
            ;
    break;}
case 158:
#line 1681 "fractal.yacc"
{
               UnaryDoubleNode *u = 0;

               DNEW(
                  u,
                  UnaryDoubleNode(
                     ENV(doubleNodeStack).pop()
                  )
               );

               ENV(doubleNodeStack).push(u);
            ;
    break;}
case 159:
#line 1694 "fractal.yacc"
{
               /* -- Nothing to do -- */
            ;
    break;}
case 160:
#line 1698 "fractal.yacc"
{
               ConstantDoubleNode *c = 0;
               DNEW(c, ConstantDoubleNode(yyvsp[0].dvalue));
               ENV(doubleNodeStack).push(c);
            ;
    break;}
case 161:
#line 1704 "fractal.yacc"
{
               // Ensure this variable has been defined

               const double *ptr =
                  ENV(fractalPtr)->getDoubleVariables().lookup(yyvsp[0].identifier);

               if(ptr == NULL)
               {
                  ostringstream temp;

                  temp << "Undefined double variable: [$" << yyvsp[0].identifier << "]";

                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[0].identifier);
                  return(-1);
               }

               VariableDoubleNode *v = 0;
               DNEW(v, VariableDoubleNode(yyvsp[0].identifier, ptr));

               ENV(doubleNodeStack).push(v);
               free(yyvsp[0].identifier);
            ;
    break;}
case 162:
#line 1729 "fractal.yacc"
{
               AttributeDoubleNode *ptr =
                  AttributeDoubleNode::create(
                     yyvsp[-3].complexAttribute, ENV(complexNodeStack).pop()
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

                  temp << "No matching attribute: " << yyvsp[-3].complexAttribute <<
                     "(complex_expression)";

                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[-3].complexAttribute);
                  return(-1);
               }

               free(yyvsp[-3].complexAttribute);

               ENV(doubleNodeStack).push(ptr);
            ;
    break;}
case 163:
#line 1762 "fractal.yacc"
{
               /* -- Nothing to do -- */
            ;
    break;}
case 164:
#line 1766 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               int error = FALSE;

               OneArgFunctionDoublePointer fPtr =
                  OneArgFunctionDoubleNode::lookup(yyvsp[-3].identifier);

               if(!fPtr)
               {
                  // This could also be a GetEntryDoubleNode so
                  // try that as well

                  GetEntryDoubleNode::WhichEntry entry =
                     GetEntryDoubleNode::lookup(yyvsp[-3].identifier);

                  if(entry == GetEntryDoubleNode::INVALID)
                  {
                     ostringstream temp;

                     temp << "No matching function: " << yyvsp[-3].identifier <<
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
                           yyvsp[-3].identifier,
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
                        yyvsp[-3].identifier, fPtr, ENV(doubleNodeStack).pop()
                     )
                  );

                  ENV(doubleNodeStack).push(o);
               }

               free(yyvsp[-3].identifier);

               if(error)
                  return(-1);
            ;
    break;}
case 165:
#line 1829 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               TwoArgFunctionDoublePointer fPtr =
                  TwoArgFunctionDoubleNode::lookup(yyvsp[-5].identifier);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << yyvsp[-5].identifier <<
                     "(double, double)";
                
                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[-5].identifier);
                  return(-1);
               }

               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               TwoArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionDoubleNode(
                     yyvsp[-5].identifier, fPtr, first, second
                  )
               );

               ENV(doubleNodeStack).push(t);

               free(yyvsp[-5].identifier);
            ;
    break;}
case 166:
#line 1867 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               ThreeArgFunctionDoublePointer fPtr =
                  ThreeArgFunctionDoubleNode::lookup(yyvsp[-7].identifier);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << yyvsp[-7].identifier <<
                     "(double, double, double)";
                
                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[-7].identifier);
                  return(-1);
               }

               const DoubleNode *third  = ENV(doubleNodeStack).pop();
               const DoubleNode *second = ENV(doubleNodeStack).pop();
               const DoubleNode *first  = ENV(doubleNodeStack).pop();

               ThreeArgFunctionDoubleNode *t = 0;

               DNEW(
                  t,
                  ThreeArgFunctionDoubleNode(
                     yyvsp[-7].identifier, fPtr, first, second, third
                  )
               );

               ENV(doubleNodeStack).push(t);

               free(yyvsp[-7].identifier);
            ;
    break;}
case 167:
#line 1910 "fractal.yacc"
{
               const ComplexNode *point  = ENV(complexNodeStack).pop();
               const DoubleNode  *thick  = ENV(doubleNodeStack).pop();
               const DoubleNode  *height = ENV(doubleNodeStack).pop();
               const ComplexNode *origin = ENV(complexNodeStack).pop();

               TextIntersectNode *t = 0;

               DNEW(
                  t,
                  TextIntersectNode(
                     yyvsp[-9].literal, origin, height, thick, point
                  )
               );

               ENV(doubleNodeStack).push(t);

               free(yyvsp[-9].literal);
            ;
    break;}
case 168:
#line 1930 "fractal.yacc"
{
               const BooleanNode *test   = ENV(booleanNodeStack).pop();
               const DoubleNode  *second = ENV(doubleNodeStack).pop();
               const DoubleNode  *first  = ENV(doubleNodeStack).pop();

               TernaryDoubleNode *t = 0;
               DNEW(t, TernaryDoubleNode(test, first, second));

               ENV(doubleNodeStack).push(t);
            ;
    break;}
case 169:
#line 1941 "fractal.yacc"
{
               const DoubleAssignmentStatement *s =
                  ENV(currentDoubleAssign);

               ENV(currentDoubleAssign) = NULL;

               AssignmentDoubleNode *a = 0;
               DNEW(a, AssignmentDoubleNode(s));
               ENV(doubleNodeStack).push(a);
            ;
    break;}
case 178:
#line 1964 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 179:
#line 1966 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 182:
#line 1974 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 183:
#line 1976 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 186:
#line 1984 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 187:
#line 1986 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 190:
#line 1994 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 191:
#line 1996 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 194:
#line 2004 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 195:
#line 2006 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 198:
#line 2014 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 199:
#line 2016 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 202:
#line 2024 "fractal.yacc"
{ doubleToComplex(voidPointer);    ;
    break;}
case 203:
#line 2026 "fractal.yacc"
{ doubleToComplex(voidPointer, 1); ;
    break;}
case 208:
#line 2038 "fractal.yacc"
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
            ;
    break;}
case 209:
#line 2056 "fractal.yacc"
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
            ;
    break;}
case 210:
#line 2074 "fractal.yacc"
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
            ;
    break;}
case 211:
#line 2092 "fractal.yacc"
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
            ;
    break;}
case 212:
#line 2110 "fractal.yacc"
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
            ;
    break;}
case 213:
#line 2134 "fractal.yacc"
{
               UnaryComplexNode *u = 0;

               DNEW(
                  u,
                  UnaryComplexNode(
                     ENV(complexNodeStack).pop()
                  )
               );

               ENV(complexNodeStack).push(u);
            ;
    break;}
case 214:
#line 2147 "fractal.yacc"
{
               /* -- Nothing to do -- */
            ;
    break;}
case 215:
#line 2151 "fractal.yacc"
{
               // Strictly speaking, we don't actually need COMPLEX
               // at all anymore now that we've revamped the automatic
               // double -> complex conversions but there's no harm
               // in supporting it for compatibility reasons

               doubleToComplex(voidPointer);
            ;
    break;}
case 216:
#line 2160 "fractal.yacc"
{
               const DoubleNode *imaginaryPart = ENV(doubleNodeStack).pop();
               const DoubleNode *realPart      = ENV(doubleNodeStack).pop();

               NumericComplexNode *n = 0;
               DNEW(n, NumericComplexNode(realPart, imaginaryPart));

               ENV(complexNodeStack).push(n);
            ;
    break;}
case 217:
#line 2170 "fractal.yacc"
{
               /* -- Ensure this variable has been defined -- */

               dcomplex *ptr =
                  ENV(fractalPtr)->getComplexVariables().lookup(yyvsp[0].identifier);

               if(ptr == NULL)
               {
                  ostringstream temp;

                  temp << "Undefined variable: [" << yyvsp[0].identifier << "]";

                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[0].identifier);
                  return(-1);
               }

               VariableComplexNode *v = 0;
               DNEW(v, VariableComplexNode(yyvsp[0].identifier, ptr));
               ENV(complexNodeStack).push(v);

               free(yyvsp[0].identifier);
            ;
    break;}
case 218:
#line 2195 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               OneArgFunctionComplexPointer fPtr =
                  OneArgFunctionComplexNode::lookup(yyvsp[-3].identifier);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << yyvsp[-3].identifier
                     << "(complex)";

                  handleError(temp.str().c_str(), voidPointer);

                  free(yyvsp[-3].identifier);
                  return(-1);
               }

               OneArgFunctionComplexNode *o = 0;

               DNEW(
                  o,
                  OneArgFunctionComplexNode(
                     yyvsp[-3].identifier, fPtr, ENV(complexNodeStack).pop()
                  )
               );

               ENV(complexNodeStack).push(o);

               free(yyvsp[-3].identifier);
            ;
    break;}
case 219:
#line 2228 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               TwoArgFunctionComplexPointer fPtr =
                  TwoArgFunctionComplexNode::lookup(yyvsp[-3].identifier);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << yyvsp[-3].identifier
                       << "(complex, complex)";

                  handleError(temp.str().c_str(), voidPointer);
                  
                  free(yyvsp[-3].identifier);
                  return(-1);
               }

               const ComplexNode *second = ENV(complexNodeStack).pop();
               const ComplexNode *first  = ENV(complexNodeStack).pop();

               TwoArgFunctionComplexNode *t = 0;

               DNEW(
                  t,
                  TwoArgFunctionComplexNode(
                     yyvsp[-3].identifier, fPtr, first, second
                  )
               );

               ENV(complexNodeStack).push(t);

               free(yyvsp[-3].identifier);
            ;
    break;}
case 220:
#line 2266 "fractal.yacc"
{
               /* -- Attempt to look up the function requested -- */

               MixedThreeArgFunctionComplexPointer fPtr =
                  MixedThreeArgFunctionComplexNode::lookup(yyvsp[-5].identifier);

               if(!fPtr)
               {
                  ostringstream temp;

                  temp << "No matching function: " << yyvsp[-5].identifier
                       << "(complex, complex, double)";

                  handleError(temp.str().c_str(), voidPointer);
                  
                  free(yyvsp[-5].identifier);
                  return(-1);
               }

               const ComplexNode *second = ENV(complexNodeStack).pop();
               const ComplexNode *first  = ENV(complexNodeStack).pop();
               const DoubleNode *third   = ENV(doubleNodeStack).pop();

               MixedThreeArgFunctionComplexNode *m = 0;

               DNEW(
                  m,
                  MixedThreeArgFunctionComplexNode(
                     yyvsp[-5].identifier, fPtr, first, second, third
                  )
               );

               ENV(complexNodeStack).push(m);

               free(yyvsp[-5].identifier);
            ;
    break;}
case 221:
#line 2303 "fractal.yacc"
{
               const BooleanNode *test    = ENV(booleanNodeStack).pop();
               const ComplexNode  *second = ENV(complexNodeStack).pop();
               const ComplexNode  *first  = ENV(complexNodeStack).pop();

               TernaryComplexNode *t = 0;
               DNEW(t, TernaryComplexNode(test, first, second));

               ENV(complexNodeStack).push(t);
            ;
    break;}
case 222:
#line 2314 "fractal.yacc"
{
               const ComplexAssignmentStatement *s =
                  ENV(currentComplexAssign);

               ENV(currentComplexAssign) = NULL;

               AssignmentComplexNode *a = 0;
               DNEW(a, AssignmentComplexNode(s));

               ENV(complexNodeStack).push(a);
            ;
    break;}
case 223:
#line 2328 "fractal.yacc"
{
            yyval.dvalue = yyvsp[0].dvalue;
         ;
    break;}
case 224:
#line 2332 "fractal.yacc"
{
            yyval.dvalue = (double)yyvsp[0].ivalue;
         ;
    break;}
case 225:
#line 2338 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[-2].dvalue + yyvsp[0].dvalue;
                     ;
    break;}
case 226:
#line 2342 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[-2].dvalue - yyvsp[0].dvalue;
                     ;
    break;}
case 227:
#line 2346 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[-2].dvalue * yyvsp[0].dvalue;
                     ;
    break;}
case 228:
#line 2350 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[-2].dvalue / yyvsp[0].dvalue;
                     ;
    break;}
case 229:
#line 2354 "fractal.yacc"
{
                        yyval.dvalue = -yyvsp[0].dvalue;
                     ;
    break;}
case 230:
#line 2358 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[-1].dvalue;
                     ;
    break;}
case 231:
#line 2362 "fractal.yacc"
{
                        yyval.dvalue = yyvsp[0].dvalue;
                     ;
    break;}
case 232:
#line 2368 "fractal.yacc"
{
                  ENV(pointCounter).increment();
               ;
    break;}
case 233:
#line 2372 "fractal.yacc"
{
                  ENV(pointCounter).increment();
               ;
    break;}
case 234:
#line 2379 "fractal.yacc"
{
            const ComplexNode *center = ENV(complexNodeStack).pop();
            const DoubleNode  *radius = ENV(doubleNodeStack).pop();

            CircleRegionNode *c = 0;
            DNEW(c, CircleRegionNode(center, radius));
            ENV(regionNodeStack).push(c);
         ;
    break;}
case 235:
#line 2389 "fractal.yacc"
{
            const ComplexNode *center  = ENV(complexNodeStack).pop();
            const DoubleNode  *yradius = ENV(doubleNodeStack).pop();
            const DoubleNode  *xradius = ENV(doubleNodeStack).pop();

            EllipseRegionNode *e = 0;
            DNEW(e, EllipseRegionNode(center, xradius, yradius));

            ENV(regionNodeStack).push(e);
         ;
    break;}
case 236:
#line 2400 "fractal.yacc"
{
            const ComplexNode *second = ENV(complexNodeStack).pop();
            const ComplexNode *first  = ENV(complexNodeStack).pop();

            RectRegionNode *r = 0;
            DNEW(r, RectRegionNode(first, second));
            ENV(regionNodeStack).push(r);
         ;
    break;}
case 237:
#line 2409 "fractal.yacc"
{
            ENV(pointCounter).beginCount();
            ENV(pointCounter).increment();
            ENV(pointCounter).increment();
         ;
    break;}
case 238:
#line 2416 "fractal.yacc"
{
            int size = ENV(pointCounter).endCount();

            const ComplexNode **points = 0;
            DNEW(points, const ComplexNode *[size]);

            for(int i = 0, j = size - 1; i < size; i ++, j --)
               points[j] = ENV(complexNodeStack).pop();

            PolyRegionNode *n = 0;

            DNEW(n, PolyRegionNode(points, size));

            ENV(regionNodeStack).push(n);
         ;
    break;}
case 239:
#line 2433 "fractal.yacc"
{
            const ComplexNode *center = ENV(complexNodeStack).pop();
            const DoubleNode  *angle  = ENV(doubleNodeStack).pop();
            const DoubleNode  *radius = ENV(doubleNodeStack).pop();
            const DoubleNode  *nSides = ENV(doubleNodeStack).pop();

            SPolyRegionNode *s = 0;
            DNEW(s, SPolyRegionNode(center, nSides, radius, angle));
            ENV(regionNodeStack).push(s);
         ;
    break;}
case 240:
#line 2446 "fractal.yacc"
{
            const ComplexNode *p2     = ENV(complexNodeStack).pop();
            const ComplexNode *p1     = ENV(complexNodeStack).pop();
            const DoubleNode  *height = ENV(doubleNodeStack).pop();
            const DoubleNode  *width  = ENV(doubleNodeStack).pop();

            CrossRegionNode *c = 0;
            DNEW(c, CrossRegionNode(p1, p2, width, height));
            ENV(regionNodeStack).push(c);
         ;
    break;}
case 241:
#line 2457 "fractal.yacc"
{
            const RegionNode *node = ENV(regionNodeStack).pop();

            NotRegionNode *n = 0;
            DNEW(n, NotRegionNode(node));
            ENV(regionNodeStack).push(n);
         ;
    break;}
case 242:
#line 2465 "fractal.yacc"
{
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            AndRegionNode *a = 0;
            DNEW(a, AndRegionNode(first, second));
            ENV(regionNodeStack).push(a);
         ;
    break;}
case 243:
#line 2474 "fractal.yacc"
{
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            OrRegionNode *o = 0;
            DNEW(o, OrRegionNode(first, second));
            ENV(regionNodeStack).push(o);
   ;
    break;}
case 244:
#line 2483 "fractal.yacc"
{
            const RegionNode *second = ENV(regionNodeStack).pop();
            const RegionNode *first  = ENV(regionNodeStack).pop();

            XorRegionNode *x = 0;
            DNEW(x, XorRegionNode(first, second));
            ENV(regionNodeStack).push(x);
   ;
    break;}
case 245:
#line 2494 "fractal.yacc"
{
      const ComplexNode *point = ENV(complexNodeStack).pop();
      const RegionNode *region = ENV(regionNodeStack).pop();

      InsideBooleanNode *i = 0;
      DNEW(i, InsideBooleanNode(point, region));
      ENV(booleanNodeStack).push(i);
   ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 2504 "fractal.yacc"


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
