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
#line 3 "parser.y"



#ifdef _WIN32
#  ifndef WIN32
#    define WIN32
#  endif
#endif


#ifdef __cplusplus

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#else

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#endif


#define __PARSER_H_INTERNAL_INCLUDE
#include "parser.h"


static GenericPointer * globalAllocMem = NULL;
static size_t globalAllocCount = 0;
static size_t globalAllocSize  = 0;
static bool needsFree = false;
static command_t * command_root = NULL;


void yyerror(const char* str);


static void ensureSize(size_t newSize)
{
	GenericPointer * newPtr;
	assert(newSize > 0);

	if (globalAllocSize == 0) {
		assert(globalAllocMem == NULL);
		globalAllocSize = newSize;
		globalAllocMem = (GenericPointer *)malloc(sizeof(GenericPointer) * globalAllocSize);
		if (globalAllocMem == NULL) {
			fprintf(stderr, "malloc() failed\n");
			exit(EXIT_FAILURE);
		}

		return;
	}

	assert(globalAllocMem != NULL);
	if (globalAllocSize >= newSize) {
		return;
	}

	globalAllocSize += newSize;
	newPtr = (GenericPointer *)realloc((void *)globalAllocMem, sizeof(GenericPointer) * globalAllocSize);
	if (newPtr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	globalAllocMem = newPtr;
}


void pointerToMallocMemory(const void * ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	ensureSize(globalAllocCount + 1);
	globalAllocMem[globalAllocCount++] = (GenericPointer)ptr;
}


static simple_command_t * bind_parts(word_t * exe_name, word_t * params, redirect_t red)
{
	simple_command_t * s = (simple_command_t *) malloc(sizeof(simple_command_t));
	pointerToMallocMemory(s);

	memset(s, 0, sizeof(*s));
	assert(exe_name != NULL);
	assert(exe_name->next_word == NULL);
	s->verb = exe_name;
	s->params = params;
	s->in = red.red_i;
	s->out = red.red_o;
	s->err = red.red_e;
	s->io_flags = red.red_flags;
	s->up = NULL;
	s->aux = NULL;
	return s;
}


static command_t * new_command(simple_command_t * scmd)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));

	if (c == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = c->cmd1 = c->cmd2 = NULL;
	c->op = OP_NONE;
	assert(scmd != NULL);
	c->scmd = scmd;
	scmd->up = c;
	c->aux = NULL;
	return c;
}


static command_t * bind_commands(command_t * cmd1, command_t * cmd2, operator_t op)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = NULL;
	assert(cmd1 != NULL);
	assert(cmd1->up == NULL);
	c->cmd1 = cmd1;
	cmd1->up = c;
	assert(cmd2 != NULL);
	assert(cmd2->up == NULL);
	assert(cmd1 != cmd2);
	c->cmd2 = cmd2;
	cmd2->up = c;
	assert((op > OP_NONE) && (op < OP_DUMMY));
	c->op = op;
	c->scmd = NULL;
	c->aux = NULL;

	return c;
}


static word_t * new_word(const char * str, bool expand)
{
	word_t * w = (word_t *) malloc(sizeof(word_t));
	pointerToMallocMemory(w);

	memset(w, 0, sizeof(*w));
	assert(str != NULL);
	w->string = str;
	w->expand = expand;
	w->next_part = NULL;
	w->next_word = NULL;

	return w;
}


static word_t * add_part_to_word(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(lst != NULL);
	assert(w != NULL);

	/*
	 we could insert at the beginnig and then invert the list
	 but this would make the code a bit more complicated
	 thus, we assume we have small lists and O(n*n) is acceptable
	*/

	while (crt->next_part != NULL) {
		crt = crt->next_part;
		assert((crt == NULL) || (crt->next_word == NULL));
	}

	crt->next_part = w;
	assert(w->next_part == NULL);
	assert(w->next_word == NULL);

	return lst;
}


static word_t * add_word_to_list(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(w != NULL);

	if (crt == NULL) {
		assert(w->next_word == NULL);
		return w;
	}
	assert(lst != NULL);

	/*
	 same as above
	*/
	while (crt->next_word != NULL) {
		crt = crt->next_word;
	}

	crt->next_word = w;
	assert(w->next_word == NULL);

	return lst;
}



