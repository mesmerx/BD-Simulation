#include <numeric>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 10000		/* number of iterations */
#define L 100		/* number of iterations */
#define simula 100
using namespace std;
vector<int> altura(L+1), somaalt(max+1);
vector<double> altmedia(max+1),rugo(max+1),delta(max+1),rugo2(max+1),delta2(max+1),rugomedia,rugomediaf(max+1);
vector<vector<double> > rugof (simula+1,vector<double> (max+1));
int coluna;
int i,j,k,m,a;

/* função para adcionar altura a uma coluna*/ 
int adcionaraltura (int coluna) {
/* calculo de altura que vc já conhece*/
if((altura[coluna] >= altura[coluna-1]) && (altura[coluna] >= altura[coluna+1]))
{
altura[coluna]++;
}
 else if(altura[coluna-1] > altura[coluna+1])
      {
         altura[coluna] = altura[coluna-1];
      }
      else
      {   
         altura[coluna] = altura[coluna+1];  
      }
/*cout << coluna << " "<< altura[coluna] << endl;*/

}
/* função para gravar os dados das alturas pro plot*/	
int dados(string const &arquivo){
ofstream meuarquivo (arquivo.c_str(), ios::out | ios::app);
meuarquivo << coluna <<"\t"<< altura[coluna] << "\n";
return 0;

}
/* função para gravar os dados da rugosidade, ainda com só 1 simulação*/
int dadosr(string const &arquivo2,int tempo,int simu){
ofstream meuarquivo2 (arquivo2.c_str(), ios::out | ios::app);
meuarquivo2 << tempo <<"\t"<< rugof[simu][tempo] << "\n";
return 0;

}
int dadosrf(string const &arquivo3){
ofstream meuarquivo3 (arquivo3.c_str(), ios::out | ios::app);
for (int p=1;p<=max;p++){
meuarquivo3 << p <<"\t"<< rugomediaf[p] << "\n";
}
return 0;

}
/* função para somar as alturas*/
int soma(vector<int> altura,int tempo){

somaalt[tempo] = accumulate(altura.begin(), altura.end(), 0);
}
/* função para pegar altura media*/
double alturamedia(int tempo){

altmedia[tempo]=(double) somaalt[tempo]/(L-1);
/*cout << somaalt[tempo] << " " << altmedia[tempo] <<endl;*/
}
/* função para calcular a rugosidade */
double rugosidade(int tempo,int simu){
int i;
/*  varre meu vetor(eliminando o extremo) fazendo o h-hmed depois faz essa diferença ao quadrado*/
for(i=1; i<=L-1; i++){
delta[i]=altura[i]-altmedia[tempo];
rugo[i]=(delta[i]*delta[i]);
/*cout <<"t: "<<i<<"altura: "<<altura[i]<<" altmedia: "<<altmedia[tempo]<<" delta: "<<delta[i]<<endl;*/
}
/*com a diferença calculada ele soma(acumula) e tira a raiz*/
delta2[tempo]= accumulate(rugo.begin(), rugo.end(), 0.0)/L;
rugof[simu][tempo]=sqrt(delta2[tempo]);
/*cout <<"deltas: "<<delta2[tempo]<<" rugf: "<<rugof[simu][tempo]<<endl;*/
}
double rugosidademedia(){
/*soma e tira a media das rugosidades*/
for( int a=1;a<=max;a++){
rugomedia.clear();
for(int m=1; m<=simula; m++){
rugomedia.resize(rugomedia.size()+1,rugof[m][a]);
}
rugomediaf[a]=accumulate(rugomedia.begin(), rugomedia.end(), 0.0)/simula;
/*cout <<rugomediaf[a]<<endl;*/
}

}
main() 
{    

string arquivo;
arquivo="dadosn.dat"; 
string arquivo2;
arquivo2="rugon.dat"; 
string arquivo3;
arquivo3="rugonf.dat";
remove( arquivo3.c_str() );
for(k=1; k<=simula; k++){
for(int o=1; o<=L; o++){
altura[o]=0;
}
/* alimenta o gerador aleatorio, ou sejá a cada segundo meus números aleatorios mudam, deixando quase certo uma aleatoriedade bem forte*/
  srand48(time(NULL));
remove( arquivo.c_str() );
remove( arquivo2.c_str() );
/*faz cada deposito separado, nesse caso vai fazer 10000 depositos */
for(i=1; i<=max; i++){
cout << "deposito: " << i <<endl;
/* deposita as N particulas, nesse caso fiz N igual ao tamanho total da camada*/
for(j=1; j<=L; j++){
coluna = (int)((L-1)*drand48() +1 ); 
adcionaraltura(coluna);
dados(arquivo);
}
/*faz os calculos de somar, media rugosidade e salvar a rugosidade*/
soma(altura,i);
alturamedia(i);
rugosidade(i,k);
/*cout<<rugof[k][i]<<" "<<rugof[1][i]<<endl;*/
dadosr(arquivo2,i,k);
cout<<"simulação:"<<k<<endl;
}    
}
rugosidademedia();
dadosrf(arquivo3);
}        
     
