#include<stdlib.h>
#include<stdio.h>
#include "cadastro.h"


int altura(No *pRaiz)
{
    int hEsq, hDir;
    if (pRaiz == NULL)
    {
        return 0;
    }
    
    hEsq = altura(pRaiz->pEsq);
    hDir = altura(pRaiz->pDir);

    if (hEsq > hDir)
    {
        return hEsq+1;
    }
    else
    {
        return hDir+1;
    }
}

void LL(No **pA)
{
    No *pB;
    pB = (*pA)->pEsq;
    (*pA)->pEsq = pB->pDir;
    pB->pDir = (*pA);
    (*pA) = pB;
}

void RR(No **pA)
{
    No *pB;
    pB = (*pA)->pDir;
    (*pA)->pDir = pB->pEsq;
    pB->pEsq = (*pA);
    (*pA) = pB;
}

void LR(No **pA)
{
    No *pB, *pC;
    pB = (*pA)->pEsq;
    pC = pB->pDir;
    pB->pDir = pC->pEsq;
    pC->pEsq = pB;
    (*pA)->pEsq = pC->pDir;
    pC->pDir = (*pA);
    (*pA) = pC;
}

void RL(No **pA)
{
    No *pB, *pC;
    pB = (*pA)->pDir;
    pC = pB->pEsq;
    pB->pEsq = pC->pDir;
    pC->pDir = pB;
    (*pA)->pDir = pC->pEsq;
    pC->pEsq = (*pA);
    (*pA) = pC;
}

int fator_balnc(No *pRaiz)
{
    if (pRaiz == NULL)
    {
        return 0;
    }
    return altura(pRaiz->pEsq) - altura(pRaiz->pDir);
}

int balanceamento(No **ppRaiz)
{
    int fat_b = fator_balnc(*ppRaiz);

    if (fat_b > 1)
    {
        int fb_esq = fator_balnc((*ppRaiz)->pEsq);

        if (fb_esq > 0)
        {
            LL(ppRaiz);
            return 1;
        } else
        if (fb_esq < 0)
        {
            LR(ppRaiz);
            return 1;
        }
        
        return 0;
    } else
    if (fat_b < -1)
    {
        int fb_dir = fator_balnc((*ppRaiz)->pDir);

        if (fb_dir > 0)
        {
            RR(ppRaiz);
            return 1;
        } else
        if (fb_dir < 0)
        {
            RL(ppRaiz);
            return 1;
        }
        
        return 0;
    } 
    else
    {
        return 0;
    }
    
}
