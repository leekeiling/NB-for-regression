#include <iostream>
#include "nb_r_matrix.cpp"
using namespace std;

int main(){
	Matrix matrix;
	matrix.getP();
	double** emotion = matrix.getEmotion();
	vector<string> letterSet = matrix.getLetterSet();
	int *one_num_per = matrix.getOneNumPer();//ÿ��1�ĸ���
	int txtnum = matrix.getTxtNum();//����ı����� 
	vector<string>* txtVector = matrix.getTxtVector(); //��������ı� 
	fstream f("D:\\r_nb_validation_set.csv");
	fstream r_result("D:\\r_result_for_NB.csv",ios::out);
	fstream tf("D:\\nb_tf.txt");
	r_result<<"textid"<<",";
	r_result<<"anger"<<",";
	r_result<<"disgust"<<",";
	r_result<<"fear"<<",";
	r_result<<"joy"<<",";
	r_result<<"sad"<<",";
	r_result<<"surprise"<<","<<"\n";
	string s;	
	int id = 1; 
	while(getline(f,s)){
		fstream one_hot("D:\\nb_tf.txt");
		vector<string> temVector = matrix.split2(s,",");
		vector<string> test = matrix.split2(temVector[0]," ");
		double *data = new double[letterSet.size()]; //��¼�����ı���one_hot���� 
		for(int i=0;i<letterSet.size();i++)	data[i]=0.0;
		double one_num_for_test = 0.0; 	
		double predict[6]={0.0};
		int flag = 0;
		for(int i=0;i<txtnum;i++){
			int data_in_tf;
			double weight = 1.0;
			for(int j=0;j<letterSet.size();j++){
				if(flag==0)//�����ظ���¼ 
					for(int k=0;k<test.size();k++){
						if(letterSet[j]==test[k]){
							data[j] = data[j]+1.0; //��¼�����ı���onehot���� 
							break;
						} 
					}  
				one_hot>>data_in_tf;//��onehhot����洢tf����ķ��Ӳ��� 
				/*lidstoneƽ�� ������Ȼ�� ������tf lidstoneƽ��*/ 
				double data_tf = (data_in_tf*1.0+0.001)/((one_num_per[i]+0.001*letterSet.size())); 
				if(data[j]!=0) 	weight*=data[j]*data_tf*1.0; 
			}//������룻  
			//cout<<weight<<endl;
			flag = 1;
			for(int j=0;j<6;j++) 	predict[j]+=weight*emotion[i][j];
		}	
		double tol = 0.0;
		for(int i=0;i<6;i++) tol+=predict[i];
		r_result<<id<<",";
		for(int i=0;i<6;i++) r_result<<predict[i]/tol<<",";
		r_result<<"\n";
		id++;
		cout<<"end";
	}
}
