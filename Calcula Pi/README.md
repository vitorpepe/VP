# CalculaPi - Sem Mutex

O programa começa pedindo ao usuário para digitar o número de threads que devem ser utilizadas no cálculo. É definindo um valor padrão para o número de iterações n = 1000000 = 10^6, e aloca memória para dois vetores: um para armazenar os identificadores das threads (thread_handles), e outro para armazenar as somas parciais calculadas por cada thread (sum).

O programa então inicializa o vetor de somas parciais com zero, cria as threads e as executa chamando a função "Thread_sum" para cada uma delas. A função "Thread_sum" recebe como parâmetro um índice de thread, e calcula a soma parcial correspondente a essa thread. A soma parcial é armazenada no vetor "sum" na posição correspondente ao índice da thread.

Após todas as threads terem concluído o processamento, o programa soma as somas parciais de todas as threads para obter o valor final de Pi, e multiplica o resultado por 4 para obter o valor correto. O programa imprime o valor final de Pi e libera a memória alocada para os vetores.

![image](https://user-images.githubusercontent.com/34254106/233492972-5daef49b-afa9-4f88-a83b-948bb7e4d683.png)

O resultado varia de acordo com o número de threads porque o cálculo do valor de Pi é feito de forma paralela entre as threads, cada uma calculando uma parte do somatório. Quando o número de threads aumenta, cada uma delas tem menos iterações para calcular, o que pode tornar a execução mais rápida. A divisão das iterações entre as threads pode não ser igual, o que pode levar a resultados diferentes. 


# CalculaPi - Com Mutex

A variável "sum" é um vetor que armazena a soma parcial calculada por cada thread. Essas somas parciais são posteriormente somadas para obter a estimativa final de Pi, ela é protegida pelas funçoes "pthread_mutex_lock" e "pthread_mutex_unlock" de acessos simultâneos e garantir que apenas uma thread por vez possa atualizar o valor de "sum".

O código começa lendo o número de threads que serão utilizadas para calcular Pi. Em seguida, ele aloca memória para os vetores thread_handles e sum, inicia o mutex e inicializa o vetor "sum" com zero para cada thread.

Em seguida, ele cria as threads utilizando a função "pthread_create". Para cada thread criada, o índice da thread é passado como argumento para a função "Thread_sum".

Depois que todas as threads foram criadas, o programa espera que todas as threads terminem utilizando a função "pthread_join".

Após todas as threads terem terminado, o valor de Pi é calculado a partir das somas parciais e é impresso na tela. Em seguida, o mutex é finalizado e a memória alocada para "thread_handles" e "sum" é liberada.

![image](https://user-images.githubusercontent.com/34254106/233494445-e1b27342-46e0-451f-9e02-5db26076a734.png)

O valor varia de acordo com o número de threads utilizadas porque as threads estão realizando operações simultâneas de adição no vetor sum, e essas operações concorrentes podem levar a condições de corrida (race conditions), onde o valor final depende da ordem em que as operações foram executadas. 


# Comparação

Na implementação sem mutex, as threads podiam acessar e atualizar o vetor de soma parcial simultaneamente, o que poderia levar a resultados inconsistentes. Isso ocorre porque a operação de atualização envolve uma leitura, uma modificação e uma escrita no vetor, e as threads poderiam intercalar suas operações, causando inconsistências.

Com o uso do mutex, as threads obtêm acesso exclusivo ao vetor de soma parcial, garantindo que cada operação seja executada completamente antes de outra thread começar a trabalhar no vetor. Assim, o uso do mutex ajuda a garantir que o resultado final seja consistente e correto.

O uso do mutex pode tornar o desempenho pior do que o código sem mutex, devido ao tempo extra necessário para adquirir e liberar o mutex. Além disso, o número de threads pode afetar o tempo de execução do programa, portanto a escolha do número de threads para o cálculo pode influenciar o tempo total de execução do programa e o resultado final obtido.
