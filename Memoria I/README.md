# Memória 1

O programa começa com a definição da estrutura **celula**, que contém um valor inteiro **conteudo** e um ponteiro para outra célula **prox**. Em seguida, são definidas as funções para manipulação da lista encadeada:

* **inserir** insere um novo valor no início da lista. Ela aloca uma nova célula **nova** e atribui o valor passado como parâmetro a ela. O ponteiro **prox** da nova célula é então configurado para apontar para o início da lista atual, e o ponteiro **inicio** é atualizado para apontar para a nova célula.

* **imprimir** percorre a lista e imprime cada valor contido nas células.

* **tamanho_celula** aloca duas células **p** e **q** e calcula o tamanho de uma célula em bytes, subtraindo os endereços de memória de **q** e **p**.

* **excluir_todos** percorre a lista e libera a memória alocada para cada célula.

* **remove_valor** remove um valor específico da lista. Ela percorre a lista e, quando encontra a célula com o valor desejado, atualiza os ponteiros para remover a célula da lista e libera a memória alocada para ela.

* **espaco_utilizado** percorre a lista e conta o número de células para calcular o espaço utilizado na memória.

O programa principal começa com a declaração da variável inicio, que será o ponteiro para o início da lista. Em seguida, é exibido um menu com as opções disponíveis para o usuário. O programa entra em um loop que executa a opção escolhida pelo usuário até que ele escolha a opção de saída (0). O loop chama as funções correspondentes para executar cada opção escolhida.

* **Inserindo Valores** 

![image](https://user-images.githubusercontent.com/34254106/234985150-00464175-acbb-4080-bb6f-a39f80581aac.png)
![image](https://user-images.githubusercontent.com/34254106/234985621-10d6c3d6-c135-499e-a22e-1d71d27f91cd.png)

* **Espaço utilizado**


