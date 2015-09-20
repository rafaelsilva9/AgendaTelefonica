#include <stdio.h>
#include "ListaTelefonica.h"
#include <string.h>

#define CAMINHO_ARQUIVO "../arquivo.bin"
#define TAMANHO_HEADER sizeof(Header)
#define TAMANHO_CONTATO sizeof(Contato)

struct Contato {
	long int id;
	char nome[20];
	char sobrenome[20];
	char telefone[20];
	long int prox;
} typedef Contato;

struct Header {
	long int qtdRegistros;
	long int head;
	long int tail;
} typedef Header;

FILE* AbreArquivo(char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	if (arq == NULL) {
		return CriaArquivoComHeader(caminho);
	}
	else {
		printf("Arquivo aberto com sucesso!\n");
		return arq;
	}
}

FILE* ArquivoParaLeitura(char* caminho) {
	FILE* arq = fopen(caminho, "rb");
	if (arq == NULL) {
		return NULL;
	}
	else
		return arq;
}

FILE* ArquivoParaEscrita(char* caminho) {
	FILE* arq = fopen(caminho, "a+b");
	if (arq == NULL) {
		return NULL;
	}
	else
		return arq;
}

FILE* ArquivoParaAlterar(char* caminho) {
	FILE* arq = fopen(caminho, "r+b");
	if (arq == NULL) {
		return NULL;
	}
	else
		return arq;
}

long int QuantidadeRegistros(char* caminho) {
	FILE* arq;
	Header header;
	long int qtdegistros;

	arq = ArquivoParaLeitura(caminho);

	if (arq != NULL)
	{
		fread(&header, TAMANHO_HEADER, 1, arq);
		return header.qtdRegistros;
	}
	else
		return NULL;

}

FILE* CriaArquivoComHeader(char* caminho) {
	FILE* arq = ArquivoParaEscrita(caminho);
	Header header;

	header.head = -1;
	header.tail = -1;
	header.qtdRegistros = 0;
	if (fwrite(&header, TAMANHO_HEADER, 1, arq) == 1) {
		fflush(arq);
		printf("Um arquivo foi criado em %s\n", caminho);
		free(header);
		return arq;
	}
	else
	{
		printf("O arquivo não pode ser criado!\n");
		return NULL;
	}
}

void FechaArquivo(FILE* arq) {
	if (fclose(arq))
		printf("Arquivo fechado com sucesso!\n");
	else
		printf("Arquivo fechado com sucesso!\n");
}

void Insere(Contato* novoContato, char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Contato cadastro, anterior;
	long int qtdRegistros = QuantidadeRegistros(caminho);

	if (qtdRegistros != 0)
	{
		InsereOrdenado(novoContato, caminho, qtdRegistros);
	}
	else {
		fclose(arq);
		novoContato->prox = -1;
		InsereContato(novoContato, caminho);
		AtualizaPonteiroHeader(TAMANHO_HEADER, caminho);
		AtualizaPonteiroTail(TAMANHO_HEADER, caminho);
	}
}

Contato* InsereOrdenado(Contato* novoContato, char* caminho, long int qtdRegistros) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Contato contato, anterior;
	int qtdPosicao = 0, existeSucessor = 0;

	fseek(arq, BuscaPonteiroHeader(caminho), SEEK_SET);
	
	do {
		fread(&contato, TAMANHO_CONTATO, 1, arq);
		if (strcmp(contato.nome, novoContato->nome) < 0)
		{
			anterior = contato;
			anterior.prox = TAMANHO_CONTATO * qtdRegistros + TAMANHO_HEADER;
			novoContato->prox = contato.prox;
			qtdPosicao++;
			existeSucessor = 1;
		}
		else if (strcmp(contato.nome, novoContato->nome) == 0) {
			if (strcmp(contato.sobrenome, novoContato->sobrenome) < 1)
			{
				anterior = contato;
				anterior.prox = TAMANHO_CONTATO * qtdRegistros + TAMANHO_HEADER;
				novoContato->prox = contato.prox;
				qtdPosicao++;
				existeSucessor = 1;
			}
		}
		fseek(arq, contato.prox, SEEK_SET);
	} while (contato.prox != -1);
	fclose(arq);

	if (existeSucessor)
	{
		AtualizaContato(&anterior, posicaoContatoPeloId(anterior.id, caminho), caminho);
		if (qtdRegistros == qtdPosicao)
		{
			AtualizaPonteiroTail(TAMANHO_CONTATO * qtdRegistros + TAMANHO_HEADER, caminho);
		}

	}
	else {
		novoContato->prox = BuscaPonteiroHeader(caminho);
		AtualizaPonteiroHeader(TAMANHO_CONTATO * qtdRegistros + TAMANHO_HEADER, caminho);
	}

	InsereContato(novoContato, caminho);
	return novoContato;
}

