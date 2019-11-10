#pragma once
//词法记号标签
enum Tag{
    ERR, //错误
    ID, //标志符
    NUM, //数字
    CH,  //字符
    STR, //字符串
 
    /*关键字*/
    KW_INT,KW_CHAR,  //数据类型 
    KW_IF,KW_ELSE,   //if - else
    KW_RETURN,       //return 
    KW_WHILE,        //while

    ADD,SUB,MUL,DIV,MOD, //+ - * / %
    EQU,                 //比较运算符
    LANGLEBRACKET,RANGLEBRACKET,// < >
    LPAREN,RPAREN, //()
    LBRACK,RBRACK,//[]
    LBRACE,RBRACE,//{}
    COMMA,COLON,SEMCOLON,//, : ;

};

