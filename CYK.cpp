#include <bits/stdc++.h>
using namespace std;
#define dbg(x)  cout<<#x<<"="<<x<<endl

const int N=500;
vector<string>dp[N][N];
map<string ,vector<string> >M;
map<string ,vector<string> >::iterator it;
map<string,int>mark;

int main() {

	int n;
	string ch;
	string x;
	string s;

	cout<<"Enter no of Productions\n";
	cin>>n;

	for(int i=0;i<n;i++) {

		cout<<"Enter Non Terminal\n";
		cin>>ch;
		cout<<"Enter productions with space followed by $\n";
		cin>>x;
		while(x!="$") {
			M[x].push_back(ch);
			cin>>x;
			

		}
	}

	cout<<"Enter String\n";

	cin>>s;

	for(int i=0;i<s.length();i++){

		x=s[i];
		for(int j=0;j<M[x].size();j++)
		{
			dp[1][i].push_back(M[x][j]);
			
		}
	}

	for(int i=2;i<=s.length();i++) {

		for(int j=0;j<s.length();j++) {

			for(int k=1;k<i;k++) {

				for(int t1=0;t1<dp[k][j].size();t1++) {
					for(int t2=0;t2<dp[i-k][j+k].size();t2++) {

						string str=dp[k][j][t1]+dp[i-k][j+k][t2];
						

						if(M[str].size()!=0) {
							for(int x=0;x<M[str].size();x++) {
								dp[i][j].push_back(M[str][x]);
							}
						}
					}
				}
			}



		}
	}
	
	for(int i=0;i<dp[s.length()][0].size();i++)
	{
		string x=dp[s.length()][0][i];
		if(mark[x]==0) {
			cout<<x<<endl;
			mark[x]=1;

		}
	}


}
/*4
S AB BC $
A BB 0 $
B BA 1 $
C AC AA 0 $
110100*/


/* 

4
S AB BC $
A BA a $
B CC b $
C AB a $
baaba
*/
