//
//  main.cpp
//  nfa_to_dfa
//
//  Created by APPLE on 10/17/23.
//



#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

// this class will be used to represent the transtions of states
class transition{
    
public:
    char input;
    char transitions;
    
    transition(char input,char transition){
        
        this->input=input;
        this->transitions=transition;
        
        
    }
public:
    bool input_check(char in){
        
        if (in == input){
            return true;
        }
        
        
        return false;
    }
    bool trans_check(char trans){
        if(transitions==trans){
            return true;
        }
        
        return false;
    }
    
    void print_transition(){
        cout<<endl<<"for input "<<input<<" the next is:";
        cout<<transitions<<endl;
    }
};
    
//this class will represent transition of states in a dfa
class trans_dfa{
public:
    char input;
    vector<char> next_state;
    
    trans_dfa(char input,vector<char> next){
        this->input=input;
        this->next_state=next;
    }
    void add_trans(char in){
        next_state.push_back(in);
        
    }
    void print_transition(){
        cout<<"for "<<input<<endl;
        cout<<"next state is :"<<endl;
        cout<<"{";
        for(char e:next_state ){
            cout<<e<<',';
            
        }
        cout<<"}"<<endl;
    }
        
};

class state_dfa{
    
public:
    vector<char> name;
    vector<trans_dfa*> transitions;
    
    state_dfa(vector<char> n){
        this->name=n;
    }
   
    
public:
    
     static bool unorderedNameEquals( state_dfa* state1,  state_dfa* state2) {
        if (!state1 || !state2) {
            // Handle the case where either pointer is null.
            return false;
        }

        vector<char>& name1 = state1->name;
        vector<char>& name2 = state2->name;

        if (name1.size() != name2.size()) {
            // If the sizes are different, the vectors are not equal.
            return false;
        }

        // Create a copy of name2 so that we can mark elements as "used."
        vector<char> name2Copy = name2;

        // For each character in name1, try to find a corresponding character in name2.
        for ( char c : name1) {
            auto it = find(name2Copy.begin(), name2Copy.end(), c);

            if (it == name2Copy.end()) {
                // If a character from name1 is not found in name2, they are not equal.
                return false;
            }

            // Mark the character as "used" by erasing it from name2Copy.
            name2Copy.erase(it);
        }

        // If we reach this point, all characters in name1 were found in name2.
        return true;
    }

    void add_transition(trans_dfa* in){
        transitions.push_back(in);
    }
    void add_name(char in){
        name.push_back(in);
        
    }
    void print_dfa_state(){
        cout<<"for state {";
        
        for(char e:name){
            cout<<e<<',';
        }
        cout<<"}"<<" transitions are given below";
        for(trans_dfa* el:transitions){
            el->print_transition();
            
        }
    }
    
    
    
};
    
    
    
    


// this class will be used to represent the states of finite automata
class state{
public:
    char name;
public:
    state(char name){
        this->name=name;
    }
    
    vector<transition*> all_transitions;
    
    // the below function will add all the transtions of the state to the transition vector
    void add_transition(transition* input){
        all_transitions.push_back(input);
    };
    
    vector<transition*> ret_transition_vector(){
        
        return this->all_transitions;
    };
    
    // this function checks the name of the vector
    bool name_check(char nam){
        if(name==nam){
            return true;
        }
        return false;
    }
    vector<char> specific(char input){
        vector<char> tr;
        for( transition* elem:all_transitions){
            
            if( elem->trans_check(input)){
                tr.push_back(elem->transitions);
            }
            
        }
        return tr;
        
        
    }
    void print_state(){
        cout<<endl<<"transitions for state "<<name<<" are given below"<<endl;
        for(transition* ele:all_transitions){
            ele->print_transition();
            
        }
    }
    
    
};

// this class will be used to represent nfa
class nfa{
    vector<state*> all_states;
public:
    void add_states(state* input){
        all_states.push_back(input);
        
        
    }
    
    vector<state*> ret_state_vector(){
        return all_states;
    }
    
    // this function returns the transition of a particullar state for a specific in put
    
    state* ret_specific(char name){
       
        for( state* elem:all_states){
            if(elem->name_check(name)){
                return elem;
                
            }
            
            
            
            
        }
        
        
        
        return all_states[0];
        
    };
    
    state* ret_first(){
        return all_states[0];
    }
    
    void print_nfa(){
        cout<<"below is the nfa generated"<<endl;
        
        for(state* ele:all_states){
            ele->print_state();
        }
    }
};

