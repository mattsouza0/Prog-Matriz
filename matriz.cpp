#include "matriz.h"
namespace tp2 {

Matriz::Matriz(int qLinhas, int qColunas):
    quantidadeDeLinhas(0),
    quantidadeDeColunas(0),
    matriz(0)
{
   if(qLinhas <= 0)
     throw QString("Quantidade de Linhas não pode ser <= 0");
   if(qColunas <= 0)
     throw QString("Quantidade de Colunas não pode ser <= 0");
   try {
       matriz = new int[qLinhas*qColunas];
       quantidadeDeLinhas = qLinhas;
       quantidadeDeColunas = qColunas;
   } catch(std::bad_alloc&){
       throw QString("Vai comprar Memoria");
   }
}

void Matriz::setQuantidadeDelinhas(int linhas){
    this->quantidadeDeLinhas = linhas;
}

void Matriz::setQuantidadeDeColunas(int colunas){
    this->quantidadeDeColunas = colunas;
}

void Matriz::setElemento(int elemento, int linha, int coluna)const{
    if(linha<0 || linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo valido");
    if(coluna<0 || coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo valido");
    int pos = linha*quantidadeDeColunas+coluna;
    *(matriz+pos) = elemento;
}

int Matriz::getElemento(int linha, int coluna)const{
    if(linha<0 || linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo valido");
    if(coluna<0 || coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo valido");
    int pos = linha*quantidadeDeColunas+coluna;
    return *(matriz+pos);
}

QString Matriz::getMatriz()const{
    QString saida = "";
    for(int linha = 0; linha < getQuantidadeDeLinhas(); linha++)
    {
        for(int coluna = 0; coluna < getQuantidadeDeColunas(); coluna++)
        {
            saida += QString::number(getElemento(linha,coluna));
            saida += "  ";
        }
        saida += "\n";
    }
    return saida;
}

Matriz* Matriz::operator +(Matriz const * const mat)const{
    if( quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() ||
        quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Nao pode ser adicionadas matriz de tamanhos diferentes");
    try{
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                int valor = this->getElemento(linha,coluna) +
                        mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }

    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}

Matriz* Matriz::operator -(const Matriz *const mat) const{
    if( quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() ||
        quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Nao pode ser adicionadas matriz de tamanhos diferentes");
    try{
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                int valor = this->getElemento(linha,coluna) -
                        mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos subtrair as matrizes");
    }
}

Matriz* Matriz::operator *(const Matriz *const mat) const{
    if(quantidadeDeColunas != mat->getQuantidadeDeLinhas())
        throw QString("Não é possivel fazer a multiplicação");
    try{
       Matriz *aux = new Matriz(quantidadeDeLinhas,mat->getQuantidadeDeColunas());
       int val=0;
       for(int linha=0;linha<quantidadeDeLinhas;linha++){
           for(int coluna=0;coluna<mat->quantidadeDeColunas;coluna++){
               for(int k=0;k<mat->quantidadeDeLinhas;k++){
                   val+=this->getElemento(linha,k)*mat->getElemento(k,coluna);
               }
               aux->setElemento(val,linha,coluna);
               val=0;
           }
       }
       return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }

}

Matriz* Matriz::transposta()const{
    try {
        Matriz* aux = new Matriz(quantidadeDeColunas,quantidadeDeLinhas);
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                aux->setElemento(getElemento(linha,coluna),coluna,linha);
            }
        }
        return aux;
    } catch (std::bad_alloc) {
        throw QString("Vai comprar Memoria");
    }
}

bool Matriz::triangularSuperior()const{
    if(quantidadeDeLinhas != quantidadeDeColunas)
        return false;
    bool test=true;
    for(int linha=0;linha<quantidadeDeLinhas && test==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && test==true;coluna++){
            if(linha > coluna && this->getElemento(linha,coluna)!=0){
                test = false;
            }
        }
    }
    return test;
}

bool Matriz::triangularInferior()const{
    if(quantidadeDeLinhas != quantidadeDeColunas)
        return false;
    bool test=true;
    for(int linha=0;linha<quantidadeDeLinhas && test==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && test==true;coluna++){
            if(linha < coluna && getElemento(linha,coluna)!=0){
                test = false;
            }
        }
    }
    return test;
}

bool Matriz::simetrica()const{//== transposta
    if(quantidadeDeLinhas!=quantidadeDeColunas)
        return false;
    bool aux=true;
    for(int linha=0;linha<quantidadeDeLinhas && aux==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && aux==true;coluna++){
            if(getElemento(linha,coluna)!= getElemento(coluna,linha))
              aux=false;
        }
    }
    return aux;
}

bool Matriz::identidade()const{

    if(quantidadeDeLinhas != quantidadeDeColunas)
        return false;
    bool aux=true;
    for(int linha=0;linha<quantidadeDeLinhas && aux==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && aux==true;coluna++){
            if(linha==coluna && getElemento(linha,coluna)!=1){
                aux = false;
            }
            if(linha!=coluna && getElemento(linha,coluna)!=0){
                aux = false;
            }
        }
    }
    return aux;
}
/*ERRO
bool Matriz::operator==(const Matriz *const mat) const{
    if(this->quantidadeDeColunas != mat->getQuantidadeDeColunas()
         || this->quantidadeDeLinhas != mat->getQuantidadeDeLinhas())
    return false;
    int num = 0;

    int qCol = this->quantidadeDeColunas;
    int qLin = this->quantidadeDeLinhas;

    for(int linha=0;linha<qLin;linha++){
        for(int coluna=0;coluna<qCol;coluna++){
            if (*(this->matriz + (linha * qCol + qLin)) == mat->getElemento(linha,coluna)){
                num++;
            }
        }
    }
    return (num == qCol * qLin);
}
*/

bool Matriz::operator==(const Matriz *const mat) const{
    if(quantidadeDeLinhas!=mat->getQuantidadeDeLinhas() || quantidadeDeColunas!=mat->getQuantidadeDeColunas())
        return false;
    bool ig=true;
    for(int linha=0;linha<quantidadeDeLinhas && ig==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && ig==true;coluna++){
            if(this->getElemento(linha,coluna)!= mat->getElemento(linha,coluna))
            ig=false;
        }
    }
    return ig;
}
bool Matriz::operator!=(const Matriz *const mat) const{
    if(quantidadeDeLinhas!=mat->getQuantidadeDeLinhas() || quantidadeDeColunas!=mat->getQuantidadeDeColunas())
        return true;
    bool dif=false;
    for(int linha=0;linha<quantidadeDeLinhas && dif==false;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && dif==false;coluna++){
            if(this->getElemento(linha,coluna)!=mat->getElemento(linha,coluna))
            dif=true;
        }
    }
    return dif;
}

