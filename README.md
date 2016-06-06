# POGWar

Bruno Arico         8125459

Gabriel Capella     8962078

Nicolas Nogueira    9277541

Esse [reposítório](https://github.com/Brunoarico/POGWar/) é destinado ao projeto da disciplina Laboratório de Programação (MAC0211) do Instituto de Matemática e Estatística da Universidade de São Paulo.

### Estrutura do Projeto
Nessa momento o projeto apresenta sua terceira parte. Nela existe o objetivo de realizar a geração de imagens. Para isso modularizamos o programa nas seguintes partes:

- math/vector: responável por conter todas as operações vetoriais envolvidas nos processos.
- physics/physics: contém todas as fórmulas de físicas necessárias para essa parte do projeto. Também apresenta formulas de cálculo de centro de massa.
- engine/object: biblioteca que administras todos os objetos presentes no jogo. Ela classifica dada tipo de objeto e atribui ids para eles.
- engine/controls: biblioteca que administra a ação dos controles no jogo (os controles estão configurados em config.h).
- graphs/bitmap: carrega os textos na tela.
- graphs/image: carrega as imagens para um struct e para o opengl. No momento imprime o nome e as dimensões das imagens carregadas.
- graphs/shape: os objetos no jogo possuiem uma forma (shape) composta por vértices. Essa biblioteca administras essas formas.
- simulation/moviments: responsável por calcular uma interação entre as partículas. Nessa biblioteca também há uma função que arruma as partículas caso elas estejam fora da tela.
- simulation/bsp: algoritmo responsável por calcular colisões no jogo. Ele realiza de forma não quadrática todas as colisões existentes no jogo, comparando os vértices dos shapes. No momento imprime o id dos objetos quando há uma colisão.
- simulation/vertices: utilizada por simulation/bsp em seus cálculos.

#### Instalação
Para rodar o nosso programa é necessário que tenha instalado as seguinter bibliotecas: [png](http://www.libpng.org/pub/png/libpng.html) e [glfw](http://www.glfw.org/). É importante executar com precisão todos os procedimentos, [descritos aqui](http://www.glfw.org/docs/latest/compile.html), para instalar o glfw.

#### Compilar
Para compilar nosso programa basta executar:
```
make clean
make
```

#### Executar
```
./jogo
```

Nota: para inserir um novo corpo ou remover, edite o arquivo `jogo.c`. Retiramos o formato de inserção de dados na entrada padrão, pois no jogo os objeto serão determinados pelo sistema, não pelo usuário.

Existem outras opções do jogo que podem ser editadas em `config.h`, lembrando que caso haja alteração desse arquivo é necessário compilá-lo novamente.

#### Controles

 Botão |      Descrição
----------------------------------
   W   | frente    (player 1)
   A   | esquerda  (player 1)
   D   | direita   (player 1)
   S   | tiro      (player 1)
   I   | frente    (player 2)
   J   | esquerda  (player 2)
   L   | direita   (player 2)
   K   | tiro      (player 2)
   R   | reset (reinicia pausado)
   P   | pause/despause
  ESC  | fecha o jogo

#### Jogo

Cada player possui uma barra de vida e uma de combustível, só é possível se mover caso a barra de combustível não esteja vazia. Quando a barra de vida de algum player acaba, a nave é destruída e o player é dado como perdedor. Para iniciar uma nova partida basta apertar R e depois P. Quando alguma nave se choca com o planeta ou com a outra nave ela é destruída.

### Nota sobre parte gráfica

Para o jogo ser consistente e eficiente tomamos a decisão de executar o processo de cálculo da gravidade em uma frequencia maior que o número de quadros desenhados por segundo. Além disso forçamos que cada quadro de cálculos gravitacionais tenha no máximo 0.0001s. O cálculo de colisões estão juntos com a parte gráfica, ou seja em uma frequência menor. Já a verificação de outside bordes está junto com os cálculos gravitacionais.

### Para fazer

- Solucionar alguns bugs de controles e alguns bugs visuais.



