//made by Larissa Yumi Harada and Thais Oyamada Tanaka
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define n_fases 5
#define n_jogos 10

//Dados do jogador.
typedef struct
{
    char nome[31], sobrenome[31];
    int score;
} jogador;

int rscore ()
{
    FILE *scoreArq;
    int score;
    scoreArq = fopen("./qualojogo/score.txt","r");
    if(scoreArq!=NULL)
        fscanf(scoreArq,"%d\n", &score);
    fclose(scoreArq);
    scoreArq=NULL;
    return score;

}

void wscore (int score)
{
    FILE* scoreArq;
    scoreArq = fopen("./qualojogo/score.txt", "w");
    if (scoreArq != NULL)
        fprintf(scoreArq, "%d\n", score);
    fclose(scoreArq);
    scoreArq = NULL;
}
void wfase(int fase)
{
    FILE* fasesArq;
    fasesArq = fopen("./qualojogo/fas.txt", "w");
    if (fasesArq != NULL)
        fprintf(fasesArq, "%d\n", fase);
    fclose(fasesArq);
    fasesArq = NULL;
}

void wfalha (int falha)
{
    FILE* falhaArqW;
    falhaArqW = fopen("./qualojogo/falhas.txt", "w");
    if (falhaArqW != NULL)
        fprintf(falhaArqW, "%d\n", falha);
    fclose(falhaArqW);
    falhaArqW = NULL;
}

void imprimeScore (int score,int fase)
{
    printf("<h2>Pontuação: %d</h2>", score);
    printf("<h3>Fase: %d/5</h3>",fase+1);
}

//imprime as opções de jogos
void imprime ()
{
    printf("<div id=\"opcoes\">");
    printf("<form action=\"jogo.cgi\" accept-charset=\"ISO-8859-1\">");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"0\" onclick=\"this.form.submit();\" style=\"display:none\"> League of Legends<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"1\" onclick=\"this.form.submit();\" style=\"display:none\"> Dota<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"2\" onclick=\"this.form.submit();\" style=\"display:none\"> Grand Theft Auto<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"3\" onclick=\"this.form.submit();\" style=\"display:none\"> Counter Strike<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"4\" onclick=\"this.form.submit();\" style=\"display:none\"> Overwatch<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"5\" onclick=\"this.form.submit();\" style=\"display:none\"> Battlefield<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"6\" onclick=\"this.form.submit();\" style=\"display:none\"> Team Fortress<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"7\" onclick=\"this.form.submit();\" style=\"display:none\"> Super Mario<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"8\" onclick=\"this.form.submit();\" style=\"display:none\"> Sonic<br></label>");
    printf("<label><input type=\"radio\" name=\"opcao\" value=\"9\" onclick=\"this.form.submit();\" style=\"display:none\"> Minecraft<br></label>");
    printf("</form>");
    printf("</div>");

}

