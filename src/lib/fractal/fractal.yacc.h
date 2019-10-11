#ifndef BISON_FRACTAL_YACC_H
# define BISON_FRACTAL_YACC_H

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


#endif /* not BISON_FRACTAL_YACC_H */