#line 293 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NOT_ACCEPTED_CHAR = 3,          /* NOT_ACCEPTED_CHAR  */
  YYSYMBOL_INVALID_ENVIRONMENT_VAR = 4,    /* INVALID_ENVIRONMENT_VAR  */
  YYSYMBOL_UNEXPECTED_EOF = 5,             /* UNEXPECTED_EOF  */
  YYSYMBOL_CHARS_AFTER_EOL = 6,            /* CHARS_AFTER_EOL  */
  YYSYMBOL_END_OF_FILE = 7,                /* END_OF_FILE  */
  YYSYMBOL_END_OF_LINE = 8,                /* END_OF_LINE  */
  YYSYMBOL_BLANK = 9,                      /* BLANK  */
  YYSYMBOL_REDIRECT_OE = 10,               /* REDIRECT_OE  */
  YYSYMBOL_REDIRECT_O = 11,                /* REDIRECT_O  */
  YYSYMBOL_REDIRECT_E = 12,                /* REDIRECT_E  */
  YYSYMBOL_INDIRECT = 13,                  /* INDIRECT  */
  YYSYMBOL_REDIRECT_APPEND_E = 14,         /* REDIRECT_APPEND_E  */
  YYSYMBOL_REDIRECT_APPEND_O = 15,         /* REDIRECT_APPEND_O  */
  YYSYMBOL_WORD = 16,                      /* WORD  */
  YYSYMBOL_ENV_VAR = 17,                   /* ENV_VAR  */
  YYSYMBOL_SEQUENTIAL = 18,                /* SEQUENTIAL  */
  YYSYMBOL_PARALLEL = 19,                  /* PARALLEL  */
  YYSYMBOL_CONDITIONAL_NZERO = 20,         /* CONDITIONAL_NZERO  */
  YYSYMBOL_CONDITIONAL_ZERO = 21,          /* CONDITIONAL_ZERO  */
  YYSYMBOL_PIPE = 22,                      /* PIPE  */
  YYSYMBOL_YYACCEPT = 23,                  /* $accept  */
  YYSYMBOL_command_tree = 24,              /* command_tree  */
  YYSYMBOL_command = 25,                   /* command  */
  YYSYMBOL_simple_command = 26,            /* simple_command  */
  YYSYMBOL_exe_name = 27,                  /* exe_name  */
  YYSYMBOL_params = 28,                    /* params  */
  YYSYMBOL_redirect = 29,                  /* redirect  */
  YYSYMBOL_word = 30                       /* word  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  23
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  75

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   261,   261,   266,   271,   276,   281,   286,   295,   299,
     303,   307,   311,   315,   323,   327,   331,   335,   343,   347,
     355,   360,   367,   374,   380,   385,   390,   396,   402,   407,
     413,   418,   423,   429,   435,   440,   446,   451,   456,   462,
     468,   472,   478,   483,   488,   494,   500,   509,   513,   517,
     521
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NOT_ACCEPTED_CHAR",
  "INVALID_ENVIRONMENT_VAR", "UNEXPECTED_EOF", "CHARS_AFTER_EOL",
  "END_OF_FILE", "END_OF_LINE", "BLANK", "REDIRECT_OE", "REDIRECT_O",
  "REDIRECT_E", "INDIRECT", "REDIRECT_APPEND_E", "REDIRECT_APPEND_O",
  "WORD", "ENV_VAR", "SEQUENTIAL", "PARALLEL", "CONDITIONAL_NZERO",
  "CONDITIONAL_ZERO", "PIPE", "$accept", "command_tree", "command",
  "simple_command", "exe_name", "params", "redirect", "word", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-22)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      44,   -22,   -22,    14,   -22,   -22,    10,    -5,   -22,     3,
     100,   -22,   -22,   100,   -22,   -22,   -22,     9,     9,     9,
       9,     9,   113,    -6,   -22,   -22,   113,   106,     7,     2,
       2,   -22,    30,    -6,   100,    38,    40,    49,    53,    55,
      58,   113,    -6,   113,    64,   113,    67,   113,    69,   113,
      73,   113,    78,   113,    82,    -6,   100,    84,   -22,    87,
     -22,    93,   -22,    96,   -22,    98,   -22,   102,   -22,   -22,
     -22,   -22,   -22,   -22,   -22
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     4,     0,    49,    50,     0,     0,     8,    22,
      18,     7,     6,    19,     1,     3,     2,     0,     0,     0,
       0,     0,    22,    16,    47,    48,     0,     9,    10,    12,
      11,    13,    22,    17,    21,     0,     0,     0,     0,     0,
       0,    22,    14,     0,    23,     0,    25,     0,    24,     0,
      28,     0,    26,     0,    27,    15,    20,    35,    29,    37,
      31,    36,    30,    40,    34,    38,    32,    39,    33,    41,
      43,    42,    46,    45,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -22,   -22,   103,   -22,   -22,   -22,   -21,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    32,    23,    10
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      13,    33,    15,    16,    35,    36,    37,    38,    39,    40,
      14,    42,    22,    17,    18,    19,    20,    21,    26,    34,
      55,    11,    12,    13,    21,     4,     5,    19,    20,    21,
       4,     5,    44,    46,    48,    50,    52,    54,    56,    41,
      57,     0,    59,     0,    61,     0,    63,    43,    65,    45,
      67,     1,     2,     3,     4,     5,     4,     5,    47,     0,
       4,     5,    49,     0,    51,     4,     5,    53,     0,     4,
       5,     4,     5,    58,     4,     5,    60,     0,    62,     0,
      24,    25,    64,    24,    25,    24,    25,    66,     0,    24,
      25,    68,     0,    69,    24,    25,    70,     0,    24,    25,
      24,    25,    71,    24,    25,    72,     0,    73,     0,    24,
      25,    74,    24,    25,    24,    25,    24,    25,    24,    25,
      27,    28,    29,    30,    31,    18,    19,    20,    21,     4,
       5
};

static const yytype_int8 yycheck[] =
{
       3,    22,     7,     8,    10,    11,    12,    13,    14,    15,
       0,    32,     9,    18,    19,    20,    21,    22,     9,    22,
      41,     7,     8,    26,    22,    16,    17,    20,    21,    22,
      16,    17,    35,    36,    37,    38,    39,    40,    41,     9,
      43,    -1,    45,    -1,    47,    -1,    49,     9,    51,     9,
      53,     7,     8,     9,    16,    17,    16,    17,     9,    -1,
      16,    17,     9,    -1,     9,    16,    17,     9,    -1,    16,
      17,    16,    17,     9,    16,    17,     9,    -1,     9,    -1,
      16,    17,     9,    16,    17,    16,    17,     9,    -1,    16,
      17,     9,    -1,     9,    16,    17,     9,    -1,    16,    17,
      16,    17,     9,    16,    17,     9,    -1,     9,    -1,    16,
      17,     9,    16,    17,    16,    17,    16,    17,    16,    17,
      17,    18,    19,    20,    21,    19,    20,    21,    22,    16,
      17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    16,    17,    24,    25,    26,    27,
      30,     7,     8,    30,     0,     7,     8,    18,    19,    20,
      21,    22,     9,    29,    16,    17,     9,    25,    25,    25,
      25,    25,    28,    29,    30,    10,    11,    12,    13,    14,
      15,     9,    29,     9,    30,     9,    30,     9,    30,     9,
      30,     9,    30,     9,    30,    29,    30,    30,     9,    30,
       9,    30,     9,    30,     9,    30,     9,    30,     9,     9,
       9,     9,     9,     9,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    23,    24,    24,    24,    24,    24,    24,    25,    25,
      25,    25,    25,    25,    26,    26,    26,    26,    27,    27,
      28,    28,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    30,    30,    30,
      30
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     2,     2,     1,     3,
       3,     3,     3,     3,     4,     5,     2,     3,     1,     2,
       3,     1,     0,     3,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     5,     5,     5,     5,     5,     5,     2,     2,     1,
       1
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
  case 2: /* command_tree: command END_OF_LINE  */