//bubble sort
void sort (int score)
{
    char s[100];
    jogador *jog,aux;
    FILE* arq;
    int i=0,k, j;
    arq = fopen("./qualojogo/record.txt","r");

    if(arq!=NULL)
    {
        while(fgets(s,100,arq)!=NULL)
            i++;
    }
    fclose(arq);
    arq=NULL;

    jog=malloc(i*sizeof(jogador));

    arq = fopen("./qualojogo/record.txt","r");

    if(arq!=NULL)
    {
        for(j=0; j<i; j++)
            fscanf(arq,"%s %s %d\n",jog[j].nome,jog[j].sobrenome,&jog[j].score);
    }
    fclose(arq);
    arq=NULL;

    //ordenação conforme o score
    for (k=1; k<i; k++)
    {
        for (j=0; j<i-k; j++)
        {
            if (jog[j].score < jog[j + 1].score)
            {
                aux.score = jog[j].score;
                jog[j].score = jog[j + 1].score;
                jog[j + 1].score = aux.score;

                strcpy(aux.nome,jog[j].nome);
                strcpy(jog[j].nome,jog[j+1].nome);
                strcpy(jog[j+1].nome,aux.nome);

                strcpy(aux.sobrenome,jog[j].sobrenome);
                strcpy(jog[j].sobrenome,jog[j+1].sobrenome);
                strcpy(jog[j+1].sobrenome,aux.sobrenome);
            }
        }
    }

    printf("<h1 align=\"center\">Recordes</h1>");
    printf("<div align=\"center\" class=\"fala\">");
    printf("<h2 align=\"center\" style=\"color:red;\">Total: %d</h2>",score);
    //impressão dos dados do top 10
    if(i>=10)
    {
        for(k=0; k<10; k++)
        {
            if(strcmp(jog[k].nome,jog[k].sobrenome)!=0)
            {
                printf("<p align=\"center\">%d) %d  %s %s</p>",k+1,jog[k].score,jog[k].nome,jog[k].sobrenome);
            }
            else
            {
                printf("<p align=\"center\">%d) %d  %s</p>",k+1,jog[k].score,jog[k].nome);
            }
        }
    }
    else
    {
        for(k=0; k<i; k++)
        {
            if(strcmp(jog[k].nome,jog[k].sobrenome)!=0)
            {
                printf("<p align=\"center\">%d) %d  %s %s<br></p>",k+1,jog[k].score,jog[k].nome,jog[k].sobrenome);

            }
            else
            {
                printf("<p align=\"center\">%d) %d  %s<br></p>",k+1,jog[k].score,jog[k].nome);
            }
        }
    }
    printf("</div>");
}

//Módulo que fornece dicas sobre o jogo que o usuário precisa adivinhar.
//Conforme o usuário erra, novas dicas serão exibidas.
void jogosDica(int falha, int jogo)
{

    //Abrir o arquivo do jogo da respectiva fase.
    FILE * arq;
    switch(jogo)
    {
    case 0:
        arq = fopen("./qualojogo/lol.txt", "r");
        break;
    case 1:
        arq = fopen("./qualojogo/dota.txt", "r");
        break;
    case 2:
        arq = fopen("./qualojogo/gta.txt", "r");
        break;
    case 3:
        arq = fopen("./qualojogo/cs.txt", "r");
        break;
    case 4:
        arq = fopen("./qualojogo/over.txt", "r");
        break;
    case 5:
        arq = fopen("./qualojogo/bat.txt", "r");
        break;
    case 6:
        arq = fopen("./qualojogo/fort.txt", "r");
        break;
    case 7:
        arq = fopen("./qualojogo/mario.txt", "r");
        break;
    case 8:
        arq = fopen("./qualojogo/sonic.txt", "r");
        break;
    case 9:
        arq = fopen("./qualojogo/mine.txt", "r");
        break;
    }

    int i = 0;
    char dica[4][100];

    //Receber todas as dicas contidas no arquivo.
    if(arq != NULL)
    {
        while((fgets(dica[i], 100, arq)) != NULL)
            i++;
    }

    //Fechar o arquivo.
    fclose(arq);
    arq = NULL;

    //Imprimir as dicas de forma acumulativa.
    for(i=0; i<=falha; i++)
    {
        printf("<div align=\"center\" class=\"fala\">");
        if (falha==0)
            puts(dica[falha]);
        else
        {
            if (i==falha)
                printf("%s", dica[falha]);
            else
                printf("%s<br>", dica[i]);
        }
        printf("</div>");
    }
}

//pontuação de cada fase
int Resultado(int falha)
{
    int score=0;

    switch(falha)
    {
    case 0:
        score = 100;
        break;
    case 1:
        score = 75;
        break;
    case 2:
        score = 50;
        break;
    case 3:
        score = 25;
        break;
    }

    return score;
}

//Esse módulo recebe: vetor dos jogos já sorteados, fase em que o jogo está.
int sorteio(int *m, int fase)
{
    int i, sort, ja;

    do
    {
        ja=0;
        sort=rand()%n_jogos;
        for(i=0; i<fase; i++)
        {
            if (m[i]==sort)
                ja=1;
        }
    }
    while(ja==1);

    m[fase]=sort;

    return sort;
}

