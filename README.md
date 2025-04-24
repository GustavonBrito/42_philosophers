# 42_philosophers

https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/

Toda vez que e criado uma thread é criado uma funcao.

Para verificar se um processo esta em execucao paralela basta por exemplo colocar um sleep no meio do processo e dois prints de cada lado, caso dois prints aconteca antes do sleep e dois aconteca depois do sleep quer dizer que esta correto.

A diff entre processos e multi thread e que threads compartilham o mesmo espaco na memoria e processos utilizam PID diferentes portanto nao compartilham o mesmo espaco na memoria, isso implica que o que e alterado a nivel de codigo em um codigo que use threads e alterado em todas as threads que foram abertas naquele codigo ja em processos eles nao compartilham as mesmas informacoes.

Pontos de atenção

    Copy‑on‑Write (COW)

        Após fork(), as páginas são compartilhadas até que uma das partes tente escrever; só então o kernel duplica a página. Por isso o fork não é tão caro quanto duplicar tudo imediatamente.

    Ordem de visibilidade entre threads

        Mudança feita por uma thread não é automaticamente visível em ordem para as demais sem regras de memory model. Em C, você garante isso usando mutexes, atomics ou barreiras (pthread_mutex_lock implica um acquire/release).

    Pilha

        Cada thread tem sua própria pilha, mesmo dentro do mesmo processo. Globais/heap são compartilhadas; variáveis locais não.

    IPC pode compartilhar memória

        Processos também podem ter memória comum via mmap/shm_open, então não é correto dizer que “processos não compartilham as mesmas informações”; eles não compartilham por padrão, mas o kernel oferece meios seguros de compartilhar partes que você quiser.

    Exclusão mútua interprocesso

        Mutexes “normais” (PTHREAD_PROCESS_PRIVATE) não funcionam entre processos; use semáforos POSIX ou mutexes em memória partilhada marcados PTHREAD_PROCESS_SHARED.

Resumindo

    Threads = mesmo PID, mesmo address space → alterações globais visíveis a todas, mas exigem sincronização para não haver races.

    Processos = PIDs distintos, address spaces isolados → não veem alterações uns dos outros a menos que você crie um IPC.

Então a essência da sua afirmação está correta, só adicione essas nuances de COW, pilhas separadas e possibilidade de memória compartilhada entre processos para ficar 100 % precisa.

Evitar race condition que e basicamente quando duas threads usam ponteiros que referenciam o mesmo endereço pois nao ha nenhum mecanismo de sincronizacao para uso do mesmo endereco. (Usar mutexes para resolver o problema).

pthread_mutex t_mutex;

pthread_mutex_lock() && pthread_mutex_unlock().

pthread_mutex_init() && pthread_mutex_destroy()

Caso eu queira o retorno da funcao que cada thread acessa eu preciso usar pthread_create() cria uma thread que vai acessar determinada funcao e pthread_join() bloqueia e espera o retorno da funcao enviada com o create.

Nao esquecer de criar as threads em um loop e em outro loop pegar as respostas da funcao caso eu precise do retorno delas, dessa forma eu garanto que estou fazendo em paralelo.