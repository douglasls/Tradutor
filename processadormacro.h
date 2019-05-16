//
// Created by myllena on 03/05/19.
//

#include <time.h>

//struct da tabela de macros
struct tabelamacro{
    std::string nomeMacro;
    std::string conteudomacro;
    std::string parametros;
    int nlinhas;
    int nparametros;
    tabelamacro (){};
    tabelamacro (std::string nome, std::string conteudo, std::string parame, int linhas, int nparame): nomeMacro(nome), conteudomacro(conteudo), parametros(parame), nlinhas(linhas), nparametros(nparame){};
};


void expandemacro(std::vector<tabelamacro> &tmacros,std::string linhacod, int i, std::ofstream &arquivosaida);
void chamamacro(std::string linha, int quantmacro, std::vector<tabelamacro> &tmacros, std::ofstream &arquivosaida);
void corpomacro(std::string nome, std::string parametro, int numparam, std::ifstream &arquivo, std::vector<tabelamacro> &tmacros, int i, int &quantmacros, std::ofstream &arquivosaida);
void conferemacro(std::string linha, int &quantmacros, std::vector<tabelamacro>  &tmacros, std::ifstream &arquivo, std::ofstream &arquivosaida);




void expandemacro(std::vector<tabelamacro> &tmacros,std::string linhacod, int i, int quantmacro, std::ofstream &arquivosaida){

    std::string instrucao, linhamacro, instcod, op1, op2, codigo, parametros, opmacro, escrevearquivo, inst, linhaexp;
    int k, posicao, l, f, nparametros, g, chamamacro;

    //pega conteudo da macro na tabela
    linhamacro = tmacros[i].conteudomacro;
    //pega os parametros da macro
    parametros = tmacros[i].parametros;
    // pega o conteudodamacro
    std::stringstream palavramacro(linhamacro);
    nparametros = tmacros[i].nparametros;

    //percorre as linhas macro da tabela
    for (k = 1; k <= tmacros[i].nlinhas; k++){
        chamamacro = 0;
        //parametros da tabela
        std::stringstream pegaparam(parametros);
        //linha do código do programa que chamou a macro
        std::stringstream palavracod(linhacod);
        //pega o nome da macro que foi chamada
        palavracod >> codigo;
        //instrucao da macro da tabela
        palavramacro >> instrucao;
        inst = instrucao;
        posicao = 0;
        if(instrucao == "COPY"){
            //pega o primeiro parametro da inst
            palavramacro >> instrucao;
            instrucao.pop_back();
            //pega o primeiro parametro da definiçao da macro
            pegaparam >> opmacro;
            if (instrucao == opmacro){
                //indica que e o primeiro argumento passado
                posicao = 1;
            }
            else{
                //pega o segundo parametro da definicao da macro
                pegaparam >> opmacro;
                std::cout << instrucao << opmacro << std::endl;
                if (instrucao == opmacro){
                    //indica que e o segundo argumento passado
                    posicao = 2;
                }
                else{
                    //indica que e o terceiro argumento passado
                    posicao =3;
                }
            }
            for (l = 1; l <= posicao; l++){//anda linha cod para pegar parametro
                palavracod >> codigo;
                if(nparametros == 3 && posicao == 1){
                    codigo.pop_back();
                }
                if(nparametros == 3 && posicao == 2){
                    codigo.pop_back();
                }
                if(nparametros == 2 && posicao == 1){
                    codigo.pop_back();
                }
                std::cout << codigo << std::endl;
            }
            escrevearquivo.append(inst);
            escrevearquivo.append(" ");
            escrevearquivo.append(codigo);
            escrevearquivo.append(" ");
            arquivosaida << inst << " " << codigo ;

            std::cout << escrevearquivo << std::endl;
            //pega o segundo parametro da inst
            palavramacro >> instrucao;
            //volta a ler a linha toda
            std::stringstream pegaparam(parametros);
            //pega o primeiro parametro da definiçao da macro
            pegaparam >> opmacro;
            //linha do código do programa que chamou a macro
            std::stringstream palavracod(linhacod);
            //pega o nome da macro que foi chamada
            palavracod >> codigo;
            std::cout << opmacro << std::endl;
            if (instrucao == opmacro){
                //indica que e o primeiro argumento passado
                posicao = 1;
            }
            else{
                //pega o segundo parametro da definicao da macro
                pegaparam >> opmacro;
                std::cout << instrucao << opmacro << std::endl;
                if (instrucao == opmacro){
                    //indica que e o segundo argumento passado
                    posicao = 2;
                }
                else{
                    //indica que e o terceiro argumento passado
                    posicao =3;
                }
            }
            for (l = 1; l <= posicao; l++){//anda linha cod para pegar parametro
                palavracod >> codigo;
                if(nparametros == 3 && posicao == 1){
                    codigo.pop_back();
                }
                if(nparametros == 3 && posicao == 2){
                    codigo.pop_back();
                }
                if(nparametros == 2 && posicao == 1){
                    codigo.pop_back();
                }
            }
            escrevearquivo.append(codigo);
            escrevearquivo.append(" ");
            if (tmacros[i].nparametros == 0){
                codigo = " ";
            }
            arquivosaida << " " << codigo << std::endl;

            std::cout << escrevearquivo << std::endl;

        }
        else {//testar a instrução chamada
            //testa se a instrucao tem o nome da macro
            for(g = 1; g <= quantmacro; g++) {
                if(instrucao == tmacros[g].nomeMacro){
                    chamamacro = 1;
                    f = g;
                }
            }//caso a instrucao seja a chamada de uma macro
            if( chamamacro == 1) {

                linhaexp.append(instrucao);
                linhaexp.append(" ");
                palavramacro >> instrucao;
                while (instrucao != "|"){
                    //parametros da tabela
                    std::stringstream pegaparam(parametros);
                    // trocar parametro pelo parametro de chamada
                    //tira virgula do parametro
                    if(instrucao.back() == ','){
                        instrucao.pop_back();
                    }
                    pegaparam >> opmacro;
                    if(instrucao == opmacro){
                        posicao = 1;
                    }
                    else{
                        //opmacro.pop_back();
                        pegaparam >> opmacro;
                        if(instrucao == opmacro){
                            posicao = 2;
                        }
                        else{
                            posicao = 3;
                        }
                    }
                    for (l = 1; l <= posicao; l++){//anda linha cod para pegar parametro
                        palavracod >> codigo;
                        if(nparametros == 3 && posicao == 1){
                            codigo.pop_back();
                        }
                        if(nparametros == 3 && posicao == 2){
                            codigo.pop_back();
                        }
                        if(nparametros == 2 && posicao == 1){
                            codigo.pop_back();
                        }
                    }

                    instrucao = codigo;

                    linhaexp.append(" ");
                    linhaexp.append(instrucao);
                    linhaexp.append(",");
                    palavramacro >> instrucao;

                }
                linhaexp.pop_back();
                expandemacro(tmacros, linhaexp , f, quantmacro, arquivosaida);

            }
            else {
                //pega o primeiro parametro da inst
                palavramacro >> instrucao;
                //pega o primeiro parametro da definiçao da macro
                pegaparam >> opmacro;
                std::cout << instrucao << opmacro << std::endl;
                if (instrucao == opmacro) {
                    //indica que e o primeiro argumento passado
                    posicao = 1;
                    std::cout << "primeiro" << std::endl;
                } else {//recursividade da macro
                    //pega o segundo parametro da definicao da macro
                    pegaparam >> opmacro;
                    std::cout << instrucao << opmacro << std::endl;
                    if (instrucao == opmacro) {
                        //indica que e o segundo argumento passado
                        posicao = 2;
                    } else {
                        //indica que e o terceiro argumento passado
                        posicao = 3;
                    }
                }

                for (l = 1; l <= posicao; l++){//anda linha cod para pegar parametro
                    palavracod >> codigo;
                    if (nparametros == 3 && posicao == 1) {
                        codigo.pop_back();
                    }
                    if (nparametros == 3 && posicao == 2) {
                        codigo.pop_back();
                    }
                    if (nparametros == 2 && posicao == 1) {
                        codigo.pop_back();
                    }
                    std::cout << codigo << std::endl;
                }

                escrevearquivo.append(inst);
                escrevearquivo.append(" ");
                escrevearquivo.append(codigo);
                escrevearquivo.append(" ");

                //caso a macro nao receba parametro
                if (tmacros[i].nparametros == 0){
                    codigo = " ";
                    std::cout << "nenhum parametro AINDA REVER " << std::endl;
                }
                arquivosaida << inst << " " << codigo << std::endl;

                std::cout << escrevearquivo << std::endl;

            }
        }
        if(chamamacro == 0){
            palavramacro >> instrucao;
        }
    }
}


