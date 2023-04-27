# Memória 1

O programa começa com a definição da estrutura celula, que contém um valor inteiro (conteudo) e um ponteiro para outra célula (prox). Em seguida, são definidas as funções para manipulação da lista encadeada.

A função inserir insere um novo valor no início da lista. Ela aloca uma nova célula (nova) e atribui o valor passado como parâmetro a ela. O ponteiro prox da nova célula é então configurado para apontar para o início da lista atual (*inicio), e o ponteiro inicio é atualizado para apontar para a nova célula.

A função imprimir percorre a lista e imprime cada valor contido nas células.

A função tamanho_celula aloca duas células (p e q) e calcula o tamanho de uma célula em bytes, subtraindo os endereços de memória de q e p.

A função excluir_todos percorre a lista e libera a memória alocada para cada célula.

A função remove_valor remove um valor específico da lista. Ela percorre a lista e, quando encontra a célula com o valor desejado, atualiza os ponteiros para remover a célula da lista e libera a memória alocada para ela.

A função espaco_utilizado percorre a lista e conta o número de células para calcular o espaço utilizado na memória.

O programa principal começa com a declaração da variável inicio, que será o ponteiro para o início da lista. Em seguida, é exibido um menu com as opções disponíveis para o usuário. O programa entra em um loop que executa a opção escolhida pelo usuário até que ele escolha a opção de saída (0). O loop chama as funções correspondentes para executar cada opção escolhida.