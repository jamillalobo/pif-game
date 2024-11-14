# WormDune

## Descrição

Imagine que voce e um astronauta e precisa sobreviver no espaco. Esse jogo mistura roleta russa e varios mundos! O astronauta tem o objetivo de sobreviver ganhando vidas, porem caso ele escolha o objeto errado, ele cai num portal que o leva pra outra dimensao (mudanca de cor do background).

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

3.  Instale biblioteca Curses através desse comando:
    ```
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```
4.  Mude o diretório raiz da biblioteca e digite o seguinte comando abaixo
    ```
    gcc ./src/*.c -I./include -o exemplo-1 -lncurses
    ```
    - Esse comando irá compilar os arquivos e gerar um arquivo executável
5.  Após gerar o executável digite no terminal `./exemplo-1` para executar o jogo
