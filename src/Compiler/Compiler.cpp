#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<list>
#include"../../header/Tag.h"
using namespace std;
//词法记号类
class Token{
    public:
    Tag tag; //词法记号标识
    string name;//词名
    Token(Tag tag,string name):tag(tag),name(name){};
};
class Compiler{
    private:
    list<Token *> linkListforLex;
    public:
    void lexical_parse(string filepath);
    void LexErrorProcess(int row,string message);
};
void Compiler::LexErrorProcess(int row,string messages){
    cout<<"***错误***:"<<messages<<",错误产生于第"<<row<<"行"<<"。"<<endl;
    exit(0);
}
static Tag getKwTag(string str){
    static unordered_map<string, Tag> KwTable;
    KwTable["int"] = KW_INT;
    KwTable["char"] = KW_CHAR;
    KwTable["if"] = KW_IF;
    KwTable["else"] = KW_ELSE;
    KwTable["return"] = KW_RETURN;
    KwTable["while"] = KW_WHILE;
    return KwTable.find(str)==KwTable.end()?ID:KwTable[str];
}

//词法分析
void Compiler::lexical_parse(string filepath){
    fstream inputFile;
    char ch;
    Tag tag;
    string name;
    Token *token;
    int row = 1;//行号
    inputFile.open(filepath,ios::in|ios::binary);
    if(!inputFile){                                         //判断输入文件是否存在
        cout<<"***错误***:无法打开文件或者文件不存在!"<<endl;   
        exit(0);
    }
   
    while(true){
        if(ch == '\n'){ row++;} //记录读取的位置       
        inputFile.get(ch);
        if(inputFile.eof()) break;
        if(ch == '\n'){ row++;} //记录读取的位置
        while(ch == ' ' || ch == 10 || ch == 13 || ch == 9){ //忽略空格、换行、回车、Tab
             inputFile.get(ch); 
             if(inputFile.eof()) break;
        }
        if(inputFile.eof()) break;
        if((ch>='a'&&ch<='z') || ch=='_' || (ch>='A'&&ch<='Z')){//判断是不是标记符或者关键字
             name = "";//记录符号串 初始化
             do{
                name.push_back(ch);
                inputFile.get(ch);
             }while(((ch>='a'&&ch<='z') ||(ch>='0'&&ch<='9')|| ch=='_' || (ch>='A'&&ch<='Z'))&&!inputFile.eof());//文件结束跳出循环
            //判断是不是关键字
            tag = getKwTag(name);
            token = (tag == ID) ? new Token(ID,name):new Token(tag,name);
            //cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
            linkListforLex.push_back(token);
        }else{
            if(ch >= '0' && ch <= '9'){ //检测是否是整数，只识别十进制整数
                name = "";
                do{
                    name.push_back(ch);
                    inputFile.get(ch);
                }while((ch >= '0' && ch <= '9')&&(!inputFile.eof()));
                /*
                分析:跳出循环的情况:
                1.文件结束
                2.正常 遇到Space、=、>、）、]、;
                3.非正常 遇到字母、_、
                */
                token = new Token(NUM,name);
                //cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
                linkListforLex.push_back(token);
            }else{
                //检测是否是字符类型
                if(ch == '\''){
                    name = "";
                    inputFile.get(ch);
                    do{
                        name.push_back(ch);
                        inputFile.get(ch);
                    }while((ch != '\'')&&(!inputFile.eof()));
                    if(!(inputFile.eof())&& (ch == '\'') && (name.length()==1)){
                        token = new Token(CH,name);
                    }else{
                        if(!(inputFile.eof())&& (ch == '\'') && (name.length()==2) ){
                            if(name[0] == '\\' && name[1] == 'n')
                                token = new Token(CH,"\n");
                            if(name[0] == '\\' && name[1] == 't')
                                token = new Token(CH,"\t");
                        }else{
                            token = new Token(ERR,name);
                            LexErrorProcess(row,"缺失右单引号或者引号内为空");
                        }
                    }
                    //cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
                    linkListforLex.push_back(token);
                }else if(ch == '"'){
                    name = "";
                    inputFile.get(ch);
                    do{
                        name.push_back(ch);
                        inputFile.get(ch);
                    }while((ch != '"')&&(!inputFile.eof()));
                    if(!(inputFile.eof()) && (ch == '"')){
                        token = new Token(STR,name);
                    }else{
                        token = new Token(ERR,name);
                        LexErrorProcess(row,"缺失右双引号");
                    }
                    //cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
                    linkListforLex.push_back(token);
                }else{
                    name = "";
                    name.push_back(ch);
                    switch(ch){
                        case '=':
                            token = new Token(EQU,name);break;           
                        case '+':
                            token = new Token(ADD,name);break;
                        case '-':
                            token = new Token(SUB,name);break; 
                        case '*':
                            token = new Token(MUL,name);break;
                        case '\\':
                            token = new Token(DIV,name);break;
                        case '%':
                            token = new Token(MOD,name);break;
                        case '<':
                            token = new Token(LANGLEBRACKET,name);break;
                        case '>':
                            token = new Token(RANGLEBRACKET,name);break;
                        case '(':
                            token = new Token(LPAREN,name);break;
                        case ')':
                            token = new Token(RPAREN,name);break;
                        case '[':
                            token = new Token(LBRACK,name);break;
                        case ']':
                            token = new Token(RBRACK,name);break;
                        case '{':
                            token = new Token(LBRACE,name);break;
                        case '}':
                            token = new Token(RBRACE,name);break;  
                        case ',':
                            token = new Token(COMMA,name);break;
                        case ':':
                            token = new Token(COLON,name);break;
                        case ';':
                            token = new Token(SEMCOLON,name);break;
                        default:
                            token = new Token(ERR,name);
                            LexErrorProcess(row,"非法符号");
                            break;
                             
                    }
                    //cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
                    linkListforLex.push_back(token);
                }
            }

        }
        
    }
    inputFile.close();                                      //关闭读入文件
}
int main(){
    Compiler c;
    c.lexical_parse("../raw/hello.c");
    //KeyWord kw;
    //cout<<kw.getKwTag("int")<<endl;
    return 0;
}