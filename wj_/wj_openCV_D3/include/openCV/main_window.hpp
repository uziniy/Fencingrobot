/**
 * @file /include/openCV/main_window.hpp
 *
 * @brief Qt based gui for openCV.
 *
 * @date November 2010
 **/
#ifndef openCV_MAIN_WINDOW_H
#define openCV_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include <opencv2/opencv.hpp>

/*****************************************************************************
** Namespace
*****************************************************************************/
using namespace cv;
namespace openCV {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();
  QTimer *m_Timer;


public Q_SLOTS:
  void main();
  void on_red_clicked();
  void on_blue_clicked();
  void on_green_clicked();



private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace openCV

#endif // openCV_MAIN_WINDOW_H