#line 261 "parser.y"
                              {
		command_root = (yyvsp[-1].command_un);
		YYACCEPT;
	}
#line 1484 "parser.tab.c"
    break;

  case 3: /* command_tree: command END_OF_FILE  */
#line 266 "parser.y"
                              {
		command_root = (yyvsp[-1].command_un);
		YYACCEPT;
	}
#line 1493 "parser.tab.c"
    break;

  case 4: /* command_tree: END_OF_LINE  */
#line 271 "parser.y"
                      {
		command_root = NULL;
		YYACCEPT;
	}
#line 1502 "parser.tab.c"
    break;

  case 5: /* command_tree: END_OF_FILE  */
#line 276 "parser.y"
                      {
		command_root = NULL;
		YYACCEPT;
	}
#line 1511 "parser.tab.c"
    break;

  case 6: /* command_tree: BLANK END_OF_LINE  */
#line 281 "parser.y"
                            {
		command_root = NULL;
		YYACCEPT;
	}
#line 1520 "parser.tab.c"
    break;

  case 7: /* command_tree: BLANK END_OF_FILE  */
#line 286 "parser.y"
                            {
		command_root = NULL;
		YYACCEPT;
	}
#line 1529 "parser.tab.c"
    break;

  case 8: /* command: simple_command  */
