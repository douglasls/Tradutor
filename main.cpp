#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "processadormacro.h"
#include "preprocessador.h"
#include "montador.h"


int main(){
    std::string nomeArquivo, nomearq, nomearqsaida, escrever, arq_entr, codigo;
    //abrir arquivo no modo de leitura
    arq_entr = "arquivo11.txt";

    std::ifstream arquivo_ent(arq_entr);
    if(!arquivo_ent){
        std::cout <<"Ocorreu um erro na abertura do arquivo"<<std::endl;
    }
    nomearqsaida = "macro.txt";
    std::ofstream arquivosaidap(nomearqsaida);
    if(!arquivosaidap){
        std::cout << "Ocorreu um erro na criacao do arquivo de saida" << std::endl;
    }

    processaarquivo(arquivo_ent, arquivosaidap);

    nomeArquivo = "macro.txt";
    std::ifstream arquivo (nomeArquivo); //modo leitura
    if(!arquivo){
        std::cout << "Ocorreu um erro na abertura do arquivo" << std::endl;
    }
    nomearq = "preprocessado.pre";
    std::ofstream arquivosaida(nomearq);
    if(!arquivo){
        std::cout << "Ocorreu um erro na criacao do arquivo de saida" << std::endl;
    }

    expandirmacro(arquivo, arquivosaida);

    codigo = "preprocessado.pre";
    //codigo = "monta";
    std::ifstream arquivomontador (codigo); //modo leitura
    if(!arquivomontador){
        std::cout << "Ocorreu um erro na abertura do arquivo" << std::endl;
    }
    montar(arquivomontador);


    return 0;

}
