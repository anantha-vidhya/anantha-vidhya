#include "mainwindow.h"
#include "ui_mainwindow.h"
//*****************
#include <QTimer>
#include <QDateTime>
#include <QDate>
//*****************

//******i2c handling c++ code*******
#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>
#include <fcntl.h>// for opening file
#include <sys/ioctl.h> //IOCTL FUNCTION
#include <unistd.h>//READ AND WRITE FUNCTIONS







//***********************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    showTime();
    showDate();
    QTimer *timer=new QTimer(this);
//    QDateTimeEdit *date_time=new QDateTimeEdit(this);
    connect(timer ,SIGNAL(timeout()),this,SLOT(showTime()));
//    connect(date_time ,SIGNAL(dateTimeChanged),this,SLOT(showTime()));
    timer->start();
//    QDateTime dateTime=QDateTime::currentDateTime();
//    QString datetimetext=dateTime.toString();
//    ui->label_2->setText(datetimetext);
}
void MainWindow::showTime()
{
    QTime time=QTime::currentTime();
      QString timetext=time.toString("hh : mm : ss");
    //blink the  colon at every sec
    if((time.second() % 2) == 0)
//    {
//        timetext[3] = ' ';
//        timetext[8] = ' ';
//    }
    ui->label->setText(timetext);
}

void MainWindow::showDate()
{
    QDate date = QDate::currentDate();

    /////////////////////////////////////////
    //       Format        Result          //
    //    dd.MM.yyyy      21.05.2001       //
    //    ddd MMMM d yy   Tue May 21 01    //
    //    hh:mm:ss.zzz	  14:13:09.120     //
    //    hh:mm:ss.z	  14:13:09.12      //
    //    h:m:s ap	      2:13:9 pm        //
    /////////////////////////////////////////


    QString datetext=date.toString("dd : MM : yyyy");
    ui->label_2->setText(datetext);

}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Status_Read_clicked()
{
        //i2cget -f -y 0 0x24 0x05  == 0x28 before fuse burn; 0xa8 after fuse burn;
        struct i2c_rdwr_ioctl_data packets;
        int file1;
        int bus = 0; // probably dynamically determined
        char filename[20];
        char buf[10];
        snprintf(filename, 19, "/dev/i2c-%d", bus);
        file1 = open(filename, O_RDWR);
        if (file1 < 0)
        {
            perror("Failed to open the i2c bus");
            exit(1);
        }
        int addr = 0x24; // The I2C address
        __u8 reg = 0x05;
        if (ioctl(file1, I2C_SLAVE, addr) < 0)
        {
            perror("Failed to talk to slave address");
            exit(1);
        }
        buf[0] = (reg >> 0) & 0xFF;
        if (read(file1, buf, 1) != 1)
        {
            perror("i2c transaction failed");
        }
        //read i2c address
         else
        {
            unsigned char reg_buf;
            //read(file1, buf, 1);
            if (ioctl(file1,  I2C_RDWR, &packets) < 0)
            {
                //return 0;
            }
        }
}
void MainWindow::on_i2creg_write_clicked()
{
        int file;
        int bus = 0; /* probably dynamically determined */
        char filename[20];
        char buf[10];

        //////////////////////////////////////////////////////////////////
        // int snprintf(char *str, size_t size, const char *format, …); //
        //////////////////////////////////////////////////////////////////

        snprintf(filename, 19, "/dev/i2c-%d", bus);
        file = open(filename, O_RDWR);
        if (file < 0)
        {
            /* ERROR HANDLING; you can check errno to see what went wrong */
            perror("Failed to open the i2c bus");
            exit(1);
        }
        //    When you have opened the device, you must specify with what device
        //    address you want to communicate:
         int addr = 0x24; /* The I2C address of RTC chip */
         if (ioctl(file, I2C_SLAVE, addr) < 0)
         {
            perror("Failed to fetch the slave address");
            exit(1);
         }
         __u8 reg = 0x05; /* Device register to access */
         buf[0] = reg;
         buf[1] = 0x43;
         buf[2] = 0x65;
         if (write(file, buf, 3) != 3)
         {
          /* ERROR HANDLING: i2c transaction failed */
         }
}
void MainWindow::update_date_time()
{
//        QDateEdit *dateEdit = new QDateEdit(this);
//        QTimeEdit *timeEdit = new QTimeEdit(this);
//    ui->daeTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->dateEdit->displayFormat();
        ui->label->setText(ui->timeEdit->text());
        ui->label->update();
        ui->label_2->setText(ui->dateEdit->text());
        ui->label_2->update();

}


void MainWindow::on_set_date_clicked()
{

//    QDateTime dateTimeEdit=new QDateTimeEdit(QDateTime::currentDateTime(),this);
//    dateTimeEdit->setDisplayFormat("yyyy.MMM.dd hh:mm");
//    exec=new QProcess(this)
//    exec->start("touch", QStringList() << "-t" <<dateTimeEdit->dateTime().toString("yyyyMMddhhmm")<<file_path);
//    exec->waitForFinished();
          QTime newModifiedTime = ui->timeEdit->time();
            QDate newModifiedDate=ui->dateEdit->date();
//        QDateTime newCreationDate=TimeEdit_Creation->dateTime();


//        system("date -s \"date");
//           system("date -s \"newModifiedTime newModifiedDate");
//        system("hwclock -w");
//        system("reboot");
        update_date_time();
}
