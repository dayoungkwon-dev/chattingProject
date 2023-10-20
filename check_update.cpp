#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using namespace std;

string getFriend(string sender, string accepter);

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "1122"; // �����ͺ��̽� ���� ��й�ȣ


sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::ResultSet* res;

string makeAllID();


// conditionSelect(id = 1, pw = 2, name = 3, phone = 4)
string checkCondition(int conditionSelect) 
{
    string id, name, phone, pw;
    bool isalphaCheck = true, pwCheck = true, phoneCheck = true;
    switch (conditionSelect)
    {
    case 1:
        while (true)
        {
            cout << "\n����� ID�� �Է��� �ּ���(����+����, 20�� �̳�) : ";
            cin >> id;
            for (int i = 0; i < size(id); i++) // ����, ���� �� �ִ��� üũ
            {
                if (isalnum(id[i]) == 0)
                {
                    isalphaCheck = false;
                }
            }

            if (isalphaCheck == false)
            {
                cout << "���̵�� ����� ���� �� �Է��� �����մϴ�." << endl;
                isalphaCheck = true;
            }
            else
            {
                if (makeAllID().find(id) != string::npos) // id �ߺ� üũ
                {
                    cout << "�ߺ��� ID�� �ֽ��ϴ�." << endl;
                }
                else
                {
                    return id;
                    break;
                }
            }
        }
        break;
    case 2:
        while (true)
        {
            cout << "\n����� PW�� �Է��� �ּ���(���� 6�ڸ� ��) : ";
            cin >> pw;
            if (size(pw) != 6)
            {
                pwCheck = false;
            }
            else
            {
                for (int i = 0; i < 6; i++)
                {
                    if (isdigit(pw[i]) == 0)
                    {
                        pwCheck = false;
                    }
                }
            }
            if (pwCheck == false)
            {
                cout << "��й�ȣ�� ���� 6�ڸ� �� �Է��� �����մϴ�." << endl;
                pwCheck = true;
            }
            else 
            {
                return pw;
                break;
            }
        }
        break;
    case 3:
        while (true)
        {
            cout << "\n�̸��� �Է��� �ּ���(10�� ����) : ";
            cin >> name;
            if (size(name) < 1 || size(name) > 10)
            {
                cout << "�̸��� 10�� ���Ͽ��� �մϴ�." << endl;
                
            }
            else
            {
                return name;
                break;
            }
        }
        break;
    case 4:
        while (true)
        {
            cout << "\n��ȭ��ȣ�� �Է��� �ּ���(���������� 11�ڸ�) : ";
            cin >> phone;

            if (size(phone) != 11) // 11�ڸ� üũ
            {
                phoneCheck = false;
            }
            else // 11�ڸ���
            {
                for (int i = 0; i < size(phone); i++)
                {
                    if (isdigit(phone[i]) == 0) // ���� üũ
                    {
                        phoneCheck = false;
                    }
                }
            }

            if (phoneCheck == false)
            {
                cout << "��ȭ��ȣ�� 11���� �����̾�� �մϴ�." << endl;
                phoneCheck = true;
            }
            else
            {
                return phone;
                break;
            }
        }
        break;
    default:
        break;
    }
    system("cls");
}


// updateSelect(pw = 2, name = 3, phone = 4, friend = 5)
void update(string myId, int updateSelect, string updateContents) 
{
    string updateItem;
    

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password);

        // db �ѱ� ������ ���� ���� 
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        if (stmt) { delete stmt; stmt = nullptr; }

        con->setSchema("chattingproject");

        stmt = con->createStatement();
    
        if (updateSelect == 2) updateItem = "password";
        else if (updateSelect == 3) updateItem = "name";
        else if (updateSelect == 4) updateItem = "phoneNumber";
        else if (updateSelect == 5) updateItem = "frienList";
    
        string query = "UPDATE member SET " + updateItem + " = '" + updateContents + "' WHERE (memberID = '" + myId + "')"; // DB�� ����
        stmt->execute(query);
    }
    catch (sql::SQLException& e) {
        delete stmt;
        delete con;
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }

    delete stmt;
    delete con;
}




