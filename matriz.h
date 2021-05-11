#ifndef MATRIZ_H
#define MATRIZ_H
#include<QString>

namespace tp2 {
class Matriz
{
private:
    int quantidadeDeLinhas;
    int quantidadeDeColunas;
    int *matriz;
public:
    Matriz(int qLinhas, int qColunas);
    ~Matriz(){if(matriz) delete[] matriz;}
    int getQuantidadeDeLinhas()const{return quantidadeDeLinhas;}
    int getQuantidadeDeColunas()const{return quantidadeDeColunas;}
    void setQuantidadeDelinhas(int linhas);
    void setQuantidadeDeColunas(int colunas);
    void setElemento(int elemento, int linha, int coluna)const;
    int getElemento(int linha, int coluna)const;
    QString getMatriz()const;
    Matriz* operator +(Matriz const * const mat)const;
    Matriz* operator -(Matriz const * const mat)const;
    Matriz* operator *(Matriz const * const mat)const;
    Matriz* transposta()const;
    bool triangularSuperior()const;
    bool triangularInferior()const;
    bool simetrica()const;
    bool identidade()const;
    bool permutacao()const;
    Matriz* potencia(int valor)const;
    bool operator ==(Matriz const * const mat)const;
    bool operator !=(Matriz const * const mat)const;
    Matriz* multiplicacaoPorK(int k)const;
    bool ortogonal()const;
};
}
#endif // MATRIZ_H
