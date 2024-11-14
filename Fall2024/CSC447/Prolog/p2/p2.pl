% Trey Rubino
% CPSC 447 
% Dr. Schwesinger
% N-ary Tree and Recursive Rules

% Define the N-ary tree structure
tree(node(a, [
    node(b, [
        node(e, [
            node(k, [])
        ]),
        node(f, [
            node(l, []),
            node(m, [
                node(t, [])
            ])
        ])
    ]),
    node(c, [
        node(g, []),
        node(h, [
            node(n, [])
        ]),
        node(i, [
            node(o, []),
            node(p, [])
        ])
    ]),
    node(d, [
        node(j, [
            node(q, []),
            node(r, []), 
            node(s, [])
        ])
    ])
])).

% Ancestor rule: True if X is an ancestor of Y in the tree
ancestor(X, Y) :-
    tree(Tree),                         % Retrieve the tree structure
    ancestor_in_tree(X, Y, Tree).       % Check if X is an ancestor of Y in the tree

% Check if Y is a direct child of X
ancestor_in_tree(X, Y, node(X, Children)) :-
    member(node(Y, _), Children).       % Base case: Y is a direct child of X

% Check if Y is a descendant of X within Xs subtrees
ancestor_in_tree(X, Y, node(X, Children)) :-
    member(Child, Children),            % Select a child of X
    ancestor_in_tree(X, Y, Child).      % Recursive case: Check if Y is a descendant within Xs subtrees

% Traverse the entire tree to find the ancestor relationship
ancestor_in_tree(X, Y, node(_, Children)) :-
    member(Child, Children),            % Select each child node for searching
    ancestor_in_tree(X, Y, Child).      % Continue searching if X is not found at the current level

% Descendant rule: True if X is a descendant of Y
descendant(X, Y) :-
    ancestor(Y, X).                     % Descendant is the reverse of ancestor

% Sibling rule: True if X and Y have the same parent
sibling(X, Y) :-
    tree(Tree),                         % Retrieve the tree structure
    sibling_in_tree(X, Y, Tree).        % Check if X and Y have the same parent in the tree

% Check if X and Y share the same parent in the tree
sibling_in_tree(X, Y, node(_, Children)) :-
    member(node(X, _), Children),       % Verify if X is a child in the Children list
    member(node(Y, _), Children),       % Verify if Y is also a child in the Children list
    X \= Y.                             % Base case: Ensure X and Y are different nodes under the same parent

% Traverse the entire tree to find sibling relationships
sibling_in_tree(X, Y, node(_, Children)) :-
    member(Child, Children),            % Select each child node for searching
    sibling_in_tree(X, Y, Child).       % Continue searching in subtrees for sibling relationship

% Same level rule: True if X and Y are at the same level in the tree
same_level(X, Y) :-
    tree(Tree),                         % Retrieve the tree structure
    level(Tree, X, DepthX),             % Find the depth of X in the tree
    level(Tree, Y, DepthY),             % Find the depth of Y in the tree
    DepthX =:= DepthY.                  % True if both nodes are at the same depth

% Helper predicate to find the level of a node in the tree
level(node(Value, _), Value, 0).        % Base case: root node has level 0

level(node(_, Children), Value, Depth) :-
    member(Child, Children),            % Check if Child is a member of the Children list
    level(Child, Value, ChildDepth),    % Recursive call to find the level of Value in the Child subtree
    Depth is ChildDepth + 1.            % Increment depth by 1 for each level down
