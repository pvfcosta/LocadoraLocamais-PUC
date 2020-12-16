#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Clientes

struct Ttelefone
{
    int ddd;
    float numero;
};
typedef struct Ttelefone tel;

struct Tendereco
{
    int numero;
    char rua[20],complemento[15],bairro[20],cidade[20],uf[3],cep[10];
};
typedef struct Tendereco ender;

struct Tclientes
{
    int codigo;
    tel telefone;
    ender endereco;
    char nome[30];
};
typedef struct Tclientes cliente;

//Funcionário

struct Tfuncionario
{
    int codigo,salario;
    tel telefone;
    char nome[30],cargo[30];
};
typedef struct Tfuncionario funcionario;

//Locação

struct Tdata
{
    int dia,mes,ano;
};
typedef struct Tdata dt;

struct Tlocacao
{
    int codigo,seguro,dias,cod_c,cod_v;
    dt dataRet;
    dt dataDev;
    dt dataEnt;
};
typedef struct Tlocacao locacao;

//Veiculo

struct Tveiculo
{
    int codigo,qnt,status;
    char descricao[100],modelo[30],cor[30],placa[9];
    float valor;
};
typedef struct Tveiculo veiculo;


int main()
{
    FILE *aclientes;
    FILE *afuncionarios;
    FILE *aveiculos;
    FILE *alocacao;

    int op;
    setlocale(LC_ALL,"portuguese");

//    Incializando os arquivos

    if ((aclientes=fopen("aclientes.dat","r+b"))==NULL)
    {
        printf("Arquivo não existia ... criando novo arquivo!");
        if ((aclientes=fopen("aclientes.dat","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((afuncionarios=fopen("afuncionarios.dat","r+b"))==NULL)
    {
        printf("Arquivo não existia ... criando novo arquivo!");
        if ((afuncionarios=fopen("afuncionarios.dat","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((aveiculos=fopen("aveiculos.dat","r+b"))==NULL)
    {
        printf("Arquivo não existia ... criando novo arquivo!");
        if ((aveiculos=fopen("aveiculos.dat","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }

    if ((alocacao=fopen("alocacao.dat","r+b"))==NULL)
    {
        printf("Arquivo não existia ... criando novo arquivo!");
        if ((alocacao=fopen("alocacao.dat","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }

//   MENU


    do
    {
        printf("Escolha:\n");
        printf("1- Cadastrar um cliente\n");
        printf("2- Cadastrar um funcionário\n");
        printf("3- Cadastrar locação\n");
        printf("4- Cadastrar veículo\n");
        printf("5- Premiação\n");
        printf("6- Imprimir dados do cliente\n");
        printf("7- Imprimir dados do funcionário\n");
        printf("8- Imprimir dados de locação do cliente\n");
        printf("9 - Sair do programa\n");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            inclui_cliente(aclientes);
            break;
        case 2:
            inclui_funcionario(afuncionarios);
            break;
        case 3:
            inclui_locacao(alocacao,aclientes,aveiculos);
            break;
        case 4:
            inclui_veiculo(aveiculos);
            break;
        case 5:
            imprime_veiculo(aveiculos);
            system("pause");
            break;
        case 6:
            imprime_cliente(aclientes);
            system("pause");
            break;
        case 7:
            imprime_funcionario(afuncionarios);
            system("pause");
            break;
        case 8:
            imprime_locacao(alocacao);
            system("pause");
            break;
        case 10:
            baixa_locacao(alocacao,aclientes,aveiculos);
            break;
        case 11:
            pesquisaClienteFuncionario(afuncionarios,aclientes);
            break;
        case 12:
            buscalocacoescliente(aclientes,alocacao);
            break;
        case 13:
            calcula_pontos(aclientes,alocacao);
            break;
        case 14:
            ganhaouKit(aclientes,alocacao);
            break;

        }
        if (op!=9)
        {
            system("pause");
        }
        system("cls");
    }
    while(op!=9);
    fclose(aclientes);
    fclose(afuncionarios);
    fclose(aveiculos);
    fclose(alocacao);
    return 0;

}

int localiza_cliente(FILE *aclientes,int codigo, char nome[30])
{
    int posicao=-1,achou=0;
    cliente c;
    fseek(aclientes,0,SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);
    while (!feof(aclientes) && !achou)
    {
        posicao++;
        if (c.codigo==codigo || strcmpi(c.nome,nome)==0)
        {
            achou=1;
        }
        fread(&c, sizeof(c),1, aclientes);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}
int localiza_funcionario(FILE *afuncionarios,int codigo, char nome[30])
{
    int posicao2=-1,achou=0;
    funcionario f;
    fseek(afuncionarios,0,SEEK_SET);
    fread(&f, sizeof(f),1, afuncionarios);
    while (!feof(afuncionarios) && !achou)
    {
        posicao2++;
        if (f.codigo==codigo || strcmpi(f.nome,nome)==0)
        {
            achou=1;
        }
        fread(&f, sizeof(f),1, afuncionarios);
    }
    if (achou)
    {
        return posicao2;
    }
    else
    {
        return -1;
    }
}
int localiza_locacao(FILE *alocacao,int codigo)
{
    int posicao=-1,achou=0;
    locacao l;
    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);
    while (!feof(alocacao) && !achou)
    {
        posicao++;
        if (l.codigo==codigo)
        {
            achou=1;
        }
        fread(&l, sizeof(l),1, alocacao);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}
int localiza_veiculo(FILE *aveiculos,int codigo,int qnt)
{
    int posicao=-1,achou=0;
    veiculo v;
    fseek(aveiculos,0,SEEK_SET);
    fread(&v, sizeof(v),1, aveiculos);
    while (!feof(aveiculos) && !achou)
    {
        posicao++;
        if (v.codigo==codigo || (v.qnt==qnt && v.status==0))
        {
            achou=1;
        }
        fread(&v, sizeof(v),1, aveiculos);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void inclui_cliente(FILE *aclientes)
{
    cliente c;
    int posicao,codigo;
    printf("Digite o código do cliente...:");
    scanf("%d",&codigo);
    posicao=localiza_cliente(aclientes,codigo,"---");
    if (posicao==-1)
    {
        printf("Digite o nome do cliente....:");
        fflush(stdin);
        gets(c.nome);
        printf("Digite o telefone do cliente:\n");
        printf("Digite o DDD................:\n");
        fflush(stdin);
        scanf("%d",&c.telefone.ddd);
        printf("Digite o número.............:\n");
        fflush(stdin);
        scanf("%f",&c.telefone.numero);
        printf("Digite o endereço do cliente\n");
        printf("Rua: ");
        fflush(stdin);
        gets(c.endereco.rua);
        printf("Número: ");
        fflush(stdin);
        scanf("%d",&c.endereco.numero);
        printf("Complemento: ");
        fflush(stdin);
        gets(c.endereco.complemento);
        printf("Bairro: ");
        fflush(stdin);
        gets(c.endereco.bairro);
        printf("Cidade: ");
        fflush(stdin);
        gets(c.endereco.cidade);
        printf("UF: ");
        fflush(stdin);
        gets(c.endereco.uf);
        printf("CEP: ");
        fflush(stdin);
        gets(c.endereco.cep);

        fseek(aclientes,0,SEEK_END);
        fwrite(&c, sizeof(c),1,aclientes);
        fflush(aclientes);
    }
    else
    {
        printf("Já existe um cliente com esse código. Inclusão não realizada!\n");
    }
}
void inclui_funcionario(FILE *afuncionarios)
{
    funcionario f;
    int posicao,codigo;
    printf("Digite o código do funcionário...:");
    scanf("%d",&codigo);
    posicao=localiza_funcionario(afuncionarios,codigo,"---");
    if (posicao==-1)
    {
        printf("Digite o nome do funcionário...:");
        fflush(stdin);
        gets(f.nome);
        printf("Digite o telefone do cliente:\n");
        printf("Digite o DDD................:\n");
        fflush(stdin);
        scanf("%d",&f.telefone.ddd);
        printf("Digite o número.............:\n");
        fflush(stdin);
        scanf("%f",&f.telefone.numero);
        printf("Digite o cargo do funcionário...:");
        fflush(stdin);
        gets(f.cargo);
        printf("Digite o salário do funcionário...:");
        fflush(stdin);
        scanf("%d",&f.salario);
        fseek(afuncionarios,0,SEEK_END);
        fwrite(&f, sizeof(f),1,afuncionarios);
        fflush(afuncionarios);
    }
    else
    {
        printf("Já existe um funcionário com esse código. Inclusão não realizada!\n");
    }
}
int calcula_dias(int dia1,int mes1,int ano1,int dia2,int mes2,int ano2)
{
    int i, total1=0, total2=0,res;

// Calcula dias da data de retirada (01/01/2020 como dia 1)

    for (i=2020; i<ano1; i++)
    {

        if((i%4==0 && i%100!=0)||i%400==0)
        {
            total1+=366;
        }
        else
        {
            total1+=365;
        }
    }
    for (i=1; i<mes1; i++)
    {
        if((i%2!=0 && i<=7)||(i%2==0 && i>7))
        {
            total1+=31;
        }

        if(i==2 && ((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total1+=29;
        }
        if(i==2 && !((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total1+=28;
        }
        if((i%2==0 && i<=7)||(i%2!=0 && i>7))
        {
            total1+=30;
        }
    }

    total1+=dia1;

// Calculando dias da data de devolução

    for(i=2020; i<ano2; i++)
    {
        if((i%4==0 && i%100!=0)||i%400==0)
        {
            total2+=366;
        }
        else
        {
            total2+=365;
        }
    }
    for(i=1; i<mes2; i++)
    {
        if((i%2!=0 && i<=7)||(i%2==0 && i>7))
        {
            total2+=31;
        }

        if(i==2 && ((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total2+=29;
        }
        if(i==2 && !((ano1%4==0 && ano1%100!=0)||i%400==0))
        {
            total2+=28;
        }
        if((i%2==0 && i<=7)||(i%2!=0 && i>7))
        {
            total2+=30;
        }
    }

    total2+=dia2;

    res=total2-total1;
    return res;


}

void inclui_locacao(FILE *alocacao, FILE *aclientes, FILE *aveiculos)
{
    locacao l;
    cliente c;
    veiculo v;
    int posicao,qtd,codigo;
    char nome[30];
    printf("Digite o código da locação...:");
    scanf("%d",&codigo);

    posicao=localiza_locacao(alocacao,codigo);
    if (posicao==-1)
    {
        printf("Digite o nome completo do cliente:");
        fflush(stdin);
        gets(nome);
        posicao=localiza_cliente(aclientes,-1,nome);
        if (posicao!=-1)
        {
            fseek(aclientes,sizeof(c)*posicao,SEEK_SET);
            fread(&c,sizeof(c),1,aclientes);
            fflush(stdin);
            l.cod_c=c.codigo;
            printf("Digite o dia, mês e ano da retirada do veículo:");
            fflush(stdin);
            scanf("%d%d%d",&l.dataRet.dia,&l.dataRet.mes,&l.dataRet.ano);
            printf("Digite o dia, mês e ano da devolução do veículo:");
            fflush(stdin);
            scanf("%d%d%d",&l.dataDev.dia,&l.dataDev.mes,&l.dataDev.ano);
            printf("Digite a quantidade de ocupantes do veiculo:");
            fflush(stdin);
            scanf("%d",&qtd);
            l.dataEnt.ano=0;
            fflush(stdin);
            l.dataEnt.dia=0;
            fflush(stdin);
            l.dataEnt.mes=0;
            fflush(stdin);
            l.dias=calcula_dias(l.dataRet.dia,l.dataRet.mes,l.dataRet.ano,l.dataDev.dia,l.dataDev.mes,l.dataDev.ano);
            posicao=localiza_veiculo(aveiculos,-1,qtd);
            if (posicao!=-1)
            {
                fseek(aveiculos,sizeof(v)*posicao,SEEK_SET);
                fread(&v,sizeof(v),1,aveiculos);
                fflush(stdin);
                l.cod_v=v.codigo;
                v.status=1;

                printf("Modelo......:%s\n",v.modelo);
                printf("Descrição...:%s\n",v.descricao);
                printf("Cor.........:%s\n",v.cor);
                printf("Placa.......:%s\n",v.placa);
                printf("Ocupantes...:%d\n",v.qnt);
                printf("Valor/diária:%f\n",v.valor);

                printf("Seguro?");
                fflush(stdin);
                scanf("%d",&l.seguro);

                fseek(aveiculos,0,SEEK_END);
                fwrite(&v, sizeof(v),1,aveiculos);
                fflush(aveiculos);

                fseek(alocacao,0,SEEK_END);
                fwrite(&l, sizeof(l),1,alocacao);
                fflush(alocacao);
            }
            else
            {
                printf("Não há carros disponíveis");
            }

        }
        else
        {
            printf("Não há clientes com esse nome. Por favor, cadastrar o cliente antes de realizar a locação.");
        }

    }
    else
    {
        printf("Já existe uma locação com esse código. Inclusão não realizada!\n");
    }
}

void inclui_veiculo(FILE *aveiculos)
{
    veiculo v;
    int posicao,codigo;
    printf("Digite o código do veículo...:");
    scanf("%d",&codigo);
    posicao=localiza_veiculo(aveiculos,codigo,0);
    if (posicao==-1)
    {
        printf("Digite o modelo do veículo...:");
        fflush(stdin);
        gets(v.modelo);
        printf("Digite a descrição do veículo...:");
        fflush(stdin);
        gets(v.descricao);
        printf("Digite a cor do veículo...:");
        fflush(stdin);
        gets(v.cor);
        printf("Digite a placa do veículo...:");
        fflush(stdin);
        scanf("%s",v.placa);
        printf("Digite o valor da diária do veículo...:");
        fflush(stdin);
        scanf("%f",&v.valor);
        printf("Digite a quantidade de ocupantes do veículo...:");
        fflush(stdin);
        scanf("%d",&v.qnt);
        v.status=0;
        fseek(aveiculos,0,SEEK_END);
        fwrite(&v, sizeof(v),1,aveiculos);
        fflush(aveiculos);
    }
    else
    {
        printf("Já existe um cliente com esse código. Inclusão não realizada!\n");
    }
}

void imprime_veiculo(FILE *aveiculos)
{
    veiculo v;
    fseek(aveiculos,0,SEEK_SET);
    fread(&v, sizeof(v),1, aveiculos);
    while (!feof(aveiculos))
    {
        printf("Código......:%d\n",v.codigo);
        printf("Descrição...:%s\n",v.descricao);
        printf("Modelo......:%s\n",v.modelo);
        printf("Cor.........:%s\n",v.cor);
        printf("Placa.......:%s\n",v.placa);
        printf("Ocupantes...:%d\n",v.qnt);
        printf("Valor/diária:%f\n",v.valor);
        printf("Status......:%d\n",v.status);
        fread(&v, sizeof(v),1, aveiculos);
    }
}

void imprime_cliente(FILE *aclientes)
{
    cliente c;
    fseek(aclientes,0,SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);
    while (!feof(aclientes))
    {
        printf("Código....:%d \n",c.codigo);
        printf("Nome.:%s \n",c.nome);
        printf("Telefone.....:(%d) %.0f\n",c.telefone.ddd,c.telefone.numero);
        printf("Endereço.....:%s, %d, %s, %s, %s - %s - CEP: %s\n",c.endereco.rua,c.endereco.numero,c.endereco.complemento,c.endereco.bairro,c.endereco.cidade,c.endereco.uf,c.endereco.cep);
        fread(&c, sizeof(c),1, aclientes);
    }
}
void imprime_funcionario(FILE *afuncionarios)
{
    funcionario f;
    fseek(afuncionarios,0,SEEK_SET);
    fread(&f, sizeof(f),1, afuncionarios);
    while (!feof(afuncionarios))
    {
        printf("Código....:%d \n",f.codigo);
        printf("Nome.:%s \n",f.nome);
        printf("Telefone.....:(%d) %.0f\n",f.telefone.ddd,f.telefone.numero);
        printf("Cargo.....:%s\n",f.cargo);
        printf("Salário.....:%d\n",f.salario);
        fread(&f, sizeof(f),1, afuncionarios);
    }
}

void imprime_locacao(FILE *alocacao)
{
    locacao l;
    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);
    while (!feof(alocacao))
    {
        printf("Código...........:%d \n",l.codigo);
        printf("Data da Retirada.:%d/%d/%d \n",l.dataRet.dia,l.dataRet.mes,l.dataRet.ano);
        printf("Data da Devolução:%d/%d/%d\n",l.dataDev.dia,l.dataDev.mes,l.dataDev.ano);
        printf("Data da Entrega:%d/%d/%d\n",l.dataEnt.dia,l.dataEnt.mes,l.dataEnt.ano);
        printf("Dias de Aluguel..:%d\n",l.dias);
        printf("Seguro?..........:%d\n",l.seguro);
        printf("Código do Cliente:%d\n",l.cod_c);
        printf("Código do Veículo:%d\n",l.cod_v);
        fread(&l, sizeof(l),1, alocacao);
    }
}

void baixa_locacao(FILE *alocacao, FILE *aclientes, FILE *aveiculos)
{
    locacao l;
    cliente c;
    veiculo v;
    int posicao1,posicao2,posicao3,dias1,codigo;
    float multa,valortotal;
    printf("Digite o código da locação...:");
    scanf("%d",&codigo);
    posicao1=localiza_locacao(alocacao,codigo);

    if (posicao1!=-1)
    {

        fseek(alocacao,sizeof(l)*(posicao1),SEEK_SET);
        fread(&l, sizeof(l),1, alocacao);
        printf("Digite o dia, mês e ano da entrega do veículo:");
        fflush(stdin);
        scanf("%d%d%d",&l.dataEnt.dia,&l.dataEnt.mes,&l.dataEnt.ano);
        dias1=calcula_dias(l.dataRet.dia,l.dataRet.mes,l.dataRet.ano,l.dataEnt.dia,l.dataEnt.mes,l.dataEnt.ano);
        posicao2=localiza_veiculo(aveiculos,l.cod_v,0);
        if (posicao2!=-1)
        {
            fseek(aveiculos,sizeof(v)*(posicao2),SEEK_SET);
            fread(&v, sizeof(v),1, aveiculos);

            fflush(stdin);
            v.status=0;

            fseek(aveiculos,0,SEEK_END);
            fwrite(&v, sizeof(v),1,aveiculos);
            fflush(aveiculos);

            fseek(alocacao,0,SEEK_END);
            fwrite(&l, sizeof(l),1,alocacao);
            fflush(alocacao);

            valortotal=(dias1*v.valor);
            printf("Valor total das diárias.:%.2f\n",valortotal);
            multa=valortotal*0.05+30*(dias1-l.dias);
            printf("Multa por dias de atraso:%.2f\n",multa);
            if(l.seguro==1)
            {
                valortotal=valortotal+multa+50.00;
                printf("Valor do seguro.........:50.00\n");
                printf("Valor total da locação..:%.2f\n",valortotal);
            }
            else
            {
                valortotal=valortotal+multa;
                printf("Valor total da locação..:%.2f\n",valortotal);
            }

            posicao3=localiza_cliente(aclientes,l.cod_c,"---");

            if (posicao3!=-1)
            {
                fseek(aclientes,sizeof(c)*(posicao3),SEEK_SET);
                fread(&c, sizeof(c),1, aclientes);
                printf("Código do cliente.......:%d\n",c.codigo);
                printf("Nome do cliente.........:%s\n",c.nome);
            }

        }




    }
    else
    {
        printf("!!!");
    }


}

void pesquisaClienteFuncionario (FILE *afuncionarios,FILE *aclientes)
{
    cliente c;
    funcionario f;
    int x,posicao,codigo;
    char nome[30];
    printf("Digite 1 para imprimir dados de funcionários ou 2 para imprimir dados de clientes: ");
    scanf("%d",&x);
    printf("Digite o nome:");
    fflush(stdin);
    gets(nome);
    if (x==1)
    {
        posicao=localiza_funcionario(afuncionarios,-1,nome);
        if (posicao==-1)
        {
            printf("Não existe um funcionário com esse código. Impressão não realizada!\n");
        }
        else
        {
            fseek(afuncionarios,sizeof(f)*(posicao),SEEK_SET);
            fread(&f, sizeof(f),1, afuncionarios);
            printf("Código....:%d \n",f.codigo);
            printf("Nome.:%s \n",f.nome);
            printf("Telefone.....:(%d) %.0f\n",f.telefone.ddd,f.telefone.numero);
            printf("Cargo.....:%s\n",f.cargo);
            printf("Salário.....:%d\n",f.salario);
        }
    }
    else
    {
        if (x==2)
        {
            posicao=localiza_cliente(aclientes,-1,nome);
            if (posicao==-1)
            {
                printf(" Não existe um cliente com esse código. Impressão não realizada!\n");
            }
            else
            {
                fseek(aclientes,sizeof(c)*(posicao),SEEK_SET);
                fread(&c, sizeof(c),1, aclientes);
                printf("Código....:%d \n",c.codigo);
                printf("Nome.:%s \n",c.nome);
                printf("Telefone.....:(%d) %.0f\n",c.telefone.ddd,c.telefone.numero);
                printf("Endereço.....:%s, %d, %s, %s, %s - %s - CEP: %s\n",c.endereco.rua,c.endereco.numero,c.endereco.complemento,c.endereco.bairro,c.endereco.cidade,c.endereco.uf,c.endereco.cep);
            }
        }
    }


}

void buscalocacoescliente (FILE *aclientes,FILE *alocacao)
{
    cliente c;
    locacao l;
    char nome[30];
    int posicao;

    printf("Digite o nome do cliente:");
    fflush(stdin);
    gets(nome);

    posicao=localiza_cliente(aclientes,-1,nome);

    fseek(aclientes,sizeof(c)*(posicao),SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);

    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);

    while (!feof(alocacao))
    {
        if (l.cod_c==c.codigo)
        {
            printf("Código...........:%d \n",l.codigo);
            printf("Data da Retirada.:%d/%d/%d \n",l.dataRet.dia,l.dataRet.mes,l.dataRet.ano);
            printf("Data da Devolução:%d/%d/%d\n",l.dataDev.dia,l.dataDev.mes,l.dataDev.ano);
            printf("Data da Entrega:%d/%d/%d\n",l.dataEnt.dia,l.dataEnt.mes,l.dataEnt.ano);
            printf("Dias de Aluguel..:%d\n",l.dias);
            printf("Seguro?..........:%d\n",l.seguro);
            printf("Código do Cliente:%d\n",l.cod_c);
            printf("Código do Veículo:%d\n",l.cod_v);


        }
        fread(&l, sizeof(l),1, alocacao);
    }

}

void calcula_pontos (FILE *aclientes,FILE *alocacao)
{
    cliente c;
    locacao l;
    char nome[30];
    int posicao,pontos=0;

    printf("Digite o nome do cliente:");
    fflush(stdin);
    gets(nome);

    posicao=localiza_cliente(aclientes,-1,nome);

    fseek(aclientes,sizeof(c)*(posicao),SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);

    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);

    while (!feof(alocacao))
    {
        if (l.cod_c==c.codigo)
        {
            pontos=pontos+l.dias*10;

        }
        fread(&l, sizeof(l),1, alocacao);
    }
    printf("O total de pontos é:%d",pontos);

}

void ganhaouKit(FILE *aclientes,FILE *alocacao)
{
    cliente c;
    locacao l;
    int pontos=0;
    fseek(aclientes,0,SEEK_SET);
    fread(&c, sizeof(c),1, aclientes);

    fseek(alocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, alocacao);
    while(!feof(aclientes))
    {
        while (!feof(alocacao))
        {
            if (l.cod_c==c.codigo)
            {
                pontos=pontos+l.dias*10;

            }
            if(pontos>=500){
                printf("O cliente %s tem %d pontos e pode retirar um kit da LocaMais",c.nome,pontos);
            }
            fread(&l, sizeof(l),1, alocacao);
        }

        fread(&c, sizeof(c),1, aclientes);
    }


    printf("O total de pontos é:%d",pontos);

}



