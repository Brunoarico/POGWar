# POGWar

Bruno Arico         8125459

Gabriel Capella     8962078

Nicolas Nogueira    9277541

Esse [reposítório](https://github.com/Brunoarico/POGWar/) é destinado ao projeto da disciplina Laboratório de Programação (MAC0211) do Instituto de Matemática e Estatística da Universidade de São Paulo.

### Estrutura do Projeto
Nessa momento o projeto somente apresenta sua primeira parte. Nela existe o objetivo de realizar simulações físicas. Para isso modularizamos o programa nas seguintes partes:

- math/vector: responável por conter todas as operações vetoriais envolvidas nos processos.
- physics/physics: contém todas as fórmulas de físicas necessárias para essa parte do projeto. Também apresenta formulas de cálculo de centro de massa - para posterior uso.
- engine/object: biblioteca que administras todos os objetos presentes no jogo. Ela classifica dada tipo de objeto e atribui ids para eles.
- graphs/image: carrega as imagens para um struct e para o opengl. No momento imprime o nome e as dimensões das imagens carregadas.
- graphs/shape: os objetos no jogo possuiem uma forma (shape) composta por vértices. Essa biblioteca administras essas formas.
- simulation/moviments: responsável por calcular uma interação entre as partículas. Nessa biblioteca também há uma função que arruma as partículas caso elas estejam fora da tela.
- simulation/bsp: algorítimo responsável por calcular colisões no jogo. Ele realiza de forma não quadrática todas as colisões existentes no jogo, comparando os vértices dos shapes. No momento imprime o id dos objetos quando há uma colisão.
- simulation/vertices: utilizada por simulation/bsp em seus cálculos.

#### Instalação
Para rodar o nosso programa é necessário que tenha instalado as seguinter bibliotecas: [png](http://www.libpng.org/pub/png/libpng.html) e [glfw](http://www.glfw.org/). É importante executar com precissão todos os procedimentos, [descritos aqui](http://www.glfw.org/docs/latest/compile.html), para instalar o glfw.

#### Copilar
Para copilar nosso programa basta executar:
```
make clean
make
```

#### Executar
```
./jogo
```

Nota: para inserir um novo corpo or remover, edite o arquivo `jogo.c`. Retiramos o formato de inserção de dados na entrada padrão, pois no jogo os objeto serão determinados pelo sistema, não pelo usuário.

Existem outras opções do jogo que podem ser editadas em `config.h`, lembrando que caso haja alteração desse arquivo é necessário copilá-lo novamente.

### Nota sobre parte gráfica

Para o jogo ser consistente e eficiente tomamos a decisão de executar o processo de cálculo da gravidade em uma frequencia maior que o número de quadros desenhados por segundo. Além disso forçamos que cada quadro de cálculos gravitacionais tenha no máximo 0.0001s. O cálculo de colisões estão juntos com a parte gráfica, ou seja em uma frequência menor. Já a verificação de outside bordes está junto com os cálculos gravitacionais.

### Para fazer

- Retirar moviments e implementar o algorítimo de [Barnes Hut](http://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html). Os cálculos são qudráticos ao número de objetos no sistema.
- Inserir função que trata e responde a colisão dos objetos de tipos diferentes.
- Completar physics. Vamos incluir no futuro fórmulas para a dinâmica angular, pois atualmente estamos usando uma adaptação defeituosa (rever 'physics:act_force()').




