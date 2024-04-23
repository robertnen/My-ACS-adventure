#lang racket

(provide (all-defined-out))

; Fișierul acesta conține date folosite pentru testare.
; Este separat de checker pentru a face codul testelor mai ușor de citit.

; Legenda spune că cei care înțeleg acest text au șanse bune să treacă la PP.
(define text-big "In computer science, functional programming is a programming paradigm where programs are constructed by applying and composing functions. It is a declarative programming paradigm in which function definitions are trees of expressions that map values to other values, rather than a sequence of imperative statements which update the running state of the program.

In functional programming, functions are treated as first-class citizens, meaning that they can be bound to names (including local identifiers), passed as arguments, and returned from other functions, just as any other data type can. This allows programs to be written in a declarative and composable style, where small functions are combined in a modular manner.

Functional programming is sometimes treated as synonymous with purely functional programming, a subset of functional programming which treats all functions as deterministic mathematical functions, or pure functions. When a pure function is called with some given arguments, it will always return the same result, and cannot be affected by any mutable state or other side effects. This is in contrast with impure procedures, common in imperative programming, which can have side effects (such as modifying the program's state or taking input from a user). Proponents of purely functional programming claim that by restricting side effects, programs can have fewer bugs, be easier to debug and test, and be more suited to formal verification.[1][2]

Functional programming has its roots in academia, evolving from the lambda calculus, a formal system of computation based only on functions. Functional programming has historically been less popular than imperative programming, but many functional languages are seeing use today in industry and education, including Common Lisp, Scheme,[3][4][5][6] Clojure, Wolfram Language,[7][8] Racket,[9] Erlang,[10][11][12] Elixir,[13] OCaml,[14][15] Haskell,[16][17] and F#.[18][19] Functional programming is also key to some languages that have found success in specific domains, like JavaScript in the Web,[20] R in statistics,[21][22] J, K and Q in financial analysis, and XQuery/XSLT for XML.[23][24] Domain-specific declarative languages like SQL and Lex/Yacc use some elements of functional programming, such as not allowing mutable values.[25] In addition, many other programming languages support programming in a functional style or have implemented features from functional programming, such as C++11, C#,[26] Kotlin,[27] Perl,[28] PHP,[29] Python,[30] Go,[31] Rust,[32] Raku,[33] Scala,[34] and Java (since Java 8).[35]

History
The lambda calculus, developed in the 1930s by Alonzo Church, is a formal system of computation built from function application. In 1937 Alan Turing proved that the lambda calculus and Turing machines are equivalent models of computation,[36] showing that the lambda calculus is Turing complete. Lambda calculus forms the basis of all functional programming languages. An equivalent theoretical formulation, combinatory logic, was developed by Moses Schönfinkel and Haskell Curry in the 1920s and 1930s.[37]

Church later developed a weaker system, the simply-typed lambda calculus, which extended the lambda calculus by assigning a data type to all terms.[38] This forms the basis for statically typed functional programming.

The first high-level functional programming language, Lisp, was developed in the late 1950s for the IBM 700/7000 series of scientific computers by John McCarthy while at Massachusetts Institute of Technology (MIT).[39] Lisp functions were defined using Church's lambda notation, extended with a label construct to allow recursive functions.[40] Lisp first introduced many paradigmatic features of functional programming, though early Lisps were multi-paradigm languages, and incorporated support for numerous programming styles as new paradigms evolved. Later dialects, such as Scheme and Clojure, and offshoots such as Dylan and Julia, sought to simplify and rationalise Lisp around a cleanly functional core, while Common Lisp was designed to preserve and update the paradigmatic features of the numerous older dialects it replaced.[41]

Information Processing Language (IPL), 1956, is sometimes cited as the first computer-based functional programming language.[42] It is an assembly-style language for manipulating lists of symbols. It does have a notion of generator, which amounts to a function that accepts a function as an argument, and, since it is an assembly-level language, code can be data, so IPL can be regarded as having higher-order functions. However, it relies heavily on the mutating list structure and similar imperative features.

Kenneth E. Iverson developed APL in the early 1960s, described in his 1962 book A Programming Language (ISBN 9780471430148). APL was the primary influence on John Backus's FP. In the early 1990s, Iverson and Roger Hui created J. In the mid-1990s, Arthur Whitney, who had previously worked with Iverson, created K, which is used commercially in financial industries along with its descendant Q.

In the mid-1960s, Peter Landin invented SECD machine,[43] the first abstract machine for a functional programming language,[44] described a correspondence between ALGOL 60 and the lambda calculus,[45][46] and proposed the ISWIM programming language.[47]

John Backus presented FP in his 1977 Turing Award lecture Can Programming Be Liberated From the von Neumann Style? A Functional Style and its Algebra of Programs.[48] He defines functional programs as being built up in a hierarchical way by means of combining forms that allow an algebra of programs; in modern language, this means that functional programs follow the principle of compositionality.[citation needed] Backus's paper popularized research into functional programming, though it emphasized function-level programming rather than the lambda-calculus style now associated with functional programming.

The 1973 language ML was created by Robin Milner at the University of Edinburgh, and David Turner developed the language SASL at the University of St Andrews. Also in Edinburgh in the 1970s, Burstall and Darlington developed the functional language NPL.[49] NPL was based on Kleene Recursion Equations and was first introduced in their work on program transformation.[50] Burstall, MacQueen and Sannella then incorporated the polymorphic type checking from ML to produce the language Hope.[51] ML eventually developed into several dialects, the most common of which are now OCaml and Standard ML.

In the 1970s, Guy L. Steele and Gerald Jay Sussman developed Scheme, as described in the Lambda Papers and the 1985 textbook Structure and Interpretation of Computer Programs. Scheme was the first dialect of lisp to use lexical scoping and to require tail-call optimization, features that encourage functional programming.

In the 1980s, Per Martin-Löf developed intuitionistic type theory (also called constructive type theory), which associated functional programs with constructive proofs expressed as dependent types. This led to new approaches to interactive theorem proving and has influenced the development of subsequent functional programming languages.[citation needed]

The lazy functional language, Miranda, developed by David Turner, initially appeared in 1985 and had a strong influence on Haskell. With Miranda being proprietary, Haskell began with a consensus in 1987 to form an open standard for functional programming research; implementation releases have been ongoing as of 1990.

More recently it has found use in niches such as parametric CAD in the OpenSCAD language built on the CGAL framework, although its restriction on reassigning values (all values are treated as constants) has led to confusion among users who are unfamiliar with functional programming as a concept.[52]

Functional programming continues to be used in commercial settings.[53][54][55]

Concepts 
A number of concepts[56] and paradigms are specific to functional programming, and generally foreign to imperative programming (including object-oriented programming). However, programming languages often cater to several programming paradigms, so programmers using mostly imperative languages may have utilized some of these concepts.[57]

First-class and higher-order functions
Main articles: First-class function and Higher-order function
Higher-order functions are functions that can either take other functions as arguments or return them as results. In calculus, an example of a higher-order function is the differential operator 

Higher-order functions are closely related to first-class functions in that higher-order functions and first-class functions both allow functions as arguments and results of other functions. The distinction between the two is subtle: higher-order describes a mathematical concept of functions that operate on other functions, while first-class is a computer science term for programming language entities that have no restriction on their use (thus first-class functions can appear anywhere in the program that other first-class entities like numbers can, including as arguments to other functions and as their return values).

Higher-order functions enable partial application or currying, a technique that applies a function to its arguments one at a time, with each application returning a new function that accepts the next argument. This lets a programmer succinctly express, for example, the successor function as the addition operator partially applied to the natural number one.

Pure functions
Main article: Pure function
Pure functions (or expressions) have no side effects (memory or I/O). This means that pure functions have several useful properties, many of which can be used to optimize the code:

If the result of a pure expression is not used, it can be removed without affecting other expressions.
If a pure function is called with arguments that cause no side-effects, the result is constant with respect to that argument list (sometimes called referential transparency or idempotence), i.e., calling the pure function again with the same arguments returns the same result. (This can enable caching optimizations such as memoization.)
If there is no data dependency between two pure expressions, their order can be reversed, or they can be performed in parallel and they cannot interfere with one another (in other terms, the evaluation of any pure expression is thread-safe).
If the entire language does not allow side-effects, then any evaluation strategy can be used; this gives the compiler freedom to reorder or combine the evaluation of expressions in a program (for example, using deforestation).
While most compilers for imperative programming languages detect pure functions and perform common-subexpression elimination for pure function calls, they cannot always do this for pre-compiled libraries, which generally do not expose this information, thus preventing optimizations that involve those external functions. Some compilers, such as gcc, add extra keywords for a programmer to explicitly mark external functions as pure, to enable such optimizations. Fortran 95 also lets functions be designated pure.[58] C++11 added constexpr keyword with similar semantics.

Recursion
Main article: Recursion (computer science)
Iteration (looping) in functional languages is usually accomplished via recursion. Recursive functions invoke themselves, letting an operation be repeated until it reaches the base case. In general, recursion requires maintaining a stack, which consumes space in a linear amount to the depth of recursion. This could make recursion prohibitively expensive to use instead of imperative loops. However, a special form of recursion known as tail recursion can be recognized and optimized by a compiler into the same code used to implement iteration in imperative languages. Tail recursion optimization can be implemented by transforming the program into continuation passing style during compiling, among other approaches.

The Scheme language standard requires implementations to support proper tail recursion, meaning they must allow an unbounded number of active tail calls.[59][60] Proper tail recursion is not simply an optimization; it is a language feature that assures users that they can use recursion to express a loop and doing so would be safe-for-space.[61] Moreover, contrary to its name, it accounts for all tail calls, not just tail recursion. While proper tail recursion is usually implemented by turning code into imperative loops, implementations might implement it in other ways. For example, Chicken intentionally maintains a stack and lets the stack overflow. However, when this happens, its garbage collector will claim space back,[62] allowing an unbounded number of active tail calls even though it does not turn tail recursion into a loop.

Common patterns of recursion can be abstracted away using higher-order functions, with catamorphisms and anamorphisms (or folds and unfolds) being the most obvious examples. Such recursion schemes play a role analogous to built-in control structures such as loops in imperative languages.

Most general purpose functional programming languages allow unrestricted recursion and are Turing complete, which makes the halting problem undecidable, can cause unsoundness of equational reasoning, and generally requires the introduction of inconsistency into the logic expressed by the language's type system. Some special purpose languages such as Coq allow only well-founded recursion and are strongly normalizing (nonterminating computations can be expressed only with infinite streams of values called codata). As a consequence, these languages fail to be Turing complete and expressing certain functions in them is impossible, but they can still express a wide class of interesting computations while avoiding the problems introduced by unrestricted recursion. Functional programming limited to well-founded recursion with a few other constraints is called total functional programming.[63]

Strict versus non-strict evaluation
Main article: Evaluation strategy
Functional languages can be categorized by whether they use strict (eager) or non-strict (lazy) evaluation, concepts that refer to how function arguments are processed when an expression is being evaluated. The technical difference is in the denotational semantics of expressions containing failing or divergent computations. Under strict evaluation, the evaluation of any term containing a failing subterm fails. For example, the expression:

print length([2+1, 3*2, 1/0, 5-4])
fails under strict evaluation because of the division by zero in the third element of the list. Under lazy evaluation, the length function returns the value 4 (i.e., the number of items in the list), since evaluating it does not attempt to evaluate the terms making up the list. In brief, strict evaluation always fully evaluates function arguments before invoking the function. Lazy evaluation does not evaluate function arguments unless their values are required to evaluate the function call itself.

The usual implementation strategy for lazy evaluation in functional languages is graph reduction.[64] Lazy evaluation is used by default in several pure functional languages, including Miranda, Clean, and Haskell.

Hughes 1984 argues for lazy evaluation as a mechanism for improving program modularity through separation of concerns, by easing independent implementation of producers and consumers of data streams.[2] Launchbury 1993 describes some difficulties that lazy evaluation introduces, particularly in analyzing a program's storage requirements, and proposes an operational semantics to aid in such analysis.[65] Harper 2009 proposes including both strict and lazy evaluation in the same language, using the language's type system to distinguish them.[66]

Type systems
Main article: Type system
Especially since the development of Hindley–Milner type inference in the 1970s, functional programming languages have tended to use typed lambda calculus, rejecting all invalid programs at compilation time and risking false positive errors, as opposed to the untyped lambda calculus, that accepts all valid programs at compilation time and risks false negative errors, used in Lisp and its variants (such as Scheme), as they reject all invalid programs at runtime when the information is enough to not reject valid programs. The use of algebraic datatypes makes manipulation of complex data structures convenient; the presence of strong compile-time type checking makes programs more reliable in absence of other reliability techniques like test-driven development, while type inference frees the programmer from the need to manually declare types to the compiler in most cases.

Some research-oriented functional languages such as Coq, Agda, Cayenne, and Epigram are based on intuitionistic type theory, which lets types depend on terms. Such types are called dependent types. These type systems do not have decidable type inference and are difficult to understand and program with.[67][68][69][70] But dependent types can express arbitrary propositions in higher-order logic. Through the Curry–Howard isomorphism, then, well-typed programs in these languages become a means of writing formal mathematical proofs from which a compiler can generate certified code. While these languages are mainly of interest in academic research (including in formalized mathematics), they have begun to be used in engineering as well. Compcert is a compiler for a subset of the C programming language that is written in Coq and formally verified.[71]

A limited form of dependent types called generalized algebraic data types (GADT's) can be implemented in a way that provides some of the benefits of dependently typed programming while avoiding most of its inconvenience.[72] GADT's are available in the Glasgow Haskell Compiler, in OCaml[73] and in Scala,[74] and have been proposed as additions to other languages including Java and C#.[75]

Referential transparency
Main article: Referential transparency
Functional programs do not have assignment statements, that is, the value of a variable in a functional program never changes once defined. This eliminates any chances of side effects because any variable can be replaced with its actual value at any point of execution. So, functional programs are referentially transparent.[76]

Consider C assignment statement x=x * 10, this changes the value assigned to the variable x. Let us say that the initial value of x was 1, then two consecutive evaluations of the variable x yields 10 and 100 respectively. Clearly, replacing x=x * 10 with either 10 or 100 gives a program a different meaning, and so the expression is not referentially transparent. In fact, assignment statements are never referentially transparent.

Now, consider another function such as int plusone(int x) {return x+1;} is transparent, as it does not implicitly change the input x and thus has no such side effects. Functional programs exclusively use this type of function and are therefore referentially transparent.

Data structures
Main article: Purely functional data structure
Purely functional data structures are often represented in a different way to their imperative counterparts.[77] For example, the array with constant access and update times is a basic component of most imperative languages, and many imperative data-structures, such as the hash table and binary heap, are based on arrays. Arrays can be replaced by maps or random access lists, which admit purely functional implementation, but have logarithmic access and update times. Purely functional data structures have persistence, a property of keeping previous versions of the data structure unmodified. In Clojure, persistent data structures are used as functional alternatives to their imperative counterparts. Persistent vectors, for example, use trees for partial updating. Calling the insert method will result in some but not all nodes being created.[78]

Comparison to imperative programming
Functional programming is very different from imperative programming. The most significant differences stem from the fact that functional programming avoids side effects, which are used in imperative programming to implement state and I/O. Pure functional programming completely prevents side-effects and provides referential transparency.

Higher-order functions are rarely used in older imperative programming. A traditional imperative program might use a loop to traverse and modify a list. A functional program, on the other hand, would probably use a higher-order map function that takes a function and a list, generating and returning a new list by applying the function to each list item.

Imperative vs. functional programming
The following two examples (written in JavaScript) achieve the same effect: they multiply all even numbers in an array by 10 and add them all, storing the final sum in the variable result.

Traditional Imperative Loop:

const numList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
let result = 0;
for (let i = 0; i < numList.length; i++) {
  if (numList[i] % 2 === 0) {
    result += numList[i] * 10;
  }
}
Functional Programming with higher-order functions:

const result = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
               .filter(n => n % 2 === 0)
               .map(a => a * 10)
               .reduce((a, b) => a + b, 0);
Simulating state
There are tasks (for example, maintaining a bank account balance) that often seem most naturally implemented with state. Pure functional programming performs these tasks, and I/O tasks such as accepting user input and printing to the screen, in a different way.

The pure functional programming language Haskell implements them using monads, derived from category theory.[79] Monads offer a way to abstract certain types of computational patterns, including (but not limited to) modeling of computations with mutable state (and other side effects such as I/O) in an imperative manner without losing purity. While existing monads may be easy to apply in a program, given appropriate templates and examples, many students find them difficult to understand conceptually, e.g., when asked to define new monads (which is sometimes needed for certain types of libraries).[80]

Functional languages also simulate states by passing around immutable states. This can be done by making a function accept the state as one of its parameters, and return a new state together with the result, leaving the old state unchanged.[81]

Impure functional languages usually include a more direct method of managing mutable state. Clojure, for example, uses managed references that can be updated by applying pure functions to the current state. This kind of approach enables mutability while still promoting the use of pure functions as the preferred way to express computations.[citation needed]

Alternative methods such as Hoare logic and uniqueness have been developed to track side effects in programs. Some modern research languages use effect systems to make the presence of side effects explicit.[citation needed]

Efficiency issues
Functional programming languages are typically less efficient in their use of CPU and memory than imperative languages such as C and Pascal.[82] This is related to the fact that some mutable data structures like arrays have a very straightforward implementation using present hardware. Flat arrays may be accessed very efficiently with deeply pipelined CPUs, prefetched efficiently through caches (with no complex pointer chasing), or handled with SIMD instructions. It is also not easy to create their equally efficient general-purpose immutable counterparts. For purely functional languages, the worst-case slowdown is logarithmic in the number of memory cells used, because mutable memory can be represented by a purely functional data structure with logarithmic access time (such as a balanced tree).[83] However, such slowdowns are not universal. For programs that perform intensive numerical computations, functional languages such as OCaml and Clean are only slightly slower than C according to The Computer Language Benchmarks Game.[84] For programs that handle large matrices and multidimensional databases, array functional languages (such as J and K) were designed with speed optimizations.

Immutability of data can in many cases lead to execution efficiency by allowing the compiler to make assumptions that are unsafe in an imperative language, thus increasing opportunities for inline expansion.[85]

Lazy evaluation may also speed up the program, even asymptotically, whereas it may slow it down at most by a constant factor (however, it may introduce memory leaks if used improperly). Launchbury 1993[65] discusses theoretical issues related to memory leaks from lazy evaluation, and O'Sullivan et al. 2008[86] give some practical advice for analyzing and fixing them. However, the most general implementations of lazy evaluation making extensive use of dereferenced code and data perform poorly on modern processors with deep pipelines and multi-level caches (where a cache miss may cost hundreds of cycles)[citation needed].

Functional programming in non-functional languages
It is possible to use a functional style of programming in languages that are not traditionally considered functional languages.[87] For example, both D[88] and Fortran 95[58] explicitly support pure functions.

JavaScript, Lua,[89] Python and Go[90] had first class functions from their inception.[91] Python had support for lambda, map, reduce, and filter in 1994, as well as closures in Python 2.2,[92] though Python 3 relegated reduce to the functools standard library module.[93] First-class functions have been introduced into other mainstream languages such as PHP 5.3, Visual Basic 9, C# 3.0, C++11, and Kotlin.[27][citation needed]

In PHP, anonymous classes, closures and lambdas are fully supported. Libraries and language extensions for immutable data structures are being developed to aid programming in the functional style.

In Java, anonymous classes can sometimes be used to simulate closures;[94] however, anonymous classes are not always proper replacements to closures because they have more limited capabilities.[95] Java 8 supports lambda expressions as a replacement for some anonymous classes.[96]

In C#, anonymous classes are not necessary, because closures and lambdas are fully supported. Libraries and language extensions for immutable data structures are being developed to aid programming in the functional style in C#.

Many object-oriented design patterns are expressible in functional programming terms: for example, the strategy pattern simply dictates use of a higher-order function, and the visitor pattern roughly corresponds to a catamorphism, or fold.

Similarly, the idea of immutable data from functional programming is often included in imperative programming languages,[97] for example the tuple in Python, which is an immutable array, and Object.freeze() in JavaScript.[98]

Comparison to logic programming
Logic programming can be viewed as a generalisation of functional programming, in which functions are a special case of relations.[99] For example, the function, mother(X) = Y, (every X has only one mother Y) can be represented by the relation mother(X, Y). Whereas functions have a strict input-output pattern of arguments, relations can be queried with any pattern of inputs and outputs. Consider the following logic program:

mother(charles, elizabeth).
mother(harry, diana).
The program can be queried, like a functional program, to generate mothers from children:

?- mother(harry, X).
X = diana.
?- mother(charles, X).
X = elizabeth.
But it can also be queried backwards, to generate children:

?- mother(X, elizabeth).
X = charles.
?- mother(X, diana).
X = harry.
It can even be used to generate all instances of the mother relation:

?- mother(X, Y).
X = charles,
Y = elizabeth.
X = harry,
Y = diana.
Compared with relational syntax, functional syntax is a more compact notation for nested functions. For example, the definition of maternal grandmother in functional syntax can be written in the nested form:

maternal_grandmother(X) = mother(mother(X)).
The same definition in relational notation needs to be written in the unnested form:

maternal_grandmother(X, Y) :- mother(X, Z), mother(Z, Y).
Here :- means if and , means and.

However, the difference between the two representations is simply syntactic. In Ciao Prolog, relations can be nested, like functions in functional programming:[100]

grandparent(X) := parent(parent(X)).
parent(X) := mother(X).
parent(X) := father(X).

mother(charles) := elizabeth.
father(charles) := phillip.
mother(harry) := diana.
father(harry) := charles.

?- grandparent(X,Y).
X = harry,
Y = elizabeth.
X = harry,
Y = phillip.
Ciao transforms the function-like notation into relational form and executes the resulting logic program using the standard Prolog execution strategy.

Applications
Spreadsheets
Spreadsheets can be considered a form of pure, zeroth-order, strict-evaluation functional programming system.[101] However, spreadsheets generally lack higher-order functions as well as code reuse, and in some implementations, also lack recursion. Several extensions have been developed for spreadsheet programs to enable higher-order and reusable functions, but so far remain primarily academic in nature.[102]

Academia
Functional programming is an active area of research in the field of programming language theory. There are several peer-reviewed publication venues focusing on functional programming, including the International Conference on Functional Programming, the Journal of Functional Programming, and the Symposium on Trends in Functional Programming.

Industry
Functional programming has been employed in a wide range of industrial applications. For example, Erlang, which was developed by the Swedish company Ericsson in the late 1980s, was originally used to implement fault-tolerant telecommunications systems,[11] but has since become popular for building a range of applications at companies such as Nortel, Facebook, Électricité de France and WhatsApp.[10][12][103][104][105] Scheme, a dialect of Lisp, was used as the basis for several applications on early Apple Macintosh computers[3][4] and has been applied to problems such as training-simulation software[5] and telescope control.[6] OCaml, which was introduced in the mid-1990s, has seen commercial use in areas such as financial analysis,[14] driver verification, industrial robot programming and static analysis of embedded software.[15] Haskell, though initially intended as a research language,[17] has also been applied in areas such as aerospace systems, hardware design and web programming.[16][17]

Other functional programming languages that have seen use in industry include Scala,[106] F#,[18][19] Wolfram Language,[7] Lisp,[107] Standard ML[108][109] and Clojure.[110]

Functional platforms have been popular in finance for risk analytics (particularly with large investment banks). Risk factors are coded as functions that form interdependent graphs (categories) to measure correlations in market shifts, similar in manner to Gröbner basis optimizations but also for regulatory frameworks such as Comprehensive Capital Analysis and Review. Given the use of OCaml and Caml variations in finance, these systems are sometimes considered related to a categorical abstract machine. Functional programming is heavily influenced by category theory.[citation needed]

Education
Many universities teach functional programming.[111][112][113][114] Some treat it as an introductory programming concept[114] while others first teach imperative programming methods.[113][115]

Outside of computer science, functional programming is used to teach problem-solving, algebraic and geometric concepts.[116] It has also been used to teach classical mechanics, as in the book Structure and Interpretation of Classical Mechanics.")
