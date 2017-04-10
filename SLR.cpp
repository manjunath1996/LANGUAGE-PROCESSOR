#include <bits/stdc++.h>
using namespace std;
#define dbg(x)   cout<<#x<<"="<<x<<endl

map<string, vector<char > >M;
map<char,vector<string > >prod;




struct SLRitem{
	char nonT;
	string body;
	int index;

	bool  operator < (const SLRitem &other)const{
		if(nonT!=other.nonT)
			return nonT<other.nonT;
		else if(body!=other.body)
			return body<other.body;
		return index<other.index;

	}
	
};

int fre=1,prodno=1;
map < SLRitem ,set<SLRitem> >closure;
map < set<SLRitem> ,int >SLRitemset;
map <int, set<SLRitem>  >rev;
map < SLRitem,int >cal_closure;
map < pair<char,string> ,int > prodNumber;
map < int,pair<char,string> >revprod;

map < int ,map< char, pair< int, char> > > action;

map< char, set<SLRitem> > got[1000];
vector<char>character;
vector<char> follow[1000],firsty[1000];
int cal_first[1000],cal_follow[1000];

string t_string(int x)
{
	string s="";
	while(x)
	{
		int y=x%10;
		x/=10;
		s=(char('0'+y))+s;
	}
	return s;
}

void print(stack <char> s1,stack<int>s2){

	int flag=1;
	string ans="";
	while(!s1.empty() || !s2.empty()){
		if(flag==0)
		{
			ans=s1.top()+ans;
			s1.pop();
		}
		else
		{
			ans=t_string(s2.top())+ans;
			s2.pop();
		}
		flag^=1;
	}
	
	cout<<ans<<"             ";
}
void print(stack <char> st){

	
	while(st.size()!=0){
		cout<<st.top();
		st.pop();
	}
	
	

	cout<<"   ";

}


bool parse(string str){
	dbg(str);
	stack <char> s1;
	stack <int> s2;
	stack <char> input;
	input.push('$');
	for(int k=str.length()-1;k>=0;k--)
		input.push(str[k]);
	s1.push('$');
	s2.push(1);

	while(!input.empty()){
		print(s1,s2);
		print(input);

		int state=s2.top();
		cout<<endl;
		if(action[state][input.top()].second=='S'){
			s1.push(input.top());
			s2.push(action[state][input.top()].first);
			input.pop();


		}
		else if(action[state][input.top()].second=='R'){
			int cnt=revprod[action[state][input.top()].first].second.length();
			cnt+=cnt;
			int flag=0;
			while(cnt--){
				if(flag==0)
					s2.pop();
				else
					s1.pop();
				flag^=1;
			}
			char ch=revprod[action[state][input.top()].first].first;
			
			s1.push(ch);
			state=s2.top();
			s2.push(action[state][ch].first);
			

		}
		else if(action[state][input.top()].second=='A'){
			cout<<"Accepted\n";
			return 0;
		}
		else
		{
			cout<<"ERROR \n";
			return 0;
		}
	}
	
}




