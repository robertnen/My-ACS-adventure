

% + este o celulă normală
% ^ este o celulă fragilă (blocul nu poate sta în picioare)
% $ este gaura prin care poate trece blocul.
% B este blocul în picioare
% b este o jumătate de bloc, când blocul este culcat
% . este un spațiu în care va fi un pod (echivalent cu blank)
% - este un spațiu în care un pod activ (echivalent cu +)
% o sunt switch-uri care pot fi activate la orice apăsare
% x sunt switch-uri care pot fi activate doar de blocul în picioare

intern_level(1, "
+++
+B++++
+++++++++
 +++++++++
     ++$++
      +++
").

intern_level(2, ("
      ++++  +++
++++  ++x+  +$+
++o+  ++++  +++
++++  ++++  +++
+B++..++++..+++
++++  ++++     ", [
                     [switch, (10, 4), (11, 4)],
                     [switch, (4, 4), (5, 4)]
                 ])).

intern_level(3, "
      +++++++
++++  +++  ++
+++++++++  ++++
+B++       ++$+
++++       ++++
            +++
").

intern_level(4, "
   ^^^^^^^
   ^^^^^^^
++++     +++
+++       ++
+++       ++
+B+  ++++^^^^^
+++  ++++^^^^^
     +$+  ^^+^
     +++  ^^^^
").

intern_level(5, ("
           ++++
 ++++--+o++++B+
 ++++       +++
 ++o+
 ++++
   +++o++++++
          ++++o
+++       +++++
+$+++--++++++
++++           ", [
                    [switch, (5, 1), (6, 1)],
                    [uponly, (5, 8), (6, 8)],
                    [dnonly, (5, 8), (6, 8)],
                    [switch, (5, 8), (6, 8)]
                ])).

intern_level(6, ("
     ++++++
     +  +++
     +  +++++
B+++++     ++++
    +++    ++$+
    +++     +++
      +  ++
      +++++
      +++++
       +++
")).

intern_load_map(Level, MapOut, SwitchData) :-
    intern_level(Level, (String, SwitchData)), !,
    string_lines(String, Lines), !,
    maplist(atom_chars, Lines, Map),
    Map = [_ | MapOut].
intern_load_map(Level, MapOut, []) :-
    intern_level(Level, String),
    string_lines(String, Lines),
    maplist(atom_chars, Lines, Map),
    Map = [_ | MapOut].


