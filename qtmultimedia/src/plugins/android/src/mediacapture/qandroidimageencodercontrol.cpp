/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
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

#include "qandroidimageencodercontrol.h"

#include "qandroidcamerasession.h"
#include "androidcamera.h"

QT_BEGIN_NAMESPACE

QAndroidImageEncoderControl::QAndroidImageEncoderControl(QAndroidCameraSession *session)
    : QImageEncoderControl()
    , m_session(session)
{
    connect(m_session, SIGNAL(opened()),
            this, SLOT(onCameraOpened()));
}

QStringList QAndroidImageEncoderControl::supportedImageCodecs() const
{
    return QStringList() << QLatin1String("jpeg");
}

QString QAndroidImageEncoderControl::imageCodecDescription(const QString &codecName) const
{
    if (codecName == QLatin1String("jpeg"))
        return tr("JPEG image");

    return QString();
}

QList<QSize> QAndroidImageEncoderControl::supportedResolutions(const QImageEncoderSettings &settings, bool *continuous) const
{
    Q_UNUSED(settings);

    if (continuous)
        *continuous = false;

    return m_supportedResolutions;
}

QImageEncoderSettings QAndroidImageEncoderControl::imageSettings() const
{
    return m_session->imageSettings();
}

void QAndroidImageEncoderControl::setImageSettings(const QImageEncoderSettings &settings)
{
    m_session->setImageSettings(settings);
}

void QAndroidImageEncoderControl::onCameraOpened()
{
    m_supportedResolutions = m_session->camera()->getSupportedPictureSizes();
}

QT_END_NAMESPACE