int main()
{

    //Impedir que os mesmos jogos sejam sorteados à cada nova execução.
    srand(time(NULL));

    //Declaração de variáveis para abertura de arquivos.
    FILE *nomeArq, *jogorodW, *fasesArq, *fasesArqW, *jogorodR, *falhaArq, *falhaArqW, *scoreArq, *recordArq;

    //Declaração da variável jogador.
    jogador jog;

    //Criar ponteiro que aponta para o conteúdo da barra do browser.
    char *pData = NULL;

    //Criar ponteiro e string para o nome inserido pelo jogador.
    char *insertName, nome[101];

    //Declaração de variáveis em geral.
    int no_repeat[n_fases], fase, i, jogo[n_fases], falha, respostauser;

    //Ponteiro pData aponta para o conteúdo da barra do browser.
    pData = getenv("QUERY_STRING");

    //Estrutura do "cabeçalho" da página HTML.
    printf("%s%c%c\n", "Content-Type:text/html;charset=ISO-8859-1", 13, 10);
    printf("<!DOCTYPE html>");
    printf("<html lang=\"pt-BR\">");
    printf("<head>");
    printf("<meta charset=\"ISO-8859-1\">");
    printf("<link href=\"https://fonts.googleapis.com/css?family=Press+Start+2P|VT323\" rel=\"stylesheet\">");
    printf("<link href=\"../css/qualojogo2.css\" rel=\"stylesheet\" type=\"text/css\"/>");
    printf("<title>Qual é o jogo?</title>");
    printf("</head>");
    printf("<body>");
    printf("<div id=\"main\">");

    //Se o conteúdo da barra for diferente de NULL...
    if(pData != NULL)
    {

        //Se a barra contiver o nome do jogador.
        if ((sscanf(pData, "nome=%s", nome)) == 1)
        {

            //Como isso significa que o jogo acabou de começar, mude falha para 0.
            falha = 0;

            //Sobrescreva o arquivo falhas.txt com o 0.
            wfalha(falha);

            //Como o jogo acabou de começar, mude fase para 0.
            fase = 0;

            //Sobrescreva o arquivo fas.txt com o 0.
            wfase(fase);

            //Quebrar o nome em strings
            insertName=strtok(nome,"+");


            strcpy(jog.nome,insertName);

            insertName=strtok(NULL,"+");

            if(insertName!=NULL)
                strcpy(jog.sobrenome,insertName);
            else
                strcpy(jog.sobrenome,jog.nome);



            //Escrever o nome do jogador no arquivo texto.
            nomeArq = fopen("./qualojogo/jogador.txt", "w");
            if (nomeArq != NULL)
                fprintf(nomeArq, "%s %s\n", jog.nome, jog.sobrenome);
            fclose(nomeArq);
            nomeArq = NULL;

            //Como ainda é o começo do jogo, definir a pontuação para 0.
            jog.score = 0;

            //Escrever a pontuação 0 no arquivo score.txt
            wscore(jog.score);

            //Abrir o arquivo que contém os jogos que serão exibidos.
            jogorodW = fopen("./qualojogo/jogrodada.txt", "w");

            //Sorteia 5 jogos para 5 fases e imprime no arquivo jogrodada.txt
            if (jogorodW != NULL)
            {
                for (i = 0; i < n_fases; i++)
                {
                    fprintf(jogorodW, "%d\n", sorteio(no_repeat, i));
                }
                fclose(jogorodW);
                jogorodW = NULL;
            }

            //Abra o arquivo jogrodada.txt
            jogorodR = fopen("./qualojogo/jogrodada.txt", "r");
            if (jogorodR != NULL)
            {

                //Armazene os números lá encontrados no vetor jogos.
                for (i = 0; i <= fase; i++)
                {
                    fscanf(jogorodR, "%d\n", &jogo[i]);

                }
            }

            imprimeScore(jog.score,fase);

            jogosDica(falha, jogo[fase]);

            imprime();

        } //Aqui termina a execução incial após o usuário inserir o nome.
        else
        {
            //Após o usuário ter feito uma escolha...
            if (sscanf(pData, "opcao=%d", &respostauser) == 1)
            {

                //Abre o arquivo fas.txt e armazena o dado encontrado em "fase".
                fasesArq = fopen("./qualojogo/fas.txt", "r");
                if(fasesArq != NULL)
                {
                    fscanf(fasesArq, "%d\n", &fase);

                }
                fclose(fasesArq);
                fasesArq = NULL;

                //Para todas as fases...

                //Abra o arquivo jogrodada.txt
                jogorodR = fopen("./qualojogo/jogrodada.txt", "r");
                if (jogorodR != NULL)
                {

                    //Armazene os números lá encontrados no vetor jogos.
                    for (i = 0; i <n_fases; i++)
                    {
                        fscanf(jogorodR, "%d\n", &jogo[i]);

                    }
                }

                //Feche o arquivo jogrodada.txt
                fclose(jogorodR);
                jogorodR = NULL;

                //Abra o arquivo falhas.txt
                falhaArq = fopen("./qualojogo/falhas.txt", "r");

                //Armazene o número lá encontrado na variável falha.
                if (falhaArq != NULL)
                {
                    fscanf(falhaArq, "%d\n", &falha);
                }

                //Feche o arquivo.
                fclose(falhaArq);
                falhaArq = NULL;

                //Abra o arquivo que contém a pontuação.
                jog.score=rscore();



                //Se o número de falhas for menor que 4...
                if (falha < 4)
                {
                    if (respostauser==jogo[fase])
                    {
                        printf("<audio autoplay><source src=\"../css/music/Correct.wav\" type=\"audio/wav\"></audio>");
                        fase+=1;
                        jog.score+=Resultado(falha);

                        wfase(fase);

                        //Rescreva o arquivo score.txt.
                        wscore(jog.score);

                        falha=0;

                        wfalha(falha);
                    }
                    else
                    {
                        printf("<audio autoplay><source src=\"../css/music/Incorrect.wav\" type=\"audio/wav\"></audio>");
                        falha+=1;

                        wfalha(falha);
                    }
                }

                //Quando o usuário alcançar o limite de falhas...
                if (falha == 4)
                {
                    //Ir para a próxima fase.
                    fase++;

                    //Sobrescrever o arquivo fas.txt.
                    wfase(fase);

                    falha=0;

                    wfalha(falha);

                }
                // como o jogo possui 5 fases, ao fim destas, o jogador tem seu score final
                if(fase==n_fases)
                {
                    nomeArq = fopen("./qualojogo/jogador.txt","r");
                    if(nomeArq != NULL)
                        fscanf(nomeArq,"%s %s\n",jog.nome,jog.sobrenome);
                    fclose(nomeArq);
                    nomeArq=NULL;

                    jog.score=rscore();

                    recordArq = fopen("./qualojogo/record.txt","a");
                    if(recordArq!=NULL)
                        fprintf(recordArq,"%s %s %d\n",jog.nome,jog.sobrenome,jog.score);
                    fclose(recordArq);
                    recordArq=NULL;
                    sort(jog.score);
                }
                else
                {
                    imprimeScore(jog.score,fase);

                    jogosDica(falha, jogo[fase]);

                    imprime();
                }
            }
            //Fechamento da condicional de pós escolha.

            else //se o jogador não tiver inserido o nome
            {
                printf("<div id=\"outerouter\"><div id=\"outer\">");
                printf("<h1 align=\"center\">Por favor, insira seu nome!</h1>");
                printf("<meta http-equiv=\"refresh\" content=1;url=\"http://cap.dc.ufscar.br/~743559/qualojogo2\">");
                printf("</div></div>");
            }
        }

    }
    printf("</main>");
    printf("</body>");
    printf("</html>");

    return 0;
}
