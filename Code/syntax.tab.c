/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./syntax.y"

#include <stdio.h>
#include <string.h>
#include "syntax_tree.h"

int yylex(void);
void yyerror(const char *s);

Node *syntax_root = NULL;
int syntax_error_count = 0;
static int last_syntax_error_line = -1;

static void report_syntax_error_line(int line, const char *msg){
    if(line <= 0) line = 1;
    if(last_syntax_error_line == line) return;
    printf("Error type B at Line %d: %s\n", line, msg);
    syntax_error_count++;
    last_syntax_error_line = line;
}

#line 92 "./syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_SEMI = 7,                       /* SEMI  */
  YYSYMBOL_COMMA = 8,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 9,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 10,                     /* RELOP  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_MINUS = 12,                     /* MINUS  */
  YYSYMBOL_STAR = 13,                      /* STAR  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_DOT = 17,                       /* DOT  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 31,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_ExtDefList = 34,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 35,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 36,                /* ExtDecList  */
  YYSYMBOL_Specifier = 37,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 38,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 39,                    /* OptTag  */
  YYSYMBOL_Tag = 40,                       /* Tag  */
  YYSYMBOL_VarDec = 41,                    /* VarDec  */
  YYSYMBOL_FunDec = 42,                    /* FunDec  */
  YYSYMBOL_VarList = 43,                   /* VarList  */
  YYSYMBOL_ParamDec = 44,                  /* ParamDec  */
  YYSYMBOL_CompSt = 45,                    /* CompSt  */
  YYSYMBOL_StmtList = 46,                  /* StmtList  */
  YYSYMBOL_Stmt = 47,                      /* Stmt  */
  YYSYMBOL_DefList = 48,                   /* DefList  */
  YYSYMBOL_Def = 49,                       /* Def  */
  YYSYMBOL_DecList = 50,                   /* DecList  */
  YYSYMBOL_Dec = 51,                       /* Dec  */
  YYSYMBOL_Exp = 52,                       /* Exp  */
  YYSYMBOL_Args = 53                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    55,    58,    62,    64,    66,    68,    77,
      79,    81,    90,    92,    97,    99,   101,   109,   112,   116,
     121,   123,   125,   134,   136,   138,   147,   149,   151,   160,
     162,   171,   173,   182,   185,   189,   191,   193,   195,   201,
     203,   205,   211,   217,   219,   225,   231,   240,   243,   247,
     249,   258,   260,   262,   271,   273,   275,   284,   286,   288,
     290,   292,   294,   296,   298,   300,   302,   304,   306,   308,
     310,   316,   318,   324,   330,   332,   334,   336,   341,   343,
     345
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "TYPE", "INT",
  "FLOAT", "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR",
  "DIV", "AND", "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "UMINUS",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,     0,   -63,    23,    20,   -63,    13,    37,   -63,   -63,
     -63,    35,    40,   -63,   -63,   -63,    47,   -63,    63,    -2,
      48,    17,    44,   -63,    88,    42,    49,   -63,    77,    80,
      69,    76,    78,   -63,    89,    87,   106,   -63,   -63,   -63,
      96,   101,     1,   103,   -63,    30,   117,   120,   -63,   -63,
     -63,   -63,   104,   -63,    11,   -63,   -63,   -63,   127,   121,
     -63,   -63,   255,   255,   255,   197,   125,   128,   -63,   115,
     103,   170,   207,   -63,   116,   -63,   -63,   -63,   187,    39,
      39,   309,   136,   268,   217,   255,   -63,   -63,   -63,   -63,
     255,   227,   255,   255,   255,   255,   255,   255,   143,   237,
     -63,   348,   -63,   -63,   131,   -63,   282,   138,   -63,   -63,
     -63,   140,   322,   335,   348,   -63,    99,   124,   124,    39,
      39,   152,   360,   -63,   148,   295,   -63,   247,   -63,   130,
     130,   149,   -63,   -63,   -63,   -63,   146,   161,   127,   -63,
     130,   130,   -63,   -63
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    12,     0,     0,     2,     0,     0,    13,     8,
      16,    19,     0,    15,     1,     3,    20,     6,     0,     9,
       0,     0,     0,     5,     0,     0,     0,     7,     0,     0,
       0,     0,     0,    24,     0,     0,    27,    11,    20,    10,
       0,     0,     0,     0,    50,    54,     0,    51,    14,    47,
      25,    30,    29,    23,     0,    22,    21,    32,     0,    75,
      76,    77,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,    49,     0,    28,    26,    46,     0,    66,
      67,     0,     0,     0,     0,     0,    31,    33,    45,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    55,    53,    52,     0,    69,    79,     0,    65,    38,
      37,     0,     0,     0,    57,    73,    60,    61,    62,    63,
      64,    58,    59,    74,     0,     0,    70,     0,    68,     0,
       0,     0,    72,    71,    80,    78,    41,    39,    44,    43,
       0,     0,    42,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   188,   -63,   171,     5,   -63,   -63,   -63,   -25,
     -63,   142,   -63,   177,   134,   -44,    31,   -63,   137,   -63,
     -62,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    18,    29,     8,    12,    13,    19,
      20,    35,    36,    68,    69,    70,    30,    31,    46,    47,
      71,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    80,    81,    83,    45,     7,    24,     9,    44,    52,
     101,     7,    75,    -4,     1,     2,   106,     2,    28,    25,
      14,     2,   112,   113,    10,    57,    11,    34,   114,   116,
     117,   118,   119,   120,   121,   122,     3,   125,     3,    72,
      16,   -48,     3,    40,    17,    32,   -18,    41,     2,    45,
      42,    25,   -48,     2,   -48,   -48,    98,    43,   -17,    34,
      99,   -48,    49,    21,    33,   106,    22,   -48,   -48,     3,
      23,    26,   -48,   -48,     3,   -48,   -48,    28,   -48,   -48,
       2,   -48,   -48,    38,    44,   136,   137,   139,   -48,    37,
      51,    38,    38,    48,   -48,   -48,   142,   143,    50,   -48,
     -48,     3,   -48,   -48,    58,   -48,    59,    53,    60,    61,
      92,    93,    94,    95,    54,    62,    98,   102,    55,    38,
      99,    63,    64,    56,    73,    25,    26,   -34,    74,    65,
      66,    58,    67,    59,    77,    60,    61,    94,    95,    86,
      78,    98,    62,   109,    84,    99,   123,    85,    63,    64,
     138,   126,    59,    26,    60,    61,    65,    66,   128,    67,
     129,    62,    91,    92,    93,    94,    95,    63,    64,    98,
     132,    88,    26,    99,   140,    65,    66,    89,    67,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   104,   141,
      59,    99,    60,    61,    15,    39,    76,    27,    82,    62,
      59,   135,    60,    61,    87,    63,    64,   105,   100,    62,
      59,   103,    60,    61,     0,    63,    64,     0,   111,    62,
      59,     0,    60,    61,     0,    63,    64,     0,   115,    62,
      59,     0,    60,    61,     0,    63,    64,     0,   124,    62,
      59,     0,    60,    61,     0,    63,    64,     0,   134,    62,
      59,     0,    60,    61,     0,    63,    64,     0,    59,    62,
      60,    61,     0,     0,     0,    63,    64,    62,     0,     0,
       0,     0,     0,    63,    64,   110,     0,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,     0,     0,    99,
     127,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,     0,     0,    99,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,     0,     0,    99,   133,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,     0,   108,
      99,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,     0,   130,    99,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,     0,   131,    99,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,     0,     0,    99,
      91,    92,    93,    94,    95,    96,     0,    98,     0,     0,
       0,    99
};

