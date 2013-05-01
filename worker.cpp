/*
   Copyright 2013 Fabien Pierre-Nicolas.
      - Primarily authored by Fabien Pierre-Nicolas

   This file is part of simple-qt-thread-example, a simple example to demonstrate how to use threads.
   This example is explained on http://fabienpn.wordpress.com/qt-thread-simple-and-stable-with-sources/

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This progra is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "worker.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}

void Worker::abort()
{
    mutex.lock();
    _abort = true;
    qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    mutex.unlock();
}

void Worker::doWork()
{
    mutex.lock();
    _abort = false;
    mutex.unlock();

    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

    for (int i = 0; i < 60; i ++) {

        // Checks if the process should be aborted
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();

        if (abort) {
            qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
            break;
        }

        // This will stupidly wait 1 sec doing nothing...
        QTimer timer;
        timer.setSingleShot(true);
        timer.setInterval(1000);
        QEventLoop loop;
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start();
        loop.exec();

        // Once we're done waiting, value is updated
        emit valueChanged(QString::number(i));
    }

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}