void chamamacro(std::string linha, int quantmacro, std::vector<tabelamacro> &tmacros, std::ofstream &arquivosaida){
    std::string token;
    int i, achoumacro;
    i = 1;
    achoumacro = 0;
    std::stringstream palavra(linha);
    palavra >> token;
    do{
        if (token == tmacros[i].nomeMacro){
            expandemacro(tmacros, linha, i, quantmacro, arquivosaida);
            achoumacro = 1;
            std::cout << "expandemacro" << std::endl;
        }
        i++;
    }while (achoumacro == 0 && i <= quantmacro);

     if(achoumacro == 0){
         //escrever no arquivo
         arquivosaida << linha << std::endl;
         std::cout << "normal" << std::endl;
     }
}

//coloca na tabela o conteudo da macro e todos os parametros
void corpomacro(std::string nome, std::string parametro, int numparam, std::ifstream &arquivo, std::vector<tabelamacro> &tmacros, int i, int &quantmacros, std::ofstream &arquivosaida){
    std::string conteudodamacro, linha, token1;
    int numlinha, achoumacro;
    numlinha = 0;
    achoumacro = 0;

    do{
        //pega linha do arquivo
        getline(arquivo, linha);
        std::stringstream palavra(linha);
        //pega na instrucao do corpo da macro
        palavra >> token1;
        //verificar se aqui tem rotulo antes ainda( FAZZEERRRRRR)
        //confere se achou uma macro sem ter encontrado o end anterior
        if(token1.back()== ':') {
            achoumacro = 1;
            std::cout << "macro sem end" << std::endl;
            std::cout << linha << std::endl;
            quantmacros = quantmacros - 1;
            conferemacro(linha, quantmacros, tmacros, arquivo, arquivosaida);
        }
        else{
            if (token1 != "END") {
                //verificar se aqui tem section antes ainda( FAZZEERRRRRR)

                if (token1 == "COPY") {
                    conteudodamacro.append(linha);
                    conteudodamacro.append(" ");
                    conteudodamacro.append("|");
                    conteudodamacro.append(" ");
                    numlinha = numlinha + 1;

                } else {
                    conteudodamacro.append(linha);
                    conteudodamacro.append(" ");
                    conteudodamacro.append("|");
                    conteudodamacro.append(" ");
                    numlinha = numlinha + 1;
                }
            }
        }
    }while(token1 != "END" && achoumacro == 0);

    if (achoumacro == 0) {
        tabelamacro tabelaaux(nome, conteudodamacro, parametro, numlinha, numparam);
        tmacros.push_back(tabelaaux);
        std::cout << tmacros[i].nomeMacro << std::endl;
        std::cout << tmacros[i].conteudomacro << std::endl;
        std::cout << tmacros[i].parametros << std::endl;
        std::cout << tmacros[i].nparametros << std::endl;
        std::cout << tmacros[i].nlinhas << std::endl;
    }

}


