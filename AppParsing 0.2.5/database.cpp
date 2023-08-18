#pragma execution_character_set("utf-8")
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
#include <QWebView>
#include <qlocale.h>
#include <QTranslator>
#include <QProgressDialog>
#include <libxml/HTMLparser.h>
#include <libxml/uri.h>
#include <libxml/xpath.h>
#include <libxml/xmlsave.h>

void DownloadFile(const char* url, const char* fname);
void replaceLinkInFile(const std::string& filePath, const std::string& oldLink, const std::string& newLink);

void printLinks(xmlNode *node, const std::string &baseUrl, std::string folderPath, int i) {
  // int i = 1;
   std::string fname;
    xmlNode *curNode = NULL;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curNode->name, (const xmlChar *)"a") == 0 ||
                xmlStrcmp(curNode->name, (const xmlChar *)"img") == 0) {
                xmlChar *link = xmlGetProp(curNode, (const xmlChar *)"href");
                if (!link)
                    link = xmlGetProp(curNode, (const xmlChar *)"src");
                if (link) {
                    std::cout << "Original Link: " << link << std::endl;
                    //fname = std::string("./")+folderPath+"/file_"+ std::to_string(i);
                    //std::cout << "Modified Links: " << link << std::endl;
                    //std::cout<<"file name : "<<fname<<std::endl;
                    //DownloadFile( (char *)link, fname.c_str());
                   // const char* fileExtension =strrchr((char *)link, '.');
                    //if(fileExtension!=NULL)
                    //fname = std::string("./")+folderPath+"/file_"+ std::to_string(i)+fileExtension;
                   // else
                    fname = std::string("./")+folderPath+"/file_"+ std::to_string(i);
                    replaceLinkInFile("index.html", (char *)link, fname.c_str());
                    i++;
                    xmlFree(link);

                }
            }
        }
        printLinks(curNode->children, baseUrl,folderPath, i+=1);
    }
}
void printLinksC(xmlNode *node, const std::string &baseUrl, std::string folderPath, int i) {
    xmlNode *curNode = NULL;
    std::string fname;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curNode->name, (const xmlChar *)"a") == 0 ||
                xmlStrcmp(curNode->name, (const xmlChar *)"img") == 0) {
                xmlChar *link = xmlGetProp(curNode, (const xmlChar *)"href");
                if (!link)
                    link = xmlGetProp(curNode, (const xmlChar *)"src");
                if (link) {
                    //const char* fileExtension =strrchr((char *)link, '.');
                    //if(fileExtension!=NULL)
                    //fname = std::string("./")+folderPath+"/file_"+ std::to_string(i)+fileExtension;
                    //else
                    fname = std::string("./")+folderPath+"/file_"+ std::to_string(i);

                    std::cout << "Modified Links: " << link << std::endl;
                    std::cout<<"file name : "<<fname<<std::endl;
                    DownloadFile( (char *)link, fname.c_str());
                    //replaceLinkInFile("index.html", originalLink, absoluteLink.c_str());
                    i++;

                    xmlFree(link);
                }
            }
        }
        printLinksC(curNode->children, baseUrl, folderPath, i+=1);
    }
}
void replaceLinks(xmlNode *node, const std::string &baseUrl) {
    xmlNode *curNode = NULL;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curNode->name, (const xmlChar *)"a") == 0 ||
                xmlStrcmp(curNode->name, (const xmlChar *)"img") == 0) {
                xmlChar *link = xmlGetProp(curNode, (const xmlChar *)"href");
                if (!link)
                    link = xmlGetProp(curNode, (const xmlChar *)"src");
                if (link) {
                    std::string originalLink(reinterpret_cast<const char *>(link));
                    xmlFree(link);

                    // Replace relative links with absolute links
                    if (originalLink.substr(0, 4) != "http" && originalLink.substr(0, 2) != "//") {
                        std::string absoluteLink = baseUrl + originalLink;
                        std::cout<<originalLink<<" "<<absoluteLink<<std::endl;
                       // replaceLinkInFile("index.html", originalLink, absoluteLink.c_str());

                        xmlSetProp(curNode, (const xmlChar *)"href", (const xmlChar *)absoluteLink.c_str());
                        xmlSetProp(curNode, (const xmlChar *)"src", (const xmlChar *)absoluteLink.c_str());
                    }
                }
            }
        }
        replaceLinks(curNode->children, baseUrl);
    }
}







