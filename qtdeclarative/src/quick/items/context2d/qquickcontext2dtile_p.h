/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKCONTEXT2DTILE_P_H
#define QQUICKCONTEXT2DTILE_P_H

#include "qquickcontext2d_p.h"
#include <QOpenGLFramebufferObject>

QT_BEGIN_NAMESPACE

class QQuickContext2DTexture;
class QQuickContext2DCommandBuffer;

class QQuickContext2DTile
{
public:
    QQuickContext2DTile();
    virtual ~QQuickContext2DTile();

    bool dirty() const {return m_dirty;}
    void markDirty(bool dirty) {m_dirty = dirty;}

    QRect rect() const {return m_rect;}

    virtual void setRect(const QRect& r) = 0;
    virtual QPainter* createPainter(bool smooth, bool antialiasing);
    virtual void drawFinished() {}

protected:
    virtual void aboutToDraw() {}
    uint m_dirty : 1;
    QRect m_rect;
    QPaintDevice* m_device;
    QPainter m_painter;
};


class QQuickContext2DFBOTile : public QQuickContext2DTile
{
public:
    QQuickContext2DFBOTile();
    ~QQuickContext2DFBOTile();
    virtual void setRect(const QRect& r);
    QOpenGLFramebufferObject* fbo() const {return m_fbo;}
    void drawFinished();

protected:
    void aboutToDraw();
private:


    QOpenGLFramebufferObject *m_fbo;
};

class QQuickContext2DImageTile : public QQuickContext2DTile
{
public:
    QQuickContext2DImageTile();
    ~QQuickContext2DImageTile();
    void setRect(const QRect& r);
    const QImage& image() const {return m_image;}
private:
    QImage m_image;
};
QT_END_NAMESPACE

#endif // QQUICKCONTEXT2DTILE_P_H