#line 295 "parser.y"
                         {
		(yyval.command_un) = new_command((yyvsp[0].simple_command_un));
	}
#line 1537 "parser.tab.c"
    break;

  case 9: /* command: command SEQUENTIAL command  */
#line 299 "parser.y"
                                     {
		(yyval.command_un) = bind_commands((yyvsp[-2].command_un), (yyvsp[0].command_un), OP_SEQUENTIAL);
	}
#line 1545 "parser.tab.c"
    break;

  case 10: /* command: command PARALLEL command  */
#line 303 "parser.y"
                                   {
		(yyval.command_un) = bind_commands((yyvsp[-2].command_un), (yyvsp[0].command_un), OP_PARALLEL);
	}
#line 1553 "parser.tab.c"
    break;

  case 11: /* command: command CONDITIONAL_ZERO command  */
#line 307 "parser.y"
                                           {
		(yyval.command_un) = bind_commands((yyvsp[-2].command_un), (yyvsp[0].command_un), OP_CONDITIONAL_ZERO);
	}
#line 1561 "parser.tab.c"
    break;

  case 12: /* command: command CONDITIONAL_NZERO command  */
#line 311 "parser.y"
                                            {
		(yyval.command_un) = bind_commands((yyvsp[-2].command_un), (yyvsp[0].command_un), OP_CONDITIONAL_NZERO);
	}
#line 1569 "parser.tab.c"
    break;

  case 13: /* command: command PIPE command  */
#line 315 "parser.y"
                               {
		(yyval.command_un) = bind_commands((yyvsp[-2].command_un), (yyvsp[0].command_un), OP_PIPE);
	}
#line 1577 "parser.tab.c"
    break;

  case 14: /* simple_command: exe_name BLANK params redirect  */
#line 323 "parser.y"
                                         {
		(yyval.simple_command_un) = bind_parts((yyvsp[-3].exe_un), (yyvsp[-1].params_un), (yyvsp[0].redirect_un));
	}
#line 1585 "parser.tab.c"
    break;

  case 15: /* simple_command: exe_name BLANK params BLANK redirect  */
#line 327 "parser.y"
                                               {
		(yyval.simple_command_un) = bind_parts((yyvsp[-4].exe_un), (yyvsp[-2].params_un), (yyvsp[0].redirect_un));
	}
#line 1593 "parser.tab.c"
    break;

  case 16: /* simple_command: exe_name redirect  */
#line 331 "parser.y"
                            {
		(yyval.simple_command_un) = bind_parts((yyvsp[-1].exe_un), NULL, (yyvsp[0].redirect_un));
	}
#line 1601 "parser.tab.c"
    break;

  case 17: /* simple_command: exe_name BLANK redirect  */
#line 335 "parser.y"
                                  {
		(yyval.simple_command_un) = bind_parts((yyvsp[-2].exe_un), NULL, (yyvsp[0].redirect_un));
	}
#line 1609 "parser.tab.c"
    break;

  case 18: /* exe_name: word  */
#line 343 "parser.y"
               {
		(yyval.exe_un) = (yyvsp[0].word_un);
	}
#line 1617 "parser.tab.c"
    break;

  case 19: /* exe_name: BLANK word  */
#line 347 "parser.y"
                     {
		(yyval.exe_un) = (yyvsp[0].word_un);
	}
#line 1625 "parser.tab.c"
    break;

  case 20: /* params: params BLANK word  */
#line 355 "parser.y"
                            {
		(yyval.params_un) = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].params_un));
		assert((yyval.params_un) == (yyvsp[-2].params_un));
	}
#line 1634 "parser.tab.c"
    break;

  case 21: /* params: word  */
#line 360 "parser.y"
               {
		(yyval.params_un) = (yyvsp[0].word_un);
	}
