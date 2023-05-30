# minishell

Minishell is one of the assignments from 42Schools, where we implement a shell in C.

### Main Features

- Redirection, pipes, AND/OR, wildcard `*` in the current directory
- Signal handling
- Input history
- Environment variables

## Table of Contents

- [Setup](#setup)
- [Usage](#usage)
- [Note](#note)

## Setup

1. The **readline** library is required. Install it as follows using a package manager like *brew*:

```sh
brew install readline
```

2. Clone this repository. Make sure to clone the *libft* repository as well.

```sh
git clone https://github.com/tsudo42/minishell.git --recursive
```

3. Compile using make.

```sh
make
```

## Usage

Once setup is complete, you can launch the shell with `./minishell`. The syntax is similar to bash.

## Note

Please be aware of the following points as they deviate from the requirements of the 42Schools assignment:

- Not all features of bash are implemented.

This repository currently does not have a license set.
