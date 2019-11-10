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
    Token(){};
};
//标记记号类
class Id:public Token{
    public:
    string IdName;
    Id(string IdName):IdName(IdName){
        tag = ID;
    }
};
//数字记号类
class Num:public Token{
    public:
    int NumValue;
    Num(int NumValue):NumValue(NumValue){
        tag = NUM;
    }
};
//字符记号类
class Char:public Token{
    public:
    char ch;
    Char(char ch):ch(ch){
        tag = CH;
    }
};
//字符串记号类
class Str:public Token{
    public:
    string str;
    Str(string str):str(str){
        tag = STR;
    }
};
//关键字记号类
class KeyWord:public Token{
    public:
    string str;
    unordered_map<string, Tag> KwTable;
    KeyWord(){//初始化关键字表
        KwTable["int"] = KW_INT;
        KwTable["char"] = KW_CHAR;
        KwTable["if"] = KW_IF;
        KwTable["else"] = KW_ELSE;
        KwTable["return"] = KW_RETURN;
        KwTable["while"] = KW_WHILE;
    }
    int getKwTag(string str){
        return KwTable.find(str)==KwTable.end()?-1:KwTable[str];
    }
    KeyWord(string str,Tag tagId):str(str){
        tag = tagId;
    }
};

//词法分析
void Compiler::lexical_parse(string filepath){
    fstream inputFile;
    char ch;
    int row = 1,col = 1;//行号
    inputFile.open(filepath,ios::in|ios::binary);
    if(!inputFile){                                         //判断输入文件是否存在
        cout<<"***错误:无法打开文件或者文件不存在!"<<endl;   
        exit(0);
    }
   
    while(true){       
        inputFile.get(ch);
        if(inputFile.eof()) 
            break;
        col++;
        if(ch == '\n'){ row++; col=1;} //记录读取的位置
        
    }
    inputFile.close();                                      //关闭读入文件
}
int main(){
    //Compiler c;
    //c.lexical_parse("../raw/hello.c");
    //KeyWord kw;
    //cout<<kw.getKwTag("int")<<endl;
    return 0;
}