#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

struct Skill{
    string name;
    int level;
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
    vector<Contributor> contributors;
    vector<Project> projects;
};

DataSet read_data(string filename){
    fstream file;
    file.open("input_data/" + filename + ".in.txt");

    DataSet data;
    int contributor_count, project_count;


    file >> contributor_count >> project_count;

    data.contributors.resize(contributor_count);
    data.projects.resize(project_count);

    for(int i = 0; i < contributor_count; i++){
        file >> data.contributors[i].name;
        int skill_count;
        file >> skill_count;
        data.contributors[i].skills.resize(skill_count);
        for(int j = 0; j < skill_count; j++){
            file >> data.contributors[i].skills[j].name >> data.contributors[i].skills[j].level;
        }
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
 
    shuffle(begin(data.contributors), end(data.contributors), g);
    shuffle(begin(data.projects), end(data.projects), g);

    return data;
}

struct Solution{
    vector<string> projects;
    vector<vector<string>> contribuitors;

};

void write_solution(Solution solution, string filename){
    fstream file;
    file.open("output_data/" + filename + ".out.txt");

    file << solution.projects.size() << '\n';

    for(int i = 0; i < solution.projects.size(); i++){
        file << solution.projects[i] << '\n';

        for(int j = 0; j < solution.contribuitors[i].size(); j++) {
            file << solution.contribuitors[i][j] << ' ';
        }
        file << '\n';
    }    
    file.close();
}

int main(){
    string my_case = "a_an_example";

    Solution solution;

    solution.projects = 
        vector<string>({
            "WebServer",
            "Logging",
            "WebChat"
        });

    solution.contribuitors.resize(3);

    solution.contribuitors[0] = 
        vector<string>({
            "Bob", "Anna"
        });

    solution.contribuitors[1] = 
        vector<string>({
            "Anna"
        });

    solution.contribuitors[2] = 
        vector<string>({
            "Maria", "Bob"
        });


    write_solution(solution, "test");

    return 0;
    
    DataSet data = read_data(my_case);

    for(auto contributor : data.contributors){
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
    
}