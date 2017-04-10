#include <bits/stdc++.h>
using namespace std;

#define dbg(x)   cout<<#x<<"="<<x<<endl
map<string, vector<char > >M;
map<char,vector<string > >prod;
map<char,vector<string > >::iterator it,jt;
vector<char > lead[1000],trail[1000];
int cal_trail[1000],cal_lead[1000];
int table[1000][1000];
vector<int> tab_2[1000][1000];
int isconflict=0;

bool printed[1000];
vector<char>character;
map<char,char> p;

char find(char x){
	if(p[x]==x)
		return x;
	else
		p[x]=find(p[x]);
	return p[x];
}

void Union(char a,char b){
	char x=find(a);
	char y=find(b);
	p[x]=y;
}


bool pos_epsilon(char ch){
	for(int i=0;i<prod[ch].size();i++){
		if(prod[ch][i]=="@")
		return 1;
	}
	return 0;
}

void add_table(char ch1,char ch2,int flag){
	table[ch1][ch2]=flag;
	for(int i=0;i<tab_2[ch1][ch2].size();i++){
		if(tab_2[ch1][ch2][i]==flag)
			return ;
	}
	tab_2[ch1][ch2].push_back(flag);
	if(tab_2[ch1][ch2].size() > 1)
		isconflict=1;
}
void combine_lead(char ch1,char ch2){
	if(ch1==ch2)
	return;
	for(int i=0;i<lead[ch2].size();i++){
		lead[ch1].push_back(lead[ch2][i]);
	}
}

void combine_trail(char ch1,char ch2){
	
	if(ch1==ch2)
	return;
	for(int i=0;i<trail[ch2].size();i++){
		trail[ch1].push_back(trail[ch2][i]);
	}

}

bool is_terminal(char ch1){
	for(int i=0;i<26;i++){
		if('A'+i==ch1)
		return 0;
	}
	for(int i=0;i<character.size();i++){
		if(character[i]==ch1)
			return 1;
	}
	character.push_back(ch1);
	return 1;
}
void add_leading(char ch){

	if(cal_lead[ch]!=0)
		return ;
	else{
		cal_lead[ch]=1;
			for(int i=0;i<prod[ch].size();i++){
				string sub=prod[ch][i];
				for(int j=0;j<sub.length();j++){
					int flag=0;
					if(is_terminal(sub[j])){
						lead[ch].push_back(sub[j]);
					}
					else{
						add_leading(sub[j]);
						combine_lead(ch,sub[j]);
						if(j+1<sub.length() && is_terminal(sub[j+1]))
							lead[ch].push_back(sub[j+1]);

					}
				
					break;
				}
				
			
			}
	}
}

void add_trailing(char ch){

	if(cal_trail[ch]!=0)
		return ;
	else{
	
			cal_trail[ch]=1;
			for(int i=0;i<prod[ch].size();i++){
				string sub=prod[ch][i];
			
				for(int j=sub.length()-1;j>=0;j--){
				
					if(is_terminal(sub[j])){
						trail[ch].push_back(sub[j]);
					}
					else{
					
						add_trailing(sub[j]);
						combine_trail(ch,sub[j]);
						if(j-1>=0 && is_terminal(sub[j-1]))
						trail[ch].push_back(sub[j-1]);
						
					}
				
					break;
				}
				
			
			}
	}
}


char find_non(string str){
	if(M[str].size()>0){
		return M[str][0];
	}
	vector<int> pos;
	for(int i=0;i<str.length();i++)
	{
		if(!is_terminal(str[i])){
			pos.push_back(i);
		}
	}
	
	if(pos.size()==2){
		for(int i=0;i<26;i++){
			for(int j=0;j<26;j++){
				char a=char(i+'A');
				char b=char(j+'A');
				string news=str;
				news[pos[0]]=a;
				news[pos[1]]=b;
				if(find(a)==find(str[pos[0]]) && find(b)==find(str[pos[1]]))
				{
					if(M[news].size()>0)
						return M[news][0];
				}
				
			}
		}	
	}
	else if(pos.size()==1){
		for(int j=0;j<26;j++){
				char b=char(j+'A');
				string news=str;
				news[pos[0]]=b;
				if(find(b)==find(str[pos[0]]))
				{

					if(M[news].size()>0)
						return M[news][0];
				}
				
		}
	}
	
	return '$';
}


void print(stack <char> st,int flag){

	if(flag==0){
			while(st.size()!=0){
				cout<<st.top();
				st.pop();
			}
	}
	else{
		string p="";
		while(st.size()!=0){
			p=st.top()+p;
			st.pop();
		}
		cout<<p;
	}

	cout<<"   ";

}
bool parse(string str){
	stack<char>st,newst;
	char lastterm;
	st.push('$');
	for(int i=str.length()-1;i>=0;i--)
	st.push(str[i]);
	lastterm='$';
	newst.push('$');
	print(newst,1);
	print(st,0);
	
	cout<<endl;
	while(true){
		
		while(table[lastterm][st.top()]==-1 || table[lastterm][st.top()]==2){
			print(newst,1);
			cout<<"\t\t<\t\t";
			print(st,0);
			cout<<endl;
			char c=st.top();
			st.pop();
			newst.push(c);
			lastterm=c;
		}
			print(newst,1);
			cout<<"\t\t>\t\t";
			print(st,0);
			cout<<endl;
		string p="";
		while( (!is_terminal(newst.top()) )|| table[newst.top()][lastterm]!=-1){
			p=newst.top()+p;
			if(is_terminal(newst.top()))
				lastterm=newst.top();
			newst.pop();
		
		
		}
		lastterm=newst.top();
		
		char ans=find_non(p);
		if(ans!='$')
			newst.push(ans);
		else
			break;
			print(newst,1);
			cout<<"\t\t\t\t";
			print(st,0);
			cout<<endl;
		if(newst.size()==2 && st.top()=='$')
			break;
		
		
	}
	
	if(find(newst.top())==find('E') and st.top()=='$'){
		return 1;
	}
	else
		return 0;

	
	
}

