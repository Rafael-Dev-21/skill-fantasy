my_reverse(A, B) :- my_reverse(A, B, []).

my_reverse([], Z, Z).
my_reverse([H|T], Z, Acc) :- my_reverse(T, Z, [H|Acc]).

my_palindrome(A) :-
  my_reverse(A, A).