//confere se na linha há uma declaração de macro
void conferemacro(std::string linha, int &quantmacros, std::vector<tabelamacro>  &tmacros, std::ifstream &arquivo, std::ofstream &arquivosaida){
    int detectaerro, i, numparam, flag, n, repetido, auxiliar;
    detectaerro = 0;
    std::string parametro, vetorparametros, variavel;
    std::vector<char> vetorparametro;
    std::string conteudodamacro;
    std::string token1, token2;
    std::stringstream palavra(linha);
    palavra >> token1;
    palavra >> token2;
    numparam = 0;
    if(token2 == "MACRO"){
        //confere se não é um nome proibido
        token1.pop_back();
        if(token1 == "CONST" || token1 == "SPACE" || token1 == "SECTION" || token1 == "EQU" || token1 == "MACRO" || token1 == "END"){
            detectaerro = 1;
            std::cout << "Erro semantico" << std::endl;
        }
        //confere se possui nome proibido de instrução
        if(token1 == "ADD" || token1 == "SUB" || token1 == "MULT" || token1 == "DIV" || token1 == "JMP" || token1 == "JMPN" || token1 == "JMPP" || token1 == "JMPZ" || token1 == "COPY" || token1 == "LOAD" || token1 == "STORE" || token1 == "INPUT" || token1 == "OUTPUT" || token1 == "STOP"){
            detectaerro = 1;
            std::cout << "Erro semantico" << std::endl;
        }

        //confere se o rotulo possui o mesmo nome que outra macro ja declarada
        for(i=0; i <= quantmacros; i++){
            //compara com o nome da macro já armazenado
            if(token1 == tmacros[i].nomeMacro && quantmacros >= 1){
                std::cout << "Erro semantico, macro já definida" << std::endl;
                detectaerro = 1;
            }
        }
        //confere parametro
        do{
            flag = 1;
            palavra >> parametro;
            //add caso tenha mais que um parametro
            if(parametro.back() == ','){
                flag = 0;
                parametro.pop_back();
                //compara com outros parametors já apresentados
                std::stringstream pegarparamen(vetorparametros);
                repetido =0;
                for (n= 0; n <= numparam; n++){
                    pegarparamen >> variavel;
                    if(parametro == variavel){
                        std::cout << "Erro semantico, parametro da macro repetido" << std::endl;
                        repetido = 1;
                    }
                }
                if (numparam >3){
                    std::cout << "Erro sintático mais de 3 argumentos " << std::endl;
                    repetido = 1;
                }
                if (repetido == 0){
                    vetorparametros.append(parametro);
                    vetorparametros.append(" ");
                    numparam = numparam +1;
                }

            }
            //add caso seja o ultimo parametro
            else{
                std::stringstream pegarparamen(vetorparametros);
                repetido =0;
                for (n= 0; n <= numparam; n++){
                    pegarparamen >> variavel;
                    if(parametro == variavel){
                        std::cout << "Erro semantico, parametro da macro repetido" << std::endl;
                        repetido = 1;
                    }
                }
                if (numparam >2){
                    std::cout << "Erro sintático mais de 3 argumentos " << std::endl;
                    repetido = 1;
                }
                if (repetido == 0){
                    vetorparametros.append(parametro);
                    numparam = numparam + 1;
                }
            }
        }while(flag == 0);

        if (detectaerro == 0){
            quantmacros = quantmacros + 1;
            auxiliar = quantmacros;
            corpomacro(token1, vetorparametros, numparam, arquivo, tmacros, auxiliar, quantmacros, arquivosaida);
        }

    }
    else{
        std::cout << "erro sintatico, falta label" << std::endl;
    }
}


