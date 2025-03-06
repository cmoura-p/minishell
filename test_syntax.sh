#!/bin/bash

# Função para imprimir o título do teste
function print_test_title() {
    echo -e "\n\033[1;34mTestando: $1\033[0m"
}

print_test_title "Expansao"
echo "Testando expansao com aspas duplas"
./minishell <<< "echo "$USER""
./minishell <<< "echo "abc$USER""
./minishell <<< "echo "$USERxyz""
./minishell <<< "echo "abc$USERxyz""
./minishell <<< "echo "abc$USER[xzy]""
./minishell <<< "echo "$USER$PWD$HOME""
./minishell <<< "echo "$A$USER$PWD$HOME""
./minishell <<< "echo "$USER$A$PWD$HOME""
./minishell <<< "echo "$USER$PWD$A$HOME""
./minishell <<< "echo "$USER$PWD$HOME$A""
./minishell <<< "echo "$A""
read -n 1 -s -r

print_test_title "Expansao"
echo "Testando expansao sem aspas"
./minishell <<< "echo $USER"
./minishell <<< "echo abc$USER"
./minishell <<< "echo $USERxyz"
./minishell <<< "echo abc$USERxyz"
./minishell <<< "echo abc$USER[xzy]"
./minishell <<< "echo $USER$PWD$HOME"
./minishell <<< "echo $A$USER$PWD$HOME"
./minishell <<< "echo $USER$A$PWD$HOME"
./minishell <<< "echo $USER$PWD$A$HOME"
./minishell <<< "echo $USER$PWD$HOME$A"
./minishell <<< "echo $A"
read -n 1 -s -r

print_test_title "Expansao"
echo "Testando expansao com aspas simples"
./minishell <<< "echo '$USER'"
./minishell <<< "echo 'abc$USER'"
./minishell <<< "echo '$USERxyz'"
./minishell <<< "echo 'abc$USERxyz'"
./minishell <<< "echo 'abc$USER[xzy]'"
./minishell <<< "echo '$USER$PWD$HOME'"
./minishell <<< "echo '$A$USER$PWD$HOME'"
./minishell <<< "echo '$USER$A$PWD$HOME'"
./minishell <<< "echo '$USER$PWD$A$HOME'"
./minishell <<< "echo '$USER$PWD$HOME$A'"
./minishell <<< "echo '$A'"
read -n 1 -s -r

print_test_title "Juntando as Partes"
echo "Testando juncao de pedacos com aspas"
./minishell <<< "e'c'ho teste"
./minishell <<< "'ec'ho teste"
./minishell <<< "ec'ho' teste"
./minishell <<< "e"c"ho teste"
./minishell <<< ""e"cho teste"
./minishell <<< "ec"ho" teste"
./minishell <<< "'cat' t"e"ste"
./minishell <<< ""cat" "te"ste"
./minishell <<< "cat te""ste"
./minishell <<< "cat te''ste"
read -n 1 -s -r

print_test_title "OUTROS TESTES"
echo "Testes mais bizarros"
./minishell <<< "echo $USER+este do Brasil<cat cat"
./minishell <<< "echo $USER[rimeira|do Brasiloioicat cat"
./minishell <<< "echo $USER[rimeira do Brasiloioicat cat"
./minishell <<< "echo teste qq>cat"
./minishell <<< "echo $USER'rimeira do Brasil'|cat cat"		// problema com valgrind
./minishell <<< "echo $USERoioioi"
./minishell <<< "echo $USER[oioioi"
./minishell <<< "echo esse eh barril >ls"
./minishell <<< "cat cat ls"
./minishell <<< "cat cat ls -la"
./minishell <<< "cat cat |ls"
./minishell <<< "cat cat |ls -la"
read -n 1 -s -r
