% Trey Rubino
% CPSC 447 
% Dr. Schwesinger
% Prolog Preliminary

% Facts
% Dio is a vampire
vampire(dio).

% Jonathan plays rugby
plays_rugby(jonathan).

% Rules 
% X is nocturnal if X is a vampire
nocturnal(X) :- vampire(X). 

% Tarkus likes X if X is nocturnal
likes(tarkus, X) :- nocturnal(X). 

% George likes X if X is nocturnal or X plays rugby
likes(george, X) :- nocturnal(X) ; plays_rugby(X). 