typedef struct TipoCadastro
{
    int cpf;
    char nome[50];
    char profissao[50];
}Info;

typedef struct TipoNo
{
    Info *info;
    struct TipoNo *pEsq;
    struct TipoNo *pDir;
}No;

No *arvoreCPF;
No *arvoreNome;

No *Iniciar(No *);
void IniciarArvores();
Info *cadastro();
No *criaNo(Info *);
int inserirCPF(No **, Info *);
int inserirNome(No **, Info *);
void InserirCadastro(Info *);
int Opcoes(int *);
void reset(char *);
void Menu();

int altura(No *);
void LL(No **);
void RR(No **);
void LR(No **);
void RL(No **);
int fator_balnc(No *);
int balanceamento(No **);