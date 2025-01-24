#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QStringList>

class QLineEdit;
class QPushButton;
class QTextEdit;

class Profile : public QWidget {
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);

private slots:
    void onLogoutButtonClicked();
    void onSubmitButtonClicked(); // Слот для обработки отправки заказа
    void onBackToHomeButtonClicked(); // Слот для обработки возврата на главную страницу
    void onSelectFiles(); // Слот для выбора файлов
    void onUploadFinished(); // Слот для обработки ответа сервера

private:
    QTextEdit *descriptionEdit; // Поле для описания заказа
    QPushButton *submitButton; // Кнопка отправки заказа
    QPushButton *backToHomeButton; // Кнопка возврата на главную страницу
    QStringList selectedFiles; // Список выбранных файлов

    QNetworkAccessManager *networkManager; // Объект для выполнения сетевых запросов

    void sendUploadRequest(const QString &description, const QStringList &files); // Метод для отправки данных и файлов на сервер
};


#endif // PROFILE_H
