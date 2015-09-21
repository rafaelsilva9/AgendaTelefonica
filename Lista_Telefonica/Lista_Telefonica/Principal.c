#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaTelefonica.h"

#define CAMINHO_ARQUIVO "../arquivo.bin"

int OpcoesPrincipal();
void MenuPrincipal(int op);
void CadastrarContato();
void ExcuirContato();

int main()
{
	MenuPrincipal(OpcoesPrincipal());
	return 0;
}

int OpcoesPrincipal() {
	int op = 0;
	while (op <= 0 || op > 5) {
		printf("Escolha uma opcao: \n\n");
		printf("1 - Adicionar contato\n");
		printf("2 - Editar contato\n");
		printf("3 - Remover contato\n");
		printf("4 - Listar todos os contatos\n");
		printf("5 - Sair\n");
		scanf_s("%d", &op);
		if (op <= 0 || op > 5)
			printf("Insira um valor valido!\n");
	}
	return op;
}

void MenuPrincipal(int op) {
	AbreArquivo(CAMINHO_ARQUIVO);
	switch (op) {
	case 1:
		CadastrarContato();
		break;
	case 2:
		break;
	case 3:
		ExcuirContato();
		break;
	case 4:
		Listar(CAMINHO_ARQUIVO);
		break;
	case 5:
		exit(1);
		break;
	}
}

void CadastrarContato() {
	Contato* contato;
	char nome[20], sobrenome[20], telefone[20];

	printf("Digite o nome do contato: \n");
	scanf("%s", &nome);
	fflush(stdin);
	printf("Digite o sobrenome do contato: \n");
	scanf("%s", &sobrenome);
	fflush(stdin);
	printf("Digite o telefone do contato: \n");
	scanf("%s", &telefone);
	fflush(stdin);
	contato = CriaContato(nome, sobrenome, telefone);
	
	Insere(contato, CAMINHO_ARQUIVO);

	free(contato);
}

void ExcuirContato() {
	char nome[20], sobrenome[20];
	printf("Digite as informacoes do contato que deseja excuir:\n\n");
	printf("Digite o nome do contato: \n");
	scanf("%s", &nome);
	fflush(stdin);
	printf("Digite o sobrenome do contato: \n");
	scanf("%s", &sobrenome);
	fflush(stdin);

	ExcuiPeloNome(nome, sobrenome, CAMINHO_ARQUIVO);
}