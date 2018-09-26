// Author : Rohan Bose (Jalpaiguri Govt. Engg. College)
// This is solution to problem named "Shooting Array" in October Long Challenge 2017 hosted by Codechef
// Problem Link : https://www.codechef.com/OCT17/problems/SHTARR/
// The problem is solved using SquareRoot Decomposition Technique

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int t;
	cin>>t;
	while(t--){
	long long n,q;
	cin>>n>>q;
	long long sq=ceil(sqrt(n));
	long long bsize=400;bsize=max(bsize,sq); //change
	double nd=n,bs=bsize;
	long long maxblocks=ceil(nd/bs);
	vector <long long> vec[maxblocks+1];
	long long ind=1,blocks=1,i,j,inp;
	for(i=1;i<=n;i++)
	{
	    cin>>inp;
	    if(blocks<=bsize)
	    {
	        vec[ind].push_back(inp);++blocks;
	    }
	    else
	    {
	        blocks=1;
	        ++ind;
	        vec[ind].push_back(inp);
	        ++blocks;
	    }
	}
	vector <long long> svec[maxblocks+1];
	for(i=1;i<=maxblocks;i++)
	{
	    long long mini=vec[i][0];
	    svec[i].push_back(mini);
	    for(j=1;j<vec[i].size();j++)
	    {
	        if(vec[i][j]>mini)
	        {
	            mini=vec[i][j];
	            svec[i].push_back(mini);
	        }
	    }
	}

	//query
	while(q--)
	{
	    char ch;
	    cin>>ch;
	    if(ch=='+')
	    {
	        long long x;
	        cin>>ind>>x;
	        double d_ind=ind;
	        long long blocknum=ceil(d_ind/bs);
	        long long in_block_range=ind-((blocknum-1)*bsize)-1;
	        vec[blocknum][in_block_range]+=x;
	        svec[blocknum].clear();
	        long long mini=vec[blocknum][0];
	        svec[blocknum].push_back(mini);
	        for(j=1;j<vec[blocknum].size();j++)
	        {
	            if(vec[blocknum][j]>mini)
	            {
	                mini=vec[blocknum][j];
	                svec[blocknum].push_back(mini);
	            }
	        }
	    }
	    else if(ch=='?')
	    {
	        long long l,r;
	        cin>>ind>>l>>r;
	        double d_ind=ind;
	        long long blocknum=ceil(d_ind/bs);
	        long long in_block_range=ind-((blocknum-1)*bsize)-1;
	        
	        long long ymin=l,ymax=r,ans=0;
	        bool got=false;
	        for(j=in_block_range;j<vec[blocknum].size();j++)
	        {
	            if(vec[blocknum][j]>=ymin)
	            {
	                if(vec[blocknum][j]>=ymax)
	                {
	                    ans=ans+1;
	                    got=true;
	                    break;
	                }
	                else
	                {
	                    ++ans;
	                    ymin=vec[blocknum][j]+1;
	                }
	            }
	        }
	        if(got==false)
	        {
	            long long grymax=0,grymin=0;
	            for(i=blocknum+1;i<=maxblocks;i++)
	            {
	                grymin=upper_bound(svec[i].begin(),svec[i].end(),ymin-1)-svec[i].begin();
	                grymin=svec[i].size()-grymin;
	                grymax=upper_bound(svec[i].begin(),svec[i].end(),ymax-1)-svec[i].begin();
	                grymax=svec[i].size()-grymax;
    	            if(grymin !=0)
    	            {     
    	                if(grymax==0)
    	                {
    	                    ymin=svec[i][svec[i].size()-1]+1;
    	                    ans+=grymin;
    	                }
    	                else
    	                {
    	                    ans+=(abs(grymin-grymax)+1);
    	                    break;
    	                }
    	            }     
	            }
	        }
	        cout<<ans<<endl;
	    }
	}
	}
	return 0;
}