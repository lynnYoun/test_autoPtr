#include "capturesetting.hpp"

using namespace std;
using namespace App;


CaptureSetting::CaptureSetting()
{
    this->m_imgWidth = 4096;                //定义图片的宽度为4096
    this->m_imgHeight = 3072;               //定义图片的高度为3072
    this->m_imgBit = ImgBit::BIT8;          //相机默认的图像位数为8位
}

CaptureSetting::~CaptureSetting()
{

}

void CaptureSetting::readCaptureSetting(const QString& path)
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        if(!QFile::exists(path))                //如果文件不存在,则直接抛出异常信息
        {
            THROW_EXCEPTION("读取CapturSetting文件失败!");
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        else                                   //如果文件存在,则读取文件中的数据
        {
            //将类QSettings实例化一个对象
            //path:存放文件的路径,QSettings::IniFormat: 为存放文件的格式
            QSettings configFile(path,QSettings::IniFormat);

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //读取文件Image/Width(图像宽度)数据,并判断是否与系统默认值匹配
            //如果不匹配,则抛出异常
            int imgWidth = configFile.value("Image/Width").toInt();

            if( this->m_imgWidth != imgWidth )
            {
                THROW_EXCEPTION("读取文件数据Image/Width失败!");
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //读取文件Image/Height(图像高度)数据,并判断是否与系统默认值匹配,
            //如果不匹配,则抛出异常
            int imgHeight = configFile.value("Image/Height").toInt();

            if( this->m_imgHeight !=  imgHeight)
            {
                THROW_EXCEPTION("读取文件数据Image/Height失败!");
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //读取文件Image/ImgBit数据,并判断是否是枚举中的元素
            //如果不匹配,则抛出异常
            QString imgBit = configFile.value("Image/ImgBit").toString();

            if(imgBit.toUpper().toStdString() == VAR_TO_STR(ImgBit::BIT8))
            {
                this->m_imgBit = ImgBit::BIT8;
            }
            else if (imgBit.toUpper().toStdString() == VAR_TO_STR(ImgBit::BIT16))
            {
                this->m_imgBit = ImgBit::BIT16;
            }
            else
            {
                THROW_EXCEPTION("读取文件数据Image/ImgBit失败!");
            }
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("读取capture.ini文件异常");
}

void CaptureSetting::writeCaptureSetting(const QString &path)
{
    try
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //将类QSettings实例化一个对象
        //path:存放文件的路径
        //QSettings::IniFormat: 为存放文件的格式
        QSettings configFile(path,QSettings::IniFormat);

        //将Image/Width的数据写为系统默认值,默认为"4096"
        configFile.setValue("Image/Width",this->m_imgWidth);
        //将Image/Height的数据写为系统默认值,默认为"3072"
        configFile.setValue("Image/Height",this->m_imgHeight);
        //将Image/Height的数据写为系统默认值,默认为"BIT8"
        configFile.setValue("Image/ImgBit","BIT8");
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch(const exception &ex)
    {
        //捕获异常,并抛出
        THROW_EXCEPTION(ex.what());
    }
}
