typedef struct Contato Contato;
typedef struct Header Header;

//Retorna um arquivo criado com header
FILE* CriaArquivoComHeader(char* caminho);
//Retorna um arquivo pronto para leitura
FILE* ArquivoParaLeitura(char* caminho);
//Retorna um arquivo pronto para escrita
FILE* ArquivoParaEscrita(char* caminho);
//Retorna um arquivo pronto para alterar
FILE* ArquivoParaAlterar(char* caminho);
//Retorna um arquivo pronto para leitura
//Se o arquivo não existir é criado um com header
FILE* AbreArquivo(char* caminho);
//Fechar arquivo
void FechaArquivo(FILE* arq);

//Retorna o Header da lista
Header* BuscaHeader(char* caminho);
//Atualiza o local que o header deve apontar
void AtualizaPonteiroHeader(long int posicao, char* caminho);
//Atualiza o local que o tail deve apontar
void AtualizaPonteiroTail(long int posicao, char* caminho);
//Retorna o local do header da lista
long int BuscaPonteiroHeader(char* caminho);
//Retorna o local do tail da lista
long int BuscaPonteiroTail(char* caminho);
//Retorna a quantidade de registros armazenado no arquivo
long int QuantidadeRegistros(char* caminho);
//Atualiza a quantidade de registros
long int AtualizaQuantidadeRegistros(char* caminho);

//Atualiza as informacoes de um contato
Contato* AtualizaContato(Contato* contato, long int posicao, char* caminho);
//Retorna um ponteiro do tipo contato
//Deve-se liberar o contato da memória após usa-lo
Contato* CriaContato(char* nome, char* sobrenome, char* telefone);
//Incrementa o id de um contato
long int IncrementaID(Contato* contato);

//Retorna o contato informado pelo nome e sobrenome
//Deve-se liberar o contato da memória após usa-lo
Contato* BuscarContatoPeloNome(char* nome, char* sobrenome, char* caminho);
//Retorna o contato da posicao passada como parametro
Contato* BuscarContatoPelaPosicao(long int posicao, char* caminho);
//Verifica se o contato esta ativo(ligado a lista) ou inativo(excluido)
//Retorna 0 se inativo
//Retorna 1 se inativo
int VerficaEstadoContato(long int posicao, char* caminho);
//Retorna a posicao do contato
long int posicaoContatoPeloId(long int id, char* caminho);
//Retorna uma posicao ideal para se armazenar um contato
//Retorna a posicao de um espaco vazio se houver
//Retorna a posicao final do arquivo se não houver
long int PosicaoParaArmazenar(char* caminho);

//Edita contato informado pelo nome
void EditaContatoPeloNome(Contato* anterior, Contato* editado, char* caminho);
//
Contato* Reordenar(Contato* contatoEditado, char* caminho);

//Insere contato na lista
void Insere(Contato* contato, char* caminho);
//Insere contato no final do arquivo
Contato* InsereContatoNoFim(Contato* contato, char* caminho);
//Insere contato Ordenado na lista
Contato* InsereOrdenado(Contato* novoContato, char* caminho, long int qtdRegistros);
//Insere contato na posicao passada por parametro
Contato* InsereContatoNaPosicao(Contato* contato, long int posicao, char* caminho);

//Lista todos os contatos
void Listar(char* caminho);

//Excui o contato pelo nome passado no parametro
void ExcuiPeloNome(char* nome, char* sobrenome, char* caminho);
//Desconecta um contato da lista
void DesconectaDaLista(Contato* contato, char* caminho);