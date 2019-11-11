# Lexical Analysis (词法分析)
![image](../image/cifafenxiqi.jpg)

## 函数声明
```
    void Compiler::lexical_parse(string filepath)
```
## 实现的功能
- 识别标记符(首字符由字母和下划线组成)
- 识别数字
- 识别字符(包含'\t' '\n')
- 识别字符串
- 识别 + - * / % {} [] <> , ; 

## 未实现的功能
- 单行注释
- 多行注释
- 完整的错误信息输出

## 输出的结果
```
    list<Token *> linkListforLex;
```
Token:(Tag,name)
