#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <cmath>
#include <math.h>
#include <queue>
using namespace std;

class Matrix{
	public:
		void getP(){//����OneHot���� 
			fstream f("D:\\r_nb_train_set.csv");
			fstream tf("D:\\nb_tf.txt",ios::out);
			int one_sum = 0;
			one_num_per = new int[2000];
			string s;
			const int JOY = 0;
			const int FEAR = 2;
			const int SAD = 1;
			const int SURPRISE = 3;
			const int ANGER = 4;
			const int DISGUST = 5;
			p_emotion = new double*[2000];
			for(int i=0;i<2000;i++)
			{
				p_emotion[i] = new double[6];
				for(int j=0;j<6;j++) p_emotion[i][j]=0;
			}
			while(getline(f,s)){	
				vector<string> temVector = split2(s,",");
				txtVector[txtnum] = split2(temVector[0]," ");
				for(int i=1;i<7;i++) //�����p_emotion�У�p_emotion��¼ÿ����������и��� 
					p_emotion[txtnum][i-1]=atof(temVector[i].c_str());
				for(int i=0;i<txtVector[txtnum].size();i++){
					if(!ifIn(letterSet,txtVector[txtnum][i]) && !InNotRelate(txtVector[txtnum][i])) {
						letterSet.push_back(txtVector[txtnum][i]);
					}
				}
				txtnum++;
			}	
			//���tfδ��һ���������̶�ȡʱ�� 
			for(int i=0;i<txtnum;i++) { 
				int arr[5000]; //����ÿ�з����λ�� 
				for(int j=0;j<5000;j++) arr[j] = -1;
				int arr2[5000]={0};//��¼ͬһ���ʳ��ִ��� 	
				int m = 0; 
				/*����ÿ�е���ز���*/ 
				for(int k=0;k<letterSet.size();k++){	
					for(int j=0;j<txtVector[i].size();j++) {
						if(letterSet[k]==txtVector[i][j]) {
							if(m==0) arr[m++]=k;
							else if(arr[m-1]!=k) arr[m++]=k;
							one_num_per[i]++; 
							arr2[k]++;
						}
					}  
				}
				for(int k=0;k<arr[0];k++) tf<<0<<" ";
				one_sum++;
				tf<<arr2[arr[0]]<<" ";
				for(int j=1;j<m;j++){
					for(int k=0;k<arr[j]-arr[j-1]-1;k++) tf<<0<<" ";;
					tf<<arr2[arr[j]]<<" ";
				}
				if(m>=1)
					if(arr[m-1]<letterSet.size()-1) {
						for(int j=0;j<letterSet.size()-1-arr[m-1];j++)	tf<<0<<" "; ;
					}
				tf<<"\n";;
			}
			cout<<"���ظ����������� "<<letterSet.size()<<endl;
			cout<<"��������: "<<txtnum<<endl; 
		}
		//�ָ�������ʵ����� 
		vector<string> split2(string str,string pattern)
		{
		    int pos;
		    vector<string> result;
		    str+=pattern;//��չ�ַ����Է������
		    int size=str.size();
		
		    for(int i=0; i<size; i++)
		    {
		        pos=str.find(pattern,i);
		        if(pos<size)
		        {
		            std::string s=str.substr(i,pos-i);
		            result.push_back(s);
		            i=pos+pattern.size()-1;
		        }
		    }
		    return result;
		}
		double** getEmotion(){
			return p_emotion;
		}
		int getTxtNum(){
			return txtnum;
		}
		vector<string> getLetterSet(){
			return letterSet;
		}
		vector<string>* getTxtVector(){
			return txtVector;
		}
		int* getOneNumPer(){
			return one_num_per;
		}
	private:
		double **p_emotion; //��¼ѵ����ÿ���ı���������; //��¼ѵ����ÿ���ı��������� 
		int txtnum = 0;
		vector<string> letterSet;
		vector<string> txtVector[2000];
		int *one_num_per = new int[1000]; 
		string not_relate[71]={//����ش�����Լ��ٷ����Ԫ�ص�Ӱ�� 
		"on","to","with","a","will","in","of","x","re","s",
		"are","on","by","could","was","at","the","is","as","its",
		"from","too","near","we","our","an","did","after","their","while",
		"would","who","and","may","us","u","over","be","can",
		"your","if","two","three","you","one","it","t","ever","i",
		"ps","before","or","than","under","here","out","off","n","me",
		"al","th","what","been","all","m","now","his","pm","st","says"};
		//��֤���ʲ��ظ� 
		bool ifIn(vector<string> v,string s) {
			for(int i=0;i<v.size();i++) {
				if(v[i]==s) return true;
			}	
			return false;
		}
		//�ж��Ƿ��ڲ���������� 
		bool InNotRelate(string s){
			for(int i=0;i<70;i++)
				if(s==not_relate[i]) return true;
			return false;
		}
};
