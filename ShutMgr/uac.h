//from https://blog.csdn.net/zyhse/article/details/108166181
#ifndef UAC_H
#define UAC_H

#include <ShlObj_core.h>
#include <QCoreApplication>

// for IsUserAnAdmin()
#pragma comment (lib, "Shell32.lib")

namespace UAC
{
    // �Թ���ԱȨ������һ����ʵ��
    // true-��������ʵ��
    // false-δ������ʵ��
    static bool runAsAdmin()
    {
        if (IsUserAnAdmin())
        {
            return false; // ��ǰ�������Թ���ԱȨ������
        }

        QStringList args = QCoreApplication::arguments(); // ��ȡ�����в���
        if (args.count() < 2 || args[1] != "runas") // ���������������Ϊ"runas"ʱ����ֱ������
        {
            // ��ȡӦ�ó����ִ���ļ���·��
            QString filePath = QCoreApplication::applicationFilePath();

            // �Թ���ԱȨ�ޣ�ִ��exe����
            HINSTANCE ins = ShellExecuteA(nullptr, "runas", filePath.toStdString().c_str(),
                                          "runas", nullptr, SW_SHOWNORMAL);
            if (ins > (HINSTANCE)32)
            {
                return true; // ������ʵ�������ɹ�
            }
        }
        return false;
    }
};

#endif // UAC_H