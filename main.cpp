#include "FamilyTree.h"
//#include "FamilyTree.cpp"

#include<iostream>
#include<conio.h>

int Choice(const char* prompt, const char* options = "");	// ��������

int Pos(char ch, const char* str)			// ����ָ���ַ�ch���ַ���str�е��±ꡣ������ʱ����-1
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        if (ch == str[i])
            return i;
    return -1;
}

int Choice(const char* prompt, const char* options)		// �������塣�����ʾ��Ϣprompt������ѡ����ַ������ء�
{
    int key;
    cout << prompt << "{";
    for (int i = 0; options[i] != '\0'; i++)
    {
        if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// ѡ��options�еĿɴ�ӡ�ַ�
            cout << options[i] << ' ';
        else														// ѡ��options�еĲ��ֿ����ַ�
        {
            switch (options[i])
            {
            case '\t':   cout << "[Tab] ";   break;					// ѡ���е�Tab�ַ�'\t'����ASCII����9��
            case '\x1b': cout << "[Esc] ";   break;					// ѡ���е�Esc�ַ�'\x1b'����ASCII����27��
            case ' ':    cout << "[Space] "; break;					// ѡ���еĿո��ַ�' '����ASCII����32��
            }
        }
    }
    cout << "\b}: ";					// '\b'�˸�����һ��������һ�����
    do
    {
        key = getch();
    } while (options[0] != '\0' && Pos(key, options) < 0); // ��optionsΪ�ճ���Ϊ0���ַ����������������ƣ�����������Ӧ����optins�С�
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
        cout << "1. ��ʾ����" << endl;
        cout << "2. ������n��" << endl;
        cout << "3. ��ѯ��Ϣ" << endl;
        cout << "4. ȷ����ϵ" << endl;
        cout << "5. ��Ӻ���" << endl;
        cout << "6. ɾ��ĳ��" << endl;
        cout << "7. �޸�ĳ����Ϣ" << endl;
        cout << "0. �˳�[Esc]" << endl;
//        item = Choice("��ѡ��", "12345670\x1b")-48;
        cin >> item;
        switch (item) {
        case 1:
            tree.display();
            break;
        case 2:
            cout << "n: ";
            cin >> n;
            tree.ShowInfoOfGenNum(n);
            break;
        case 3:
            cout << "����: ";
            cin >> name1;
            tree.ShowInfoOf(name1);
            break;
        case 4:
            cout << "��һ������: ";
            cin >> name1;
            cout << "�ڶ�������: ";
            cin >> name2;
            tree.relationship(name1, name2);
            break;
        case 5:
            cout << "��������: " << endl;
            cin >> name1;
            tree.addChild(name1);
            break;
        case 6:
            cout << "����" << endl;
            cin >> name1;
            tree.remove(name1);
            break;
        case 7:
            cout << "����" << endl;
            cin >> name1;
            tree.update(name1);
            break;
        case 0:
            tree.exportToFile("test/person_out.txt", "test/case01_out.txt");
            exit(0);
        default:
            break;
        }
    }
}