Contato* AtualizaContato(Contato* contato, long int posicao, char* caminho) {
	FILE* arq = ArquivoParaAlterar(caminho);

	fseek(arq, posicao, SEEK_SET);
	fwrite(contato, TAMANHO_CONTATO, 1, arq);
	fflush(arq);
	fclose(arq);

	return contato;
}

Contato* InsereContato(Contato* contato, char* caminho) {
	FILE* arq = ArquivoParaEscrita(caminho);
	int resultado;

	IncrementaID(contato, caminho);

	if (fwrite(contato, TAMANHO_CONTATO, 1, arq) == 1) {
		fflush(arq);
		resultado = 1;
		//AtualizaHeader();
		AtualizaQuantidadeRegistros(caminho);
	}
	else
	{
		resultado = 0;
	}

	fclose(arq);

	if (resultado) {
		printf("Contato registrado com sucesso!\n");
		return contato;
	}
	else {
		printf("Não foi possivel cadastrar contato!\n");
		return NULL;
	}
}

long int IncrementaID(Contato* contato, char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Header header;
	long int novaQuantidade;

	fread(&header, TAMANHO_HEADER, 1, arq);
	novaQuantidade = header.qtdRegistros + 1;
	contato->id = novaQuantidade;
	fclose(arq);

	return novaQuantidade;
}

Header* BuscaHeader(char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Header header;

	fread(&header, TAMANHO_HEADER, 1, arq);
	fclose(arq);

	return &header;
}

long int AtualizaQuantidadeRegistros(char* caminho) {
	FILE* arq = ArquivoParaAlterar(caminho);
	Header header;
	long int novaQuantidade;

	header = *BuscaHeader(caminho);
	novaQuantidade = header.qtdRegistros + 1;
	header.qtdRegistros = novaQuantidade;

	if (fwrite(&header, TAMANHO_HEADER, 1, arq) == 1) {
		fflush(arq);
	}
	fclose(arq);

	return novaQuantidade;
}

void AtualizaPonteiroHeader(long int posicao, char* caminho) {
	FILE* arq = ArquivoParaAlterar(caminho);
	Header header;

	header = *BuscaHeader(caminho);
	header.head = posicao;

	fwrite(&header, TAMANHO_HEADER, 1, arq);
	fflush(arq);
	fclose(arq);
}

long int BuscaPonteiroHeader(char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Header header;
	long int posicao;

	fread(&header, TAMANHO_HEADER, 1, arq);
	posicao = header.head;

	return posicao;
}

long int BuscaPonteiroTail(char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Header header;
	long int posicao;

	fread(&header, TAMANHO_HEADER, 1, arq);
	posicao = header.tail;

	return posicao;
}

void AtualizaPonteiroTail(long int posicao, char* caminho) {
	FILE* arq = ArquivoParaAlterar(caminho);
	Header header;

	header = *BuscaHeader(caminho);
	header.tail = posicao;

	fwrite(&header, TAMANHO_HEADER, 1, arq);
	fflush(arq);
	fclose(arq);
}

void Listar(char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Contato contato;

	printf("------ Lista de Contatos ------ \n\n");
	fseek(arq, BuscaPonteiroHeader(caminho), SEEK_SET);
	do
	{
		fread(&contato, TAMANHO_CONTATO, 1, arq);

		printf("Id: %d\n", contato.id);
		printf("Nome: %s\n", contato.nome);
		printf("Sobrenome: %s\n", contato.sobrenome);
		printf("Telefone: %s\n", contato.telefone);
		printf("\n");
		fseek(arq, contato.prox, SEEK_SET);
	} while (contato.prox != -1);
	fclose(arq);
}

Contato* CriaContato(char* nome, char* sobrenome, char* telefone) {
	Contato* contato = (Contato*)malloc(TAMANHO_CONTATO);
	strcpy(contato->nome, nome);
	strcpy(contato->sobrenome, sobrenome);
	strcpy(contato->telefone, telefone);
	return contato;
}

long int posicaoContatoPeloId(long int id, char* caminho) {
	FILE* arq = ArquivoParaLeitura(caminho);
	Contato contato;
	long int posicao = 12;

	fseek(arq, TAMANHO_HEADER, SEEK_SET);
	fread(&contato, TAMANHO_CONTATO, 1, arq);
	while (!feof(arq)) {
		if (contato.id == id)
			break;
		posicao += TAMANHO_CONTATO;
		fread(&contato, TAMANHO_CONTATO, 1, arq);
	}

	return posicao;
}

void Excuir(char* caminho) {

}