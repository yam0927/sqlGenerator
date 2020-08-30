#include<iostream>
#include<vector>
#include<string>
using namespace std;

class queryClause;
class queryClauseFirst;
class queryClauseNotFirst;
class sqlGenerator;

class queryClause {
public:
    void virtual generateQuery() = 0;
};

class queryClauseFirst : public queryClause{
private:
    string attrName;
    string predicate;
    string condition;
public:
    queryClauseFirst(string _attrName, string _predicate, string _condition):attrName(_attrName),
                     predicate(_predicate), condition(_condition){}
    void generateQuery(){
        cout << attrName << " " <<  predicate << " " << condition << " ";
    }
};

class queryClauseNotFirst : public queryClause {
private:
    string attrName;
    string predicate;
    string condition;
    string connector;
public:
    queryClauseNotFirst(string _connector, string _attrName, string _predicate, string _condition):
                       connector(_connector), attrName(_attrName), predicate(_predicate),
                       condition(_condition){}
    void generateQuery(){
        cout << connector << " " << attrName << " " << predicate << " " << condition << " ";
    }
};
class sqlGenarator {
private:
    vector<queryClause*> queries;
public:
    void addQuery(queryClause* query){
        queries.push_back(query);
    }
    void generateSQL(){
        cout << "SELECT * where ";
        for(int i = 0; i < queries.size(); i++){
            queries[i]->generateQuery();
        }
        cout << "FROM CUSTOMER" << endl;
    }
};

int main(){
    sqlGenarator m_generator;
    queryClause *clause1 = new queryClauseFirst("Company name", "equal", "aaa");
    queryClause *clause2 = new queryClauseNotFirst("and", "Contact Title", "not equal", "bbb");
    queryClause *clause3 = new queryClauseNotFirst("or", "Phone", "contains", "6");
    m_generator.addQuery(clause1);
    m_generator.addQuery(clause2);
    m_generator.addQuery(clause3);
    m_generator.generateSQL();
    return 0;
}

