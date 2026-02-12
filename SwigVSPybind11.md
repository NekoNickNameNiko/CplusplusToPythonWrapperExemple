# Rapport

## Swig : Pour et contre
### Pour:
- **Multi-language :** Permet de générer des wrappers pour tout type de language (Python / Java / C# /...).
- **Automatisation :** Peu importe le nombre de classes C++, Swig peut scanner les **.h** et tout wrapper automatiquement.
- **Stabilité :** Très stable pour des projets longue durée.

### Contre:
- **Outil externe :** Tu dois installer l'executable **swig** et l'ajouter au processus de compilation.
- **Syntaxe spécifique :** Tu dois apprendre la syntaxe des fichiers **.i**.
- **Difficile a déboguer :** Swig génère un fichier **.cxx** contenant plusieurs milliers de lignes de code.
- **Embedding complexe :** "Embarquer" python et donc le garder dans le code c++ est laborieux.

## Pybind11 : Pour et Contre
### Pour:
- **Syntaxe C++ pure :** Pas besoin d'apprendre nouveau language, tout ce fait en Python et C++.
- **Support C++ moderne :** Peut gérer les pointeurs intelligent, multithreading, lambdas, etc.
- **Embedding facilité :** Sa conception facilite l'appel de scripts python depuis le C++ (se fait en quelques lignes).
- **Conversions automatiques :** Il convertit nativement les types standards (std::vector devient une list Python).
- **Header-only :** Tu n'as rien à "installer" sur ton système. Tu copies juste les fichiers d'en-tête de pybind11 dans ton projet.

### Contre:
- **Temps de compilation :** Puisqu'il utilise beaucoup de templates C++, le temps de compilation peut être plus long.
- **Python uniquement :** Le moteur n'est scriptable qu'en Python.
- **C++11 minimum :** Nécessite un compilateur relativement moderne.

## Choix : Pybind11
On a choisi Pybind11 car pour notre projet moteur, nous n'utiliseront que Python pour le scripting. De plus nous trouvons l'utilisation de Pybind plus claire et comprehensible. Et enfin, ce qui a motié notre choix est également le fait que Pybind supporte le multithreading et les pointeurs, rendant la logique de scripting plus simple à mettre en place.