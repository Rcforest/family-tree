#include <iostream>
#include "FamilyTree.h"
int main() {
  int n;
  string name1, name2;
  FamilyTree tree;
  tree.importFromFile();
  int item;
  while (true) {
    cout << "1. 显示家谱" << endl;
    cout << "2. 描述第n代" << endl;
    cout << "3. 查询信息" << endl;
    cout << "4. 确定关系" << endl;
    cout << "5. 添加孩子" << endl;
    cout << "6. 删除某人" << endl;
    cout << "7. 修改某人信息" << endl;
    cout << "0. 退出" << endl;
    cin >> item;
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
        tree.exportToFile();
        exit(0);
      default:
        break;
    }
  }
}
