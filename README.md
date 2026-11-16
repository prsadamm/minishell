# minishell

*Ce projet a été réalisé dans le cadre du cursus de l'école 42.*

## Description

**minishell** est une réimplémentation simplifiée d'un shell Unix, inspirée de **bash**. Le programme affiche un prompt, lit les commandes saisies par l'utilisateur, les interprète puis les exécute, tout en gérant les redirections, les pipes, les variables d'environnement et les signaux.

Cette version inclut les **bonus** : les opérateurs logiques `&&` et `||`, les parenthèses pour les priorités, et les wildcards `*`. Le parsing repose sur un **arbre binaire (AST)** qui représente la structure de la ligne de commande et permet de respecter les priorités d'exécution.

L'objectif est de comprendre en profondeur les processus, les descripteurs de fichiers, la création de processus avec `fork`, l'exécution avec `execve`, la gestion des signaux et la construction d'un arbre syntaxique.

## Prototype

```bash
./minishell
```

Le programme lance un shell interactif avec un prompt et un historique des commandes.

## Fonctionnalités

| Fonctionnalité | Description |
|----------------|-------------|
| Prompt | Affiche un prompt en attente d'une nouvelle commande |
| Historique | Conserve l'historique des commandes saisies |
| Exécution | Lance les exécutables via le `PATH`, un chemin relatif ou absolu |
| Quotes | Gère les guillemets simples `'` et doubles `"` |
| Variables | Développe les variables d'environnement `$VAR` |
| Code de retour | Développe `$?` avec le statut de la dernière commande |
| Pipes | Gère les pipes `\|` pour chaîner les commandes |
| Redirections | Gère `<`, `>`, `<<` et `>>` |
| Signaux | Gère `Ctrl-C`, `Ctrl-D` et `Ctrl-\` comme dans bash |

## Bonus

| Fonctionnalité | Description |
|----------------|-------------|
| `&&` | Exécute la commande suivante seulement si la précédente réussit |
| `\|\|` | Exécute la commande suivante seulement si la précédente échoue |
| `( )` | Les parenthèses permettent de définir les priorités |
| `*` | Les wildcards sont développés dans le répertoire courant |

## Arbre syntaxique (AST)

La ligne de commande est transformée en **arbre binaire** où chaque nœud représente une opération et chaque feuille une commande. L'arbre est ensuite parcouru récursivement pour exécuter les commandes dans le bon ordre.

| Type de nœud | Description |
|--------------|-------------|
| Commande | Feuille de l'arbre, contient la commande et ses arguments |
| Pipe `\|` | Relie la sortie d'une commande à l'entrée de la suivante |
| `&&` | Exécute le nœud droit si le nœud gauche réussit |
| `\|\|` | Exécute le nœud droit si le nœud gauche échoue |
| Parenthèses | Regroupent des commandes et modifient la priorité |

Exemple pour la ligne `(ls && echo ok) | wc -l` :

```
         PIPE
        /    \
     AND     wc -l
    /   \
   ls   echo ok
```

## Redirections

| Symbole | Description |
|---------|-------------|
| `<` | Redirige l'entrée depuis un fichier |
| `>` | Redirige la sortie vers un fichier (écrase) |
| `<<` | Here-document : lit l'entrée jusqu'à un délimiteur |
| `>>` | Redirige la sortie vers un fichier (ajoute à la fin) |

## Commandes intégrées (builtins)

| Commande | Description |
|----------|-------------|
| `echo` | Affiche du texte (avec l'option `-n`) |
| `cd` | Change de répertoire (chemin relatif ou absolu) |
| `pwd` | Affiche le répertoire courant |
| `export` | Ajoute ou modifie une variable d'environnement |
| `unset` | Supprime une variable d'environnement |
| `env` | Affiche les variables d'environnement |
| `exit` | Quitte le shell |

## Signaux

| Touche | Comportement |
|--------|--------------|
| `Ctrl-C` | Affiche un nouveau prompt sur une nouvelle ligne |
| `Ctrl-D` | Quitte le shell |
| `Ctrl-\` | Ne fait rien |

## Fonctionnement

| Étape | Description |
|-------|-------------|
| Lecture | Récupère la ligne saisie avec `readline` |
| Lexing | Découpe la ligne en tokens (mots, opérateurs, quotes, parenthèses) |
| Parsing | Construit l'arbre binaire en respectant les priorités |
| Expansion | Développe les variables d'environnement, `$?` et les wildcards |
| Exécution | Parcourt l'arbre récursivement, crée les processus, gère pipes et redirections |
| Attente | Récupère le code de retour avec `waitpid` |

## Fonctions autorisées

| Fonction | Rôle |
|----------|------|
| `readline`, `add_history` | Lecture de la ligne et historique |
| `fork`, `execve`, `wait`, `waitpid` | Gestion des processus |
| `pipe`, `dup`, `dup2` | Gestion des pipes et des descripteurs |
| `open`, `close`, `read`, `write` | Manipule les fichiers |
| `opendir`, `readdir`, `closedir` | Lecture des répertoires (wildcards) |
| `signal`, `sigaction`, `kill` | Gestion des signaux |
| `getcwd`, `chdir` | Gestion du répertoire courant |
| `access`, `stat`, `unlink` | Informations et gestion des fichiers |
| `getenv` | Récupère une variable d'environnement |
| `malloc`, `free`, `exit` | Mémoire et sortie |

## Compilation

```bash
make        # compile le programme minishell
make clean  # supprime les fichiers objets
make fclean # supprime les objets et l'exécutable minishell
make re     # recompile entièrement
```

La bibliothèque `readline` doit être installée :

```bash
sudo apt install libreadline-dev
```

## Utilisation

Lancer le shell :

```bash
./minishell
```

Exemples de commandes :

```bash
minishell$ echo "Bonjour 42"
minishell$ ls -l | grep minishell > resultat.txt
minishell$ cat << EOF
minishell$ export MA_VAR=42 && echo $MA_VAR
minishell$ (ls && echo ok) || echo erreur
minishell$ ls *.c
```

## Normes

- Respect de la **Norme** de 42
- Compilation avec `-Wall -Wextra -Werror`
- Aucune fuite mémoire (hors fuites de `readline`)
- Une seule variable globale autorisée (pour les signaux)

## Auteur

@prsadamm
