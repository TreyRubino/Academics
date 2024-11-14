% Trey Rubino
% CPSC 447 
% Dr. Schwesinger
% Added predicate escape/2

% A person trying to escape a room. The person is at the door, but the door is
% locked. There is a window in the room, but it is too high to climb out from
% the floor. There is a box in the middle of the room that the person can push
% around and climb on. Can the person escape through the window?

% Legal actions

% Climb out the window
action( state( atwindow , onbox, atwindow, trapped),
      climb,
      state( atwindow, onbox, atwindow, free) ).

% Climb the box
action( state( P, onfloor, P, H),
      climb,
      state( P, onbox, P, H) ).

% Push box from P1 to P2
action( state( P1, onfloor, P1, H),
      push( P1, P2),
      state( P2, onfloor, P2, H) ).

% Walk from P1 to P2
action( state( P1, onfloor, B, H),
      walk( P1, P2),
      state( P2, onfloor, B, H) ).

% escape( State): the person can escape
escape( state( _, _, _, free) ).

escape( State1) :-
    action( State1, _, State2),
    escape( State2).

% Predicate escape/2 
escape(state(_, _, _, free), []).               % Base case: the person has escaped, no further actions
escape(State, [Action|Actions]) :-              % Recursive step
      action(State, Action, NextState),         % Get the next state after performing an action
      escape(NextState, Actions).               % Recursive call: continue finding actions to take based on the next state 

% Example query
% escape( state(atdoor, onfloor, middle, trapped) ).

