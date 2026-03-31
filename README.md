# ----- Projeto 01 - Computação Visual - André Kishimoto ----- 

10419790 - Carlos Eduardo Hayashi

10419663 - Edson Luiz Cardoso Ohira

10419471 - Vinicius Oliveira Piccazzio

main.c / main.h -> Codificação principal (interface e controle das funções / métodos)
imagem.c / image.h -> Desenvolvimento das funções realizadas sob a imagem: 
    1. Carregamento / Processamento da imagem;
    2. Validação se a imagem já se encontra em grayscale; 
    3. Conversão para grayscale;
    4. Salvar a imagem no output.
processing.c / processing.h


### ----- Step by Step - Compilando e Executando o programa -----

OBS: A exemplificação a seguir foi realizada em um MAC OS

1 - Antes de tudo, via terminal (cmd, VSCode...), acesse o diretório onde a pasta do projeto foi instalada. 

(base) carloseduardohayashi@MacBook-Pro-de-Carlos 7º semestre % cd Computação\ Visual/ 

(base) carloseduardohayashi@MacBook-Pro-de-Carlos Computação Visual % cd Projeto_01_V04

(base) carloseduardohayashi@MacBook-Pro-de-Carlos Projeto_01_V04 % 

2 - Na pasta, basta realizar o seguinte comando para compilar o projeto e gerar um executável (no exemplo, o .exe é chamado programa).

(base) carloseduardohayashi@MacBook-Pro-de-Carlos Projeto_01_V04 % gcc src/main.c src/image.c src/processing.c -Iinclude -o programa \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lSDL3 -lSDL3_image -lSDL3_ttf -lm

3 - Por último, basta executar o programa, passando o caminho da imagem de entrada.

(base) carloseduardohayashi@MacBook-Pro-de-Carlos Projeto_01_V04 % ./programa input/input_image.png                                   

OBS: O terminal estará bloqueado, por conta que o .exe estará em execução, para fechar o programa, o usuário pode realizar o comando CTRL + C no terminal.


### ----- Usuabilidade / Funcionalidades do Programa -----

O programa, uma vez aberto, se torna usável. O programa exibe duas telas (PAI e FILHA), onde:

Janela pai: Nesta janela é exibida a imagem de entrada em grayscale (escala de cinza);
Janela filha: Nesta janela é exibida o histograma da imagem, com as métricas de brilho e contraste (desvio padrão), e um botão interativo, que realiza a conversão entre imagem equalizada e original.

Uma outra funcionalidade do programa é a capacidade do usuário salvar a imagem, basta utilizar o comando CTRL + S, no qual o programa salva na pasta /output e exibe um informativo ao usuário.


### ----- Conceitos aplicados -----

- Grayscale (Escala de Cinza): Conversão da imagem colorida para tons de cinza utilizando a fórmula ponderada: 
Y = 0.2125R + 0.7154G + 0.0721B

- Histograma: Representação gráfica da distribuição dos níveis de intensidade (0–255) da imagem.

- Brilho: Calculado através da média dos níveis de intensidade.

- Contraste: Calculado a partir do desvio padrão.

- Equalização do Histograma: Técnica que redistribui os níveis de intensidade da imagem, melhorando o contraste e destacando detalhes.

### Contribuição dos Integrantes

O desenvolvimento deste projeto foi realizado de forma colaborativa entre os membros do grupo, com a divisão de responsabilidades conforme descrito abaixo:

- Vinicius Oliveira Piccazzio: Responsável pela elaboração da documentação do projeto. Ficou encarregado da produção do arquivo README.md, incluindo a descrição detalhada do funcionamento do sistema, instruções de compilação e execução, além da organização geral da documentação.
- Carlos Eduardo Hayashi: Responsável pelo desenvolvimento das funcionalidades principais relacionadas ao processamento de imagens, incluindo a implementação dos arquivos image.c e processing.c. Suas atividades abrangeram o carregamento das imagens, conversão para escala de cinza, cálculo e equalização do histograma, bem como as demais operações de processamento.
- Edson Luiz Cardoso Ohira: Responsável pela implementação do arquivo main.c, incluindo a estrutura principal do programa, gerenciamento da interface gráfica, controle do fluxo de execução e integração entre os módulos do sistema.