bool pos_epsilon(char ch){
	for(int i=0;i<prod[ch].size();i++){
		if(prod[ch][i]=="@")
		return 1;
	}
	return 0;
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


void combine_first(char ch1,char ch2){
	if(ch1==ch2)
	return;
	for(int i=0;i<firsty[ch2].size();i++){
		firsty[ch1].push_back(firsty[ch2][i]);
	}
}

void add_first(char ch){

	if(cal_first[ch]!=0)
		return ;
	else{
		cal_first[ch]=1;
			for(int i=0;i<prod[ch].size();i++){
				string sub=prod[ch][i];
				for(int j=0;j<sub.length();j++){
					int flag=0;
					if(is_terminal(sub[j])){
						firsty[ch].push_back(sub[j]);
					}
					else{
						add_first(sub[j]);
						combine_first(ch,sub[j]);
						if(pos_epsilon(sub[j]))
							flag=1;
					}
					if(flag==0)
						break;
				}
				
			
			}
	}
}
void combine_follow_first(char ch1,char ch2){
	
	for(int i=0;i<firsty[ch2].size();i++){
		int flag=0;
		for(int k=0;k<follow[ch1].size();k++){
			if(firsty[ch2][i]==follow[ch1][k])
				flag=1;
		}
		if(flag==0)
		follow[ch1].push_back(firsty[ch2][i]);
	}
}
void combine_follow_follow(char ch1,char ch2){
	if(ch1==ch2)
	return;
	for(int i=0;i<follow[ch2].size();i++){
		int flag=0;
		for(int k=0;k<follow[ch1].size();k++){
			if(follow[ch2][i]==follow[ch1][k])
				flag=1;
		}
		if(flag==0)
		follow[ch1].push_back(follow[ch2][i]);
	}
}


void add_follow(char ch){

	if(cal_follow[ch]!=0)
		return ;
	else{
		cal_follow[ch]=1;

		for(auto jt=M.begin();jt!=M.end();jt++){
			
			string sub=jt->first;
			int x=sub.length()+1;

			for(int i=0;i<sub.length();i++){

				if(sub[i]==ch){
					x=i;
					break;
				}
			}
			if(x==sub.length()-1){
					add_follow(jt->second[0]);
					combine_follow_follow(ch,jt->second[0]);
			}
			for(int i=x+1;i<sub.length();i++){
				int flag=0;
				if(is_terminal(sub[i])){
					follow[ch].push_back(sub[i]);
				}
				else{
					add_first(sub[i]);
					combine_follow_first(ch,sub[i]);
					if(pos_epsilon(sub[i]))
						flag=1;
				}
				if(flag==0)
					break;
				if(i==sub.length()-1){
					add_follow(jt->second[0]);
					combine_follow_follow(ch,jt->second[0]);
				}
			}


		}
		
	}
}



set<SLRitem>  add_sets(set<SLRitem > to,set<SLRitem>  from){
	

	for(auto it:from){
		to.insert(it);
	}

	return to;

}

set<SLRitem>  find_closure(SLRitem k){
	
	
	if(closure[k].size()!=0)
		return closure[k];
	
	closure[k].insert(k);
	if(k.index>=k.body.length()){
		
	
		return closure[k];
	}
	else{
		
		char ch=k.body[k.index];
	
		if(!is_terminal(ch)){
			
			for(int i=0;i<prod[ch].size();i++){
				SLRitem temp;
				temp.nonT=ch;
				temp.body=prod[ch][i];
				temp.index=0;
				set<SLRitem > s=find_closure(temp);
				closure[k]=add_sets(closure[k],s);
			}
		}

	}
	
		return closure[k];
}

int main( ){

	int n;
	char ch;
	string x;
	cout<<"Enter no of Productions\n";
	cin>>n;


	for(int i=0;i<n;i++) {

		cout<<"Enter Non Terminal\n";
		cin>>ch;
		character.push_back(ch);
		cout<<"Enter productions with space followed by $\n";
		cin>>x;
		while(x!="$") {
			prodNumber[{ch,x}]=prodno;
			revprod[prodno++]={ch,x};
			M[x].push_back(ch);
			prod[ch].push_back(x);
			cin>>x;
		}	
	}

	

	//Augmenting 
	M["E"].push_back('Z');
	prod['Z'].push_back("E");
	follow['E'].push_back('$');


	SLRitem k;
	k.nonT='Z';
	k.body="E";
	k.index=0;
	
	
	



	SLRitemset[find_closure(k)]=fre;
	
	
	rev[fre++]=find_closure(k);
	queue < set<SLRitem>  >q;
	q.push(find_closure(k));



	while(!q.empty()){

		set<SLRitem> s=q.front();
		q.pop();
		int setnum=SLRitemset[s];

		for(auto it: s){
			SLRitem k=it;
			if(k.index==k.body.length())
				continue;
			else{
				char ch=k.body[k.index];
				k.index++;
				got[setnum][ch]=add_sets(got[SLRitemset[s]][ch],find_closure(k));
			}

		}

		for (auto jt=got[setnum].begin();jt!=got[setnum].end();jt++){
			
			if(SLRitemset[jt->second]==0){
				
				SLRitemset[jt->second]=fre;
				rev[fre++]=jt->second;
				q.push(jt->second);
			}
		}

	}


	for(int i=1;i<fre;i++){
		cout<<"itemset "<<i<<"\n";
		
		set< SLRitem > s=rev[i];
		for(auto jt : s){
			cout<<jt.nonT<<" "<<jt.body<<" "<<jt.index<<endl;
		}
		
		cout<<endl;
	}



	for(int i=1;i<fre;i++){

		for (auto jt=got[i].begin();jt!=got[i].end();jt++){
			 
			 	action[i][jt->first].first=SLRitemset[jt->second];
			 	if(is_terminal(jt->first))
			 		action[i][jt->first].second='S'; 
			 	else
			 		action[i][jt->first].second='J'; 
			 	

		}
		set< SLRitem > s=rev[i];
		for(auto jt : s){
			if(jt.body.length()==jt.index){
				if(jt.nonT=='Z' && jt.body=="E"){
					action[i]['$'].first=100;
					action[i]['$'].second='A';
					continue;
				}
				add_follow(jt.nonT);
				cout<<"follow of "<<jt.nonT<<endl;
				for(int k=0;k<follow[jt.nonT].size();k++){
					dbg(follow[jt.nonT][k]);
					action[i][follow[jt.nonT][k]].first=prodNumber[{jt.nonT,jt.body}];
			 		action[i][follow[jt.nonT][k]].second='R'; 
				}
				cout<<"***\n";
			}
		}

	}


	sort(character.begin(),character.end());
	character.push_back('$');
	cout<<"         ";
	for(int k=0;k<character.size();k++)
		cout<<setw(2)<<character[k]<<" ";
	cout<<endl;
	for(int i=1;i<fre;i++){

		cout<<"state "<<i<<" : ";
		for(int j=0;j<character.size();j++){
			if(action[i][character[j]].first!=0)
				cout<<action[i][character[j]].first<<action[i][character[j]].second<<" ";
		else
				cout<<"E  ";

		}
		cout<<endl;
	}


	string str;
	cout<<"Enter string to parse\n";
	cin>>str;

	parse(str);









	
}

/*
3
E
E+T
T
$
T
T*F
F
$
F
(E)
a
$
a+a*a
*/
