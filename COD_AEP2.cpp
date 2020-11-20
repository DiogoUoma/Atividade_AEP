#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


typedef struct tipoReceita
{
	int id;
	char nome[100];
	char palavrasChaves[20];
	int info;
	struct tipoReceita *proximo;
}TReceita;
// ---------------------------------------------------
typedef struct tipoLista
{
	TReceita *inicio;
	TReceita *fim;
}TLista;
// ---------------------------------------------------
TLista tabelaHashing[20];
// ---------------------------------------------------
int hash(int info)
{
	return info % 5;
}
// ---------------------------------------------------
void inicializar()
{
	for(int i = 0; i < 20; i++)
	{
		tabelaHashing[i].inicio = NULL;
		tabelaHashing[i].fim = NULL;
	}
}
// ---------------------------------------------------
void inserir()
{
	TReceita *receita;
	receita = new  TReceita;
	int indice;
	
	printf("\n Informe o nome da receita: ");
	fflush(stdin);
	fgets(receita->nome, 100, stdin);
	
	printf("\n Informe o id da receita: ");
	scanf("%d", &receita->id);
	receita->proximo = NULL;
	

	printf("\nInforme a palavra chave: ");
	fflush(stdin);
	fgets(receita->palavrasChaves, 20, stdin);

	
	indice = hash(receita->id);
	
	if(tabelaHashing[indice].inicio == NULL)
	{
		tabelaHashing[indice].inicio = receita;
		tabelaHashing[indice].fim = receita;
	}
	else
	{
		tabelaHashing[indice].fim->proximo = receita;
		tabelaHashing[indice].fim = receita;
	}
	
	system("cls");
}
// ---------------------------------------------------
void apresentar()
{
	int i;
	
	for(i = 0; i <= 20; i++)
	{
		TReceita *aux;
		aux = tabelaHashing[i].inicio;
		
		if(aux != NULL)
		{
			printf("\nIndice: %d - ", i);
			while(aux != NULL)
			{
				printf("%d | ", aux->id);
				aux = aux->proximo;
			}
		}
		else
		{
			printf("\nIndice: %d - / ", i);
		}
			
	}
	
	getch();
	system("cls");
}
// ---------------------------------------------------
void excluir()
{
	int valexclui;
	
	printf("\n Informe o id da receita que deseja-se excluir: ");
	scanf("%d", &valexclui);
	
	int indice;
	indice = hash(valexclui);
	
	TReceita *atual;
	TReceita *anterior;
	
	atual = tabelaHashing[indice].inicio;
	anterior = tabelaHashing[indice].inicio;
	
	while(atual != NULL)
	{
		if(atual->id == valexclui)
		{
			if(atual == tabelaHashing[indice].inicio)
			{
				tabelaHashing[indice].inicio = atual->proximo;
			}
			else
			{
				anterior->proximo = atual->proximo;
				if(atual == tabelaHashing[indice].fim)
				{
					tabelaHashing[indice].fim = anterior;
				}
			}
			break;
		}
		else
		{
			anterior = atual;
			atual->proximo;
		}
	}
	
	if(atual != NULL)
	{
		printf("\n Receita excluida!");
		free(atual);
	}
	else
	{
		printf("\n Receita nao existe!");
	}
	
	getch();
	system("cls");
}
// ---------------------------------------------------
void consultar()
{
	int consulta;
	int cont = 0, comp;
	
	printf("\n Informe id da receita a ser consultada: ");
	scanf("%d", &consulta);
	
	int indice;
	indice = hash(consulta);
	
	TReceita *aux;
	aux = tabelaHashing[indice].inicio;
	
	while(aux != NULL)
	{
		if(aux->id == consulta)
		{
			printf("\n Receita encontrada!");
			break;
		}
		else
		{
			aux = aux->proximo;
		}
	}
	
	if(aux == NULL)
	{
		printf("\n Receita nao encontrada!");
	}
	
	getch();
	system("CLS");
	 
}
// ---------------------------------------------------
int main()
{
	int opcao;
	inicializar();
	
	do
	{
		printf("\n 1- Inserir receita");
		printf("\n 2- Consultar receita pelo ID");
		printf("\n 3- Apresentar espalhamento por ID");
		printf("\n 4- Excluir receita pelo ID");
		printf("\n 0- Sair");
		printf("\n Opcao: ");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1:
				inserir();
				break;
			case 2:
				consultar();
				break;
			case 3:
				apresentar();
				break;
			case 4:
				excluir();
				break;
		}
	}while(opcao != 0);
}
