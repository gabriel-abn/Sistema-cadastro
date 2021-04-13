#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cadastro.h"

No *Iniciar(No *pRaiz)
{
    return NULL;
}

void IniciarArvores()
{
    arvoreCPF = NULL;
    arvoreNome = NULL;
}

Info *cadastro()
{
    Info *pReturn = (Info*)malloc(sizeof(Info));
    printf("CPF: ");
    scanf("%d", &(pReturn->cpf));
    fflush(stdin);

    printf("Nome: ");
    gets(pReturn->nome);
    fflush(stdin);

    printf("Profissao: ");
    gets(pReturn->profissao);
    fflush(stdin);

    return pReturn;
}

No *criaNo(Info *p)
{
    No *insert = (No*)malloc(sizeof(No));
    insert->info = p;
    insert->pDir = NULL;
    insert->pEsq = NULL;

    return insert;
}

int inserirCPF(No **ppRaiz, Info *p)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = criaNo(p);
        return 1;
    }
    if (p->cpf < (*ppRaiz)->info->cpf)
    {
        return inserirCPF(&((*ppRaiz)->pEsq), p);
    }
    if (p->cpf > (*ppRaiz)->info->cpf)
    {
        return inserirCPF(&((*ppRaiz)->pDir), p);
    }

    return 0;
}

int inserirNome(No **ppRaiz, Info *p)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = criaNo(p);
        return 1;
    }
    for (int i = 0; i < strlen(p->nome); i++)
    {
        if (p->nome[i] < (*ppRaiz)->info->nome[i])
        {
            return inserirNome(&((*ppRaiz)->pEsq), p);
        }
        if (p->nome[i] > (*ppRaiz)->info->nome[i])
        {
            return inserirNome(&((*ppRaiz)->pDir), p);
        }
    }

    return 0;
}

void InserirCadastro(Info *pInsert)
{
    if (inserirNome(&(arvoreNome), pInsert) && inserirCPF(&(arvoreCPF), pInsert))
    {
        printf("Cadastro concluido!\n");
        printf("------------------------\n");
    }
    else
    {
        printf("Erro no cadastro: Registro ja existente!\n");
        printf("------------------------\n");
    }
}

void Display(Info *p)
{
    printf("------------------------\n");
    printf("Nome: ");
    puts(p->nome);
    printf("CPF: %d\n", p->cpf);
    printf("Profissao: ");
    puts(p->profissao);
    printf("------------------------\n");
}

void Imprimir(No *pRaiz)
{
    if(pRaiz != NULL)
    {
        Imprimir(pRaiz->pEsq);
        Display(pRaiz->info);
        Imprimir(pRaiz->pDir);
    }
}



int Pesquisa(int *i)
{
    printf("Digite um meio de pesquisa: \n");
    printf("1. Nome\n");
    printf("------------------------\n");
    printf("2. CPF\n");
    printf("------------------------\n");
    scanf("%d", i);
    fflush(stdin);

    return *i;
}

int Opcoes(int *i)
{
    printf("1. Inserir cadastro\n");
    printf("------------------------\n");
    printf("2. Pesquisar cadastro\n");
    printf("------------------------\n");
    printf("4. Imprimir cadastros\n");
    printf("------------------------\n");
    printf("5. Sair\n");
    printf("------------------------\n");
    printf("Opcao: ");
    scanf("%d", i);
    fflush(stdin);

    return *i;
}

void reset(char *c)
{
    printf("Deseja fazer outra acao? (s para SIM e n para NAO): ");
    scanf("%c", c);
    fflush(stdin);
    system("cls");
}

void Menu()
{
    IniciarArvores();
    char c = 's';
    int i;
    Info *pIns;

    do
    {
        switch (Opcoes(&i))
        {
        case 1:
            pIns = cadastro();
            InserirCadastro(pIns);
            reset(&c);
            break;
        case 2:
            
            switch (Pesquisa(&i))
            {
            case 1:
                /* code */
                break;
            case 2:
                /* code */
                break;
            
            default:
                printf("Opcao invalida! voltando...");
                break;
            }

            reset(&c);
            break;
        case 4:
            Imprimir(arvoreNome);
            printf("Fim dos cadastros!\n");
            reset(&c);
            break;
        case 5:
            printf("Saindo...");
            exit(0);
            break;
        
        default:
            printf("Opcao invalida...\n");
            reset(&c);
            break;
        }
    } while (c == 's');

    printf("Saindo...");
    exit(0);
}