#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include <QMainWindow>
#include <QDialog>
#include <QIcon>


namespace Ui {
    class DialogPreferences;
}

class MainWindow;


class DlgPreferences: public QDialog
{
    Q_OBJECT
public:
    explicit DlgPreferences(MainWindow *parent=NULL);
    ~DlgPreferences();

    static bool editPreferences(MainWindow *parent);

    static QIcon trayIconFrom(const QString& path);

private slots:
    void onCategoryChanged(int category);
    void reset();
    void restoreDefaults();
    void updateTrayIcon(const QString& iconPath);
    void chooseTrayIconFile();
    void onCurrentPluginChanged(int currentIndex);
    void onPluginStateChanged(int state);

private:
    void resetInterface();
    void resetShortcuts();
    void resetPlugins();

    void restoreInterface();
    void restoreShortcuts();
    void restorePlugins();

    void applyInterface();
    void applyShortcuts();
    void applyPlugins();


private:
    Ui::DialogPreferences* ui;
    MainWindow* mainWindow;
};

#endif // DLGPREFERENCES_H
