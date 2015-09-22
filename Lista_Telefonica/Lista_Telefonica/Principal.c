#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaTelefonica.h"

#define CAMINHO_ARQUIVO "../arquivo.bin"

void MenuPrincipal();
void RedirecionaOpcao(int op);
void CadastrarContato();
void Edicao();
void ExcuirContato();
void EditaContatoPorNome();
Contato* InformacoesContato();

int main()
{
	MenuPrincipal();
	return 0;
}

void MenuPrincipal() {
	int op = 0;
	do {
		op = 0;
		while (op <= 0 || op > 5) {
			printf("Escolha uma opcao: \n\n");
			printf("1 - Adicionar contato\n");
			printf("2 - Editar contato\n");
			printf("3 - Remover contato\n");
			printf("4 - Listar todos os contatos\n");
			printf("5 - Sair\n\n");
			scanf_s("%d", &op);
			fflush(stdin);
			if (op <= 0 || op > 5) {
				printf("Insira um valor valido!\n");
				system("pause");
			}
			system("cls");
		}
		RedirecionaOpcao(op);
		system("pause");
		system("cls");
	} while (op != 5);
	return op;
}

void RedirecionaOpcao(int op) {
	AbreArquivo(CAMINHO_ARQUIVO);
	switch (op) {
	case 1:
		CadastrarContato();
		break;
	case 2:
		Edicao();
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
	printf("----Cadastrar Contato----\n\n");

	Contato* contato = InformacoesContato();

	Insere(contato, CAMINHO_ARQUIVO);

	free(contato);
}

void ExcuirContato() {
	char nome[20], sobrenome[20];

	printf("----Excuir Contato----\n\n");
	printf("Digite as informacoes do contato que deseja excuir:\n\n");
	printf("Digite o nome do contato: \n");
	scanf("%s", &nome);
	fflush(stdin);
	printf("Digite o sobrenome do contato: \n");
	scanf("%s", &sobrenome);
	fflush(stdin);

	ExcuiPeloNome(nome, sobrenome, CAMINHO_ARQUIVO);
}

void Edicao() {
	int op = 0;
	printf("----Editar Contato----\n\n");
	do {
		printf("Escolha uma opcao: \n");
		printf("1 - Alterar contato pelo nome\n");
		printf("2 - Alterar contato pelo telefone\n");
		printf("3 - Voltar\n\n");
		scanf("%d", &op);
		fflush(stdin);
		if (op < 1 || op > 3)
			printf("Digite uma opcao valida");
	} while (op < 1 || op > 3);
	system("cls");
	switch (op)
	{
	case 1:
		EditaContatoPorNome();
		break;
	case 2:
		break;
	case 3:
		return;
		break;
	}
}

void EditaContatoPorNome() {
	char nome[20], sobrenome[20];
	Contato* anterior;
	Contato* editado;

	printf("----Editar Contato----\n\n");
	printf("Digite as informacoes do contato que deseja editar!\n\n");
	printf("Digite o nome do contato: \n");
	scanf("%s", &nome);
	fflush(stdin);
	printf("Digite o sobrenome do contato: \n");
	scanf("%s", &sobrenome);
	fflush(stdin);
	system("cls");
	printf("----Editar Contato----\n\n");
	printf("Digite as novas informacoes desse contato!\n\n");
	anterior = BuscarContatoPeloNome(nome, sobrenome, CAMINHO_ARQUIVO);
	if (anterior != NULL) {
		editado = InformacoesContato();
		EditaContatoPeloNome(anterior, editado, CAMINHO_ARQUIVO);
		free(editado);
	}
	else {
		printf("Esse contato nao existe!\n");
	}

	free(anterior);
}

Contato* InformacoesContato() {
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

	return contato;
}