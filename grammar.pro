:- use_module(library(clpfd)).
:- use_module(library(random)).

mappend(_, [], []).
mappend(Pred, [H0|T0], Rs) :-
  call(Pred, H0, H1),
  mappend(Pred, T0, Rs0),
  append(H1, Rs0, Rs).

numbers_and_negations(Ins, Ous) :-
  mappend(number_and_negation, Ins, Ous).

number_and_negation(X, []) :- \+ number(X).
number_and_negation(X, [X, Y]) :- Y is -X.

list_and_reverse([], []).
list_and_reverse(X, [X, Y]) :- reverse(X, Y).


simple_grammar([
  [sentence, ->, [noun_phrase, verb_phrase]],
  [noun_phrase, ->, [article, noun]],
  [verb_phrase, ->, [verb, noun_phrase]],
  [article, ->, the, a],
  [noun, ->, man, ball, woman, table],
  [verb, ->, hit, took, saw, liked]
]).

bigger_grammar([
  [sentence, ->, [noun_phrase, verb_phrase]],
  [noun_phrase, ->, [article, adjN, noun, ppN], [name], [pronoun]],
  [verb_phrase, ->, [verb, noun_phrase, ppN]],
  [ppN, ->, [], [pp, ppN]],
  [adjN, ->, [], [adj, adjN]],
  [pp, ->, [prep, noun_phrase]],
  [prep, ->, to, in, by, with, on],
  [adj, ->, big, little, blue, green, adiabatic],
  [article, ->, the, a],
  [name, ->, pat, kim, lee, terry, robin],
  [noun, ->, man, ball, woman, table],
  [verb, ->, hit, took, saw, liked],
  [pronoun, ->, he, she, it, these, those, that]
]).

grammar(X) :- bigger_grammar(X).

find_sublist(Id, LL, [Id|T]) :-
  member([Id|T], LL).

rule_lhs([H|...], H).
rule_rhs([_,_|T], T).
rewrites(C, R) :-
  grammar(G),
  find_sublist(C, G, X),
  rule_rhs(X, R).

%% generate([], [[]]).
generate(P, R) :-
  ( is_list(P) -> mappend(generate, P, R)
  ; ( rewrites(P, Ch) ->
        Ln #> 0,
        length(Ch, Ln),
        random_member(N, Ch),
        generate(N, R)
    ; R = [P])).
