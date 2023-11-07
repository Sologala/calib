
#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <algorithm>
#include <array>
#include <random>
#include <string>
#include <unordered_map>

#include <PropertyEditor/CBoolProperty.h>
#include <PropertyEditor/CColorProperty.h>
#include <PropertyEditor/CDateProperty.h>
#include <PropertyEditor/CDateTimeProperty.h>
#include <PropertyEditor/CDoubleProperty.h>
#include <PropertyEditor/CFontProperty.h>
#include <PropertyEditor/CIntegerProperty.h>
#include <PropertyEditor/CListProperty.h>
#include <PropertyEditor/CPropertyHeader.h>
#include <PropertyEditor/CStringProperty.h>
#include <PropertyEditor/CTimeProperty.h>

QVector<QVector3D> generateRandomPointCloud1(int numPoints)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    QVector<QVector3D> pointCloud;
    for (int i = 0; i < numPoints; ++i)
    {
        QVector3D pt;
        pt.setX(dist(gen));
        pt.setY(dist(gen));
        pt.setZ(dist(gen));
        pointCloud.push_back(pt);
    }
    return pointCloud;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* ui->ui_property->addWidget() */

    pt_gl_widget = new PointCloudOpenGLWidget(this);

    /* 这个时候 gl 还没有初始化。 */
    /* pt_gl_widget->addPoints(generateRandomPointCloud1(1000)); */
    ui->gridLayout->addWidget(pt_gl_widget, 0, 0);

    /*---------- */
    prop_editor = new CPropertyEditor(this);
    prop_editor->init();

    CPropertyHeader *pointcloud_head = new CPropertyHeader("pointcloud_head", "PointCloud");
    prop_editor->add(pointcloud_head);

    CBoolProperty *pointcloud_show = new CBoolProperty(pointcloud_head, "pointcloud_show", "show", true);
    prop_editor->add(pointcloud_show);

    CIntegerProperty *pointcloud_size = new CIntegerProperty(pointcloud_head, "pointcloud_size", "size", 2);
    prop_editor->add(pointcloud_show);

    CColorProperty *pointcloud_color = new CColorProperty(pointcloud_head, "pointcloud_color", "color", Qt::red);
    prop_editor->add(pointcloud_color);

    ui->proptree->addWidget(prop_editor);
    connect(prop_editor, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this,
            SLOT(onItemChanged(QTreeWidgetItem *, int)));

    /* connect(ui->proptree, SIGNAL(itemSelectionChanged()), this, SLOT(closeEditor())); */

    // -------------按钮
    connect(ui->cleanBtn, SIGNAL(clicked(bool)), this, SLOT(cleanClicked()));
    connect(ui->randomPointsBtn, SIGNAL(clicked(bool)), this, SLOT(randomPointsClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pt_gl_widget;
}

void MainWindow::randomPointsClicked()
{
    pt_gl_widget->addPoints(generateRandomPointCloud1(1000));
}

void MainWindow::cleanClicked()
{
    pt_gl_widget->clean();
}
template <typename T>

void MainWindow::setPropTo(CBaseProperty *prop, T *tar_var)
{
    *tar_var = prop->getVariantValue().value<T>();
}

void MainWindow::onItemChanged(QTreeWidgetItem *item, int column)
{
    std::map<const std::string, std::function<void(CBaseProperty *)>> prop_map;

#define PROP_MAP(_name, _type, _var)                                                                                   \
    prop_map[_name] = [&](CBaseProperty *prop) { *_var = prop->getVariantValue().value<_type>(); };

    PROP_MAP("pointcloud_size", int, &pt_gl_conf.pointcloud_size);
    PROP_MAP("pointcloud_color", QColor, &pt_gl_conf.pointcloud_color);
    PROP_MAP("pointcloud_show", bool, &pt_gl_conf.pointcloud_show);

    CBaseProperty *prop = dynamic_cast<CBaseProperty *>(item);
    if (prop == nullptr)
        return;

    const std::string prop_id(prop->getId());
    if (column)
    {
        if (prop_map.count(prop_id))
        {
            auto &f = prop_map[prop_id];
            f(prop);
        }
    }
    else
    {
        if (prop->isMarkable())
        {
            /* qDebug() << "key " << prop_id.c_str() << " clicked"; */
        }
    }

    pt_gl_widget->setConfig(pt_gl_conf);
}
