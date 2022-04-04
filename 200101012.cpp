#include <bits/stdc++.h>

using namespace std;

class bucket{
    public:
        vector<int> v;
        int num_keys;
        int local_depth;
};

int main()
{
    int global_depth,bucket_capacity,c;
    c=0;
    cin >> global_depth;
    cin >> bucket_capacity;
    map<int,bucket*> mp;
    vector<bucket*> vnew;
    int j;
    for(j=0;j<int(pow(2,global_depth));j++){
        bucket* bucket_var= new bucket;
        mp[j]=bucket_var;
        bucket_var->local_depth=global_depth;
        bucket_var->num_keys=0;
        vnew.push_back(bucket_var);
        c++;
    }
    int x,y,z;
    x=2;
    while(x==2 || x==3 || x==4 || x==5){
        cin >> x;
        if(x==2){
            cin >> y;
            int d=0;
            int e=0;
            z=y%(int(pow(2,global_depth)));
            for(auto i=(mp[z]->v).begin();i!=(mp[z]->v).end();i++){
                if(*i==y){
                    d=1;
                    break;
                }
            }
            if(d==0){
                while((mp[z]->num_keys)==bucket_capacity){
                    if((mp[z]->local_depth)==global_depth){
                        if(global_depth==20){
                            cout << "global depth reached 20 , can't insert" << endl;
                            e=1;
                            break;
                        }
                        else{
                            vector<int> tempv;
                            global_depth++;
                            for(j=int(pow(2,global_depth-1));j<int(pow(2,global_depth));j++){
                                mp[j]=mp[j-int(pow(2,global_depth-1))];
                            }
                            bucket* bucket_var= new bucket;
                            (mp[z]->local_depth)++;
                            mp[z]->num_keys=0;
                            mp[z+int(pow(2,global_depth-1))]=bucket_var;
                            bucket_var->local_depth=global_depth;
                            bucket_var->num_keys=0;
                            vnew.push_back(bucket_var);
                            c++;
                            for(auto i=(mp[z]->v).begin();i<(mp[z]->v).end();i++){
                                tempv.push_back(*i);
                            }
                            (mp[z]->v).clear();
                            for(auto i=tempv.begin();i<tempv.end();i++){
                                (mp[(*i)%(int(pow(2,global_depth)))]->v).push_back(*i);
                                (mp[(*i)%(int(pow(2,global_depth)))]->num_keys)++;
                            }
                            tempv.clear();
                            z=y%(int(pow(2,global_depth)));
                        }
                    }
                    else{
                        vector<int> tempv;
                        (mp[z]->local_depth)++;
                        bucket* bucket_var= new bucket;
                        mp[z]->num_keys=0;
                        bucket_var->local_depth=(mp[z%(int(pow(2,(mp[z]->local_depth)-1)))])->local_depth;
                        if(z%(int(pow(2,(mp[z]->local_depth))))>=int(pow(2,(mp[z]->local_depth)-1))){
                            mp[z]=bucket_var;
                        }
                        else{
                            mp[z+int(pow(2,(mp[z]->local_depth)-1))]=bucket_var;
                        }
                        bucket_var->num_keys=0;
                        vnew.push_back(bucket_var);
                        c++;
                        for(auto i=(mp[z%(int(pow(2,(mp[z]->local_depth)-1)))]->v).begin();i<(mp[z%(int(pow(2,(mp[z]->local_depth)-1)))]->v).end();i++){
                            tempv.push_back(*i);
                        }
                        (mp[z%(int(pow(2,(mp[z]->local_depth)-1)))]->v).clear();
                        for(auto i=tempv.begin();i<tempv.end();i++){
                            (mp[(*i)%(int(pow(2,mp[z]->local_depth)))]->v).push_back(*i);
                            (mp[(*i)%(int(pow(2,mp[z]->local_depth)))]->num_keys)++;
                        }
                        tempv.clear();
                        for(j=int(pow(2,mp[z]->local_depth));j<int(pow(2,global_depth));j++){
                            if((j%int(pow(2,(mp[z]->local_depth)-1)))==(z%int(pow(2,(mp[z]->local_depth)-1)))){
                                mp[j]=mp[j%(int(pow(2,(mp[z]->local_depth))))];
                            }
                        }
                        z=y%(int(pow(2,global_depth)));
                        
                    }
                }
                if(e==1){
                    break;
                }
                (mp[z]->v).push_back(y);
                (mp[z]->num_keys)++;
            }
        }
        if(x==3){
            cin >> y;
            int a=0;
            z=y%(int(pow(2,global_depth)));
            if((mp[z]->num_keys)!=0){
                for(auto i=(mp[z]->v).begin();i!=(mp[z]->v).end();i++){
                    if(*i==y){
                        a=1;
                        break;
                    }
                }
            }
            if(a==1){
                cout << "Found" << endl;
            }
            else{
                cout << "Not Found" << endl;
            }
        }
        if(x==4){
            cin >> y;
            int b=0;
            z=y%(int(pow(2,global_depth)));
            if((mp[z]->num_keys)!=0){
                for(auto i=(mp[z]->v).begin();i!=(mp[z]->v).end();i++){
                    if(b==1){
                        *(i-1)=*i;
                    }
                    if(*i==y){
                        b=1;
                    }
                }
            }
            if(b==1){
                (mp[z]->v).pop_back();
                (mp[z]->num_keys)--;
                cout << "deleted" << endl;
            }
            else{
                cout << "not deleted , no existence" << endl;
            }
            
        }
        if(x==5){
            cout << global_depth << endl;
            cout << c << endl;
            for(auto i=vnew.begin();i!=vnew.end();i++){
                cout << (*i)->num_keys << " " << (*i)->local_depth << endl;
            }
        }
    }
    return 0;
}