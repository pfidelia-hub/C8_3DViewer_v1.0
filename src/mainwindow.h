#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>
#include <QTimer>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_x_plus_pressed();
  void on_x_minus_pressed();
  void on_y_plus_pressed();
  void on_y_minus_pressed();
  void on_z_plus_pressed();
  void on_z_minus_pressed();

  void on_x_plus_move_pressed();
  void on_x_minus_move_pressed();
  void on_y_plus_move_pressed();
  void on_y_minus_move_pressed();
  void on_z_plus_move_pressed();
  void on_z_minus_move_pressed();
  void on_pushButton_move_clicked();

  void on_xyz_plus_scale_clicked();
  void on_xyz_minus_scale_clicked();
  void on_x_plus_scale_clicked();
  void on_x_minus_scale_clicked();
  void on_y_plus_scale_clicked();
  void on_y_minus_scale_clicked();
  void on_z_plus_scale_clicked();
  void on_z_minus_scale_clicked();

  void on_speed_textChanged(const QString &arg1);

  void on_line_color_clicked();

  void on_bg_color_btn_clicked();

  void on_LineApply_clicked();

  void on_bg_apply_clicked();

  void on_pushButton_rotate_clicked();

  void on_actionOpen_triggered();

  void on_actionReopen_last_triggered();

  void on_actionClose_triggered();

  void on_DefSettings_clicked();

  void on_projectionApply_clicked();

  void on_pushButtonVertApply_clicked();

  void on_pushButton_Screenshoot_clicked();

  void on_vert_color_btn_clicked();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  int speed = 1;
  float zoom_factor = 1.1f;
  QString last_file = "";
  QColor *LineColor = new QColor(255, 249, 0, 255);
  QColor *BackColor = new QColor(182, 0, 255, 255);
  QColor *VerColor = new QColor();
  void loadSettings(QString);
  void saveSettings();
};
#endif  //  SRC_MAINWINDOW_H_