static const yytype_int16 yycheck[] =
{
      62,    63,    64,    65,    29,     0,     8,     7,     7,    34,
      72,     6,     1,     0,     1,     4,    78,     4,     1,    21,
       0,     4,    84,    85,     1,    24,     3,    22,    90,    91,
      92,    93,    94,    95,    96,    97,    25,    99,    25,     9,
       3,    24,    25,     1,     7,     1,    23,     5,     4,    74,
       1,    21,     3,     4,     5,     6,    17,    26,    23,    54,
      21,    12,    31,    23,    20,   127,    19,    18,    19,    25,
       7,    23,    23,    24,    25,    26,    27,     1,    29,     3,
       4,     5,     6,     3,     7,   129,   130,   131,    12,     1,
       1,     3,     3,    24,    18,    19,   140,   141,    20,    23,
      24,    25,    26,    27,     1,    29,     3,    20,     5,     6,
      11,    12,    13,    14,     8,    12,    17,     1,    22,     3,
      21,    18,    19,    22,     7,    21,    23,    24,     8,    26,
      27,     1,    29,     3,     7,     5,     6,    13,    14,    24,
      19,    17,    12,     7,    19,    21,     3,    19,    18,    19,
       1,    20,     3,    23,     5,     6,    26,    27,    20,    29,
      20,    12,    10,    11,    12,    13,    14,    18,    19,    17,
      22,     1,    23,    21,    28,    26,    27,     7,    29,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     1,    28,
       3,    21,     5,     6,     6,    24,    54,    20,     1,    12,
       3,   127,     5,     6,    70,    18,    19,    20,     1,    12,
       3,    74,     5,     6,    -1,    18,    19,    -1,     1,    12,
       3,    -1,     5,     6,    -1,    18,    19,    -1,     1,    12,
       3,    -1,     5,     6,    -1,    18,    19,    -1,     1,    12,
       3,    -1,     5,     6,    -1,    18,    19,    -1,     1,    12,
       3,    -1,     5,     6,    -1,    18,    19,    -1,     3,    12,
       5,     6,    -1,    -1,    -1,    18,    19,    12,    -1,    -1,
      -1,    -1,    -1,    18,    19,     7,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    21,    22,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    21,
      10,    11,    12,    13,    14,    15,    -1,    17,    -1,    -1,
      -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     4,    25,    33,    34,    35,    37,    38,     7,
       1,     3,    39,    40,     0,    34,     3,     7,    36,    41,
      42,    23,    19,     7,     8,    21,    23,    45,     1,    37,
      48,    49,     1,    20,    37,    43,    44,     1,     3,    36,
       1,     5,     1,    48,     7,    41,    50,    51,    24,    48,
      20,     1,    41,    20,     8,    22,    22,    24,     1,     3,
       5,     6,    12,    18,    19,    26,    27,    29,    45,    46,
      47,    52,     9,     7,     8,     1,    43,     7,    19,    52,
      52,    52,     1,    52,    19,    19,    24,    46,     1,     7,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    21,
       1,    52,     1,    50,     1,    20,    52,    53,    20,     7,
       7,     1,    52,    52,    52,     1,    52,    52,    52,    52,
      52,    52,    52,     3,     1,    52,    20,     8,    20,    20,
      20,    20,    22,    22,     1,    53,    47,    47,     1,    47,
      28,    28,    47,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    36,
      36,    36,    37,    37,    38,    38,    38,    39,    39,    40,
      41,    41,    41,    42,    42,    42,    43,    43,    43,    44,
      44,    45,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    50,    50,    50,    51,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     3,     1,     1,     5,     2,     2,     1,     0,     1,
       1,     4,     4,     4,     3,     4,     3,     1,     3,     2,
       2,     4,     3,     2,     0,     2,     1,     3,     3,     5,
       7,     5,     7,     5,     5,     2,     2,     2,     0,     3,
       2,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
       4,     4,     4,     3,     3,     1,     1,     1,     3,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 51 "./syntax.y"
      { syntax_root = (yyval.node) = new_nonterm("Program", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1660 "./syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 56 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDefList", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1666 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 58 "./syntax.y"
      { (yyval.node) = NULL; }
#line 1672 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 63 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDef", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1678 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 65 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDef", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1684 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 67 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDef", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1690 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: error SEMI  */
#line 69 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1700 "./syntax.tab.c"
    break;

  case 9: /* ExtDecList: VarDec  */
#line 78 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDecList", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1706 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 80 "./syntax.y"
      { (yyval.node) = new_nonterm("ExtDecList", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1712 "./syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA error  */
#line 82 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1722 "./syntax.tab.c"
    break;

  case 12: /* Specifier: TYPE  */
#line 91 "./syntax.y"
      { (yyval.node) = new_nonterm("Specifier", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1728 "./syntax.tab.c"
    break;

  case 13: /* Specifier: StructSpecifier  */
#line 93 "./syntax.y"
      { (yyval.node) = new_nonterm("Specifier", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1734 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 98 "./syntax.y"
      { (yyval.node) = new_nonterm("StructSpecifier", (yylsp[-4]).first_line, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1740 "./syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT Tag  */
#line 100 "./syntax.y"
      { (yyval.node) = new_nonterm("StructSpecifier", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1746 "./syntax.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT error  */
#line 102 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1756 "./syntax.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 110 "./syntax.y"
      { (yyval.node) = new_nonterm("OptTag", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1762 "./syntax.tab.c"
    break;

  case 18: /* OptTag: %empty  */
#line 112 "./syntax.y"
      { (yyval.node) = NULL; }
#line 1768 "./syntax.tab.c"
    break;

  case 19: /* Tag: ID  */
#line 117 "./syntax.y"
      { (yyval.node) = new_nonterm("Tag", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1774 "./syntax.tab.c"
    break;

  case 20: /* VarDec: ID  */
#line 122 "./syntax.y"
      { (yyval.node) = new_nonterm("VarDec", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1780 "./syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB INT RB  */
#line 124 "./syntax.y"
      { (yyval.node) = new_nonterm("VarDec", (yylsp[-3]).first_line, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1786 "./syntax.tab.c"
    break;

  case 22: /* VarDec: VarDec LB error RB  */
#line 126 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1796 "./syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP VarList RP  */
#line 135 "./syntax.y"
      { (yyval.node) = new_nonterm("FunDec", (yylsp[-3]).first_line, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1802 "./syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP RP  */
#line 137 "./syntax.y"
      { (yyval.node) = new_nonterm("FunDec", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1808 "./syntax.tab.c"
    break;

  case 25: /* FunDec: ID LP error RP  */
#line 139 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1818 "./syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec COMMA VarList  */
#line 148 "./syntax.y"
      { (yyval.node) = new_nonterm("VarList", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1824 "./syntax.tab.c"
    break;

  case 27: /* VarList: ParamDec  */
#line 150 "./syntax.y"
      { (yyval.node) = new_nonterm("VarList", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1830 "./syntax.tab.c"
    break;

  case 28: /* VarList: ParamDec COMMA error  */
#line 152 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1840 "./syntax.tab.c"
    break;

  case 29: /* ParamDec: Specifier VarDec  */
#line 161 "./syntax.y"
      { (yyval.node) = new_nonterm("ParamDec", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1846 "./syntax.tab.c"
    break;

  case 30: /* ParamDec: Specifier error  */
#line 163 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1856 "./syntax.tab.c"
    break;

  case 31: /* CompSt: LC DefList StmtList RC  */
#line 172 "./syntax.y"
      { (yyval.node) = new_nonterm("CompSt", (yylsp[-3]).first_line, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1862 "./syntax.tab.c"
    break;

  case 32: /* CompSt: LC error RC  */
#line 174 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1872 "./syntax.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 183 "./syntax.y"
      { (yyval.node) = new_nonterm("StmtList", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1878 "./syntax.tab.c"
    break;

  case 34: /* StmtList: %empty  */
#line 185 "./syntax.y"
      { (yyval.node) = NULL; }
#line 1884 "./syntax.tab.c"
    break;

  case 35: /* Stmt: Exp SEMI  */
#line 190 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1890 "./syntax.tab.c"
    break;

  case 36: /* Stmt: CompSt  */
#line 192 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 1896 "./syntax.tab.c"
    break;

  case 37: /* Stmt: RETURN Exp SEMI  */
#line 194 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1902 "./syntax.tab.c"
    break;

  case 38: /* Stmt: RETURN error SEMI  */
#line 196 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1912 "./syntax.tab.c"
    break;

  case 39: /* Stmt: IF LP Exp RP Stmt  */
#line 202 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[-4]).first_line, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1918 "./syntax.tab.c"
    break;

  case 40: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 204 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[-6]).first_line, 7, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1924 "./syntax.tab.c"
    break;

  case 41: /* Stmt: IF LP error RP Stmt  */
#line 206 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1934 "./syntax.tab.c"
    break;

  case 42: /* Stmt: IF LP error RP Stmt ELSE Stmt  */
#line 212 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-3]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1944 "./syntax.tab.c"
    break;

  case 43: /* Stmt: WHILE LP Exp RP Stmt  */
#line 218 "./syntax.y"
      { (yyval.node) = new_nonterm("Stmt", (yylsp[-4]).first_line, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1950 "./syntax.tab.c"
    break;

  case 44: /* Stmt: WHILE LP Exp RP error  */
#line 220 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1960 "./syntax.tab.c"
    break;

  case 45: /* Stmt: Exp error  */
#line 226 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Missing \";\".");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1970 "./syntax.tab.c"
    break;

  case 46: /* Stmt: error SEMI  */
#line 232 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1980 "./syntax.tab.c"
    break;

  case 47: /* DefList: Def DefList  */
#line 241 "./syntax.y"
      { (yyval.node) = new_nonterm("DefList", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1986 "./syntax.tab.c"
    break;

  case 48: /* DefList: %empty  */
#line 243 "./syntax.y"
      { (yyval.node) = NULL; }
#line 1992 "./syntax.tab.c"
    break;

  case 49: /* Def: Specifier DecList SEMI  */
#line 248 "./syntax.y"
      { (yyval.node) = new_nonterm("Def", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1998 "./syntax.tab.c"
    break;

  case 50: /* Def: error SEMI  */
#line 250 "./syntax.y"
      {
          report_syntax_error_line((yylsp[-1]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2008 "./syntax.tab.c"
    break;

  case 51: /* DecList: Dec  */
#line 259 "./syntax.y"
      { (yyval.node) = new_nonterm("DecList", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2014 "./syntax.tab.c"
    break;

  case 52: /* DecList: Dec COMMA DecList  */
#line 261 "./syntax.y"
      { (yyval.node) = new_nonterm("DecList", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2020 "./syntax.tab.c"
    break;

  case 53: /* DecList: Dec COMMA error  */
#line 263 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2030 "./syntax.tab.c"
    break;

  case 54: /* Dec: VarDec  */
#line 272 "./syntax.y"
      { (yyval.node) = new_nonterm("Dec", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2036 "./syntax.tab.c"
    break;

  case 55: /* Dec: VarDec ASSIGNOP Exp  */
#line 274 "./syntax.y"
      { (yyval.node) = new_nonterm("Dec", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2042 "./syntax.tab.c"
    break;

  case 56: /* Dec: VarDec ASSIGNOP error  */
#line 276 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2052 "./syntax.tab.c"
    break;

  case 57: /* Exp: Exp ASSIGNOP Exp  */
#line 285 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2058 "./syntax.tab.c"
    break;

  case 58: /* Exp: Exp AND Exp  */
#line 287 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2064 "./syntax.tab.c"
    break;

  case 59: /* Exp: Exp OR Exp  */
#line 289 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2070 "./syntax.tab.c"
    break;

  case 60: /* Exp: Exp RELOP Exp  */
#line 291 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2076 "./syntax.tab.c"
    break;

  case 61: /* Exp: Exp PLUS Exp  */
#line 293 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2082 "./syntax.tab.c"
    break;

  case 62: /* Exp: Exp MINUS Exp  */
#line 295 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2088 "./syntax.tab.c"
    break;

  case 63: /* Exp: Exp STAR Exp  */
#line 297 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2094 "./syntax.tab.c"
    break;

  case 64: /* Exp: Exp DIV Exp  */
#line 299 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2100 "./syntax.tab.c"
    break;

  case 65: /* Exp: LP Exp RP  */
#line 301 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2106 "./syntax.tab.c"
    break;

  case 66: /* Exp: MINUS Exp  */
#line 303 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2112 "./syntax.tab.c"
    break;

  case 67: /* Exp: NOT Exp  */
#line 305 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-1]).first_line, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2118 "./syntax.tab.c"
    break;

  case 68: /* Exp: ID LP Args RP  */
#line 307 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-3]).first_line, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2124 "./syntax.tab.c"
    break;

  case 69: /* Exp: ID LP RP  */
#line 309 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2130 "./syntax.tab.c"
    break;

  case 70: /* Exp: ID LP error RP  */
#line 311 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Invalid function call.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2140 "./syntax.tab.c"
    break;

  case 71: /* Exp: Exp LB Exp RB  */
#line 317 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-3]).first_line, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2146 "./syntax.tab.c"
    break;

  case 72: /* Exp: Exp LB error RB  */
#line 319 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Missing \"]\".");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2156 "./syntax.tab.c"
    break;

  case 73: /* Exp: Exp RELOP error  */
#line 325 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Syntax error.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2166 "./syntax.tab.c"
    break;

  case 74: /* Exp: Exp DOT ID  */
#line 331 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2172 "./syntax.tab.c"
    break;

  case 75: /* Exp: ID  */
#line 333 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2178 "./syntax.tab.c"
    break;

  case 76: /* Exp: INT  */
#line 335 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2184 "./syntax.tab.c"
    break;

  case 77: /* Exp: FLOAT  */
#line 337 "./syntax.y"
      { (yyval.node) = new_nonterm("Exp", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2190 "./syntax.tab.c"
    break;

  case 78: /* Args: Exp COMMA Args  */
#line 342 "./syntax.y"
      { (yyval.node) = new_nonterm("Args", (yylsp[-2]).first_line, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2196 "./syntax.tab.c"
    break;

  case 79: /* Args: Exp  */
#line 344 "./syntax.y"
      { (yyval.node) = new_nonterm("Args", (yylsp[0]).first_line, 1, (yyvsp[0].node)); }
#line 2202 "./syntax.tab.c"
    break;

  case 80: /* Args: Exp COMMA error  */
#line 346 "./syntax.y"
      {
          report_syntax_error_line((yylsp[0]).first_line, "Invalid function call.");
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2212 "./syntax.tab.c"
    break;


#line 2216 "./syntax.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 353 "./syntax.y"


void yyerror(const char *s){
    extern YYLTYPE yylloc;
    report_syntax_error_line(yylloc.first_line, s);
}

#include "lex.yy.c"
