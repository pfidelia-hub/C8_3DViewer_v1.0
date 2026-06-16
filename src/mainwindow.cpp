#include "mainwindow.h"

#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLShaderProgram>
#include <QTime>
#include <QWidget>

#include "affine_transformation.h"
#include "geometryengine.h"
#include "ui_mainwindow.h"

extern "C" {
#include "3d_viewer.h"
#include "affine_transformation.h"
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //    loadSettings("./new_settings.cfg");
  loadSettings("/new_settings.cfg");
  on_bg_apply_clicked();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_x_plus_pressed() {
  ui->openGLWidget->geometries->Xrotation(speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_x_minus_pressed() {
  ui->openGLWidget->geometries->Xrotation(-speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_plus_pressed() {
  ui->openGLWidget->geometries->Yrotation(speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_minus_pressed() {
  ui->openGLWidget->geometries->Yrotation(-speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_plus_pressed() {
  ui->openGLWidget->geometries->Zrotation(speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_minus_pressed() {
  ui->openGLWidget->geometries->Zrotation(-speed * 1.0f);
  ui->openGLWidget->upd();
}

void MainWindow::on_x_plus_move_pressed() {
  ui->openGLWidget->geometries->Xmoving(speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_x_minus_move_pressed() {
  ui->openGLWidget->geometries->Xmoving(-speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_plus_move_pressed() {
  ui->openGLWidget->geometries->Ymoving(speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_minus_move_pressed() {
  ui->openGLWidget->geometries->Ymoving(-speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_plus_move_pressed() {
  ui->openGLWidget->geometries->Zmoving(speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_minus_move_pressed() {
  ui->openGLWidget->geometries->Zmoving(-speed * .1f);
  ui->openGLWidget->upd();
}

void MainWindow::on_xyz_plus_scale_clicked() {
  ui->openGLWidget->geometries->XYZscale(zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_xyz_minus_scale_clicked() {
  ui->openGLWidget->geometries->XYZscale(-zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_x_plus_scale_clicked() {
  ui->openGLWidget->geometries->Xscale(zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_x_minus_scale_clicked() {
  ui->openGLWidget->geometries->Xscale(-zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_plus_scale_clicked() {
  ui->openGLWidget->geometries->Yscale(zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_y_minus_scale_clicked() {
  ui->openGLWidget->geometries->Yscale(-zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_plus_scale_clicked() {
  ui->openGLWidget->geometries->Zscale(zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_z_minus_scale_clicked() {
  ui->openGLWidget->geometries->Zscale(-zoom_factor);
  ui->openGLWidget->upd();
}

void MainWindow::on_speed_textChanged(const QString& arg1) {
  if (ui->speed->value() == 0)
    speed = 1;
  else
    speed = ui->speed->value();
}

void MainWindow::on_line_color_clicked() {
  *LineColor = QColorDialog::getColor(*ui->openGLWidget->color);
  LineColor = ui->openGLWidget->color;
}

void MainWindow::on_bg_color_btn_clicked() {
  *BackColor = QColorDialog::getColor();
  BackColor = ui->openGLWidget->color_back;
}

void MainWindow::on_bg_apply_clicked() {
  ui->openGLWidget->color_back = BackColor;
  ui->openGLWidget->upd();
}

void MainWindow::on_LineApply_clicked() {
  if (ui->radioButton_2->isChecked()) {
    ui->openGLWidget->flag_dotted = 1;
    ui->openGLWidget->upd();
  } else {
    ui->openGLWidget->flag_dotted = 0;
    ui->openGLWidget->upd();
  }
  ui->openGLWidget->color = LineColor;
  ui->openGLWidget->upd();
  ui->openGLWidget->line_width = ui->width->value();
  ui->openGLWidget->upd();
}

void MainWindow::on_pushButton_move_clicked() {
  ui->openGLWidget->geometries->Xmoving(ui->doubleSpinBoxMoveX->value());
  ui->openGLWidget->geometries->Ymoving(ui->doubleSpinBoxMoveY->value());
  ui->openGLWidget->geometries->Zmoving(ui->doubleSpinBoxMoveZ->value());
  ui->openGLWidget->upd();
}

void MainWindow::on_pushButton_rotate_clicked() {
  ui->openGLWidget->geometries->Xrotation(ui->spinBoxRotationX->value());
  ui->openGLWidget->geometries->Yrotation(ui->spinBoxRotationY->value());
  ui->openGLWidget->geometries->Zrotation(ui->spinBoxRotationZ->value());
  ui->openGLWidget->upd();
}

void MainWindow::on_actionOpen_triggered() {
  QString str = QFileDialog::getOpenFileName(this, "open file", "/", "*.obj");
  if (str.length()) {
    last_file = str;
    QList<QString> name = str.split('/');
    QByteArray barr = str.toLatin1();
    char* path = (char*)barr.data();
    strlcpy(path, barr, str.length() + 1);
    ui->openGLWidget->geometries->initCubeGeometry(path);
    ui->openGLWidget->geometries->drawCubeGeometry(&ui->openGLWidget->program);
    ui->openGLWidget->upd();
  }
}

void MainWindow::on_actionReopen_last_triggered() {
  char* path = (char*)malloc(sizeof(char) * last_file.length() + 1);
  QByteArray barr = last_file.toLatin1();
  strlcpy(path, barr, last_file.length() + 1);
  ui->openGLWidget->geometries->initCubeGeometry(path);
  free(path);
  ui->openGLWidget->geometries->drawCubeGeometry(&ui->openGLWidget->program);
  ui->openGLWidget->upd();
}

void MainWindow::on_actionClose_triggered() {
  ui->openGLWidget->geometries->initCubeGeometry("");
  ui->openGLWidget->geometries->drawCubeGeometry(&ui->openGLWidget->program);
  ui->openGLWidget->upd();
}

void MainWindow::on_DefSettings_clicked() { loadSettings(":/settings.cfg"); }

void MainWindow::loadSettings(QString str) {
  on_bg_apply_clicked();
  QString path = "";
  if (str[0] != ':') path = QCoreApplication::applicationDirPath();
  path += str;
  qDebug() << "load from: " << path;
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    qDebug() << "file opened";
    QTextStream t_stream(&file);
    QString str = t_stream.readLine();
    if (str.toInt() == MainWidget::central) {
      ui->openGLWidget->proj_type = MainWidget::central;
      ui->radioButtonCentralProjection->setChecked(1);
      ui->radioButtonParallelProjection->setChecked(0);
    } else {
      ui->openGLWidget->proj_type = MainWidget::parallel;
      ui->radioButtonCentralProjection->setChecked(0);
      ui->radioButtonParallelProjection->setChecked(1);
    }
    str = t_stream.readLine();
    if (str.toInt() == 0) {
      ui->openGLWidget->flag_dotted = 0;
      ui->radioButton->setChecked(1);
      ui->radioButton_2->setChecked(0);
    } else {
      ui->openGLWidget->flag_dotted = 1;
      ui->radioButton->setChecked(0);
      ui->radioButton_2->setChecked(1);
    }
    str = t_stream.readLine();
    if (str.toInt() == 0) {
      ui->radioButtonVertNone->setChecked(1);
      ui->radioButtonVertSphere->setChecked(0);
      ui->radioButtonVertCube->setChecked(0);
    } else if (str.toInt() == 1) {
      ui->radioButtonVertSphere->setChecked(0);
      ui->radioButtonVertNone->setChecked(0);
      ui->radioButtonVertCube->setChecked(1);
    } else if (str.toInt() == 2) {
      ui->radioButtonVertCube->setChecked(0);
      ui->radioButtonVertSphere->setChecked(1);
      ui->radioButtonVertNone->setChecked(0);
    }
    //        on_pushButtonVertApply_clicked();
    str = t_stream.readLine();
    ui->width->setValue(str.toInt());
    ui->openGLWidget->line_width = ui->width->value();
    str = t_stream.readLine();
    ui->size_ver->setValue(str.toInt());
    str = t_stream.readLine();
    QList<QString> clr = str.split(' ');
    LineColor->setRgb(clr[0].toInt(), clr[1].toInt(), clr[2].toInt(),
                      clr[3].toInt());
    clr.clear();
    str = t_stream.readLine();
    clr = str.split(' ');
    BackColor->setRgb(clr[0].toInt(), clr[1].toInt(), clr[2].toInt(),
                      clr[3].toInt());
    clr.clear();
    str = t_stream.readLine();
    clr = str.split(' ');
    VerColor->setRgb(clr[0].toInt(), clr[1].toInt(), clr[2].toInt(),
                     clr[3].toInt());
    file.close();
  }
  on_LineApply_clicked();
  on_projectionApply_clicked();
  //    if (ui->checkBoxVert->isChecked())
  //        on_pushButtonVertApply_clicked();
  ui->openGLWidget->upd();
  on_bg_apply_clicked();
  //    on_pushButtonVertApply_clicked();
}

void MainWindow::saveSettings() {
  QString path;
  path += QCoreApplication::applicationDirPath();
  path += "/new_settings.cfg";
  QFile file(path);
  //    qDebug() << file.open(QIODevice::NewOnly);
  //    file.open()
  qDebug() << path;
  if (file.open(QIODevice::ReadWrite)) {
    qDebug() << "save start\n";
    QTextStream t_stream(&file);
    t_stream.flush();
    t_stream << ui->openGLWidget->proj_type << '\n';
    t_stream << ui->openGLWidget->flag_dotted << '\n';
    if (ui->radioButtonVertNone->isChecked()) {
      t_stream << "0\n";
    } else if (ui->radioButtonVertSphere->isChecked()) {
      t_stream << "2\n";
    } else {
      t_stream << "1\n";
    }
    t_stream << ui->width->value() << '\n';
    t_stream << ui->size_ver->value() << '\n';
    int red, green, blue, alpha;
    LineColor->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    BackColor->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    VerColor->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    file.close();
  }
}

void MainWindow::on_projectionApply_clicked() {
  if (ui->radioButtonCentralProjection->isChecked()) {
    ui->openGLWidget->proj_type = MainWidget::central;
  } else {
    ui->openGLWidget->proj_type = MainWidget::parallel;
  }
  ui->openGLWidget->resizeGL(640, 480);
  ui->openGLWidget->upd();
}

void MainWindow::on_pushButtonVertApply_clicked() {
  if (ui->radioButtonVertNone->isChecked()) {
    ui->openGLWidget->geometries->flag_ver = 0;
    ui->openGLWidget->geometries->flag_sphere = 0;
  } else if (ui->radioButtonVertSphere->isChecked()) {
    ui->openGLWidget->geometries->flag_ver = 1;
    ui->openGLWidget->geometries->flag_sphere = 1;
  } else {
    ui->openGLWidget->geometries->flag_ver = 1;
    ui->openGLWidget->geometries->flag_sphere = 0;
  }
  ui->openGLWidget->color_ver = VerColor;
  ui->openGLWidget->geometries->size_ver = ui->size_ver->value();
  ui->openGLWidget->upd();
}

void MainWindow::on_pushButton_Screenshoot_clicked() {
  QDate curDate;
  QTime curTime;
  QString curTimeStr = curTime.currentTime().toString();
  QString curDateStr = curDate.currentDate().toString();
  QString pathToSave = QFileDialog::getExistingDirectory();

  if (!ui->openGLWidget->grabFramebuffer().save(
          pathToSave + "/" + curDateStr + curTimeStr + ".JPG", NULL, 100) &&
      pathToSave.length()) {
    QMessageBox::warning(this, "File could not be saved", "Wrong",
                         QMessageBox::Ok);
  } else {
    ui->openGLWidget->grabFramebuffer().save(
        pathToSave + "/" + curDateStr + curTimeStr + ".BMP", NULL, 100);
  }
}

void MainWindow::on_vert_color_btn_clicked() {
  *VerColor = QColorDialog::getColor();
  VerColor = ui->openGLWidget->color_ver;
}

void MainWindow::on_pushButton_clicked() { ui->openGLWidget->setTimer(); }