void reset(){
	
	for(int i=0;i<26;i++)
	{
		p[char(i+'A')]=char(i+'A');
		
	}
}

void print_char(int k,int flag){
	if(flag)
	cout<<setw(2);
	if(k==0){
		cout<<"E";
	}
	else if(k==1){
		cout<<">";
	}
	else if(k==-1){
		cout<<"<";
	}
	else
	cout<<"=";
	if(flag)
		cout<<" ";
}

int main(){
	reset();
	int n;
	char ch;
	string x;
	cout<<"Enter no of Productions\n";
	cin>>n;

	for(int i=0;i<n;i++) {

		cout<<"Enter Non Terminal\n";
		cin>>ch;
		cout<<"Enter productions with space followed by $\n";
		cin>>x;
		while(x!="$") {
			M[x].push_back(ch);
			prod[ch].push_back(x);
			if(x.length()==1 && !is_terminal(x[0])){
				Union(ch,x[0]);
			}
			cin>>x;
			

		}
	}
	cout<<"dsfjhsjdf\n";
	//calculate leading of each non terminal
	dbg(prod.size());
	for(it=prod.begin();it!=prod.end();it++){
		add_leading(it->first);
	}
	
	//calculate traling of each non terminal
		for(it=prod.begin();it!=prod.end();it++){
		add_trailing(it->first);
	}
	
	//actual check
	
	cout<<"sdfigdhfs\n";
	for(it=prod.begin();it!=prod.end();it++){
		
		char ch=it->first;
		for(int i=0;i<prod[ch].size();i++){
			
			string sub=prod[ch][i];
			
			for(int j=0;j<sub.length()-1;j++){
				if(is_terminal(sub[j]) and is_terminal(sub[j+1]) ) {
					add_table(sub[j],sub[j+1],2);
				}
				if(j<sub.length()-2){
					if(is_terminal(sub[j])  and is_terminal(sub[j+2]) and !is_terminal(sub[j+1])){
						add_table(sub[j],sub[j+2],2);
					}
				}
				if(is_terminal(sub[j]) and !is_terminal(sub[j+1])){
					for(int k=0;k<lead[sub[j+1]].size();k++){
						add_table(sub[j],lead[sub[j+1]][k],-1);
					}
				}
				if(!is_terminal(sub[j]) and is_terminal(sub[j+1])){
					for(int k=0;k<trail[sub[j]].size();k++){
						add_table(trail[sub[j]][k],sub[j+1],1);
					}
				}
			}
		}
	}
	
	for(int i=0;i<lead['E'].size();i++){
		add_table('$',lead['E'][i],-1);
	}
	
	for(int i=0;i<trail['E'].size();i++){
		add_table(trail['E'][i],'$',1);
	}
	
	if(isconflict){
			cout<<"  ";
		for(int i=0;i<character.size();i++){
			cout<<setw(3)<<character[i];
		}
		cout<<endl;
		for(int i=0;i<character.size();i++){
			cout<<setw(2)<<character[i]<<" ";
			for(int j=0;j<character.size();j++){
				for(int k=0;k<tab_2[character[i]][character[j]].size();k++)
					print_char(tab_2[character[i]][character[j]][k],0);
				
				cout<<" ";
			}
			cout<<endl;
		}
		cout<<"Conflict in table\n";
		return 0;
	}
	for(int i=0;i<1000;i++){
		if(lead[i].size()!=0){
			memset(printed,0,sizeof(printed));
			cout<<"leading of "<<char(i)<<endl;
			for(int j=0;j<lead[i].size();j++)
				if(!printed[lead[i][j]]){
						cout<<lead[i][j]<<" ";
						printed[lead[i][j]]=1;
					
				}
			
			cout<<endl;
		}
	}
		for(int i=0;i<1000;i++){
		if(trail[i].size()!=0){
			memset(printed,0,sizeof(printed));
			cout<<"trailing of "<<char(i)<<endl;
			for(int j=0;j<trail[i].size();j++)
				if(!printed[trail[i][j]]){
						cout<<trail[i][j]<<" ";
						printed[trail[i][j]]=1;
				}
			
			cout<<endl;
		}
	}
	character.push_back('$');

	cout<<"  ";
	for(int i=0;i<character.size();i++){
		cout<<setw(2)<<character[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<character.size();i++){
		cout<<setw(2)<<character[i]<<" ";
		for(int j=0;j<character.size();j++){
				print_char(table[character[i]][character[j]] ,1);
		}
		cout<<endl;
	}
	string str;
	cout<<"Give string to parse\n";
	cin>>str;
	if(parse(str)){
		cout<<"String is Valid\n";
	}
	else
		cout<<"String is Invalid\n";
		return 0;

}