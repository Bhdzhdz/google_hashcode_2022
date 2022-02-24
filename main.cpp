#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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
};


struct DataSet{
    vector<Contributor> contributors;
    vector<Project> projects;
};

DataSet read_data(string filename){
    fstream file;
    file.open(filename);

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

    return data;
}

int main(){
    DataSet data = read_data("input_data/a_an_example.in.txt");

    for(auto contributor : data.contributors){
        cout << contributor.name << '\n';

        for(auto skill : contributor.skills){
            cout << skill.name << ' ' << skill.level << '\n';
        }
    }

    for(auto project : data.projects){
        cout << project.name << '\n';
        cout << project.duration << '\n';
        cout << project.score <<
    }

}