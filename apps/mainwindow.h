#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <PropertyEditor/CPropertyEditor.h>
#include <PropertyEditor/CBaseProperty.h>

#include <QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <widget/points.h>
#include <unordered_map>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void cleanClicked();
    void randomPointsClicked();
    void onItemChanged(QTreeWidgetItem *item, int column);

  private:
    Ui::MainWindow *ui;
    PointCloudOpenGLWidget *pt_gl_widget;
    PointCloudOpenGLWidget::Config pt_gl_conf;
    CPropertyEditor *prop_editor;

    
    template<typename T>

    void setPropTo(CBaseProperty* prop, T* tar_var);
};
#endif // MAINWINDOW_H
