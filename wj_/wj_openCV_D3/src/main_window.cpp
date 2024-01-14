/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/openCV/main_window.hpp"
#include "opencv2/opencv.hpp"
double hmin;
double smin;
double vmin;
double hmax;
double smax;
double vmax;


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace openCV {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    setWindowIcon(QIcon(":/images/icon.png"));

    qnode.init();

    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(main()));
    m_Timer->start(100);

    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Functions
*****************************************************************************/
void MainWindow::main(){

  Mat img = cv::imread("/home/capstone/KakaoTalk_20230906_204823358.jpg");
  GaussianBlur(img, img, Size(7,7),3);
  Mat clone_mat = img.clone();
  cv::resize(clone_mat,clone_mat,cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
  QImage image = QImage((const unsigned char*)(clone_mat.data),clone_mat.cols,clone_mat.rows,QImage::Format_RGB888);
  ui.label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));

  Mat img1 = cv::imread("/home/capstone/KakaoTalk_20230906_204823358.jpg");

  Mat clone_mat1 = img1.clone();
  cv::resize(clone_mat1,clone_mat1,cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
  QImage image1 = QImage((const unsigned char*)(clone_mat1.data),clone_mat1.cols,clone_mat1.rows,QImage::Format_RGB888);
  ui.label_2->setPixmap(QPixmap::fromImage(image1.rgbSwapped()));

  Mat HSV_mat = clone_mat.clone();
  Mat result_mat;
  cv::cvtColor(clone_mat,HSV_mat,CV_BGR2HSV);
  inRange(HSV_mat, cv::Scalar(hmin,smin,vmin),cv::Scalar(hmax,smax,vmax), result_mat);
  cv::resize(result_mat, result_mat, cv::Size(640, 480),0 ,0, cv::INTER_CUBIC);


  cv::Mat label, stats, centroids;
  int num = cv::connectedComponentsWithStats(result_mat, label, stats, centroids, 8);

      for (int i=1; i<num; ++i) {
        int x = static_cast<int>(stats.at<int>(i,cv::CC_STAT_LEFT));
        int y= static_cast<int>(stats.at<int>(i,cv::CC_STAT_TOP));
        int width = static_cast<int>(stats.at<int>(i,cv::CC_STAT_WIDTH));
        int height = static_cast<int>(stats.at<int>(i,cv::CC_STAT_HEIGHT));

        cv::rectangle(result_mat, cv::Rect(x,y,width,height),cv::Scalar(255, 255, 255));
        QImage result_image = QImage((const unsigned char*)(result_mat.data), result_mat.cols, result_mat.rows, QImage::Format_Indexed8);
        ui.label->setPixmap(QPixmap::fromImage(result_image));

        int xp = x+(width/2);
        int yp = y+(height/2);

        circle(result_mat,Point(xp,yp),3,Scalar(0,0,0),-1);


      }


}
void MainWindow::on_red_clicked(){
  hmin=0;
  std::cout<<hmin<<std::endl;
  smin=140;
  std::cout<<smin<<std::endl;
  vmin=151;
  std::cout<<vmin<<std::endl;
  hmax=30;
  std::cout<<hmax<<std::endl;
  smax=255;
  std::cout<<smax<<std::endl;
  vmax=246;
  std::cout<<vmax<<std::endl;

}
void MainWindow::on_blue_clicked(){
  hmin=43;
  std::cout<<hmin<<std::endl;
  smin=13;
  std::cout<<smin<<std::endl;
  vmin=108;
  std::cout<<vmin<<std::endl;
  hmax=94;
  std::cout<<hmax<<std::endl;
  smax=255;
  std::cout<<smax<<std::endl;
  vmax=255;
  std::cout<<vmax<<std::endl;

}
void MainWindow::on_green_clicked(){
  hmin=87;
  std::cout<<hmin<<std::endl;
  smin=65;
  std::cout<<smin<<std::endl;
  vmin=154;
  std::cout<<vmin<<std::endl;
  hmax=125;
  std::cout<<hmax<<std::endl;
  smax=255;
  std::cout<<smax<<std::endl;
  vmax=255;
  std::cout<<vmax<<std::endl;

}

}  // namespace openCV

