#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include"../../header/Tag.h"
using namespace std;
class Compiler{
    private:
    public:
    void lexical_parse(string filepath);
};
//词法记号类
class Token{
    public:
    Tag tag; //词法记号标识
    string name;//词名
    Token(Tag tag,string name):tag(tag),name(name){};
};
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
    int row = 1,col = 1;//行号
    inputFile.open(filepath,ios::in|ios::binary);
    if(!inputFile){                                         //判断输入文件是否存在
        cout<<"***错误:无法打开文件或者文件不存在!"<<endl;   
        exit(0);
    }
   
    while(true){       
        inputFile.get(ch);
        if(inputFile.eof()) break;
        col++;
        if(ch == '\n'){ row++; col=1;} //记录读取的位置
        while(ch == ' ' || ch == 10 || ch == 13 || ch == 9){ //忽略空格、换行、回车、Tab
             inputFile.get(ch);
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
            cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
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
                cout<<'('<<token->tag<<','<<token->name<<')'<<endl;
            }else{
                //检测是否是字符类型 (暂时忽略转义字符)
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
                        token = new Token(ERR,name);
                    }
                    cout<<'('<<token->tag<<','<<token->name<<')'<<endl;

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