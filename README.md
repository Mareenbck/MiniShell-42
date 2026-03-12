# 🐚 MiniShell-42

>  Développer un shell simplifié en **C**, inspiré de bash — Projet 42.

## ✨ Fonctionnalités

- 📝 **Lexer & Parser** — Tokenisation et analyse syntaxique des commandes
- 🔧 **Builtins** — `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- 🔀 **Pipes** — Chaînage de commandes avec `|`
- 📂 **Redirections** — `>`, `>>`, `<`, `<<` (heredoc)
- 💲 **Expansion** — Variables d'environnement (`$VAR`, `$?`)
- 🔤 **Quotes** — Gestion des simple et double quotes
- 🚦 **Signaux** — `ctrl-C`, `ctrl-D`, `ctrl-\`

## 🛠 Stack

**Langage** : C · **Lib** : libft · readline  
**Compilation** : gcc · Makefile · Flags `-Wall -Wextra -Werror`

## 📁 Structure

```
├── builtin/     # echo, cd, pwd, export, unset, env, exit
├── parsing/     # Lexer → Parser → Quotes → Redirections
├── lexerd/      # Tokenisation de l'input
├── exe/         # Exécution des commandes (fork, execve, pipes)
├── expand/      # Expansion des variables d'environnement
├── env/         # Gestion de l'environnement
├── append/      # Redirections & heredoc
├── toolbox/     # Utilitaires (listes chaînées, free, erreurs)
├── libft/       # Bibliothèque C personnalisée
├── main.c       # Point d'entrée
├── signal.c     # Gestion des signaux
└── minishell.h  # Header principal
```

## 🚀 Utilisation

```bash
git clone https://github.com/Mareenbck/MiniShell-42.git
cd MiniShell-42
make
./minishell
```

```
minishell$ echo "Hello World" | cat -e
Hello World$
minishell$ ls -la > output.txt
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
```
