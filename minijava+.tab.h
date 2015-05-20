/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_MINIJAVA_TAB_H_INCLUDED
# define YY_YY_MINIJAVA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    PONTOEVIRGULA = 259,
    LP = 260,
    RP = 261,
    LB = 262,
    RB = 263,
    LC = 264,
    RC = 265,
    PONTO = 266,
    IGUAL = 267,
    EXCLAMACAO = 268,
    CLASS = 269,
    SYSTEMOUTPRINTLN = 270,
    PSVM = 271,
    STRING = 272,
    EXTENDS = 273,
    LENGTH = 274,
    READERS = 275,
    WHILE = 276,
    IF = 277,
    TRUE = 278,
    FALSE = 279,
    NEW = 280,
    THIS = 281,
    INT = 282,
    BOOLEAN = 283,
    PUBLIC = 284,
    RETORNA = 285,
    ELSE = 286,
    INTEGER_LITERAL = 287,
    ID = 288,
    OPERATOR = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "minijava+.y" /* yacc.c:1909  */

	int int_val;
	string* id_val;
	string* op_val;
	char type_val;
	ASTNode* node;

#line 97 "minijava+.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MINIJAVA_TAB_H_INCLUDED  */
