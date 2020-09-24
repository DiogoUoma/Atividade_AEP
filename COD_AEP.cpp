#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


typedef struct tipoReceita
{
	int id;
	char nome [100]; //nome da receita
	char palavrasChave [5][20]; // array / 5 palavras / 20 carac
}TReceita;

//---------------------------------------------------------------------
typedef struct tipoNo
{
	tipoReceita receita;
	struct tipoNo *dir;
}TNo;

//---------------------------------------------------------------------
void lerDados(TReceita *receita)
{
	printf("\nNome da receita: ");
	fflush(stdin);
	fgets(receita->nome, 100, stdin);
	printf("\n ID: ");
	scanf("%d", &receita->id);
	
	for(int x = 1; x <= 5; x++) // Le as palavras chaves para a busca
	{
		printf("\nInforme palavras chave para busca:\nPalavra %d.: ", x);
		fflush(stdin);
		fgets(receita->palavrasChave[x], 20, stdin);
	}
	
	
}

//---------------------------------------------------------------------
TNo* inserir(TNo *raiz, TReceita *receita)
{
	if(raiz == NULL)
	{
		raiz = new TNo;
		raiz->receita.id = receita->id;
		strcpy(raiz->receita.nome, receita->nome);
		
		for(int aux = 1; aux <=5; aux++)
		{
			strcpy(raiz->receita.palavrasChave[aux], receita->palavrasChave[aux]);
		}
		
		raiz->dir = NULL;
	}
	else
	{
		raiz->dir = inserir(raiz->dir, receita);	
	}
	
	return raiz;
}

//---------------------------------------------------------------------
void apresentar(TNo *raiz)
{
	if(raiz != NULL)
	{
		printf("\nNome................: %s", raiz->receita.nome);
		printf("\nID..................: %d", raiz->receita.id);
		printf("\n\n-----------------------------------------------------\n\n");
		
		apresentar(raiz->dir);
	}
	
	
}

//---------------------------------------------------------------------

int busca(TNo *raiz)
{
	char palavraBusca[20];
	int x = 0, comp;
	
	printf("\n\nPalavra chave da receita que deseja-se buscar.:  ");
	fflush(stdin);
	fgets(palavraBusca, 20, stdin);
	
	while(raiz != NULL)
	{
		for(int aux = 1; aux <= 5; aux++)
		{
			comp = strncmp(raiz->receita.palavrasChave[aux], palavraBusca, 20);
			if(comp == 0)
			{
				x++;
				break;
			}
		}
		raiz = raiz->dir;
	
	}
	
	return x;
}

//---------------------------------------------------------------------

TNo* remover(TNo *raiz, int auxID)
{
	TNo *atual, *anterior;
	atual = raiz;
	anterior = raiz;
	
	while(atual != NULL)
	{
		if(atual->receita.id == auxID)
		{
			free(atual);
			anterior->dir = atual->dir;
			atual->dir = NULL;
			break;
		}
		else
		{
			anterior = atual;
			atual = atual->dir;
		}
	}
	

	return raiz;
}

//---------------------------------------------------------------------
int main()
{
	TNo *raiz;
	raiz = NULL;
	
	TReceita receita;
	
	int opcao, aux = 0;
	
	do
	{
		printf("\n1 - Cadastrar receita");
		printf("\n2 - Pesquisar receita");
		printf("\n3 - Apresentar receitas");
		printf("\n4 - Remover receita");
		printf("\n0 - Sair");
		printf("\nEscolha opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao)
		{
			case 1:
				{
					lerDados(&receita);
					raiz = inserir(raiz, &receita);
					printf("\nReceita inserida!");
					getch();
					system("cls");
					break;
				}
				
			case 2:
				{
					int encontrou;
					encontrou = busca(raiz);
					if(encontrou >= 1)
					{
						printf("\n %d receitas encontrada(s)!", encontrou);
					}
					else
					{
						printf("\nNenhuma receita encontrada!");
						printf("     %d", encontrou);
					}
					
					getch();
					system("cls");
					break;
				}
			case 3:
				{
					apresentar(raiz);
					getch();
					system("cls");
					break;
				}
			case 4:
				{
					int auxID;
					printf("\nQual o id da receita a ser excluida?\n");
					scanf("\n%d", &auxID);
					
					raiz = remover(raiz, auxID);
					
					system("cls");
				}
		}
	}while (opcao != 0);
	
}
