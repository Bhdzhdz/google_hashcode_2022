#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(),x.end()

struct Skill{
    string name;
    int level;

    bool operator<(const Skill &other){
        return name < other.name;
    }
};

struct Contributor {
    string name;
    vector<Skill> skills;
};

struct Project{
    string name;
    int duration; // duration
    int score; // score
    int best_before;
    vector<Skill> roles;

    /*bool comparator <(bool ){

    }*/
};

struct DataSet{
    unordered_map<string, Contributor> contributors;
    vector<Project> projects;
};

DataSet read_data(string filename);

struct Solution{
    vector<string> projects;
    vector<vector<string>> contributors;

};

void write_solution(Solution solution, string filename);

Solution solution;

unordered_map<string, map<int, set<string>>> with_skill; // name_skill; level, name
unordered_map<string, int> avaiable_at;  // name, time
void accept_project(const Project &project,  const vector<Contributor*> &contributors){

    int start_at = 0;
    int end_at;
    
    for(auto contributor : contributors){
        start_at = max(start_at, avaiable_at[contributor->name]);
    }

    end_at = start_at + project.duration;

    int rol = 0;
    for(auto contributor : contributors){
        avaiable_at[contributor->name] = end_at;

        auto it = lower_bound(all(contributor->skills), project.roles[rol]);

        if(it->level <= project.roles[rol].level){
            with_skill[it->name][it->level].erase(contributor->name);
            with_skill[it->name][1+it->level].insert(contributor->name);
        }

        rol++;
    }

       
    
  
}


int solve(string my_case){

    auto data = read_data(my_case);

    for(auto [name, contributor] : data.contributors){
        for(auto skill : contributor.skills)
            with_skill[skill.name][skill.level].insert(contributor.name);
    }

    //unordered_map<string, map<int, set<string>>> with_skill;
    for(auto project : data.projects){
        vector<Contributor*> ans;
        vector<string> ans_name;
        map<string, bool> used;
      
        for(auto role : project.roles){
            auto first_skill = with_skill[role.name].lower_bound(role.level); 
          
            string contributor_name = "*";

            for(auto current = first_skill; 
                current != with_skill[role.name].end() and contributor_name == "*"; current++){
                  for(auto contributor = current->second.begin(); 
                      contributor != current->second.end() and contributor_name == "*";
                      contributor++){
                        if(not used[*contributor])
                          contributor_name = *contributor;
                      }
            }
          
            if(contributor_name != "*"){
              ans.push_back(&data.contributors[contributor_name]);
              used[contributor_name] = true;

              ans_name.push_back(contributor_name);
            }
            else
              break;
        }

        if(ans.size() == project.roles.size()){
          accept_project(project, ans);  
          
          solution.projects.push_back(project.name);
          solution.contributors.push_back(ans_name);
        }

        write_solution(solution, my_case);
        
    }

    return 0;
    /*
    data = read_data(my_case);

    for(auto [name, contributor] : data.contributors){
        cout << contributor.name << '\n';

        for(auto skill : contributor.skills){
            cout << skill.name << ' ' << skill.level << '\n';
        }
    }

    for(auto project : data.projects){
        cout << project.name << '\n';
        cout << project.duration << '\n';
        cout << project.score << '\n';
    }   
    */
}


DataSet read_data(string filename){
    fstream file;
    file.open("input_data/" + filename + ".in.txt");

    DataSet data;
    int contributor_count, project_count;


    file >> contributor_count >> project_count;

    data.contributors;
    data.projects.resize(project_count);

    for(int i = 0; i < contributor_count; i++){
        string name;
        file >> name;
        int skill_count;
        file >> skill_count;
	data.contributors[name].name = name;
        data.contributors[name].skills.resize(skill_count);
        for(int j = 0; j < skill_count; j++){
            file >> data.contributors[name].skills[j].name >> data.contributors[name].skills[j].level;
        }
        
        sort(all(data.contributors[name].skills));
    }

    for(int i = 0; i < project_count; i++){
        file >> data.projects[i].name >> data.projects[i].duration >> data.projects[i].score >> data.projects[i].best_before;
        int role_count;
        file >> role_count;
        data.projects[i].roles.resize(role_count);
        for(int j = 0; j < role_count; j++){
            file >> data.projects[i].roles[j].name >> data.projects[i].roles[j].level;
        }
        
    }

    file.close();

    random_device rd;
    mt19937 g(rd());
 
    shuffle(begin(data.projects), end(data.projects), g);

    return data;
}



void write_solution(Solution solution, string filename){
    fstream file;
    file.open("output_data/" + filename + ".out.txt");

    file << solution.projects.size() << '\n';

    for(int i = 0; i < solution.projects.size(); i++){
        file << solution.projects[i] << '\n';

        for(int j = 0; j < solution.contributors[i].size(); j++) {
            file << solution.contributors[i][j] << ' ';
        }
        file << '\n';
    }    
    file.close();
}