#line 1642 "parser.tab.c"
    break;

  case 22: /* redirect: %empty  */
#line 367 "parser.y"
          { /* empty */
		(yyval.redirect_un).red_o = NULL;
		(yyval.redirect_un).red_i = NULL;
		(yyval.redirect_un).red_e = NULL;
		(yyval.redirect_un).red_flags = IO_REGULAR;
	}
#line 1653 "parser.tab.c"
    break;

  case 23: /* redirect: redirect REDIRECT_OE word  */
#line 374 "parser.y"
                                    {
		(yyvsp[-2].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_o);
		(yyvsp[-2].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1663 "parser.tab.c"
    break;

  case 24: /* redirect: redirect REDIRECT_E word  */
#line 380 "parser.y"
                                   {
		(yyvsp[-2].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1672 "parser.tab.c"
    break;

  case 25: /* redirect: redirect REDIRECT_O word  */
#line 385 "parser.y"
                                   {
		(yyvsp[-2].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_o);
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1681 "parser.tab.c"
    break;

  case 26: /* redirect: redirect REDIRECT_APPEND_E word  */
#line 390 "parser.y"
                                          {
		(yyvsp[-2].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_e);
		(yyvsp[-2].redirect_un).red_flags |= IO_ERR_APPEND;
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1691 "parser.tab.c"
    break;

  case 27: /* redirect: redirect REDIRECT_APPEND_O word  */
#line 396 "parser.y"
                                          {
		(yyvsp[-2].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_o);
		(yyvsp[-2].redirect_un).red_flags |= IO_OUT_APPEND;
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1701 "parser.tab.c"
    break;

  case 28: /* redirect: redirect INDIRECT word  */
#line 402 "parser.y"
                                 {
		(yyvsp[-2].redirect_un).red_i = add_word_to_list((yyvsp[0].word_un), (yyvsp[-2].redirect_un).red_i);
		(yyval.redirect_un) = (yyvsp[-2].redirect_un);
	}
#line 1710 "parser.tab.c"
    break;

  case 29: /* redirect: redirect REDIRECT_OE word BLANK  */
#line 407 "parser.y"
                                          {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1720 "parser.tab.c"
    break;

  case 30: /* redirect: redirect REDIRECT_E word BLANK  */
#line 413 "parser.y"
                                         {
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1729 "parser.tab.c"
    break;

  case 31: /* redirect: redirect REDIRECT_O word BLANK  */
#line 418 "parser.y"
                                         {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1738 "parser.tab.c"
    break;

  case 32: /* redirect: redirect REDIRECT_APPEND_E word BLANK  */
#line 423 "parser.y"
                                                {
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyvsp[-3].redirect_un).red_flags |= IO_ERR_APPEND;
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1748 "parser.tab.c"
    break;

  case 33: /* redirect: redirect REDIRECT_APPEND_O word BLANK  */
#line 429 "parser.y"
                                                {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyvsp[-3].redirect_un).red_flags |= IO_OUT_APPEND;
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1758 "parser.tab.c"
    break;

  case 34: /* redirect: redirect INDIRECT word BLANK  */
#line 435 "parser.y"
                                       {
		(yyvsp[-3].redirect_un).red_i = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-3].redirect_un).red_i);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1767 "parser.tab.c"
    break;

  case 35: /* redirect: redirect REDIRECT_OE BLANK word  */
#line 440 "parser.y"
                                          {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1777 "parser.tab.c"
    break;

  case 36: /* redirect: redirect REDIRECT_E BLANK word  */
#line 446 "parser.y"
                                         {
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1786 "parser.tab.c"
    break;

  case 37: /* redirect: redirect REDIRECT_O BLANK word  */
#line 451 "parser.y"
                                         {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1795 "parser.tab.c"
    break;

  case 38: /* redirect: redirect REDIRECT_APPEND_E BLANK word  */
#line 456 "parser.y"
                                                {
		(yyvsp[-3].redirect_un).red_e = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_e);
		(yyvsp[-3].redirect_un).red_flags |= IO_ERR_APPEND;
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1805 "parser.tab.c"
    break;

  case 39: /* redirect: redirect REDIRECT_APPEND_O BLANK word  */
#line 462 "parser.y"
                                                {
		(yyvsp[-3].redirect_un).red_o = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_o);
		(yyvsp[-3].redirect_un).red_flags |= IO_OUT_APPEND;
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1815 "parser.tab.c"
    break;

  case 40: /* redirect: redirect INDIRECT BLANK word  */
#line 468 "parser.y"
                                       {
		(yyvsp[-3].redirect_un).red_i = add_word_to_list((yyvsp[0].word_un), (yyvsp[-3].redirect_un).red_i);
		(yyval.redirect_un) = (yyvsp[-3].redirect_un);
	}
#line 1824 "parser.tab.c"
    break;

  case 41: /* redirect: redirect REDIRECT_OE BLANK word BLANK  */
#line 472 "parser.y"
                                                {
		(yyvsp[-4].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_o);
		(yyvsp[-4].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1834 "parser.tab.c"
    break;

  case 42: /* redirect: redirect REDIRECT_E BLANK word BLANK  */
#line 478 "parser.y"
                                               {
		(yyvsp[-4].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_e);
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1843 "parser.tab.c"
    break;

  case 43: /* redirect: redirect REDIRECT_O BLANK word BLANK  */
#line 483 "parser.y"
                                               {
		(yyvsp[-4].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_o);
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1852 "parser.tab.c"
    break;

  case 44: /* redirect: redirect REDIRECT_APPEND_O BLANK word BLANK  */
#line 488 "parser.y"
                                                      {
		(yyvsp[-4].redirect_un).red_o = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_o);
		(yyvsp[-4].redirect_un).red_flags |= IO_OUT_APPEND;
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1862 "parser.tab.c"
    break;

  case 45: /* redirect: redirect REDIRECT_APPEND_E BLANK word BLANK  */
#line 494 "parser.y"
                                                      {
		(yyvsp[-4].redirect_un).red_e = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_e);
		(yyvsp[-4].redirect_un).red_flags |= IO_ERR_APPEND;
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1872 "parser.tab.c"
    break;

  case 46: /* redirect: redirect INDIRECT BLANK word BLANK  */
#line 500 "parser.y"
                                             {
		(yyvsp[-4].redirect_un).red_i = add_word_to_list((yyvsp[-1].word_un), (yyvsp[-4].redirect_un).red_i);
		(yyval.redirect_un) = (yyvsp[-4].redirect_un);
	}
#line 1881 "parser.tab.c"
    break;

  case 47: /* word: word WORD  */
#line 509 "parser.y"
                    {
		(yyval.word_un) = add_part_to_word(new_word((yyvsp[0].string_un), false), (yyvsp[-1].word_un));
	}
#line 1889 "parser.tab.c"
    break;

  case 48: /* word: word ENV_VAR  */
#line 513 "parser.y"
                       {
		(yyval.word_un) = add_part_to_word(new_word((yyvsp[0].string_un), true), (yyvsp[-1].word_un));
	}
#line 1897 "parser.tab.c"
    break;

  case 49: /* word: WORD  */
#line 517 "parser.y"
               {
		(yyval.word_un) = new_word((yyvsp[0].string_un), false);
	}
#line 1905 "parser.tab.c"
    break;

  case 50: /* word: ENV_VAR  */
#line 521 "parser.y"
                  {
		(yyval.word_un) = new_word((yyvsp[0].string_un), true);
	}
#line 1913 "parser.tab.c"
    break;


#line 1917 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 526 "parser.y"



bool parse_line(const char * line, command_t ** root)
{
	if (*root != NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	if (line == NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	free_parse_memory();
	globalParseAnotherString(line);
	needsFree = true;
	command_root = NULL;

	yylloc.first_line = yylloc.last_line = 1;
	yylloc.first_column = yylloc.last_column = 0;

	if (yyparse() != 0) {
		/* yyparse failed */
		return false;
	}

	*root = command_root;

	return true;
}


void free_parse_memory()
{
	if (needsFree) {
		globalEndParsing();
		while (globalAllocCount != 0) {
			globalAllocCount--;
			assert(globalAllocMem[globalAllocCount] != NULL);
			free(globalAllocMem[globalAllocCount]);
			globalAllocMem[globalAllocCount] = NULL;
		}

		if (globalAllocMem != NULL) {
			free((void *)globalAllocMem);
			globalAllocMem = NULL;
		}

		globalAllocSize = 0;
		needsFree = false;
	}
}


void yyerror(const char* str)
{
	parse_error(str, yylloc.first_column);
}