//Lê linha do arquivo e chama a funcao conferemacro
void expandirmacro(std::ifstream &arquivo, std::ofstream &arquivosaida){
    std::string linha, testeparada;
    std::string nomeArquivo;


    std::vector<tabelamacro> tmacros;

    int quantdemacros;

    //armazena espaço para um elemento no vector de struct é necessário sempre pra colocar um novo elemento
    tmacros.push_back(tabelamacro());

    //quant de macros encontradas
    quantdemacros = 0;

    //abrir arquivo no modo de leitura
    //nomeArquivo = "macro.txt";
    //std::ifstream arquivo (nomeArquivo); //modo leitura
    //if(!arquivo){
    //    std::cout << "Ocorreu um erro na abertura do arquivo" << std::endl;
    //}

    //ler do arquivo parte de definição de macros
    while(!arquivo.eof()){ //testa se o tem algo para ler
        getline(arquivo,linha); //lê uma linha do arquivo e armazena na variavel linha
        std::stringstream definicao(linha);
        definicao >> testeparada;
        definicao >> testeparada;
        if((testeparada != "MACRO" || linha == "SECTION DATA") && linha != "SECTION TEXT"  ){
            break;
        }
        if(linha == "SECTION TEXT"){
            arquivosaida << "SECTION TEXT" << std::endl;
        }
        else{
            conferemacro(linha, quantdemacros, tmacros, arquivo, arquivosaida); //função de conferir o rotulo da macro
        }

    }

    //ler do arquivo a parte de section text

    while(!arquivo.eof()){

        getline(arquivo,linha);

        if (linha == "SECTION DATA"){
            break;
        }
        //percorre código atrás da chamada da macro
        chamamacro(linha, quantdemacros, tmacros, arquivosaida);
    }

    //ler do arquivo a parte de section data
    arquivosaida << "SECTION DATA" << std::endl;
    while(!arquivo.eof()) {
        getline(arquivo,linha); //lê uma linha do arquivo e armazena na variavel linha
        arquivosaida << linha << std::endl;
        std::cout << linha << std::endl;
    }

}