static std::string base64_encode(const std::string &in) {
    std::string out;
    int val = 0, valb = -6;
    for (uchar c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
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




void regexing(int lineNumber, int i,std::string folderPath,std::string line,std::smatch match,std::string qurl)
{

    std::cout << "Ссылка найдена на строке " << lineNumber << ": " << match[0] << std::endl; // вывод найденной ссылки и на какой строчке она находится
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
    std::string fq = std::string ("./")+folderPath+"/"+"file_" +std::to_string(i)+"."+naming.substr(pos+1); //вывод в консоль названия созданных файлов






    if(naming.length()>0 &&   pos>posq && posq!=0)
    {
        std:: cout<<"name file:  "<<fq<<std::endl<<pos<<" "<<posq<<std::endl;
        DownloadFile(naming.c_str(), fq.c_str()); // загрузка файлов по ссылкам
        replaceLinkInFile("index.html", match[2], fq);
    }
}







DataBase::DataBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBase)
{
    ui->setupUi(this);

    driver = sql::mysql::get_mysql_driver_instance();
    connectToDatabase();



     // Считывание результатов запроса в переменную
     sql::ResultSet *res = executeQuery("SELECT categoryname FROM category");
     std::string result;
     QString q ="";
     while(res->next())
     {
        result = res->getString("categoryname");

        QString qstr = QString::fromStdString(result);
        ui->textBrowser->setText(q);
        result+= '\n';
        q+=qstr;
        ui->comboBox->addItem(qstr);
      }
    closeConnection();
}




DataBase::~DataBase()
{
 delete ui;
}

void DataBase::on_pushButton_clicked()
{ // кнопка добавления новой ссылки на html страницу и ее парсинг
    connectToDatabase();
    bool isOkPressed{};
    bool isOkPressed2{};
    bool isOkPressed3{};
    QString link;

    QString Folder;
    QString Category;
    link= QInputDialog::getText(nullptr, "Ввод данных", "Введите URL:", QLineEdit::Normal, "",&isOkPressed); //ссылка
    if (isOkPressed)
    Folder = QInputDialog::getText(nullptr, "Ввод данных", "Введите Папку:", QLineEdit::Normal, "",&isOkPressed2); // папка
    else
        return;
    if (isOkPressed2)
    Category = QInputDialog::getText(nullptr, "Ввод данных", "Введите Категорию:", QLineEdit::Normal, "",&isOkPressed3); //категория ссылки
    else
        return;
    if (isOkPressed3){
    ui->comboBox->clear();



    //ui->comboBox->addItem(Category);
    //ui->comboBox->itemData(ui->comboBox->currentIndex());
    std::string uurl = link.toStdString(); //ссылка для либы Curl для скачивания
    std::cout<<uurl<<std::endl;
    std::string folderPath = Folder.toStdString(); //папка куда будет скачиваться контент
    std::string fild2=folderPath;
    std::string fild3 = Category.toStdString();
    std::cout << "Category: " << fild3 << std::endl;
    std::string qurl = uurl;

    //получение даты и времени и перевод их в форма date mysql
    std::time_t current_time = std::time(nullptr);
    std::tm* datetime = std::localtime(&current_time);
    std::ostringstream datetime_stream;
    datetime_stream << std::put_time(datetime, "%Y-%m-%d %H:%M:%S");
    std::string datetime_mysql = datetime_stream.str();
    std::cout << "Текущая дата и время: " << datetime_mysql << std::endl;




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
    bool isOkPressed4{};
    isOkPressed4=true;
    while(res!= CURLE_OK && isOkPressed4)
    {

        std::cerr << " failed: " << curl_easy_strerror(res) << std::endl;
        link = QInputDialog::getText(nullptr, "Некорректный URL", "Введите URL сорректно:", QLineEdit::Normal, "",&isOkPressed4); //ссылка
        if (isOkPressed) {
        uurl = link.toStdString();
        curl_easy_setopt(curl,CURLOPT_URL,uurl.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
        response = curl_easy_perform(curl);
        res = curl_easy_perform(curl);
        }
        else
            return;
    }
    if(res== CURLE_OK){
    std::string query = "insert into category (categoryname,datechange) values ('"+fild3+"','"+datetime_mysql+"') ON DUPLICATE KEY UPDATE "+"datechange = '"+datetime_mysql+"'";

    std::cout<<query<<std::endl;
    sql::Statement* stmt = con->createStatement();
    stmt->execute(query);
    sql::ResultSet *resq = executeQuery("SELECT categoryname FROM category");
    std::string result;
    QString q ="";
    while(resq->next())
    {
       result = resq->getString("categoryname");

       QString qstr = QString::fromStdString(result);
       ui->textBrowser->setText(q);
       result+= '\n';
       q+=qstr;
       ui->comboBox->addItem(qstr);
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
        QMessageBox::critical(nullptr,"Не удалось открыть страницу","Попробкйте ввести другой Url");
        std::cout<<"err: file not opened"<<std::endl;
   }
    else {

        std::string htmlFilePath = "index.html";
            std::string baseUrl = uurl;

            xmlDocPtr doc = htmlReadFile(htmlFilePath.c_str(), NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
            if (doc == NULL) {
                std::cerr << "Error reading HTML file." << std::endl;

            }

            xmlNode *rootElement = xmlDocGetRootElement(doc);
            int i =1;
            // Print original links
            std::cout << "Original Links:" << std::endl;
            printLinks(rootElement, baseUrl,folderPath, i);

            // Replace relative links with absolute links
            replaceLinks(rootElement, baseUrl);


            // Print modified links
            std::cout << "Modified Links:" << std::endl;
            printLinksC(rootElement, baseUrl,folderPath, i);

            xmlFreeDoc(doc);
            xmlCleanupParser();
            fedit.close();
            //DownloadFile(naming.c_str(), fq.c_str()); // загрузка файлов по ссылкам
            //replaceLinkInFile("index.html", match[2], fq);












//
//    int i=0;
//
//
//    std::regex linkRegex(R"(\s+(?:[^>]*?\s+)?href=(["'])(.*?)\1)");
//    std::regex linkRegex2(R"(\s+(?:[^>]*?\s+)?src=(["'])(.*?)\1)");
//
//    std::string line;
//    int lineNumber = 1;
//    while (std::getline(fedit, line))
//    {
//        std::smatch match;
//        while (  std::regex_search(line, match, linkRegex2))  //проход по ссылка с src
//        {
//            i++;
//            //regexing( lineNumber, i, folderPath,line, match, qurl);
//            std::cout << "Ссылка найдена на строке " << lineNumber << ": " << match[0] << std::endl; // вывод найденной ссылки и на какой строчке она находится по src
//            line = match.suffix().str();
//            std:: string naming;
//            auto str = match[2];
//            std::cout<<str<<" "<<std::endl;
//            std::string po = match[2].str();
//            auto poss = po.find_first_of(":");
//            auto possq = po.find_first_of("/");
//            if(poss>possq || poss>1000)
//            {
//                naming=qurl+"/"+std::string(match[2]);
//                std::cout<<"link = "<<naming << std::endl;
//
//            }
//            else
//                 naming=match[2].str();
//
//            const std::string empty;
//            auto pos = naming.find_last_of(".");
//            auto posq =naming.find_last_of("/");
//            std::string sbs = naming.substr(pos+1);
//            std::string fq = std::string ("./")+folderPath+"/"+"file_" +std::to_string(i)+"."+naming.substr(pos+1); //вывод в консоль названия созданных файлов
////
//
//
//
//
//
//            if(naming.length()>0 &&   pos>posq && posq!=0)
//            {
//                std:: cout<<"name file:  "<<fq<<std::endl<<pos<<" "<<posq<<std::endl;
//               DownloadFile(naming.c_str(), fq.c_str()); // загрузка файлов по ссылкам
//                replaceLinkInFile("index.html", match[2], fq);
//            }
//
//         }
//
//
//
//
//         while (  std::regex_search(line, match, linkRegex))  //проход по ссылка с href  далле тоже самое
//         {
//            i++;
//            //regexing( lineNumber, i, folderPath,line, match, qurl);
//            std::cout << "Ссылка найдена на строке " << lineNumber << ": " << match[0] << std::endl;
//            line = match.suffix().str();
//            std:: string naming;
//
//            auto str = match[2];
//            std::cout<<str<<" "<<std::endl;
//            std::string po = match[2].str();
//            auto poss = po.find_first_of(":");
//            auto possq = po.find_first_of("/");
//
//            if(poss>possq || poss>1000)
//            {
//                naming=qurl+"/"+std::string(match[2]);
//                std::cout<<"link = "<<naming << std::endl;
//            }
//            else
//                naming=match[2].str();
//
//            const std::string empty;
//            auto pos = naming.find_last_of(".");
//            auto posq =naming.find_last_of("/");
//            std::string sbs = naming.substr(pos+1);
//            std::string fq = std::string ("./")+folderPath+"/"+"file_" +std::to_string(i)+"."+naming.substr(pos+1);
//
//
//
//
//            if(naming.length()>0 &&   pos>posq && posq!=0)
//            {
//                std:: cout<<"name file:  "<<fq<<std::endl<<pos<<" "<<posq<<std::endl;
//                DownloadFile(naming.c_str(), fq.c_str());
//                replaceLinkInFile("index.html", match[2], fq);
//            }
//
//         }
//
//         lineNumber++;
//
//}
//
//
//  fedit.close();







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

    while(!fin.eof())
    {
        std:: getline(fin, strh);
        str1 += strh;
        if (!fin.eof())
        {
            str1 += '\n';
        }

    }
    fin.close();

    std::string links_ = "insert into links (idcategory,name,context,datechange) values ((SELECT idcategory FROM category  where categoryname = '"+fild3+"' ORDER BY idcategory DESC limit 1),'"+fild2+"','"+base64_encode(str1)+"','"+datetime_mysql1+"')";
    stmt->execute(links_);

    delete stmt;
    closeConnection();
    }
    else
        return;
    }
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
{ // при нажатии окрывает список названия статей выбранной категории
    connectToDatabase();

    std::string result;
    QString n ="";  //name
    QString idl=""; // idlink
    QString dtc=""; //datechange
    QString eb =  ui->comboBox->currentText(); //выбирается категория
    std::string w = eb.toStdString();
    std::string qq2 = " select name, idlink, datechange from links where idcategory =(SELECT idcategory FROM category  where categoryname = '"+w+"' ORDER BY idcategory DESC limit 1)";
    sql::ResultSet *res = executeQuery(qq2);
        ui->comboBox_2->clear();
        while(res->next())
        {
            result = res->getString("name");
            QString qstr = QString::fromStdString(result);
            ui->comboBox_2->addItem(qstr);
            n+=qstr;
            n+='\n';
            result = res->getString("idlink");
            qstr = QString::fromStdString(result);
            idl+=qstr;
            idl+='\n';
            result=res->getString("datechange");
            qstr = QString::fromStdString(result);
            dtc+=qstr;
            dtc+='\n';
            ui->textBrowser->setText(n);
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
{   //кнопка открытия выбранной страницы

    connectToDatabase();

    //Получаем выбранный context для открытия его в новом окне
    QString name = ui->comboBox_2->currentText();
    std::string nm = name.toStdString();
    std::cout<<name.toStdString()<<std::endl;
    std::string dcd = "select context from links where name = '"+nm+"'";
    sql::ResultSet *res =executeQuery(dcd);
    std::string row;
    while(res->next())
    {
        row = res->getString("context");

    }
    delete res;
    row = base64_decode(row); //перевод обратно из base64

    std::cout<<row<<std::endl;

    std::ofstream brows;
    brows.open("br.html");
    if (brows.is_open())
    {
         std::cout<<"file rewriting"<<std::endl;
         brows << row ;

    }
    brows.close();
    std::cout<<row<<std::endl;
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QWebView *myWebView = new QWebView;

    //myWebView->setHtml(QString::fromStdString(row));
    // QWebEngineSettings::setFontFamily("utf8");
    // QWebEngineSettings::setDefaultTextEncoding("utf8");

    myWebView->load(QUrl("file:///home/sawert/qtprojects/build-AppParsing-unknown-Debug/br.html"));
    myWebView->show();

    // ui->webView->load(QString::fromStdString(row));
    // ui->webView->show();
    // Отображение QWebView
    // ui->webView->show();
    //QDesktopServices::openUrl(QUrl("br.html"));

    closeConnection();
}