Matriz* Matriz::potencia(int valor)const{
    if(quantidadeDeLinhas != quantidadeDeColunas)
        throw QString("Não foi possivel fazer a potenciação da matriz");
    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        Matriz *mat = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);

        if(valor==1){
            for(int linha=0;linha<quantidadeDeLinhas;linha++){
                for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                    aux->setElemento(getElemento(linha,coluna),linha,coluna);
                }
            }
        }
        else{
            if(valor==0){
                    for(int linha=0;linha<quantidadeDeLinhas;linha++){
                        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                            if(linha==coluna)
                                aux->setElemento(1,linha,coluna);
                            if(linha!=coluna)
                                aux->setElemento(0,linha,coluna);
                        }
                    }
        }
            else{
                for(int linha=0;linha<quantidadeDeLinhas;linha++){
                    for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                        aux->setElemento(getElemento(linha,coluna),linha,coluna);
                        mat->setElemento(getElemento(linha,coluna),linha,coluna);
                    }
                }
                for(int i=1;i<valor;i++){
                    aux = aux->operator*(mat);
                }
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Vai comprar Memoria");
    }
}

Matriz* Matriz::multiplicacaoPorK(int k)const{
    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        int valor;
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                valor = getElemento(linha,coluna)*k;
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Vai comprar Memoria");
    }
}

bool Matriz::permutacao()const{
    bool PM=true;
    for(int linha=0;linha<quantidadeDeLinhas && PM==true;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas && PM==true;coluna++){
            if(getElemento(linha,coluna)!=0 && getElemento(linha,coluna)!=1)
                PM=false;
        }
    }
    return PM;
}

bool Matriz::ortogonal()const{//se mat * transposta de mat == identidade ela é ortogonal
    try {
        if(quantidadeDeColunas!=quantidadeDeLinhas)
            return false;

        Matriz *transposta = this->transposta();
        //Matriz *resultado = (*this).operator*(transposta);
        Matriz *resultado = this->operator*(transposta);
        if(resultado->identidade())
        {
            delete transposta;
            delete resultado;
            return true;
        }
        else{
            delete transposta;
            delete resultado;
            return false;
        }
    } catch (std::bad_alloc&) {
        throw QString("Vai comprar Memoria");
    }
}

}
