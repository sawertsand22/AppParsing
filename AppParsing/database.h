#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <chrono>
#include <ctime>
#include <iomanip>
namespace Ui {
class DataBase;
}

class DataBase : public QWidget
{
    Q_OBJECT

//   sql::mysql::MySQL_Driver *driver;
//  sql::Connection *con;
//   sql::ResultSet *res;
//
//
//     sql::Statement *stmt = con->createStatement();


public:
    explicit DataBase(QWidget *parent = nullptr);
    ~DataBase();
 // sql::mysql::MySQL_Driver *driver;
 // sql::Connection *con;
 // sql::Statement *stmt;
    sql::mysql::MySQL_Driver *driver;
     sql::Connection *con;

     void connectToDatabase() {
            // Подключаемся к базе данных
            con = driver->connect("tcp://127.0.0.1/Urls", "root", "root");
            con->setSchema("Urls");
        }
     sql::ResultSet* executeQuery(const std::string& query) {
           // Выполняем SQL-запрос и возвращаем результат
           sql::Statement *stmt = con->createStatement();
           sql::ResultSet *res = stmt->executeQuery(query);
           return res;
       }
   void  execute(const std::string& query) {
           // Выполняем SQL-запрос и возвращаем результат
           sql::Statement *stmt;
           stmt= con->createStatement();
            stmt->execute(query);

     }
     void closeConnection() {
         // Закрываем соединение с базой данных
         con->close();
     }

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_DataBase_destroyed();

    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked(bool checked);

    void on_pushButton_4_clicked();

private:
    Ui::DataBase *ui;
};

#endif // DATABASE_H
