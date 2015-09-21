typedef struct Contato Contato;
typedef struct Header Header;

Header* BuscaHeader(char* caminho);
void AtualizaPonteiroHeader(long int posicao, char* caminho);
void AtualizaPonteiroTail(long int posicao, char* caminho);
long int BuscaPonteiroHeader(char* caminho);
long int BuscaPonteiroTail(char* caminho);

Contato* AtualizaContato(Contato* contato, long int posicao, char* caminho);
Contato* CriaContato(char* nome, char* sobrenome, char* telefone);
long int IncrementaID(Contato* contato);
Contato* BuscarContatoPeloNome(char* nome, char* sobrenome, char* caminho);
Contato* BuscarContatoPelaPosicao(long int posicao, char* caminho);
int VerficaEstadoContato(long int posicao, char* caminho);

FILE* CriaArquivoComHeader(char* caminho);
FILE* ArquivoParaLeitura(char* caminho);
FILE* ArquivoParaEscrita(char* caminho);
FILE* ArquivoParaAlterar(char* caminho);
FILE* AbreArquivo(char* caminho);
void FechaArquivo(FILE* arq);

void Insere(Contato* contato, char* caminho);
Contato* InsereContatoNoFim(Contato* contato, char* caminho);
Contato* InsereOrdenado(Contato* novoContato, char* caminho, long int qtdRegistros);
Contato* InsereContatoNaPosicao(Contato* contato, long int posicao, char* caminho);

void Listar(char* caminho);
void ExcuiPeloNome(char* nome, char* sobrenome, char* caminho);
void DesconectaDaLista(Contato* contato, char* caminho);

long int QuantidadeRegistros(char* caminho);
long int AtualizaQuantidadeRegistros(char* caminho);
long int posicaoContatoPeloId(long int id, char* caminho);
long int PosicaoParaArmazenar(char* caminho);