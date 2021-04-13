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

Info *cadastroInserir()
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

int pesquisaCPF(No *pRaiz, Info *pInfo)
{
    if (pRaiz == NULL)
    {
        printf("Registro nao encontrado...\n");
        return 0;
    }
    if (pInfo->cpf > pRaiz->info->cpf)
    {
        return pesquisaCPF(pRaiz->pDir, pInfo);
    }
    if (pInfo->cpf < pRaiz->info->cpf)
    {
        return pesquisaCPF(pRaiz->pEsq, pInfo);
    }

    *pInfo = *pRaiz->info;
    Display(pInfo);
    return 1;
}

int pesquisaNome(No *pRaiz, Info *pInfo)
{
    if (pRaiz == NULL)
    {
        printf("Registro nao encontrado...\n");
        return 0;
    }
    for (int i = 0; i < strlen(pInfo->nome); i++)
    {
        if (pInfo->nome[i] > pRaiz->info->nome[i])
        {
            return pesquisaNome(pRaiz->pDir, pInfo);
        }
        if (pInfo->nome[i] < pRaiz->info->nome[i])
        {
            return pesquisaNome(pRaiz->pEsq, pInfo);
        }
    }

    *pInfo = *pRaiz->info;
    Display(pInfo);
    return 1;
}

void sucessor(No *folha, No **ppRaiz)
{
    No *pAux;

    if ((*ppRaiz)->pEsq != NULL)
    {
        sucessor(folha, &(*ppRaiz)->pEsq);
    }

    *folha->info = *(*ppRaiz)->info;
    pAux = *ppRaiz;
    *ppRaiz = (*ppRaiz)->pDir;
    free(pAux);
}

int retirarCPF(No **ppRaiz, Info *r)
{
    if (*ppRaiz == NULL)
    {
        return 0;
    }
    
    if ((*ppRaiz)->info->cpf > r->cpf)
    {
        if (retirarCPF(&((*ppRaiz)->pEsq), r))
        {
            if (balanceamento(ppRaiz))
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    else 
        if ((*ppRaiz)->info->cpf < r->cpf)
        {
            if (retirarCPF(&((*ppRaiz)->pDir), r))
            {
                if (balanceamento(ppRaiz))
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
        }
        else if ((*ppRaiz)->info->cpf == r->cpf)
        {
            No *pAux;
            *r = *(*ppRaiz)->info;

            if ((*ppRaiz)->pDir == NULL)
            {
                pAux = *ppRaiz;
                *ppRaiz = (*ppRaiz)->pEsq;
                free(pAux);
                if (balanceamento(ppRaiz))
                {
                    return 1;
                }
                return 0;
            }
            if ((*ppRaiz)->pEsq == NULL)
            {
                pAux = *ppRaiz;
                *ppRaiz = (*ppRaiz)->pDir;
                free(pAux);
                if (balanceamento(ppRaiz))
                {
                    return 1;
                }
                return 0;
            }
        }
    sucessor(*ppRaiz, &(*ppRaiz)->pDir);
    if (balanceamento(ppRaiz))
    {
        return 1;
    }
    return 0;
}

int retirarNome(No **ppRaiz, Info *r)
{
    if (*ppRaiz == NULL)
    {
        return 0;
    }
    for (int i = 0; i < strlen(r->nome); i++)
    {
        if ((*ppRaiz)->info->nome[i] > r->nome[i])
        {
            if (retirarNome(&((*ppRaiz)->pEsq), r))
            {
                if (balanceamento(ppRaiz))
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
        }
        else 
            if ((*ppRaiz)->info->nome[i] < r->nome[i])
            {
                if (retirarNome(&((*ppRaiz)->pDir), r))
                {
                    if (balanceamento(ppRaiz))
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if ((*ppRaiz)->info->nome[i] == r->nome[i])
            {
                No *pAux;
                *r = *(*ppRaiz)->info;

                if ((*ppRaiz)->pDir == NULL)
                {
                    pAux = *ppRaiz;
                    *ppRaiz = (*ppRaiz)->pEsq;
                    free(pAux);
                    if (balanceamento(ppRaiz))
                    {
                        return 1;
                    }
                    return 0;
                }
                if ((*ppRaiz)->pEsq == NULL)
                {
                    pAux = *ppRaiz;
                    *ppRaiz = (*ppRaiz)->pDir;
                    free(pAux);
                    if (balanceamento(ppRaiz))
                    {
                        return 1;
                    }
                    return 0;
                }
            }
    } 
    sucessor(*ppRaiz, &(*ppRaiz)->pDir);
    if (balanceamento(ppRaiz))
    {
        return 1;
    }
    return 0;
}

void InserirCadastro(Info *pInsert)
{
    if (inserirNome(&(arvoreNome), pInsert) && inserirCPF(&(arvoreCPF), pInsert))
    {
        if (!(balanceamento(&(arvoreCPF)) && balanceamento(&(arvoreNome))))
        {
            printf("Cadastro concluido!\n");
            printf("------------------------\n");
        }
    }
    else
    {
        printf("Erro no cadastro: Registro ja existente!\n");
        printf("------------------------\n");
    }
}

void RetirarCadastro(Info *pRemove)
{    
    if (!(retirarNome(&(arvoreNome), pRemove) && retirarCPF(&(arvoreCPF), pRemove)))
    {
        printf("Cadastro retirado!\n");
        printf("------------------------\n");
        Display(pRemove);
    }
    else
    {
        printf("Erro!\n");
        printf("------------------------\n");
    }
}

int PesqInfo(int *i)
{
    printf("Digite um meio de pesquisa: \n");
    printf("1. Nome\n");
    printf("------------------------\n");
    printf("2. CPF\n");
    printf("------------------------\n");
    printf("Opcao: ");
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
    printf("3. Retirar cadastro\n");
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
    Info *pPes = (Info*)malloc(sizeof(Info));

    do
    {
        switch (Opcoes(&i))
        {
        case 1:
            pIns = cadastroInserir();
            InserirCadastro(pIns);
            reset(&c);
            break;
        case 2:
            system("cls");
            switch (PesqInfo(&i))
            {
            case 1:
                printf("Digite o nome: ");
                gets(pPes->nome);
                fflush(stdin);
                pesquisaNome(arvoreNome, pPes);
                break;
            case 2:
                printf("Digite o CPF: ");
                scanf("%d", &(pPes->cpf));
                fflush(stdin);
                pesquisaCPF(arvoreCPF, pPes);
                break;
            
            default:
                printf("Opcao invalida! voltando...");
                break;
            }

            reset(&c);
            break;
        case 3:
            system("cls");
            switch (PesqInfo(&i))
            {
            case 1:
                printf("Digite o nome: ");
                gets(pPes->nome);
                fflush(stdin);

                if (pesquisaNome(arvoreNome, pPes));

                RetirarCadastro(pPes);
                break;
            case 2:
                printf("Digite o CPF: ");
                scanf("%d", &(pPes->cpf));
                fflush(stdin);

                if (pesquisaCPF(arvoreCPF, pPes));

                RetirarCadastro(pPes);
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