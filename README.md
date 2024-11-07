# SnakeDune

## Descrição

O classico jogo da corbinha agora tem uma versao aprimorada, que mistura roleta russa e varios mundos! A cobrinha tem o obejtivo de comer frutinhas, que faz ela ganhar mais vidas, porem caso ela escolha a frutinha errada, ela cai num buraco que a leva pra outra dimensao (mudanca de cor do background).

## Integrantes

- Jamilla Lobo ([@jamillalobo](https://github.com/jamillalobo))
- Lucas Deodato ([@Lucas-deodato](https://github.com/Lucas-deodato))
- Luis Facunde ([@LuisFacunde](https://github.com/LuisFacunde))

## Instituição

- CESAR School

## Disciplina

- Programação Imperativa e Funcional - 2024.2

## Como jogar:

1.  Utilizar sistema basedo em `Linux`
2.  ter o GCC instalado (para que o jogo seja compilado)

    ```
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update
    sudo apt install gcc-13
    ```

3.  Mude o diretório raiz da biblioteca e digite o seguinte comando abaixo
    ```
    gcc ./src/\*.c -I./include -o exemplo-1 -lncurses
    ```
    - Esse comando irá compilar os arquivos e gerar um arquivo executável
4.  Após gerar o executável digite no terminal `./exemplo-1` para executar o jogo
