init_world([
    place(field),
    place(forest),
    place(river),

    path(field, north, forest),
    path(field, east, river),
    path(river, west, field),
    path(forest, south, field),

    kind(wolf, predator),
    kind(deer, herbivore),
    kind(tree, plant),
    kind(player, human),

    at(wolf, forest),
    at(deer, field),
    at(tree, forest),
    at(player, field),

    energy(wolf, 50),
    energy(deer, 80),
    energy(player, 100)
]).

fact(World, Fact) :-
    member(Fact, World).

where(World, Thing, Place) :-
    fact(World, at(Thing, Place)).

energy(World, Thing, Energy) :-
    fact(World, energy(Thing, Energy)).

kind(World, Thing, Kind) :-
    fact(World, kind(Thing, Kind)).

replace(World0, Old, New, World1) :-
    select(Old, World0, New, World1).

move(World0, Actor, To, World1) :-
    where(World0, Actor, From),
    fact(World0, path(From, _, To)),
    replace(World0, at(Actor, From), at(Actor, To), World1).

things_at(World, Place, Things) :-
    findall(
        Thing,
        member(at(Thing, Place), World),
        Things
    ).

/*
can_eat(predator, herbivore).
can_eat(herbivore, plant).

possible_action(Actor, eat(Target)).
possible_action(Actor, move(Direction)).
possible_action(Actor, rest).

tick :-
    forall(actor(A), act(A)).*/
