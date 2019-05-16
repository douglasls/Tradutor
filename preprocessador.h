#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <algorithm>

struct Rotulo
{
    std::string nomeLabel;
    std::string  valorEQU;
    Rotulo (){};
    Rotulo(std::string nome, std::string equ): nomeLabel(nome), valorEQU(equ){};
};

int processaarquivo(std::ifstream &arquivo, std::ofstream &arquivosaida)
{   std::string arq_entr, linha, palavra, frase, linha_aux, Label, SegundoToken, ValorEQU, IF, descarte;
    char caracter;
    char *p;
    int tam, i, tamp, tam_frase, j, pos, achou, verificador;
    std::vector<Rotulo> TabRotulo; // ONDE VOU GUARDAR AS LABELS QUE DEVEM SER SUBSTITUIDAS

    TabRotulo.push_back(Rotulo());

    //arq_entr = "arquivo11.txt";

    //std::ifstream arquivo(arq_entr);
    //if(!arquivo){
        //std::cout <<"erro"<<std::endl;
    //}
    while(!arquivo.eof())
    {
        getline(arquivo, linha_aux);

        achou = linha_aux.find(';');
        linha = linha_aux.substr(0,achou);
        std::transform (linha.begin(), linha.end(), linha.begin(), ::toupper); //transforma todos os caracteres em maisculo
        std::stringstream estrutura(linha); //pega a palavra até o espaco
        tam = 0;
        for (i = 0; i < linha.length(); i++)
        {
            if(!isspace(linha[i]))
            {
                tam++;
            }
        }
        while(tam > 0)
        {
            estrutura >> palavra;
            tamp = palavra.length();
            tam = tam - tamp;
            frase.append(palavra);
            frase.append(" ");
        }
        tam_frase = frase.length(); //vê o tamanho de uma linha do programa

        frase.at(tam_frase-1) = '\n';

        //ANALISE DE DIRETIVAS
        std::stringstream pegaToken (frase);
        pegaToken >> Label;
        if(Label.back() == ':')
        {
            pegaToken >> SegundoToken;
            if(SegundoToken == "EQU")
            {
                Label.pop_back();
                pegaToken >> ValorEQU;

                Rotulo adicionar(Label, ValorEQU); //não consigo resolver isso!!!!!
                TabRotulo.push_back(adicionar);

            }
        }
        if(Label == "IF")
        {
            pegaToken >> IF;
            /*TEM QUE FAZER ANALISE DE ERRO AQUI E INCREMENTAR O CONTADOR*/
            //VERIFICAR SE O IF EH VALOR POSITIVO
            verificador = strtol(IF.c_str(), &p , 10);
            if (verificador != 1)
            {
                getline(arquivo, descarte); //pega a proxima linha e joga fora
            }
        }
    }
    pos = frase.find("SECTION DATA");
    if(pos == -1)
    {
        std::cout << "SECTION DATA nao encontrada" << std::endl;
    }
    else
    {
        std::cout << "SECTION DATA OK" << std::endl;
    }

    pos = frase.find("SECTION TEXT");
    if(pos == -1)
    {
        std::cout << "SECTION TEXT nao encontrada" << std::endl;
    }
    else
    {
        std::cout << "SECTION TEXT OK" << std::endl;
    }

    arquivosaida << frase << std::endl;

    std::cout << frase <<std::endl;

    return 0;
}