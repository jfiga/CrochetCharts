/****************************************************************************\
 Copyright (c) 2010-2014 Stitch Works Software
 Brian C. Milco <bcmilco@gmail.com>

 This file is part of Crochet Charts.

 Crochet Charts is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Crochet Charts is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Crochet Charts. If not, see <http://www.gnu.org/licenses/>.

 \****************************************************************************/
#include "testcell.h"
#include "../src/ChartItemTools.h"
#include "../src/stitchlibrary.h"

#include <QPainter>
#include <QFile>
#include <QCryptographicHash>
#include <QSvgGenerator>

void TestCell::initTestCase()
{
    i = 0;

    StitchLibrary::inst()->loadStitchSets();
}

void TestCell::setCellValues()
{
    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);

    Cell* c = new Cell();
    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QVERIFY(c->sceneBoundingRect().width() == width);
    QVERIFY(c->sceneBoundingRect().height() == height);

    delete c;
    c = 0;

}

void TestCell::setCellValues_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0;
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0;
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0;

}

void TestCell::setRotation()
{
    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, angle);
    QFETCH(QString, rasterHash);

    Cell* c = new Cell();
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setRotation(angle);

    QString rasterImage = "TestCell-SetRotation-" + QString::number(i) + "-" + name + ".png";

    saveSceneSvg(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setRotation_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("angle");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 45.0 << "4c0b196681ae83f9f9c1835abfde7c2b86d379a8";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 45.0 << "45561bb6d7454205da5fa37fa22e01e043f74255";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 45.0 << "09c1a34efff5eb2774e51147b2960f01402975f2";

}

void TestCell::setScale()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, scaleX);
    QFETCH(qreal, scaleY);
    QFETCH(QString, rasterHash);

    Cell* c = new Cell();
    QGraphicsScene *scene = new QGraphicsScene();

    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    ChartItemTools::setScaleX(c, scaleX);
    ChartItemTools::setScaleY(c, scaleY);

    QString rasterImage = "TestCell-ScaleTest-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setScale_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("scaleX");
    QTest::addColumn<qreal>("scaleY");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 1.0 << 1.0 << "7d1cdaeb6750679933628de65d3bf6e3e39598d8";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 2.5 << 2.5 << "91e5a3165e6e466bc1b1e2cdf45932b370a9b2de";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 2.5 << 2.5 << "5b3432ae2d25a8e76aa73f895db680d3fca4681c";
}

void TestCell::setBgColor()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(QString, color);
    QFETCH(QString, rasterHash);

    QGraphicsScene *scene = new QGraphicsScene();
    Cell* c = new Cell();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setBgColor(QColor(color));

    QString rasterImage = "TestCell-BgColor-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setBgColor_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<QString>("color");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << "#0000FF" << "02513fdc49de5f6e7dfe6bd3bf02011b27f9d1b5";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << "#FF0000" << "4df2003561727ffecac22d3f11e47d813dfa4e88";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << "#00FF00" << "d90842263fd9d49753edf69b112c23673e33d6e0";

}

void TestCell::setAllProperties()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, angle);
    QFETCH(qreal, scaleX);
    QFETCH(qreal, scaleY);
    QFETCH(QString, color);
    QFETCH(QString, rasterHash);

    QGraphicsScene *scene = new QGraphicsScene();
    Cell* c = new Cell();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setBgColor(QColor(color));
    c->setRotation(angle);
    ChartItemTools::setScaleX(c, scaleX);
    ChartItemTools::setScaleY(c, scaleY);


    QString rasterImage = "TestCell-AllProperties-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setAllProperties_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("angle");
    QTest::addColumn<qreal>("scaleX");
    QTest::addColumn<qreal>("scaleY");
    QTest::addColumn<QString>("color");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 45.0 << 1.5 << 2.0 << "#0000FF"
                                    << "660213a2bc03665a8eacf3f57197e49676f92f76";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 45.0 << 1.5 << 2.0 << "#FF0000"
                                    << "06b49f17c9b6273fb854e5e6c0d292b3297ffc8d";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 45.0 << 1.5 << 2.0 << "#00FF00"
                                    << "e614ba3c97df4df135794dcc4d841df2cf185ae5";

}

void TestCell::saveScene(QGraphicsScene* scene, QSizeF size, QString fileName)
{

    scene->setSceneRect(scene->itemsBoundingRect());

    QPixmap pix = QPixmap(scene->sceneRect().width(), scene->sceneRect().height());
    pix.fill(QColor(Qt::white));
    QPainter p;
    p.begin(&pix);
    scene->render(&p);
    p.end();
    pix.save(fileName, "PNG", 100);

}

void TestCell::saveSceneSvg(QGraphicsScene* scene, QSizeF size, QString fileName)
{
    scene->setSceneRect(scene->itemsBoundingRect());

    QPainter p;
    QSvgGenerator gen;
    gen.setFileName(fileName);
    gen.setSize(size.toSize());
    gen.setViewBox(QRectF(0,0,size.width(),size.height()));

    p.begin(&gen);
    scene->render(&p);
    p.end();

}

QString TestCell::hashFile(QString fileName)
{
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly)) {
        qFatal("Could not compare png file with expected results");
    }

    QByteArray data = f.readAll();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

    QString hexHash = hash.toHex();
    f.flush();
    f.close();

    return hexHash;
}

void TestCell::cleanupTestCase()
{
}
