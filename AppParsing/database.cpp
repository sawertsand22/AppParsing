#include "database.h"
#include "ui_database.h"
#include "qmessagebox.h"
#include <qstring.h>
#include <qinputdialog.h>
#include <qtextbrowser.h>
#include <string>
#include <QtSql/QSql>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <curl/curl.h>
#include <unordered_set>
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
#include <QDesktopServices>
#include <QUrl>
#include <QtWebKit/QtWebKit>

std::string base64_encode(const std::string &s)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i=0,ix=0,leng = s.length();
    std::stringstream q;

    for(i=0,ix=leng - leng%3; i<ix; i+=3)
    {
        q<< base64_chars[ (s[i] & 0xfc) >> 2 ];
        q<< base64_chars[ ((s[i] & 0x03) << 4) + ((s[i+1] & 0xf0) >> 4)  ];
        q<< base64_chars[ ((s[i+1] & 0x0f) << 2) + ((s[i+2] & 0xc0) >> 6)  ];
        q<< base64_chars[ s[i+2] & 0x3f ];
    }
    if (ix<leng)
    {
        q<< base64_chars[ (s[ix] & 0xfc) >> 2 ];
        q<< base64_chars[ ((s[ix] & 0x03) << 4) + (ix+1<leng ? (s[ix+1] & 0xf0) >> 4 : 0)];
        q<< (ix+1<leng ? base64_chars[ ((s[ix+1] & 0x0f) << 2) ] : '=');
        q<< '=';
    }
    return q.str();
}

static std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    int val=0, valb=-8;
    for (uchar c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}



static size_t write_data(void *content,size_t size,size_t  nmemb, FILE *stream)
{
    size_t written= fwrite(content,size,nmemb,stream);
    return written;

}

void DownloadFile(const char* url, const char* fname)
{
    CURL *curl;
        FILE *fp;
        CURLcode res;
        curl = curl_easy_init();
        if (curl){
            fp = fopen(fname, "wb");
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);
        }
}
void replaceLinkInFile(const std::string& filePath, const std::string& oldLink, const std::string& newLink) {
    std::ifstream file(filePath);
    std::stringstream buffer;


    buffer << file.rdbuf();
    std::string fileContent = buffer.str();


    size_t pos = fileContent.find(oldLink);
    if (pos != std::string::npos) {
        fileContent.replace(pos, oldLink.size(), newLink);
    }


    file.close();


    std::ofstream outFile(filePath);

    outFile << fileContent;

    outFile.close();
}












DataBase::DataBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBase)
{
    ui->setupUi(this);
  //  ui->comboBox->addItem("Evbla");


    driver = sql::mysql::get_mysql_driver_instance();
    connectToDatabase();    // sql::mysql::MySQL_Driver *driver;
//sql::Connection *con;
// sql::ResultSet *res;
//       sql::ResultSet *res;
//  driver = sql::mysql::get_mysql_driver_instance();
//
//
//  con.reset(driver->connect("tcp://127.0.0.1/Urls", "root", "root"));
//   //sql::Statement *stmt = con->createStatement();
//   stmt.reset(con->createStatement());
//   stmt->execute("USE Urls");
//    std::time_t current_time = std::time(nullptr);
//     std::tm* datetime = std::localtime(&current_time);
 //    std::ostringstream datetime_stream;
 //    datetime_stream << std::put_time(datetime, "%Y-%m-%d %H:%M:%S");
//     std::string datetime_mysql = datetime_stream.str();
//std::cout << "Текущая дата и время: " << datetime_mysql << std::endl;
 //   std::string result;
  //  std::string proverka ="SELECT EXISTS (SELECT * FROM category WHERE categoryname = '"+fild3+"')";
 //   reso = stmt->executeQuery(proverka);

  //   bool isAdmin = reso;
     //   std::cout<<"have this category: "<<getool(reso)<<std::endl;


  //    std::string category_ ="insert into category (categoryname,datechange) values ('"+fild3+"','"+datetime_mysql+"') ON DUPLICATE KEY UPDATE "+"datechange = '"+datetime_mysql+"'";
   //   stmt->execute(category_);




     //    executeQuery("SELECT categoryname FROM category");
  //res = stmt->executeQuery("SELECT * FROM category where categoryname = 'sawert'");
         // Считывание результатов запроса в переменную
     sql::ResultSet *res = executeQuery("SELECT categoryname FROM category");
         std::string result;
          QString q ="";
         while(res->next()) {
             result = res->getString("categoryname");

             QString qstr = QString::fromStdString(result);
              ui->textBrowser->setText(q);
              result+= '\n';
             q+=qstr;

           ui->comboBox->addItem(qstr);
         }

   //      delete stmt;
   //      delete con;
     //    delete res;
  //
closeConnection();


  //







}




