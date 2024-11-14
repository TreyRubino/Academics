% Trey Rubino
% CPSC 447 
% Dr. Schwesinger
% Fundamental Predicates for Arithmetic and Lists

% Predicate factorial/2
factorial(0, 1).                                    % Base case: the factorial of 0 is 1
factorial(N, Result) :-                             % Recursive step 
    N > 0,                                          % For all n > 0
    PreviousN is N - 1,                             % Decrement N by 1
    factorial(PreviousN, PreviousResult),           % Recursive call: getting the factorial of N - 1
    Result is N * PreviousResult.                   % Calculate the result --> (N!) = N * (N - 1)!

% Predicate assoc/3
assoc(Property, [[Property, Value]|_], Value).      % Base case: the property is the first element in the list
assoc(Property, [_|Tail], Value) :-                 % Recursive step
    assoc(Property, Tail, Value).                   % Recursive call: using the tail of the list to continue searching and store within Value

% Predicate nth/3
nth(0, [Elt|_], Elt).                               % Base case: the element is the head of the list
nth(N, [_|Tail], Elt) :-                            % Recursive step
    N > 0,                                          % For all n > 0
    PreviousN is N - 1,                             % Decrement N by 1
    nth(PreviousN, Tail, Elt).                      % Recursive call: using the tail of the list to continue searching and store within Elt