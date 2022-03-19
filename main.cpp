#include "FamilyTree.h"
//#include "FamilyTree.cpp"

#include<iostream>
#include<conio.h>

int Choice(const char* prompt, const char* options = "");	// 函数声明

int Pos(char ch, const char* str)			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        if (ch == str[i])
            return i;
    return -1;
}

int Choice(const char* prompt, const char* options)		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
{
    int key;
    cout << prompt << "{";
    for (int i = 0; options[i] != '\0'; i++)
    {
        if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// 选项options中的可打印字符
            cout << options[i] << ' ';
        else														// 选项options中的部分控制字符
        {
            switch (options[i])
            {
            case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'（即ASCII编码9）
            case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'（即ASCII编码27）
            case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '（即ASCII编码32）
            }
        }
    }
    cout << "\b}: ";					// '\b'退格。先退一格，在输出右花括号
    do
    {
        key = getch();
    } while (options[0] != '\0' && Pos(key, options) < 0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
    cout << endl;
    return key;
}



int main() {
    int n;
    string name1, name2;
    FamilyTree tree;
    tree.importFromFile("test/person.txt", "test/case01.txt");
    int item;
    while (true) {
        cout << "1. 显示家谱" << endl;
        cout << "2. 描述第n代" << endl;
        cout << "3. 查询信息" << endl;
        cout << "4. 确定关系" << endl;
        cout << "5. 添加孩子" << endl;
        cout << "6. 删除某人" << endl;
        cout << "7. 修改某人信息" << endl;
        cout << "0. 退出[Esc]" << endl;
        item = Choice("请选择：", "12345670\x1b")-48;
        switch (item) {
        case 1:
            tree.display();
            break;
        case 2:
            cout << "姓名: ";
            cin >> name1;
            tree.query(name1);
            break;
        case 3:
            cout << "n: ";
            cin >> n;
            tree.describeGeneration(n);
            break;
        case 4:
            cout << "第一人姓名: ";
            cin >> name1;
            cout << "第二人姓名: ";
            cin >> name2;
            tree.relationship(name1, name2);
            break;
        case 5:
            cout << "父亲姓名: " << endl;
            cin >> name1;
            tree.addChild(name1);
            break;
        case 6:
            cout << "姓名" << endl;
            cin >> name1;
            tree.remove(name1);
            break;
        case 7:
            cout << "姓名" << endl;
            cin >> name1;
            tree.update(name1);
            break;
        case 0:
            tree.exportToFile("test/person_out.txt", "test/case01_out.txt");
            exit(0);
        case -21:
            tree.exportToFile("test/person_out.txt", "test/case01_out.txt");
            exit(0);
        default:
            break;
        }
    }
}