DataBase::~DataBase()
{
 delete ui;
}

void DataBase::on_pushButton_clicked()
{
    connectToDatabase();
    QString link = QInputDialog::getText(nullptr, "Ввод данных", "Введите URL:", QLineEdit::Normal, "");
    QString Folder = QInputDialog::getText(nullptr, "Ввод данных", "Введите Папку:", QLineEdit::Normal, "");
    QString Category = QInputDialog::getText(nullptr, "Ввод данных", "Введите Категорию:", QLineEdit::Normal, "");
    ui->comboBox->addItem(Category);
    ui->comboBox->itemData(ui->comboBox->currentIndex());
    std::string uurl = link.toStdString();
    std::cout<<uurl<<std::endl;
    std::string folderPath = Folder.toStdString();
    std::string fild2=folderPath;
    std::string fild3 = Category.toStdString();
std::cout << "Category: " << fild3 << std::endl;
 std::string qurl = uurl;

    std::time_t current_time = std::time(nullptr);
     std::tm* datetime = std::localtime(&current_time);
     std::ostringstream datetime_stream;
     datetime_stream << std::put_time(datetime, "%Y-%m-%d %H:%M:%S");
     std::string datetime_mysql = datetime_stream.str();
std::cout << "Текущая дата и время: " << datetime_mysql << std::endl;
 //   std::string proverka ="SELECT EXISTS (SELECT * FROM category WHERE categoryname = '"+fild3+"')";
 //   reso = stmt->executeQuery(proverka);
//sql::ResultSet *res = executeQuery(proverka);
   //  bool isAdmin = reso;
   //   std::cout<<"have this category: "<<getool(reso)<<std::endl;


    std::string query = "insert into category (categoryname,datechange) values ('"+fild3+"','"+datetime_mysql+"') ON DUPLICATE KEY UPDATE "+"datechange = '"+datetime_mysql+"'";
//std::string query = "insert into category (categoryname) values ('pita')";
    std::cout<<query<<std::endl;
    sql::Statement* stmt = con->createStatement();
   stmt->execute(query);

  // execute(category_);

CURL *curl;
FILE *file = fopen("index.html","wb");
std::string getcontent;
CURLcode response;
CURLcode res;
std::string str_response;
curl=curl_easy_init();
curl_easy_setopt(curl,CURLOPT_URL,uurl.c_str());
curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
response = curl_easy_perform(curl);


res = curl_easy_perform(curl);
if (res!= CURLE_OK)
{
    std::cerr << " failed: " << curl_easy_strerror(res) << std::endl;
}
else
{
    std::cout<<"file opened"<<std::endl;
}

   // Создание папки, если она не существует
   #ifdef _WIN32
       std::string command = "mkdir " + folderPath;
   #else
       std::string command = "mkdir -p " + folderPath;
   #endif
   system(command.c_str());

 std::ifstream fedit;
 fedit.open("index.html");
 if(!fedit.is_open())
 {
     std::cout<<"err: file not opened"<<std::endl;
 }
 else {





     int i=0;
     std::regex linkRegex(R"(\s+(?:[^>]*?\s+)?href=(["'])(.*?)\1)");
     std::regex linkRegex2(R"(\s+(?:[^>]*?\s+)?src=(["'])(.*?)\1)");

     std::string line;
     int lineNumber = 1;
     while (std::getline(fedit, line)) {
         std::smatch match;

         while (  std::regex_search(line, match, linkRegex2)) {
             i++;
             std::cout << "Ссылка найдена на строке " << lineNumber << ": " << match[0] << std::endl;
             line = match.suffix().str();

             std:: string naming;


             auto str = match[2];
             std::cout<<str<<" "<<std::endl;
             std::string po = match[2].str();
             auto poss = po.find_first_of(":");
             auto possq = po.find_first_of("/");

            if(poss>possq || poss>1000)
            {
                 naming=qurl+"/"+std::string(match[2]);
             std::cout<<"link = "<<naming << std::endl;
             }
             else
                 naming=match[2].str();

             const std::string empty;
             auto pos = naming.find_last_of(".");
              auto posq =naming.find_last_of("/");
             std::string sbs = naming.substr(pos+1);
              std::string fq = std::string ("./")+folderPath+"/"+"file_" +std::to_string(i)+"."+naming.substr(pos+1);






         if(naming.length()>0 &&   pos>posq && posq!=0)

              {
                  std:: cout<<"name file:  "<<fq<<std::endl<<pos<<" "<<posq<<std::endl;
              DownloadFile(naming.c_str(), fq.c_str());
              replaceLinkInFile("index.html", match[2], fq);
              }

         }




         while (  std::regex_search(line, match, linkRegex)) {
             i++;
             std::cout << "Ссылка найдена на строке " << lineNumber << ": " << match[0] << std::endl;
             line = match.suffix().str();
             std:: string naming;

             auto str = match[2];
             std::cout<<str<<" "<<std::endl;
             std::string po = match[2].str();
             auto poss = po.find_first_of(":");
             auto possq = po.find_first_of("/");

            if(poss>possq || poss>1000)
            {
                 naming=qurl+"/"+std::string(match[2]);
             std::cout<<"link = "<<naming << std::endl;
             }
             else
                 naming=match[2].str();

             const std::string empty;
             auto pos = naming.find_last_of(".");
              auto posq =naming.find_last_of("/");
             std::string sbs = naming.substr(pos+1);
              std::string fq = std::string ("./")+folderPath+"/"+"file_" +std::to_string(i)+"."+naming.substr(pos+1);




         if(naming.length()>0 &&   pos>posq && posq!=0)

              {
                  std:: cout<<"name file:  "<<fq<<std::endl<<pos<<" "<<posq<<std::endl;
              DownloadFile(naming.c_str(), fq.c_str());
              replaceLinkInFile("index.html", match[2], fq);
              }

         }













         lineNumber++;

}


  fedit.close();







}
curl_easy_cleanup(curl);
   std::time_t current_time1 = std::time(nullptr);

    // Преобразование в формат datetime MySQL
    std::tm* datetime1 = std::localtime(&current_time1);
    std::ostringstream datetime_stream1;
    datetime_stream1 << std::put_time(datetime1, "%Y-%m-%d %H:%M:%S");
    std::string datetime_mysql1 = datetime_stream1.str();
std::cout << "Текущая дата и время: " << datetime_mysql1 << std::endl;



      std::ifstream fin("index.html");

      std::string strh;
      std::string str1;

      while(!fin.eof()){
      std:: getline(fin, strh);
      str1 += strh;
      if (!fin.eof()){
          str1 += '\n';
      }
      }
      fin.close();



    std::string links_ = "insert into links (idcategory,name,context,datechange) values ((SELECT idcategory FROM category  where categoryname = '"+fild3+"' ORDER BY idcategory DESC limit 1),'"+fild2+"','"+base64_encode(str1)+"','"+datetime_mysql1+"')";
      stmt->execute(links_);

delete stmt;
closeConnection();










}








void DataBase::on_comboBox_currentIndexChanged(const QString &arg1)
{  // con.reset(driver->connect("tcp://127.0.0.1/Urls", "root", "root"));
    //sql::Statement *stmt = con->createStatement();
  //  stmt.reset(con->createStatement());
   // stmt->execute("USE Urls");
  //  stmt.reset(con->createStatement());
  //  stmt->execute("USE Urls");
          //  ui->textBrowser->setText();

//      //   ui->comboBox->addItem(qstr);
//

//delete resp;
}


void DataBase::on_DataBase_destroyed()
{
  // delete stmt;
  // delete con;
  // delete res;

}


void DataBase::on_pushButton_2_clicked()
{
    connectToDatabase();

    std::string result;
    QString q ="";
    QString idl="";
    QString dtc="";
   QString eb =  ui->comboBox->currentText();
 std::string w = eb.toStdString();
 std::string z ="SELECT * FROM links where idcategory = '"+w+"'";
std::string qq = " select name from links where idcategory =(SELECT idcategory FROM category  where categoryname = '"+w+"' ORDER BY idcategory DESC limit 1)";
//std::string qq2 = " select idlink from links where idcategory =(SELECT idcategory FROM category  where categoryname = '"+w+"' ORDER BY idcategory DESC limit 1)";
std::string qq2 = " select idlink, datechange from links where idcategory =(SELECT idcategory FROM category  where categoryname = '"+w+"' ORDER BY idcategory DESC limit 1)";
 sql::ResultSet *res = executeQuery(qq);
 sql::ResultSet *res2 = executeQuery(qq2);
 // std::string z ="SELECT * FROM links where categoryname = 'sawert'";
//      res = stmt->executeQuery("SELECT * FROM category where categoryname = 'sawert'");
        ui->comboBox_2->clear();
        while(res->next()&&res2->next()) {
           result = res->getString("name");
        //   result+='\n';
            QString qstr = QString::fromStdString(result);
            ui->comboBox_2->addItem(qstr);
             q+=qstr;
             q+='\n';
          result = res2->getString("idlink");
         // result+='\n';
             qstr = QString::fromStdString(result);
             idl+=qstr;
             idl+='\n';
            result=res2->getString("datechange");
             qstr = QString::fromStdString(result);
             dtc+=qstr;
             dtc+='\n';
           ui->textBrowser->setText(q);
           ui->textBrowser_2->setText(idl);
           ui->textBrowser_3->setText(dtc);

          // ui->comboBox_2->removeItem(ui->comboBox_2->currentIndex());
}
closeConnection();

}


void DataBase::on_comboBox_currentTextChanged(const QString &arg1)
{
//    connectToDatabase();
//
//    std::string result;
//    QString q ="";
//   QString eb =  ui->comboBox->currentText();
// std::string w = eb.toStdString();
// std::string z ="SELECT * FROM category where categoryname = '"+w+"'";
// sql::ResultSet *res = executeQuery(z);
// // std::string z ="SELECT * FROM category where categoryname = 'sawert'";
////      res = stmt->executeQuery("SELECT * FROM category where categoryname = 'sawert'");
//
//        while(res->next()) {
//           result = res->getString("categoryname");
//           result+='/n';
//            QString qstr = QString::fromStdString(result);
//             q+=qstr;
//           ui->textBrowser->setText(eb);
//}
//closeConnection();
}

void DataBase::on_pushButton_clicked(bool checked)
{

}








void DataBase::on_pushButton_4_clicked()
{
    connectToDatabase();
   //QString name = ui->comboBox_2->(ui->comboBox_2->currentIndex());
    QString name = ui->comboBox_2->currentText();
    std::cout<<name.toStdString()<<std::endl;
    std::string dcd = "select context from links where name = 'po'";
    sql::ResultSet *res =executeQuery(dcd);
    std::string row;
    while(res->next())
    {
        row = res->getString("context");

    }
  row = base64_decode(row);
    std::cout<<row
            <<std::endl;

    std::ofstream brows;
     brows.open("br.html");
     if (brows.is_open())
     {
         brows << row ;
     }
    brows.close();
  //  QString rr= QString::fromStdString(row);
  //  QString filePath = "br.html";
  //  QUrl fileUrl = QUrl::fromLocalFile(filePath);
  //  QDesktopServices::openUrl(fileUrl);
 //   QTextBrowser *tb = new QTextBrowser(this);
   // tb->setOpenExternalLinks(true);
   // tb->setHtml(rr);
    QString filePath = "br.html"; // Укажите путь к вашему HTML-файлу
      QUrl url = QUrl::fromLocalFile(filePath);
    //  ui->webView->load(url);
      // ui->webView->show();

      QDesktopServices::openUrl(QUrl("br.html"));

}
