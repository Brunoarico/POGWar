# POGWar

Esse reposítório é destinado ao projeto da displima Laboratótio de Programação (MAC0211) no Instituto de Matemática e Estatística.

### Estrutura do Projeto
Nessa nommento o projeto somente apresenta sua primeira parte. Nela existe o objetivo de realizar simulações físicas. Para isso modularizamos o programa nas seguintes partes:

- vector: responável por conter todas as operações vetoriais envolvidas nos processos.
- physics: contém todas as fórmulas de físicas necessárias para essa parte do projeto. Também apresenta formulas de cálculo de centro de massa - para posterior uso.
- moviments: responsável por calcular uma interação entre as partículas.

#### simulacao.c
Esse código foi implentado especialmente para a primeira parte do projeto. Ele recebe na entrada padrão as seguintes informações:

A entrada será fornecida em um arquivo com o seguinte formato:
- A primeira linha tem os parâmetros globais, separados por espaço:
	1. Tamanho do planeta (raio).
	2. Massa do planeta.
	3. Tempo total de simulação.
- A segunda linha contém a descrição da primeira nave, com os seguintescampos separados por espaço:
	1. nome — nome da nave, para referência posterior.
	2. massa — massa da nave.
	3. pos x — coordenada x da posição da nave.
	4. pos y — coordenada y da posição da nave.
	5. vel x — componente x da velocidade da nave.
	6. vel y — componente y da velocidade da nave.
- A terceira linha descreve a segunda nave, da mesma forma.
- A quarta linha indicará o número de projéteis e a duração (tempo de vida) deles.
- As linhas seguintes conterão a descrição de cada projétil, da mesma
forma que nas naves, mas sem o campo nome.

O resultado desse programa são linhas da seguinte forma:
	
	m: 1.498332e+16 	x: 0.000000e+00 	y: 0.000000e+00 	vx: 0.000000e+00 	vy: 0.000000e+00 
	m: 1.498334e+12 	x: 4.986434e+01 	y: 8.781620e+01 	vx: -8.691832e+02 	vy: 4.946798e+02 
	m: 1.498334e+12 	x: -4.986434e+01 	y: -8.781620e+01 	vx: 8.691832e+02 	vy: -4.946798e+02 

m é a massa do corpo, x e y a posição e vx e vj a velocidade após as interações.

É importante resaltar que esse programa possui um argumento na linha de entrada, que é o tempo de duração de cada interação do programa. Ou seja, o tempo que a força criada pela gravidade irá exercer no sistema. Qunto menor esse número melhor e mais devagar a simulação.

Obs: se o tempo de duração dos projéteis for menor do que o tempo total da simulação, eles não irão aparecer na saída final, pois vão desaparecer.

### Para fazer

- Retirar moviments e implementar o algorítimo de [Barnes Hut](http://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html). Os cálculos são qudráticos se ao número de objetos no sistema.
- Criar módulo de shape (formato). Cada corpo físico deve ter um formato, ou seja um vetor composto por vértices do objeto. Vamos usar posteriormente esse vetor para as colizões e a parte gráfica. Uma implentação comercial dessa técnica pode ser vista [aqui](https://developer.apple.com/library/ios/documentation/GraphicsAnimation/Conceptual/SpriteKit_PG/Physics/Physics.html).
- Criar algorítmo de identificação de colizão entre os corpos.
- Mecanismo de tratamento dos projéteis.
- Completar physics. Vamos incluir no futuro fórmulas para a dinâmica angular.
- Criar interface gráfica e mecanismo de jogo.


