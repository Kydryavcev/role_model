#include <iostream>
#include <ctime>
#include <Windows.h>
#include <typeinfo>
#include "Person.h"
#include "Admin.h"
#include "Employee.h"
#include "Relation.h"
#include "SQL.h"
#include "Model.h"


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try
    {
        Model m("users");

        string login, password;

        do
        {
            cout << "Введите логин: ";
            cin >> login;

            if (m.identification(login))
            {
                break;
            }
            else
            {
                cout << "Вы ввели неверный логин. Попробуйте ещё раз." << endl;
            }

        } while (true);

        do
        {
            cout << "Введите пароль: ";
            cin >> password;

            if (m.authentication(password))
            {
                break;
            }
            else
            {
                cout << "Вы ввели неверный пароль. Попробуйте ещё раз." << endl;
            }

        } while (true);

        if (m.authorization())
        {
            cout << "Аутентификация прошла успешна." << endl;

            Sleep(1000);
        }
        else
        {
            cout << "В ходе аутентификации прошли непредвиденные шоколадки." << endl;

            return -1;
        }

        system("cls");

        cout << "Доступные роли" << endl;

        vector<map<string, string, less<string> > > roles = m.getUserRoles();

        for (int i = 0; i < roles.size(); i++)
        {
            cout << i + 1 << ") " << roles[i]["description"] << ";" << endl;
        }

        unsigned roleNumSel;

        while (true)
        {
            cout << "Выберите роль, под которой желаете войти: ";

            cin >> roleNumSel;

            if (cin.good() && roleNumSel > 0 && roleNumSel < roles.size() + 1)
            {
                cin.ignore(30, '\n');

                break;
            }

            cin.clear();

            cout << "Вы ввели некорректные данные. Введите число от 1 до " << roles.size() << ". Соответствующее нужному пункту меню." << endl;

            cin.ignore(30, '\n');
        }

        m.setRole(stoi(roles[roleNumSel - 1]["role"]));

        cout << endl << "Вы вошли как " << roles[roleNumSel - 1]["description"] << endl;

        Sleep(1000);

        system("cls");

        unsigned numMenu;

        vector<map<string, string, less<string> > > objects = m.getObjects();

        while (true)
        {
            cout << "----------------Меню----------------" << endl << endl;

            for (int i = 0; i < objects.size(); i++)
            {
                cout << i + 1 << ") " << objects[i]["name"] << ";" << endl;
            }

            cout << "0) Выход из программы." << endl << endl;

            cout << "------------------------------------" << endl;

            while (true)
            {
                cout << "Ваш выбор: ";

                cin >> numMenu;

                if (cin.good())
                {
                    cin.ignore(30, '\n');

                    break;
                }

                cin.clear();

                cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

                cin.ignore(30, '\n');
            }

            if (numMenu == 0)
            {
                cout << "Пора в отпуск! Всем пока!" << endl;
                Sleep(1000);

                return 0;
            }
            else if (numMenu > 0 && numMenu < objects.size() + 1)
            {
                regex rgobj{ R"(.+\.exe)" };

                if (regex_match(objects[numMenu - 1]["name"].begin(), objects[numMenu - 1]["name"].end(), rgobj))
                {
                    cout << "1) Выполнить;" << endl << "0) Выход" << endl;

                    int numMenuFile;

                    while (true)
                    {
                        cout << "Ваш выбор: ";

                        cin >> numMenuFile;

                        if (cin.good() && numMenuFile >= 0 && numMenuFile < 2)
                        {
                            cin.ignore(30, '\n');

                            break;
                        }

                        cin.clear();

                        cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

                        cin.ignore(30, '\n');
                    }

                    switch (numMenuFile)
                    {
                    case 0:
                    {
                        continue;
                    }
                    case 1:
                    {
                        int objectNum = stoi(objects[numMenu - 1]["object"]);

                        try
                        {
                            m.executeObject(objectNum);
                        }
                        catch (Model::ModelException ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << ex.discription << endl;
                        }
                        catch (Model::UnauthorizedAccess ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

                            cout << "Доступ запрещен!" << endl;
                        }

                        break;
                    }
                    default:
                        cout << "Вы ввели некорректные данные." << endl;
                        break;
                    }
                }
                else
                {
                    cout << "1) Прочитать;" << endl
                        << "2) Переписать;" << endl
                        << "0) Выход" << endl;

                    int numMenuFile;

                    while (true)
                    {
                        cout << "Ваш выбор: ";

                        cin >> numMenuFile;

                        if (cin.good() && numMenuFile >= 0 && numMenuFile < 3)
                        {
                            cin.ignore(30, '\n');

                            break;
                        }

                        cin.clear();

                        cout << "Вы ввели некорректные данные. Введите число от 0 до 2. Соответствующее нужному пункту меню." << endl;

                        cin.ignore(30, '\n');
                    }

                    switch (numMenuFile)
                    {
                    case 0: 
                    {
                        continue;
                    }
                    case 1:
                    {
                        int objectNum = stoi(objects[numMenu - 1]["object"]);

                        try
                        {
                            m.readObject(objectNum);
                        }
                        catch (Model::ModelException ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << ex.discription << endl;
                        }
                        catch (Model::UnauthorizedAccess ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

                            cout << "Доступ запрещен!" << endl;
                        }

                        break;
                    }
                    case 2:
                    {
                        int objectNum = stoi(objects[numMenu - 1]["object"]);

                        try
                        {
                            m.writeObject(objectNum);
                        }
                        catch (Model::ModelException ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << ex.discription << endl;
                        }
                        catch (Model::UnauthorizedAccess ex)
                        {
                            cout << endl << "Произошло исключение" << endl << endl;

                            cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

                            cout << "Доступ запрещен!" << endl;
                        }

                        break;
                    }
                    default:
                        cout << "Вы ввели некорректные данные." << endl;
                        break;
                    }
                }

                Sleep(2500);
            }
            else
            {
                cout << "Вы ввели некорректные данные. Введите число от 0 до " << objects.size() << ". Соответствующее нужному пункту меню." << endl;
                Sleep(2000);
                break;
            }

            system("cls");
        }

        //if (m.isAdmin())
        //{
        //    unsigned numMenu;

        //    vector<map<string, string, less<string> > > objects = m.getObjects();

        //    while (true)
        //    {
        //        cout << "----------------Меню----------------" << endl << endl;

        //        for (int i = 0; i < objects.size(); i++)
        //        {
        //            cout << i + 1 << ") " << objects[i]["name"] << ";" << endl;
        //        }

        //        cout << "0) Выход из программы." << endl << endl;

        //        cout << "------------------------------------" << endl;

        //        while (true)
        //        {
        //            cout << "Ваш выбор: ";

        //            cin >> numMenu;

        //            if (cin.good())
        //            {
        //                cin.ignore(30, '\n');

        //                break;
        //            }

        //            cin.clear();

        //            cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

        //            cin.ignore(30, '\n');
        //        }

        //        if (numMenu == 0)
        //        {
        //            cout << "Пора в отпуск! Всем пока!" << endl;
        //            Sleep(1000);

        //            return 0;
        //        }
        //        else if (numMenu > 0 && numMenu < objects.size() + 1)
        //        {
        //            regex rgobj{ R"(.+\.exe)" };

        //            if (regex_match(objects[numMenu - 1]["name"].begin(), objects[numMenu - 1]["name"].end(), rgobj))
        //            {
        //                cout << "1) Выполнить;" << endl << "0) Выход" << endl;

        //                int numMenuFile;

        //                while (true)
        //                {
        //                    cout << "Ваш выбор: ";

        //                    cin >> numMenuFile;

        //                    if (cin.good() && numMenuFile >= 0 && numMenuFile < 2)
        //                    {
        //                        cin.ignore(30, '\n');

        //                        break;
        //                    }

        //                    cin.clear();

        //                    cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

        //                    cin.ignore(30, '\n');
        //                }

        //                switch (numMenuFile)
        //                {
        //                case 0:
        //                {
        //                    continue;
        //                }
        //                case 1:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    try
        //                    {
        //                        m.executeObject(objectNum);
        //                    }
        //                    catch (Model::ModelException ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << ex.discription << endl;
        //                    }
        //                    catch (Model::UnauthorizedAccess ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                        cout << "Доступ запрещен!" << endl;
        //                    }

        //                    break;
        //                }
        //                default:
        //                    cout << "Вы ввели некорректные данные." << endl;
        //                    break;
        //                }
        //            }
        //            else
        //            {
        //                cout << "1) Прочитать;" << endl
        //                    << "2) Переписать;" << endl
        //                    << "0) Выход" << endl;

        //                int numMenuFile;

        //                while (true)
        //                {
        //                    cout << "Ваш выбор: ";

        //                    cin >> numMenuFile;

        //                    if (cin.good() && numMenuFile >= 0 && numMenuFile < 3)
        //                    {
        //                        cin.ignore(30, '\n');

        //                        break;
        //                    }

        //                    cin.clear();

        //                    cout << "Вы ввели некорректные данные. Введите число от 0 до 2. Соответствующее нужному пункту меню." << endl;

        //                    cin.ignore(30, '\n');
        //                }

        //                switch (numMenuFile)
        //                {
        //                case 0:
        //                {
        //                    continue;
        //                }
        //                case 1:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    if (objectNum == 4)
        //                    {
        //                        list<map<string, string, less<string> > > table = m.getAllData();

        //                        list<map<string, string, less<string> > >::iterator ittab = table.begin();

        //                        cout << endl << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

        //                        cout << "|" << setw(10) << "№" << "|" << setw(20) << "Логин" << "|" << setw(81) << "Пароль" << "|" << setw(20) << "Имя" << "|" << setw(20) << "Фамилия" << "|" << setw(5) << "Admin" << "|" << setw(30) << "Роль" << "|" << endl;

        //                        cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

        //                        while (ittab != table.end())
        //                        {
        //                            cout << "|" << setw(10) << (*ittab)["number"] << "|" << setw(20) << (*ittab)["login"] << "|" << setw(81) << (*ittab)["password"] << "|" << setw(20) << (*ittab)["firstname"] << "|" << setw(20) << (*ittab)["surname"] << "|" << setw(5) << (*ittab)["admin"] << "|" << setw(30) << (*(m.getRole(stoi((*ittab)["role"])))) << "|" << endl;

        //                            ittab++;
        //                        }

        //                        cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

        //                        cout << endl << endl << "Введите что-нибудь для продолжения: ";

        //                        string a;

        //                        cin >> a;
        //                    }
        //                    else if (objectNum == 5)
        //                    {
        //                        list<map<string, string, less<string> > > table = m.getAllDataRoles();

        //                        list<map<string, string, less<string> > >::iterator ittab = table.begin();

        //                        cout << endl << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

        //                        cout << "|" << setw(8) << "№" << "|" << setw(100) << "Описание" << "|" << setw(8) << "Потомки"<< "|" << endl;

        //                        cout << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

        //                        while (ittab != table.end())
        //                        {
        //                            cout << "|" << setw(8) << (*ittab)["role"] << "|" << setw(100) << (*ittab)["description"] << "|" << setw(8) << (*ittab)["descendants"] << "|" << endl;

        //                            ittab++;
        //                        }

        //                        cout << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

        //                        cout << endl << endl << "Введите что-нибудь для продолжения: ";

        //                        string a;

        //                        cin >> a;
        //                    }
        //                    else if (objectNum == 6)
        //                    {
        //                        list<map<string, string, less<string> > > table = m.getAllDataMU();

        //                        list<map<string, string, less<string> > >::iterator ittab = table.begin();

        //                        cout << endl << "+----------------+----------------+--------------------+" << endl;

        //                        cout << "|" << setw(16) << "№ пользователя" << "|" << setw(16) << "№ объекта" << "|" << setw(20) << "Права" << "|" << endl;

        //                        cout << "+----------------+----------------+--------------------+" << endl;

        //                        while (ittab != table.end())
        //                        {
        //                            cout << "|" << setw(16) << (*ittab)["user"] << "|" << setw(16) << (*ittab)["object"] << "|" << setw(20) << (*ittab)["powers"] << "|" << endl;

        //                            ittab++;
        //                        }

        //                        cout << "+----------------+----------------+--------------------+" << endl;

        //                        cout << endl << endl << "Введите что-нибудь для продолжения: ";

        //                        string a;

        //                        cin >> a;
        //                    }
        //                    else if (objectNum == 7)
        //                    {
        //                        list<map<string, string, less<string> > > table = m.getAllDataMR();

        //                        list<map<string, string, less<string> > >::iterator ittab = table.begin();

        //                        cout << endl << "+----------------+----------------+--------------------+" << endl;

        //                        cout << "|" << setw(16) << "№ роли" << "|" << setw(16) << "№ объекта" << "|" << setw(20) << "Права" << "|" << endl;

        //                        cout << "+----------------+----------------+--------------------+" << endl;

        //                        while (ittab != table.end())
        //                        {
        //                            cout << "|" << setw(16) << (*ittab)["role"] << "|" << setw(16) << (*ittab)["object"] << "|" << setw(20) << (*ittab)["powers"] << "|" << endl;

        //                            ittab++;
        //                        }

        //                        cout << "+----------------+----------------+--------------------+" << endl;

        //                        cout << endl << endl << "Введите что-нибудь для продолжения: ";

        //                        string a;

        //                        cin >> a;
        //                    }
        //                    else if (objectNum == 8)
        //                    {
        //                    list<map<string, string, less<string> > > table = m.getAllDataObjects();

        //                    list<map<string, string, less<string> > >::iterator ittab = table.begin();

        //                    cout << endl << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

        //                    cout << "|" << setw(16) << "№" << "|" << setw(100) << "Название объекта" << "|" << endl;

        //                    cout << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

        //                    while (ittab != table.end())
        //                    {
        //                        cout << "|" << setw(16) << (*ittab)["object"] << "|" << setw(100) << (*ittab)["name"] << "|" << endl;

        //                        ittab++;
        //                    }

        //                    cout << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

        //                    cout << endl << endl << "Введите что-нибудь для продолжения: ";

        //                    string a;

        //                    cin >> a;
        //                    }
        //                    else
        //                    {
        //                        try
        //                        {
        //                            m.readObject(objectNum);
        //                        }
        //                        catch (Model::ModelException ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << ex.discription << endl;
        //                        }
        //                        catch (Model::UnauthorizedAccess ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                            cout << "Доступ запрещен!" << endl;
        //                        }
        //                    }

        //                    break;
        //                }
        //                case 2:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    if (objectNum == 4)
        //                    {
        //                        bool exitUPD = false;

        //                        int numberUPD;

        //                        cout << "-----Обновление учетной записи------" << endl;

        //                        while (true)
        //                        {
        //                            cout << "Введите номер сотрудника, данные которого хотите изменить: ";

        //                            cin >> numberUPD;

        //                            if (cin.good() && numberUPD > 0)
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        while (m.getUser(numberUPD) == NULL)
        //                        {
        //                            string yesNo;

        //                            cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
        //                                << "Продолжить обновление(Да/Нет): ";

        //                            cin >> yesNo;

        //                            while (yesNo != "Да" && yesNo != "Нет")
        //                            {
        //                                cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
        //                                    << "Попробуйте еще раз: ";

        //                                cin >> yesNo;
        //                            }

        //                            if (yesNo == "Да")
        //                            {
        //                                cout << "Введите номер сотрудника, данные которого хотите изменить: ";
        //                                cin >> numberUPD;
        //                            }
        //                            else
        //                            {
        //                                exitUPD = true;

        //                                break;
        //                            }
        //                        }

        //                        if (exitUPD)
        //                            break;

        //                        map<string, array<string, 2>, less<string> > columnsUPD;

        //                        while (true)
        //                        {
        //                            unsigned numMenuUPD;

        //                            cout << "Выберите поля для обновления" << endl
        //                                << "1) Логин" << (columnsUPD.contains("login") ? ": указано \"" + columnsUPD["login"][1] + "\";" : ";") << endl
        //                                << "2) Пароль" << (columnsUPD.contains("password") ? ": указано \"" + columnsUPD["password"][1] + "\";" : ";") << endl
        //                                << "3) Имя" << (columnsUPD.contains("firstname") ? ": указано \"" + columnsUPD["firstname"][1] + "\";" : ";") << endl
        //                                << "4) Фамилия" << (columnsUPD.contains("surname") ? ": указано \"" + columnsUPD["surname"][1] + "\";" : ";") << endl
        //                                << "5) Админ" << (columnsUPD.contains("admin") ? ": указано \"" + columnsUPD["admin"][1] + "\";" : ";") << endl
        //                                << "6) Роль" << (columnsUPD.contains("role") ? ": указано \"" + columnsUPD["role"][1] + "\";" : ";") << endl
        //                                << "0) Обновить учетную запись." << endl;

        //                            cout << "Ваш выбор: ";

        //                            cin >> numMenuUPD;

        //                            switch (numMenuUPD)
        //                            {
        //                            case 1:
        //                            {
        //                                string loginUPD;

        //                                cout << "Введите новый логин: ";

        //                                cin >> loginUPD;

        //                                //regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

        //                                //while (!regex_match(loginUPD.begin(), loginUPD.end(), rxl))
        //                                //{
        //                                //    cout << "Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов." << endl
        //                                //        << "Попробуйте ещё раз: ";

        //                                //    cin >> loginUPD;
        //                                //}

        //                                while (m.loginExists(loginUPD))
        //                                {
        //                                    cout << "Данный логин занят." << endl
        //                                        << "Попробуйте еще раз: ";

        //                                    cin >> loginUPD;
        //                                }

        //                                columnsUPD["login"] = { {"=", loginUPD} };

        //                                break;
        //                            }
        //                            case 2:
        //                            {
        //                                string passwordUPD;

        //                                cout << "Введите новый пароль: ";

        //                                cin >> passwordUPD;

        //                                regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };

        //                                while (!regex_match(passwordUPD.begin(), passwordUPD.end(), rx))
        //                                {
        //                                    cout << "Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов." << endl
        //                                        << "Попробуйте ещё раз: ";

        //                                    cin >> passwordUPD;
        //                                }

        //                                columnsUPD["password"] = { {"=", passwordUPD} };

        //                                break;
        //                            }
        //                            case 3:
        //                            {
        //                                string firstnameUPD;

        //                                regex rxfs{ R"([A-Za-zА-Яа-я]{3,})" };

        //                                while (true)
        //                                {
        //                                    cout << "Введите новое имя: ";

        //                                    cin >> firstnameUPD;

        //                                    if (regex_match(firstnameUPD.begin(), firstnameUPD.end(), rxfs))
        //                                    {
        //                                        break;
        //                                    }

        //                                    cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
        //                                }

        //                                columnsUPD["firstname"] = { {"=", firstnameUPD} };

        //                                break;
        //                            }
        //                            case 4:
        //                            {
        //                                string surnameUPD;

        //                                regex rxfs{ R"([A-Za-ZА-Яа-я]{3,})" };

        //                                while (true)
        //                                {
        //                                    cout << "Введите новую фамилию: ";

        //                                    cin >> surnameUPD;

        //                                    if (regex_match(surnameUPD.begin(), surnameUPD.end(), rxfs))
        //                                    {
        //                                        break;
        //                                    }

        //                                    cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
        //                                }

        //                                columnsUPD["surname"] = { {"=", surnameUPD} };

        //                                break;
        //                            }
        //                            case 5:
        //                            {
        //                                string adminUPD;

        //                                cout << "Сделать пользователя админом(Да/Нет): ";

        //                                cin >> adminUPD;

        //                                while (adminUPD != "Да" && adminUPD != "Нет")
        //                                {
        //                                    cout << "Вы ввели некорректные данные. Данное поле принимает значения Да или Нет." << endl
        //                                        << "Попробуйте еще раз: ";

        //                                    cin >> adminUPD;
        //                                }

        //                                if (adminUPD == "Да")
        //                                {
        //                                    columnsUPD["admin"] = { {"=", "true"} };
        //                                }
        //                                else
        //                                {
        //                                    columnsUPD["admin"] = { {"=", "false"} };
        //                                }

        //                                break;
        //                            }
        //                            case 6:
        //                            {
        //                                cout << "Список существующих ролей:" << endl;

        //                                vector<map<string, string, less<string> > > rolesEx = m.getRoles();

        //                                for (int i = 0; i < rolesEx.size(); i++)
        //                                {
        //                                    cout << i + 1 << ") " << rolesEx[i]["description"] << ";" << endl;
        //                                }

        //                                unsigned roleNumUp;

        //                                while (true)
        //                                {
        //                                    cout << "Выберите роль: ";

        //                                    cin >> roleNumUp;

        //                                    if (cin.good() && roleNumUp > 0 && roleNumUp < rolesEx.size() + 1)
        //                                    {
        //                                        cin.ignore(30, '\n');

        //                                        break;
        //                                    }

        //                                    cin.clear();

        //                                    cout << "Вы ввели некорректные данные. Введите число от 1 до " << rolesEx.size() << ". Соответствующее нужному пункту меню." << endl;

        //                                    cin.ignore(30, '\n');
        //                                }

        //                                columnsUPD["role"] = { {"=", rolesEx[roleNumUp - 1]["description"]} };

        //                                break;
        //                            }
        //                            case 0:
        //                                exitUPD = true;

        //                                break;
        //                            default:
        //                                cout << "Вы ввели некорректные данные. Введите число от 0 до 5. Соответствующее нужному пункту меню." << endl;
        //                                break;
        //                            }

        //                            if (exitUPD)
        //                                break;
        //                        }

        //                        cout << "------------------------------------" << endl;

        //                        try
        //                        {
        //                            m.updateUser(numberUPD, columnsUPD);
        //                        }
        //                        catch (Model::ModelException ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << ex.discription << endl;
        //                        }
        //                        catch (exception ex)
        //                        {
        //                            cout << ex.what() << endl;
        //                        }
        //                        catch (...)
        //                        {
        //                            cout << "Произошло исключение" << endl;
        //                        }

        //                        cout << endl << "Блок обновления закончен." << endl;

        //                        Sleep(3000);
        //                    }
        //                    else if (objectNum == 6)
        //                    {
        //                        bool exitUPD = false;

        //                        int numberUser, numberObject;

        //                        string newPowers;

        //                        cout << "-----Обновление таблицы MU------" << endl;

        //                        while (true)
        //                        {
        //                            cout << "Введите номер сотрудника, которому хотите изменить полномочия: ";

        //                            cin >> numberUser;

        //                            if (cin.good() && numberUser > 0)
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        while (m.getUser(numberUser) == NULL)
        //                        {
        //                            string yesNo;

        //                            cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
        //                                << "Продолжить обновление(Да/Нет): ";

        //                            cin >> yesNo;

        //                            while (yesNo != "Да" && yesNo != "Нет")
        //                            {
        //                                cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
        //                                    << "Попробуйте еще раз: ";

        //                                cin >> yesNo;
        //                            }

        //                            if (yesNo == "Да")
        //                            {
        //                                cout << "Введите номер сотрудника, которому хотите изменить полномочия: ";
        //                                cin >> numberUser;
        //                            }
        //                            else
        //                            {
        //                                exitUPD = true;

        //                                break;
        //                            }
        //                        }

        //                        if (exitUPD)
        //                            break;

        //                        while (true)
        //                        {
        //                            cout << "Введите номер объекта, права к которому будут выданы: ";

        //                            cin >> numberObject;

        //                            if (cin.good() && numberObject > 0)
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        while (m.getObject(numberObject) == NULL)
        //                        {
        //                            string yesNo;

        //                            cout << "Объекта с таким номером не существует. Попробовать еще раз?" << endl
        //                                << "Продолжить обновление(Да/Нет): ";

        //                            cin >> yesNo;

        //                            while (yesNo != "Да" && yesNo != "Нет")
        //                            {
        //                                cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
        //                                    << "Попробуйте еще раз: ";

        //                                cin >> yesNo;
        //                            }

        //                            if (yesNo == "Да")
        //                            {
        //                                cout << "Введите номер объекта, права к которому будут выданы: ";
        //                                cin >> numberObject;
        //                            }
        //                            else
        //                            {
        //                                exitUPD = true;

        //                                break;
        //                            }
        //                        }

        //                        if (exitUPD)
        //                            break;

        //                        regex rgpowers{ R"(([rweo]*|-))" };

        //                        while (true)
        //                        {
        //                            cout << "Введите права: ";

        //                            cin >> newPowers;

        //                            if (cin.good() && regex_match(newPowers.begin(), newPowers.end(), rgpowers))
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите строку из прав: r, w, e, o. Или '-' в случае отсутствия прав." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        try
        //                        {
        //                            if (newPowers == "-")
        //                            {
        //                                newPowers = "";
        //                            }

        //                            m.updateMU(numberUser, numberObject, newPowers);
        //                        }
        //                        catch (Model::ModelException ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << ex.discription << endl;
        //                        }
        //                        catch (exception ex)
        //                        {
        //                            cout << ex.what() << endl;
        //                        }
        //                        catch (...)
        //                        {
        //                            cout << "Произошло исключение" << endl;
        //                        }

        //                        cout << endl << "Блок обновления MU закончен." << endl;

        //                        Sleep(3000);

        //                    }
        //                    else if (objectNum == 7)
        //                    {
        //                        bool exitUPD = false;

        //                        int numberUser, numberObject;

        //                        string newPowers;

        //                        cout << "-----Обновление таблицы MR------" << endl;

        //                        while (true)
        //                        {
        //                            cout << "Введите номер роли, которой хотите изменить права: ";

        //                            cin >> numberUser;

        //                            if (cin.good() && numberUser > 0)
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        while (m.getRole(numberUser) == NULL)
        //                        {
        //                            string yesNo;

        //                            cout << "Роли с таким номером не существует. Попробовать еще раз?" << endl
        //                                << "Продолжить обновление(Да/Нет): ";

        //                            cin >> yesNo;

        //                            while (yesNo != "Да" && yesNo != "Нет")
        //                            {
        //                                cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
        //                                    << "Попробуйте еще раз: ";

        //                                cin >> yesNo;
        //                            }

        //                            if (yesNo == "Да")
        //                            {
        //                                cout << "Введите номер роли, которой хотите изменить права: ";
        //                                cin >> numberUser;
        //                            }
        //                            else
        //                            {
        //                                exitUPD = true;

        //                                break;
        //                            }
        //                        }

        //                        if (exitUPD)
        //                            break;

        //                        while (true)
        //                        {
        //                            cout << "Введите номер объекта, права к которому будут выданы: ";

        //                            cin >> numberObject;

        //                            if (cin.good() && numberObject > 0)
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        while (m.getObject(numberObject) == NULL)
        //                        {
        //                            string yesNo;

        //                            cout << "Объекта с таким номером не существует. Попробовать еще раз?" << endl
        //                                << "Продолжить обновление(Да/Нет): ";

        //                            cin >> yesNo;

        //                            while (yesNo != "Да" && yesNo != "Нет")
        //                            {
        //                                cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
        //                                    << "Попробуйте еще раз: ";

        //                                cin >> yesNo;
        //                            }

        //                            if (yesNo == "Да")
        //                            {
        //                                cout << "Введите номер объекта, права к которому будут выданы: ";
        //                                cin >> numberObject;
        //                            }
        //                            else
        //                            {
        //                                exitUPD = true;

        //                                break;
        //                            }
        //                        }

        //                        if (exitUPD)
        //                            break;

        //                        regex rgpowers{ R"([rweo]*)" };

        //                        while (true)
        //                        {
        //                            cout << "Введите права: ";

        //                            cin >> newPowers;

        //                            if (cin.good() && regex_match(newPowers.begin(), newPowers.end(), rgpowers))
        //                            {
        //                                cin.ignore(30, '\n');

        //                                break;
        //                            }

        //                            cin.clear();

        //                            cout << "Вы ввели некорректные данные. Введите строку из прав: r, w, e, o." << endl;

        //                            cin.ignore(30, '\n');
        //                        }

        //                        try
        //                        {
        //                            m.updateMR(numberUser, numberObject, newPowers);
        //                        }
        //                        catch (Model::ModelException ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << ex.discription << endl;
        //                        }
        //                        catch (exception ex)
        //                        {
        //                            cout << ex.what() << endl;
        //                        }
        //                        catch (...)
        //                        {
        //                            cout << "Произошло исключение" << endl;
        //                        }

        //                        cout << endl << "Блок обновления MU закончен." << endl;

        //                        Sleep(3000);

        //                    }
        //                    else
        //                    {
        //                        try
        //                        {
        //                            m.writeObject(objectNum);
        //                        }
        //                        catch (Model::ModelException ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << ex.discription << endl;
        //                        }
        //                        catch (Model::UnauthorizedAccess ex)
        //                        {
        //                            cout << endl << "Произошло исключение" << endl << endl;

        //                            cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                            cout << "Доступ запрещен!" << endl;
        //                        }
        //                    } 

        //                    break;
        //                }
        //                default:
        //                    cout << "Вы ввели некорректные данные." << endl;
        //                    break;
        //                }
        //            }

        //            Sleep(2500);
        //        }
        //        else
        //        {
        //            cout << "Вы ввели некорректные данные. Введите число от 0 до " << objects.size() << ". Соответствующее нужному пункту меню." << endl;
        //            Sleep(2000);
        //            break;
        //        }

        //        system("cls");
        //    }
        //}
        //else
        //{
        //    unsigned numMenu;

        //    vector<map<string, string, less<string> > > objects = m.getObjects();

        //    while (true)
        //    {
        //        cout << "----------------Меню----------------" << endl << endl;

        //        for (int i = 0; i < objects.size(); i++)
        //        {
        //            cout << i + 1 << ") " << objects[i]["name"] << ";" << endl;
        //        }

        //        cout << "0) Выход из программы." << endl << endl;

        //        cout << "------------------------------------" << endl;

        //        while (true)
        //        {
        //            cout << "Ваш выбор: ";

        //            cin >> numMenu;

        //            if (cin.good())
        //            {
        //                cin.ignore(30, '\n');

        //                break;
        //            }

        //            cin.clear();

        //            cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

        //            cin.ignore(30, '\n');
        //        }

        //        if (numMenu == 0)
        //        {
        //            cout << "Пора в отпуск! Всем пока!" << endl;
        //            Sleep(1000);

        //            return 0;
        //        }
        //        else if (numMenu > 0 && numMenu < objects.size() + 1)
        //        {
        //            //cout << "Выполнение действия: " << powers[numMenu - 1]["description"] << endl;

        //            regex rgobj{ R"(.+\.exe)" };

        //            if (regex_match(objects[numMenu - 1]["name"].begin(), objects[numMenu - 1]["name"].end(), rgobj))
        //            {
        //                cout << "1) Выполнить;" << endl << "0) Выход" << endl;

        //                int numMenuFile;

        //                while (true)
        //                {
        //                    cout << "Ваш выбор: ";

        //                    cin >> numMenuFile;

        //                    if (cin.good() && numMenuFile >= 0 && numMenuFile < 2)
        //                    {
        //                        cin.ignore(30, '\n');

        //                        break;
        //                    }

        //                    cin.clear();

        //                    cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;

        //                    cin.ignore(30, '\n');
        //                }

        //                switch (numMenuFile)
        //                {
        //                case 0:
        //                {
        //                    continue;
        //                }
        //                case 1:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    try
        //                    {
        //                        m.executeObject(objectNum);
        //                    }
        //                    catch (Model::ModelException ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << ex.discription << endl;
        //                    }
        //                    catch (Model::UnauthorizedAccess ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                        cout << "Доступ запрещен!" << endl;
        //                    }

        //                    break;
        //                }
        //                default:
        //                    cout << "Вы ввели некорректные данные." << endl;
        //                    break;
        //                }
        //            }
        //            else
        //            {
        //                cout << "1) Прочитать;" << endl 
        //                    << "2) Переписать;" << endl
        //                    << "0) Выход" << endl;

        //                int numMenuFile;

        //                while (true)
        //                {
        //                    cout << "Ваш выбор: ";

        //                    cin >> numMenuFile;

        //                    if (cin.good() && numMenuFile >= 0 && numMenuFile < 3)
        //                    {
        //                        cin.ignore(30, '\n');

        //                        break;
        //                    }

        //                    cin.clear();

        //                    cout << "Вы ввели некорректные данные. Введите число от 0 до 2. Соответствующее нужному пункту меню." << endl;

        //                    cin.ignore(30, '\n');
        //                }

        //                switch (numMenuFile)
        //                {
        //                case 0:
        //                {
        //                    continue;
        //                }
        //                case 1:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    try
        //                    {
        //                        m.readObject(objectNum);
        //                    }
        //                    catch (Model::ModelException ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << ex.discription << endl;
        //                    }
        //                    catch (Model::UnauthorizedAccess ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                        cout << "Доступ запрещен!" << endl;
        //                    }

        //                    break;
        //                }
        //                case 2:
        //                {
        //                    int objectNum = stoi(objects[numMenu - 1]["object"]);

        //                    try
        //                    {
        //                        m.writeObject(objectNum);
        //                    }
        //                    catch (Model::ModelException ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << ex.discription << endl;
        //                    }
        //                    catch (Model::UnauthorizedAccess ex)
        //                    {
        //                        cout << endl << "Произошло исключение" << endl << endl;

        //                        cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;

        //                        cout << "Доступ запрещен!" << endl;
        //                    }

        //                    break;
        //                }
        //                default:
        //                    cout << "Вы ввели некорректные данные." << endl;
        //                    break;
        //                }
        //            }

        //            Sleep(2500);
        //        }
        //        else
        //        {
        //            cout << "Вы ввели некорректные данные. Введите число от 0 до " << objects.size() << ". Соответствующее нужному пункту меню." << endl;
        //            Sleep(2000);
        //            break;
        //        }

        //        system("cls");
        //    }
        //}

    }
    catch (Model::AccessBlockedException)
    {
        cout << "Вы израсходовали все попытки для входа." << endl;

        exit(1);
    }
    catch (Model::ModelException ex)
    {
        cout << endl << "Произошло исключение" << endl << endl;

        cout << ex.discription << endl;
    }
    catch (Model::UnauthorizedAccess ex)
    {
        cout << endl << "Произошло исключение" << endl << endl;

        cout << "Пользователь: " << ex.userName << " совершил попытку не санкционированного доступа " << ex.action << "." << endl;
    }
    catch (Model::DateException ex)
    {
        cout << static_cast<unsigned>(ex.data.day()) << " " << static_cast<unsigned>(ex.data.month())
            << " " << static_cast<int>(ex.data.year()) << " " << ex.discription << endl;
    }
    catch (SQL::ListOfTablesFileException ex)
    {
        cout << "Произошло исключение. Ошибка с файлом, хранящим список таблиц. Причина ошибки " << ex.discription << endl;
    }
    catch (SQL::TableException ex)
    {
        cout << "Произошло исключение. Ошибка с файлом, хранящим таблицу " << ex.tableName << ". Причина ошибки " << ex.discription << endl;
    }
    catch (SQL::InsertException ex)
    {
        cout << ex.discription << endl;
    }
    catch (SQL::TypeException ex)
    {
        cout << ex.expectedType << " " << ex.passedValue << endl;
    }
    catch (exception ex)
    {
        cout << ex.what() << endl;
    }
    catch (...)
    {
        cout << endl << "Произошло исключение. Какое? Сам разбирайся!" << endl;
    }
}
