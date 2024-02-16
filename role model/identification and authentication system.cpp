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

            Sleep(3000);
        }
        else
        {
            cout << "В ходе аутентификации прошли непредвиденные шоколадки." << endl;

            return -1;
        }

        system("cls");

        if (m.isAdmin())
        {
            unsigned numMenu;

            while (true)
            {
                cout << "----------------Меню----------------" << endl << endl;

                cout << "1) База данных;" << endl << "2) Добавить пользователя;" << endl 
                    << "3) Изменить учетную запись;" << endl << "4) Аудит;" << endl
                    << "5) Удалить пользователя;" << endl << "0) Выход из программы." << endl << endl;

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

                    cout << "Вы ввели некорректные данные. Введите число от 0 до 5. Соответствующее нужному пункту меню." << endl;

                    cin.ignore(30, '\n');
                }

                switch (numMenu)
                {
                case 1:
                {
                    list<map<string, string, less<string> > > table = m.getAllData();

                    list<map<string, string, less<string> > >::iterator ittab = table.begin();

                    cout << endl << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+" << endl;

                    cout << "|" << setw(10) << "№" << "|" << setw(20) << "Логин" << "|" << setw(81) << "Пароль" << "|" << setw(20) << "Имя" << "|" << setw(20) << "Фамилия" << "|" << setw(5) << "Admin" << "|" << endl;

                    cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+" << endl;

                    while (ittab != table.end())
                    {
                        cout << "|" << setw(10) << (*ittab)["number"] << "|" << setw(20) << (*ittab)["login"] << "|" << setw(81) << (*ittab)["password"] << "|" << setw(20) << (*ittab)["firstname"] << "|" << setw(20) << (*ittab)["surname"] << "|" << setw(5) << (*ittab)["admin"] << "|" << endl;
            
                        ittab++;
                    }

                    cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+" << endl;

                    cout << endl << endl << "Введите что-нибудь для продолжения: ";
                    
                    string a;

                    cin >> a;

                    break;
                }
                case 2:
                {
                    string loginNU, passwordNU, firstnameNU, surnameNU, adminNU;
                    int numberNU;
                    bool adminNUB;

                    cout << "----Создание нового пользователя----" << endl
                        << "Заполните поля пользователя" << endl << "Логин: ";

                    cin >> loginNU;

                    //regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

                    //while (!regex_match(loginNU.begin(), loginNU.end(), rxl))
                    //{
                    //    cout << "Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов." << endl
                    //        << "Попробуйте ещё раз: ";

                    //    cin >> loginNU;
                    //}

                    map<string, array<string, 2>, less<string> > cwhereNU;

                    cwhereNU["login"] = { {"=", loginNU} };

                    while (m.getUsers(cwhereNU).size() != 0)
                    {
                        cout << "Данный логин занят. Выбирете другой:  ";

                        cin >> loginNU;

                        cwhereNU["login"] = { {"=", loginNU} };
                    }

                    cout << "Пароль: ";

                    cin >> passwordNU;

                    regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };

                    while (!regex_match(passwordNU.begin(), passwordNU.end(), rx))
                    {
                        cout << "Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов." << endl
                            << "Попробуйте ещё раз: ";

                        cin >> passwordNU;
                    }

                    regex rxfs{ R"([A-Za-zА-Яа-я]{3,})" };

                    while (true)
                    {
                        cout << "Имя: ";

                        cin >> firstnameNU;

                        if (regex_match(firstnameNU.begin(), firstnameNU.end(), rxfs))
                        {
                            break;
                        }

                        cout << "Имя может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
                    }
                    
                    while (true)
                    {
                        cout << "Фамилия: ";

                        cin >> surnameNU;

                        if (regex_match(firstnameNU.begin(), firstnameNU.end(), rxfs))
                        {
                            break;
                        }

                        cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
                    }

                    while (true)
                    {
                        cout << "Номер: ";

                        cin >> numberNU;

                        if (cin.good() && numberNU > 0)
                        {
                            cin.ignore(30, '\n');

                            break;
                        }

                        cin.clear();

                        cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

                        cin.ignore(30, '\n');
                    }

                    while (m.getUser(numberNU) != NULL)
                    {
                        cout << "Данный номер занят. Выбирете другой:  ";

                        cin >> numberNU;
                    }

                    cout << "Админ(Да/Нет): ";

                    cin >> adminNU;

                    while (adminNU != "Да" && adminNU != "Нет")
                    {
                        cout << "Вы ввели некорректные данные. Данное поле принимает значения Да или Нет." << endl
                            << "Попробуйте еще раз: ";

                        cin >> adminNU;
                    }

                    if (adminNU == "Да")
                    {
                        adminNUB = true;
                    }
                    else
                    {
                        adminNUB = false;
                    }

                    cout << "------------------------------------" << endl;

                    bool res = m.addUser(loginNU, passwordNU, firstnameNU, surnameNU, numberNU, adminNUB);

                    if (res)
                    {
                        cout << "Пользователь успешно добавлен." << endl;
                        Sleep(1000);
                    }
                    else
                    {
                        cout << "При добавлении пользователя произошла неизвестная ошибка." << endl << endl 
                            << "Введите что-нибудь для продолжения: ";

                        string a;

                        cin >> a;
                    }
                    
                    break;
                }
                case 3:
                {
                    bool exitUPD = false;

                    int numberUPD;

                    cout << "-----Обновление учетной записи------" << endl;

                    while (true)
                    {
                        cout << "Введите номер сотрудника, данные которого хотите изменить: ";

                        cin >> numberUPD;

                        if (cin.good() && numberUPD > 0)
                        {
                            cin.ignore(30, '\n');

                            break;
                        }

                        cin.clear();

                        cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

                        cin.ignore(30, '\n');
                    }

                    while (m.getUser(numberUPD) == NULL)
                    {
                        string yesNo;

                        cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
                            << "Продолжить обновление(Да/Нет): ";

                        cin >> yesNo;

                        while (yesNo != "Да" && yesNo != "Нет")
                        {
                            cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
                                << "Попробуйте еще раз: ";

                            cin >> yesNo;
                        }

                        if (yesNo == "Да")
                        {
                            cout << "Введите номер сотрудника, данные которого хотите изменить: ";
                            cin >> numberUPD;
                        }
                        else
                        {
                            exitUPD = true;

                            break;
                        }                        
                    }

                    if (exitUPD)
                        break;

                    map<string, array<string, 2>, less<string> > columnsUPD;

                    while (true)
                    {
                        unsigned numMenuUPD;

                        cout << "Выберите поля для обновления" << endl
                            << "1) Логин" << (columnsUPD.contains("login") ? ": указано \"" + columnsUPD["login"][1] + "\";" : ";") << endl
                            << "2) Пароль" << (columnsUPD.contains("password") ? ": указано \"" + columnsUPD["password"][1] + "\";" : ";") << endl
                            << "3) Имя" << (columnsUPD.contains("firstname") ? ": указано \"" + columnsUPD["firstname"][1] + "\";" : ";") << endl
                            << "4) Фамилия" << (columnsUPD.contains("surname") ? ": указано \"" + columnsUPD["surname"][1] + "\";" : ";") << endl
                            << "5) Админ" << (columnsUPD.contains("admin") ? ": указано \"" + columnsUPD["admin"][1] + "\";" : ";") << endl
                            << "0) Обновить учетную запись." << endl;

                        cout << "Ваш выбор: ";

                        cin >> numMenuUPD;

                        switch (numMenuUPD)
                        {
                        case 1:
                        {
                            string loginUPD;

                            cout << "Введите новый логин: ";

                            cin >> loginUPD;

                            //regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

                            //while (!regex_match(loginUPD.begin(), loginUPD.end(), rxl))
                            //{
                            //    cout << "Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов." << endl
                            //        << "Попробуйте ещё раз: ";

                            //    cin >> loginUPD;
                            //}

                            while (m.loginExists(loginUPD))
                            {
                                cout << "Данный логин занят." << endl
                                    << "Попробуйте еще раз: ";

                                cin >> loginUPD;
                            }

                            columnsUPD["login"] = { {"=", loginUPD} };

                            break;
                        }
                        case 2:
                        {
                            string passwordUPD;

                            cout << "Введите новый пароль: ";

                            cin >> passwordUPD;

                            regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };

                            while (!regex_match(passwordUPD.begin(), passwordUPD.end(), rx))
                            {
                                cout << "Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов." << endl
                                    << "Попробуйте ещё раз: ";

                                cin >> passwordUPD;
                            }

                            columnsUPD["password"] = { {"=", passwordUPD} };

                            break;
                        }
                        case 3:
                        {
                            string firstnameUPD;

                            regex rxfs{ R"([A-Za-zА-Яа-я]{3,})" };

                            while (true)
                            {
                                cout << "Введите новое имя: ";

                                cin >> firstnameUPD;

                                if (regex_match(firstnameUPD.begin(), firstnameUPD.end(), rxfs))
                                {
                                    break;
                                }

                                cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
                            }

                            columnsUPD["firstname"] = { {"=", firstnameUPD} };

                            break;
                        }
                        case 4:
                        {
                            string surnameUPD;

                            regex rxfs{ R"([A-Za-ZА-Яа-я]{3,})" };

                            while (true)
                            {
                                cout << "Введите новую фамилию: ";

                                cin >> surnameUPD;

                                if (regex_match(surnameUPD.begin(), surnameUPD.end(), rxfs))
                                {
                                    break;
                                }

                                cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
                            }

                            columnsUPD["surname"] = { {"=", surnameUPD} };

                            break;
                        }
                        case 5:
                        {
                            string adminUPD;

                            cout << "Сделать пользователя админом(Да/Нет): ";

                            cin >> adminUPD;

                            while (adminUPD != "Да" && adminUPD != "Нет")
                            {
                                cout << "Вы ввели некорректные данные. Данное поле принимает значения Да или Нет." << endl
                                    << "Попробуйте еще раз: ";

                                cin >> adminUPD;
                            }

                            if (adminUPD == "Да")
                            {
                                columnsUPD["admin"] = { {"=", "true"} };
                            }
                            else
                            {
                                columnsUPD["admin"] = { {"=", "false"} };
                            }

                            break;
                        }
                        case 0:
                            exitUPD = true;

                            break;
                        default:
                            cout << "Вы ввели некорректные данные. Введите число от 0 до 5. Соответствующее нужному пункту меню." << endl;
                            break;
                        }

                        if (exitUPD)
                            break;
                    }

                    cout << "------------------------------------" << endl;

                    m.updateUser(numberUPD, columnsUPD);

                    cout << "Данные успешно обновлены." << endl;

                    Sleep(1000);

                    break;
                }
                case 4:
                {
                    
                    cout << "----------------Аудит---------------" << endl;

                    unsigned dayBegin, dayEnd, monthBegin, monthEnd, yearBegin, yearEnd;

                    cout << "Введите дату начала отсчета" << endl
                        << "День: ";

                    cin >> dayBegin;

                    while (dayBegin < 1 || dayBegin > 31)
                    {
                        cout << "Значение дня должно находиться интервале от 1 до 31." << endl
                            << "Попробуйте еще раз: ";

                        cin >> dayBegin;
                    }

                    cout << "Месяц: ";

                    cin >> monthBegin;

                    while (monthBegin < 1 || monthBegin > 12)
                    {
                        cout << "Значение месяца должно находиться интервале от 1 до 12." << endl
                            << "Попробуйте еще раз: ";

                        cin >> monthBegin;
                    }

                    cout << "Год: ";

                    cin >> yearBegin;

                    const chrono::time_point now{ chrono::system_clock::now() };

                    const chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };

                    int thisYear = static_cast<int>(ymd.year());

                    while (yearBegin < 1970 || yearBegin > thisYear)
                    {

                        cout << "Значение года должно находиться интервале от 1970 до " << thisYear  << "." << endl
                            << "Попробуйте еще раз: ";

                        cin >> yearBegin;
                    }

                    chrono::year_month_day *beginData = new chrono::year_month_day{ chrono::year(yearBegin), chrono::month(monthBegin), chrono::day(dayBegin) };

                    while (!(*beginData).ok())
                    {
                        cout << dayBegin << "." << monthBegin << "." << yearBegin << " не представляет действительную дату." << endl
                            << "Попробуйте ввести дату еще раз." << endl;

                        cout << "Введите дату начала отсчета" << endl
                            << "День: ";

                        cin >> dayBegin;

                        while (dayBegin < 1 || dayBegin > 31)
                        {
                            cout << "Значение дня должно находиться интервале от 1 до 31." << endl
                                << "Попробуйте еще раз: ";

                            cin >> dayBegin;
                        }

                        cout << "Месяц: ";

                        cin >> monthBegin;

                        while (monthBegin < 1 || monthBegin > 12)
                        {
                            cout << "Значение месяца должно находиться интервале от 1 до 12." << endl
                                << "Попробуйте еще раз: ";

                            cin >> monthBegin;
                        }

                        cout << "Год: ";

                        cin >> yearBegin;

                        while (yearBegin < 1970 || yearBegin > thisYear)
                        {

                            cout << "Значение года должно находиться интервале от 1970 до " << thisYear << "." << endl
                                << "Попробуйте еще раз: ";

                            cin >> yearBegin;
                        }

                        delete beginData;

                        beginData = new chrono::year_month_day{ chrono::year(yearBegin), chrono::month(monthBegin), chrono::day(dayBegin) };
                    }

                    cout << "Введите дату окончания отсчета" << endl
                        << "День: ";

                    cin >> dayEnd;

                    while (dayEnd < 1 || dayEnd > 31)
                    {
                        cout << "Значение дня должно находиться интервале от 1 до 31." << endl
                            << "Попробуйте еще раз: ";

                        cin >> dayEnd;
                    }

                    cout << "Месяц: ";

                    cin >> monthEnd;

                    while (monthEnd < 1 || monthEnd > 12)
                    {
                        cout << "Значение месяца должно находиться интервале от 1 до 12." << endl
                            << "Попробуйте еще раз: ";

                        cin >> monthEnd;
                    }

                    cout << "Год: ";

                    cin >> yearEnd;

                    while (yearEnd < 1970 || yearEnd > thisYear)
                    {

                        cout << "Значение года должно находиться интервале от 1970 до " << thisYear << "." << endl
                            << "Попробуйте еще раз: ";

                        cin >> yearEnd;
                    }

                    chrono::year_month_day *endData = new chrono::year_month_day{ chrono::year(yearEnd), chrono::month(monthEnd), chrono::day(dayEnd) };

                    while (!(*endData).ok())
                    {
                        cout << dayEnd << "." << monthEnd << "." << yearEnd << " не представляет действительную дату." << endl
                            << "Попробуйте ввести дату еще раз." << endl;

                        cout << "Введите дату начала отсчета" << endl
                            << "День: ";

                        cin >> dayEnd;

                        while (dayEnd < 1 || dayEnd > 31)
                        {
                            cout << "Значение дня должно находиться интервале от 1 до 31." << endl
                                << "Попробуйте еще раз: ";

                            cin >> dayEnd;
                        }

                        cout << "Месяц: ";

                        cin >> monthEnd;

                        while (monthEnd < 1 || monthEnd > 12)
                        {
                            cout << "Значение месяца должно находиться интервале от 1 до 12." << endl
                                << "Попробуйте еще раз: ";

                            cin >> monthEnd;
                        }

                        cout << "Год: ";

                        cin >> yearEnd;

                        while (yearEnd < 1970 || yearEnd > thisYear)
                        {

                            cout << "Значение года должно находиться интервале от 1970 до " << thisYear << "." << endl
                                << "Попробуйте еще раз: ";

                            cin >> yearEnd;
                        }

                        delete beginData;

                        endData = new chrono::year_month_day{ chrono::year(yearEnd), chrono::month(monthEnd), chrono::day(dayEnd) };
                    }

                    multimap<unsigned, Person*, less<unsigned> > auditdata = m.audit(*beginData, *endData);

                    multimap<unsigned, Person*, less<unsigned> >::iterator iterad = auditdata.begin();

                    cout << endl << "----------Результаты аудита---------" << endl << endl
                         << "+----------+--------------------+--------------------+-----+---------------+" << endl
                         << "|" << setw(10) << "№" << "|" << setw(20) << "Имя" << "|" << setw(20) << "Фамилия" << "|" << setw(5) << "Admin" << "|" << setw(15) << "Кол-во входов" << "|" << endl
                         << "+----------+--------------------+--------------------+-----+---------------+" << endl;

                    while (iterad != auditdata.end())
                    {
                        Employee *e = dynamic_cast<Employee*>(iterad->second);

                        cout << "|" << setw(10) << e->getNumber() << "|" << setw(20) << e->getFirstname() << "|" << setw(20) << e->getSurname() << "|" << setw(5) << (Model::isAdmin(e)?"+":"-") << "|" << setw(15) << iterad->first << "|" << endl;

                        iterad++;
                    }                    
                    
                    cout << "+----------+--------------------+--------------------+-----+---------------+" << endl;

                    cout << endl << "Введите что-нибудь для продолжения: ";

                    string a;

                    cin >> a;

                    delete beginData;
                    delete endData;

                    break;
                }
                case 5:
                {
                    bool exitD = false;

                    int numberD;

                    cout << "--------Удаление пользователя-------" << endl;

                    while (true)
                    {
                        cout << "Введите номер сотрудника, данные которого хотите удалить: ";

                        cin >> numberD;

                        if (cin.good() && numberD > 0)
                        {
                            cin.ignore(30, '\n');

                            break;
                        }

                        cin.clear();

                        cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

                        cin.ignore(30, '\n');
                    }

                    while (m.getUser(numberD) == NULL)
                    {
                        string yesNo;

                        cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
                            << "Продолжить удаление(Да/Нет): ";

                        cin >> yesNo;

                        while (yesNo != "Да" && yesNo != "Нет")
                        {
                            cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
                                << "Попробуйте еще раз: ";

                            cin >> yesNo;
                        }

                        if (yesNo == "Да")
                        {
                            cout << "Введите номер сотрудника, данные которого хотите удалить: ";
                            cin >> numberD;
                        }
                        else
                        {
                            exitD = true;

                            break;
                        }
                    }

                    if (exitD)
                        break;

                    cout << "------------------------------------" << endl;

                    if (m.deleteUser(numberD))
                    {
                        cout << "Пользователь успешно удалён." << endl;
                        Sleep(1000);
                    }
                    else
                    {
                        cout << "В ходе удаления произошла ошибка." << endl;
                        Sleep(5000);
                    }

                    break;
                }
                case 0:
                    cout << "Пора в отпуск! Всем пока!" << endl;
                    Sleep(1000);

                    return 0;
                default:
                    cout << "Вы ввели некорректные данные. Введите число от 0 до 5. Соответствующее нужному пункту меню." << endl;
                    Sleep(2000);
                    
                    break;
                }

                system("cls");
            }
        }
        else
        {
            unsigned numMenu;

            while (true)
            {
                cout << "----------------Меню----------------" << endl << endl;

                cout << "1) Работать;" << endl << "0) Выход из программы." << endl << endl;

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

                switch (numMenu)
                {
                case 1:
                    cout << "Работаю я!" << endl;
                    Sleep(1000);
                    break;
                case 0:
                    cout << "Пора в отпуск! Всем пока!" << endl;
                    Sleep(1000);

                    return 0;
                default:
                    cout << "Вы ввели некорректные данные. Введите число от 0 до 1. Соответствующее нужному пункту меню." << endl;
                    Sleep(2000);
                    break;
                }

                system("cls");
            }
        }

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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
