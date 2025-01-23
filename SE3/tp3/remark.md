Exercice 1 et 2 : Dans ces exercices, en raison de l'accès concurrent à la variable V, la valeur finale peut varier. Dans l'exercice 1, la valeur finale devrait théoriquement être 0, mais en pratique, elle peut être différente à cause des interférences entre les threads. Dans l'exercice 2, la valeur finale devrait être 20000, mais encore une fois, des variations peuvent se produire.

Exercice 3 : L'algorithme de Peterson garantit l'exclusion mutuelle, ce qui signifie que la valeur finale de V devrait être 20000, car les threads ne peuvent pas accéder à V en même temps.

Exercice 4 : La matrice est initialisée avec des zéros. Les deux threads incrémentent les éléments diagonaux de la matrice. Grâce à l'algorithme de Peterson, la valeur finale des éléments diagonaux devrait être 200, mais des variations peuvent se produire si l'algorithme n'est pas correctement implémenté.