// this class will be used to represent dfa
class dfa{
    vector<state_dfa*> all_states;
    
public:
    void add_states(state_dfa* in){
        all_states.push_back(in);
        
    }
    void print_dfa(){
        for(state_dfa* el:all_states){
            el->print_dfa_state();
        }
    }
   
    
    
};



int main(int argc, const char * argv[]) {
    // insert code here...
    int number_of_states;
    nfa first;
    std::cout << "please enter number of states"<<endl;
    cin>>number_of_states;
    char name;
    
    for(int i=1;i<=number_of_states;i++)
        
    {
        cout<<"enter name of state "<<i<<endl;
        cin>>name;
        
        state* newstate=new state(name);
        first.add_states(newstate);
        
        
        
    }
    int num;
    vector<state*> get_states;
    char input,trans;
    
    get_states=first.ret_state_vector();
    
    for (int i=0;i<number_of_states;i++){
        
        cout<<"enter the number of transitions for "<<get_states[i]->name<<endl;
        cin>>num;
        cout<<"please enter the input and transition for "<<get_states[i]->name<<endl;
        
        for(int j=1;j<=num;j++){
            
            cout<<"enter input for state: "<<get_states[i]->name<<" transition no"<<j<<endl;
            cin>>input;
            cout<<"enter  next state : "<<get_states[i]->name<<" transition no"<<j<<endl;
            cin>>trans;
            transition* in=new transition(input,trans);
            
            get_states[i]->add_transition(in);
            
            
}
        
        
        
    }
    
    // from below here we will be creating a process that converts an  nfa to a dfa
    //creatin a dfa object
    dfa my_dfa;
    
    // creating two vectors observed and unobserved one will hold states explored and the other states that are not explored
    vector<state_dfa*> observed;
    vector<state_dfa*> unobserved;
    //for inialization
    vector<char> in;
    
    // now because the first state of nfa is also the fisrt state of dfa therefore we create a dfa state and give it name as nfa state
    state_dfa*  fir=new state_dfa(in);
    
    /*
     to calcullate the transitions of thsi first state we need to calcullate that this first
     state makes for specific inputs
     */
    
    // we will get the first state of our nfa
    state* dir= first.ret_first();
    
    //we will give our dfa state name
    fir->add_name(dir->name);
    
    // creating a vector containg inputs to be used
    vector<char> inputs={'0','1'};
    // creating a vector that will hold the number of states our first states visits for a specific input
    vector<char> states_visited;
    vector<char> check;
    check.push_back(dir->name);
    
    for (auto c:inputs){
        states_visited=dir->specific(dir->name);
        sort(states_visited.begin(), states_visited.end());
        auto uniqueEnd = unique(states_visited.begin(), states_visited.end());
          states_visited.erase(uniqueEnd, states_visited.end());
        trans_dfa* tra=new trans_dfa(c,states_visited);
        fir->add_transition(tra);
        if (states_visited!=check){
            state_dfa* tem=new state_dfa(states_visited);
            unobserved.push_back(tem);
            
            
        }
        
    }
    observed.push_back(fir);
    
    
    // now as we have some thing in our unobserved we will go forward
    // we will get a state from our unobserved and we will expand it
    state_dfa* fo;
    state* fi;
    vector<char> eas;
    vector<char> t;
    vector<char> assistant;
    bool find=false;
    \
    while(!(unobserved.empty())){
        fo=unobserved[0];
        unobserved.erase(unobserved.begin());
        observed.push_back(fo);
        eas=fo->name;
        for(auto c:inputs)
        {
            
            for(auto j:eas){
                fi=first.ret_specific(j);
                assistant=fi->specific(c);
                t.insert(t.end(), assistant.begin(), assistant.end());
                sort(t.begin(), t.end());
                auto uniqueEnd = unique(t.begin(), t.end());
                  t.erase(uniqueEnd, t.end());
                
                
            }
            trans_dfa* tr=new trans_dfa(c,t);
            fo->add_transition(tr);
            state_dfa* mo=new state_dfa( t);
            
            for (auto ele:observed){
                if(state_dfa::unorderedNameEquals(ele,mo)){
                    find=true;
                }
            }
            
            
            if(!find){
                unobserved.push_back(mo);
            }
            find=false;
        }
        my_dfa.add_states(fo);
        
        
        
        
        
    }
    
    cout<<endl<<"below is your nfa"<<endl;
    first.print_nfa();
    cout<<endl<<"below is you dfa"<<endl;
    my_dfa.print_dfa();
 
    
    
    
        
        
        
       
        
           
            
        
    
    
    
    
    
    
    
    
    
    return 0;
}
